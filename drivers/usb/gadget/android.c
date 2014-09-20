/*
 * Gadget Driver for Android
 *
 * Copyright (C) 2008 Google, Inc.
 * Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
 * Author: Mike Lockwood <lockwood@android.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/

/* #define DEBUG */
/* #define VERBOSE_DEBUG */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/debugfs.h>

#include <linux/usb/android_composite.h>
#include <linux/usb/ch9.h>
#include <linux/usb/composite.h>
#include <linux/usb/gadget.h>

#include "gadget_chips.h"




#include "f_cdrom.h"
#include "comm_usb.h"


#include "f_timer.h"




/*
 * Kbuild is not very cooperative with respect to linking separately
 * compiled library objects into one module.  So for now we won't use
 * separate compilation ... ensuring init/exit sections work to shrink
 * the runtime footprint, and giving us at least some parts of what
 * a "gcc --combine ... part1.c part2.c part3.c ... " build would.
 */
#include "usbstring.c"
#include "config.c"
#include "epautoconf.c"
#include "composite.c"

MODULE_AUTHOR("Mike Lockwood");
MODULE_DESCRIPTION("Android Composite USB Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");





static int android_set_pid(const char *val, struct kernel_param *kp);
static int android_get_pid(char *buffer, struct kernel_param *kp);
module_param_call(product_id, android_set_pid, android_get_pid,
					NULL, 0664);
MODULE_PARM_DESC(product_id, "USB device product id");




enum Direction
{
	VE120_TO_MODELPID = 1,   
	MODELPID_TO_VE120        
};



#define LOCAL_MODEM		0x0001
#define LOCAL_MASS		0x0002
#define LOCAL_TETHER	0x0003
#define LOCAL_VE111	0x0004





static u16 usb_local_pid = LOCAL_MODEM;
static u16 bef_usb_local_pid = LOCAL_MODEM;








static const char longname[] = "Gadget Android";

/* Default vendor and product IDs, overridden by platform data */
#define VENDOR_ID		0x18D1
#define PRODUCT_ID		0x0001





static u8 usb_dbg_mode;
static int android_set_dbg_mode(const char *val, struct kernel_param *kp);
static int android_get_dbg_mode(char *buffer, struct kernel_param *kp);
module_param_call(usb_dbg_mode, android_set_dbg_mode, android_get_dbg_mode,
					&usb_dbg_mode, 0664);
MODULE_PARM_DESC(usb_dbg_mode, "USB debugging mode");
#define MAX_SERIAL_LEN 256
static char serial_number_VE309[MAX_SERIAL_LEN] = "1234567890ABCDEF";
static struct kparam_string kps = {
	.string			= serial_number_VE309,
	.maxlen			= MAX_SERIAL_LEN,
};
static int android_set_sn(const char *kmessage, struct kernel_param *kp);
module_param_call(serial_number, android_set_sn, param_get_string,
						&kps, 0664);
MODULE_PARM_DESC(serial_number, "SerialNumber string");

static int adb_hidden_state = true;






struct android_dev {
	struct usb_composite_dev *cdev;
	struct usb_configuration *config;
	int num_products;
	struct android_usb_product *products;
	int num_functions;
	char **functions;

	int product_id;
	int version;




	struct mutex lock;




};

static struct android_dev *_android_dev;

#define MAX_STR_LEN		17 





#define DEVICE_DESC_BCDDEVICE	0x0100 




/* string IDs are assigned dynamically */

#define STRING_MANUFACTURER_IDX		0
#define STRING_PRODUCT_IDX		1
#define STRING_SERIAL_IDX		2

char serial_number[MAX_STR_LEN];
/* String Table */
static struct usb_string strings_dev[] = {
	/* These dummy values should be overridden by platform data */
	[STRING_MANUFACTURER_IDX].s = "Android",
	[STRING_PRODUCT_IDX].s = "Android",
	[STRING_SERIAL_IDX].s = "0123456789ABCDEF",
	{  }			/* end of list */
};

static struct usb_gadget_strings stringtab_dev = {
	.language	= 0x0409,	/* en-us */
	.strings	= strings_dev,
};

static struct usb_gadget_strings *dev_strings[] = {
	&stringtab_dev,
	NULL,
};

static struct usb_device_descriptor device_desc = {
	.bLength              = sizeof(device_desc),
	.bDescriptorType      = USB_DT_DEVICE,
	.bcdUSB               = __constant_cpu_to_le16(0x0200),

	


	.bDeviceClass         = USB_CLASS_COMM,



	.idVendor             = __constant_cpu_to_le16(VENDOR_ID),
	.idProduct            = __constant_cpu_to_le16(PRODUCT_ID),
	.bcdDevice            = __constant_cpu_to_le16(0xffff),
	.bNumConfigurations   = 1,
};





















static struct list_head _functions = LIST_HEAD_INIT(_functions);
static int _registered_function_count = 0;










#define USB_STAT_DISCN 0
#define USB_STAT_CONN  1
#define USB_STAT_OPEN  2

extern u32 usb_connect_boot_flag;


extern int msm72k_udc_usb_state;






static void android_set_default_product(int product_id);

void android_usb_set_connected(int connected)
{
	if (_android_dev && _android_dev->cdev && _android_dev->cdev->gadget) {
		if (connected)
			usb_gadget_connect(_android_dev->cdev->gadget);
		else
			usb_gadget_disconnect(_android_dev->cdev->gadget);
	}
}

static struct android_usb_function *get_function(const char *name)
{
	struct android_usb_function	*f;
	list_for_each_entry(f, &_functions, list) {
		if (!strcmp(name, f->name))
			return f;
	}
	return 0;
}

static void bind_functions(struct android_dev *dev)
{
	struct android_usb_function	*f;
	char **functions = dev->functions;
	int i;

	for (i = 0; i < dev->num_functions; i++) {
		char *name = *functions++;
		f = get_function(name);
		if (f)
			f->bind_config(dev->config);
		else
			pr_err("%s: function %s not found\n", __func__, name);
	}

	/*
	 * set_alt(), or next config->bind(), sets up
	 * ep->driver_data as needed.
	 */
	usb_ep_autoconfig_reset(dev->cdev->gadget);
}

static int __ref android_bind_config(struct usb_configuration *c)
{
	struct android_dev *dev = _android_dev;




	printk(KERN_DEBUG "android_bind_config\n");

	printk(KERN_DEBUG "_registered_function_count=%d dev->num_functions=%d\n",
		_registered_function_count, dev->num_functions);




	dev->config = c;

	/* bind our functions if they have all registered */
	if (_registered_function_count == dev->num_functions)
		bind_functions(dev);

	return 0;
}

static int android_setup_config(struct usb_configuration *c,
		const struct usb_ctrlrequest *ctrl);

static struct usb_configuration android_config_driver = {
	.label		= "android",
	.bind		= android_bind_config,
	.setup		= android_setup_config,
	.bConfigurationValue = 1,

	.bMaxPower	= 0xFA, /* 500ma */


};




static struct usb_function *get_function2(const char *name)
{
	struct usb_function	*f;
	list_for_each_entry(f, &android_config_driver.functions, list) {
		if (!strcmp(name, f->name)) {
			printk(KERN_INFO "get_function2 name %s\n", name);
			return f;
		}
	}
	return 0;
}





static int android_setup_config(struct usb_configuration *c,
		const struct usb_ctrlrequest *ctrl)
{
	int i;
	int ret = -EOPNOTSUPP;

	for (i = 0; i < android_config_driver.next_interface_id; i++) {
		if (android_config_driver.interface[i]->setup) {
			ret = android_config_driver.interface[i]->setup(
				android_config_driver.interface[i], ctrl);
			if (ret >= 0)
				return ret;
		}
	}
	return ret;
}


































static int get_product_id(struct android_dev *dev)
{




	return le16_to_cpu(device_desc.idProduct);


















}

static int __devinit android_bind(struct usb_composite_dev *cdev)
{
	struct android_dev *dev = _android_dev;
	struct usb_gadget	*gadget = cdev->gadget;




	int			id, product_id, ret;







	pr_debug("android_bind\n");

	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */
	id = usb_string_id(cdev);
	if (id < 0)
		return id;
	strings_dev[STRING_MANUFACTURER_IDX].id = id;
	device_desc.iManufacturer = id;

	id = usb_string_id(cdev);
	if (id < 0)
		return id;
	strings_dev[STRING_PRODUCT_IDX].id = id;
	device_desc.iProduct = id;

	id = usb_string_id(cdev);
	if (id < 0)
		return id;
	strings_dev[STRING_SERIAL_IDX].id = id;
	device_desc.iSerialNumber = id;











	if (!usb_gadget_set_selfpowered(gadget))
		android_config_driver.bmAttributes |= USB_CONFIG_ATT_SELFPOWER;












	/* register our configuration */
	ret = usb_add_config(cdev, &android_config_driver);
	if (ret) {
		pr_err("%s: usb_add_config failed\n", __func__);
		return ret;
	}





	device_desc.bcdDevice = cpu_to_le16(DEVICE_DESC_BCDDEVICE);




















	usb_gadget_set_selfpowered(gadget);
	dev->cdev = cdev;
	product_id = get_product_id(dev);

	device_desc.idProduct = __constant_cpu_to_le16(product_id);




	if(product_id == 0x02EC || product_id == 0x02ED){
		cdev->desc.idProduct = __constant_cpu_to_le16(0x02EF);
	}
	else
	{
		cdev->desc.idProduct = device_desc.idProduct;
	}






	return 0;
}

static struct usb_composite_driver android_usb_driver = {
	.name		= "android_usb",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.bind		= android_bind,
	.enable_function = android_enable_function,
};

void android_register_function(struct android_usb_function *f)
{
	struct android_dev *dev = _android_dev;

	pr_debug("%s: %s\n", __func__, f->name);
	list_add_tail(&f->list, &_functions);
	_registered_function_count++;

	/* bind our functions if they have all registered
	 * and the main driver has bound.
	 */
	if (dev->config && _registered_function_count == dev->num_functions) {
		bind_functions(dev);
		android_set_default_product(dev->product_id);
	}
}

/**
 * android_set_function_mask() - enables functions based on selected pid.
 * @up: selected product id pointer
 *
 * This function enables functions related with selected product id.
 */
static void android_set_function_mask(struct android_usb_product *up)
{
	int index, found = 0;
	struct usb_function *func;

	list_for_each_entry(func, &android_config_driver.functions, list) {
		/* adb function enable/disable handled separetely */
		if (!strcmp(func->name, "adb"))
			continue;



		if ((!strcmp(func->name, "diag")) && (usb_dbg_mode == 0))
			continue;




		for (index = 0; index < up->num_functions; index++) {
			if (!strcmp(up->functions[index], func->name)) {
				found = 1;
				break;
			}
		}

		if (found) { /* func is part of product. */
			/* if func is disabled, enable the same. */
			if (func->disabled)
				usb_function_set_enabled(func, 1);
			found = 0;
		} else { /* func is not part if product. */
			/* if func is enabled, disable the same. */
			if (!func->disabled)
				usb_function_set_enabled(func, 0);
		}
	}
}

/**
 * android_set_defaut_product() - selects default product id and enables
 * required functions
 * @product_id: default product id
 *
 * This function selects default product id using pdata information and
 * enables functions for same.
*/
static void android_set_default_product(int pid)
{
	struct android_dev *dev = _android_dev;
	struct android_usb_product *up = dev->products;
	int index;

	for (index = 0; index < dev->num_products; index++, up++) {
		if (pid == up->product_id)
			break;
	}
	android_set_function_mask(up);
}

/**
 * android_config_functions() - selects product id based on function need
 * to be enabled / disabled.
 * @f: usb function
 * @enable : function needs to be enable or disable
 *
 * This function selects product id having required function at first index.
 * TODO : Search of function in product id can be extended for all index.
 * RNDIS function enable/disable uses this.
*/
#ifdef CONFIG_USB_ANDROID_RNDIS
static void android_config_functions(struct usb_function *f, int enable)
{
	struct android_dev *dev = _android_dev;
	struct android_usb_product *up = dev->products;
	int index;
	char **functions;

	/* Searches for product id having function at first index */
	if (enable) {
		for (index = 0; index < dev->num_products; index++, up++) {
			functions = up->functions;
			if (!strcmp(*functions, f->name))
				break;
		}
		android_set_function_mask(up);
	} else
		android_set_default_product(dev->product_id);
}
#endif

void android_enable_function(struct usb_function *f, int enable)
{
	struct android_dev *dev = _android_dev;
	int disable = !enable;
	int product_id;




	u16 pid;


	adb_hidden_state = disable;
	pid = get_product_id(dev);
	
	if(pid == 0x02ED){
		return;
	}




	if (!!f->disabled != disable) {
		usb_function_set_enabled(f, !disable);

#ifdef CONFIG_USB_ANDROID_RNDIS
		if (!strcmp(f->name, "rndis")) {

			/* We need to specify the COMM class in the device descriptor
			 * if we are using RNDIS.
			 */
			if (enable) {
#ifdef CONFIG_USB_ANDROID_RNDIS_WCEIS
				dev->cdev->desc.bDeviceClass = USB_CLASS_MISC;
				dev->cdev->desc.bDeviceSubClass      = 0x02;
				dev->cdev->desc.bDeviceProtocol      = 0x01;
#else
				dev->cdev->desc.bDeviceClass = USB_CLASS_COMM;
#endif
			} else {
				dev->cdev->desc.bDeviceClass = USB_CLASS_PER_INTERFACE;
				dev->cdev->desc.bDeviceSubClass      = 0;
				dev->cdev->desc.bDeviceProtocol      = 0;
			}

			android_config_functions(f, enable);
		}
#endif

		product_id = get_product_id(dev);
		device_desc.idProduct = __constant_cpu_to_le16(product_id);




	{
		int cnt = 0; 
		int i = 0;
	
		for (i = 0; i < android_config_driver.next_interface_id; i++) {
			f = android_config_driver.interface[i];
			if (f) {
				if(f->disabled == false) {
					cnt++;
				}
			}
		}
		
		if(cnt > 1) {
			device_desc.bDeviceClass     = 2;
		}else{
			device_desc.bDeviceClass     = 0;
		}
	}
		if (dev->cdev) {

			if(product_id == 0x02EC || product_id == 0x02ED){
				dev->cdev->desc.idProduct =  __constant_cpu_to_le16(0x02EF);
			}
			else
			{
				dev->cdev->desc.idProduct = device_desc.idProduct;
			}



			dev->cdev->desc.bDeviceClass    = device_desc.bDeviceClass;
		}









		usb_composite_force_reset(dev->cdev);

		
	}
}

#ifdef CONFIG_DEBUG_FS
static int android_debugfs_open(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	return 0;
}

static ssize_t android_debugfs_serialno_write(struct file *file, const char
				__user *buf,	size_t count, loff_t *ppos)
{
	char str_buf[MAX_STR_LEN];

    memset(str_buf, 0, sizeof(str_buf));  
	if (count >= MAX_STR_LEN)             
		return -EFAULT;

	if (copy_from_user(str_buf, buf, count))
		return -EFAULT;

	strlcpy(serial_number, str_buf, MAX_STR_LEN); 

	if (serial_number[count - 1] == '\n')
		serial_number[count - 1] = '\0';

	strings_dev[STRING_SERIAL_IDX].s = serial_number;

	return count;
}
const struct file_operations android_fops = {
	.open	= android_debugfs_open,
	.write	= android_debugfs_serialno_write,
};

struct dentry *android_debug_root;
struct dentry *android_debug_serialno;

static int android_debugfs_init(struct android_dev *dev)
{
	android_debug_root = debugfs_create_dir("android", NULL);
	if (!android_debug_root)
		return -ENOENT;

	android_debug_serialno = debugfs_create_file("serial_number", 0222,
						android_debug_root, dev,
						&android_fops);
	if (!android_debug_serialno) {
		debugfs_remove(android_debug_root);
		android_debug_root = NULL;
		return -ENOENT;
	}
	return 0;
}

static void android_debugfs_cleanup(void)
{
       debugfs_remove(android_debug_serialno);
       debugfs_remove(android_debug_root);
}
#endif
static int __init android_probe(struct platform_device *pdev)
{
	struct android_usb_platform_data *pdata = pdev->dev.platform_data;
	struct android_dev *dev = _android_dev;
	int result;

	dev_dbg(&pdev->dev, "%s: pdata: %p\n", __func__, pdata);

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	result = pm_runtime_get(&pdev->dev);
	if (result < 0) {
		dev_err(&pdev->dev,
			"Runtime PM: Unable to wake up the device, rc = %d\n",
			result);
		return result;
	}

	if (pdata) {
		dev->products = pdata->products;
		dev->num_products = pdata->num_products;
		dev->functions = pdata->functions;
		dev->num_functions = pdata->num_functions;
		if (pdata->vendor_id)
			device_desc.idVendor =
				__constant_cpu_to_le16(pdata->vendor_id);
		if (pdata->product_id) {
			dev->product_id = pdata->product_id;
			device_desc.idProduct =
				__constant_cpu_to_le16(pdata->product_id);
		}
		if (pdata->version)
			dev->version = pdata->version;

		if (pdata->product_name)
			strings_dev[STRING_PRODUCT_IDX].s = pdata->product_name;
		if (pdata->manufacturer_name)
			strings_dev[STRING_MANUFACTURER_IDX].s =
					pdata->manufacturer_name;
		if (pdata->serial_number)




			strings_dev[STRING_SERIAL_IDX].s = serial_number_VE309;






	}
#ifdef CONFIG_DEBUG_FS
	result = android_debugfs_init(dev);
	if (result)
		pr_debug("%s: android_debugfs_init failed\n", __func__);
#endif
	return usb_composite_register(&android_usb_driver);
}






























static int get_usbmode(int pid)
{
	int mode = -1;

	switch(pid) {
	case LOCAL_MODEM: 
		mode = USBMODE_MODEM;
		break;
	case LOCAL_MASS: 
		mode = USBMODE_MASS;
		break;

	default: 
		break;
	}
	return mode;
}












































static void android_set_hidden( u16 pid )
{
	struct android_dev *dev = _android_dev;
	struct usb_function		*f = NULL;
	struct android_usb_product *product_tbl = NULL;
	int i;





		
	printk(KERN_INFO "%s pid=%x\n", __func__,pid);
	for(i = 0; i < dev->num_products; i++) {
		printk(KERN_INFO "%s dev->products[%d].product_id=%x\n", __func__,i,dev->products[i].product_id);

		if(pid == dev->products[i].product_id) {
			product_tbl = &dev->products[i];
			break;
		}
	}
	
	if(!product_tbl) {
		printk(KERN_ERR "%s pid=%x product_tbl is not found.\n", __func__,pid);
		return;
	}

	
	for (i = 0; i < android_config_driver.next_interface_id; i++) {
		f = android_config_driver.interface[i];
		if (f) {
			if (f->name == NULL) {
				printk(KERN_ERR "reset %s i=%d\n", __func__, i);
				continue;
			}

			if (!strcmp(f->name, "adb")){



				continue;
			}
			f->disabled = true;
		}
	}
	
	for ( i = 0; i < product_tbl->num_functions; i++ ) {
		char *name = product_tbl->functions[i];
		if (name == NULL) {
			printk(KERN_ERR "set hidden %s i=%d\n", __func__, i);
			continue;
		}
		if (!strcmp(name, "adb")) {
			continue;
		}
		f = get_function2(name);
		if (f) {
			f->disabled = false;
			if (!strcmp(name, "diag")) {










				if ((!usb_dbg_mode) 



                    ) {

					f->disabled = true;
				}










			}
		}
	}


	{
		int cnt =0;
	
		for (i = 0; i < android_config_driver.next_interface_id; i++) {
			f = android_config_driver.interface[i];
			if (f) {
				if(f->disabled == false) {
					cnt++;
				}
			}
		}
		
		if(cnt > 1) {
			device_desc.bDeviceClass     = 2;
		}else{
			device_desc.bDeviceClass     = 0;
		}
	}


	for (i = 0; i < android_config_driver.next_interface_id; i++) {
		f = android_config_driver.interface[i];
		if (f) {
			printk(KERN_INFO "*** function=%s hidden=%d ***\n", f->name, f->disabled);







		}
	}

	return;
}


static int android_switch_composition(u16 pid)
{
	struct android_dev *dev = _android_dev;
	u16 bef_pid;

	int ret;
	printk(KERN_INFO "android_switch_composition() start\n");

	bef_pid = get_product_id(dev);

	printk(KERN_INFO "%s bef_pid=%x aft_pid=%x\n", __func__, bef_pid, pid);


	if(pid == 0x02EB){
		return 0;
	}




	if( pid != 0x0310 && pid != 0x0311 )
	{
		printk(KERN_INFO "[%s] change_bef_pid = %d\n", __func__, pid);
		pid = 0x0311;
		printk(KERN_INFO "[%s] change_aft_pid = %d\n", __func__, pid);
		printk(KERN_INFO "[%s] change_bef_usb_local_pid = %d\n", __func__, usb_local_pid);
		usb_local_pid = LOCAL_MODEM;
		printk(KERN_INFO "[%s] change_aft_usb_local_pid = %d\n", __func__, usb_local_pid);
	}







































	android_set_hidden(pid);

	
	device_desc.idProduct = __constant_cpu_to_le16(pid);
	if (dev->cdev) {

		if(pid == 0x02EC || pid == 0x02ED){
			dev->cdev->desc.idProduct =  __constant_cpu_to_le16(0x02EF);
		}
		else
		{
	   	    dev->cdev->desc.idProduct = device_desc.idProduct;
		}




		dev->cdev->desc.bDeviceClass    = device_desc.bDeviceClass;


	    usb_composite_force_reset(dev->cdev);

	}





	if (pid != 0x02EB) {


















		

		ret = comm_usb_request_close(get_usbmode(bef_usb_local_pid));



		if (ret != 0) {
			printk(KERN_ERR "comm_usb_request_close() err=%d\n", ret);
		}
		

		ret = comm_usb_request_open(get_usbmode(usb_local_pid));



		if (ret != 0) {
			printk(KERN_ERR "comm_usb_request_open() err=%d\n", ret);
		}
	}


	printk(KERN_INFO "android_switch_composition() end\n");
	return 0;
}



static u16 android_transform_pid(u16 pid, enum Direction dir)
{	
	u16 product_id = 0;

	printk(KERN_INFO "android_transform_pid() start\n");
	printk(KERN_INFO "%s : pid=%x\n", __func__, pid);

	if (dir == VE120_TO_MODELPID) {
		bef_usb_local_pid = usb_local_pid; 
		printk(KERN_INFO "%s : bef_usb_local_pid=%x\n", __func__, bef_usb_local_pid);
		usb_local_pid = pid; 
		printk(KERN_INFO "%s : usb_local_pid=%x\n", __func__, usb_local_pid);
		

		
			switch(pid){
			case LOCAL_MODEM:   
				product_id = 0x0311;
				printk(KERN_INFO "%s : change VE119 to VE402  product_id=%x\n", __func__, product_id);
				break;
			case LOCAL_MASS:   
				product_id = 0x0311;
				printk(KERN_INFO "%s : change VE118 to VE402  product_id=%x\n", __func__, product_id);
				break;
			default:
				product_id = pid;
				printk(KERN_INFO "%s : Not supported VE402 pid=%x\n", __func__, product_id);
				break;
			}

























	} else if (dir == MODELPID_TO_VE120) {
		
		product_id = usb_local_pid; 
	} else{
		
		printk(KERN_INFO "%s : Not supported Direction \n", __func__);
	}
	printk(KERN_INFO "%s : usb_local_pid=%x dir=%d\n", __func__, usb_local_pid, dir);
	printk(KERN_INFO "%s : return product_id=%x dir=%d\n", __func__, product_id, dir);
	printk(KERN_INFO "android_transform_pid() end\n");
	return product_id;
}



static int android_set_pid(const char *val, struct kernel_param *kp)
{
	int ret = 0;
	unsigned long tmp;


	printk(KERN_INFO "android_set_pid() start\n");

	ret = strict_strtoul(val, 16, &tmp);
	if (ret)
		goto out;

	if((tmp != 0x02EB ) || (msm72k_udc_usb_state != 1)){
		printk(KERN_INFO "android_set_pid() usb_connect_boot_flag = 0\n");
		usb_connect_boot_flag = 0;
	}
	if(tmp == 0x02EB){
		printk(KERN_INFO "%s : pid=%x\n", __func__, (u16) tmp);
		goto out;
	}

	

	printk(KERN_INFO "%s : before pid=%x\n", __func__, (u16) tmp);
	tmp = android_transform_pid((u16)tmp, VE120_TO_MODELPID);
	printk(KERN_INFO "%s : after pid=%x\n", __func__, (u16) tmp);

	

	


	if (!_android_dev) {
		device_desc.idProduct = tmp;
		goto out;
	}

	mutex_lock(&_android_dev->lock);
	ret = android_switch_composition(tmp);
	mutex_unlock(&_android_dev->lock);
out:
	printk(KERN_INFO "android_set_pid() end\n");
	return ret;
}

static int android_get_pid(char *buffer, struct kernel_param *kp)
{
	int ret;
	int product_id;
	struct android_dev *dev = _android_dev;

	printk(KERN_INFO "android_get_pid() start\n");
	product_id = get_product_id(dev);
	

	printk(KERN_INFO "%s : before pid=%x\n", __func__, (u16) product_id);
	product_id = android_transform_pid((u16)product_id, MODELPID_TO_VE120);
	printk(KERN_INFO "%s : after pid=%x\n", __func__, (u16) product_id);

	

	mutex_lock(&_android_dev->lock);
	ret = sprintf(buffer, "%x", product_id);
	mutex_unlock(&_android_dev->lock);

	printk(KERN_INFO "android_get_pid() end\n");
	return ret;
}



static int android_set_dbg_mode(const char *val, struct kernel_param *kp)
{
	int ret = 0;



	int pid;
	u8 usb_dbg_mode_old = usb_dbg_mode;
	struct android_dev *dev = _android_dev;




	switch(*val) {
	case '0': 
		usb_dbg_mode = 0;
		break;
	case '1': 
		usb_dbg_mode = 1;
		break;
	default:
		usb_dbg_mode = 0;
	}




	mutex_lock(&_android_dev->lock);
	pid = get_product_id(dev);
	android_set_hidden(pid);

	
	device_desc.idProduct = __constant_cpu_to_le16(pid);
	if (dev->cdev) {
		dev->cdev->desc.idProduct = device_desc.idProduct;
		dev->cdev->desc.bDeviceClass    = device_desc.bDeviceClass;
	}
	if(usb_dbg_mode_old != usb_dbg_mode){
        usb_composite_force_reset(dev->cdev);
	}
	mutex_unlock(&_android_dev->lock);



	return ret;
}

static int android_get_dbg_mode(char *buffer, struct kernel_param *kp)
{
	int ret;

	mutex_lock(&_android_dev->lock);
	ret = sprintf(buffer, "%x", usb_dbg_mode);
	mutex_unlock(&_android_dev->lock);

	return ret;
}

static int android_set_sn(const char *kmessage, struct kernel_param *kp)
{
	int len = strlen(kmessage);

	if (len >= MAX_SERIAL_LEN) {
		pr_err("serial number string too long\n");
		return -ENOSPC;
	}

	strlcpy(serial_number_VE309, kmessage, MAX_SERIAL_LEN);
	
	if (serial_number_VE309[len - 1] == '\n')
		serial_number_VE309[len - 1] = '\0';

	return 0;
}



static int andr_runtime_suspend(struct device *dev)
{
	dev_dbg(dev, "pm_runtime: suspending...\n");
	return 0;
}

static int andr_runtime_resume(struct device *dev)
{
	dev_dbg(dev, "pm_runtime: resuming...\n");
	return 0;
}

static struct dev_pm_ops andr_dev_pm_ops = {
	.runtime_suspend = andr_runtime_suspend,
	.runtime_resume = andr_runtime_resume,
};

static struct platform_driver android_platform_driver = {
	.driver = { .name = "android_usb", .pm = &andr_dev_pm_ops},
};





void android_callback(struct usb_comm_response *response, void * puser)
{
	int product_id;
	struct android_dev *dev = _android_dev;

	product_id = get_product_id(dev);

	switch (response->head.type) {
	case TYPE_RESPONSE_OPEN:
		if (response->status == STATUS_SUCCESS) {





			printk(KERN_INFO "%s : open request success pid=%x\n", __func__, product_id);
		} else {
			printk(KERN_ERR "%s : open request err\n", __func__);
		}
		break;
	case TYPE_RESPONSE_CLOSE:
		if (response->status == STATUS_SUCCESS) {





			printk(KERN_INFO "%s : close request success pid=%x\n", __func__, product_id);
		} else {
			printk(KERN_ERR "%s : close request err\n", __func__);
		}
		break;
	case TYPE_RESPONSE_READ:
		if (response->status == STATUS_SUCCESS) {






























		} else {
			int ret;
			printk(KERN_ERR "%s : read request err\n", __func__);
			
			ret = comm_usb_request_close(get_usbmode(product_id));
			if (ret != 0) {
				printk(KERN_ERR "%s : comm_usb_request_close() err=%d\n", __func__, ret);
			}
		}
		break;
	case TYPE_RESPONSE_CONNECT:
		if (response->status == STATUS_SUCCESS) {
			usb_connect_boot_flag = 0;
			printk(KERN_INFO "%s : connect request success\n", __func__);
		} else {
			printk(KERN_ERR "%s : connect request err\n", __func__);
		}
		break;
	case TYPE_RESPONSE_DISCONNECT:
		if (response->status == STATUS_SUCCESS) {





			printk(KERN_INFO "%s : disconnect request success\n", __func__);
		} else {
			printk(KERN_ERR "%s : disconnect request err\n", __func__);
		}
		break;
	default:
		break;
	}
	return;
}





static int __init init(void)
{
	struct android_dev *dev;




	int ret;




	pr_debug("android init\n");

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	/* set default values, which should be overridden by platform data */
	dev->product_id = PRODUCT_ID;
	_android_dev = dev;




	mutex_init(&dev->lock);




	ret = platform_driver_probe(&android_platform_driver, android_probe);    

	if (ret)
		goto out;

out:
	return ret;







}





int android_get_product_id(void)
{
	return get_product_id(_android_dev);
}





module_init(init);

static void __exit cleanup(void)
{
#ifdef CONFIG_DEBUG_FS
	android_debugfs_cleanup();
#endif
	usb_composite_unregister(&android_usb_driver);
	platform_driver_unregister(&android_platform_driver);
	kfree(_android_dev);
	_android_dev = NULL;
}
module_exit(cleanup);
