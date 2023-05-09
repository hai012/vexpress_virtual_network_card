#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>


#include <linux/cdev.h>



#include "common.h"

#define BUFFER_SIZE 1500

char *VIRT_NETDEV_RX_FIFO_A;
char *VIRT_NETDEV_TX_FIFO_A;
char *VIRT_NETDEV_RX_FIFO_B;
char *VIRT_NETDEV_TX_FIFO_B;



struct transfer_t {
    struct dma_chan *chan;
    struct completion transfer_ok;
    struct dma_async_tx_descriptor *tx_descriptor;
    dma_cookie_t cookie;
    struct ring_node_t *ring_node_tx;
    struct ring_node_t *ring_node_rx;
    void (*tx_irq_fn)(void);
    void (*rx_irq_fn)(void);
} 

static struct transfer_t a2b = {0};
static struct transfer_t b2a = {0};

static void dma_callback(void *data)
{
    struct transfer_t *x2y = (struct transfer_t *)data;
    complete(x2y->transfer_ok);
    x2y->tx_irq_fn();
    x2y->rx_irq_fn();
    return;
}

int copy_thread(void *data)
{
    struct transfer_t *x2y = (struct transfer_t *)data;
    init_completion(&x2y->transfer_ok);
    for(;;) {
        wait_for_completion(x2y->ring_node_tx->allow_to_transfer);
        wait_for_completion(x2y->ring_node_rx->allow_to_transfer);
        tx_descriptor = dmaengine_prep_dma_memcpy(  x2y->chan,
                                                    x2y->ring_node_tx->dma_dst_addr,
                                                    x2y->ring_node_tx->dma_src_addr,
                                                    BUFFER_SIZE,
                                                    0);
        if (!x2y->tx_descriptor) {
            pr_err("Failed to prepare DMA transfer\n");
            continue;
        }

        
        x2y->tx_descriptor->callback = dma_callback;
        x2y->tx_descriptor->callback_param = x2y;

        x2y->cookie = dmaengine_submit(x2y->tx_descriptor);
        if (dma_submit_error(x2y->cookie)) {
            pr_err("%s: Failed to start DMA transfer\n", __FUNCTION__);
            return;
        }

        dma_async_issue_pending(x2y->chan);
        wait_for_completion(&x2y->transfer_ok);
        x2y->ring_node_tx = x2y->ring_node_tx->next;
    }
}


void set_hw_reg_tx_bd(char which,struct ring_node_t *ring_node)
{
    if(which='a') {
        a2b.ring_node_tx = ring_node;
    }
    if(which='b') {
        b2a.ring_node_tx = ring_node;
    }
}
void set_hw_reg_rx_bd(char which,struct ring_node_t *ring_node)
{
    if(which='a') {
        b2a.ring_node_rx = ring_node;
    }
    if(which='b') {
        a2b.ring_node_rx = ring_node;
    }
}
void register_tx_irq(char which,void (*tx_irq_fn)(void)) 
{
    if(which='a') {
        a2b.tx_irq_fn = tx_irq_fn;
    }
    if(which='b') {
        b2a.tx_irq_fn = tx_irq_fn;
    }
}
void register_tx_irq(char which,void (*rx_irq_fn)(void)) 
{
    if(which='a') {
        a2b.rx_irq_fn = rx_irq_fn;
    }
    if(which='b') {
        b2a.rx_irq_fn = rx_irq_fn;
    }
}

void set_hw_reg_enable_transfer()
{
    if(a2b.ring_node_tx && a2b.ring_node_rx) {
        if(kthread_create(copy_thread, &a2b,"virt_hw_a2b")) {
            pr_err("kthread_create virt_hw_a2b failed");
        }
    }
    if(b2a.ring_node_tx && b2a.ring_node_rx) {
        if(kthread_create(copy_thread, &a2b,"virt_hw_b2a")) {
            pr_err("kthread_create virt_hw_b2a failed");
        }
    }
}




static int  virt_netdev_hw_init_chan(struct transfer_t *x2y) {
    //    dma_init();
    
        dma_cap_mask_t dma_cap_mask;
        dma_cap_zero(dma_cap_mask);
        dma_cap_set(DMA_MEMCPY, dma_cap_mask);
        x2y->chan = dma_request_channel(dma_cap_mask,NULL, NULL);
        if (!priv->chan) {
            pr_err("dma_request_channel failed for %s",priv->netdev->name);
            return;
        }

        struct dma_slave_config dma_cfg = {0};
        dma_cfg.direction = DMA_MEM_TO_MEM;
        dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_64_BYTES;
        dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_64_BYTES;
        dma_cfg.dst_maxburst = 4096;
        dma_cfg.src_maxburst = 4096;
        if(dmaengine_slave_config(x2y->chan, &dma_cfg)) {
            pr_err("dmaengine_slave_config failed");
            return;
        }
}
static int __init virt_netdev_hw_init(void) {
    virt_netdev_hw_init_chan(&a2b);
    virt_netdev_hw_init_chan(&b22);
}
static void __exit virt_netdev_hw_exit(void) {

}
module_init(virt_netdev_hw_init);
module_exit(virt_netdev_hw_exit);
MODULE_LICENSE ("GPL");
