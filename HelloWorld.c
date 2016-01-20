#include<linux/module.h>
#include<linux/init.h>
static int hello_init(void){
	printk(KERN_ALERT "\nTEST:This is intialization function...\n");
	return 0;
}
static void hello_exit(void){
	printk(KERN_ALERT "\nTEST:This is termination function\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
