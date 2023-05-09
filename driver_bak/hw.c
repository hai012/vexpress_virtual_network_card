
void hw_deinit(struct mynet_info_t *info)
{

}


void hw_init(struct mynet_info_t *info)
    for(int i=0; i < MAX_CHANNEL_NUM; ++i) {
        writel(info->reg_base_channel[i]->tx_ctl_status, 0);
        writel(info->reg_base_channel[i]->tx_ring_base , 0);
        writel(info->reg_base_channel[i]->tx_irq_flag  , 0);
        writel(info->reg_base_channel[i]->tx_irq_mask  , 0);
        writel(info->reg_base_channel[i]->rx_ctl_status, 0);
        writel(info->reg_base_channel[i]->rx_ring_base , 0);
        writel(info->reg_base_channel[i]->rx_irq_flag  , 0);
        writel(info->reg_base_channel[i]->rx_irq_mask  , 0);
    }
}
void hw_start_real_channel(struct mynet_info_t *info)
{
    for(int i=0; i < info->real_tx_channel_count; ++i) {
        writel(info->reg_base_channel[i]->tx_ring_base , info->tx_ring[i]->dma_addr);//set base
        writel(info->reg_base_channel[i]->tx_irq_flag  , 0);
        writel(info->reg_base_channel[i]->tx_irq_mask  , 0xffffffff);//unmask irq
        writel(info->reg_base_channel[i]->tx_ctl_status, 1);//start
    }
    for(int i=0; i < info->real_rx_channel_count; ++i) {
        writel(info->reg_base_channel[i]->rx_ring_base , info->rx_ring[i]->dma_addr);
        writel(info->reg_base_channel[i]->rx_irq_flag  , 0);
        writel(info->reg_base_channel[i]->rx_irq_mask  , 0xffffffff);
        writel(info->reg_base_channel[i]->rx_ctl_status, 1);
    }
}
void hw_start_channel(struct mynet_info_t *info,int channelIndex,int tx_or_rx)
{
    if(tx_or_rx) {
        writel(info->reg_base_channel[channelIndex]->tx_ring_base , info->tx_ring[channelIndex]->dma_addr);
        writel(info->reg_base_channel[channelIndex]->tx_irq_flag  , 0);
        writel(info->reg_base_channel[channelIndex]->tx_irq_mask  , 0xffffffff);//unmask
        writel(info->reg_base_channel[channelIndex]->tx_ctl_status, 1);//start
    } else {
        writel(info->reg_base_channel[channelIndex]->rx_ring_base , info->rx_ring[channelIndex]->dma_addr);
        writel(info->reg_base_channel[channelIndex]->rx_irq_flag  , 0);
        writel(info->reg_base_channel[channelIndex]->rx_irq_mask  , 0xffffffff);
        writel(info->reg_base_channel[channelIndex]->rx_ctl_status, 1);
    }
}
void hw_stop_channel(struct mynet_info_t *info,int channelIndex,int tx_or_rx)
{
    if(tx_or_rx) {
        writel(info->reg_base_channel[channelIndex]->tx_ctl_status, 0);
        writel(info->reg_base_channel[channelIndex]->tx_ring_base , 0);
        writel(info->reg_base_channel[channelIndex]->tx_irq_flag  , 0);
        writel(info->reg_base_channel[channelIndex]->tx_irq_mask  , 0);
    } else {
        writel(info->reg_base_channel[channelIndex]->rx_ctl_status, 0);
        writel(info->reg_base_channel[channelIndex]->rx_ring_base , 0);
        writel(info->reg_base_channel[channelIndex]->rx_irq_flag  , 0);
        writel(info->reg_base_channel[channelIndex]->rx_irq_mask  , 0);
    }
}
void hw_stop_all_channel(struct mynet_info_t *info)
{
    for(int i=0; i < info->real_tx_channel_count; ++i) {
        writel(info->reg_base_channel[channelIndex]->tx_ctl_status, 0);
        writel(info->reg_base_channel[channelIndex]->tx_ring_base , 0);
        writel(info->reg_base_channel[channelIndex]->tx_irq_flag  , 0);
        writel(info->reg_base_channel[channelIndex]->tx_irq_mask  , 0);
    }
    for(int i=0; i < info->real_rx_channel_count; ++i) {
        writel(info->reg_base_channel[channelIndex]->rx_ctl_status, 0);
        writel(info->reg_base_channel[channelIndex]->rx_ring_base , 0);
        writel(info->reg_base_channel[channelIndex]->rx_irq_flag  , 0);
        writel(info->reg_base_channel[channelIndex]->rx_irq_mask  , 0);
    }
}
void hw_set_channel_irq_musk(struct mynet_info_t *info,int channelIndex,int tx_or_rx,uint32_t musk)
{
    if(tx_or_rx) {
        writel(info->reg_base_channel[channelIndex]->tx_irq_mask  , musk);
    } else {
        writel(info->reg_base_channel[channelIndex]->rx_irq_mask  , musk);
    }
}
void hw_clear_irq_flag(struct mynet_info_t *info,int channelIndex,int tx_or_rx,uint32_t irq_type)
{
    if(tx_or_rx) {
        writel(info->reg_base_channel[channelIndex]->tx_irq_flag  , irq_flag);
    } else {
        writel(info->reg_base_channel[channelIndex]->rx_irq_flag  , irq_flag);
    }
}