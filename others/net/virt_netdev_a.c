#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>


#include <linux/cdev.h>


static int poll_weight = 2;
module_param(poll_weight, int, 0);


static int tx_timeout_jiffy = 5;
module_param(tx_timeout_jiffy, int, 0);

static unsigned int tx_queue = 1;
module_param(tx_queue, uint, 0);

static unsigned int rx_queue = 1;
module_param(rx_queue, uint, 0);

static unsigned int tx_buffer_size = 1;
module_param(tx_buffer_size, uint, 0);

static unsigned int rx_buffer_size = 1;
module_param(rx_buffer_size, uint, 0);


static unsigned int tx_ring_size = 20;
module_param(rx_buffer_size, uint, 0);

static unsigned int rx_ring_size = 20;
module_param(rx_buffer_size, uint, 0);


struct net_device virt_netdev;


struct queue_data {
    struct ring_node_t ring;
    struct sk_buff *rx_skb;
}


struct virt_netdev_priv {
    struct net_device  *netdev;
    struct napi_struct napi;
    struct net_device_stats stats;

    struct queue_data_t * tx_queue_data;
    struct queue_data_t * rx_queue_data;
}

static void rx_irq(void)
{
    //struct dma_tx_state	state;
    //dmaengine_tx_status(chan,cookie, &state);
    dma_unmap_single(chan->device->dev,dma_src_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);
    dma_unmap_single(chan->device->dev,dma_dst_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);


    complete(&transfer_ok);
    /* 通过rx_data和tx_data虚拟地址处理缓冲区*/

    napi_schedule
    return;
}
static void tx_irq(void)
{

    return;
}

static int virt_netdev_open(struct net_device *dev)
{
    struct virt_netdev_priv* priv = (struct virt_netdev_priv*)netdev_priv(dev);

    priv->ring(tx_ring_size*sizeof(struct ring_node_t));

	priv->rxskb = dev_alloc_skb(tx_buffer_size + 2);
    dma_src_addr = dma_map_single(chan->device->dev, skb->data,BUFFER_SIZE, DMA_MEM_TO_MEM);
    if(!dma_src_addr) {
        pr_err("dma_map_single dma_src_addr failed");
        return;
    }

}

static netdev_tx_t virt_netdev_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
//////////////////////dma_map_single///////////////
    dma_src_addr = dma_map_single(chan->device->dev, skb->data,BUFFER_SIZE, DMA_MEM_TO_MEM);
    if(!dma_src_addr) {
        pr_err("dma_map_single dma_src_addr failed");
        return;
    }

}


static int virt_netdev_stop(struct net_device *dev)
{

}

static struct net_device_stats* virt_netdev_get_stats(struct net_device *dev)
{

}


static const struct net_device_ops virt_netdev_ops[] = {
    {
	.ndo_open		= virt_netdev_open,
	.ndo_stop		= virt_netdev_release,
//	.ndo_set_config		= virt_netdev_config,
	.ndo_start_xmit		= virt_netdev_tx,
//	.ndo_do_ioctl		= virt_netdev_ioctl,
	.ndo_get_stats		= virt_netdev_stats,
//	.ndo_change_mtu		= virt_netdev_change_mtu,
	.ndo_tx_timeout     = virt_netdev_tx_timeout,
    }
};


static void setup_virt_netdev(struct net_device *dev)
{
    struct virt_netdev_priv *priv = netdev_priv(dev);
	memset(priv, 0, sizeof(struct virt_netdev_priv));
	priv->netdev = dev;
		

	/* keep the default flags, just add NOARP */
    eth_setup(dev);
	dev->flags           |= IFF_NOARP;
	dev->features        |= NETIF_F_HW_CSUM;
    dev->watchdog_timeo = tx_timeout_jiffy;
	dev->netdev_ops = &virt_netdev_ops;


    netif_napi_add(dev, &priv->napi, virt_netdev_poll, poll_weight);
}

static int __init virt_netdev_init(void)
{
    virt_netdev = alloc_netdev_mqs(sizeof(virt_netdev_priv), "virt_net_a", NET_NAME_UNKNOWN, setup_virt_netdev, tx_queue, rx_queue);
    if(!virt_netdev) {
        pr_err("alloc_netdev_mqs virt_netdev failed");

    }
    if(register_netdev(virt_netdev)) {
        pr_err("register_netdev virt_netdev failed");
    }
}




static int __exit virtual_netdev_exit(void) 
{

}



module_init(virt_netdev_init);
module_exit(virt_netdev_exit);
MODULE_LICENSE ("GPL");