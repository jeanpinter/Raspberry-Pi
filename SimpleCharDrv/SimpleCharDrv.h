#ifndef __SIMPLE_CHAR_DRV_H
#define __SIMPLE_CHAR_DRV_H

#include <linux/init.h>
MODULE_LICENSE("GPL");

extern int SimpleCharDrv_open (struct inode* poInode, struct file* poFile);
extern ssize_t SimpleCharDrv_read(struct file* poFile, char __user *poBuff, size_t length, loff_t *poOffset);
extern ssize_t SimpleCharDrv_write(struct file* poFile, const char __user *poBuff, size_t length, loff_t *poOffset);
extern int SimpleCharDrv_close(struct inode *poInode, struct file *poFile);

struct file_operations SimpleCharDrv_fops = {
    .owner = THIS_MODULE,
    .read  = SimpleCharDrv_read,
    .write = SimpleCharDrv_write,
    .open  = SimpleCharDrv_open,
    .release = SimpleCharDrv_close,
};

#endif
