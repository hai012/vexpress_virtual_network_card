






int ring_init(void)
{
    size_t node_count = (1+real_tx_channel_count) * tx_ring_node_count +
                        (1+real_rx_channel_count) * rx_ring_node_count;
    ring_node_info_table = devm_kcalloc(netdev,node_count,sizeof(struct ring_node_info),GFP_KERNEL);
    if(unlikely(!priv->ring_node_info_table)) {
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
    for(int i=0; i<real_tx_channel_count ++i) {
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
        channel_info[i].rx_ring_empty = ptr;
        channel_info[i].rx_ring_full = ptr;
    }

    if(unlikely(alloc_and_map_skb_for_rx_ring())) {
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



int alloc_and_map_skb_for_rx_ring(void)
{
    int channelIndex,nodeIndex;
    
    for(channelIndex=0; channelIndex<real_rx_channel_count; ++channelIndex) {

        struct napi_struct *napi = channel_info[channelIndex].napi_rx;
        while(channel_info[channelIndex].rx_ring_empty->next != channel_info[channelIndex].rx_ring_full)
        {
            //struct skb_buff *skb = netdev_alloc_frag(napi,  MAX_RX_SKB_BUFF_LEN);
            if(unlikely(!skb )) {
                pr_err("napi_alloc_skb failed");
                goto err_clean_previous;
            }
            skb_reserve(skb, 2);
            skb_record_rx_queue(skb,channelIndex);
            dma_addr_t dma_addr = dma_map_single(netdev,
                                                 skb->data,
                                                 MAX_RX_SKB_BUFF_LEN-2,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(netdev, dma_addr))) {
                pr_err("dma_map_single dma_dst_addr failed");
                kfree_skb(skb);
                goto err_clean_previous;
            }
            channel_info[channelIndex].rx_ring_empty->skb = skb;
            WRITE_ONCE(channel_info[channelIndex].rx_ring_empty->virtual_addr->base,dma_addr);
            WRITE_ONCE(channel_info[channelIndex].rx_ring_empty->virtual_addr->len,MAX_RX_SKB_BUFF_LEN-2);
            WRITE_ONCE(channel_info[channelIndex].rx_ring_empty->virtual_addr->flag,NODE_F_TRANSFER|NODE_F_BELONG);
            channel_info[channelIndex].rx_ring_empty = channel_info[channelIndex].rx_ring_empty->next;
        }
    }
    return 0;

err_clean_previous:
    for(channelIndex=0; channelIndex< real_rx_channel_count; ++channelIndex) {
        while(channel_info[channelIndex].rx_ring_full != channel_info[channelIndex].rx_ring_empty)
        {
            dma_unmap_single(netdev,
                             channel_info[channelIndex].rx_ring_full->virtual_addr->base,
                             MAX_RX_SKB_BUFF_LEN-2,
                             DMA_FROM_DEVICE);
            kfree_skb(channel_info[channelIndex].rx_ring_full->skb);
            channel_info[channelIndex].rx_ring_full = channel_info[channelIndex].rx_ring_full->next;
        }
    }
    return -1;
}

int alloc_map_insert_skb_to_rx_ring(struct sk_buff *skb)
{



}

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
    num_dma_bufs = dma_map_sg(netdev, scl, num_sg, DMA_TO_DEVICE);
    if (unlikely(num_dma_bufs<=0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }


    //check if it has enough node to fill
    spin_lock(&channel->lock_tx);
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
        node_table[num_dma_bufs-1]->skb = skb;
        node_table[num_dma_bufs-1]->scl = slc;
        writel(node_table[num_dma_bufs-1]->virtual_addr->flag, NODE_F_TRANSFER|NODE_F_BELONG);
    } else {
        node_table[num_dma_bufs-1]->skb = skb;
        node_table[num_dma_bufs-1]->scl = slc;
        writel_relaxed(node_table[num_dma_bufs-1]->virtual_addr->flag, NODE_F_TRANSFER|NODE_F_BELONG);
        for (int i=num_dma_bufs-2; i>0; ++i) {
            writel_relaxed(node_table[i]->virtual_addr->flag, NODE_F_BELONG);
        }
        writel(node_table[0]->virtual_addr->flag, NODE_F_BELONG);
    }

    channel->tx_ring_empty = fill;
    spin_unlock(&channel->lock_tx);
    return 0;

dma_unmap:
    spin_unlock(&channel->lock_tx);
	dma_unmap_sg(netdev, scl, num_sg, DMA_TO_DEVICE);
dma_map_sg_failed:
	devm_kfree(netdev,scl);
	return err;
}

