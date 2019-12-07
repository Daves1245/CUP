#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Santamaria");
MODULE_DESCRIPTION("An exercise to learning the kernel");
MODULE_SUPPORTED_DEVICE("test");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello2 initialized!\n");
    return 0;
}

static void __exit hello_exit(void)
{
        printk(KERN_INFO "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

