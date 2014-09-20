/**********************************************************************
* File Name: include/linux/i2c/i2c_fsa928x.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/








#ifndef I2C_FSA928X_H
#define I2C_FSA928X_H

#include <linux/i2c.h>
#include <linux/ioctl.h>



#define FSA928X_I2C_TRANSFER_OK 0
#define FSA928X_I2C_TRANSFER_NG -1


#define FSA928X_I2C_SLAVE_ADDRESS         (0x25)


#define FSA928X_I2C_DEVICE_NAME           ("FSA928x i2c driver")

#define FSA928X_DEVICE_ID_ADDRESS         (0x01)




#define FSA9280_CONTROL_ADDRESS           (0x02)


#define FSA9280_INTERRUPT1_ADDRESS        (0x03)
#define FSA9280_INTERRUPT2_ADDRESS        (0x04)


#define FSA9280_INTERRUPT_MASK1_ADDRESS   (0x05)
#define FSA9280_INTERRUPT_MASK2_ADDRESS   (0x06)


#define FSA9280_ADC_ADDRESS               (0x07)


#define FSA9280_TIMING_SET1_ADDRESS       (0x08)
#define FSA9280_TIMING_SET2_ADDERSS       (0x09)


#define FSA9280_DEVICE_TYPE1_ADDRESS      (0x0a)
#define FSA9280_DEVICE_TYPE2_ADDRESS      (0x0b)


#define FSA9280_BUTTON1_ADDRESS           (0x0c)
#define FSA9280_BUTTON2_ADDRESS           (0x0d)


#define FSA9280_CAR_KIT_STATUS_ADDRESS    (0x0e)


#define FSA9280_MANUALSW1_ADDRESS         (0x13)
#define FSA9280_MANUALSW2_ADDRESS         (0x14)


#define FSA9280_RESET_ADDRESS             (0x1b)


#define FSA9280_VBUS_VALID_STATUS_ADDRESS (0x1d)


#define FSA9285_DEVICE_ID_ADDRESS         (0x01)


#define FSA9285_CONTROL_ADDRESS           (0x02)


#define FSA9285_INTERRUPT_ADDRESS         (0x03)


#define FSA9285_INTERRUPT_MASK_ADDRESS    (0x05)


#define FSA9285_ADC_ADDRESS               (0x07)


#define FSA9285_TIMING_SET_ADDRESS        (0x08)


#define FSA9285_STATUS_ADDERSS            (0x09)


#define FSA9285_DEVICE_TYPE_ADDRESS       (0x0a)


#define FSA9285_DAC_SAR_ADDRESS           (0x0b)


#define FSA9285_MANUAL_SWITCH_ADDRESS     (0x13)


#define FSA9285_MANUAL_CHG_CTRL_ADDRESS   (0x14)


#define FSA9280A_DEVICEID_VALUE           (0x00) 
#define FSA9281_DEVICEID_VALUE            (0x08) 
#define FSA9285_DEVICEID_VALUE            (0x10) 

#define FSA9280_REGULATE_SWITCH_ENABLE_MASKB  (0xfb) 
#define FSA9280_REGULATE_SWITCH_DISABLE_MASKB (0x04) 
#define FSA9285_REGULATE_SWITCH_ENABLE_MASKB  (0xeb) 
#define FSA9285_REGULATE_SWITCH_DISABLE_MASKB (0x14) 

#define FSA9280_ADC_VALUE_MCPC_MODE1        (0x19)    
#define FSA9280_ADC_VALUE_MCPC_MODE2        (0x1e)    
#define FSA9280_ADC_VALUE_MCPC_MODE3        (0x1c)    

#define FSA9285_ADC_VALUE_MCPC_MODE1        (0x05)    
#define FSA9285_ADC_VALUE_MCPC_MODE2        (0x01)    
#define FSA9285_ADC_VALUE_MCPC_MODE3        (0x02)    

#define FSA9280_DEVTYPE1_AUDIOTYPE_MASKB     (0x01)    
#define FSA9280_DEVTYPE2_UARTBOOT_OFF_MASKB  (0x08)    
#define FSA9280_DEVTYPE2_UARTBOOT_ON_MASKB   (0x04)    
#define FSA9280_DEVTYPE2_USBBOOT_OFF_MASKB   (0x02)    
#define FSA9280_DEVTYPE2_USBBOOT_ON_MASKB    (0x01)    




#define FSA928X_MANUAL_SW1_DM_OPEN_MASKB     (0x00)    
#define FSA928X_MANUAL_SW1_DM_HOST_MASKB     (0x20)    
#define FSA928X_MANUAL_SW1_DM_AUDI_L_MASKB   (0x40)    
#define FSA928X_MANUAL_SW1_DM_HOST2_MASKB    (0x60)    

#define FSA928X_MANUAL_SW1_DP_OPEN_MASKB     (0x00)    
#define FSA928X_MANUAL_SW1_DP_HOST_MASKB     (0x04)    
#define FSA928X_MANUAL_SW1_DP_AUDI_R_MASKB   (0x08)    
#define FSA928X_MANUAL_SW1_DP_HOST2_MASKB    (0x0C)    
#define FSA928X_MANUAL_SW1_DP_MIC_MASKB      (0x10)    

#define FSA928X_MANUAL_SW1_VBUS_BIT_MASKB    (0x02)    
#define FSA928X_MANUAL_SW1_VBUS_OUT_MASKB    (0x03)    
#define FSA928X_MANUAL_SW1_VBUS_MIC_SET      (0x02)    
#define FSA928X_I2C_PM_GPIO_INTB  (16)         



struct fsa928x_i2c_data {
    struct i2c_client *client ;    
    bool inuse ;                   
} ;

struct fsa928x_platform_data {
    u32  (*fsa928x_setup)( void ) ;       
    void (*fsa928x_shutdown)( void ) ;    

} ;


int fsa928x_i2c_read( unsigned char reg , unsigned char* data ) ;


int fsa928x_i2c_write( unsigned char reg , unsigned char value ) ;
#endif


