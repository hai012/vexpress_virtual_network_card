

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
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/uio.h>


#include "mynet_types.h"




static int tap_write(struct MynetStateChannel *msc);
static void *pthread_fn_tx(void *ptr);
static int tap_read(struct MynetStateChannel *msc);
static void *pthread_fn_rx(void *ptr);
static void mynet_channel_writefn(void *opaque, hwaddr addr, uint64_t value, unsigned size);
static uint64_t mynet_channel_readfn(void *opaque, hwaddr addr, unsigned size);
static int open_tap(void);
static void mynet_channel_instance_init(Object *obj);
static void mynet_channel_register_types(void);


/*#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
void print_stacktrace()
{
    int size = 16;
    void * array[size];
    int stack_num = backtrace(array, size);
    char ** stacktrace = backtrace_symbols(array, stack_num);
    for (int i = 0; i < stack_num; ++i)
    {
        printf("%s\n", stacktrace[i]);
    }
    free(stacktrace);
}*/



#define CTL_FLAG_START 1
#define CTL_FLAG_STOP  0

#define TX_FLAG_MODIFY(CTL_FLAG)  do {                         \
  while(pthread_mutex_trylock(&msc->mutex_tx));               \
  msc->reg.tx_ctl_status = CTL_FLAG;                            \
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
            qemu_set_irq(msc->irq[CHANNEL_IRQ_TX], 1);\
            qemu_mutex_unlock_iothread();\
    }\
} while(0)
#define RX_IF_NEED_IRQ(X)  do {\
    msc->reg.rx_irq_flag |= (X);\
    if(msc->reg.rx_irq_mask & (X)) {\
        qemu_mutex_lock_iothread();\
        /*printf("QEMU:RX IRQ:0x%04x 0x%04x 0x%04x\n",msc->reg.rx_irq_mask,msc->reg.rx_irq_flag, X);*/\
        qemu_set_irq(msc->irq[CHANNEL_IRQ_RX], 1);\
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

static int tap_write(int fd,struct ring_node_t *node_table,uini32_t frag_count)
{
    struct ring_node_t * node = msc->tx_node_host;
    struct ring_node_t *node_table[MAX_SKB_FRAGS];
    struct iovec  iov[MAX_SKB_FRAGS];
    ssize_t all_len=0;

    for(int index=0; index<frag_count; ++index) {
        iov[index].iov_base = cpu_physical_memory_map(node_table[index]->base,node_table[index]->len,0);
        if(!iov[index].iov_base){
            printf("QEMU:channel_%d, parse tap_write iov_base failed, guest phy addr=0x%08x,len=0x%08x\n",msc->num,node_table[index]->base,node_table[index]->len);
            return -1;
        }
        iov[index].iov_len = (size_t)node_table[index]->len;
        all_len += node_table[index]->len;
    }
    ssize_t ret = writev(msc->tap_fd, iov, frag_count);
    for(int index=0; index<frag_count; ++index) {
        cpu_physical_memory_unmap(node_table[index]->base, node_table[index]->len,0,node_table[index]->len);
    }
    if(ret <= 0 || ret != all_len) {
        printf("QEMU:write failed,reason=%s,ret=%ld,count=%ld\n",strerror(errno),ret,all_len);
        return -1;
    }
}

static void *pthread_fn_tx(void *ptr)
{
    MynetStateChannel *msc = ptr;
    struct ring_node_t node_table[MAX_SKB_FRAGS];

    for(;;) {
        pthread_mutex_lock(&msc->mutex_tx);
        while(!msc->reg.tx_ctl_status)
            pthread_cond_wait(&msc->cond_tx, &msc->mutex_tx);
        pthread_mutex_unlock(&msc->mutex_tx);
        //printf("QEMU:start tx skb:%p\n",msc->tx_node_host);

        for(int frag_index=0; frag_index<MAX_SKB_FRAGS; ++frag_index) {
            if(read_guest_phy_addr(msc->reg.tx_ring_base,&node_table[frag_index],sizeof(struct ring_node_t))) {
                printf("QEMU:fail to read ring_node from guest when TX ,msc->reg.tx_ring_base=0x%08x\n",msc->reg.tx_ring_base);
                TX_FLAG_MODIFY(CTL_FLAG_STOP);
                TX_IF_NEED_IRQ(IRQF_TX_ERR);
                break;
            }
            if(!(node_table[frag_index].flag & NODE_F_BELONG)) {
                if(frag_index) {
                    printf("QEMU:ring format err,flag & NODE_F_BELONG == 0, belong to driver, but frag_index=%d\n",frag_index);
                    TX_FLAG_MODIFY(CTL_FLAG_STOP);
                    TX_IF_NEED_IRQ(IRQF_TX_ERR);
                    break;
                }
                printf("QEMU:flag & NODE_F_BELONG == 0, belong to driver, tx ring buffer empty\n");
                TX_FLAG_MODIFY(CTL_FLAG_STOP);
                TX_IF_NEED_IRQ(IRQF_TX_EMPTY);
                break;
            }
            if(node_table[frag_index].flag & NODE_F_TRANSFER) {
                if(tap_write(msc->tap_fd,node_table,frag_count)) {
                    printf("QEMU:tap_write failed\n");
                    TX_FLAG_MODIFY(CTL_FLAG_STOP);
                    TX_IF_NEED_IRQ(IRQF_TX_ERR);
                    break;
                }
                //send sucess, ring_node_flag bit1==1, mark nodes belong to driver
                while(frag_index--) {
                    node_table[frag_index].flag |= NODE_F_BELONG;//,belong to driver
                    write_guest_phy_addr(msc->reg.tx_ring_base,&node_table[frag_index].flag,4);
                }
                TX_IF_NEED_IRQ(IRQF_TX_SEND);
                break;//check tx_ctl_status before send the next skb
            }
            msc->reg.tx_ring_base = node_table[frag_index].next;//next frag which belong a same skb
        }
    }
    return NULL;
}

static int tap_read(struct MynetStateChannel* msc)
{
    struct ring_node_t * node = msc->rx_node_host;
    int frag_index=0;
    struct ring_node_t *node_table[MAX_SKB_FRAGS];
    struct iovec  iov[MAX_SKB_FRAGS];

    for(int frag_index=0; frag_index<MAX_SKB_FRAGS; ++frag_index) {
        node_table[frag_index] = node;
        iov[frag_index].iov_base = guest_to_host(node->base);
        if(!iov[frag_index].iov_base){
            printf("QEMU:channel_%d, parse tap_read iov_base failed, guest phy addr=0x%08x\n",msc->num,node->base);
            return -1;
        }
        iov[frag_index].iov_len = (size_t)node->len;
        if(node->flag & NODE_F_TRANSFER) {
            break;
        }
        node = guest_to_host(node->next);
        if(!node || !(node->flag & NODE_F_BELONG)) {
            printf("QEMU:fail to get NODE_F_TRANSFER,and the next node is NULL or not belong to card\n");
            return -1;
        }
    }
    if(frag_index >= MAX_SKB_FRAGS) {
        printf("QEMU:frag count is large than  MAX_SKB_FRAGS\n");
        return -1;
    }

    ssize_t ret = readv(msc->tap_fd, iov, 1+frag_index);
    if(ret <= 0) {
        printf("QEMU:fail to readv,reason=%s,ret=%ld\n",strerror(errno),ret);
        return -1;
    }
    for(int i=frag_index;i>0;--i) {//the last frag to the first frag
        node_table[i]->flag &= ~NODE_F_BELONG;//belong to driver now
    }
    barrier();//smp_wmb()
    node_table[0]->flag &= ~NODE_F_BELONG;//belong to driver now
    msc->rx_node_host = guest_to_host(node->next);
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
        //printf("QEMU:start rx:%p\n",msc->rx_node_host);
        for(;;){
            if(!msc->rx_node_host) {
                printf("QEMU:msc->rx_node_host = NULL when recv\n");
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                RX_IF_NEED_IRQ(IRQF_RX_ERR);
                break;
            }
            if(!(msc->rx_node_host->flag & NODE_F_BELONG)) {
                printf("QEMU:flag & NODE_F_BELONG == 0, belong to driver, rx ring buffer full\n");
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                RX_IF_NEED_IRQ(IRQF_RX_FULL);
                break;
            }
            
            //printf("QEMU:tap_read\n");
            if(tap_read(msc)) {
                printf("QEMU:tap_read failed\n");
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                RX_IF_NEED_IRQ(IRQF_RX_ERR);
            }

            if(!msc->rx_node_host) {
                printf("QEMU: fail to map rx_node_host->next\n");
                RX_FLAG_MODIFY(CTL_FLAG_STOP);
                RX_IF_NEED_IRQ(IRQF_RX_ERR);
                continue;
            }

            if(msc->rx_node_host->flag & NODE_F_BELONG) {
                //flag_bit[0]= 1 belong to net card
                //printf("QEMU:recv continuely\n");
                RX_IF_NEED_IRQ(IRQF_RX_RECV);
                continue;//send a package completely and has space to  recv continuely
            }
            //printf("QEMU:don't have space to recv\n");
            RX_IF_NEED_IRQ(IRQF_RX_RECV|IRQF_RX_FULL);
            RX_FLAG_MODIFY(CTL_FLAG_STOP);//send a package completely and stop for don't have space to recv
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
            return;
        /*msc->tx_node_host = cpu_physical_memory_map(value,sizeof()
        if(!msc->tx_node_host && value) {
            printf("QEMU:channel_%d, parse tx_node_host failed, guest phy addr=0x%08lx\n",msc->num,value);
            return;
        }*/
        msc->reg.tx_ring_base = value;
        break;
    case 0x04://ctl reg
        if(value==1 && msc->reg.tx_ctl_status==0) {
            TX_FLAG_MODIFY(CTL_FLAG_START);
            pthread_cond_signal(&msc->cond_tx);
        }
        if(value==0 && msc->reg.tx_ctl_status==1) {
            TX_FLAG_MODIFY(CTL_FLAG_STOP);
        }
        break;
    case 0x08://irq flag reg
        //printf("CLEAR_SEND_IRQ\n");
        msc->reg.tx_irq_flag = (uint32_t) value & ALL_IRQF_TX;
        if( !(msc->reg.tx_irq_flag & msc->reg.tx_irq_mask)) {
            //printf("QEMU:set flag,clear tx irq,tx_irq_flag=0x%04x,tx_irq_mask=0x%04x\n",msc->reg.tx_irq_flag,msc->reg.tx_irq_mask);
            qemu_set_irq(msc->irq[CHANNEL_IRQ_TX], 0);
        }
        break;
    case 0x0c://irq mask reg, 0 musk , 1 not musk
		msc->reg.tx_irq_mask = (uint32_t)value & ALL_IRQF_TX;
        if( !(msc->reg.tx_irq_flag & msc->reg.tx_irq_mask)) {
            //printf("QEMU:set mask,clear tx irq,tx_irq_flag=0x%04x,tx_irq_mask=0x%04x\n",msc->reg.tx_irq_flag,msc->reg.tx_irq_mask);
            qemu_set_irq(msc->irq[CHANNEL_IRQ_TX], 0);
        }
        break;
/////////////////////////////////////////////////////////////////////////////////////
    case 0x10://rx ring phy base reg
        if(msc->reg.rx_ctl_status)
            return;
        /*msc->rx_node_host = guest_to_host(value);
        if(!msc->tx_node_host && value) {
            printf("QEMU:channel_%d, parse rx_node_host failed, guest phy addr=0x%08lx\n",msc->num,value);
            return;
        }*/
        msc->reg.rx_ring_base = value;
        break;
    case 0x14://ctl reg
        if(value==1 && msc->reg.rx_ctl_status==0) {
            RX_FLAG_MODIFY(CTL_FLAG_START);
            pthread_cond_signal(&msc->cond_rx);
        }
        /*if(value==0 && msc->reg.rx_ctl_status==1) {
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
        }*/
        break;
    case 0x18:
        msc->reg.rx_irq_flag = (uint32_t) value & ALL_IRQF_RX;
        if(!( msc->reg.rx_irq_flag & msc->reg.rx_irq_mask)) {//0 mask, 1 ummask
            //printf("QEMU:set flag,clear rx irq,rx_irq_flag=0x%04x,rx_irq_mask=0x%04x\n",msc->reg.rx_irq_flag,msc->reg.rx_irq_mask);
            qemu_set_irq(msc->irq[CHANNEL_IRQ_RX], 0);
        }
        break;
    case 0x1c://irq mask reg, low level works
		msc->reg.rx_irq_mask = (uint32_t)(value) & ALL_IRQF_RX;//MAX_IRQ_NUM_PER_CHANNEL_RX bits
        if( !(msc->reg.rx_irq_flag & msc->reg.rx_irq_mask)) {
            //printf("QEMU:set mask,clear rx irq,rx_irq_flag=0x%04x,rx_irq_mask=0x%04x\n",msc->reg.rx_irq_flag,msc->reg.rx_irq_mask);
            qemu_set_irq(msc->irq[CHANNEL_IRQ_RX], 0);
        }
        break;
    }
}



static uint64_t mynet_channel_readfn(void *opaque, hwaddr addr, unsigned size)
{
    MynetStateChannel *msc = MYNET_CHANNEL(opaque);
    return (uint64_t) (    *(  (uint32_t *)( (uint8_t *)&msc->reg + addr )  )  );
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
    ifr.ifr_flags = IFF_TAP|IFF_MULTI_QUEUE;
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

