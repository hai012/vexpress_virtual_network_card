#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>


#include <linux/cdev.h>

#include <linux/netdevice.h>



#include <linux/kallsyms.h>




#include <linux/kthread.h>
#include <linux/delay.h>

#define print_error(fmt, args...) printk(KERN_ERR  "[%s]: %s() line: %d " fmt, __FILE__, __FUNCTION__, __LINE__, ##args)
#define print_info(fmt, args...)  printk(KERN_INFO "[%s]: %s() line: %d " fmt, __FILE__, __FUNCTION__, __LINE__, ##args)

void * get_ttbr0_el1(void);
void * get_ttbr1_el1(void);
static int threadfn(void *data) {
	while(!kthread_should_stop()) {
	pr_err("ttbr0_el1: %pK\n",get_ttbr0_el1());	
	pr_err("ttbr0_el1: %px\n",get_ttbr0_el1());	
	pr_err("ttbr0_el1: %llx\n",(unsigned long long)get_ttbr0_el1());	
	pr_err("ttbr1_el1: %pK\n",get_ttbr1_el1());	
	pr_err("ttbr1_el1: %px\n",get_ttbr1_el1());	
	pr_err("ttbr1_el1: %llx\n",(unsigned long long)get_ttbr1_el1());	
	pr_err("__pa: %pK\n",(void *)__pa(0xffffffc01134f000));	
	pr_err("__pa: %px\n",(void *)__pa(0xffffffc01134f000));	
	pr_err("__pa %llx\n", __pa(0xffffffc01134f000));

	pr_err("swapper_pg_dir: %px\n", (void *)kallsyms_lookup_name("swapper_pg_dir") );

	msleep(2000);
	}
	return 0;
}
static struct task_struct * thread_ptr=NULL;
static int  __init get_addr_init(void) {
	thread_ptr = kthread_run(threadfn,NULL,"kthread_get_addr_info");
	if(!thread_ptr) {
		pr_err("kthread_run failed");
		return -ECHILD;
	}
	return 0;
}

static void __exit get_addr_exit(void) {
	if(thread_ptr)
		kthread_stop(thread_ptr);
	return ;
}
module_init(get_addr_init);
module_exit(get_addr_exit);
MODULE_LICENSE ("GPL");
