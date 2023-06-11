#ifndef HW_NET_MYNET_H
#define HW_NET_MYNET_H

#include <stdint.h>
#include "exec/hwaddr.h"
#include "qemu/typedefs.h"
void mynet_init(hwaddr base,qemu_irq * pic);



#endif
