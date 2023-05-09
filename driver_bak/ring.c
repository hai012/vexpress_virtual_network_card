


int ring_init(truct net_device *dev)
{
    struct mynet_priv_t *priv = netdev_priv(dev);
    struct mynet_info_t *info = priv->info;
    struct ring_node_info *ptr;


    size_t node_count = info->real_tx_channel_count * info->tx_ring_node_count +
                        info->real_rx_channel_count * info->rx_ring_node_count;
    priv->ring_node_info_table = devm_kcalloc(dev,node_count,sizeof(struct ring_node_info),GFP_KERNEL);
    if(unlikely(!priv->ring_node_info_table)) {
        pr_err("%s:alloc  ring_node_info_table failed",__func__);
        return -1;
    }
    priv->pool = dma_pool_create("dma_pool",dev, sizeof(struct ring_node_t),4,0);
    if(unlikely(!priv->pool)) {
        pr_err("%s:dma_pool_create failed",__func__);
        kfree(priv->ring_node_info_table);
        return -1;
    }

    //tx
    for(int i=0; i< info->real_tx_channel_count ++i) {
        ptr = priv->ring_node_info_table + i;
        ptr->virtual_addr = dma_pool_zalloc(priv->pool, GFP_KERNEL, &ptr->dma_addr);
        if(unlikely(!ptr->virtual_addr)) {
            goto err_out;
        }
        for(int j=1; j< info->tx_ring_node_count; ++j) {
            (ptr+j)->virtual_addr = dma_pool_zalloc(priv->pool, GFP_KERNEL, &(ptr+j)->dma_addr);
            if(unlikely(!(ptr+j)->virtual_addr)) {
                goto err_out;
            }
            (ptr+j-1)->next = (ptr+j);
            (ptr+j-1)->virtual_addr->next = (ptr+j)->dma_addr;
        }
        (ptr+info->tx_ring_node_count-1)->next = ptr;
        (ptr+info->tx_ring_node_count-1)->virtual_addr->next = ptr->dma_addr;
        priv->tx_ring[i] = ptr;
    }

    //rx
    for(int i=0; i< info->real_rx_channel_count ++i) {
        ptr = priv->ring_node_info_table + info->real_tx_channel_count * info->tx_ring_node_count +i;
        ptr->virtual_addr = dma_pool_zalloc(priv->pool, GFP_KERNEL, &ptr->dma_addr);
        
        if(unlikely(!ptr->virtual_addr)) {
            goto err_out;
        }
        for(int j=1; j< info->rx_ring_node_count; ++j) {
            (ptr+j)->virtual_addr = dma_pool_zalloc(priv->pool, GFP_KERNEL, &(ptr+j)->dma_addr);
            if(unlikely(!(ptr+j)->virtual_addr)) {
                goto err_out;
            }
            (ptr+j-1)->next = (ptr+j);
            (ptr+j-1)->virtual_addr->next = (ptr+j)->dma_addr;
        }
        (ptr+info->rx_ring_node_count-1)->next = ptr;
        (ptr+info->rx_ring_node_count-1)->virtual_addr->next = ptr->dma_addr;
        priv->rx_ring[i] = ptr;
    }
    if(unlikely(alloc_and_map_skb_for_rx_ring(dev))) {
        pr_err("%s:fail to alloc and map skb for rx_ring",__func__);
        goto err_out;
    }
    return 0;
err_out:
    dma_pool_destroy(priv->pool);
    devm_kfree(dev,priv->ring_node_info_table);
    return -1;
}
//void dma_pool_free(struct dma_pool *pool, void *vaddr, dma_addr_t dma)


int alloc_and_map_skb_for_rx_ring(truct net_device *dev)
{
    struct mynet_priv_t *priv = netdev_priv(dev);
    struct mynet_info_t *info = priv->info;

    int channelIndex,nodeIndex;
    for(channelIndex=0; channelIndex< info->real_rx_channel_count; ++channelIndex) {
        for(nodeIndex=0; nodeIndex< info->rx_ring_node_count; ++nodeIndex) {
            (priv->rx_ring[channelIndex]+nodeIndex)->skb = napi_alloc_skb(priv->napi_rx,MAX_RX_SKB_BUFF_LEN);
            if(unlikely(!(priv->rx_ring[channelIndex]+nodeIndex)->skb)) {
                pr_err("napi_alloc_skb  failed");
                goto err_clean_previous;
            }
            skb_reserve((priv->rx_ring[channelIndex]+nodeIndex)->skb,    2);
            dma_addr_t dma_addr = dma_map_single(dev,
                                                 skb->data,
                                                 MAX_RX_SKB_BUFF_LEN-2,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(dev, dma_addr))) {
                pr_err("dma_map_single dma_dst_addr failed");
                kfree_skb((priv->rx_ring[channelIndex]+nodeIndex)->skb);
                goto err_clean_previous;
            }
            (priv->rx_ring[channelIndex]+nodeIndex)->virtual_addr->base = dma_addr;
            (priv->rx_ring[channelIndex]+nodeIndex)->virtual_addr->len = MAX_RX_SKB_BUFF_LEN-2;
            (priv->rx_ring[channelIndex]+nodeIndex)->virtual_addr->flag = 1;
        }
    }
    return 0;

err_clean_previous:
    for(int i=channelIndex;i>=0;--i) {
        for(int j=nodeIndex-1;j>=0;--j) {
            dma_unmap_single(dev,
                             (priv->rx_ring[i]+j)->virtual_addr->base,
                             MAX_RX_SKB_BUFF_LEN-2,
                             DMA_FROM_DEVICE);
            kfree_skb((priv->rx_ring[i]+j)->skb);
        }
    }
    return -1;
}
void ring_deinit(truct net_device *dev)
{
    struct mynet_priv_t *priv = netdev_priv(dev);
    struct mynet_info_t *info = priv->info;

    for(int channelIndex=0; channelIndex< info->real_rx_channel_count; ++channelIndex) {
        for(int nodeIndex=0; nodeIndex< info->rx_ring_node_count; ++nodeIndex) {
            dma_unmap_single(dev,
                             (priv->rx_ring[channelIndex]+nodeIndex)->virtual_addr->base,
                             MAX_RX_SKB_BUFF_LEN-2,
                             DMA_FROM_DEVICE);
            kfree_skb((priv->rx_ring[i]+j)->skb);
        }
    }

    dma_pool_destroy(priv->pool);
    devm_kfree(dev,priv->ring_node_info_table);
}

int inline is_node_belong_to_driver(struct ring_node_info *node)
{
    return !(node->virtual_addr->flag & NODE_F_BELONG);
}

int insert_skb_to_tx_ring(struct sk_buff *skb,struct net_device *dev)
{
    struct mynet_priv_t *priv = netdev_priv(dev);
    struct mynet_info_t *info = priv->info;
    int err;

/* Create and map scatterlist.
* We don't advertise NETIF_F_FRAGLIST, so skb_to_sgvec() will not have
* to go beyond nr_frags+1.
* Note: We don't support chained scatterlists*/

    struct scatterlist *scl, *crt_scl;
    int num_dma_bufs;
    int num_sg;
    scl = devm_kmalloc_array(dev,nr_frags + 1, sizeof(struct scatterlist), GFP_KERNEL);
    if (unlikely(!scl))
      	return -ENOMEM;
    sg_init_table(scl, nr_frags + 1);
    num_sg = skb_to_sgvec(skb, scl, 0, skb->len);
    if (unlikely(num_sg < 0)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }
    num_dma_bufs = dma_map_sg(dev, scl, num_sg, DMA_TO_DEVICE);
    if (unlikely(!num_dma_bufs)) {
    	err = -ENOMEM;
    	goto dma_map_sg_failed;
    }

    //check if it has enough node to fill
    int nodes_need = num_dma_bufs;
    for(struct ring_node_info *node=priv->tx_ring[skb->queue_mapping];
        is_node_belong_to_driver();
        node=node->next) {
            if(nodes_need--)
                break;
    }
    if(nodes_need) {
        //pr_err("it dose not have enough node to fill head and frags,wait for send previous node\n");
        goto dma_unmap;
        return -1;
    }

    //start fill
    struct ring_node_t *node_table[MAX_SKB_FRAGS];
    for_each_sg(scl, crt_scl, num_dma_bufs, i) {
        node_table[i] = priv->tx_ring[skb->queue_mapping];
        priv->tx_ring[skb->queue_mapping]->virtual_addr->base = sg_dma_address(crt_scl);
        priv->tx_ring[skb->queue_mapping]->virtual_addr->len = sg_dma_len(crt_scl);
        priv->tx_ring[skb->queue_mapping]->skb = skb;
        priv->tx_ring[skb->queue_mapping] =  priv->tx_ring[skb->queue_mapping] -> next;
    }
    for (int i=num_dma_bufs; i>0; ++i) {
        node_table[i]->virtual_addr->flag = 1;
    }
    wmb();
    node_table[0]->virtual_addr->flag = 1;
    return 0;

dma_unmap:
	dma_unmap_sg(dev, scl, num_sg, DMA_FROM_DEVICE);
dma_map_sg_failed:
	devm_kfree(scl);
	return err;
}

int check_ring_nodes_flag(struct ring_node_info *list,int n,int belong)
{


}