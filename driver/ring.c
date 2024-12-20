#include <linux/scatterlist.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/spinlock_types.h>
#include <linux/dmapool.h>
#include <linux/gfp.h>

#include "mynet.h"

static struct dma_pool * pool;
static struct ring_node_info *ring_node_info_table;

void dump_ring(void);
void dump_ring(void)
{
    struct ring_node_info *ptr;
    pr_err("\n\n\n\n\n");
    for(int i=0; i< real_tx_channel_count; ++i) {
        ptr = ring_node_info_table + i * tx_ring_node_count;
        for(int j=0; j< tx_ring_node_count; ++j) {
            pr_err("MYNET:%d:TX:ring_node info_kva=0x%08x info_next=0x%08x node_base_kva=0x%08x node_base_phy=0x%08x flag=0x%08x base=0x%08x len=0x%08x next=0x%08x\n",
                        i,(uint32_t)(ptr+j),(uint32_t)(ptr+j)->next,
                        (uint32_t)(ptr+j)->virtual_addr,        (ptr+j)->dma_addr,
                        (ptr+j)->virtual_addr->flag,  (ptr+j)->virtual_addr->base,
                        (ptr+j)->virtual_addr->len,   (ptr+j)->virtual_addr->next);
        }
    }
    for(int i=0; i< real_rx_channel_count; ++i) {
        ptr = ring_node_info_table + real_tx_channel_count * tx_ring_node_count + i * rx_ring_node_count;
        for(int j=0; j< rx_ring_node_count; ++j) {
            pr_err("MYNET:%d:RX:ring_node info_kva=0x%08x info_next=0x%08x node_base_kva=0x%08x node_base_phy=0x%08x flag=0x%08x base=0x%08x len=0x%08x next=0x%08x\n",
                        i,(uint32_t)(ptr+j),(uint32_t)(ptr+j)->next,
                        (uint32_t)(ptr+j)->virtual_addr,        (ptr+j)->dma_addr,
                        (ptr+j)->virtual_addr->flag,  (ptr+j)->virtual_addr->base,
                        (ptr+j)->virtual_addr->len,   (ptr+j)->virtual_addr->next);
        }
    }
}

int ring_init(void)
{
    struct ring_node_info *ptr;
    size_t node_count = real_tx_channel_count * tx_ring_node_count +
                        real_rx_channel_count * rx_ring_node_count;
    

    ring_node_info_table = devm_kcalloc(&pdev->dev,node_count,sizeof(struct ring_node_info),GFP_KERNEL);
    if(unlikely(!ring_node_info_table)) {
        pr_err("%s:alloc  ring_node_info_table failed\n",__func__);
        return -ENOMEM;
    }
    pool = dmam_pool_create(pdev->name,&pdev->dev, sizeof(struct ring_node_t),4,0);
    if(unlikely(!pool)) {
        pr_err("%s:dma_pool_create failed\n",__func__);
        kfree(ring_node_info_table);
        return -ENOMEM;
    }

    //dma_pool_zalloc底层是dma_alloc_coherent连续映射
    for(int i=0; i<real_tx_channel_count; ++i) {
        ptr = ring_node_info_table + i * tx_ring_node_count;
        for(int j=0; j< tx_ring_node_count; ++j) {
            (ptr+j)->virtual_addr = dma_pool_zalloc(pool, GFP_KERNEL|GFP_DMA, &(ptr+j)->dma_addr);
            if(unlikely(!(ptr+j)->virtual_addr)) {
                goto err_out;
            }
        }
        
        for(int j=0; j<tx_ring_node_count-1; ++j) {
            (ptr+j)->next = (ptr+j+1);
            (ptr+j)->virtual_addr->next = (ptr+j+1)->dma_addr;
        }
        (ptr+tx_ring_node_count-1)->next = ptr;
        (ptr+tx_ring_node_count-1)->virtual_addr->next = ptr->dma_addr;
        channel_info[i].tx_ring_empty = ptr;
        channel_info[i].tx_ring_full = ptr;
    }
    for(int i=0; i< real_rx_channel_count; ++i) {
        ptr = ring_node_info_table + real_tx_channel_count * tx_ring_node_count + i * rx_ring_node_count;
        for(int j=0; j< rx_ring_node_count; ++j) {
            (ptr+j)->virtual_addr = dma_pool_zalloc(pool, GFP_KERNEL|GFP_DMA, &(ptr+j)->dma_addr);
            if(unlikely(!(ptr+j)->virtual_addr)) {
                goto err_out;
            }
        }
        for(int j=0; j<rx_ring_node_count-1; ++j) {
            (ptr+j)->next = (ptr+j+1);
            (ptr+j)->virtual_addr->next = (ptr+j+1)->dma_addr;
        }
        (ptr+rx_ring_node_count-1)->next = ptr;
        (ptr+rx_ring_node_count-1)->virtual_addr->next = ptr->dma_addr;
        channel_info[i].rx_ring = ptr;
    }

    //dump_ring();

    if(unlikely(rx_ring_dma_init())) {
        pr_err("%s:fail to alloc and map skb for rx_ring\n",__func__);
        goto err_out;
    }
    
    //dump_ring();


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


/*

get_online_cpus()
for_each_online_cpu(cpuid){

}
put_online_cpus()

*/




int rx_ring_dma_init(void)
{
    int channelIndex;
    struct ring_node_info * init_start;
    struct ring_node_info * init_end;
    dma_addr_t dma_addr;

    for(channelIndex=0; channelIndex<real_rx_channel_count; ++channelIndex) {
        init_start=channel_info[channelIndex].rx_ring;
        init_end=channel_info[channelIndex].rx_ring;
        do
        {
            //pr_err("channelIndex=%d,MAX_RX_SKB_LINEAR_BUFF_LEN=%d\n",channelIndex,MAX_RX_SKB_LINEAR_BUFF_LEN);
            char *liner_buffer = page_frag_alloc_align(&channel_info[channelIndex].page_cache, MAX_RX_SKB_LINEAR_BUFF_LEN, GFP_KERNEL|GFP_DMA, 0);
            if(unlikely(!liner_buffer)) {
                pr_err("netdev_alloc_frag failed\n");
                goto err_clean_previous;
            }
            dma_addr = dma_map_single(&pdev->dev,
                                                 liner_buffer + ETH_HEADER_OFFSET_IN_LINEAR_BUFF,
                                                 MAX_RECV_LEN,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(&pdev->dev, dma_addr))) {
                pr_err("dma_map_single dma_dst_addr failed\n");
                skb_free_frag(liner_buffer);  //page_frag_free
                goto err_clean_previous;
            }

            init_start->linear_buffer = liner_buffer;
            writel_relaxed(dma_addr,                        &init_start->virtual_addr->base);
            writel_relaxed(MAX_RECV_LEN,                    &init_start->virtual_addr->len);
            writel(NODE_F_TRANSFER|NODE_F_BELONG,   &init_start->virtual_addr->flag);
            //init_start->virtual_addr->base = dma_addr;
            //init_start->virtual_addr->len = MAX_RECV_LEN;
            //init_start->virtual_addr->flag = NODE_F_TRANSFER|NODE_F_BELONG;

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
    unsigned int num_dma_bufs,i,empty_count;
    int num_sg;
    unsigned int frag_count = skb_shinfo(skb)->nr_frags + 1;
    struct ring_node_info * fill;
    struct ring_node_info *node_table[MAX_SKB_FRAGS];


    scl = devm_kmalloc_array(&pdev->dev,frag_count, sizeof(struct scatterlist), GFP_KERNEL);
    if (unlikely(!scl))
      	return -ENOMEM;
    sg_init_table(scl, frag_count);
    num_sg = skb_to_sgvec(skb, scl, 0, skb->len);//将SKB内要发送数据的物理地址和长度放入scl，数据本身不拷贝
    if (unlikely(num_sg < 0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }

    //num_dma_bufs <= num_sg   映射要发送数据所在区域，得到DMA地址，此后该区域只允许DMA硬件去访问
    num_dma_bufs = dma_map_sg(&pdev->dev, scl, num_sg, DMA_TO_DEVICE);
    if (unlikely(num_dma_bufs <= 0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }

    //spin_lock(&channel->spinlock_tx_ring_empty);
    //printk("check if it has enough node to fill,num_dma_bufs=%d\n",num_dma_bufs);
    fill = channel->tx_ring_empty;
    for(empty_count=0; empty_count < num_dma_bufs; ++empty_count) {
        if(fill->next == READ_ONCE(channel->tx_ring_full)) {
            pr_err("it dose not have enough node to fill head and frags,need_bufs=%d empty_count%d\n",num_dma_bufs,empty_count);
            err = -EBUSY;
            goto dma_unmap;
        }
        fill = fill->next;
    }

    //将每个scatterlist的DMA地址和长度放入DMA描述符
    fill = channel->tx_ring_empty;
    for_each_sg(scl, crt_scl, num_dma_bufs, i) {
        node_table[i] = fill;//记录本次使用了那些DMA节点
        writel_relaxed(sg_dma_address(crt_scl), &fill->virtual_addr->base);
        writel_relaxed(sg_dma_len(crt_scl), &fill->virtual_addr->len);
        fill = fill -> next;
    }

    //在装记录最后一个scatterlist的ring_node_info上记录相关信息
    node_table[num_dma_bufs-1]->skb = skb;
    node_table[num_dma_bufs-1]->scl = scl;
    node_table[num_dma_bufs-1]->num_sg = num_sg;

    //让DMA描述符属于DMA，启动传输,从后往前,这样DMA硬件检测到第一个属于DMA的描述符时后面的也填充好了。
    writel(NODE_F_TRANSFER|NODE_F_BELONG, &node_table[num_dma_bufs-1]->virtual_addr->flag);
    for (int i=num_dma_bufs-2; i>=0; --i) {
        writel(NODE_F_BELONG, &node_table[i]->virtual_addr->flag);
    }

    //让tx_ring_empty指向后续的属于驱动的描述符，也就是空闲DMA描述符
    WRITE_ONCE(channel->tx_ring_empty ,fill);
    //spin_unlock(&channel->spinlock_tx_ring_empty);

    return 0;

dma_unmap:
    //spin_unlock(&channel->spinlock_tx_ring_empty);
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


    //dump_ring();



    for(channelIndex=0; channelIndex<real_rx_channel_count; ++channelIndex) {
        deinit_start = deinit_end =  channel_info[channelIndex].rx_ring;
        do{
            dma_unmap_single(&pdev->dev,
                             deinit_start->virtual_addr->base,
                             deinit_start->virtual_addr->len,
                             DMA_FROM_DEVICE);
            skb_free_frag(deinit_start->linear_buffer);
            //pr_err("RXdeinit:0x%08x 0x%08x 0x%08x\n",(uint32_t)deinit_start,(uint32_t)deinit_start->virtual_addr,(uint32_t)deinit_start->dma_addr);
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
            }
            //pr_err("TXdeinit1:0x%08x 0x%08x 0x%08x\n",(uint32_t)deinit_start,(uint32_t)deinit_start->virtual_addr,(uint32_t)deinit_start->dma_addr);
            dma_pool_free(pool, deinit_start->virtual_addr, deinit_start->dma_addr);
            deinit_start = deinit_start->next;
        }
        deinit_start = channel_info[channelIndex].tx_ring_empty;
        deinit_end = channel_info[channelIndex].tx_ring_full;
        do {
            //pr_err("TXdeinit2:0x%08x 0x%08x 0x%08x\n",(uint32_t)deinit_start,(uint32_t)deinit_start->virtual_addr,(uint32_t)deinit_start->dma_addr);
            dma_pool_free(pool, deinit_start->virtual_addr, deinit_start->dma_addr);
            deinit_start = deinit_start->next;
        } while(deinit_start != deinit_end);
    }

    dmam_pool_destroy(pool);
    devm_kfree(&pdev->dev,ring_node_info_table);
}