This is where i started developing device drivers
* A device in linux is treated as a file where you can open the file, read from, write into and close the file.
* The whole point of writing a device driver is to create this abstraction of device being a file.
* In kernel space, building a device driver starts with fetching a file name for the device file which is done by requesting kernel to allocate available device number to the device file that is to be created.
* Using this file name, a character device file(object) is created where in you assign operations on this file accordig to the behaviour of your device.
* Most of the intelligence in your driver lies in the file operations you write to give an of device being a file. So understanding your device is the most toughest part of writing a device sriver. 
