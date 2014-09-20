


/*===========================================================================
 FILENAME : ak7837a_i2c_driver.c

 Copyright (C) 2010 NEC Corporation.
 No permission to use, copy, modify and distribute this software
 and its documentation for any purpose is granted.
 This software is provided under applicable license agreement only.
===========================================================================*/
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/




















#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/err.h>

#include <linux/i2c.h>
#include <linux/gpio.h>


#include <linux/delay.h>


#include "linux/audio_compile_switch_apps.h"
#include <ak7837a_i2c_driver.h>







static int __devinit ak7837a_probe( struct i2c_client* client , const struct i2c_device_id* id ) ;


static int __devexit ak7837a_remove( struct i2c_client* client ) ;


static int __init ak7837a_init( void ) ;   


static void __exit ak7837a_exit( void ) ;






struct ak7837a ak7837a_modules ;

static struct i2c_device_id ak7837a_id_table[ 1 ] = {
    { AK7837A_I2C_DEVICE_NAME , 0x00 }
} ;

static struct i2c_driver ak7837a_driver = {
    .driver = {



        .name   = AK7837A_I2C_DEVICE_NAME ,
    } ,
    .id_table   = ak7837a_id_table ,
    .probe      = ak7837a_probe ,
    .remove     = __devexit_p( ak7837a_remove ) ,
} ;





#define AK7837A_ADDRESS (ak7837a_modules.client->addr)

MODULE_DESCRIPTION( AK7837A_I2C_DEVICE_NAME ) ;
MODULE_ALIAS( "platform:AK7837A I2C DRIVER" ) ;
MODULE_LICENSE( "Dual BSD/GPL" ) ;
MODULE_VERSION( "0.1" ) ;
MODULE_DEVICE_TABLE( i2c , ak7837a_id_table ) ;

EXPORT_SYMBOL( ak7837a_read ) ;  
EXPORT_SYMBOL( ak7837a_write ) ; 
module_init( ak7837a_init ) ;    
module_exit( ak7837a_exit ) ;    




















int ak7837a_read( u8 reg , u8* val )
{
    int ret ;                      

    struct i2c_msg msg[ 2 ] = {    
        {    
            .addr = AK7837A_ADDRESS ,     
            .flags = 0 ,                  
            .buf = &reg ,                 
            .len = 1 ,                    
        } ,
        {    
            .addr = AK7837A_ADDRESS ,     
            .flags = I2C_M_RD ,           
            .buf = val ,                  
            .len = 1 ,                    
        }
    } ;










    
    ret = i2c_transfer( ak7837a_modules.client->adapter , &msg[0] , 1 ) ;
    if ( 0 > ret ) {
        printk( KERN_ERR "AK7837A I2C Read ERROR01\n" ) ;
    } else {
        
        (*val) = 0xff ;

        
        ret = i2c_transfer( ak7837a_modules.client->adapter , &msg[1] , 1 ) ;
        if ( 0 > ret ) {
            printk( KERN_ERR "AK7837A I2C Read ERROR02\n" ) ;
        }
    }





    return ( ret ) ;
}




















int ak7837a_write( u8 reg , u8 val )
{
    int ret ;                       
    u8  data[2] ;                   

    struct i2c_msg msg = {          
        .addr = AK7837A_ADDRESS ,   
        .flags = 0 ,                
        .buf = &data[0] ,           
        .len = 2                    
    } ;

    
    data[0] = reg ;
    data[1] = val ;











    
    ret = i2c_transfer( ak7837a_modules.client->adapter , &msg , 1 ) ;
    if ( 0 > ret ) {
        printk( KERN_ERR "AK7837A I2C Write ERROR\n" ) ;
    }





    return ( ret ) ;
}





















static int __devinit ak7837a_probe( struct i2c_client* client , const struct i2c_device_id* id )
{
    struct ak7837a_platform_data* pdata ;    
    struct ak7837a* ak7837a ;                
    int    status ;                          
    struct platform_device* pdev ;

    
    pdata = client->dev.platform_data ;
    ak7837a = &ak7837a_modules ;
    ak7837a->client = client ;

    
    if ( NULL == pdata ) {
        printk( KERN_ERR "AK7837A I2C Probe(ERROR:no platform data)\n" ) ;
        return ( -EINVAL ) ;
    }

    
    if ( 0 == i2c_check_functionality( client->adapter , I2C_FUNC_I2C ) ) {
        printk( KERN_ERR "AK7837A I2C Probe(ERROR:can't talk I2C)\n" ) ;
        return ( -EIO ) ;
    }

    
    if ( true == ak7837a->inuse ) {
        printk( KERN_ERR "AK7837A I2C Probe(ERROR:driver already in use)\n" ) ;
        return ( -EBUSY ) ;
    }

    
    if ( NULL == ak7837a->client ) {
        printk( KERN_ERR "AK7837A I2C Probe(ERROR:can't attach client)\n" ) ;
        return ( -ENOMEM ) ;
    }

    strlcpy( ak7837a->client->name , id->name , sizeof( ak7837a->client->name ) ) ;

    
    ak7837a->inuse = true ;

    i2c_set_clientdata( client , pdata ) ;

    pdev = platform_device_alloc( AK7837A_I2C_DEVICE_NAME , -1 ) ;


    if( NULL == pdev ) {
        printk( KERN_ERR "AK7837A I2C Probe(ERROR:can't alloc AK7837A_I2C_DEVICE_NAME) \n" ) ;
        return ( -ENOMEM ) ;
    }


    pdev->dev.parent = &ak7837a->client->dev ;
    platform_set_drvdata( pdev , ak7837a ) ;

    if ( NULL != pdata ) {
        status = platform_device_add_data( pdev , pdata , sizeof( struct ak7837a_platform_data ) ) ;
        status = platform_device_add( pdev ) ;
    }

    
    if ( NULL != pdata->ak7837a_setup ) {
        pdata->ak7837a_setup() ;
    }


    mdelay( 50 );






    return ( 0 ) ;
}




















static int __devexit ak7837a_remove( struct i2c_client* client )
{
    struct ak7837a_platform_data* pdata ;
    struct ak7837a* ak7837a ;

    ak7837a = &ak7837a_modules ;

    if ( NULL != ak7837a->client ) {
        i2c_unregister_device( ak7837a->client ) ;
        ak7837a->client = NULL ;

        
        pdata = client->dev.platform_data ;
        if ( NULL != pdata->ak7837a_shutdown ) {
            pdata->ak7837a_shutdown() ;
        }





    }

    return ( 0 ) ;
}




















static int __init ak7837a_init( void )
{




    return ( i2c_add_driver( &ak7837a_driver ) ) ;
}



















static void __exit ak7837a_exit( void )
{
    i2c_del_driver( &ak7837a_driver ) ;




}



