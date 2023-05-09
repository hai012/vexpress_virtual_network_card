#include <linux/init.h>               //__init __exit
#include <linux/module.h>             //module_init/exit
#include <linux/kernel.h>             //printk


#include <linux/dev_printk.h>

#include <asm/io.h>                    //ioremap iounmap
#include <linux/delay.h>               //ssleep
#include <linux/kthread.h>             //kthread_run
#include <linux/interrupt.h>           //request_threaded_irq free_irq
#include <linux/platform_device.h>     //platform
#include <linux/slab.h>//kzmalloc
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>
//#include <linux/types.h> //dma_addr_t

#include "mynet.h"


static int param_poll_weight_tx = 4;
module_param(param_poll_weight_rx, int, 0644);
static int param_poll_weight = 4;
module_param(param_poll_weight, int, 0644);

static int param_real_tx_channel_count = 4;
module_param(param_real_tx_channel_count, int, 0644);
static int param_real_rx_channel_count = 4;
module_param(param_real_rx_channel_count, int, 0644);


//static int param_watchdog_timeo = 5;/* In jiffies */
//module_param(param_watchdog_timeo, int, 0);

static int param_tx_ring_node_count = 100;
module_param(param_tx_ring_node_count, int, 0644);
static int param_rx_ring_node_count = 100;
module_param(param_rx_ring_node_count, int, 0644);



struct mynet_info_t mynet_info;


int	mynet_stop(struct net_device *dev)
{
    ring_deinit();
    unregister_irq(dev);
    hw_deinit(dev);
}
int	mynet_open(struct net_device *dev)
{
    struct mynet_priv_t *priv = netdev_priv(dev);
    struct mynet_info_t *info = priv->info;
    //hw init
    for(int i=0; i < MAX_CHANNEL_NUM; ++i) {
        WRITE_ONCE(info->reg_base_channel[i]->tx_ctl_status, 0);
        WRITE_ONCE(info->reg_base_channel[i]->rx_ctl_status, 0);
        wmb();
        WRITE_ONCE(info->reg_base_channel[i]->tx_ring_base , 0);
        WRITE_ONCE(info->reg_base_channel[i]->tx_irq_flag  , 0);
        WRITE_ONCE(info->reg_base_channel[i]->tx_irq_mask  , 0);
        WRITE_ONCE(info->reg_base_channel[i]->rx_ring_base , 0);
        WRITE_ONCE(info->reg_base_channel[i]->rx_irq_flag  , 0);
        WRITE_ONCE(info->reg_base_channel[i]->rx_irq_mask  , 0);
    }

    //request irq
    if(register_irq(dev)) {
        return -1;
    }

    //ring init
    if(ring_init(dev)){
        unregister_irq(dev);
        return -1
    }

    //hw_start_real_channel
    for(int i=0; i < info->real_tx_channel_count; ++i) {
        WRITE_ONCE(info->reg_base_channel[i]->tx_ring_base , info->tx_ring[i]->dma_addr);//set base
        WRITE_ONCE(info->reg_base_channel[i]->tx_irq_flag  , 0);
        WRITE_ONCE(info->reg_base_channel[i]->tx_irq_mask  , 0xffffffff);//unmask irq
        wmb();
        WRITE_ONCE(info->reg_base_channel[i]->tx_ctl_status, 1);//start
    }
    for(int i=0; i < info->real_rx_channel_count; ++i) {
        WRITE_ONCE(info->reg_base_channel[i]->rx_ring_base , info->rx_ring[i]->dma_addr);
        WRITE_ONCE(info->reg_base_channel[i]->rx_irq_flag  , 0);
        WRITE_ONCE(info->reg_base_channel[i]->rx_irq_mask  , 0xffffffff);
        wmb();
        WRITE_ONCE(info->reg_base_channel[i]->rx_ctl_status, 1);
    }
    return 0;
}

netdev_tx_t	mynet_xmit(struct sk_buff *skb,struct net_device *dev)
{
    if(insert_skb_to_tx_ring(skb,dev)) {
        return NETDEV_TX_BUSY;
    }
    return NETDEV_TX_OK;
}
static const struct net_device_ops mynet_netdev_ops = {
	.ndo_open		= mynet_open,
	.ndo_stop		= mynet_stop,
	//.ndo_set_config		= mynet_config,
	.ndo_start_xmit		= mynet_xmit,
	//.ndo_do_ioctl		= mynet_ioctl,
	//.ndo_get_stats		= mynet_stats,
	//.ndo_change_mtu		= mynet_change_mtu,
	//.ndo_tx_timeout    = mynet_tx_timeout,
};
static int mynet_poll_tx(struct napi_struct *napi_ptr, int budget)
{
    struct mynet_priv_t *priv = netdev_priv(napi_ptr->dev);
    struct mynet_info_t *info = priv->info;
    struct irq_data* data = continerof(napi_ptr, struct irq_data, napi);
    int channelIndex = data->channelIndex;


    WRITE_ONCE(info->reg_base_channel[channelIndex]->tx_irq_mask  , musk);


    //located channel,then pase flag
    READ_ONCE(info->reg_base_channel[i]->tx_ctl_status, 0);
    WRITE_ONCE(info->reg_base_channel[i]->rx_ctl_status, 0);
    wmb();
    WRITE_ONCE(info->reg_base_channel[i]->tx_ring_base , 0);
    WRITE_ONCE(info->reg_base_channel[i]->tx_irq_flag  , 0);
    WRITE_ONCE(info->reg_base_channel[i]->tx_irq_mask  , 0);
    WRITE_ONCE(info->reg_base_channel[i]->rx_ring_base , 0);
    WRITE_ONCE(info->reg_base_channel[i]->rx_irq_flag  , 0);
    WRITE_ONCE(info->reg_base_channel[i]->rx_irq_mask  , 0);
}
static int mynet_poll_rx(struct napi_struct *napi, int budget)
{

}

static int mynet_probe(struct platform_device *pdev)
{
    //parse dtb
    struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        pr_err("%s: fail to get RegCommon virtual base addr\n",__func__);
        return -1;
    }
    mynet_info.reg_base_common = (struct RegCommon *)res->start;
    for(int i=0; i<MAX_CHANNEL_NUM;++i) {
        res = platform_get_resource(pdev, IORESOURCE_MEM, i);
        if (!res) {
            pr_err("%s: fail to get RegChannel virtual base addr, channel=%d\n",__func__,i)
            return -1;
        }
        mynet_info.reg_base_channel[i] = (struct RegChannel *)res->start;

        int irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL);
        if(irq < 0) {
            pr_err("%s: fail to get tx irq, channel=%d,irq=%d\n",__func__,i,j);
            return -1;
        }
        mynet_info.tx_irqs[i] = irq;
        int irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL+1);
        if(irq < 0) {
            pr_err("%s: fail to get rx irq, channel=%d,irq=%d\n",__func__,i,j);
            return -1;
        }
        mynet_info.rx_irqs[i] = irq;
    }

    //param check
    mynet_info.real_tx_channel_count = param_real_tx_channel_count;
    mynet_info.real_rx_channel_count = param_real_rx_channel_count;
    mynet_info.poll_weight_tx = param_poll_weight_tx;
    mynet_info.poll_weight_tx = param_poll_weight_rx;
    mynet_info.tx_ring_node_count = param_tx_ring_node_count;
    mynet_info.rx_ring_node_count = param_rx_ring_node_count;
    if(mynet_info.real_tx_channel_count > MAX_CHANNEL_NUM || mynet_info.real_tx_channel_count <= 0) {
        pr_err("%s: real_tx_channel_count is not valid\n",__func__);
        return -1;
    }
    if(mynet_info.real_rx_channel_count > MAX_CHANNEL_NUM || mynet_info.real_rx_channel_count <= 0) {
        pr_err("%s: real_rx_channel_count is not valid\n",__func__);
        return -1;
    }

   //netdev init
    struct net_device * dev = alloc_netdev_mqs( sizeof(struct mynet_priv_t),
                                                "mynet%d",
                                                NET_NAME_UNKNOWN,
                                                ether_setup,
                                                mynet_info.real_tx_channel_count, 
                                                mynet_info.real_rx_channel_count);
    if(!dev) {
        pr_err("%s: failed to create netdev\n",__func__);
        return -1;
    }
    struct mynet_priv_t *priv = netdev_priv(dev);
    priv->info = &mynet_info;
    mynet_info.netdev = dev;
    for(int i=0; i<mynet_info.real_tx_channel_count; ++i) {
	    netif_napi_add(dev, &priv->irq_data_tx[i].napi, mynet_poll_tx, mynet_info.poll_weight_tx);
    }
    for(int i=0; i<mynet_info.real_rx_channel_count; ++i) {
        netif_napi_add(dev, &priv->irq_data_rx[i].napi, mynet_poll_rx, mynet_info.poll_weight_rx);
    }
    dev->netdev_ops = &mynet_netdev_ops;
	dev->flags           |= IFF_NOARP;
	dev->features        |= NETIF_F_HW_CSUM;
    if(register_netdev(dev)) {
        pr_err("%s: fail to register netdev\n",__func__);
        free_netdev(dev);
        return -1;
    }
    return 0;
}

static int mynet_remove(struct platform_device *dev)
{

    unregister_irq(mynet_info.netdev);
    unregister_netdev(mynet_info.netdev);
    free_netdev(mynet_info.netdev);
    return 0;
}

static const struct of_device_id id_table[] = {
	{.compatible = "ghj,mynet",},
	{},
};
static struct platform_driver mynet_drv = {
	.probe	=	mynet_probe,
	.remove	=	mynet_remove,
	.driver	=	{
		.name	=	"mynet",
		.of_match_table	= id_table,	
	}
};

MODULE_LICENSE ("GPL");

#if 0
module_platform_driver(mynet_drv);
#else
static int __init mynet_drv_init(void)
{
   return platform_driver_register(&mynet_drv);
}
module_init(mynet_drv_init);
static void __exit mynet_drv_exit(void) 
{
  platform_driver_unregister(&mynet_drv);
}
module_exit(mynet_drv_exit);
#endif
