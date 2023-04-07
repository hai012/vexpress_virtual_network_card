

#include "hw/net/mynet.h"


#include "qemu/osdep.h"
#include "hw/sysbus.h"
#include "migration/vmstate.h"
#include "net/net.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qemu/main-loop.h"
#include "exec/address-spaces.h"
#include "qemu/typedefs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <pthread.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/uio.h>


#include "mynet_types.h"




static int tap_write(int fd,void *buffer,size_t allToSend);
static void *pthread_fn_tx(void *ptr);
static int tap_read(int fd,void *buffer,size_t *allToRecv);
static void *pthread_fn_rx(void *ptr);
static void mynet_channel_writefn(void *opaque, hwaddr addr, uint64_t value, unsigned size);
static uint64_t mynet_channel_readfn(void *opaque, hwaddr addr, unsigned size);
static int open_tap(void);
static void mynet_channel_instance_init(Object *obj);
static void mynet_channel_register_types(void);



#define CTL_FLAG_START 1
#define CTL_FLAG_STOP  0

#define TX_FLAG_MODIFY(CTL_FLAG)  do {                         \
  while(pthread_mutex_trylock(&msc->mutex_tx));               \
  msc->reg.tx_ctl_status = CTL_FLAG;                              \
  pthread_mutex_unlock(&msc->mutex_tx);                       \
} while(0)
#define RX_FLAG_MODIFY(CTL_FLAG)  do {                        \
  while(pthread_mutex_trylock(&msc->mutex_rx));               \
  msc->reg.rx_ctl_status = CTL_FLAG;                              \
  pthread_mutex_unlock(&msc->mutex_rx);                       \
} while(0)

#define TX_IF_NEED_IRQ(X)  do {\
    msc->reg.tx_irq_flag |= (X);\
    if(msc->reg.tx_irq_mask & (X)) {\
            qemu_mutex_lock_iothread();\
            qemu_set_irq(msc->irq[0], 1);\
            qemu_mutex_unlock_iothread();\
    }\
} while(0)
#define RX_IF_NEED_IRQ(X)  do {\
    msc->reg.rx_irq_flag |= (X);
    if(msc->reg.rx_irq_mask & (X)) {\
        qemu_mutex_lock_iothread();\
        qemu_set_irq(msc->irq[1], 1);\
        qemu_mutex_unlock_iothread();\
    }\
} while(0)




//**************************************************************************************

static const TypeInfo mynet_channel_info = {
    .name          = TYPE_MYNET_CHANNEL,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_init = mynet_channel_instance_init,
    .instance_size = sizeof(MynetStateChannel),
};
static const MemoryRegionOps mynet_channel_mem_ops = {
    .read = mynet_channel_readfn,
    .write = mynet_channel_writefn,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

//**************************************************************************************

static int tap_write(MynetStateChannel *msc)
{
    uint64_t count = msc->tx_node_host->frags_count;
    struct iovec * iov = malloc(count * sizeof(struct iovec);
    struct frag_t *base = guest_to_host(msc->tx_node_host->frags_addr);
    for(uint64_t i=0; i<count; ++i) {
        iov[i].iov_base = guest_to_host(base[i].buffer);
        iov[i].iov_len = (size_t)base[i].len;
    }
    ssize_t ret = writev(fd, iov, count);
    if(ret < 0) {
        return -1;
    }
    return 0;
}

static void *pthread_fn_tx(void *ptr)
{
    MynetStateChannel *msc = ptr;
    for(;;){
        pthread_mutex_lock(&msc->mutex_tx);
        while(!msc->reg.tx_ctl_status)
            pthread_cond_wait(&msc->cond_tx, &msc->mutex_tx);
        pthread_mutex_unlock(&msc->mutex_tx);

        //start tx
        if(!msc->tx_node_host){
            TX_IF_NEED_IRQ(IRQF_TX_ERR);
            TX_FLAG_MODIFY(CTL_FLAG_STOP);
            //printf("failed to write tap dev,tap erro or data erro\n");
            continue;
        }
        
        if(!msc->tx_node_host->flag) {
            TX_IF_NEED_IRQ(IRQF_TX_EMPTY);
            TX_FLAG_MODIFY(CTL_FLAG_STOP);
            //printf("failed to write tap dev,tap erro or data erro\n");
            continue;
        }

        if(tap_write(msc)){
            TX_IF_NEED_IRQ(IRQF_TX_ERR);
            TX_FLAG_MODIFY(CTL_FLAG_STOP);
            printf("tap_write failed\n");
            continue;
        }

        ring_node_t * tmp = msc->tx_node_host;
        msc->tx_node_host = guest_to_host(msc->tx_node_host->next);
        tmp->flag = 0;//mark this node belong to driver now

        if(!msc->tx_node_host){
            TX_IF_NEED_IRQ(IRQF_TX_ERR);
            TX_FLAG_MODIFY(CTL_FLAG_STOP);
            //printf("failed to write tap dev,tap erro or data erro\n");
            continue;
        }

        if(msc->tx_node_host->flag) {
		    TX_IF_NEED_IRQ(IRQF_TX_SEND);
            continue;//send a package completely and continue to send
        }
        TX_IF_NEED_IRQ(IRQF_TX_SEND|IRQF_TX_EMPTY);
        TX_FLAG_MODIFY(CTL_FLAG_STOP);//send a package completely and stop for nothing to send
        //printf("tx empty\n");
    }
    return NULL;
}

static int tap_read(int fd,void *buffer,size_t *allToRecv)
{

    ssize_t ret = read(fd, buffer, *allToRecv);
    if(ret < 0) {
        return -1;
    }
    *allToRecv = ret;
    printf("read:%ld\n", *allToRecv);
    return 0;

    uint64_t count = msc->rx_node_host->frags_count;
    struct iovec * iov = malloc(count * sizeof(struct iovec);
    struct frag_t *base = guest_to_host(msc->rx_node_host->frags_addr);
    for(uint64_t i=0; i<count; ++i) {
        iov[i].iov_base = guest_to_host(base[i].buffer);
        iov[i].iov_len = (size_t)base[i].len;
    }
    ssize_t ret = readv(fd, iov, count);
    if(ret < 0) {
        return -1;
    }
    return 0;

}
static void *pthread_fn_rx(void *ptr)
{
    MynetStateChannel *msc = ptr;
    for(;;){
        pthread_mutex_lock(&msc->mutex_rx);
        while(!msc->reg.rx_ctl_status)
            pthread_cond_wait(&msc->cond_rx, &msc->mutex_rx);
        pthread_mutex_unlock(&msc->mutex_rx);

        for(;;){
            if(!msc->rx_node_host) {
                printf("tx ring node base or format error\n");
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                RX_IF_NEED_IRQ(IRQ_RX_ERR);
                break;
            }
            if(msc->rx_node_host->flag) {
                //flag==1, rx ring buffer full
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                RX_IF_NEED_IRQ(IRQ_RX_FULL);
                break;
            }
            
            //start rx
            if(tap_read(msc)) {
                printf("tap_read failed\n");
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                RX_IF_NEED_IRQ(IRQ_RX_ERR);
            }

            ring_node_t * tmp = msc->tx_node_host;
            msc->tx_node_host = guest_to_host(msc->tx_node_host->next);
            tmp->flag = 0;//mark this node belong to driver now

            if(!msc->rx_node_host){
                RX_IF_NEED_IRQ(IRQF_RX_ERR);
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                //printf("failed to write tap dev,tap erro or data erro\n");
                continue;
            }

            if(msc->rx_node_host->flag) {
                RX_IF_NEED_IRQ(IRQF_RX_SEND);
                continue;//send a package completely and continue to recv
            }
            RX_IF_NEED_IRQ(IRQF_RX_SEND|IRQF_RX_FULL);
            RX_FLAG_MODIFY(CTL_FLAG_STOP);//send a package completely and stop for nothing to send
        }
    }
    return NULL;
}

//**************************************************************************************

static void mynet_channel_writefn(void *opaque, hwaddr addr,
                               uint64_t value, unsigned size)
{
    MynetStateChannel *msc = MYNET_CHANNEL(opaque);
    switch (addr) {
    case 0x00://tx ring phy base reg
        if(msc->reg.tx_ctl_status)
            return
        msc->tx_node_host = guest_to_host(value);
        msc->reg.tx_ring_base = value;
        break;
    case 0x04://ctl reg
        if(value==1 && msc->reg.tx_ctl_status==0) {
            if(msc->tx_node_host || msc->tx_node_host->flag) {
                TX_FLAG_MODIFY(CTL_FLAG_START);
                pthread_cond_signal(&msc->cond_tx);
            }
        }
        if(value==0 && msc->reg.tx_ctl_status==1) {
            TX_FLAG_MODIFY(CTL_FLAG_STOP);
        }
        break;
    case 0x08://irq flag reg
        for(int i=0;i<MAX_IRQ_NUM_PER_CHANNEL_TX;++i) {
            if( !(value&(1<<i)) && (msc->reg.tx_irq_flag&(1<<i)) ) {
                //printf("CLEAR_SEND_IRQ\n");
                qemu_set_irq(msc->irq[i], 0);
                msc->reg.tx_irq_flag &= ~(1<<i);//reset bit
            }
        }
        break;
    case 0x0c://irq mask reg, low level works
		msc->reg.tx_irq_mask = (uint32_t)(value) & 0x0003;//MAX_IRQ_NUM_PER_CHANNEL_TX bits
        break;
/////////////////////////////////////////////////////////////////////////////////////
    case 0x10://rx ring phy base reg
        if(msc->reg.rx_ctl_status)
            return;
        msc->rx_node_host = guest_to_host(value);
        msc->reg.rx_ring_base = value;
        break;
    case 0x14://ctl reg
        if(value==1 && msc->reg.rx_ctl_status==0) {
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
            pthread_cond_signal(&msc->cond_rx);
        }
        if(value==0 && msc->reg.rx_ctl_status==1) {
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
        }
        break;
    case 0x18:
        for(int i=0;i<MAX_IRQ_NUM_PER_CHANNEL_RX;++i) {
            if( !(value&(1<<i)) && (msc->reg.rx_irq_flag&(1<<i)) ) {
                //printf("CLEAR_SEND_IRQ\n");
                qemu_set_irq(msc->irq[i+MAX_IRQ_NUM_PER_CHANNEL_TX], 0);
                msc->reg.tx_irq_flag &= ~(1<<i);//reset bit
            }
        }
        break;
    case 0x1c://irq mask reg, low level works
		    msc->reg.rx_irq_mask = (uint32_t)(value) & 0x003;//MAX_IRQ_NUM_PER_CHANNEL_RX bits
        break;
    }
}



static uint64_t mynet_channel_readfn(void *opaque, hwaddr addr, unsigned size)
{
    MynetStateChannel *msc = MYNET_CHANNEL(opaque);
    return (uint64_t) (   *( (uint32_t *)&msc->reg + addr ) );
    return 0;
}


//**************************************************************************************
static int open_tap(void)
{
    struct ifreq ifr;
    int fd;
    fd = open("/dev/net/tun", O_RDWR);
    if (fd < 0) {
        printf("open /dev/net/tun failed,exit\n");
        exit(-1);
    }
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name,"tap0",IFNAMSIZ);
    ifr.ifr_flags = IFF_TAP|IFF_MULTI_QUEUE|IFF_NAPI_FRAGS;
    if(ioctl(fd, TUNSETIFF, (void *) &ifr) < 0) {
        printf("creat tap failed,exit\n");
        exit(-1);
    }

    /*const u32 offload = TUN_F_CSUM | TUN_F_TSO4 | TUN_F_TSO6 | TUN_F_TSO_ECN | TUN_F_UFO;
    if (ioctl(netdev->tun_fd, TUNSETOFFLOAD, offload)) {
        printf("set tap offload failed,exit\n");
        exit(-1);
    }*/
    return fd;
}

static void mynet_channel_instance_init(Object *obj)
{
    printf("%s:start\n",__func__);
    MynetStateChannel  *msc  = MYNET_CHANNEL(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    
    msc->tap_fd = open_tap();

    memset(&msc->reg, 0, sizeof(RegChannel));
    pthread_mutex_init(&msc->mutex_tx, NULL);
    pthread_cond_init(&msc->cond_tx, NULL);
    pthread_create(&msc->thread_tx, NULL,pthread_fn_tx, msc);
    pthread_mutex_init(&msc->mutex_rx, NULL);
    pthread_cond_init(&msc->cond_rx, NULL);
    pthread_create(&msc->thread_rx, NULL,pthread_fn_rx, msc);


    memory_region_init_io(&msc->mmio, OBJECT(msc), &mynet_channel_mem_ops, msc,"mynet-mmio", sizeof(RegChannel));
    sysbus_init_mmio(sbd, &msc->mmio);
    for(int j=0;j<MAX_IRQ_NUM_PER_CHANNEL;++j)
        sysbus_init_irq(sbd, &msc->irq[j]);
}

static void mynet_channel_register_types(void)
{
    type_register_static(&mynet_channel_info);
}

type_init(mynet_channel_register_types)

