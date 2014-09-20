/**********************************************************************
* File Name: arch/arm/mach-msm/qdsp5v2/yda160_i2c_driver.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/
#ifndef _YDA160_I2C_DRIVER_H
#define _YDA160_I2C_DRIVER_H

#include <linux/types.h>
#include <linux/i2c.h>








#define YDA160_I2C_SLAVE_ADDRESS (0x6C)


#define YDA160_I2C_DEVICE_NAME ("YDA160 i2c driver")







struct yda160 {
	struct i2c_client *client ;	
	bool inuse ;				
} ;

struct yda160_platform_data {
	u32 (*yda160_setup)( void ) ;		
	void (*yda160_shutdown)( void ) ;	
} ;








int yda160_read( u8 reg , u8* value ) ;






int yda160_write( u8 reg , u8 value ) ;

#endif	
