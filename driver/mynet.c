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
//#include <linux/types.h> //dma_addr_t

#include "mynet.h"


static int POLL_WEIGHT = 4;
module_param(POLL_WEIGHT, int, 0);
 
static int WATCHDOG_TIMEO = 5;/* In jiffies */
module_param(WATCHDOG_TIMEO, int, 0);


irqreturn_t irq_handler_tx_package(int irq, void *data)
{
	*(base+1)=0;//clear irq
	return IRQ_HANDLED;
}

int init_irq(struct net_device *dev)
{



    struct mynet_priv *mynet_priv = netdev_priv(dev);


    for(int i=0; i<MAX_CHANNEL_NUM;++i){
        for(int j=0; j<MAX_IRQ_NUM_PER_CHANNEL;++j){
            int irq = platform_get_irq(pdev, i*MAX_IRQ_NUM_PER_CHANNEL+j);
            if(irq<0) {
                    dev_err(dev,"%s: Can't get irq, index=%d\n",__func__,i*MAX_IRQ_NUM_PER_CHANNEL+j);
                    clean_module(dev);
                    return -1;
            }
            mynet_priv->channels[i].irq[j] = irq;
        }
    }

    irqreturn_t *(irq_handler[])(int, void *) = {
        irq_handler_tx,
        irq_handler_rx
    }
    int state[MAX_CHANNEL_NUM][MAX_IRQ_NUM_PER_CHANNEL] = {{0,},};
    for(int i=0; i<MAX_CHANNEL_NUM; ++i) {
        for(int j=0; j<MAX_IRQ_NUM_PER_CHANNEL; ++j){
            if(request_irq(mynet_priv->channels[i].irq[j],//irq_num
                           irq_handler[j],//func
                           0,//irqflags
                           "mynet_irq",//irqname
                           NULL)) {//dev_id
                goto err_out;
            } else {
                state[i][j] = 1;
            }
        }
    }
    return 0;
err_out:
    for(int i=0; i<MAX_CHANNEL_NUM; ++i) {
        for(int j=0; j<MAX_IRQ_NUM_PER_CHANNEL; ++j){
            if(state[i][i]) {
                free_irq(mynet_priv->channels[i].irq[j],//irq_num
                 NULL); //dev_id
            }
        }
    }
}


int ring_count_modify(struct channel *channel,int tx_count,int rx_count)
{
    struct mynet_priv *mynet_priv = netdev_priv(dev);
    int state[MAX_CHANNEL_NUM][MAX_IRQ_NUM_PER_CHANNEL] = {{0,},};



    virtual_addr = dma_alloc_coherent(dev,
                        sizeof(struct ring_node_t)*RING_NODE_COUNT*2,
                        &dma_addr,
                        GFP_KERNEL);


    for(int i=0; i<MAX_CHANNEL_NUM; ++i) {
        for(int i=0; i<RING_NODE_COUNT; ++i) {
            struct ring_node_t *virtual_addr;
            dma_addr_t dma_addr;
            
            if(!virtual_addr) {

            } else {

            }
            struct ring_node_t *rx_ring_virtual_addr;
            dma_addr_t rx_ring_dma_addr;
            mynet_priv.dma_alloc_coherent()
        }
    }
}

int	mynet_open(struct net_device *dev)
{
    struct mynet_priv *mynet_priv = netdev_priv(dev);


    tx_data = kzalloc(4,GFP_KERNEL);
    if(!tx_data) {
        pr_err("kzalloc rx_data failed");
        return -1;
    }
    *tx_data = 888;

    dma_dst_addr = dma_map_single(&pdev->dev, tx_data, 4, DMA_TO_DEVICE);
    if(!dma_dst_addr) {
        pr_err("dma_map_single dma_dst_addr failed");
        return -1;
    }
    *base = (uint32_t)tx_data;
    dma_unmap_single(&pdev->dev, dma_dst_addr,4, DMA_TO_DEVICE);

    rx_data = kzalloc(4,GFP_KERNEL);
    if(!rx_data) {
        pr_err("kzalloc rx_data failed");
        return -1;
    }

    dma_dst_addr2 = dma_map_single(&pdev->dev, rx_data, 4, DMA_FROM_DEVICE);
    if(!dma_dst_addr) {
        pr_err("dma_map_single dma_dst_addr failed");
        return -1;
    }
     *(base+3) = (uint32_t)rx_data; 
     dma_unmap_single(&pdev->dev, dma_dst_addr2,4, DMA_FROM_DEVICE);
     pr_err("DMA_FROM_DEVICE:%d\n", *rx_data);  
    return 0;
}

static const struct net_device_ops mynet_netdev_ops = {
	.ndo_open		= mynet_open,
	.ndo_stop		= mynet_release,
	.ndo_set_config		= mynet_config,
	.ndo_start_xmit		= mynet_tx,
	.ndo_do_ioctl		= mynet_ioctl,
	.ndo_get_stats		= mynet_stats,
	.ndo_change_mtu		= mynet_change_mtu,
	.ndo_tx_timeout    = mynet_tx_timeout,
};
static int mynet_poll_tx(struct napi_struct *, int budget)
{

}
static int mynet_poll_rx(struct napi_struct *, int budget)
{

}
static int mynet_probe(struct platform_device *pdev)
{
    struct net_device * dev = alloc_netdev_mqs(sizeof(struct mynet_device), 
                                                    "mynet%d",
                                                    NET_NAME_UNKNOWN,
                                                    ether_setup,
                                                    MAX_CHANNEL_NUM, 
                                                    MAX_CHANNEL_NUM);
    if(!dev) {
        pr_err("failed to create netdev\n");
        return -1;
    }
    //netdev priv init
    mynet_priv->netdev = dev;
    struct mynet_priv *mynet_priv = netdev_priv(dev);

    struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, i);
    if (!res) {
        dev_err(dev,"%s: Can't get %d MEM resource, index=%d \n",__func__,i);
        clean_module(dev);
        return -1;
    }
    mynet_priv->reg_virtual_addr = (struct RegCommon *)res->start;
    for(int i=0; i<MAX_CHANNEL_NUM;++i){
        res = platform_get_resource(pdev, IORESOURCE_MEM, i);
        if (!res) {
            dev_err(dev,"%s: Can't get %d MEM resource, index=%d \n",__func__,i);
            clean_module(dev);
            return -1;
        }
        mynet_priv->channels[i].reg_virtual_addr = (struct RegChannel *)res->start;
    }



    //init netdev and napi
	netif_napi_add(dev, &mynet_priv->napi_tx, mynet_poll_tx, POLL_WEIGHT_TX);
    netif_napi_add(dev, &mynet_priv->napi_rx, mynet_poll_rx, POLL_WEIGHT_RX);
    dev->netdev_ops = &mynet_netdev_ops;
	dev->flags           |= IFF_NOARP;
	dev->features        |= NETIF_F_HW_CSUM;
	dev->watchdog_timeo = WATCHDOG_TIMEO;
	
    if(register_netdev(dev)) {
        dev_err(dev,"%s: Can't get irq, index=%d\n",__func__,i*MAX_IRQ_NUM_PER_CHANNEL+j);
        clean_module(dev);
        return -1;
    }
}

static int mynet_remove(struct platform_device *dev)
{
    clean_module(netdev);
    iounmap(base);
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
