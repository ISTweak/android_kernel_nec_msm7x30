/**********************************************************************
* File Name: drivers/i2c/chips/i2c_fsa928x.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/




















#include <linux/i2c.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/freezer.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/timer.h> 
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include "linux/i2c/i2c_fsa928x.h"

#include <linux/usb/fsa928x_usb_knl.h>




static int __devinit fsa928x_i2c_probe( struct i2c_client* client , const struct i2c_device_id* id ) ;


static int __devexit fsa928x_i2c_remove( struct i2c_client* client ) ;


static int __init fsa928x_i2c_init( void ) ;


static void __exit fsa928x_i2c_exit( void ) ;



struct fsa928x_i2c_data fsa928x_modules ;
static struct i2c_client *this_client;
static struct i2c_device_id fsa928x_id_table[ 1 ] = {
    { FSA928X_I2C_DEVICE_NAME , 0x00 }
} ;

static struct i2c_driver fsa928x_driver = {
    .driver = {
        .owner    = THIS_MODULE ,
        .name    = FSA928X_I2C_DEVICE_NAME ,
    } ,
    .id_table    = fsa928x_id_table ,
    .probe        = fsa928x_i2c_probe ,
    .remove        = fsa928x_i2c_remove ,
} ;


#define FSA928X_ADDRESS (fsa928x_modules.client->addr)

MODULE_DESCRIPTION( FSA928X_I2C_DEVICE_NAME ) ;
MODULE_ALIAS( "platform:fsa928x i2c driver" ) ;
MODULE_LICENSE( "GPL" ) ;
MODULE_VERSION( "0.1" ) ;
MODULE_DEVICE_TABLE( i2c , fsa928x_id_table ) ;


module_init( fsa928x_i2c_init ) ;


module_exit( fsa928x_i2c_exit ) ;
EXPORT_SYMBOL( fsa928x_i2c_read ) ;
EXPORT_SYMBOL( fsa928x_i2c_write ) ;

unsigned char  g_usb_intb_flags;




















static irqreturn_t fsa928x_irq_handler(int irq, void *dev_id)
{
	disable_irq_nosync(this_client->irq);

	
	fsa928x_detect_intb( );

	enable_irq(this_client->irq);
	return IRQ_HANDLED;
}




















static u32 fsa928x_irq_setup(struct i2c_client *client)
{
	int rc = 0;
	struct fsa928x_i2c_data *data;

	data = i2c_get_clientdata(client);
	rc = request_threaded_irq(client->irq, NULL, fsa928x_irq_handler, 
			IRQF_TRIGGER_FALLING, FSA928X_I2C_DEVICE_NAME, data);

	printk(KERN_INFO "[FSA928X] fsa928x_irq_setup: rc=%d\n", rc);

	return rc;
}


 







static int __devinit fsa928x_i2c_probe( struct i2c_client* client , const struct i2c_device_id* id )
{
    struct fsa928x_platform_data* pdata_p ;    
    struct fsa928x_i2c_data* fsa928x_p ;       
    int status ;                               

    
    
    pdata_p = client->dev.platform_data ;
    fsa928x_p = &fsa928x_modules ;
    fsa928x_p->client = client ;
    this_client = client;
    
    if ( pdata_p == NULL ) {
        printk( "FSA928x I2C Probe(ERROR 01)\n" ) ;
		dev_dbg( &client->dev , "no platform data?\n" ) ;

        status = -EINVAL ;
        return ( status ) ;
    }

    
    if ( i2c_check_functionality( client->adapter , I2C_FUNC_I2C ) == 0 ) {
        printk( "FSA928x I2C Probe(ERROR 02)\n" ) ;
		dev_dbg( &client->dev , "can't talk I2C?\n" ) ;

        status = -EIO ;
        return ( status ) ;
    }

    
    if ( fsa928x_p->inuse == true ) {
        printk( "FSA928x I2C Probe(ERROR 03)\n" ) ;
		dev_dbg( &client->dev , "driver already in use\n" ) ;

        status = -EBUSY ;
        return ( status ) ;
    }

    
    if ( fsa928x_p->client == NULL ) {
        printk( "FSA928x I2C Probe(ERROR 04)\n" ) ;
		dev_err( &fsa928x_p->client->dev , "can't attach client\n" ) ;

        status = -ENOMEM ;
    } else {
        

        strlcpy( fsa928x_p->client->name , id->name , sizeof( fsa928x_p->client->name ) ) ;

        
        fsa928x_p->inuse = true ;

        i2c_set_clientdata( client , pdata_p ) ;
        if ( pdata_p->fsa928x_setup != NULL ) {
            pdata_p->fsa928x_setup() ;
        }


        fsa928x_init();                                   

        fsa928x_irq_setup(client);


		enable_irq_wake(client->irq);


        printk( "FSA928x I2C Probe(OK)\n" ) ;

        status = 0 ;
    }
    return ( status ) ;
}

 





static int __devexit fsa928x_i2c_remove( struct i2c_client* client )
{
    struct fsa928x_i2c_data* fsa928x_p ;       
    fsa928x_p = &fsa928x_modules ;
    fsa928x_p->inuse = false ;                 

    printk( "FSA928x I2C remove(OK)\n" ) ;

    i2c_release_client(client);

    return ( 0 ) ;
}

 





static int __init fsa928x_i2c_init( void )
{
    struct fsa928x_i2c_data* fsa928x_p ;       
    fsa928x_p = &fsa928x_modules ;
    fsa928x_p->inuse = false;                  
    printk( "FSA928x I2C Init(OK)\n" ) ;

    return ( i2c_add_driver( &fsa928x_driver ) ) ;
}

 





static void __exit fsa928x_i2c_exit( void )
{
    i2c_del_driver( &fsa928x_driver ) ;

    printk( "FSA928x I2C Exit(OK)\n" ) ;
}










int fsa928x_i2c_read( unsigned char reg , unsigned char* data )
{
    struct i2c_msg msgs[] =                     
    {
        {   
            .addr = FSA928X_ADDRESS,            
            .flags = 0,                         
            .len = 1,                           
            .buf = &reg,                        
        },
        {   
            .addr = FSA928X_ADDRESS,            
            .flags = I2C_M_RD,                  
            .len = 1,                           
            .buf = data,                        
        },                                      
    };
    int ret = FSA928X_I2C_TRANSFER_NG;          
    
    if ( i2c_transfer(fsa928x_modules.client->adapter, msgs, 2 ) < 0 ) 
    {   
        printk(KERN_ERR "FSA928x I2C read : transfer error\n");
    }
    else
    {
        ret = FSA928X_I2C_TRANSFER_OK;
    }

    return ( ret );
}









int fsa928x_i2c_write( unsigned char reg , unsigned char value )
{
    unsigned char data[2];               

    struct i2c_msg msg[] =              
    {
        {
            .addr = FSA928X_ADDRESS,    
            .flags = 0,                 
            .len = 2,                   
            .buf = data,                
        },
    };
    int ret = FSA928X_I2C_TRANSFER_NG;  
    
    data[0] = reg;
    data[1] = value;
    
    if ( i2c_transfer(fsa928x_modules.client->adapter, msg, 1 ) < 0) 
    {   
        printk(KERN_ERR "FSA928x I2C write: transfer error\n");
    }else{
        ret = FSA928X_I2C_TRANSFER_OK;
    }
    return ( ret );
}


