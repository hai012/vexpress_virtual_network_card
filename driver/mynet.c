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
    u16 channelIndex = skb_get_queue_mapping(skb);
    if(insert_skb_to_tx_ring(&channel_info[channelIndex],dev)) {
        netif_tx_stop_queue(netdev_get_tx_queue(dev, channelIndex));
        return NETDEV_TX_BUSY;
    }
    uint32_t flag = readl_relaxed(&channel->reg_base_channel->tx_irq_flag);
    if(flag & IRQF_TX_EMPTY) {
        flag &= ~IRQF_TX_EMPTY;//clear TX_EMPTY flag
        writel_relaxed(flag, &channel->reg_base_channel->tx_irq_flag);
        wmb();
        writel_relaxed(1,&channel->reg_base_channel->tx_ctl_status);//restart tx
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

static int mynet_poll_tx(struct napi_struct *napi, int budget)
{
    if(unlikely(budget<=0)){
        goto  poll_tx_exit;
    }

    struct channel_data * channel = continerof(napi, struct channel_data, napi_tx);
    int count=0;
    int stop_reason_error=1;

    //spin_lock(&channel->spinlock_tx_ring_full);
    while(budget > count) {
        if(is_node_belong_to_hw(channel->tx_ring_full)) {
            //now ,we don't have skb to release
            //there is data in tx ting,wait hw send data
            break;
        }
        if(channel->tx_ring_full==channel->tx_ring_empty) {
            //now ,we don't have skb to release
            //there is no data in tx ting
            break;
        }
        if(is_node_transfer(channel->tx_ring_full)) {
            //now , we find the last frag
            dma_unmap_sg(netdev, channel->tx_ring_full->scl, channel->tx_ring_full->num_sg, DMA_FROM_DEVICE);
            devm_kfree(netdev,channel->tx_ring_full->scl);
            kfree_skb(channel->tx_ring_full->skb);
            ++count;
            stop_reason_error=0;
        } else {
            stop_reason_error=1;
        }
        channel->tx_ring_full = channel->tx_ring_full->next;
    }
    spin_unlock(&channel->spinlock_tx_ring_full);

    BUG_ON(stop_reason_error);//unknown error,tx ring data was damaged

    netif_tx_wake_queue(netdev,netdev_get_tx_queue(channel->queue_index));
poll_tx_exit:
    //unmask IRQF_TX_SEND
    uini32_t mask = readl_relaxed(&channel->reg_base_channel->tx_irq_mask);
    mask |= IRQF_TX_SEND;
    writel_relaxed(mask, &channel->reg_base_channel->tx_irq_mask);
    return count;
}
static int mynet_poll_rx(struct napi_struct *napi, int budget)
{
    struct channel_data * channel = continerof(napi, struct channel_data, napi_rx);
    int count=0;
    while(budget>count)
    {
        //if(is_node_transfer(channel->tx_ring_full)) {
            if(is_node_belong_to_hw(channel->rx_ring)) {

            }
            //replace
            char * linear_buffer_replace = napi_alloc_frag(MAX_RX_SKB_LINEAR_BUFF_LEN);
            if(unlikely(!linear_buffer_replace)) {
                pr_err("napi_alloc_frag failed");
                return count;
            }
            dma_addr_t dma_addr = dma_map_single(netdev,
                                                 linear_buffer_replace + ETH_HEADER_OFFSET_IN_LINEAR_BUFF,
                                                 MAX_RECV_LEN,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(netdev, dma_addr))) {
                pr_err("dma_map_single  failed");
                skb_free_frag(linear_buffer_replace);  //page_frag_free
                return count;
            }
            dma_unmap_single(netdev,
                            channel->rx_ring->virtual_addr->base,
                            channel->rx_ring->virtual_addr->len,
                            DMA_FROM_DEVICE);
            char * linear_buffer_recv = channel->rx_ring->linear_buffer;//

            channel->rx_ring->liner_buffer = linear_buffer_replace;
            writel_relaxed(dma_addr,                        &channel->rx_ring->virtual_addr->base);
            writel_relaxed(MAX_RECV_LEN,                    &channel->rx_ring->virtual_addr->len);
            writel_relaxed(NODE_F_TRANSFER|NODE_F_BELONG,   &channel->rx_ring->virtual_addr->flag);
            channel->rx_ring = channel->rx_ring->next;

            //recv
            struct skbuff * skb = build_skb(linear_buffer_recv, MAX_RX_SKB_LINEAR_BUFF_LEN);
            if (unlikely(!skb)) {
                skb_free_frag(linear_buffer_recv);
                netdev->stats.rx_dropped++;
                return count;
            }
            skb_reserve(skb, ETH_HEADER_OFFSET_IN_LINEAR_BUFF);
            skb_record_rx_queue(skb,channel->queue_index);
            napi_gro_receive(skb);
            ++count;
        //}
    }

    //unmask IRQF_TX_SEND
    uini32_t mask = readl_relaxed(&channel->reg_base_channel->tx_irq_mask);
    mask |= IRQF_TX_SEND;
    writel_relaxed(mask,  &channel->reg_base_channel->tx_irq_mask);
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

        spin_lock_init(&channel_info[i].spinlock_tx_ring_empty);
        spin_lock_init(&channel_info[i].spinlock_tx_ring_full);
        channel_info[i].queue_index = i;
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
	    netif_napi_add(netdev, &channel_info[i].napi_tx, mynet_poll_tx, poll_weight_tx);
    }
    for(int i=0; i<real_rx_channel_count; ++i) {
        netif_napi_add(netdev, &channel_info[i].napi_rx, mynet_poll_rx, poll_weight_rx);
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
