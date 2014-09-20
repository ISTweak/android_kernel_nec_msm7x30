/**********************************************************************
* File Name: arch/arm/mach-msm/qdsp5v2/Diag_acad.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/
#ifndef _DIAG_ACAD_H
#define _DIAG_ACAD_H





















#include <linux/types.h>
#include <linux/ioctl.h>
#include <asm/sizes.h>

#define DIAG_ACAD_MAJOR                0           
#define DIAG_ACAD_DEVICE_NAME        "diagACAD"    


#define DIAG_ACAD_IOCTL_MAGIC         'a'          
#define DIAG_ACAD_IOCTL_15   _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x02, diag_acad_ctrl )
#define DIAG_ACAD_IOCTL_16   _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x03, diag_acad_ctrl )
#define DIAG_ACAD_IOCTL_21   _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x04, diag_acad_ctrl )
#define DIAG_ACAD_IOCTL_0201 _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x05, diag_acad_ctrl )
#define DIAG_ACAD_IOCTL_0202 _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x06, diag_acad_ctrl )




#define DIAG_ACAD_IOCTL_25   _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x07, diag_acad_ctrl )



#define DIAG_ACAD_IOCTL_0203 _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x08, diag_acad_ctrl )
#define DIAG_ACAD_IOCTL_0204 _IOW (DIAG_ACAD_IOCTL_MAGIC, 0x09, diag_acad_ctrl )



#define DIAG_ACAD_IOCTL_0205 _IOWR(DIAG_ACAD_IOCTL_MAGIC, 0x10, diag_acad_ctrl )	
#define DIAG_ACAD_IOCTL_0206 _IOWR(DIAG_ACAD_IOCTL_MAGIC, 0x11, diag_acad_ctrl )	







#define DIAG_AK7837A_DRV_POWER_OFF            0x00            
#define DIAG_AK7837A_DRV_POWER_ON             0x01            
#define DIAG_AK7837A_DRV_POWER_DEBUG_OFF      0xF0            
#define DIAG_AK7837A_DRV_POWER_DEBUG_ON_01    0xF1            
#define DIAG_AK7837A_DRV_POWER_DEBUG_ON_02    0xF2            
#define DIAG_AK7837A_DRV_POWER_DEBUG_ON_03    0xF3            
#define DIAG_AK7837A_DRV_POWER_DEBUG_ON_04    0xF4            
#define DIAG_AK7837A_DRV_POWER_DEBUG_ON_05    0xF5            
#define DIAG_AK7837A_DRV_POWER_DEBUG_ONP06    0xF6            







typedef  struct {
    unsigned char tx_dev;    
    unsigned char rx_dev;    
    unsigned char type;      




}diag_acad_qtr_action;




typedef  struct {
    unsigned char path;    







}diag_acad_qtr_loopback;




typedef  struct {
    unsigned char bias;    
}diag_acad_pm_hsedbias;







typedef struct {
    unsigned char   power;                       
                                                 
                                                 
} diag_acad_ak7837a_drive;








typedef  struct {
    diag_acad_qtr_action       act;         
    diag_acad_qtr_loopback     lb;          
    diag_acad_pm_hsedbias      hsed;        



    diag_acad_ak7837a_drive    ak7837a_drv; 



    unsigned char              req[16];     
    unsigned char              rsp[16];     


    signed char                adjust;      



    unsigned int               devState;    


}diag_acad_ctrl;






#endif 

