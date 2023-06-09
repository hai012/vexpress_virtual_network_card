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
#include <linux/scatterlist.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/spinlock_types.h>
#include <linux/mod_devicetable.h>
#include <linux/etherdevice.h>
#include "mynet.h"




adrv9010_DmaMemRead(device, ADRV9010_ADDR_DPD_TX_CAPTURE_DATA, captureBuffer, extDpdCaptureData->txCaptureData.extDpdCaptureSampleArrSize*4, 0);
write_to_file(call_times,
┊   ┊   ┊   ┊ "TX_CAPTURE",
┊   ┊   ┊   ┊captureBuffer,
┊   ┊   ┊   extDpdCaptureData->txCaptureData.extDpdCaptureSampleArrSize*4);
adrv9010_ExtDpdCaptureDataParse(device,captureBuffer, &extDpdCaptureData->txCaptureData.extDpdCaptureDataI[0], &extDpdCaptureData->txCaptureData.extDpdCaptureDtaQ[0], extDpdCaptureData->txCaptureData.extDpdCaptureSampleArrSize);




adrv9010_DmaMemRead(device, ADRV9010_ADDR_DPD_ALT_TX_CAPTURE_DATA, captureBuffer, extDpdCaptureData->txAlternateCaptureData.extDpdCaptureSampleArrSize*4, 0);
write_to_file(call_times,
┊   ┊   ┊   ┊ "ALT_TX_CAPTURE",
┊   ┊   ┊   ┊ captureBuffer,
┊   ┊   ┊   ┊ extDpdCaptureData->txAlternateCaptureData.extDpdCaptureSampleArrSize*4);
adrv9010_ExtDpdCaptureDataParse(device, captureBuffer, &extDpdCaptureData->txAlternateCaptureData.extDpdCaptureDataI[0], &extDpdCaptureData->txAlternateCaptureData.extDpdCaptureDataQ[0], extDpdCaptureData->txAlternateCaptureData.extDpdCaptureSampleArrSize);


adrv9010_DmaMemRead(device, ADRV9010_ADDR_DPD_ORX_CAPTURE_DATA, captureBuffer, extDpdCaptureData->orxCaptureData.extDpdCaptureSampleArrSize*4, 0);
write_to_file(call_times,
┊   ┊   ┊   ┊ "ORX_CAPTURE",
┊   ┊   ┊   ┊ captureBuffer,
┊   ┊   ┊   ┊ extDpdCaptureData->orxCaptureData.extDpdCaptureSampleArrSize);
adrv9010_ExtDpdCaptureDataParse(device, captureBuffer, &extDpdCaptureData->orxCaptureData.extDpdCaptureDataI[0], &extDpdCaptureData->orxCaptureData.extDpdCaptureDataQ[0], extDpdCaptureData->orxCaptureData.extDpdCaptureSampleArrSize);


static int param_real_tx_channel_count = 4;
module_param(param_real_tx_channel_count, int, 0644);
static int param_real_rx_channel_count = 4;
module_param(param_real_rx_channel_count, int, 0644);


//static int param_watchdog_timeo = 5;/* In jiffies */
//module_param(param_watchdog_timeo, int, 0);

static int param_tx_ring_node_count = 64;
module_param(param_tx_ring_node_count, int, 0644);
static int param_rx_ring_node_count = 64;
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
struct net_device * netdev;
struct platform_device *pdev;
//channel data
struct channel_data channel_info[MAX_CHANNEL_NUM];




int	mynet_open(struct net_device *netdev)
{
    //hw_init
    for(int i=0; i < MAX_CHANNEL_NUM; ++i) {
        writel_relaxed(0, &channel_info[i].reg_base_channel->tx_ctl_status);
        writel_relaxed(0, &channel_info[i].reg_base_channel->rx_ctl_status);
        wmb();
        writel_relaxed(0, &channel_info[i].reg_base_channel->tx_ring_base );
        writel_relaxed(0, &channel_info[i].reg_base_channel->tx_irq_flag  );
        writel_relaxed(0, &channel_info[i].reg_base_channel->tx_irq_mask  );
        writel_relaxed(0, &channel_info[i].reg_base_channel->rx_ring_base );
        writel_relaxed(0, &channel_info[i].reg_base_channel->rx_irq_flag  );
        writel_relaxed(0, &channel_info[i].reg_base_channel->rx_irq_mask  );
    }

    if(register_irq()) {
        return -1;
    }


    if(ring_init()){
        return -1;
    }

    //hw_start_real_channel
    for(int i=0; i < real_tx_channel_count; ++i) {
        writel_relaxed(channel_info[i].tx_ring_full->dma_addr,    &channel_info[i].reg_base_channel->tx_ring_base);//set base
        writel_relaxed(0,                                         &channel_info[i].reg_base_channel->tx_irq_flag);
        writel_relaxed(IRQF_TX_SEND,                               &channel_info[i].reg_base_channel->tx_irq_mask);//unmask IRQF_TX_SEND
        writel(1,                                                 &channel_info[i].reg_base_channel->tx_ctl_status);//start
    }
    for(int i=0; i < real_rx_channel_count; ++i) {
        writel_relaxed(channel_info[i].rx_ring->dma_addr,    &channel_info[i].reg_base_channel->rx_ring_base);//set base
        writel_relaxed(0,                                         &channel_info[i].reg_base_channel->rx_irq_flag);
        writel_relaxed(IRQF_RX_RECV,                                &channel_info[i].reg_base_channel->rx_irq_mask);//unmask IRQF_RX_RECV
        writel(1,                                                 &channel_info[i].reg_base_channel->rx_ctl_status);//start
    }

    netif_tx_start_all_queues(netdev);
    return 0;
}
int	mynet_stop(struct net_device *netdev)
{
    netif_tx_stop_all_queues(netdev);
    ring_deinit();
    unregister_irq();
    //hw_deinit(netdev);
    return 0;
}
netdev_tx_t	mynet_xmit(struct sk_buff *skb,struct net_device *netdev)
{
    u16 channelIndex = skb_get_queue_mapping(skb);
    if(insert_skb_to_tx_ring(&channel_info[channelIndex],skb)) {
        netif_tx_stop_queue(netdev_get_tx_queue(netdev, channelIndex));
        return NETDEV_TX_BUSY;
    }

    //start tx anyway
    writel_relaxed(1, &channel_info[channelIndex].reg_base_channel->tx_ctl_status);
   /*uint32_t flag = readl_relaxed(&channel->reg_base_channel->tx_irq_flag);
    if(flag & IRQF_TX_EMPTY) {
        flag &= ~IRQF_TX_EMPTY;//clear TX_EMPTY flag
        writel_relaxed(flag, &channel->reg_base_channel->tx_irq_flag);
        wmb();
        writel_relaxed(1,&channel->reg_base_channel->tx_ctl_status);//restart tx
    }*/
    return NETDEV_TX_OK;
}
static const struct net_device_ops mynet_netdev_ops = {
	.ndo_open		= mynet_open,
	.ndo_stop		= mynet_stop,
	//.ndo_set_config		= mynet_config,
	.ndo_start_xmit		= mynet_xmit,
    .ndo_set_mac_address = eth_mac_addr,
	//.ndo_do_ioctl		= mynet_ioctl,
	//.ndo_get_stats		= mynet_stats,
	//.ndo_change_mtu		= mynet_change_mtu,
	//.ndo_tx_timeout    = mynet_tx_timeout,
};

static int mynet_poll_tx(struct napi_struct *napi, int budget)
{
    struct channel_data * channel = container_of(napi, struct channel_data, napi_tx);
    int count=0;
    int format_error = 1;

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
            dma_unmap_sg(&pdev->dev, channel->tx_ring_full->scl, channel->tx_ring_full->num_sg, DMA_FROM_DEVICE);
            devm_kfree(&pdev->dev,channel->tx_ring_full->scl);
            kfree_skb(channel->tx_ring_full->skb);
            ++count;
            format_error=0;
        } else {
            format_error=1;
        }
        channel->tx_ring_full = channel->tx_ring_full->next;
    }
    //spin_unlock(&channel->spinlock_tx_ring_full);

    BUG_ON(format_error);//unknown error,tx ring data was damaged

    //wake up queue anyway
    netif_tx_wake_queue(netdev_get_tx_queue(netdev,channel->queue_index));

    //unmask IRQF_TX_SEND
    //uini32_t mask = readl_relaxed(&channel->reg_base_channel->tx_irq_mask);
    //mask |= IRQF_TX_SEND;
    writel_relaxed(IRQF_TX_SEND, &channel->reg_base_channel->tx_irq_mask);
    return count;
}
static int mynet_poll_rx(struct napi_struct *napi, int budget)
{
    struct channel_data * channel = container_of(napi, struct channel_data, napi_tx);
    int count=0;
    int format_error=1;
    while(budget>count)
    {
        //if(is_node_transfer(channel->tx_ring_full)) {
            if(is_node_belong_to_hw(channel->rx_ring)) {
                //now, there is no linear_buffer to receive
                break;
            }

            //replace
            //char * linear_buffer_replace = napi_alloc_frag(MAX_RX_SKB_LINEAR_BUFF_LEN);
            char *linear_buffer_replace = page_frag_alloc_align(&channel->page_cache, MAX_RX_SKB_LINEAR_BUFF_LEN, GFP_KERNEL, 0);
            if(unlikely(!linear_buffer_replace)) {
                pr_err("napi_alloc_frag failed");
                return count;
            }
            dma_addr_t dma_addr = dma_map_single(&pdev->dev,
                                                 linear_buffer_replace + ETH_HEADER_OFFSET_IN_LINEAR_BUFF,
                                                 MAX_RECV_LEN,
                                                 DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(&pdev->dev, dma_addr))) {
                pr_err("dma_map_single  failed");
                skb_free_frag(linear_buffer_replace);  //page_frag_free
                return count;
            }
            dma_unmap_single(&pdev->dev,
                            channel->rx_ring->virtual_addr->base,
                            channel->rx_ring->virtual_addr->len,
                            DMA_FROM_DEVICE);
            char * linear_buffer_recv = channel->rx_ring->linear_buffer;//

            channel->rx_ring->linear_buffer = linear_buffer_replace;
            writel_relaxed(dma_addr,                        &channel->rx_ring->virtual_addr->base);
            writel_relaxed(MAX_RECV_LEN,                    &channel->rx_ring->virtual_addr->len);
            writel_relaxed(NODE_F_TRANSFER|NODE_F_BELONG,   &channel->rx_ring->virtual_addr->flag);
            channel->rx_ring = channel->rx_ring->next;

            //recv
            struct sk_buff * skb = build_skb(linear_buffer_recv, MAX_RX_SKB_LINEAR_BUFF_LEN);
            if (unlikely(!skb)) {
                skb_free_frag(linear_buffer_recv);
                netdev->stats.rx_dropped++;
                return count;
            }
            skb_reserve(skb, ETH_HEADER_OFFSET_IN_LINEAR_BUFF);
            skb_record_rx_queue(skb,channel->queue_index);
            //skb_mark_for_recycle(skb); see page_pool
            napi_gro_receive(napi,skb);
            ++count;
            format_error = 0;
        //}
    }


    BUG_ON(format_error);



    //unmask IRQF_TX_IRQF_RX_RECVSEND
    //uini32_t mask = readl_relaxed(&channel->reg_base_channel->tx_irq_mask);
    //mask |= IRQF_RX_RECV;
    writel_relaxed(IRQF_RX_RECV,  &channel->reg_base_channel->tx_irq_mask);


    //start rx anyway
    writel_relaxed(1,  &channel->reg_base_channel->rx_ctl_status);

    return count;
}

static int mynet_probe(struct platform_device *dev)
{
    int irq;
    pdev = dev;


    /*if(!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
        pr_err("%s: dma_set_mask failed\n",__func__);
        return -1;
    }
    if(!dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32))) {
        pr_err("%s: dma_set_coherent_mask failed\n",__func__);
        return -1;
    }*/

    //parse dtb
    struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        pr_err("%s: fail to get RegCommon virtual base addr\n",__func__);
        return -ENODEV;
    }
    reg_base_common = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(reg_base_common))
        return PTR_ERR(reg_base_common);

    for(int i=0; i<MAX_CHANNEL_NUM;++i) {
        res = platform_get_resource(pdev, IORESOURCE_MEM, i+1);
        if (!res) {
            pr_err("%s: fail to get RegChannel virtual base addr, channel=%d\n",__func__,i);
            return -ENODEV;
        }
        channel_info[i].reg_base_channel = devm_ioremap_resource(&pdev->dev, res);
        if (IS_ERR(channel_info[i].reg_base_channel))
            return PTR_ERR(channel_info[i].reg_base_channel);
    }
    for(int i=0; i<MAX_CHANNEL_NUM;++i) {
        irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL);
        if(irq < 0) {
            pr_err("%s: fail to get tx irq, channel=%d,irq=%d\n",__func__,i,0);
            return -ENODEV;
        }
        channel_info[i].tx_irqs = irq;
        irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL+1);
        if(irq < 0) {
            pr_err("%s: fail to get rx irq, channel=%d,irq=%d\n",__func__,i,1);
            return -ENODEV;
        }
        channel_info[i].rx_irqs = irq;
    }

    /*for(int i=0; i<MAX_CHANNEL_NUM;++i) {
        spin_lock_init(&channel_info[i].spinlock_tx_ring_empty);
        spin_lock_init(&channel_info[i].spinlock_tx_ring_full);
        channel_info[i].queue_index = i;
    }*/

    //param check
    real_tx_channel_count = param_real_tx_channel_count;
    real_rx_channel_count = param_real_rx_channel_count;
    tx_ring_node_count = param_tx_ring_node_count+1;
    rx_ring_node_count = param_rx_ring_node_count;
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
                               NET_NAME_ENUM,
                               ether_setup,
                               real_tx_channel_count, 
                               real_rx_channel_count);
    if(!netdev) {
        pr_err("%s: failed to create netdev\n",__func__);
        return -1;
    }
    for(int i=0; i<real_tx_channel_count; ++i) {
	    netif_napi_add(netdev, &channel_info[i].napi_tx, mynet_poll_tx);
    }
    for(int i=0; i<real_rx_channel_count; ++i) {
        netif_napi_add(netdev, &channel_info[i].napi_rx, mynet_poll_rx);
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
