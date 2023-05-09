


irqreturn_t irq_handler_tx(int irq, void *data)
{
    struct irq_data * irq_info = (struct irq_data *)data;
    napi_schedule(&irq_info -> napi);
    WRITE_ONCE(info->reg_base_channel[irq_info->channelIndex]->rx_irq_flag  , irq_flag);
    return IRQ_HANDLED;
}
irqreturn_t irq_handler_rx(int irq, void *data)
{
    struct irq_data * irq_info = (struct irq_data *)data;
    napi_schedule(&irq_info -> napi);
    WRITE_ONCE(info->reg_base_channel[channelIndex]->rx_irq_flag  , irq_flag);
    return IRQ_HANDLED;
}
int register_irq(struct net_device *dev)
{
    struct mynet_priv_t *priv = netdev_priv(dev);
    struct mynet_info_t *info = priv->info;
    for(int i=0; i< info->real_rx_channel_count; ++i) {
        priv->irq_data_tx[i].channelIndex = i;
        priv->irq_data_tx[i].priv = priv;
        if(request_irq(info->rx_irqs[i],//irq_num
                    irq_handler,//func
                    0,//irqflags
                    "mynet_irq_rx",//irqname
                    &priv->irq_data_tx[i])) {//dev_id
            pr_err("%s: fail to request rx irq, channel=%d\n",__func__,i);
            while( --i >= 0 ) {
                free_irq(info->rx_irqs[i]);
            }
            return -1;
        }
    }
    for(int i=0; i< info->real_tx_channel_count; ++i) {
        priv->irq_data_rx[i].channelIndex = i;
        priv->irq_data_rx[i].priv = priv;
        if(request_irq(info->tx_irqs[i],//irq_num
                    irq_handler,//func
                    0,//irqflags
                    "mynet_irq_tx",//irqname
                    &priv->irq_data_rx[i])) {//dev_id
            pr_err("%s: fail to request tx irq, channel=%d\n",__func__,i);
            while( --i >= 0 ) {
                free_irq(info->tx_irqs[i]);
            }
            return -1;
        }
    }
}
void unregister_irq(struct net_device *dev)
{
    struct mynet_priv_t *priv = netdev_priv(dev);
    struct mynet_info_t *info = priv->info;
    for(int i=0; i< info->real_rx_channel_count ++i) {
        free_irq(info->rx_irqs[i]);
    }
    for(int i=0; i< info->real_tx_channel_count ++i) {
        free_irq(info->tx_irqs[i]);
    }
}