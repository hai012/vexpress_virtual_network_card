#ifndef __MYNET_H
#define __MYNET_H

/*
kmalloc   kmalloc_array
kzalloc   kcalloc
*/


/*
drivers/net/ethernet/freescale/dpaa2/dpaa2-eth.c  dpaa2_eth_build_sg_fd
include/linux/netdev_features.h

barrier()
writel
SO_REUSEPORT  SO_REUSEADDR

http://127.0.0.1:8088/source/xref/kernel_android13/drivers/net/ethernet/mediatek/mtk_eth_soc.c#mtk_tx_map
http://127.0.0.1:8088/source/xref/kernel_android13/drivers/net/ethernet/freescale/dpaa2/dpaa2-eth.c#797


NETIF_F_FRAGLIST   skb_shinfo(skb)->frag_list
NETIF_F_SG         skb_shinfo(skb)->frags

NETIF_F_FRAGLIST does not seem to be used often
NETIF_F_FRAGLIST is used in lo net device

handle IPv4/IPv6 fragmentation and reassembly
TSO/UFO/GRO is related to NETIF_F_FRAGLIST and NETIF_F_SG
*/



//align 2bytes
//dsc mac 6bytes
//src mac 6bytes
//type/len 2bytes
//64~1500 bytes
//Frame Check Sequence 4bytes
// 2+6+6+1500+4 = 1518
#define MAX_RX_SKB_BUFF_LEN 1518



#define MAX_SKB_FRAGS 17
#define NODE_F_BELONG (1<<0)
#define NODE_F_TRANSFER (1<<1)


#define MAX_RX_MAC_FILTER_MASK 4
#define MAX_CHANNEL_NUM 4

#define IRQF_TX_SEND        (1<<0)
#define IRQF_TX_EMPTY       (1<<1)
#define IRQF_TX_ERR         (1<<2)
#define ALL_IRQF_TX         (IRQF_TX_SEND|IRQF_TX_EMPTY|IRQF_TX_ERR)

#define IRQF_RX_RECV        (1<<0)
#define IRQF_RX_FULL        (1<<1)
#define IRQF_RX_ERR         (1<<2)
#define ALL_IRQF_RX         (IRQF_RX_RECV|IRQF_RX_FULL|IRQF_RX_ERR)

#define CHANNEL_IRQ_TX 0
#define CHANNEL_IRQ_RX 1
#define MAX_IRQ_NUM_PER_CHANNEL 2




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
    //flag bit0 = 1,belone to eth card,bit0==0,belone to driver.
    //flag bit1 = 1,transfer imidiately, bit1 = 0, transfer together with the next.
    uint32_t flag;
    uint32_t base;
    uint32_t len;
    uint32_t next;
};


struct ring_node_info {
    struct ring_node_t *virtual_addr;
    dma_addr_t dma_addr;
    struct skbuff *skb;
    struct ring_node_info * next;
}


struct mynet_info_t {
    //hw info
    struct RegCommon * reg_base_common;
    struct RegChannel *reg_base_channel[MAX_CHANNEL_NUM];
    int tx_irqs[MAX_CHANNEL_NUM];
    int rx_irqs[MAX_CHANNEL_NUM];

    //config info
    int real_tx_channel_count;
    int real_rx_channel_count;
    int poll_weight_tx;
    int poll_weight_rx;
    int tx_ring_node_count;
    int rx_ring_node_count;
}

struct irq_data {
    struct napi_struct napi;
    int channelIndex;
    struct mynet_priv_t *priv;
}

struct mynet_priv_t {
    struct net_device *netdev;
    struct irq_data irq_data_tx[MAX_CHANNEL_NUM];
    struct irq_data irq_data_rx[MAX_CHANNEL_NUM];

    struct dma_pool * pool;
    struct ring_node_info *ring_node_info_table;
    struct skb_buff *skb_rx;

    struct ring_node_info *tx_ring[MAX_CHANNEL_NUM];
    struct ring_node_info *rx_ring[MAX_CHANNEL_NUM];
    

    struct mynet_info_t * info;
}

#endif
