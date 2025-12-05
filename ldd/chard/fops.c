#include <linux/module.h>    // Required for kernel modules
#include <linux/kernel.h>    // Required for printk()
#include <linux/fs.h>        // Required for file_operations
#include <asm/uaccess.h>     // Required for copy_to_user/copy_from_user
#include<linux/ioctl.h>
#include"chard_if.h"
static bool lock = false;
static int buffer_size = 1024;
static char message[1024];
static short size_of_message;

// Device open function
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "SimpleCharDevice: device_open()\n");
    return 0;
}

// Device release (close) function
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "SimpleCharDevice: device_release()\n");
    return 0;
}

// Device read function
static ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset) {
    if(lock)
	    return 0;
    if (*offset >= size_of_message) {
        return 0; // End of file
    }
    if (*offset + len > size_of_message) {
        len = size_of_message - *offset; // Adjust length if reading past end
    }
    if (copy_to_user(buffer, message + *offset, len) != 0) {
        return -EFAULT; // Bad address
    }
    *offset += len;
    printk(KERN_INFO "SimpleCharDevice: device_read() - read %zu bytes\n", len);
    return len;
}

// Device write function
static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
    if(lock)
	    return 0;

    if (len > buffer_size) {
        len = buffer_size; // Prevent buffer overflow
    }
    if (copy_from_user(message, buffer, len) != 0) {
        return -EFAULT; // Bad address
    }
    size_of_message = len;
    printk(KERN_INFO "SimpleCharDevice: device_write() - wrote %zu bytes\n", len);
    return len;
}
static long device_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
	pr_info("ioctl called %d",cmd);
	switch(cmd){
		case CHARD_LOCK:
			lock = true;
			break;
		case CHARD_UNLOCK:
			lock = false;
			break;
		case CHARD_BUFF_SIZE:
			if(arg>1024 || arg<0)
				buffer_size = 1024;
			else
				buffer_size = arg;
			pr_info("buffer size %d",buffer_size);
			break;

		default:
			break;
	}
	return 0;
}

// File operations structure
static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
    .owner = THIS_MODULE
};

