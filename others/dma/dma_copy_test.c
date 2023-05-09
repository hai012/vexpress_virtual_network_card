#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>


#include <linux/cdev.h>

#include <linux/netdevice.h>


#define print_error(fmt, args...) printk(KERN_ERR  "[%s]: %s() line: %d " fmt, __FILE__, __FUNCTION__, __LINE__, ##args)
#define print_info(fmt, args...)  printk(KERN_INFO "[%s]: %s() line: %d " fmt, __FILE__, __FUNCTION__, __LINE__, ##args)


#define MAJOR_BASE 0
#define MINOR_COUNT 1

#define BUFFER_SIZE 4096

struct class *dct_class;
struct device *dct_device;

struct cdev *dct_cdev;
dev_t dct_dev;


struct dma_chan *chan;

struct completion transfer_ok;

char *rx_data, *tx_data;
dma_addr_t dma_src_addr;
dma_addr_t dma_dst_addr;

dma_cookie_t cookie;

static const struct file_operations dct_fops[] = {
	 {
		.owner      = THIS_MODULE,

	},
};



struct net_device    * virt_netdev;
static void dma_callback(void *ptr)
{
    //struct dma_tx_state	state;
    //dmaengine_tx_status(chan,cookie, &state);
    dma_unmap_single(chan->device->dev,dma_src_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);
    dma_unmap_single(chan->device->dev,dma_dst_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);
    //dma_unmap_single(chan->device->dev,dma_src_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);
    //dma_unmap_single(chan->device->dev,dma_dst_addr,BUFFER_SIZE, DMA_MEM_TO_MEM);

    if(strncmp(rx_data,tx_data,sizeof("test"))==0)
        pr_err("test equal");
    else
        pr_err("dma test unequal");
    pr_err("dma_callback end");
    complete(&transfer_ok);
    /* 通过rx_data和tx_data虚拟地址处理缓冲区*/
    return;
}

void dtc_init(void){
    virt_netdev = alloc_netdev_mqs(0, "virt_net_a", NET_NAME_UNKNOWN, ether_setup, 1, 1);

    


    dma_cap_mask_t dma_cap_mask;
    struct dma_slave_config dma_cfg = {0};
    struct dma_async_tx_descriptor *tx_descriptor;

/////////////////////////dma_request_channel//////////////////////
    dma_cap_zero(dma_cap_mask);
    dma_cap_set(DMA_MEMCPY, dma_cap_mask);
    chan = dma_request_channel(dma_cap_mask,NULL, NULL);
    if (!chan) {
        pr_err("dma_request_channel failed");
        return;
    }

/////////////////////////dmaengine_slave_config//////////////////////
    /*  enum dma_transfer_direction {
            DMA_MEM_TO_MEM,
            DMA_MEM_TO_DEV, 
            DMA_DEV_TO_MEM, 
            DMA_DEV_TO_DEV, 
        }; */
    dma_cfg.direction = DMA_MEM_TO_MEM;

    /*  src_addr：所要读取（RX）DMA从设备数据的缓
    冲器的物理地址（实际上是总线地址）。如果源是内
    存，则此元素将被忽略。*/
    //dma_cfg.src_addr = dma_src_addr

    /*dst_addr: 是所写入（TX）DMA从设备数据的缓冲区的物理
    地址（实际上是总线地址），如果源是内存，则该元素将被忽略。*/
    //dma_cfg.dst_addr =  dma_dst_addr

    /*src_addr_width是所读取DMA数据（RX）的源寄存器的
    字节宽度。如果源是内存，则根据架构不同，这可能会被忽略。
    enum dma_slave_buswidth {
        DMA_SLAVE_BUSWIDTH_UNDEFINED = 0,
        DMA_SLAVE_BUSWIDTH_1_BYTE = 1,
        DMA_SLAVE_BUSWIDTH_2_BYTES = 2,
        DMA_SLAVE_BUSWIDTH_3_BYTES = 3,
        DMA_SLAVE_BUSWIDTH_4_BYTES = 4,
        DMA_SLAVE_BUSWIDTH_8_BYTES = 8,
        DMA_SLAVE_BUSWIDTH_16_BYTES = 16,
        DMA_SLAVE_BUSWIDTH_32_BYTES = 32,
        DMA_SLAVE_BUSWIDTH_64_BYTES = 64,
    };*/
    dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_64_BYTES;

    /* dst_addr_width与src_addr_width类似，但是用于dst TX */
    dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_64_BYTES;

    /*src_maxburs：一次突发中可以发送到设备的最大
    字数（这里，将字作为src_addr_width成员的单位，而
    不是字节）。通常情况下，这是I/O外设FIFO大小的一
    半，不会使其溢出。这可能适用于内存源，也可能不适用*/
    //dma_cfg.dst_maxburst =

     /* src_maxburst与src_maxburs类似，但是用于dst TX */
    //dma_cfg.src_maxburst =
    if(dmaengine_slave_config(chan, &dma_cfg)) {
        pr_err("dmaengine_slave_config failed");
        return;
    }

//////////////////////////kzalloc////////////////////////////////////////////////////
    rx_data = kzalloc(BUFFER_SIZE,GFP_DMA);
    if(!rx_data) {
        pr_err("kzalloc rx_data failed");
        return;
    }
    tx_data = kzalloc(BUFFER_SIZE,GFP_DMA);
    if(!tx_data) {
        pr_err("kzalloc tx_data failed");
        return;
    }

////////////////////fill data/////////////////////////////
    memcpy(tx_data,"test",sizeof("test"));


    pr_err("dma_mask:::");
    pr_err("virt_netdev:::%llx",     virt_netdev->dev.dma_mask);
    //pr_err("virt_netdev:::%llx",     virt_netdev->dev.dma_ops);
    pr_err("chan:::%llx",chan->device->dev->dma_mask);
    //pr_err("chan:::%llx",chan->device->dev->dma_ops);
    pr_err("dma_maskend:::");
    pr_err("dma_maskend:::");
    //return ;
//////////////////////dma_map_single///////////////
    dma_src_addr = dma_map_single(chan->device->dev, tx_data,BUFFER_SIZE, DMA_MEM_TO_MEM);
    if(!dma_src_addr) {
        pr_err("dma_map_single dma_src_addr failed");
        return;
    }
    dma_dst_addr = dma_map_single(chan->device->dev, rx_data,BUFFER_SIZE, DMA_MEM_TO_MEM);
    if(!dma_dst_addr) {
        pr_err("dma_map_single dma_dst_addr failed");
        return;
    }

/////////////////////dmaengine_prep_dma_memcpy////////////////////
    tx_descriptor = dmaengine_prep_dma_memcpy(chan,dma_dst_addr,dma_src_addr, BUFFER_SIZE, 0);
    if (!tx_descriptor) {
        pr_err("Failed to prepare DMA transfer\n");
        return;
        /* dma_unmap_* the buffer */
    }
/////////////////fill callback/////////////////////////////////
    init_completion(&transfer_ok);
    tx_descriptor->callback = dma_callback;



//////////////////dmaengine_submit///////////////////////////////////
    cookie = dmaengine_submit(tx_descriptor);
    if (dma_submit_error(cookie)) {
        pr_err("%s: Failed to start DMA transfer\n", __FUNCTION__);
        return;
    }

/////////////////dma_async_issue_pending/////////////////
    dma_async_issue_pending(chan);
    pr_err("start wait_for_completion");
    wait_for_completion(&transfer_ok);
    pr_err("end wait_for_completion");
    pr_err("end wait_for_completion");
}















static int __init dma_init(void) {
    dtc_init();
    return 0;
    /*if(dtc_init())
        goto out_return;*/

    //alloc_chrdev_region返回的int值等于0成功，小于0为错误编码
    if(alloc_chrdev_region(&dct_dev, MAJOR_BASE, MINOR_COUNT, "dct_chrdev")){
        pr_err("failed to alloc_chrdev_region\n");
        goto out_return;
    }

    //cdev_alloc返回有效指针成功，返回NULL失败
    dct_cdev = cdev_alloc();
    if(NULL == dct_cdev){
        pr_err("failed to alloc cdev\n");
        goto out_unregister_chrdev_region;
    }

    dct_cdev->ops = dct_fops;
    dct_cdev->owner = THIS_MODULE;

    //cdev_add返回的int值等于0成功，小于0为错误编码
    if(cdev_add(dct_cdev, dct_dev, MINOR_COUNT)){
        pr_err("failed to add cdev\n");
        goto out_cdev_del;
    }
    
    dct_class = class_create(THIS_MODULE, "dct_class");
    //class_create返回有效指针为成功，返回错误指针失败。
    if(IS_ERR(dct_class)) {
        pr_err("failed to create class\n");
        goto out_cdev_del;
    }


    dct_device = device_create(dct_class, NULL, dct_dev, NULL, "dct%d", 0);
    //device_create返回有效指针为成功，返回错误指针失败。
    if(IS_ERR(dct_device)) {
        pr_err("failed to create device\n");
        goto out_class_destroy;
    }
	return 0;
//如果成功调用cdev_alloc、cdev_init或cdev_add，则后续释放时需要使用cdev_del。cdev_init返回void，调用cdev_init一定成功。
out_class_destroy:
	class_destroy(dct_class);
out_cdev_del:
	cdev_del(dct_cdev);
out_unregister_chrdev_region:
	unregister_chrdev_region(dct_dev, MINOR_COUNT);
out_return:
	return -1;
}

static void __exit dma_exit(void) {
if(tx_data)
    kfree(tx_data);
if(rx_data)
    kfree(rx_data);
if(chan)
    dma_release_channel(chan);
    pr_err("End of the dma_exit\n");      
}
module_init(dma_init);
module_exit(dma_exit);
MODULE_LICENSE ("GPL");
