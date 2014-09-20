/**********************************************************************
* File Name: drivers/i2c/i2c-alarm.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/


#include <linux/kernel.h>
#include "i2c-alarm.h"

typedef struct i2c_alarm {
    int slave_addr;     
    int alarm_id;       
} i2c_alarm_t;

void i2c_notify_alarm(int slave_addr, int info, int opt)
{
    int i = 0;
    static const i2c_alarm_t i2c_alarm_table[] = {
            
        { 0x1A            , 0x60           }, 
        { 0x3C            , 0x60           }, 
        { 0x44            , 0x61           }, 
        { 0x6C            , 0x62           }, 
        { 0x60            , 0x63           }, 
        { 0x1C            , 0x64           }, 
        { 0x76            , 0x65           }, 
        { 0x10            , 0x66           }, 
        { 0x25            , 0x67           }, 
        { 0x00            , 0xff           }
    };
    
    while ( i2c_alarm_table[i].slave_addr != 0x00 ) {
        if ( slave_addr == i2c_alarm_table[i].slave_addr ) {
            printk( KERN_ERR "[T][ARM]Event:0x%02X Info:0x%02X",
                    i2c_alarm_table[i].alarm_id, info );
            break;
        }
        i++;
    }
    
    return;
} 


