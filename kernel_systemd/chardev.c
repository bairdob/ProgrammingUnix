#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/wait.h> 
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/stat.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("BairDobylov");
MODULE_DESCRIPTION("Waiting Process Demo");

#define FIRST_MINOR 0
#define MINOR_CNT 1
#define TRUE 1
#define FALSE 0
#define BUF_LEN 1024

static int counter = 0;
static bool thr_lock = FALSE; 
static dev_t dev;
static struct cdev c_dev;
static struct class *cl;
static DECLARE_WAIT_QUEUE_HEAD(wq);
static char msg[BUF_LEN]; 
static char *msg_Ptr;


struct task_struct *ts; 
int thread(void *data) { 
    while(1) {
        msleep(100);
        sprintf(msg, "%d\n",counter);
        msg_Ptr = msg;
        if (thr_lock == FALSE) {
            counter++;
            printk("Hello. I am kernel thread! counter=%d\n", counter);
            msleep(5000);
            thr_lock = TRUE;
            wake_up_interruptible(&wq);
        } 
    } 
    return 0; 
} 

ssize_t read(struct file *filp, char *buffer, size_t length, loff_t *offset) 
{
    printk(KERN_INFO "Inside read\n");
    printk(KERN_INFO "Scheduling Out\n");
    wait_event_interruptible(wq, thr_lock == TRUE);
    thr_lock = FALSE;
    printk(KERN_INFO "Woken Up\n");

    int bytes_read = 0;

    if (*msg_Ptr == 0) 
        return 0;

    while (length && *msg_Ptr) {
        put_user(*(msg_Ptr++), buffer++);
        length--; 
        bytes_read++;
    }

    return bytes_read;
}

int open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Inside open\n");
    try_module_get(THIS_MODULE);
    return 0;
}

int release(struct inode *inode, struct file *filp) 
{
    printk (KERN_INFO "Inside close\n");
    module_put(THIS_MODULE);
    return 0;
}

struct file_operations pra_fops = {
    read:        read,
    open:        open,
    release:     release
};

int init_module(void) { 
    printk(KERN_INFO "init_module() called\n");

    int ret;
    struct device *dev_ret;

    if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "SCD")) < 0)
    {
        return ret;
    }
    printk("Major Nr: %d\n", MAJOR(dev));

    cdev_init(&c_dev, &pra_fops);

    if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
    {
        unregister_chrdev_region(dev, MINOR_CNT);
        return ret;
    }

    if (IS_ERR(cl = class_create(THIS_MODULE, "chardrv")))
    {
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(cl);
    }
    if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "chardev")))
    {
        class_destroy(cl);
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(dev_ret);
    }

    ts=kthread_run(thread,NULL,"foo kthread");
    return 0;
} 

void cleanup_module(void) { 
    kthread_stop(ts); 
    printk(KERN_INFO "cleanup_module() called\n"); 
    device_destroy(cl, dev);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev, MINOR_CNT);
}

