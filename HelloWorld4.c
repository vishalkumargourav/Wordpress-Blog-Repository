#include<linux/module.h>
#include<linux/init.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vishal Kumar Gourav");

static int var_int=0;
static char *var_string;
static int var_arr[3]={0,0,0};
static int arr_arg=0;

//Initialization of variables
module_param(var_int,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
module_param(var_string,charp,0000);
module_param_array(var_arr,int,&arr_arg,0000);

//Description of variables
MODULE_PARM_DESC(var_int ,"Integer variable");
MODULE_PARM_DESC(var_string ,"String variable");
MODULE_PARM_DESC(var_arr ,"Array of integers");
MODULE_PARM_DESC(arr_arg ,"For tracking number of array elements");
static int __init hello_init(void){
	int i;
	printk(KERN_ALERT "\nHello World this is hello_init function");
	printk(KERN_ALERT "\nvar_int=%d",var_int);
	printk(KERN_ALERT "\nvar_string=%s",var_string);
	for(i=0;i<(sizeof(var_arr)/sizeof(var_arr[0]));i++){
		printk(KERN_ALERT "\nvar_arr[%d]=%d",i,var_arr[i]);		;
	}
	printk(KERN_ALERT "\narr_arg=%d",arr_arg);
	return 0;
}
static void __exit hello_exit(void){
	printk(KERN_ALERT "\nThis is hello_exit function");
}
module_init(hello_init);
module_exit(hello_exit);
