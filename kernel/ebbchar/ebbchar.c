// copied from derek molloy's tutorial introduction to kernel hacking

/**
* @file         ebbchar.c
* @author       Derek Molloy
* @version      0.1
* @brief An introductory character driver to support the second article of my series on
* linux loadable kernel module (LKM) development. This modulel maps to /dev/ebbchar and
* comes with a helper C program that can be run in linux user space to communicate with
* this the LKM.
* @see http://www.derekmolloy.ei/ for a full description and follow up descriptions.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "ebbchar"   // < The device will appear at /dev/ebbchar using this value
#define CLASS_NAME "ebb"        // The device class -- this is a character device driver

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Derek Molloy");
MODULE_DESCRIPTION("A simple char device for the BBB");
MODULE_VERSION("0.1");

static int major;
static char message[256] = { 0 };
static short message_size;
static int number_of_opens = 0;
static struct class *ebb_char_class = NULL;
static struct device *ebb_char_device = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

/**
* @brief Devices are represented as file structures in the kernel The file_ops struct from linux/fs.h lists
* the callback functions that you wish to associate with your file operations using a C99 syntax structure.
* char devices implement open, read, write and release calls
*/

static struct file_operations fops = 
{
        .open = dev_open,
        .release = dev_release,
        .read = dev_read,
        .write = dev_write,
};

/**
* @brief The LKM initialization function
* The static keyword restricts the visibilaty of the function to within this C file. The __init
* macro means that for a built-in driver (not a LKM) the function is only used at initialization
* time and that it can be discarded and its memory freed up after that point.
*/
static int __init ebbchar_init(void)
{
        printk(KERN_INFO "EBBChar: Initializing the Ebbchar LKM\n");

        // Try to dynamically allocate a major number number for this device -- more difficult but worth it
        major = register_chrdev(0, DEVICE_NAME, &fops);
        if (major < 0) {
                printk(KERN_ALERT "EBBChar failed to register a major number\n");
                return major;
        }
        printk(KERN_INFO "EBBChar: Registered correctly with major number %d\n", major);

        // Register a device class
        ebb_char_class = class_create(THIS_MODULE, CLASS_NAME);
        if (IS_ERR(ebb_char_class)) {
                unregister_chrdev(major, DEVICE_NAME);
                printk(KERN_ALERT "Failed to register device class\n");
                return PTR_ERR(ebb_char_class);
        } 
        printk(KERN_INFO "EBBChar: device class registered correctly\n");

        // Register the device driver
        ebb_char_device = device_create(ebb_char_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
        if (IS_ERR(ebb_char_device)) {
                class_destroy(ebb_char_class);
                unregister_chrdev(major, DEVICE_NAME);
                printk(KERN_ALERT "Failed to create device\n");
                return PTR_ERR(ebb_char_device);
        }
        printk(KERN_INFO "EBBChar: device class created correctly\n");
        return 0;
}

/**
* @brief The LKM cleanup function
* Similar to the initialization function, it is static. The __exit macro notifies that if this
* code is used for a built-in driver (not a LKM) that this function is not required.
*/
static void __exit ebbchar_exit(void)
{
        device_destroy(ebb_char_class, MKDEV(major, 0));
        class_unregister(ebb_char_class);
        class_destroy(ebb_char_class);
        unregister_chrdev(major, DEVICE_NAME);
        printk(KERN_INFO "EBBChar: goodbye from the LKM!\n");
}

/**
* @brief The device open function that is called each time the device is opened
* This will only incrememnt the number of opens counter in this case
* @param inodep A pointer to an inode object (defined in linux/fs.h)
* @param filep A pointer to a file object (defined in linux/fs.h)
*/
static int dev_open(struct inode *inodep, struct file *filep)
{
        number_of_opens++;
        printk(KERN_INFO "EBBChar: Device has been opened %d times", number_of_opens);
        return 0;
}

/**
* @brief This function is called whenever device is being read from user space i.e.
* data is sent to the device from the user. The data is copied to the message[] array in this
* LKM using the sprintf() function along with the length of the string
* @param filep A pointer to a file object
* @param buffer The buffer that contains the string to write to the device
* @param len The length of the array of data that is being passed in the const char buffer
* @param offset The offset if required.
*/
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
        int err_count = copy_to_user(buffer, message, message_size);

        if (err_count == 0) {
                printk(KERN_INFO "EBBChar: Sent %d characters to the user\n", err_count);
                return -EFAULT;
        }
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
        sprintf(message, "%s(%zu letters)", buffer, len);
        message_size = strlen(message);
        printk(KERN_INFO "EBBChar: Received %zu characters from the user\n", len);
        return len;
}

/**
* @brief The device release function that is called whenever the device is closed/released from the user program
* @param inodep A pointer to an inode object (defined in linux/fs.h)
* @param filep A pointer to a file object (defined in linux/fs.h)
*/
static int dev_release(struct inode *inodep, struct file *filep)
{
        printk(KERN_INFO "EBBChar: Device successfully closed\n");
        return 0;
}

/**
* @brief A module must use the module_init() module_exit() macros from linux/init.h, which 
* identify the initialization function at insertion time and the cleanup function (as
* listed above)
*/
module_init(ebbchar_init);
module_exit(ebbchar_exit);
