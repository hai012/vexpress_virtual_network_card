#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>


#include <linux/cdev.h>





#define BUFFER_SIZE 1500

extern char *VIRT_NETDEV_RX_FIFO_A;
extern char *VIRT_NETDEV_RX_FIFO_B;
extern char *VIRT_NETDEV_TX_FIFO_B;
extern char *VIRT_NETDEV_TX_FIFO_A;

struct ring_node_t {
    struct completion allow_to_transfer;
    char * dma_src_addr;
    char * dma_dst_addr;
    struct ring_node_t *next;
}




