#include<linux/init.h>
#include<linux/module.h>
void  cleanup_module(void){
  printk(KERN_ALERT "\n This is hello_world_5 cleanup_module function....");
}
