#ifndef __MYNET_TYPES_H
#define __MYNET_TYPES_H


#include "hw/sysbus.h"


#define TYPE_MYNET "mynet"
#define MYNET(obj) OBJECT_CHECK(MynetState, (obj), TYPE_MYNET)
#define TYPE_MYNET_CHANNEL "mynet_channel"
#define MYNET_CHANNEL(obj) OBJECT_CHECK(MynetStateChannel, (obj), TYPE_MYNET_CHANNEL)




#define MAX_RX_MAC_FILTER_MASK 4
#define MAX_CHANNEL_NUM 4

#define IRQF_TX_SEND        1
#define IRQF_TX_STOP        2
#define IRQF_TX_ERR         4
#define MAX_IRQF_TX_PER_CHANNEL 3

#define IRQF_RX_SEND      1
#define IRQF_RX_FULL      2
#define IRQF_RX_ERR       4
#define MAX_IRQF_RX_PER_CHANNE 3

#define MAX_HW_IRQ_PER_CHANNEL  2



struct MynetStateChannel;
struct ring_node_t;
struct RegChannel;
struct MynetState;
struct RegCommon;


struct RegCommon{
    //uint32_t link_status;
    //uint32_t link_speed;
    //uint32_t tsg;

    uint8_t global_mac_addr[6];
    uint8_t rx_mask[MAX_RX_MAC_FILTER_MASK][6];
    uint8_t rx_filter[MAX_RX_MAC_FILTER_MASK][6];
} __attribute__((packed));


struct MynetState{
    SysBusDevice parent_obj;
    //common
    MemoryRegion mmio;
    char tap_name[IFNAMSIZ];
    struct RegCommon reg;
    //channel
    struct MynetStateChannel *channels[MAX_CHANNEL_NUM];
};


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





// ring data: little ending 
// frags_addr/nextNode_addr/buffer is guest phy addr
struct frag_t {
    uint64_t buffer;
    uint64_t len;
}
struct ring_node_t {
    //flag==1,belone to eth card.
    //flag==0,belone to driver.
    int flag;
    int frags_count;
    uint64_t frags_addr;
    uint64_t byte_count;
    uint64_t next;
};


static inline void *guest_to_host(uint64_t vguest_phy_addr)
{
    MemoryRegionSection mem_section_tx = memory_region_find(get_system_memory((hwaddr)msc->tx_node_host), value, 0);
    return memory_region_get_ram_ptr(mem_section_tx.mr) + mem_section_tx.offset_within_region;
}


struct MynetStateChannel {
    SysBusDevice parent_obj;

    MemoryRegion mmio;
    qemu_irq irq[MAX_IRQ_NUM_PER_CHANNEL];
    
    struct MynetState *ms;

    int tap_fd;

    struct ring_node_t * tx_node_host;
    pthread_t thread_tx;
    pthread_mutex_t mutex_tx;
    pthread_cond_t cond_tx;


    struct ring_node_t * rx_node_host;
    pthread_t thread_rx;
    pthread_mutex_t mutex_rx;
    pthread_cond_t cond_rx;

    struct RegChannel reg;
};


typedef struct MynetStateChannel MynetStateChannel;
typedef struct ring_node_t ring_node_t;
typedef struct RegChannel RegChannel;
typedef struct MynetState MynetState;
typedef struct RegCommon RegCommon;
#endif