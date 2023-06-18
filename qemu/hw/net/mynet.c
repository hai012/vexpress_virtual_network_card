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


#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if.h>

#include "mynet_types.h"


static uint64_t mynet_common_readfn(void *opaque, hwaddr addr, unsigned size);
static void mynet_common_writefn(void *opaque, hwaddr addr,uint64_t value, unsigned size);
static void mynet_instance_init(Object *obj);
static void mynet_realize(DeviceState *dev, Error **errp);
static void mynet_class_init(ObjectClass *klass, void *data);
static void mynet_register_types(void);
void mynet_init(hwaddr base, qemu_irq *irq_table);

//*********************************************************************************************
static const TypeInfo mynet_info = {
    .name          = TYPE_MYNET,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_init = mynet_instance_init,
    .instance_size = sizeof(MynetState),
    .class_init    = mynet_class_init,
};



static const MemoryRegionOps mynet_common_mem_ops = {
    .read = mynet_common_readfn,
    .write = mynet_common_writefn,
    .valid.min_access_size = 1,
    .valid.max_access_size = 1,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

const char global_mac[6] = {
    0x11,0x11,0x11,0x11,0x11,0x11
};

//*************************************************************************************************
static uint64_t mynet_common_readfn(void *opaque, hwaddr addr, unsigned size)
{
    MynetState *ms = MYNET(opaque);
    return (uint64_t) (    *(  (uint32_t *)( (uint8_t *)&ms->reg + addr )  )  );
}

static void mynet_common_writefn(void *opaque, hwaddr addr,uint64_t value, unsigned size)
{
    MynetState *ms = MYNET(opaque);

    switch( addr ) {
        case 0:
        default:
            *( (uint8_t *)&ms->reg + addr) = (uint8_t)value;
            break;
    }
}
//************************************************************************************************
static void mynet_instance_init(Object *obj)
{
    printf("%s:start\n",__func__);
    MynetState  *ms  = MYNET(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    
    //common
    memset(&ms->reg,0,sizeof(RegCommon));
    memcpy(&(ms->reg.global_mac_addr), global_mac, 6);
    memory_region_init_io(&ms->mmio, OBJECT(ms), &mynet_common_mem_ops, ms,"mynet-mmio", sizeof(RegCommon));
    sysbus_init_mmio(sbd, &ms->mmio);


    for(int i=0;i<MAX_CHANNEL_NUM;++i) {
        MynetStateChannel *msc = MYNET_CHANNEL(qdev_new(TYPE_MYNET_CHANNEL));
        ms->channels[i] = msc;
        msc->ms = ms;
        msc->num=i;
    }
    system("ifconfig tap0 hw ether a6:28:24:ef:20:76");
    system("ip addr add 192.168.0.1/24 dev tap0");
    //system("arp -s  192.168.0.33   52:54:00:12:34:33");
    system("ip link set dev tap0 up");
}

static void mynet_realize(DeviceState *dev, Error **errp)
{
    MynetState *ms = MYNET(dev);
    for(int i=0;i<MAX_CHANNEL_NUM;++i)
        sysbus_realize(SYS_BUS_DEVICE(ms->channels[i]), NULL);//realize
}

static void mynet_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    dc->realize = mynet_realize;
}


static void mynet_register_types(void)
{
    type_register_static(&mynet_info);
}
type_init(mynet_register_types)


//we can use  pic[16] ~ pic[39]
//MAX_IRQ_NUM <= 39 - 16 +1
void mynet_init(hwaddr base, qemu_irq *pic)
{
    hwaddr install_base = base;

    DeviceState  *dev = qdev_new(TYPE_MYNET);//instance_init
    SysBusDevice *sbd = SYS_BUS_DEVICE(dev);
    MynetState   *ms  = MYNET(dev);

    sysbus_realize(sbd, NULL);//realize

    printf("common_base:0x%lx size:0x%lx\n", install_base,sizeof(RegCommon));
    sysbus_mmio_map(sbd, 0, install_base);
    install_base += sizeof(RegCommon) - sizeof(RegCommon)%4  +  4;//common align
    hwaddr channel_align_size = sizeof(struct RegChannel) - sizeof(struct RegChannel)%4 + 4;//channel align
    for(int i=0;i<MAX_CHANNEL_NUM;++i)//MAX_CHANNEL_NUM channels
    {
        printf("channel[%d]_base:0x%lx size=0x%lx\n",i, install_base, sizeof(struct RegChannel));
        sysbus_mmio_map(SYS_BUS_DEVICE(ms->channels[i]), 0, install_base);
        install_base += channel_align_size;
    }


    //ms->channels[i].irq[j] = gic_SPI i*MAX_IRQ_NUM_PER_CHANNEL+j + 16 = linux hwirq i*MAX_IRQ_NUM_PER_CHANNEL+j+16+32
    for(int i=0;i<MAX_CHANNEL_NUM;++i)
        for(int j=0;j<MAX_IRQ_NUM_PER_CHANNEL;++j)
            sysbus_connect_irq(SYS_BUS_DEVICE(ms->channels[i]), j, pic[16 + i*MAX_IRQ_NUM_PER_CHANNEL+j]);
}