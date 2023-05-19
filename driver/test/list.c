#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/list.h>
LIST_HEAD(list);


struct node_t {
        int cnt;
        struct list_head entry;
};





static int mynet_probe(struct platform_device *pdev)
{

struct list_head *p1;
struct node_t *p2;


struct node_t node[10];


for(int i=0;i<10;++i)
{

	node[i].cnt = i;
	list_add_tail(&node[i].entry,&list);
}
list_for_each(p1,&list) {
	p2 = container_of(p1,struct node_t,entry);
	printk("%d\n",p2->cnt);
}


list_for_each_entry(p2,&list,entry) {
	printk("%d\n",p2->cnt);
}

    return 0;
}

static int mynet_remove(struct platform_device *dev)
{

    return 0;
}

static const struct of_device_id id_table[] = {
	{.compatible = "ghj,mynet",},
	{},
};
static struct platform_driver mynet_drv = {
	.probe	=	mynet_probe,
	.remove	=	mynet_remove,
	.driver	=	{
		.name	=	"mynet",
		.of_match_table	= id_table,
	}
};

MODULE_LICENSE ("GPL");

module_platform_driver(mynet_drv);
