


irqreturn_t irq_handler_tx(int irq, void *data)
{
    struct channel_data * channel = (struct channel_data *)data;
    uint32_t flag = READ_ONCE(channel->reg_base_channel->tx_irq_flag);
    if(flag & IRQF_TX_SEND) {
        //mask IRQF_TX_SEND;
        uini32_t mask = READ_ONCE(channel->reg_base_channel->tx_irq_mask);
        mask &= ~IRQF_TX_SEND;
        WRITE_ONCE(channel->reg_base_channel->tx_irq_mask, mask);

        napi_schedule(& channel->napi_tx);

        flag &= ~IRQF_TX_SEND;//clear
    }
    if(flag & IRQF_TX_EMPTY) {

        flag &= ~IRQF_TX_EMPTY;//clear
    }
    if(flag & IRQF_TX_ERR) {

        flag &= ~IRQF_TX_ERR;//clear
    }
    WRITE_ONCE(channel->reg_base_channel->tx_irq_flag  , flag);
    return IRQ_HANDLED;
}
irqreturn_t irq_handler_rx(int irq, void *data)
{
    struct channel_data * channel = (struct channel_data *)data;
    uint32_t flag = READ_ONCE(channel->reg_base_channel->rx_irq_flag);
    if(flag & IRQF_RX_RECV) {
        napi_schedule(& channel->napi_rx);
        flag &= ~IRQF_RX_RECV;//clear
    }
    if(flag & IRQF_RX_FULL) {

        flag &= ~IRQF_RX_FULL;//clear
    }
    if(flag & IRQF_RX_ERR) {

        flag &= ~IRQF_RX_ERR;//clear
    }
    WRITE_ONCE(channel->reg_base_channel->rx_irq_flag  , flag);
    return IRQ_HANDLED;
}
int register_irq(void)
{
    for(int i=0; i<real_rx_channel_count; ++i) {
        if(request_irq(channel_info[i].rx_irqs,//irq_num
                    irq_handler,//func
                    0,//irqflags
                    "mynet_irq_rx",//irqname
                    &channel_info[i])) {//dev_id
            pr_err("%s: fail to request rx irq, channel=%d\n",__func__,i);
            while( --i >= 0 ) {
                free_irq(channel_info[i].rx_irqs);
            }
            return -1;
        }
    }
    for(int i=0; i<real_tx_channel_count; ++i) {
        if(request_irq(channel_info[i].tx_irqs,//irq_num
                    irq_handler,//func
                    0,//irqflags
                    "mynet_irq_tx",//irqname
                    &channel_info[i])) {//dev_id
            pr_err("%s: fail to request tx irq, channel=%d\n",__func__,i);
            while( --i >= 0 ) {
                free_irq(channel_info[i].tx_irqs);
            }
            return -1;
        }
    }
}
void unregister_irq(void)
{
    for(int i=0; i<real_rx_channel_count ++i) {
        free_irq(channel_info[i].rx_irqs);
    }
    for(int i=0; i<real_tx_channel_count ++i) {
        free_irq(channel_info[i].tx_irqs);
    }
}