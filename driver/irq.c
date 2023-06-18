#include <linux/irqreturn.h>
#include "mynet.h"


irqreturn_t irq_handler_tx(int irq, void *data)
{
    struct channel_data * channel = (struct channel_data *)data;
    uint32_t flag = readl_relaxed(&channel->reg_base_channel->tx_irq_flag);
    //printk("MYNET:tx_hw_irq,flag:0x%04x\n",flag);
    if(likely(flag & IRQF_TX_SEND)) {
        //printk("MYNET:tx_hw_irq,prep\n");
        //uini32_t mask = readl_relaxed(&channel->reg_base_channel->tx_irq_mask);
        //mask &= ~IRQF_TX_SEND;
        writel_relaxed(0, &channel->reg_base_channel->tx_irq_mask);//mask IRQF_TX_SEND;
        napi_schedule(&channel->napi_tx);
    }
    /*if(flag & IRQF_TX_EMPTY) { 
        flag &= ~IRQF_TX_EMPTY;//clear
    }
    if(flag & IRQF_TX_ERR) {
        //netif_tx_stop_queue(netdev_get_tx_queue(dev, channel->queue_index));
        BUG();
        //flag &= ~IRQF_TX_ERR;//clear
    }*/
    //if(unlikely(flag & IRQF_TX_ERR)) {
        //printk("MYNET:irq_handler_tx:clear flag\n");
    //};

    //clear all tx irq flag
    writel(0, &channel->reg_base_channel->tx_irq_flag);
    return IRQ_HANDLED;
}
irqreturn_t irq_handler_rx(int irq, void *data)
{
    struct channel_data * channel = (struct channel_data *)data;
    uint32_t flag = readl_relaxed(&channel->reg_base_channel->rx_irq_flag);
    //printk("MYNET:rx_hw_irq,flag:0x%08x\n",flag);
    if(likely(flag & IRQF_RX_RECV)) {
        //uint32_t mask = readl_relaxed(&channel->reg_base_channel->tx_irq_mask);
        //mask &= ~IRQF_RX_RECV;
        writel_relaxed(0, &channel->reg_base_channel->rx_irq_mask);//mask IRQF_RX_RECV;
        napi_schedule(&channel->napi_rx);
    }
    /*if(flag & IRQF_RX_FULL) {
 
    }
    if(flag & IRQF_RX_ERR) {

    }*/
    //printk("MYNET:rxirq:w:0x%04x\n",flag);
    //if(unlikely(flag & IRQF_RX_ERR)) {

    //}
    
    //clear all irq flag
    writel(0, &channel->reg_base_channel->rx_irq_flag);
    return IRQ_HANDLED;
}
const char * irq_name_rx[] = {
    "mynet_irq_rx_0",
    "mynet_irq_rx_1",
    "mynet_irq_rx_2",
    "mynet_irq_rx_3"
};
const char * irq_name_tx[] = {
    "mynet_irq_tx_0",
    "mynet_irq_tx_1",
    "mynet_irq_tx_2",
    "mynet_irq_tx_3"
};
int register_irq(void)
{
    for(int i=0; i<real_rx_channel_count; ++i) {
        if(devm_request_irq(&pdev->dev,channel_info[i].rx_irqs,//irq_num
                    irq_handler_rx,//func
                    0,//irqflags
                    irq_name_rx[i],//irqname
                    &channel_info[i])) {//dev_id
            pr_err("%s: fail to request %s\n",__func__,irq_name_rx[i]);
            while( --i >= 0 ) {
                devm_free_irq(&pdev->dev,channel_info[i].rx_irqs, &channel_info[i]);
            }
            return -1;
        }
    }
    for(int i=0; i<real_tx_channel_count; ++i) {
        if(devm_request_irq(&pdev->dev,channel_info[i].tx_irqs,//irq_num
                    irq_handler_tx,//func
                    0,//irqflags
                    irq_name_tx[i],//irqname
                    &channel_info[i])) {//dev_id
            pr_err("%s: fail to request %s\n",__func__,irq_name_tx[i]);
            while( --i >= 0 ) {
                devm_free_irq(&pdev->dev,channel_info[i].tx_irqs, &channel_info[i]);
            }
            return -1;
        }
    }
    return 0;
}
void unregister_irq(void)
{
    for(int i=0; i<real_rx_channel_count; ++i) {
        devm_free_irq(&pdev->dev,channel_info[i].rx_irqs, &channel_info[i]);
    }
    for(int i=0; i<real_tx_channel_count; ++i) {
        devm_free_irq(&pdev->dev,channel_info[i].tx_irqs, &channel_info[i]);
    }
}