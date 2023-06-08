#include <linux/scatterlist.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/spinlock_types.h>
#include <linux/dmapool.h>
#include "mynet.h"

static struct dma_pool * pool;
static struct ring_node_info *ring_node_info_table;


int ring_init(void)
{
    size_t node_count = real_tx_channel_count * tx_ring_node_count +
                        real_rx_channel_count * rx_ring_node_count;
    ring_node_info_table = devm_kcalloc(&pdev->dev,node_count,sizeof(struct ring_node_info),GFP_KERNEL);
    if(unlikely(!ring_node_info_table)) {
        pr_err("%s:alloc  ring_node_info_table failed",__func__);
        return -ENOMEM;
    }
    pool = dmam_pool_create(pdev->name,&pdev->dev, sizeof(struct ring_node_t),4,0);
    if(unlikely(!pool)) {
        pr_err("%s:dma_pool_create failed",__func__);
        kfree(ring_node_info_table);
        return -ENOMEM;
    }

    struct ring_node_info *ptr;
    for(int i=0; i<real_tx_channel_count; ++i) {
        ptr = ring_node_info_table + i*tx_ring_node_count;
        ptr->virtual_addr = dma_pool_zalloc(pool, GFP_KERNEL, &ptr->dma_addr);
        if(unlikely(!ptr->virtual_addr)) {
            goto err_out;
        }
        for(int j=1; j< tx_ring_node_count; ++j) {
            (ptr+j)->virtual_addr = dma_pool_zalloc(pool, GFP_KERNEL, &(ptr+j)->dma_addr);
            if(unlikely(!(ptr+j)->virtual_addr)) {
                goto err_out;
            }
            (ptr+j-1)->next = (ptr+j);
            (ptr+j-1)->virtual_addr->next = (ptr+j)->dma_addr;
        }
        (ptr+tx_ring_node_count-1)->next = ptr;
        (ptr+tx_ring_node_count-1)->virtual_addr->next = ptr->dma_addr;
        channel_info[i].tx_ring_empty = ptr;
        channel_info[i].tx_ring_full = ptr;
    }
    for(int i=0; i< real_rx_channel_count; ++i) {
        ptr = ring_node_info_table + real_tx_channel_count * tx_ring_node_count +i;
        ptr->virtual_addr = dma_pool_zalloc(pool, GFP_KERNEL, &ptr->dma_addr);
        if(unlikely(!ptr->virtual_addr)) {
            goto err_out;
        }
        for(int j=1; j< rx_ring_node_count; ++j) {
            (ptr+j)->virtual_addr = dma_pool_zalloc(pool, GFP_KERNEL, &(ptr+j)->dma_addr);
            if(unlikely(!(ptr+j)->virtual_addr)) {
                goto err_out;
            }
            (ptr+j-1)->next = (ptr+j);
            (ptr+j-1)->virtual_addr->next = (ptr+j)->dma_addr;
        }
        (ptr+rx_ring_node_count-1)->next = ptr;
        (ptr+rx_ring_node_count-1)->virtual_addr->next = ptr->dma_addr;
        channel_info[i].rx_ring = ptr;
    }

    if(unlikely(rx_ring_dma_init())) {
        pr_err("%s:fail to alloc and map skb for rx_ring",__func__);
        goto err_out;
    }
    return 0;

err_out:
    for(size_t index=0; index<node_count; ++index) {
        struct ring_node_info *node = ring_node_info_table + index;
        if(node->virtual_addr)
            dma_pool_free(pool, node->virtual_addr, node->dma_addr);
        else
            break;
    }
    dmam_pool_destroy(pool);
    devm_kfree(&pdev->dev,ring_node_info_table);
    return -ENOMEM;
}
//void dma_pool_free(struct dma_pool *pool, void *vaddr, dma_addr_t dma)



int rx_ring_dma_init(void)
{
    int channelIndex;
    struct ring_node_info * init_start;
    struct ring_node_info * init_end;

    for(channelIndex=0; channelIndex<real_rx_channel_count; ++channelIndex) {
        init_start=channel_info[channelIndex].rx_ring;
        init_end=channel_info[channelIndex].rx_ring;
        do
        {
            struct napi_alloc_cache *nc = per_cpu_ptr(&napi_alloc_cache, channelIndex);
            char *liner_buffer = page_frag_alloc_align(&nc->page, MAX_RX_SKB_LINEAR_BUFF_LEN, GFP_KERNEL, 0);
            if(unlikely(!liner_buffer)) {
                pr_err("netdev_alloc_frag failed");
                goto err_clean_previous;
            }
            //skb_reserve(skb, 2);
            //skb_record_rx_queue(skb,channelIndex);
            dma_addr_t dma_addr = dma_map_single(&pdev->dev,
                                                 liner_buffer + ETH_HEADER_OFFSET_IN_LINEAR_BUFF,
                                                 MAX_RECV_LEN,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(&pdev->dev, dma_addr))) {
                pr_err("dma_map_single dma_dst_addr failed");
                skb_free_frag(liner_buffer);  //page_frag_free
                goto err_clean_previous;
            }
            init_start->linear_buffer = liner_buffer;
            writel_relaxed(dma_addr,                        &init_start->virtual_addr->base);
            writel_relaxed(MAX_RECV_LEN,                    &init_start->virtual_addr->len);
            writel_relaxed(NODE_F_TRANSFER|NODE_F_BELONG,   &init_start->virtual_addr->flag);

            init_start = init_start->next;
        }while(init_start != init_end);
    }
    return 0;

err_clean_previous:
    for(; channelIndex >= 0; --channelIndex) {
        for(struct ring_node_info * deinit_start=channel_info[channelIndex].rx_ring;
            deinit_start != init_start;
            deinit_start = deinit_start->next)
        {
            dma_unmap_single(&pdev->dev,
                             deinit_start->virtual_addr->base,
                             deinit_start->virtual_addr->len,
                             DMA_FROM_DEVICE);
            skb_free_frag(deinit_start->linear_buffer);
        }
    }
    return -1;
}

//Q----CPU0
//  \--CPU1    ? 
int insert_skb_to_tx_ring(struct channel_data * channel,struct sk_buff *skb)
{
    int err;

/* Create and map scatterlist.
* We don't advertise NETIF_F_FRAGLIST, so skb_to_sgvec() will not have
* to go beyond nr_frags+1.
* Note: We don't support chained scatterlists*/
    struct scatterlist *scl, *crt_scl;
    unsigned int num_dma_bufs,i;
    int num_sg;
    unsigned int frag_count = skb_shinfo(skb)->nr_frags + 1;
    scl = devm_kmalloc_array(&pdev->dev,frag_count, sizeof(struct scatterlist), GFP_KERNEL);
    if (unlikely(!scl))
      	return -ENOMEM;
    sg_init_table(scl, frag_count);
    num_sg = skb_to_sgvec(skb, scl, 0, skb->len);
    if (unlikely(num_sg < 0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }
    //num_dma_bufs <= num_sg
    num_dma_bufs = dma_map_sg(&pdev->dev, scl, num_sg, DMA_TO_DEVICE);
    if (unlikely(num_dma_bufs==0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }


    //check if it has enough node to fill
    spin_lock(&channel->spinlock_tx_ring_empty);
    unsigned int nodes_need = num_dma_bufs;
    for(struct ring_node_info *node=channel->tx_ring_empty;
        node->next != channel->tx_ring_full;
        node=node->next) {
            if(nodes_need--)
                break;
    }
    if(nodes_need) {
        //pr_err("it dose not have enough node to fill head and frags,wait for send previous node\n");
        err = -EBUSY;
        goto dma_unmap;
    }

    //start fill content
    struct ring_node_info * fill = channel->tx_ring_empty;
    struct ring_node_info *node_table[MAX_SKB_FRAGS];
    for_each_sg(scl, crt_scl, num_dma_bufs, i) {
        node_table[i] = fill;
        writel_relaxed(sg_dma_address(crt_scl), &fill->virtual_addr->base);
        writel_relaxed(sg_dma_len(crt_scl), &fill->virtual_addr->len);
        fill = fill -> next;
    }
    if(num_dma_bufs==1) {
        node_table[0]->skb = skb;
        node_table[0]->scl = scl;
        node_table[0]->num_sg = num_sg;
        writel(NODE_F_TRANSFER|NODE_F_BELONG, &node_table[0]->virtual_addr->flag);
    } else {
        node_table[num_dma_bufs-1]->skb = skb;
        node_table[num_dma_bufs-1]->scl = scl;
        node_table[num_dma_bufs-1]->num_sg = num_sg;
        writel_relaxed(NODE_F_TRANSFER|NODE_F_BELONG, &node_table[num_dma_bufs-1]->virtual_addr->flag);
        for (int i=num_dma_bufs-2; i>0; ++i) {
            writel_relaxed(NODE_F_BELONG, &node_table[i]->virtual_addr->flag);
        }
        writel(NODE_F_BELONG, &node_table[0]->virtual_addr->flag);
    }

    channel->tx_ring_empty = fill;
    spin_unlock(&channel->spinlock_tx_ring_empty);

    return 0;

dma_unmap:
    spin_unlock(&channel->spinlock_tx_ring_empty);
	dma_unmap_sg(&pdev->dev, scl, num_sg, DMA_TO_DEVICE);
dma_map_sg_failed:
	devm_kfree(&pdev->dev,scl);
	return err;
}


void ring_deinit()
{
    int channelIndex;
    struct ring_node_info * deinit_start;
    struct ring_node_info * deinit_end;

    for(channelIndex=0; channelIndex<real_rx_channel_count; ++channelIndex) {
        deinit_start = deinit_end =  channel_info[channelIndex].rx_ring;
        do{
            dma_unmap_single(&pdev->dev,
                             deinit_start->virtual_addr->base,
                             deinit_start->virtual_addr->len,
                             DMA_FROM_DEVICE);
            skb_free_frag(deinit_start->linear_buffer);
            dma_pool_free(pool, deinit_start->virtual_addr, deinit_start->dma_addr);
            deinit_start = deinit_start->next;
        }while(deinit_start != deinit_end);

        deinit_start = channel_info[channelIndex].tx_ring_full;
        deinit_end = channel_info[channelIndex].tx_ring_empty;
        while(deinit_start != deinit_end) {
            if(is_node_transfer(deinit_start)) {
                //now , we find the last frag
                dma_unmap_sg(&pdev->dev, deinit_start->scl, deinit_start->num_sg, DMA_FROM_DEVICE);
                devm_kfree(&pdev->dev,deinit_start->scl);
                kfree_skb(deinit_start->skb);
                dma_pool_free(pool, deinit_start->virtual_addr, deinit_start->dma_addr);
            }
            deinit_start = deinit_start->next;
        }
    }

    dmam_pool_destroy(pool);
    devm_kfree(&pdev->dev,ring_node_info_table);
}