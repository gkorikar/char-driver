// Thi sc fiel is a character device driver for scull based devices
// AUthor: Gautam Anand Korikar
// Start date: Feb 24 2016


//including necessary header files
#include <linux/module.h>	// contains symbols and functions for loadable modules
#include <linux/kernel.h>	// for talking to kernel
#include <linux/init.h>		// contains initialization and cleanup functions
#include <linux/fs.h>		// for fetching device number
#include <linux/cdev.h>		// for character device file 
#include <linux/semaphore.h>

//defining macros
#define MY_DEVICE "Gau_Device"

struct memdevice{
    char mem_map[150];
    struct semaphore sem;
}my_device;

//necessary varaibles 
int major_number, ret;
dev_t gdevice;
struct cdev *device_file;

//defining file operations on device file
int open_dfile(struct inode *inode,struct file *filp){
    if(down_interruptible(&my_device.sem)!=0){
	printk(KERN_ALERT "Device cannot be opened");
	return -1;
    }
    printk(KERN_ALERT "Device opened\n");
    return 0;
}

ssize_t read_dfile(struct file* filp,char* buf_data,size_t buf_size,loff_t* seek){
    return 0;
}

ssize_t write_dfile(struct file* filp, const char* buf_data,size_t buf_size,loff_t* seek){
    return 0;
}

int close_dfile(struct inode *inode,struct file *flip){
    up(&my_device.sem);
    printk(KERN_ALERT "Device closed\n");
    return 0;
}

//setting devce file operations
struct file_operations fops ={
    .owner=THIS_MODULE,	//this module owns the device
    .open=open_dfile,	//set open device file call back function
    .read=read_dfile,	//set read device file call back function
    .write=write_dfile,	//set write to device file call back function
    .release=close_dfile//set close device file call back function
};

// defining module entry function
static int __init gdevice_setup(void){
    ret=alloc_chrdev_region(&gdevice,0,1,MY_DEVICE);	// fetch device number 
    if(ret<0){
	printk(KERN_ALERT "Device number cannot be allocated\n");
	return ret;
    }
    major_number=MAJOR(gdevice);	// extract major number
    printk("type \"mknod /dev/%s c %d 0\" to create device node\n",MY_DEVICE,major_number);
    
    //create character device file in kernel
    device_file=cdev_alloc();
   //set device file properties 
    ret=cdev_add(device_file,gdevice,1);
    if(ret<0){
	printk(KERN_ALERT "Device cannot be added\n");
	return ret;
    }
    device_file->ops=&fops;
    printk(KERN_ALERT "Device file sucessfully created\n");
    sema_init(&my_device.sem,1);	//setting lock value for device




    return 0;
} 

//defining module cleanup function 
static void __exit gdevice_cleanup(void){
    unregister_chrdev_region(gdevice,1);	// unregister device number
    printk(KERN_ALERT "Module removed\n");
}

module_init(gdevice_setup);
module_exit(gdevice_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gautam Anand Korikar");
