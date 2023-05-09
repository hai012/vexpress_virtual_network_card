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



//config data
int real_tx_channel_count;
int real_rx_channel_count;
int poll_weight_tx;
int poll_weight_rx;
int tx_ring_node_count;
int rx_ring_node_count;
//common data
struct RegCommon * reg_base_common;
struct dma_pool * pool;
struct ring_node_info *ring_node_info_table;
struct net_device * netdev;
//channel data
struct channel_data channel_info[MAX_CHANNEL_NUM];



int	mynet_stop(struct net_device *dev)
{
    ring_deinit();
    unregister_irq(dev);
    hw_deinit(dev);
}
int	mynet_open(struct net_device *dev)
{
    hw_init();

    if(register_irq(dev)) {
        return -1;
    }

    //ring init
    if(ring_init(dev)){
        unregister_irq(dev);
        return -1
    }

    hw_start_real_channel();
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

int inline is_node_belong_to_driver(struct ring_node_info *node)
{
    return !(READ_ONCE(node->virtual_addr->flag) & NODE_F_BELONG);
}
int inline is_node_transfer(struct ring_node_info *node)
{
    return READ_ONCE(node->virtual_addr->flag) & NODE_F_TRANSFER;
}
static int mynet_poll_tx(struct napi_struct *napi, int budget)
{
    struct channel_data * channel = continerof(napi, struct channel_data, napi_tx);
    int count=0;
    while(is_node_belong_to_driver(channel->tx_ring_full)&&
          channel->tx_ring_full!=channel->tx_ring_empty)
    {
        if(is_node_transfer(channel->tx_ring_full)) {
            dma_unmap_sg(channel->tx_ring_full->scl);
            devm_kfree(netdev,channel->tx_ring_full->scl);
            free_skb(channel->tx_ring_full->skb);
            ++count;
            if(count==budget)
                break;
        }
        channel->tx_ring_full = channel->tx_ring_full->next;
    }

    //unmask IRQF_TX_SEND
    uini32_t mask = READ_ONCE(channel->reg_base_channel->tx_irq_mask);
    mask |= IRQF_TX_SEND;
    WRITE_ONCE(channel->reg_base_channel->tx_irq_mask, mask);
    return count;
}
static int mynet_poll_rx(struct napi_struct *napi, int budget)
{
    struct channel_data * channel = continerof(napi, struct channel_data, napi_rx);
    int count=0;
    while(is_node_belong_to_driver(channel->rx_ring_full)&&
          channel->rx_ring_full!=channel->rx_ring_empty)
    {
        //if(is_node_transfer(channel->tx_ring_full)) {
            dma_unmap_single(netdev,
                            channel->tx_ring_full->virtual_addr->base,
                            channel->tx_ring_full->virtual_addr->len,
                            DMA_FROM_DEVICE);
            struct skb_buff *skb_recv = channel->skb;

            //replace
            struct skb_buff *skb_replace = napi_alloc_skb(napi,  MAX_RX_SKB_BUFF_LEN);
            if(unlikely(!skb_replace)) {
                pr_err("napi_alloc_skb failed");
                goto err_clean_previous;
            }
            skb_reserve(skb_replace, 2);
            skb_record_rx_queue(skb_replace,skb_get_rx_queue(skb_recv));
            dma_addr_t dma_addr = dma_map_single(netdev,
                                                 skb_replace->data,
                                                 MAX_RX_SKB_BUFF_LEN-2,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(netdev, dma_addr))) {
                pr_err("dma_map_single skb_replace failed");
                kfree_skb(skb_replace);
                goto err_clean_previous;
            }
            channel->rx_ring_full->skb = skb_replace;
            WRITE_ONCE(channel->rx_ring_full->virtual_addr->base,dma_addr);
            WRITE_ONCE(channel->rx_ring_full->virtual_addr->len,MAX_RX_SKB_BUFF_LEN-2);
            wmb();
            channel->rx_ring_full = channel->rx_ring_full->next;
            WRITE_ONCE(channel->rx_ring_full->virtual_addr->flag,NODE_F_TRANSFER|NODE_F_BELONG);
            


            //recv
            napi_gro_receive(skb_recv);
            ++count;
            if(count==budget)
                break;
        //}
    }

    //unmask IRQF_TX_SEND
    uini32_t mask = READ_ONCE(channel->reg_base_channel->tx_irq_mask);
    mask |= IRQF_TX_SEND;
    WRITE_ONCE(channel->reg_base_channel->tx_irq_mask, mask);
    return count;
}

static int mynet_probe(struct platform_device *pdev)
{
    //parse dtb
    struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        pr_err("%s: fail to get RegCommon virtual base addr\n",__func__);
        return -1;
    }
    reg_base_common = (struct RegCommon *)res->start;
    for(int i=0; i<MAX_CHANNEL_NUM;++i) {
        res = platform_get_resource(pdev, IORESOURCE_MEM, i);
        if (!res) {
            pr_err("%s: fail to get RegChannel virtual base addr, channel=%d\n",__func__,i)
            return -1;
        }
        channel_info[i].reg_base_channel = (struct RegChannel *)res->start;

        int irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL);
        if(irq < 0) {
            pr_err("%s: fail to get tx irq, channel=%d,irq=%d\n",__func__,i,j);
            return -1;
        }
        channel_info[i].tx_irqs = irq;
        int irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL+1);
        if(irq < 0) {
            pr_err("%s: fail to get rx irq, channel=%d,irq=%d\n",__func__,i,j);
            return -1;
        }
        channel_info[i].rx_irqs = irq;
    }

    //param check
    real_tx_channel_count = param_real_tx_channel_count;
    real_rx_channel_count = param_real_rx_channel_count;
    poll_weight_tx = param_poll_weight_tx;
    poll_weight_tx = param_poll_weight_rx;
    tx_ring_node_count = param_tx_ring_node_count+1;
    rx_ring_node_count = param_rx_ring_node_count+1;
    if(real_tx_channel_count > MAX_CHANNEL_NUM || real_tx_channel_count <= 0) {
        pr_err("%s: real_tx_channel_count is not valid\n",__func__);
        return -1;
    }
    if(real_rx_channel_count > MAX_CHANNEL_NUM || real_rx_channel_count <= 0) {
        pr_err("%s: real_rx_channel_count is not valid\n",__func__);
        return -1;
    }

    //netdev init
    netdev = alloc_netdev_mqs( 0,
                               "mynet%d",
                               NET_NAME_UNKNOWN,
                               ether_setup,
                               mynet_info.real_tx_channel_count, 
                               mynet_info.real_rx_channel_count);
    if(!netdev) {
        pr_err("%s: failed to create netdev\n",__func__);
        return -1;
    }
    for(int i=0; i<real_tx_channel_count; ++i) {
	    netif_napi_add(dev, &channel_info[i].napi_tx, mynet_poll_tx, poll_weight_tx);
    }
    for(int i=0; i<real_rx_channel_count; ++i) {
        netif_napi_add(dev, &channel_info[i].napi_rx, mynet_poll_rx, poll_weight_rx);
    }
    netdev->netdev_ops = &mynet_netdev_ops;
	netdev->flags           |= IFF_NOARP;
	netdev->features        |= NETIF_F_HW_CSUM;
    if(register_netdev(netdev)) {
        pr_err("%s: fail to register netdev\n",__func__);
        free_netdev(netdev);
        return -1;
    }
    return 0;
}

static int mynet_remove(struct platform_device *dev)
{
    unregister_irq(netdev);
    unregister_netdev(netdev);
    free_netdev(netdev);
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
