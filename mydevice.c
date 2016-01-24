#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>		//FOR FILE STRUCTURE
#include<asm/uaccess.h>

//FUNCTION PROTOTYPES
int init_module(void);		//FOR INITIALIZING OUR MODULE
void cleanup_module(void);	//FOR DE-INITIALIZING OUR MODULE
static ssize_t read_my_device(struct file *,char *,size_t,loff_t *);	//FOR READING THE DEVICE
static ssize_t write_my_device(struct file *,const char *,size_t,loff_t *);	//FOR WRITING TO THE DEVICE
static int open_my_device(struct inode *,struct file *);	//FOR OPENING THE DEVICE
static int release_my_device(struct inode *,struct file *);	//FOR CLOSING THE DEVICE

//CONSTANTS
#define SUCCESS 0			
#define DEVICE_NAME "mydevice"		//NAME OF DEVICE
#define BUF_LEN 80			//MAX LENGTH OF MESSAGE FROM DEVICE

/*
 * Global variables are declared static so that they are global within the file
 */

static int Major_number;		//MAJOR NUMBER ASSIGNED TO OUR DEVICE DRIVER
static int Is_device_open=0;		//IS DEVICE OPEN?SO AS TO PREVENT MULTIPLE ACCESS TO DEVICE
static char msg[BUF_LEN];		//THE MESSAGE THAT DEVICE WILL GIVE WHEN ASKED
static char *msg_p;			//POINTER TO MESSAGE

static struct file_operations fops = {
		.read=read_my_device,
		.write=write_my_device,
		.open=open_my_device,
		.release=release_my_device
};

int init_module(void){
	Major_number=register_chrdev(0,DEVICE_NAME,&fops);	//USED TO REGISTER DEVICE, FIRST ARGUMENT IS MAJOR NUMBER , IF WE PASS 0 IN THAT PLACE THEN KERNEL WILL AUTOMATICALLY ASSIGN A RANDOM Major Number AND THE RETURNED VALUE OF THIS FUNCTION IS THAT MAJOR NUMBER,SECOND ARGUMENT IS THE DEVICE NAME,AND THIRD ARGUMENT IS FILE OPERATIONS DATASTRUCTURE
	if(Major_number<0){	//IF ABOVE FUNCTION RETURNS -ve NUMBER THEN IT HAS FAILED TO REGISTER OUR DEVICE
		printk(KERN_ALERT "\nRegistering device failed!!! returned value is:%d\n",Major_number);
		return Major_number;
	}

	printk(KERN_INFO "\nMajor Number assigned to me is:%d\n",Major_number);
	printk(KERN_INFO "\nTo talk to driver, create a dev file with 'mknod /dev/%s c %d 0'.\n",DEVICE_NAME,Major_number);
	printk(KERN_INFO "\nTry various minor numbers,Try to cat and echo to the device file /dev/%s\n",DEVICE_NAME);
	printk(KERN_INFO "\nRemove the device file and module when donewith 'rm /dev/%s'\n",DEVICE_NAME);
	return SUCCESS;
}

void cleanup_module(void){
	unregister_chrdev(Major_number,DEVICE_NAME);	//USED FOR UNREGISTERING THE DEVICE
}

static int open_my_device(struct inode *inode,struct file *file){
	static int counter=0;
	if(Is_device_open)
		return -EBUSY;
	Is_device_open++;		//TO PREVENT MULTIPLE ACCESS TO FILE SIMULTENEOUSLY
	sprintf(msg,"\nI already told you %d times Hello World!!!\n",counter++);	//THIS FUNCTIONS STORES THE MESSAGE INTO STRING msg
	msg_p=msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

static int release_my_device(struct inode *inode,struct file *file){
	Is_device_open--;
	module_put(THIS_MODULE);
	return SUCCESS;
}

static ssize_t read_my_device(struct file *flip,char *buffer,size_t length,loff_t *offset){
	int bytes_read=0;	//NUMBER OF BYTES ACTUALLY WRITTEN TO BUFFER
	if(*msg_p==0)
		return 0;
	while(length&&*msg_p){
		put_user(*(msg_p++),buffer++);
		length--;
		bytes_read++;
	}
	return bytes_read;
}

static ssize_t write_my_device(struct file *flip,const char *buff,size_t len,loff_t *offset){
	printk(KERN_ALERT "\nSorry!!! This operations is not supported\n");
	return -EINVAL;
}
