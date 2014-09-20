


#ifndef _AK7837A_I2C_DRIVER_H
#define _AK7837A_I2C_DRIVER_H
/*===========================================================================
 FILENAME : ak7837a_i2c_driver.h

 Copyright (C) 2010 NEC Corporation.
 No permission to use, copy, modify and distribute this software
 and its documentation for any purpose is granted.
 This software is provided under applicable license agreement only.
===========================================================================*/
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/

















#include <linux/types.h>
#include <linux/i2c.h>






#define AK7837A_I2C_DEVICE_NAME ("AK7837A I2C")   
#define AK7837A_I2C_SLAVE_ADDRESS (0x10)          
                                                  




struct ak7837a {
    struct i2c_client *client ;           
    bool   inuse ;                        
} ;

struct ak7837a_platform_data {
    u32  (*ak7837a_setup)( void ) ;       
    void (*ak7837a_shutdown)( void ) ;    
} ;






int ak7837a_read( u8 reg , u8* val ) ;  
int ak7837a_write( u8 reg , u8 val ) ;  

#endif	



