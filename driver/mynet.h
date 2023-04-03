#ifndef __MYNET_H
#define __MYNET_H




#define MAX_RX_MAC_FILTER_MASK 4
#define MAX_CHANNEL_NUM 4

#define IRQ_TX_PACKAGE   0
#define IRQ_TX_EMPTY     1
#define IRQ_TX_ERR       2
#define IRQ_RX_PACKAGE   3
#define IRQ_RX_FULL      4
#define IRQ_RX_ERR       5

#define MAX_IRQ_NUM_PER_CHANNEL_TX 3
#define MAX_IRQ_NUM_PER_CHANNEL_RX 3
#define MAX_IRQ_NUM_PER_CHANNEL (MAX_IRQ_NUM_PER_CHANNEL_TX + MAX_IRQ_NUM_PER_CHANNEL_RX)


struct RegCommon{
    //uint32_t link_status;
    //uint32_t link_speed;
    //uint32_t tsg;

    uint8_t global_mac_addr[6];
    uint8_t rx_mask[MAX_RX_MAC_FILTER_MASK][6];
    uint8_t rx_filter[MAX_RX_MAC_FILTER_MASK][6];
} __attribute__((packed));


struct RegChannel{
    uint32_t tx_ring_base;
    uint32_t tx_ctl_status;
    uint32_t tx_irq_flag;
    uint32_t tx_irq_mask;

    uint32_t rx_ring_base;
    uint32_t rx_ctl_status;
    uint32_t rx_irq_flag;
    uint32_t rx_irq_mask;
} __attribute__((packed));


struct ring_node_t {
    //flag==1,belone to eth card.
    //flag==0,belone to driver.
    uint32_t flag;
    void * buffer;
    size_t len;
    struct ring_node_t *next;
};


struct channel{
    int irq[MAX_IRQ_NUM_PER_CHANNEL];
    volatile struct RegChannel *reg_virtual_addr;

    //dma_alloc_coherent
    int tx_ring_count;
    struct ring_node_t *tx_ring_virtual_addr;
    dma_addr_t tx_ring_dma_addr;

    int rx_ring_count;
    struct ring_node_t *rx_ring_virtual_addr;
    dma_addr_t rx_ring_dma_addr;
}

struct mynet_priv {
    struct net_device *netdev;
    struct napi_struct napi;
    int poll_weight;
    //common
    struct RegCommon *reg_virtual_addr;

    //channel
    struct channel channels[MAX_CHANNEL_NUM];
}
#endif
