/**********************************************************************
* File Name: drivers/usb/gadget/usb_diag_ioctl.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/

















#ifndef USB_DIAG_H
#define USB_DIAG_H

#include <linux/ioctl.h>

#define IOC_MAGIC_USB_DIAG 'u'                        




#define USB_DIAG_REGULATE_SWITCH_ENABLE  0x01         
#define USB_DIAG_REGULATE_SWITCH_DISABLE 0x00         



#define USB_DIAG_START_POLLING           0x00         
#define USB_DIAG_STOP_POLLING            0x11         
#define EARPHONE_POLLING_INTERVAL_TIME   10           



#define USB_DETECT_EARPHONE_SWITCH_START 0x01   
#define USB_DETECT_EARPHONE_SWITCH_STOP  0x00   




#define IOCTL_USB_DIAG_FS_ENUM _IOR(IOC_MAGIC_USB_DIAG, 1, char) 
#define IOCTL_USB_DIAG_HS_ENUM _IOR(IOC_MAGIC_USB_DIAG, 3, char) 




#define IOCTL_USB_DIAG_GET_CONNECT_STATUS   _IOR(IOC_MAGIC_USB_DIAG, 10, char)   
#define IOCTL_USB_DIAG_REGULATE_SWITCH      _IOW(IOC_MAGIC_USB_DIAG, 11, char)   
#define IOCTL_USB_DIAG_GET_REGISTER_VALUE   _IOR(IOC_MAGIC_USB_DIAG, 12, char)   
#define IOCTL_USB_DIAG_SET_REGISTER_VALUE   _IOW(IOC_MAGIC_USB_DIAG, 13, char)   


#define IOCTL_USB_DIAG_DETECT_EARPHONE      _IOWR(IOC_MAGIC_USB_DIAG, 100, char)   


#define IOCTL_USB_GET_HEADSET_INFO          _IOR(IOC_MAGIC_USB_DIAG, 200, char)  



#define IOCTL_USB_SET_DETECT_EARPHONE_SWITCH _IOWR(IOC_MAGIC_USB_DIAG, 201, char) 



#define IOCTL_USB_SET_MIC_DEC_WAITTIME      _IOWR(IOC_MAGIC_USB_DIAG, 202, char) 





#define DEVICE_COUNTS          1    
#define USB_DEV_MAJOR          0    
#define USB_DEV_MINOR          0    

struct usb_diag_ioctl_cmd {
    char rsp_data[1];
};

struct ioctl_cmd {
    char rsp_data[1];
};


typedef enum
{
    USB_DIAG_NOT_AUDIO_CONNECTION,
    USB_DIAG_AUDIO_MODE1_CONNECTION,
    USB_DIAG_AUDIO_MODE2_CONNECTION,
    USB_DIAG_AUDIO_MODE3_CONNECTION,
    USB_DIAG_ERROR_CONNECTION
}usb_diag_connected_audio_device_enum;

typedef enum
{
    USB_DIAG_VBUSIN_OPEN,
    USB_DIAG_VBUSIN_CON_VCHG,
    USB_DIAG_VBUSIN_CON_MIC,
}usb_diag_vbus_in_path_enum;


#endif 
