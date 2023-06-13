

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




static int tap_write(int fd,struct ring_node_t *node_table,uint32_t frag_count);
static void *pthread_fn_tx(void *ptr);
static ssize_t tap_read(int fd,struct ring_node_t *ring_node_ptr);
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

static int tap_write(int fd,struct ring_node_t *node_table,uint32_t frag_count)
{
    struct iovec  iov[MAX_SKB_FRAGS];
    ssize_t all_len=0,ret;
    hwaddr frag_len;

    for(int index=0; index<frag_count; ++index) {
        frag_len = node_table[index].len;
        iov[index].iov_base = cpu_physical_memory_map(node_table[index].base,&frag_len,0);
        if(!iov[index].iov_base){
            printf("QEMU:TX:parse tap_write iov_base failed, guest phy addr=0x%08x,len=0x%08x\n",node_table[index].base,node_table[index].len);
            return -1;
        }
        if(frag_len != node_table[index].len) {
            printf("QEMU:TX:cpu_physical_memory_map modify frag_len\n");
            return -1;
        }
        printf("QEMU:TX:FRAG:");
        for(int i=0;i<node_table[index].len;++i) {
            printf(" 0x%02hhx", *((char*)iov[index].iov_base + i) );
        }
        printf("\n");
        iov[index].iov_len = (size_t)node_table[index].len;
        all_len += node_table[index].len;
    }
    ret = writev(fd, iov, frag_count);
    for(int index=0; index<frag_count; ++index) {
        cpu_physical_memory_unmap(iov[index].iov_base, node_table[index].len,0,node_table[index].len);
    }
    if(ret != all_len) {
        printf("QEMU:TX:write failed,reason=%s,ret=%ld,count=%ld\n",strerror(errno),ret,all_len);
        return -1;
    }
    return 0;
}

static void *pthread_fn_tx(void *ptr)
{
    MynetStateChannel *msc = ptr;
    struct ring_node_t node_table[MAX_SKB_FRAGS];
    uint32_t node_table_guest[MAX_SKB_FRAGS];
    int frag_index;

    for(;;) {
        pthread_mutex_lock(&msc->mutex_tx);
        while(!msc->reg.tx_ctl_status)
            pthread_cond_wait(&msc->cond_tx, &msc->mutex_tx);
        pthread_mutex_unlock(&msc->mutex_tx);

        printf("QEMU:tx a skb:tx_ring_node_base=0x%08x\n",msc->reg.tx_ring_base);
        for(frag_index=0; frag_index<MAX_SKB_FRAGS; ++frag_index) {
            node_table_guest[frag_index] = msc->reg.tx_ring_base;
            if(read_guest_phy_addr(msc->reg.tx_ring_base,&node_table[frag_index],sizeof(struct ring_node_t))) {
                printf("QEMU:TX:read ring_node failed,guest addr=0x%08x\n",msc->reg.tx_ring_base);
                TX_FLAG_MODIFY(CTL_FLAG_STOP);
                TX_IF_NEED_IRQ(IRQF_TX_ERR);
                break;
            }
            printf("flag=0x%08x base=0x%08x len=0x%08x next=0x%08x\n",node_table[frag_index].flag,node_table[frag_index].base,node_table[frag_index].len,node_table[frag_index].next);

            if(!(node_table[frag_index].flag & NODE_F_BELONG)) {
                if(frag_index) {
                    printf("QEMU:TX:ring format err,flag bit0 == 0, belong to driver, but frag_index=%d\n",frag_index);
                    TX_FLAG_MODIFY(CTL_FLAG_STOP);
                    TX_IF_NEED_IRQ(IRQF_TX_ERR);
                    break;
                }
                printf("QEMU:TX:flag bit0 == 0, belong to driver, tx ring buffer empty\n");
                TX_FLAG_MODIFY(CTL_FLAG_STOP);
                TX_IF_NEED_IRQ(IRQF_TX_EMPTY);
                break;
            }

            

            if(node_table[frag_index].flag & NODE_F_TRANSFER) {
                if(tap_write(msc->tap_fd,node_table,frag_index+1)) {
                    printf("QEMU:TX:tap_write failed\n");
                    TX_FLAG_MODIFY(CTL_FLAG_STOP);
                    TX_IF_NEED_IRQ(IRQF_TX_ERR);
                    break;
                }

                printf("QEMU:send sucess, set ring_node_flag bit0==0,belongs to driver\n");
                for(int mark_index=frag_index; mark_index>=0; --mark_index) {
                    node_table[mark_index].flag &= ~NODE_F_BELONG;
                    if(write_guest_phy_addr(node_table_guest[mark_index],&node_table[mark_index].flag,4)) {
                        printf("QEMU:TX:write FLAG failed,guest addr=0x%08x\n",node_table_guest[mark_index]);
                        TX_FLAG_MODIFY(CTL_FLAG_STOP);
                        TX_IF_NEED_IRQ(IRQF_TX_ERR);
                    }
                }
                TX_IF_NEED_IRQ(IRQF_TX_SEND);
                msc->reg.tx_ring_base = node_table[frag_index].next;//handle next frag which belong a new skb
                break;//check tx_ctl_status before send the next skb
            }
            msc->reg.tx_ring_base = node_table[frag_index].next;//handle next frag which belong a same skb
        }
        if(frag_index == MAX_SKB_FRAGS) {
            printf("QEMU:TX:formant err, frags is too many in a skb\n");
            TX_FLAG_MODIFY(CTL_FLAG_STOP);
            TX_IF_NEED_IRQ(IRQF_TX_ERR);
        }
    }
    return NULL;
}

static ssize_t tap_read(int fd,struct ring_node_t *ring_node_ptr)
{
    ssize_t buf_len=0,ret;
    void *buf;
    hwaddr frag_len = ring_node_ptr->len;
    buf = cpu_physical_memory_map(ring_node_ptr->base,&frag_len,1);
    if(!buf) {
        printf("QEMU:RX:parse tap_write iov_base failed, guest phy addr=0x%08x,len=0x%08x\n",ring_node_ptr->base,ring_node_ptr->len);
        return -1;
    }
    if(frag_len != ring_node_ptr->len) {
        printf("QEMU:RX:cpu_physical_memory_map modify frag_len\n");
        return -1;
    }
    buf_len = ring_node_ptr->len;

    ret = read(fd, buf, buf_len);

    cpu_physical_memory_unmap(buf, ring_node_ptr->len,1,ring_node_ptr->len);

    if(ret <= 0) {
        printf("QEMU:RX:fail to readv,reason=%s,ret=%ld\n",strerror(errno),ret);
        return -1;
    }
    return ret;
}
static void *pthread_fn_rx(void *ptr)
{
    MynetStateChannel *msc = ptr;
    struct ring_node_t ring_node;
    ssize_t ret;
    for(;;){
        pthread_mutex_lock(&msc->mutex_rx);
        while(!msc->reg.rx_ctl_status)
            pthread_cond_wait(&msc->cond_rx, &msc->mutex_rx);
        pthread_mutex_unlock(&msc->mutex_rx);

        //printf("QEMU:start rx:%p\n",msc->rx_node_host);
        if(read_guest_phy_addr(msc->reg.rx_ring_base,&ring_node,sizeof(struct ring_node_t))) {
            printf("QEMU:RX:read ring_node failed,guest addr=0x%08x\n",msc->reg.rx_ring_base);
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
            RX_IF_NEED_IRQ(IRQF_RX_ERR);
            continue;
        }
        if(!(ring_node.flag & NODE_F_BELONG)) {
            printf("QEMU:RX:flag bit0== 0, belong to driver, rx ring buffer full\n");
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
            RX_IF_NEED_IRQ(IRQF_RX_FULL);
            continue;
        }

        ret = tap_read(msc->tap_fd, &ring_node);
        if(ret <= 0) {
            printf("QEMU:RX:tap_read failed\n");
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
            RX_IF_NEED_IRQ(IRQF_RX_ERR);
            continue;
        }
        //recv sucess, record length
        ring_node.len = ret;
        if(write_guest_phy_addr(msc->reg.rx_ring_base + 8,&ring_node.len,4)) {
            printf("QEMU:RX:write LEN failed,guest addr=0x%08x\n",msc->reg.rx_ring_base+8);
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
            RX_IF_NEED_IRQ(IRQF_RX_ERR);
        }
        //set ring_node_flag bit0==0, belongs to driver
        ring_node.flag &= ~NODE_F_BELONG;
        if(write_guest_phy_addr(msc->reg.rx_ring_base,&ring_node.flag,4)) {
            printf("QEMU:RX:write FLAG failed,guest addr=0x%08x\n",msc->reg.rx_ring_base);
            RX_FLAG_MODIFY(CTL_FLAG_STOP);
            RX_IF_NEED_IRQ(IRQF_RX_ERR);
        }
        RX_IF_NEED_IRQ(IRQF_RX_RECV);
        msc->reg.rx_ring_base = ring_node.next;//handle the next skb
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
        msc->reg.tx_irq_flag = (uint32_t) value & ALL_IRQF_TX;
        printf("QEMU:set IRQ flag,reg=0x%08x\n",msc->reg.tx_irq_flag);
        if( !(msc->reg.tx_irq_flag & msc->reg.tx_irq_mask)) {
            printf("QEMU:set flag,clear tx irq,tx_irq_flag=0x%08x,tx_irq_mask=0x%08x\n",   msc->reg.tx_irq_flag,   msc->reg.tx_irq_mask);
            qemu_set_irq(msc->irq[CHANNEL_IRQ_TX], 0);
        }
        break;
    case 0x0c://irq mask reg, 0 musk , 1 not musk
		msc->reg.tx_irq_mask = (uint32_t)value & ALL_IRQF_TX;
        printf("QEMU:set IRQ mask,reg=0x%08x\n",msc->reg.tx_irq_mask);
        if( !(msc->reg.tx_irq_flag & msc->reg.tx_irq_mask)) {
            printf("QEMU:set IRQ mask,clear tx irq,tx_irq_flag=0x%08x,tx_irq_mask=0x%08x\n",msc->reg.tx_irq_flag,msc->reg.tx_irq_mask);
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

