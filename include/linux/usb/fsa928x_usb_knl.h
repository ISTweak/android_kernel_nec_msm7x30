/**********************************************************************
* File Name: include/linux/usb/fsa928x_usb_knl.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/

















#ifndef FSA928X_USB_DRV_H
#define FSA928X_USB_DRV_H




#define FSA928X_OK 0    
#define FSA928X_NG -1   

#define INT_OVP_OCP_COUNT (5)   




#define FSA928X_CONTROL_ERRATA_MASKB                  (0x01)       


#define FSA928X_INTERRUPT1_ATTACH_MASKB               (0x01)      
#define FSA928X_INTERRUPT1_DETACH_MASKB               (0x02)      
#define FSA928X_INTERRUPT1_OCP_OVP_MASKB              (0x60)      
#define FSA928X_INTERRUPT1_RECOVERY_MASKB             (0x80)       
#define FSA928X_INTERRUPT2_ACCESSORY_ATTACH_MASKB     (0x02)      

#define FSA928X_ADC_VALUE_CDP_DCP_HOST      (0x1f)    
#define FSA928X_ADC_VALUE_MCPC_MODE1        (0x19)    
#define FSA928X_ADC_VALUE_MCPC_MODE1_2      (0x18)     
#define FSA928X_ADC_VALUE_MCPC_MODE2        (0x1e)    
#define FSA928X_ADC_VALUE_MCPC_MODE3        (0x1c)    
#define FSA928X_ADC_VALUE_MCPC_MODE3_2      (0x1d)     
#define FSA928X_ADC_VALUE_VE333_DEVICE    (0x0e)    
#define FSA928X_ADC_VALUE_SENDEND_KEY       (0x11)    
#define FSA928X_ADC_VALUE_SENDEND_KEY_2     (0x10)    


#define FSA928X_DEVTYPE1_0K_VBUS_MASKB       (0x80)    
#define FSA928X_DEVTYPE1_DCP_MASKB           (0x40)    
#define FSA928X_DEVTYPE1_CDP_MASKB           (0x20)    
#define FSA928X_DEVTYPE1_CARKIT_MASKB        (0x10)    
#define FSA928X_DEVTYPE1_UART_MASKB          (0x08)    
#define FSA928X_DEVTYPE1_SDP_MASKB           (0x04)    
#define FSA928X_DEVTYPE1_AUDIOTYPE_MASKB     (0x01)    
#define FSA928X_DEVTYPE2_TTY_MASKB           (0x20)    
#define FSA928X_DEVTYPE2_UARTBOOT_OFF_MASKB  (0x08)    
#define FSA928X_DEVTYPE2_UARTBOOT_ON_MASKB   (0x04)    
#define FSA928X_DEVTYPE2_USBBOOT_OFF_MASKB   (0x02)    
#define FSA928X_DEVTYPE2_USBBOOT_ON_MASKB    (0x01)    



#define FSA928X_MANUAL_SW1_DM_OPEN_MASKB     (0x00)    
#define FSA928X_MANUAL_SW1_DM_HOST_MASKB     (0x20)    
#define FSA928X_MANUAL_SW1_DM_AUDI_L_MASKB   (0x40)    
#define FSA928X_MANUAL_SW1_DM_TXD_MASKB      (0x60)    

#define FSA928X_MANUAL_SW1_DP_OPEN_MASKB     (0x00)    
#define FSA928X_MANUAL_SW1_DP_HOST_MASKB     (0x04)    
#define FSA928X_MANUAL_SW1_DP_AUDI_R_MASKB   (0x08)    
#define FSA928X_MANUAL_SW1_DP_RXD_MASKB      (0x0C)    

#define FSA928X_MANUAL_SW1_VBUS_BIT_MASKB    (0x02)    
#define FSA928X_MANUAL_SW1_VBUS_OUT_MASKB    (0x03)    
#define FSA928X_MANUAL_SW1_VBUS_MIC_SET      (0x02)    
















































typedef enum{
    FSA928X_VBUSIN_OPEN     = 0,    
    FSA928X_VBUSIN_CON_VCHG = 1,    
    FSA928X_VBUSIN_CON_MIC  = 2     
}fsa928x_vbus_in_path_enum;



typedef enum{
    USB_HEADSET_STEREO = 0, 
    USB_HEADSET_MONO,       
}usb_headset_stereo_mono_enum;



typedef struct{
    unsigned char    address;                    
    unsigned char    value;                      
}fsa928x_reg_type;



typedef struct{
    fsa928x_reg_type    interrupt1;               
    fsa928x_reg_type    interrupt2;               
}fsa9280a_interrupt_info_type;

typedef struct{
    fsa928x_reg_type    adc;                      
    fsa928x_reg_type    device_type1;             
    fsa928x_reg_type    device_type2;             
    fsa928x_reg_type    vbus_state;               
    fsa928x_reg_type    control;                   
}fsa9280a_identify_device_info_type;

typedef struct{
    fsa928x_reg_type    manual_sw1;               
}fsa9280a_switch_path_info_type;

typedef struct{
    fsa928x_reg_type    interrupt_mask1;          
    fsa928x_reg_type    interrupt_mask2;          
    fsa928x_reg_type    control;                  
    fsa928x_reg_type    reset;                     
}fsa9280a_init_info_type;

typedef struct{
    fsa9280a_interrupt_info_type          interrupt_info;          
    fsa9280a_identify_device_info_type    identify_device_info;    
    fsa9280a_switch_path_info_type        switch_path_info;        
}fsa9280a_read_device_info_type;

typedef struct{
    fsa9280a_switch_path_info_type    switch_path_info;            
    fsa9280a_init_info_type           init_info;                   
}fsa9280a_write_device_info_type;








































typedef struct{
    usb_headset_stereo_mono_enum stereo_mono_type;
}usb_headset_info_type;



void fsa928x_init( void );                                        
void fsa928x_detect_intb( void );                                 
int fsa928x_main( void );                                         
int fsa928x_read_interrupt_info( void );                          
int fsa928x_read_switch_path_info( void );                        
int fsa928x_read_device_id_info( void );                          
int fsa928x_set_manual_switch_all_open( void );                   

int fsa928x_set_manual_switch_detected_device( void );           

void fsa928x_set_path_vbus_in( fsa928x_vbus_in_path_enum  vbus_in_path );   
int fsa928x_switch_path( void );                                  

int fsa928x_detect_mic( void );                                   


#endif


