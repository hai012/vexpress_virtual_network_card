#ifndef __MYNET_H
#define __MYNET_H

/*
kmalloc   kmalloc_array
kzalloc   kcalloc
*/


/*
drivers/net/ethernet/freescale/dpaa2/dpaa2-eth.c  dpaa2_eth_build_sg_fd
include/linux/netdev_features.h


all :
    (start/stop tsg)		(start/stop checksum)
    (link speed)     		(link status)

	(global mac addr)
	(rx mac addr musk[4])	(rx mac addr filter[4])

fec_enet_rx_napi




barrier()
writel
SO_REUSEPORT  SO_REUSEADDR
http://127.0.0.1:8080/source/xref/linux-6.1.15/drivers/net/ethernet/mediatek/mtk_eth_soc.c#mtk_tx_map
http://127.0.0.1:8088/source/xref/kernel_android13/drivers/net/ethernet/mediatek/mtk_eth_soc.c#mtk_tx_map
http://127.0.0.1:8088/source/xref/kernel_android13/drivers/net/ethernet/freescale/dpaa2/dpaa2-eth.c#797


NETIF_F_FRAGLIST   skb_shinfo(skb)->frag_list
NETIF_F_SG         skb_shinfo(skb)->frags

NETIF_F_FRAGLIST does not seem to be used often
NETIF_F_FRAGLIST is used in lo net device

handle IPv4/IPv6 fragmentation and reassembly
TSO/UFO/GRO is related to NETIF_F_FRAGLIST and NETIF_F_SG
*/




#include <linux/scatterlist.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/spinlock_types.h>
#include <linux/dmapool.h>
#include <linux/platform_device.h> 
#include <linux/gfp.h>
//NET_SKB_PAD
//NET_IP_ALIGN   0 or 2
//ETH_HLEN 14    dest_mac 、src_mac 、type
//ETH_DATA_LEN   1500
//ETH_FCS_LEN 4  tap dev doesn't have FCS
#define MAX_RX_SKB_LINEAR_BUFF_LEN \
(SKB_DATA_ALIGN((NET_SKB_PAD  +  NET_IP_ALIGN + ETH_HLEN + ETH_DATA_LEN))\
+ SKB_DATA_ALIGN(sizeof(struct skb_shared_info)))
                               
#define ETH_HEADER_OFFSET_IN_LINEAR_BUFF (NET_SKB_PAD  +  NET_IP_ALIGN)
#define MAX_RECV_LEN (ETH_HLEN + ETH_DATA_LEN)



//#define MAX_SKB_FRAGS 17
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
//////////////////////////////////////////////////////////////////////////////////////

struct ring_node_info {
    struct ring_node_t *virtual_addr;
    dma_addr_t dma_addr;
    struct ring_node_info * next;

    //tx
    struct sk_buff *skb;
    struct scatterlist *scl;
    int num_sg;
    //rx
    char * linear_buffer;
};

//TX    channel <- Qdisc(do not need lock queue) <- cpu
//RX    hash(skb) -> cpu
struct channel_data {
    struct RegChannel *reg_base_channel;
    unsigned short queue_index; 
    int tx_irqs;
    int rx_irqs;


    struct napi_struct napi_tx;//preempt
    struct napi_struct napi_rx;

    //tx_ring_empty point to a node which is empty
    //if tx_ring_full!=tx_ring_empty, then tx_ring_full point to a full node
    struct ring_node_info *tx_ring_empty;
    struct ring_node_info *tx_ring_full;
    //spinlock_t spinlock_tx_ring_empty;
    //spinlock_t spinlock_tx_ring_full;

    struct ring_node_info *rx_ring;
    //int is_rx_ring_full;
    //int is_tx_ring_empty;
    struct page_frag_cache page_cache;

};

//config data
extern int real_tx_channel_count;
extern int real_rx_channel_count;
extern int poll_weight_tx;
extern int poll_weight_rx;
extern int tx_ring_node_count;
extern int rx_ring_node_count; 
//common data
extern struct RegCommon * reg_base_common;
extern struct net_device * netdev;
extern struct platform_device *pdev;
extern struct u64_stats_sync	stats_syncp_tx;
extern struct u64_stats_sync	stats_syncp_rx;
extern atomic64_t tx_packets;
extern atomic64_t tx_bytes;
extern atomic64_t rx_packets;
extern atomic64_t rx_bytes;
//channel data
extern struct channel_data channel_info[MAX_CHANNEL_NUM];



static int inline is_node_belong_to_hw(struct ring_node_info *node)
{
    return NODE_F_BELONG & readl_relaxed(&node->virtual_addr->flag);
}
static int inline is_node_transfer(struct ring_node_info *node)
{
    return NODE_F_TRANSFER & readl_relaxed(&node->virtual_addr->flag);
}


int ring_init(void);
int rx_ring_dma_init(void);
int insert_skb_to_tx_ring(struct channel_data * channel,struct sk_buff *skb);
int register_irq(void);
void unregister_irq(void);
void ring_deinit(void);

#endif
