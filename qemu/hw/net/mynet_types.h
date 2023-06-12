#ifndef __MYNET_TYPES_H
#define __MYNET_TYPES_H

#include "exec/cpu-common.h"
#include "exec/address-spaces.h"
#include "hw/sysbus.h"
#include "exec/memattrs.h"

#define TYPE_MYNET "mynet"
#define MYNET(obj) OBJECT_CHECK(MynetState, (obj), TYPE_MYNET)
#define TYPE_MYNET_CHANNEL "mynet_channel"
#define MYNET_CHANNEL(obj) OBJECT_CHECK(MynetStateChannel, (obj), TYPE_MYNET_CHANNEL)




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


#define MAX_SKB_FRAGS 17
#define NODE_F_BELONG (1<<0)
#define NODE_F_TRANSFER (1<<1)

struct ring_node_t {
    //flag bit0 = 1,belone to eth card,     bit0==0,belone to driver.
    //flag bit1 = 1,transfer imidiately, bit1 = 0, transfer together with the next.
    uint32_t flag;
    uint32_t base;
    uint32_t len;
    uint32_t next;
};





struct MynetStateChannel {
    SysBusDevice parent_obj;

    MemoryRegion mmio;
    qemu_irq irq[MAX_IRQ_NUM_PER_CHANNEL];
    
    struct MynetState *ms;

    int tap_fd;


    pthread_t thread_tx;
    pthread_mutex_t mutex_tx;
    pthread_cond_t cond_tx;


    pthread_t thread_rx;
    pthread_mutex_t mutex_rx;
    pthread_cond_t cond_rx;
    int num;
    struct RegChannel reg;
};


typedef struct MynetStateChannel MynetStateChannel;
typedef struct ring_node_t ring_node_t;
typedef struct RegChannel RegChannel;
typedef struct MynetState MynetState;
typedef struct RegCommon RegCommon;



static inline MemTxResult read_guest_phy_addr(hwaddr addr,void *buf, hwaddr len)
{
    return address_space_read_full(&address_space_memory, addr, MEMTXATTRS_UNSPECIFIED, buf, len);
}
static inline MemTxResult write_guest_phy_addr(hwaddr addr,void *buf, hwaddr len)
{
    return address_space_write(&address_space_memory, addr, MEMTXATTRS_UNSPECIFIED, buf, len);
}



/*
3123  void *cpu_physical_memory_map(hwaddr addr,
3124                                hwaddr *plen,
3125                                bool is_write)

3131  void cpu_physical_memory_unmap(void *buffer, hwaddr len,
3132                                 bool is_write, hwaddr access_len)

2808  void cpu_physical_memory_rw(hwaddr addr, void *buf,
2809                              hwaddr len, bool is_write)
*/








#endif
