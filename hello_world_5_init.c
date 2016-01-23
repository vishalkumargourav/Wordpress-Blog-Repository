#include<linux/init.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
int init_module(void){
  printk(KERN_ALERT "\nThis is the hello_world_5 init_module function.....");
  return 0;
}
