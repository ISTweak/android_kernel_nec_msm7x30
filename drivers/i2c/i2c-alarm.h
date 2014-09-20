/**********************************************************************
* File Name: drivers/i2c/i2c-alarm.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/


#ifndef _I2C_ALARM_H
#define _I2C_ALARM_H


#define I2C_ALARM_BUS_BUSY              ( 0x01 )
#define I2C_ALARM_BUFFER_FULL           ( 0x02 )
#define I2C_ALARM_TRANS_TIMEOUT         ( 0x03 )
#define I2C_ALARM_TRANS_FAILURE         ( 0x04 )
#define I2C_ALARM_SLAVE_NOT_CONNECT     ( 0x05 )


extern void i2c_notify_alarm( int slave_addr, int info, int opt );

#endif 


