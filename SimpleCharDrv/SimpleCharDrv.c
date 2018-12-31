#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

#include "SimpleCharDrv.h"

dev_t dev;
struct cdev *my_cdev;


__init int SimpleCharDrv_init(void)
{
    printk(KERN_ALERT "Init. %s\n", __FUNCTION__);

    // let kernel allocate device number for me
    // alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
    alloc_chrdev_region(&dev, 0, 1, "SimpleCharDrv");
	
    // set up cdev struct
    my_cdev = cdev_alloc();
    cdev_init (my_cdev, &SimpleCharDrv_fops);
    cdev_add(my_cdev, dev, 1);
	
    return 0;
}


int  SimpleCharDrv_open(struct inode* poInode, struct file* poFile)
{
    printk(KERN_ALERT "Open. %s\n", __FUNCTION__);
    return 0;
}

int SimpleCharDrv_read(struct file* poFile, char __user *poBuff, size_t length, loff_t *poOffset)
{
    printk(KERN_ALERT "Read. %s\n", __FUNCTION__);
    return 0;
}

int SimpleCharDrv_write(struct file* poFile, const char __user *poBuff, size_t length, loff_t *poOffset)
{
    printk(KERN_ALERT "Write. %s\n", __FUNCTION__);
    return 0;
}

int SimpleCharDrv_close(struct inode *poInode, struct file *poFile)
{
    printk(KERN_ALERT "Close. %s\n", __FUNCTION__);
    return 0;
}

__exit void SimpleCharDrv_exit(void)
{
    printk(KERN_ALERT "Exit. %s\n", __FUNCTION__);
    unregister_chrdev_region(dev, 1);
    cdev_del(my_cdev);
}

module_init(SimpleCharDrv_init);
module_exit(SimpleCharDrv_exit);
