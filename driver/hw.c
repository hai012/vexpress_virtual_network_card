
void hw_deinit(struct mynet_info_t *info)
{

}


void hw_init(void)
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
}
void hw_start_real_channel(void)
{
    for(int i=0; i < info->real_tx_channel_count; ++i) {
        writel_relaxed(channel_info[i].tx_ring_full->dma_addr,    &channel_info[i].reg_base_channel->tx_ring_base);//set base
        writel_relaxed(0,                                         &channel_info[i].reg_base_channel->tx_irq_flag);
        writel_relaxed(0xffffffff,                                &channel_info[i].reg_base_channel->tx_irq_mask);//unmask irq
        wmb();
        writel_relaxed(1,                                         &channel_info[i].reg_base_channel->tx_ctl_status);//start
    }
    for(int i=0; i < info->real_rx_channel_count; ++i) {
        writel_relaxed(channel_info[i].rx_ring_full->dma_addr,    &channel_info[i].reg_base_channel->rx_ring_base);//set base
        writel_relaxed(0,                                         &channel_info[i].reg_base_channel->rx_irq_flag);
        writel_relaxed(0xffffffff,                                &channel_info[i].reg_base_channel->rx_irq_mask);//unmask irq
        wmb();
        writel_relaxed(1,                                         &channel_info[i].reg_base_channel->rx_ctl_status);//start
    }
}


