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




static int param_real_tx_channel_count = 4;
module_param(param_real_tx_channel_count, int, 0644);
static int param_real_rx_channel_count = 4;
module_param(param_real_rx_channel_count, int, 0644);


//static int param_watchdog_timeo = 5;/* In jiffies */
//module_param(param_watchdog_timeo, int, 0);

static int param_tx_ring_node_count = 4096;
module_param(param_tx_ring_node_count, int, 0644);
static int param_rx_ring_node_count = 4096;
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

struct u64_stats_sync	stats_syncp_tx;
struct u64_stats_sync	stats_syncp_rx;
atomic64_t tx_packets;
atomic64_t tx_bytes;
atomic64_t rx_packets;
atomic64_t rx_bytes;


int	mynet_open(struct net_device *dev)
{
    //pr_err("mynet_open:hw_init\n");
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

    //pr_err("mynet_open:ring_init\n");
    if(ring_init()){
        return -1;
    }

    for(int i=0; i < real_tx_channel_count; ++i) {
        napi_enable(&channel_info[i].napi_tx);
    }
    for(int i=0; i < real_rx_channel_count; ++i) {
        napi_enable(&channel_info[i].napi_rx);
    }

    if(register_irq()) {
        return -1;
    }

    //pr_err("hw_start_real_channel\n");
    for(int i=0; i < real_rx_channel_count; ++i) {
        //pr_err("MYNET:%d:RX set base:channel_info[i].rx_ring->dma_addr=0x%08x\n",i,channel_info[i].rx_ring->dma_addr);
        writel_relaxed(channel_info[i].rx_ring->dma_addr,         &channel_info[i].reg_base_channel->rx_ring_base);//set base
        //pr_err("rx channel:%d set irq_flag\n",i);
        writel_relaxed(0,                                         &channel_info[i].reg_base_channel->rx_irq_flag);
        //pr_err("rx channel:%d set irq_mask\n",i);
        writel_relaxed(IRQF_RX_RECV,                              &channel_info[i].reg_base_channel->rx_irq_mask);//unmask IRQF_RX_RECV
        //pr_err("rx channel:%d set ctl_status\n",i);
        writel(1,                                                 &channel_info[i].reg_base_channel->rx_ctl_status);//start
    }
    

    for(int i=0; i < real_tx_channel_count; ++i) {
        //pr_err("MYNET:%d:TX set base:channel_info[i].tx_ring_full->dma_addr=0x%08x\n",i,channel_info[i].tx_ring_full->dma_addr);
        writel_relaxed(channel_info[i].tx_ring_full->dma_addr,    &channel_info[i].reg_base_channel->tx_ring_base);//set base
        //pr_err("tx channel:%d set irq_flag\n",i);
        writel_relaxed(0,                                         &channel_info[i].reg_base_channel->tx_irq_flag);
        //pr_err("tx channel:%d set irq_mask\n",i);
        writel_relaxed(IRQF_TX_SEND,                               &channel_info[i].reg_base_channel->tx_irq_mask);//unmask IRQF_TX_SEND
        //pr_err("tx channel:%d set ctl_status\n",i);
        writel(1,                                                 &channel_info[i].reg_base_channel->tx_ctl_status);//start
    }

    netif_tx_start_all_queues(netdev);
    //pr_err("mynet_open:return\n");
    return 0;
}
int	mynet_stop(struct net_device *dev)
{
    netif_tx_stop_all_queues(netdev);
    for(int i=0; i < real_tx_channel_count; ++i) {
        napi_disable(&channel_info[i].napi_tx);
    }
    for(int i=0; i < real_rx_channel_count; ++i) {
        napi_disable(&channel_info[i].napi_rx);
    }
    unregister_irq();
    ring_deinit();
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
    return 0;
}
uint32_t xmit_flag=0xf;
netdev_tx_t	mynet_xmit(struct sk_buff *skb,struct net_device *dev)
{
    int ret;
    //u32 processor_id = smp_processor_id();
    u16 channelIndex = skb_get_queue_mapping(skb);


    //pr_err("smp_processor_id=%d  qdisc_id=%d\n",processor_id,channelIndex);
    //if(0x0f != READ_ONCE(xmit_flag)){
    //    pr_err("multi cpus run mynet_xmit at the same time\n");
    //}

    //WRITE_ONCE(xmit_flag, processor_id);
    
    ret = insert_skb_to_tx_ring(&channel_info[channelIndex],skb);
    

    if(ret) {
        //pr_err("smp_processor_id=%d  qdisc_id=%d  insert_skb_to_tx_ring failed\n",smp_processor_id(),channelIndex);
        netif_tx_stop_queue(netdev_get_tx_queue(netdev, channelIndex));
        //WRITE_ONCE(xmit_flag, 0xf);
        return NETDEV_TX_BUSY;
    }

    //start tx anyway
    writel(1, &channel_info[channelIndex].reg_base_channel->tx_ctl_status);
   /*uint32_t flag = readl_relaxed(&channel->reg_base_channel->tx_irq_flag);
    if(flag & IRQF_TX_EMPTY) {
        flag &= ~IRQF_TX_EMPTY;//clear TX_EMPTY flag
        writel_relaxed(flag, &channel->reg_base_channel->tx_irq_flag);
        wmb();
        writel_relaxed(1,&channel->reg_base_channel->tx_ctl_status);//restart tx
    }*/
    //pr_err("smp_processor_id=%d  qdisc_id=%d  insert_skb_to_tx_ring OK\n",processor_id,channelIndex);
    //WRITE_ONCE(xmit_flag, 0xf);
    return NETDEV_TX_OK;
}

void mynet_stats64(struct net_device *dev,struct rtnl_link_stats64 *storage)
{
    storage->tx_packets = atomic64_read(&tx_packets);
    storage->tx_bytes = atomic64_read(&tx_bytes);
    storage->rx_packets = atomic64_read(&rx_packets);
    storage->rx_bytes = atomic64_read(&rx_bytes);
}

static int mynet_mac_addr(struct net_device *dev, void *p)
{
    //将单播MAC地址写入网卡,并设置网卡RX FIFO0 MAC地址过滤接收该单播MAC地址
    return eth_mac_addr(dev,p);
}
static void mynet_set_rx_mode(struct net_device *dev) 
{ 
    //用于根据dev中的状态设置网卡的接收模式，包括多播地址、广播地址以及接收所有数据包等功能
    //ifconfig设置混杂模式/多播地址时会调用
    //ndo_open返回0后会调用
}
static const struct net_device_ops mynet_netdev_ops = {
	.ndo_open		= mynet_open,
	.ndo_stop		= mynet_stop,
	//.ndo_set_config		= mynet_config,
	.ndo_start_xmit		= mynet_xmit,
    .ndo_set_mac_address = mynet_mac_addr,
     .ndo_set_rx_mode = mynet_set_rx_mode,
	//.ndo_do_ioctl		= mynet_ioctl,
	.ndo_get_stats64		= mynet_stats64,
	//.ndo_change_mtu		= mynet_change_mtu,
	//.ndo_tx_timeout    = mynet_tx_timeout,
    //.ndo_validate_addr = eth_validate_addr,
};

static int mynet_poll_tx(struct napi_struct *napi, int budget)
{
    struct channel_data * channel = container_of(napi, struct channel_data, napi_tx);
    long long done=0,bytes = 0;
    //int format_error = 1;
    u16 channelIndex;
    //pr_err("MYNET:mynet_poll_tx:channel=%d\n",channel->queue_index);
    //spin_lock(&channel->spinlock_tx_ring_full);
    while(budget > done) {
        if(channel->tx_ring_full==READ_ONCE(channel->tx_ring_empty)) {
            //pr_err("MYNET:mynet_poll_tx:don't have skb to release,"
            //        "there is no data in tx ting\n");
            break;
        }
        if(is_node_belong_to_hw(channel->tx_ring_full)) {
            //pr_err("MYNET:mynet_poll_tx:don't have skb to release,"
            //      "there is data in tx ting, but wait for hw send data\n");
            break;
        }
        if(is_node_transfer(channel->tx_ring_full)) {
            //pr_err("MYNET:mynet_poll_tx:find the last frag,and consume skb\n");
            dma_unmap_sg(&pdev->dev, channel->tx_ring_full->scl, channel->tx_ring_full->num_sg, DMA_FROM_DEVICE);
            devm_kfree(&pdev->dev,channel->tx_ring_full->scl);
            bytes += channel->tx_ring_full->skb->len;

            channelIndex = skb_get_queue_mapping(channel->tx_ring_full->skb);

            napi_consume_skb(channel->tx_ring_full->skb,budget);
            WRITE_ONCE(channel->tx_ring_full, channel->tx_ring_full->next);
            netif_tx_wake_queue(netdev_get_tx_queue(netdev,channelIndex));//wake up queue anyway
            ++done;
            continue;
            //format_error=0;
        } //else {
        //    format_error=1;
        //}
        WRITE_ONCE(channel->tx_ring_full, channel->tx_ring_full->next);
    }

    atomic64_add(done, &tx_packets);
    atomic64_add(bytes,&tx_bytes);

    if(done==budget) {
        return budget;
    }
    if(likely(napi_complete_done(napi,done))) {
        writel(IRQF_TX_SEND, &channel->reg_base_channel->tx_irq_mask);//unmask IRQF_TX_SEND
    }

    return done;
}



static int mynet_poll_rx(struct napi_struct *napi, int budget)
{
    struct channel_data * channel = container_of(napi, struct channel_data, napi_rx);
    int done=0, bytes = 0;
    char *linear_buffer_replace;
    char *linear_buffer_recv;
    dma_addr_t dma_addr;
    struct sk_buff * skb;
    uint32_t recv_bytes;
    
    while(budget>done)
    {
        //pr_err("MYNET:%d:RX:mynet_poll_rx done=%d budget=%d\n",channel->queue_index,done,budget);
        //if(is_node_transfer(channel->tx_ring_full)) {
            if(is_node_belong_to_hw(channel->rx_ring)) {
                //now, there is no linear_buffer to receive
                //pr_err("MYNET:%d:RX:now, there is no linear_buffer to receive\n",channel->queue_index);
                break;
            }

            //save received page
            dma_unmap_single(&pdev->dev,
                            channel->rx_ring->virtual_addr->base,
                            MAX_RECV_LEN,
                            DMA_FROM_DEVICE);
            linear_buffer_recv = channel->rx_ring->linear_buffer;
            recv_bytes = channel->rx_ring->virtual_addr->len;


            //replace
            //char * linear_buffer_replace = napi_alloc_frag(MAX_RX_SKB_LINEAR_BUFF_LEN);
            linear_buffer_replace = page_frag_alloc_align(&channel->page_cache, MAX_RX_SKB_LINEAR_BUFF_LEN, GFP_ATOMIC|GFP_DMA, 0);
            if(unlikely(!linear_buffer_replace)) {
                pr_err("MYNET:%d:RX:napi_alloc_frag failed\n",channel->queue_index);
                break;
            }
            dma_addr = dma_map_single(&pdev->dev,
                                      linear_buffer_replace + ETH_HEADER_OFFSET_IN_LINEAR_BUFF,
                                      MAX_RECV_LEN,
                                      DMA_TO_DEVICE);
            if (unlikely(dma_mapping_error(&pdev->dev, dma_addr))) {
                pr_err("MYNET:%d:RX:dma_map_single  failed\n",channel->queue_index);
                skb_free_frag(linear_buffer_replace);  //page_frag_free
                break;
            }
            channel->rx_ring->linear_buffer = linear_buffer_replace;
            writel_relaxed(dma_addr,                        &channel->rx_ring->virtual_addr->base);
            writel_relaxed(MAX_RECV_LEN,                    &channel->rx_ring->virtual_addr->len);
            writel(NODE_F_TRANSFER|NODE_F_BELONG,   &channel->rx_ring->virtual_addr->flag);
            channel->rx_ring = channel->rx_ring->next;
            //start rx anyway no mater hw rx thread is run
            writel(1,  &channel->reg_base_channel->rx_ctl_status);

            //recv
            skb = napi_build_skb(linear_buffer_recv, MAX_RX_SKB_LINEAR_BUFF_LEN);
            if (unlikely(!skb)) {
                pr_err("MYNET:%d:RX:build_skb fail\n",channel->queue_index);
                skb_free_frag(linear_buffer_recv);
                //netdev->stats.rx_dropped++;
                break;
            }
            skb_reserve(skb, ETH_HEADER_OFFSET_IN_LINEAR_BUFF);
            skb_record_rx_queue(skb,channel->queue_index);
            skb_put(skb,recv_bytes);
            //skb_mark_for_recycle(skb); see page_pool
            
            /*接收过程中，ip_summed字段包含了网络设备硬件告诉L4软件当前校验和的状态，各值含义如下：
CHECKSUM_NONE：硬件没有提供校验和，可能是硬件不支持，也可能是硬件校验出错但是并未丢弃数据包，这时L4软件需要自己进行校验和计算；
CHECKSUM_UNNECESSARY：硬件已经进行了完整的校验，软件无需再进行检查。这时L4软件会跳过校验和检查；
CHECKSUM_COMPLETE：硬件已经计算了L4报头和其payload部分的校验和，并将计算结果保存在了skb->csum中，L4软件只需要再计算伪报头即可；
发送过程中，ip_summed字段记录了L4软件想要告诉网络设备硬件关于当前数据包的校验和状态信心。各值含义如下：

CHECKSUM_NONE：L4软件已经对数据包进行了完整的校验，或者该数据包不需要校验。总之这种情况下网络设备硬件无需做任何校验和计算；
CHECKSUM_PARTIAL：L4软件计算了伪报头的校验和，并且将值保存在了数据报的L4层首部的check字段中，网络设备硬件需要计算其余部分的校验和（报文首部+数据部分）。硬件需要计算的报文范围是从skb->csum_start到报文最后一个字节，计算结果需要填写到（skb->csum_start + skb->csum_offset）处。
*/
            skb->ip_summed = CHECKSUM_UNNECESSARY;
            skb->protocol = eth_type_trans(skb, netdev);

            bytes += skb->len;
            ++done;


            //pr_err("MYNET:RX:SKB:buflen=%d recv_bytes=%d,len=%d\n", MAX_RECV_LEN ,recv_bytes,skb->len);
            //for(int i=0;i<skb->len;++i) {
            //    pr_err(" 0x%02hhx\n", *((char*)linear_buffer_recv + ETH_HEADER_OFFSET_IN_LINEAR_BUFF + i) );
            //}
            napi_gro_receive(napi,skb);
        //}
    }

    atomic64_add(done, &rx_packets);
    atomic64_add(bytes,&rx_bytes);


    if(done==budget) {
        //说明预算用完了但还有数据要处理，无需开启接收中断，
        //直接让内核将当前napi_struct加入softirq/net_rx_action待处理list
        //下次softirq执行时再次回调poll函数
        return budget;
    }

    //到这里说明预算没用完硬件中没数据了，这波poll结束，待下次触发中断napi_schedule后再回调poll

    if(likely(napi_complete_done(napi,done))) {
        //如果在某个napi_struct的poll期间的时候硬件中断上半部再调napi_schedule(napi_struct)，
        //就会产生NAPIF_STATE_MISSED标记，导致napi_complete_done返回false(意味着中断上半部没MASK接收中断)
        //mynet在硬件中断上半部已经关掉IRQF_RX_RECV，因此其实不会出现这种返回false的情况。
        //对于mask接收中断的情况，需要再次unmask以便后续触发中断再次napi_schedule
        writel(IRQF_RX_RECV,  &channel->reg_base_channel->rx_irq_mask);//umask IRQF_RX_RECV
    }
    
    return done;
}

static int mynet_probe(struct platform_device *dev)
{
    int irq;
    struct resource *res;

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
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
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
        if (irq_set_affinity(irq, cpumask_of(i))) {
            pr_err("Failed to set IRQ affinity channel/cpu =%d\n",i);
            return -ENODEV;
        }
        channel_info[i].tx_irqs = irq;
        irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL+1);
        if(irq < 0) {
            pr_err("%s: fail to get rx irq, channel=%d,irq=%d\n",__func__,i,1);
            return -ENODEV;
        }
        if (irq_set_affinity(irq, cpumask_of(i))) {
            pr_err("Failed to set IRQ affinity channel/cpu =%d\n",i);
            return -ENODEV;
        }
        channel_info[i].rx_irqs = irq;
    }

    /*for(int i=0; i<MAX_CHANNEL_NUM;++i) {
        spin_lock_init(&channel_info[i].spinlock_tx_ring_empty);
        spin_lock_init(&channel_info[i].spinlock_tx_ring_full);
        channel_info[i].queue_index = i;
        channel_info[i].tx_packets = 0;
        channel_info[i].tx_bytes = 0;
        channel_info[i].rx_packets = 0;
        channel_info[i].rx_bytes = 0;
    }*/
    atomic64_set(&rx_packets,0);
    atomic64_set(&rx_bytes,0);
    atomic64_set(&tx_packets,0);
    atomic64_set(&tx_bytes,0);

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
                               NET_NAME_ENUM,//网卡名由内核枚举
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
    //dev->flags           |= IFF_NOARP;
    //dev->features        |= NETIF_F_HW_CSUM;
/*NETIF_F_IP_CSUM	2	网络设备可以提供对基于IPv4的TCP和UDP数据包进行校验，其它协议报文不支持
NETIF_F_NO_CSUM	4	网络设备的传输非常可靠，无需L4执行任何校验，环回设备一般设置该标记
NETIF_F_HW_CSUM	8	网络设备可以对任何L4协议的数据包进行校验，基本很少有硬件能够实现
NETIF_F_IPV6_CSUM	16	网络设备可以对基于IPv6的TCP和UDP数据包进行校验，其它协议报文不支持*/
	//netdev->features       |=  NETIF_F_GRO |NETIF_F_GSO| NETIF_F_SG;//hardware doesn't support checksum ,calc it by software when GSO segment
    netdev->priv_flags |= IFF_UNICAST_FLT;
    netdev->features       |=  NETIF_F_GRO |NETIF_F_GSO|NETIF_F_SG;
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
