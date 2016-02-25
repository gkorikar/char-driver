// Thi sc fiel is a character device driver for scull based devices
// AUthor: Gautam Anand Korikar
// Start date: Feb 24 2016


//including necessary header files
#include <linux/module.h>	// contains symbols and functions for loadable modules
#include <linux/kernel.h>	// for talking to kernel
#include <linux/init.h>		// contains initialization and cleanup functions
#include <linux/fs.h>		// for fetching device number

//defining macros
#define MY_DEVICE "Gau_Device"

//necessary varaibles 
int major_number, ret;
dev_t gdevice;

// defining module entry function
static int __init gdevice_setup(void){
    ret=alloc_chrdev_region(&gdevice,0,1,MY_DEVICE);	// fetch device number 
    if(ret<0){
	printk(KERN_ALERT "Device number cannot be allocated\n");
	return ret;
    }
    major_number=MAJOR(gdevice);	// extract major number
    printk("major number allocated is %d\n",major_number);
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
