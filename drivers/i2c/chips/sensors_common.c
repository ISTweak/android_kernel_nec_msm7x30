/**********************************************************************
* File Name: drivers/i2c/chips/sensors_common.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/



#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/spinlock.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <asm/uaccess.h>

#include <linux/i2c/i2c_sensors.h>









#define sensors_common_DRV_NAME "sensors_common"
#define DRIVER_VERSION      "1.0.0"





enum _e_sensors_type
{
    SENSORS_TYPE_ORIENTATION = 0,
    SENSORS_TYPE_ACCELERATION,
    SENSORS_TYPE_TEMPERATURE,
    SENSORS_TYPE_MAGNETIC_FIELD,
    SENSORS_TYPE_LIGHT,
    SENSORS_TYPE_PROXIMITY,
    SENSORS_TYPE_NUM_MAX
};

unsigned long g_ActiveSensors = 0;

int64_t g_DelayTime[SENSORS_TYPE_NUM_MAX];
static wait_queue_head_t g_active_queue;
static spinlock_t time_spin_lock;


static int get_sensors_delay( unsigned long arg )
{
    int ret = 0;
    void __user *argp = (void __user *)arg;
    struct delay_time __delay_time;
    
    memset( &__delay_time, 0x0, sizeof( struct delay_time ) );

    if( copy_from_user(&__delay_time, argp, sizeof(struct delay_time)) )
    {
        printk( KERN_ERR "[get_sensors_delay] copy_from_user() Err!!\n" );
        return -EFAULT;
    }

    spin_lock( &time_spin_lock );
    
    if( __delay_time.type >= SENSORS_TYPE_NUM_MAX )
    {
        printk( KERN_ERR "[get_sensors_delay] delay_time.type(%ld) delay_time.time(%lld) type >= SENSORS_TYPE_NUM_MAX Err!!\n", __delay_time.type, __delay_time.time );
        ret = -EINVAL;
    }
    else
    {
        __delay_time.time = g_DelayTime[__delay_time.type];


    }
    
    spin_unlock( &time_spin_lock );
    
    if( copy_to_user(argp, &__delay_time, sizeof(struct delay_time)) )
    {
        printk( KERN_ERR "[get_sensors_delay] copy_to_user() Err!!\n" );
        ret = -EFAULT;
    }

    return ret;
}

static int set_sensors_delay( unsigned long arg )
{
    int ret = 0;
    void __user *argp = (void __user *)arg;
    struct delay_time __delay_time;
    
    memset( &__delay_time, 0x0, sizeof( struct delay_time ) );

    if( copy_from_user(&__delay_time, argp, sizeof(struct delay_time)) )
    {
        printk( KERN_ERR "[set_sensors_delay] copy_from_user() Err!!\n" );
        return -EFAULT;
    }
    
    spin_lock( &time_spin_lock );

    if( __delay_time.type >= SENSORS_TYPE_NUM_MAX )
    {
        printk( KERN_ERR "[set_sensors_delay] delay_time.type(%ld) delay_time.time(%lld) type >= SENSORS_TYPE_NUM_MAX Err!!\n", __delay_time.type, __delay_time.time );
        ret = -EINVAL;
    }
    else
    {
        g_DelayTime[__delay_time.type] = __delay_time.time;

    }

    spin_unlock( &time_spin_lock );
    
    return ret;
}



static int sensors_common_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int sensors_common_release(struct inode *inode, struct file *file)
{
    return 0;
}

static int
sensors_common_ioctl(struct inode *inode, struct file *file, unsigned int cmd,
       unsigned long arg)
{
    int ret = -EINVAL;
    void __user *argp = (void __user *)arg;
    
    if( arg == 0 )
    {
        return ret;
    }
    
    switch( cmd )
    {
        case D_IOCTL_SET_ACTIVE_SENSOR:
            if( copy_from_user(&g_ActiveSensors, argp, sizeof(g_ActiveSensors)) )
            {
                printk( KERN_ERR "[D_IOCTL_SET_ACTIVE_SENSOR] copy_to_user() Err!!\n" );
                return -EFAULT;
            }
            wake_up_interruptible( &g_active_queue );
            ret = 0;
            break;
            
        case D_IOCTL_GET_ACTIVE_SENSOR:
            if( copy_to_user(argp, &g_ActiveSensors, sizeof(g_ActiveSensors)) )
            {
                printk( KERN_ERR "[D_IOCTL_GET_ACTIVE_SENSOR] copy_to_user() Err!!\n" );
                return -EFAULT;
            }
            ret = 0;
            break;

        case D_IOCTL_GET_DELAY_TIME:
            ret = get_sensors_delay( arg );
            break;

        case D_IOCTL_SET_DELAY_TIME:
            ret = set_sensors_delay( arg );
            break;

        case D_IOCTL_WAIT_GET_ACTIVE_SENSOR:
            wait_event_interruptible( g_active_queue, g_ActiveSensors != 0 );
            if( copy_to_user(argp, &g_ActiveSensors, sizeof(g_ActiveSensors)) )
            {
                printk( KERN_ERR "[D_IOCTL_WAIT_GET_ACTIVE_SENSOR] copy_to_user() Err!!\n" );
                return -EFAULT;
            }
            ret = 0;
            break;

        default:
            break;
    }

    return ret;
}

static struct file_operations sensors_common_fops = {
    .owner = THIS_MODULE,
    .open = sensors_common_open,
    .release = sensors_common_release,
    .ioctl = sensors_common_ioctl,
};

static struct miscdevice sensors_common_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "sensors_common",
    .fops = &sensors_common_fops,
};

static int __init sensors_common_init(void)
{
    printk(KERN_INFO "sensors_common_init: " sensors_common_DRV_NAME " driver ver." DRIVER_VERSION "\n" );
    
    init_waitqueue_head( &g_active_queue );
    spin_lock_init( &time_spin_lock );
    
    return misc_register(&sensors_common_device);
}

static void __exit sensors_common_exit(void)
{
    misc_deregister(&sensors_common_device);
}

MODULE_AUTHOR("NEC Communication Systems Co.,Ltd");
MODULE_DESCRIPTION("Sensors Common driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

module_init(sensors_common_init);
module_exit(sensors_common_exit);
