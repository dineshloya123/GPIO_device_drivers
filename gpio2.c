#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/delay.h>
#include<linux/uaccess.h>
#include<linux/gpio.h>
#include<linux/err.h>
#include<linux/gpio/consumer.h>

int  GPIO_21=21;

dev_t dev=0;
static struct class *dev_class;
static struct cdev etx_cdev;
static struct gpio_desc *gpio21_desc; // Gpio descriptor

static int etx_open(struct inode *inode, struct file *file)
{
	pr_info("Device file opened...!\n");
	return 0;
}

static int etx_release(struct inode *inode, struct file *file)
{
	pr_info("Device file closed...!\n");
	return 0;
}
static ssize_t etx_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
	unsigned int  gpio_state=0;
	gpio_state=gpiod_get_value(gpio21_desc);
	len=1;
	if(copy_to_user(buf,&gpio_state,len)>0)
	{
		pr_err("Error: Data not Read properly..!\n");
	}
	pr_info("GPIO 21 Pin State:%d\n",gpio_state);
	return 0;
}

static ssize_t etx_write(struct file *file,const char __user *buf,size_t len, loff_t *off)
{
	unsigned int state=0;
	
	if(copy_from_user(&state,buf,len)>0)
	{
		pr_err("Error:Data not wrote properly...!\n");
	}
	pr_info("gpio 21 pin set to %d state\n",state);
	if(state==1)
		gpiod_set_value(gpio21_desc,1);
	else if(state==0)
		gpiod_set_value(gpio21_desc,0);
	else
		pr_err("Not a correct option, Enter 1 or 0\n");
	return 0;
}

static struct file_operations fops=
{
	.owner=THIS_MODULE,
	.read= etx_read,
	.write=etx_write,
	.open=etx_open,
	.release=etx_release,
};

static int __init etx_driver_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"etx_dev"))<0)
	{
		pr_err("cannot allocate major number\n");
		unregister_chrdev_region(dev,1);
	}
	pr_info("Major=%d Minor=%d\n", MAJOR(dev),MINOR(dev));

	cdev_init(&etx_cdev,&fops);

	if((cdev_add(&etx_cdev,dev,1))<0)
	{
		pr_err("cannot create device..!\n");
		cdev_del(&etx_cdev);
	}
	if(IS_ERR(dev_class=class_create("etx_class")))
	{
		pr_err("Cannot create class..!\n");
		class_destroy(dev_class);
	}
	if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"etx_device")))
	{
		pr_err("cannot create device...!\n");
		device_destroy(dev_class,dev);
	}

	gpio21_desc= gpio_to_desc(GPIO_21); //get gpio descriptor
	
       	if (!gpio21_desc)
	 {
       		 pr_err("GPIO %d is not valid..!\n", GPIO_21);
        	device_destroy(dev_class, dev);
        	class_destroy(dev_class);
        	cdev_del(&etx_cdev);
        	unregister_chrdev_region(dev, 1);
        	return -1;
   	 }


	if(gpio_is_valid(GPIO_21)==false)
	{
		pr_err("GPIO %d is not valid..!\n",GPIO_21);
		device_destroy(dev_class,dev);
	}
	if(gpio_request(GPIO_21,"GPIO _21")<0)
	{
		pr_err("Error:GPIO %d request \n",GPIO_21);
		gpio_free(GPIO_21);
	}

	gpio_direction_output(GPIO_21,0);

	gpiod_export(gpio21_desc,true);

	pr_info("Device Driver Insert...Done!!!\n");
	return 0;
}

static void __exit etx_driver_exit(void)
{
	unregister_chrdev_region(dev,1);
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&etx_cdev);
	gpiod_unexport(gpio21_desc);
	gpio_free(GPIO_21);
	pr_info("Device Driver Remove ...Done!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_AUTHOR("DINESH");
MODULE_DESCRIPTION("GPIO MODULE");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
