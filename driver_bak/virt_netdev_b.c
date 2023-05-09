#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>


#include <linux/cdev.h>


static int poll_weight_0 = 2;
static int poll_weight_1 = 2;
module_param(poll_weight_0, int, 0);
module_param(poll_weight_1, int, 0);


static int tx_timeout_jiffy_0 = 5;
static int tx_timeout_jiffy_1 = 5;
module_param(tx_timeout_jiffy_0, int, 0);
module_param(tx_timeout_jiffy_1, int, 0);

static unsigned int tx_queue_0 = 1;
static unsigned int tx_queue_1 = 1;
module_param(tx_queue_0, uint, 0);
module_param(tx_queue_1, uint, 0);

static unsigned int rx_queue_0 = 1;
static unsigned int rx_queue_1 = 1;
module_param(rx_queue_0, uint, 0);
module_param(rx_queue_1, uint, 0);

static unsigned int tx_buffer_size_0 = 1;
static unsigned int tx_buffer_size_1 = 1;
module_param(tx_buffer_size_0, uint, 0);
module_param(tx_buffer_size_1, uint, 0);

static unsigned int rx_buffer_size_0 = 1;
static unsigned int rx_buffer_size_1 = 1;
module_param(rx_buffer_size_0, uint, 0);
module_param(rx_buffer_size_1, uint, 0);



struct adaptor {
    struct net_device virt_netdev;
    
}
struct net_device virt_netdev[2];





struct virt_netdev_priv {
    struct net_device  *netdev;
    struct napi_struct napi;
    struct net_device_stats stats;



    struct dma_chan *chan;
    struct completion transfer_ok_completion;

    struct sk_buff *rx_skb;
    dma_addr_t dma_dst_addr;

    struct sk_buff *tx_skb;
    dma_addr_t dma_src_addr;

    dma_cookie_t cookie;
}

static void dma_callback(void *ptr)
{
    //struct dma_tx_state	state;
    //dmaengine_tx_status(chan,cookie, &state);
    dma_unmap_single(chan->device->dev,dma_src_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);
    dma_unmap_single(chan->device->dev,dma_dst_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);

    if(strncmp(rx_data,tx_data,sizeof("test"))==0)
        pr_err("test equal");
    else
        pr_err("dma test unequal");
    pr_err("dma_callback end");
    complete(&transfer_ok);
    /* 通过rx_data和tx_data虚拟地址处理缓冲区*/





    napi_schedule
    return;
}

static int virt_netdev_open(struct net_device *dev)
{
    struct virt_netdev_priv* priv = (struct virt_netdev_priv*)netdev_priv(dev);
    dma_cap_mask_t dma_cap_mask;
    dma_cap_zero(dma_cap_mask);
    dma_cap_set(DMA_MEMCPY, dma_cap_mask);
    priv->chan = dma_request_channel(dma_cap_mask,NULL, NULL);
    if (!priv->chan) {
        pr_err("dma_request_channel failed for %s",priv->netdev->name);
        return;
    }

    struct dma_slave_config dma_cfg = {0};
    dma_cfg.direction = DMA_MEM_TO_MEM;
    dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_64_BYTES;
    dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_64_BYTES;
    dma_cfg.dst_maxburst = 4096;
    dma_cfg.src_maxburst = 4096;
    if(dmaengine_slave_config(chan, &dma_cfg)) {
        pr_err("dmaengine_slave_config failed");
        return;
    }


	priv->rxskb = dev_alloc_skb(tx_buffer_size_0 + 2);
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


/////////////////////dmaengine_prep_dma_memcpy////////////////////
    tx_descriptor = dmaengine_prep_dma_memcpy(chan,dma_dst_addr,dma_src_addr, BUFFER_SIZE, 0);
    if (!tx_descriptor) {
        pr_err("Failed to prepare DMA transfer\n");
        return;
        /* dma_unmap_* the buffer */
    }
/////////////////fill callback/////////////////////////////////
    init_completion(&transfer_ok);
    tx_descriptor->callback = dma_callback;



//////////////////dmaengine_submit///////////////////////////////////
    cookie = dmaengine_submit(tx_descriptor);
    if (dma_submit_error(cookie)) {
        pr_err("%s: Failed to start DMA transfer\n", __FUNCTION__);
        return;
    }

/////////////////dma_async_issue_pending/////////////////
    dma_async_issue_pending(chan);
    //pr_err("start wait_for_completion");
    wait_for_completion(&transfer_ok);
    //pr_err("end wait_for_completion");
    //pr_err("end wait_for_completion");
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


static void setup_virt_netdev_0(struct net_device *dev)
{
    struct virt_netdev_priv *priv = netdev_priv(dev);
	memset(priv, 0, sizeof(struct virt_netdev_priv));
	priv->netdev = dev;
		

	/* keep the default flags, just add NOARP */
    eth_setup(dev);
	dev->flags           |= IFF_NOARP;
	dev->features        |= NETIF_F_HW_CSUM;
    dev->watchdog_timeo = tx_timeout_jiffy_0;
	dev->netdev_ops = &virt_netdev_ops;


    netif_napi_add(dev, &priv->napi, virt_netdev_poll, poll_weight_0);
}
static void setup_virt_netdev_1(struct net_device *dev)
{
    setup_virt_netdev_0(dev);
}



static int __init virt_netdev_init(void)
{
    virt_netdev[0] = alloc_netdev_mqs(sizeof(virt_netdev_priv), "virt_net_0", NET_NAME_UNKNOWN, setup_virt_netdev_0, tx_queue_0, rx_queue_0);
    if(!virt_netdev[0]) {
        pr_err("alloc_netdev_mqs virt_netdev[0] failed");

    }
    virt_netdev[1] = alloc_netdev_mqs(sizeof(virt_netdev_priv), "virt_net_1", NET_NAME_UNKNOWN, setup_virt_netdev_1, tx_queue_1, rx_queue_1);
    if(!virt_netdev[1]) {
        pr_err("alloc_netdev_mqs virt_netdev[1] failed");

    }
    if(register_netdev(virt_netdev[0])) {
        pr_err("register_netdev virt_netdev[0] failed");
    }
    if(register_netdev(virt_netdev[1])) {
        pr_err("register_netdev virt_netdev[0] failed");
    }
}




static int __exit virtual_netdev_exit(void) 
{

}



module_init(virt_netdev_init);
module_exit(virt_netdev_exit);
MODULE_LICENSE ("GPL");