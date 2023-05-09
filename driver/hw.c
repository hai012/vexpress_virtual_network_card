
void hw_deinit(struct mynet_info_t *info)
{

}


void hw_init(void)
    for(int i=0; i < MAX_CHANNEL_NUM; ++i) {
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_ctl_status, 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_ctl_status, 0);
        wmb();
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_ring_base , 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_irq_flag  , 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_irq_mask  , 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_ring_base , 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_irq_flag  , 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_irq_mask  , 0);
    }
}
void hw_start_real_channel(void)
{
    for(int i=0; i < info->real_tx_channel_count; ++i) {
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_ring_base , channel_info[i].tx_ring_full->dma_addr);//set base
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_irq_flag  , 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_irq_mask  , 0xffffffff);//unmask irq
        wmb();
        WRITE_ONCE(channel_info[i].reg_base_channel->tx_ctl_status, 1);//start
    }
    for(int i=0; i < info->real_rx_channel_count; ++i) {
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_ring_base , channel_info[i].rx_ring_full->dma_addr);
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_irq_flag  , 0);
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_irq_mask  , 0xffffffff);
        wmb();
        WRITE_ONCE(channel_info[i].reg_base_channel->rx_ctl_status, 1);
    }
}