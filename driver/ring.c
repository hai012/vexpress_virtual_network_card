
#include <linux/types.h> 
#include "mynet.h"




int ring_init(void)
{
    size_t node_count = (1+real_tx_channel_count) * tx_ring_node_count +
                        (1+real_rx_channel_count) * rx_ring_node_count;
    ring_node_info_table = devm_kcalloc(netdev,node_count,sizeof(struct ring_node_info),GFP_KERNEL);
    if(unlikely(!ring_node_info_table)) {
        pr_err("%s:alloc  ring_node_info_table failed",__func__);
        return -1;
    }
    pool = dma_pool_create("dma_pool",netdev, sizeof(struct ring_node_t),4,0);
    if(unlikely(!pool)) {
        pr_err("%s:dma_pool_create failed",__func__);
        devm_kfree(ring_node_info_table);
        return -1;
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
    for(int i=0; i< real_rx_channel_count ++i) {
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
    dma_pool_destroy(pool);
    devm_kfree(dev,ring_node_info_table);
    return -1;
}
//void dma_pool_free(struct dma_pool *pool, void *vaddr, dma_addr_t dma)



int rx_ring_dma_init(void)
{
    int channelIndex;
    struct napi_struct *napi;
    struct ring_node_info *rx_ring_start;
    struct ring_node_info * init_node;
    struct ring_node_info * deinit_node;

    for(channelIndex=0; channelIndex<real_rx_channel_count; ++channelIndex) {
        rx_ring_start=channel_info[channelIndex].rx_ring;
        for(init_node=rx_ring_start; init_node->next != rx_ring_start; init_node=init_node->next)
        {
            char *liner_buffer = netdev_alloc_frag(MAX_RX_SKB_LINEAR_BUFF_LEN);
            if(unlikely(!liner_buffer)) {
                pr_err("netdev_alloc_frag failed");
                goto err_clean_previous;
            }
            //skb_reserve(skb, 2);
            //skb_record_rx_queue(skb,channelIndex);
            dma_addr_t dma_addr = dma_map_single(netdev,
                                                 liner_buffer + ETH_HEADER_OFFSET_IN_LINEAR_BUFF,
                                                 MAX_RECV_LEN,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(netdev, dma_addr))) {
                pr_err("dma_map_single dma_dst_addr failed");
                skb_free_frag(liner_buffer);  //page_frag_free
                goto err_clean_previous;
            }
            init_node->liner_buffer = liner_buffer;
            writel_relaxed(dma_addr,                        &init_node->virtual_addr->base);
            writel_relaxed(MAX_RECV_LEN,                    &init_node->virtual_addr->len);
            writel_relaxed(NODE_F_TRANSFER|NODE_F_BELONG,   &init_node->virtual_addr->flag);
        }
    }
    return 0;

err_clean_previous:
    for(; channelIndex >= 0; --channelIndex) {
        for(struct ring_node_info * deinit_node=channel_info[channelIndex].rx_ring;
            deinit_node != init_node;
            deinit_node = deinit_node->next)
        {
            dma_unmap_single(netdev,
                             deinit_node->virtual_addr->base,
                             MAX_RX_SKB_BUFF_LEN-2,
                             DMA_FROM_DEVICE);
            skb_free_frag(deinit_node->liner_buffer);
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
    int num_dma_bufs;
    int num_sg;
    scl = devm_kmalloc_array(netdev,nr_frags + 1, sizeof(struct scatterlist), GFP_KERNEL);
    if (unlikely(!scl))
      	return -ENOMEM;
    sg_init_table(scl, nr_frags + 1);
    num_sg = skb_to_sgvec(skb, scl, 0, skb->len);
    if (unlikely(num_sg < 0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }
    //num_dma_bufs <= num_sg
    num_dma_bufs = dma_map_sg(netdev, scl, num_sg, DMA_TO_DEVICE);
    if (unlikely(num_dma_bufs<=0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }


    //check if it has enough node to fill
    spin_lock(&channel->spinlock_tx_ring_empty);
    int nodes_need = num_dma_bufs;
    for(struct ring_node_info *node=channel->tx_ring_empty;
        node->next != channel->tx_ring_full;
        node=node->next) {
            if(nodes_need--)
                break;
    }
    if(nodes_need) {
        //pr_err("it dose not have enough node to fill head and frags,wait for send previous node\n");
        goto dma_unmap;
        return -1;
    }

    //start fill content
    struct ring_node_info * fill = channel->tx_ring_empty;
    struct ring_node_t *node_table[MAX_SKB_FRAGS];
    for_each_sg(scl, crt_scl, num_dma_bufs, i) {
        node_table[i] = fill;
        writel_relaxed(sg_dma_address(crt_scl), &fill->virtual_addr->base);
        writel_relaxed(sg_dma_len(crt_scl), &fill->virtual_addr->len);
        fill = fill -> next;
    }
    if(num_dma_bufs==1) {
        node_table[0]->skb = skb;
        node_table[0]->scl = slc;
        node_table[0]->num_sg = num_sg;
        writel(node_table[0]->virtual_addr->flag, NODE_F_TRANSFER|NODE_F_BELONG);
    } else {
        node_table[num_dma_bufs-1]->skb = skb;
        node_table[num_dma_bufs-1]->scl = slc;
        node_table[num_dma_bufs-1]->num_sg = num_sg;
        writel_relaxed(node_table[num_dma_bufs-1]->virtual_addr->flag, NODE_F_TRANSFER|NODE_F_BELONG);
        for (int i=num_dma_bufs-2; i>0; ++i) {
            writel_relaxed(node_table[i]->virtual_addr->flag, NODE_F_BELONG);
        }
        writel(node_table[0]->virtual_addr->flag, NODE_F_BELONG);
    }

    channel->tx_ring_empty = fill;
    spin_unlock(&channel->spinlock_tx_ring_empty);
    return 0;

dma_unmap:
    spin_unlock(&channel->spinlock_tx_ring_empty);
	dma_unmap_sg(netdev, scl, num_sg, DMA_TO_DEVICE);
dma_map_sg_failed:
	devm_kfree(netdev,scl);
	return err;
}

