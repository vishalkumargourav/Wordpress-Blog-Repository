#include<linux/module.h>
#include<linux/init.h>
static int __init hello_init(void){
	printk(KERN_ALERT "\nTEST:This is intialization function...\n");
	return 0;
}
static void __exit hello_exit(void){
	printk(KERN_ALERT "\nTEST:This is termination function\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vishal Kumar Gourav");
MODULE_DESCRIPTION("This is a test module");
MODULE_SUPPORTED_DEVICE("DEVICE NAME");
