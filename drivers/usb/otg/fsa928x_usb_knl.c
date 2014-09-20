/**********************************************************************
* File Name: drivers/usb/otg/fsa928x_usb_knl.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/


























































#include <linux/timer.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/workqueue.h> 
#include <asm/unistd.h>
#include <mach/rpc_server_handset.h>

#include <linux/usb/fsa928x_usb_knl.h>
#include <linux/i2c/i2c_fsa928x.h>
#include <linux/gpio.h>            
#include <linux/mfd/pmic8058.h>    
#include <mach/rpc_hsusb.h>    
#include <mach/msm_battery.h>

#include <mach/pmic.h>


#include <linux/wakelock.h>


#define POLLING_INTERVAL_TIME           10               
#define SEND_END_KEY_STABILIZING_TIME   10               
#define INT_OVP_OCP_MAX_COUNT           5                
#define I2C_RETRY_MAX_COUNT             5                

#define I2C_RETRY_MAX2_COUNT           10                



#define WAITTIME_USB_AUDIO_BOOT         200000           



#define WLOCK_TIMEOUT_SEC               10              

    
    

#define OVP_WLOCK_TIMEOUT_SEC           15            

    


#define HS_PRESSED_K            0x00                     
#define HS_HEADSET_SWITCH_K     0x84                     
#define HS_REL_K                0xFF                    

#define FSA928X_ALERM_EVENT 0x50
#define FSA928X_ALERM_INFO_I2C_READ     0x80
#define FSA928X_ALERM_INFO_I2C_WRITE    0x81



#define USB_WALLCHARGER_CHG_CURRENT 1800                
#define USB_WALLCHARGER_NO_CHG_CURRENT 0                


#define MIC_DEC_WAITTIME            0x3c            










static int fsa928x_read_reg( fsa928x_reg_type* reg_p);          
static int fsa928x_write_reg(const fsa928x_reg_type* reg_p);    
static void fsa928x_avoid_errata( void );                       
extern void FSA_set_otg_workable(int enable);                   


void fsa928x_start_adc_polling( void );                            
static void fsa928x_adc_polling_handler( struct work_struct *w );  
void fsa928x_stop_adc_polling( void );                             




fsa9280a_read_device_info_type   g_read_device_info;     
fsa9280a_write_device_info_type  g_write_device_info;    
bool          g_timer_use_flg    = false;                
static struct delayed_work adc_polling_work;             








struct wake_lock g_fsa928x_wlock;



unsigned char g_usb_mic_dec_waittime = MIC_DEC_WAITTIME;               



usb_headset_info_type g_usb_headset_info;               


bool          g_usb_audio_flg    = false;                
bool          g_fsa928x_mic_flg  = false;


bool g_usb_earphone_keypress_flg = false;
bool g_usb_earphone_switch_detect_flg = false;



bool          g_fsa928x_power_supply_flg  = false;      


bool          g_fsa928x_sdp_flg = false;                        

DEFINE_MUTEX(g_fsa928x_usb_main_lock);
extern struct work_struct usbsw_work;                     


DEFINE_MUTEX(g_fsa928x_usb_sendend_key_polling_lock);



extern void usb_sw_otg_set_power(unsigned set_power);          









void fsa928x_init( void )
{
    g_usb_audio_flg   = false;          
    
    
    
    
    g_read_device_info.interrupt_info.interrupt1.address = FSA9280_INTERRUPT1_ADDRESS;
    g_read_device_info.interrupt_info.interrupt1.value = 0x00;
    
    g_read_device_info.interrupt_info.interrupt2.address = FSA9280_INTERRUPT2_ADDRESS;
    g_read_device_info.interrupt_info.interrupt2.value = 0x00;
    
    
    
    g_read_device_info.identify_device_info.adc.address = FSA9280_ADC_ADDRESS;
    g_read_device_info.identify_device_info.adc.value = 0x00;
    
    g_read_device_info.identify_device_info.device_type1.address = FSA9280_DEVICE_TYPE1_ADDRESS;
    g_read_device_info.identify_device_info.device_type1.value = 0x00;
    
    g_read_device_info.identify_device_info.device_type2.address = FSA9280_DEVICE_TYPE2_ADDRESS;
    g_read_device_info.identify_device_info.device_type2.value = 0x00;
    
    g_read_device_info.identify_device_info.vbus_state.address = FSA9280_VBUS_VALID_STATUS_ADDRESS;
    g_read_device_info.identify_device_info.vbus_state.value = 0x00;
    
    
    
    g_read_device_info.switch_path_info.manual_sw1.address = FSA9280_MANUALSW1_ADDRESS;
    g_read_device_info.switch_path_info.manual_sw1.value = 0x00;
    
    
    
    
    g_read_device_info.identify_device_info.control.address = FSA9280_CONTROL_ADDRESS;
    g_read_device_info.identify_device_info.control.value = 0x00;
    

    
    
    
    g_write_device_info.switch_path_info.manual_sw1.address = FSA9280_MANUALSW1_ADDRESS;
    g_write_device_info.switch_path_info.manual_sw1.value = 0x00;
    
    
    
    g_write_device_info.init_info.interrupt_mask1.address = FSA9280_INTERRUPT_MASK1_ADDRESS;
    
    g_write_device_info.init_info.interrupt_mask1.value = 0x9c;  
    
    g_write_device_info.init_info.interrupt_mask2.address = FSA9280_INTERRUPT_MASK2_ADDRESS;
    g_write_device_info.init_info.interrupt_mask2.value = 0x1c;
    
    g_write_device_info.init_info.control.address = FSA9280_CONTROL_ADDRESS;
    g_write_device_info.init_info.control.value = 0x12;

    
    
    g_write_device_info.init_info.reset.address = FSA9280_RESET_ADDRESS;
    g_write_device_info.init_info.reset.value = 0x09;
    
    
    pmic_hsed_enable(PM_HSED_CONTROLLER_1, PM_HSED_ENABLE_OFF);     
    printk(KERN_INFO "%s MIC_BIAS1 = PM_HSED_ENABLE_OFF\n", __func__ );

    
    FSA_set_otg_workable(0);
    

    
    
    fsa928x_write_reg(&g_write_device_info.init_info.reset);
    

    
    if(fsa928x_read_device_id_info() == FSA928X_NG)
    {
        return;
    }
    
    fsa928x_set_manual_switch_detected_device();
    
    
    
    if(fsa928x_write_reg(&g_write_device_info.switch_path_info.manual_sw1) == FSA928X_NG )
    {
        return;
    }

    
    if( fsa928x_write_reg(&g_write_device_info.init_info.interrupt_mask1) == FSA928X_NG )
    {
        return;
    }
    if( fsa928x_write_reg(&g_write_device_info.init_info.interrupt_mask2) == FSA928X_NG )
    {
        return;
    }
    
    if( fsa928x_write_reg(&g_write_device_info.init_info.control) == FSA928X_NG )
    {
        return;
    }
    
    INIT_DELAYED_WORK(&adc_polling_work, fsa928x_adc_polling_handler);   

















    
    wake_lock_init(&g_fsa928x_wlock, WAKE_LOCK_SUSPEND, "fsa928x");
    
}







void fsa928x_detect_intb( void )
{
    schedule_work(&usbsw_work);                   
}
EXPORT_SYMBOL(fsa928x_detect_intb);








int fsa928x_main( void )
{
    mutex_lock(&g_fsa928x_usb_main_lock);

    fsa928x_read_reg( &g_read_device_info.identify_device_info.control );
    
    
    if( (g_read_device_info.identify_device_info.control.value & FSA928X_CONTROL_ERRATA_MASKB) == FSA928X_CONTROL_ERRATA_MASKB )
    {
        fsa928x_avoid_errata();
    }
    

    
    if( fsa928x_read_interrupt_info() == FSA928X_NG )
    {
        mutex_unlock(&g_fsa928x_usb_main_lock);
        return FSA928X_NG;
    }
    
    if( fsa928x_read_switch_path_info() == FSA928X_NG )
    {
        mutex_unlock(&g_fsa928x_usb_main_lock);
        return FSA928X_NG;
    }
    else
    {
       g_write_device_info.switch_path_info.manual_sw1.value = g_read_device_info.switch_path_info.manual_sw1.value;
    }   

    
    
        
        
        if((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_OCP_OVP_MASKB) != 0)
        {
        printk(KERN_INFO "FSA928x_main:OVP/OCP Interrupt Interrupt1 register = 0x%02x, Interrupt2 register = 0x%02x!\n",
                     g_read_device_info.interrupt_info.interrupt1.value, g_read_device_info.interrupt_info.interrupt2.value);
            wake_lock_timeout(&g_fsa928x_wlock, (OVP_WLOCK_TIMEOUT_SEC * HZ) );    
            
            pm_usb_ovp_notify(true);
        }
    
    
    
    
    if((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_DETACH_MASKB) == FSA928X_INTERRUPT1_DETACH_MASKB)
    {
        printk(KERN_INFO "FSA928x_main:Detach Interrupt Interrupt1 register = 0x%02x, Interrupt2 register = 0x%02x!\n",
							g_read_device_info.interrupt_info.interrupt1.value, g_read_device_info.interrupt_info.interrupt2.value);


        
        
        pmic_hsed_enable( PM_HSED_CONTROLLER_1, PM_HSED_ENABLE_OFF );
        printk(KERN_INFO "%s MIC_BIAS1 = PM_HSED_ENABLE_OFF\n", __func__ );
        

        
        
        
        if( g_fsa928x_power_supply_flg == true )
        {
            wake_lock_timeout(&g_fsa928x_wlock, (WLOCK_TIMEOUT_SEC * HZ) );
            printk(KERN_INFO "%s : call wake_lock_timeout timeout = %d sec\n", __func__, WLOCK_TIMEOUT_SEC);
        }
        

        
        if( fsa928x_set_manual_switch_all_open() == FSA928X_NG )
        {
            mutex_unlock(&g_fsa928x_usb_main_lock);
            return FSA928X_NG;
        }

        
        pm_usb_ovp_notify(false);
    
        
        g_fsa928x_sdp_flg = false;
        printk(KERN_INFO "%s: g_fsa928x_sdp_flg = false \n", __func__);
        
            
    }
    else if(((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_ATTACH_MASKB ) == FSA928X_INTERRUPT1_ATTACH_MASKB ) ||
             ((g_read_device_info.interrupt_info.interrupt2.value & FSA928X_INTERRUPT2_ACCESSORY_ATTACH_MASKB ) == FSA928X_INTERRUPT2_ACCESSORY_ATTACH_MASKB ))
    {
        printk(KERN_INFO "FSA928x_main:Attach Interrupt Interrupt1 register = 0x%02x, Interrupt2 register = 0x%02x!\n",
                            g_read_device_info.interrupt_info.interrupt1.value, g_read_device_info.interrupt_info.interrupt2.value);

        
        if( fsa928x_read_device_id_info() == FSA928X_NG )
        {
            mutex_unlock(&g_fsa928x_usb_main_lock);
            return FSA928X_NG;
        }
        
        
        
        if( (g_read_device_info.identify_device_info.vbus_state.value & FSA928X_MANUAL_SW1_VBUS_BIT_MASKB) == FSA928X_MANUAL_SW1_VBUS_BIT_MASKB )
        {
            g_fsa928x_power_supply_flg = true;  
            
            wake_lock_timeout(&g_fsa928x_wlock, (WLOCK_TIMEOUT_SEC * HZ) );
            printk(KERN_INFO "%s : call wake_lock_timeout timeout = %d sec\n", __func__, WLOCK_TIMEOUT_SEC);
            
        }
        else
        {
            g_fsa928x_power_supply_flg = false; 
        }
    
        printk(KERN_INFO "%s:g_fsa928x_power_supply_flg = %d\n", __func__, g_fsa928x_power_supply_flg);
        
        
        
        
        if( fsa928x_set_manual_switch_detected_device() == FSA928X_NG)
        {
            mutex_unlock(&g_fsa928x_usb_main_lock);
            return FSA928X_NG;
        }
        
    }
    else
    {
        mutex_unlock(&g_fsa928x_usb_main_lock);
        return FSA928X_NG;
    }
    
    
    if(g_read_device_info.switch_path_info.manual_sw1.value != g_write_device_info.switch_path_info.manual_sw1.value)
    {   
         
        if( fsa928x_switch_path() == FSA928X_NG )
        {
            mutex_unlock(&g_fsa928x_usb_main_lock);
            return FSA928X_NG;
        }
    }
    
        
    if( g_usb_audio_flg == true ) 
    {
        
        if((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_DETACH_MASKB) == FSA928X_INTERRUPT1_DETACH_MASKB)
        {
            




            if( g_fsa928x_mic_flg == true )
            {
                printk(KERN_ERR "[%s]call hs_report_headphone_usbaudio(HEADPHONE_4,false)\n",__func__);
                hs_report_headphone_usbaudio(HEADPHONE_4, false);  
            }else                                                
            {                                                    
                printk(KERN_ERR "[%s]call hs_report_headphone_usbaudio(HEADPHONE_3,false)\n",__func__);
                hs_report_headphone_usbaudio(HEADPHONE_3, false);  
            }

            g_fsa928x_mic_flg = false;
            
            g_usb_audio_flg = false;                             
            
        
        }else if( ((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_ATTACH_MASKB) == FSA928X_INTERRUPT1_ATTACH_MASKB) ||
                  ((g_read_device_info.interrupt_info.interrupt2.value & FSA928X_INTERRUPT2_ACCESSORY_ATTACH_MASKB) == FSA928X_INTERRUPT2_ACCESSORY_ATTACH_MASKB))
        {
            
            usleep( WAITTIME_USB_AUDIO_BOOT );
            

            




            if( g_fsa928x_mic_flg == true )
            {
                printk(KERN_ERR "[%s]call hs_report_headphone_usbaudio(HEADPHONE_4,true)\n",__func__);
                hs_report_headphone_usbaudio(HEADPHONE_4, true);  
            }else
            {
                printk(KERN_ERR "[%s]call hs_report_headphone_usbaudio(HEADPHONE_3,true)\n",__func__);
                hs_report_headphone_usbaudio(HEADPHONE_3, true);  
                
                
                
                pmic_hsed_enable( PM_HSED_CONTROLLER_1, PM_HSED_ENABLE_OFF );
                printk(KERN_INFO "%s MIC_BIAS1 = PM_HSED_ENABLE_OFF\n", __func__ );
                
                
            }

            
        }
        else
        {
            
        }
    }
    else
    {
        
    }

    
    
    if((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_CDP_DCP_HOST)  &&
            ((g_read_device_info.identify_device_info.device_type1.value & FSA928X_DEVTYPE1_DCP_MASKB) != 0) &&
            (g_read_device_info.identify_device_info.device_type2.value == 0))
    {
        if((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_DETACH_MASKB) == FSA928X_INTERRUPT1_DETACH_MASKB)
        {
            usb_sw_otg_set_power(USB_WALLCHARGER_NO_CHG_CURRENT);
            printk(KERN_INFO "[%s] usb_sw_otg_set_power(USB_WALLCHARGER_NO_CHG_CURRENT)called\n", __func__ );
        }
        else if((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_ATTACH_MASKB ) == FSA928X_INTERRUPT1_ATTACH_MASKB )
        {
            usb_sw_otg_set_power(USB_WALLCHARGER_CHG_CURRENT);
            printk(KERN_INFO "[%s] usb_sw_otg_set_power(USB_WALLCHARGER_CHG_CURRENT)called\n", __func__ );
        }
    }
    

    if((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_DETACH_MASKB) == FSA928X_INTERRUPT1_DETACH_MASKB)
    {
        
        g_fsa928x_power_supply_flg = false; 
        printk(KERN_INFO "%s:g_fsa928x_power_supply_flg = %d\n", __func__, g_fsa928x_power_supply_flg);
        

        
        FSA_set_otg_workable(0);
        

        
        if(g_usb_earphone_switch_detect_flg == true)
        {
            fsa928x_stop_adc_polling();
            printk(KERN_ERR "[%s] fsa928x_stop_adc_polling called",__func__);
        }
        
    }
    
    else if(((g_read_device_info.interrupt_info.interrupt1.value & FSA928X_INTERRUPT1_ATTACH_MASKB ) == FSA928X_INTERRUPT1_ATTACH_MASKB ))
    {
        if( g_fsa928x_power_supply_flg == true )
        {
            
            FSA_set_otg_workable(1);
        }
        else
        {
            
            FSA_set_otg_workable(0);
        }
    }
    

    printk(KERN_INFO "%s:end [read ]manual_sw1=0x%x\n", __FUNCTION__, g_read_device_info.switch_path_info.manual_sw1.value);
    printk(KERN_INFO "%s:end [write]manual_sw1=0x%x\n", __FUNCTION__, g_write_device_info.switch_path_info.manual_sw1.value);

    mutex_unlock(&g_fsa928x_usb_main_lock);
    return FSA928X_OK;

}








int fsa928x_read_interrupt_info( void )
{
    int ret = FSA928X_NG;

    
    ret = fsa928x_read_reg( &g_read_device_info.interrupt_info.interrupt1 );

    if( ret != FSA928X_OK )
    {
        return FSA928X_NG;
    }
    else
    {
       
    }

    
    ret = fsa928x_read_reg( &g_read_device_info.interrupt_info.interrupt2 );

    if( ret != FSA928X_OK )
    {
        return FSA928X_NG;
    }
    else
    {
       
    }
    return FSA928X_OK;
}








int fsa928x_read_switch_path_info( void )
{
    int ret = FSA928X_NG;

    
    ret = fsa928x_read_reg( &g_read_device_info.switch_path_info.manual_sw1 );
    if( ret != FSA928X_OK )
    {
        return FSA928X_NG;
    }
    else
    {
       
    }

    return FSA928X_OK;
}








int fsa928x_read_device_id_info( void )
{
    int ret = FSA928X_NG;

    
    ret = fsa928x_read_reg( &g_read_device_info.identify_device_info.adc );
    printk(KERN_INFO "%s:start adc=0x%x\n", __FUNCTION__, g_read_device_info.identify_device_info.adc.value);

   if( ret != FSA928X_OK )
    {
        return FSA928X_NG;
    }
    else
    {
       
    }

    
    ret = fsa928x_read_reg( &g_read_device_info.identify_device_info.device_type1 );
    printk(KERN_INFO "%s:start device_type1=0x%x\n", __FUNCTION__, g_read_device_info.identify_device_info.device_type1.value);

   if( ret != FSA928X_OK )
    {
        return FSA928X_NG;
    }
    else
    {
       
    }

    
    ret = fsa928x_read_reg( &g_read_device_info.identify_device_info.device_type2 );
    printk(KERN_INFO "%s:start device_type2=0x%x\n", __FUNCTION__, g_read_device_info.identify_device_info.device_type2.value);

   if( ret != FSA928X_OK )
    {
        return FSA928X_NG;
    }
    else
    {
       
    }

    
    ret = fsa928x_read_reg( &g_read_device_info.identify_device_info.vbus_state );
    printk(KERN_INFO "%s:start vbus_state=0x%x\n", __FUNCTION__, g_read_device_info.identify_device_info.vbus_state.value);

   if( ret != FSA928X_OK )
    {
        return FSA928X_NG;
    }
    else
    {
        
        g_read_device_info.identify_device_info.vbus_state.value &= FSA928X_MANUAL_SW1_VBUS_BIT_MASKB;
    }

    return FSA928X_OK;
}







int fsa928x_set_manual_switch_all_open( void )
{
    
    fsa928x_set_path_vbus_in(FSA928X_VBUSIN_OPEN);

    
    g_write_device_info.switch_path_info.manual_sw1.value &= FSA928X_MANUAL_SW1_VBUS_OUT_MASKB;

    return FSA928X_OK;
}








int fsa928x_set_manual_switch_detected_device( void )
{
    int  ret = FSA928X_NG;
    
    
    if((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_CDP_DCP_HOST)  &&
       ((g_read_device_info.identify_device_info.device_type1.value & FSA928X_DEVTYPE1_SDP_MASKB) != 0) &&
       (g_read_device_info.identify_device_info.device_type2.value == 0) )
    {
        
        g_write_device_info.switch_path_info.manual_sw1.value &= FSA928X_MANUAL_SW1_VBUS_OUT_MASKB;    
        g_write_device_info.switch_path_info.manual_sw1.value |= (FSA928X_MANUAL_SW1_DM_HOST_MASKB|FSA928X_MANUAL_SW1_DP_HOST_MASKB);    

        
        g_fsa928x_sdp_flg = true;
        printk(KERN_INFO "%s: g_fsa928x_sdp_flg = true \n", __func__);
        
        




        
    }
    
    else if((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_CDP_DCP_HOST)  &&
            ((g_read_device_info.identify_device_info.device_type1.value & FSA928X_DEVTYPE1_DCP_MASKB) != 0) &&
            (g_read_device_info.identify_device_info.device_type2.value == 0))
    {
        
        
        g_write_device_info.switch_path_info.manual_sw1.value &= FSA928X_MANUAL_SW1_VBUS_OUT_MASKB;    
        g_write_device_info.switch_path_info.manual_sw1.value |= (FSA928X_MANUAL_SW1_DM_HOST_MASKB|FSA928X_MANUAL_SW1_DP_HOST_MASKB);    
        
        
        




        
    }
    
    else if((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_CDP_DCP_HOST)  &&
            ((g_read_device_info.identify_device_info.device_type1.value & FSA928X_DEVTYPE1_CDP_MASKB) != 0) &&
            (g_read_device_info.identify_device_info.device_type2.value == 0))
    {
        
        g_write_device_info.switch_path_info.manual_sw1.value &= FSA928X_MANUAL_SW1_VBUS_OUT_MASKB;    
        g_write_device_info.switch_path_info.manual_sw1.value |= (FSA928X_MANUAL_SW1_DM_HOST_MASKB|FSA928X_MANUAL_SW1_DP_HOST_MASKB);    

        




        
    }

    else if(((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_MCPC_MODE1) &&
            (g_read_device_info.identify_device_info.device_type1.value == 0) &&
            ((g_read_device_info.identify_device_info.device_type2.value & FSA928X_DEVTYPE2_USBBOOT_ON_MASKB) != 0)) ||
            ((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_MCPC_MODE1_2) &&
            (g_read_device_info.identify_device_info.device_type1.value == 0) &&
            ((g_read_device_info.identify_device_info.device_type2.value & FSA928X_DEVTYPE2_USBBOOT_OFF_MASKB) != 0)))
    {
        printk(KERN_INFO "%s:[mode1]\n", __FUNCTION__);
        g_usb_audio_flg = true;    
        
        g_usb_headset_info.stereo_mono_type = USB_HEADSET_STEREO;   
        

        printk(KERN_INFO "%s:[mode1] stereo_mono_type=%d \n", __FUNCTION__, g_usb_headset_info.stereo_mono_type);

        
        g_usb_earphone_keypress_flg = false;      
        
        if(g_usb_earphone_switch_detect_flg == true)
        {
            fsa928x_start_adc_polling();          
            printk(KERN_INFO "[%s] fsa928x_start_adc_polling called",__func__);
        }
        
        
        g_write_device_info.switch_path_info.manual_sw1.value &= FSA928X_MANUAL_SW1_VBUS_OUT_MASKB;    
        g_write_device_info.switch_path_info.manual_sw1.value |= (FSA928X_MANUAL_SW1_DM_AUDI_L_MASKB|FSA928X_MANUAL_SW1_DP_AUDI_R_MASKB);    

        
        if( (g_read_device_info.identify_device_info.vbus_state.value & FSA928X_MANUAL_SW1_VBUS_BIT_MASKB) == 0 )
        {
            
            fsa928x_set_path_vbus_in( FSA928X_VBUSIN_CON_MIC );
            
            ret = fsa928x_detect_mic();
            printk(KERN_INFO "%s:[mode1] call fsa928x_detect_mic() \n", __FUNCTION__);
            return ( ret );
            
        }
        else  
        {
            printk(KERN_INFO "%s:[mode1] VBUSon \n", __FUNCTION__);
            




            
        }
    }
    
    else if((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_MCPC_MODE2) &&
            ((g_read_device_info.identify_device_info.device_type1.value & FSA928X_DEVTYPE1_AUDIOTYPE_MASKB) != 0) &&
            (g_read_device_info.identify_device_info.device_type2.value == 0))
    {
        printk(KERN_INFO "%s:[mode2]\n", __FUNCTION__);
        g_usb_audio_flg = true;    
        
        g_usb_headset_info.stereo_mono_type = USB_HEADSET_MONO;     
        

        printk(KERN_INFO "%s:[mode2] stereo_mono_type=%d \n", __FUNCTION__, g_usb_headset_info.stereo_mono_type);

        
        g_usb_earphone_keypress_flg = false;      
        
        if(g_usb_earphone_switch_detect_flg == true)
        {
            fsa928x_start_adc_polling();          
            printk(KERN_INFO "[%s] fsa928x_start_adc_polling called",__func__);
        }
        

        
        g_write_device_info.switch_path_info.manual_sw1.value &= FSA928X_MANUAL_SW1_VBUS_OUT_MASKB;    
        g_write_device_info.switch_path_info.manual_sw1.value |= (FSA928X_MANUAL_SW1_DM_AUDI_L_MASKB|FSA928X_MANUAL_SW1_DP_OPEN_MASKB);    

        
        if( (g_read_device_info.identify_device_info.vbus_state.value & FSA928X_MANUAL_SW1_VBUS_BIT_MASKB) == 0 )
        {
            
            fsa928x_set_path_vbus_in( FSA928X_VBUSIN_CON_MIC );
            
            ret = fsa928x_detect_mic();
            printk(KERN_INFO "%s:[mode2] call fsa928x_detect_mic() \n", __FUNCTION__);
            return ( ret );
            
        }
        else  
        {
            printk(KERN_INFO "%s:[mode2] VBUSon \n", __FUNCTION__);
            




            
        }
    }


































































    
    else
    {
        printk(KERN_ERR "%s:[UNKNOWN DEVICE] g_fsa928x_power_supply_flg is cleared\n", __FUNCTION__);
        
        fsa928x_set_manual_switch_all_open();

		
        g_fsa928x_power_supply_flg = false;

    }
    printk(KERN_INFO "%s: g_usb_earphone_switch_detect_flg = %d, g_usb_audio_flg = %d\n",__func__, g_usb_earphone_switch_detect_flg, g_usb_audio_flg);
    
    return (FSA928X_OK);
    
}







int fsa928x_detect_mic( void )
{
    int ret  = FSA928X_NG;
    
    ret = fsa928x_switch_path();
    if( ret != FSA928X_OK )
    {
        return ( FSA928X_NG );
    }

    
    
    pmic_hsed_enable( PM_HSED_CONTROLLER_1, PM_HSED_ENABLE_ALWAYS );
    printk(KERN_INFO "%s MIC_BIAS1 = PM_HSED_ENABLE_ALWAYS\n", __func__ );
    

    
    
    msleep( g_usb_mic_dec_waittime * 10 );              
    
    
    msm_chg_usb_audio_det_mic(&g_fsa928x_mic_flg);
    printk(KERN_INFO "fsa928x_detect_mic g_fsa928x_mic_flg = %d!\n",g_fsa928x_mic_flg);

    return (FSA928X_OK);
}










void fsa928x_set_path_vbus_in( fsa928x_vbus_in_path_enum  vbus_in_path )
{




    
    if(vbus_in_path == FSA928X_VBUSIN_CON_MIC)
    {
        
    }
    else
    {
        
        if( (g_read_device_info.switch_path_info.manual_sw1.value & FSA928X_MANUAL_SW1_VBUS_OUT_MASKB) == FSA928X_MANUAL_SW1_VBUS_OUT_MASKB )
        {
            return;
        }
    }
    


    
    switch(vbus_in_path)
    {
        
        case FSA928X_VBUSIN_OPEN:
            g_write_device_info.switch_path_info.manual_sw1.value &= (~FSA928X_MANUAL_SW1_VBUS_OUT_MASKB);   
            break;
            
        
        case FSA928X_VBUSIN_CON_MIC:
            g_write_device_info.switch_path_info.manual_sw1.value &= (~FSA928X_MANUAL_SW1_VBUS_OUT_MASKB);   
            g_write_device_info.switch_path_info.manual_sw1.value |= FSA928X_MANUAL_SW1_VBUS_MIC_SET;        
            break;
            
        
        default:
            printk(KERN_ERR "Fatal Error! vbus_in_path == %d!\n", vbus_in_path);
            break;
    }
}








int fsa928x_switch_path( void )
{
    int ret = FSA928X_NG;
    
    ret = fsa928x_write_reg(&g_write_device_info.switch_path_info.manual_sw1);
    
    return ret;
}







void fsa928x_start_adc_polling( void )
{
    g_timer_use_flg = true;      
    
    schedule_delayed_work(&adc_polling_work, POLLING_INTERVAL_TIME);
    printk(KERN_INFO "fsa928x_start_adc_polling_handler:work scheduled!\n" );
}







static void fsa928x_adc_polling_handler( struct work_struct *w )
{

    
    mutex_lock(&g_fsa928x_usb_sendend_key_polling_lock);
    

    
    if( g_timer_use_flg == false )
    {
        
        mutex_unlock(&g_fsa928x_usb_sendend_key_polling_lock);
        

        return;
    }
    
    if( fsa928x_read_reg(&g_read_device_info.identify_device_info.adc) == FSA928X_OK)
    {
        if((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_SENDEND_KEY) ||
           (g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_SENDEND_KEY_2))
        {
            
            usleep( SEND_END_KEY_STABILIZING_TIME * 1000 );
            
            if( fsa928x_read_reg(&g_read_device_info.identify_device_info.adc) == FSA928X_OK)
            {
                if((g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_SENDEND_KEY) ||
                   (g_read_device_info.identify_device_info.adc.value == FSA928X_ADC_VALUE_SENDEND_KEY_2))
                {
                    
                    
                    if(g_usb_earphone_keypress_flg == false)
                    {
                        g_usb_earphone_keypress_flg = true;
                        usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_PRESSED_K);
                        printk(KERN_INFO "[%s]:usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_PRESSED_K)!\n" ,__func__);
                    }
                    
                }
                else
                {
                    
                    if(g_usb_earphone_keypress_flg == true)
                    {
                        g_usb_earphone_keypress_flg = false;
                        usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_REL_K);
                        printk(KERN_INFO "[%s]:usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_REL_K)!\n" ,__func__);
                    }
                    
                }
            }
            else
            {
                
            }
        }
        else    
        {
            
            if(g_usb_earphone_keypress_flg == true)
            {
                g_usb_earphone_keypress_flg = false;
                usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_REL_K);
                printk(KERN_INFO "[%s]:usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_REL_K)!\n" ,__func__);
            }
            
        }
    }
    else    
    {
        
    }

    
    schedule_delayed_work(&adc_polling_work, POLLING_INTERVAL_TIME);
    printk(KERN_INFO "fsa928x_adc_polling_handler:work scheduled!\n" );
    
    mutex_unlock(&g_fsa928x_usb_sendend_key_polling_lock);
    

}







void fsa928x_stop_adc_polling( void )
{
    
    mutex_lock(&g_fsa928x_usb_sendend_key_polling_lock);
    

    g_timer_use_flg = false;   
    printk(KERN_INFO "fsa928x_stop_adc_polling:work flag false!\n" );

    
    if(g_usb_earphone_keypress_flg == true)
    {
        g_usb_earphone_keypress_flg = false;
        usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_REL_K);
        printk(KERN_INFO "[%s]:usb_report_hs_key_public(HS_HEADSET_SWITCH_K, HS_REL_K)!\n" ,__func__);
    }
    
    
    mutex_unlock(&g_fsa928x_usb_sendend_key_polling_lock);
    
}








static int fsa928x_read_reg( fsa928x_reg_type* reg_p)
{
    int ret = FSA928X_I2C_TRANSFER_NG;      
    int retry_counter = 0;                  

    if(reg_p == NULL )
    {
        printk(KERN_ERR "Error in fsa928x_read_reg! reg_p == NULL" );
        return FSA928X_NG;
    }
    else
    {
        
        ret = fsa928x_i2c_read( reg_p->address , &(reg_p->value) );

        
        if( ret != FSA928X_I2C_TRANSFER_OK )
        {

            
            while( (ret !=  FSA928X_I2C_TRANSFER_OK) && (retry_counter < I2C_RETRY_MAX2_COUNT) ){
                msleep(10);

                
                ret = fsa928x_i2c_read( reg_p->address , &(reg_p->value) );
                
                retry_counter++;
            }
            
            if( ret != FSA928X_I2C_TRANSFER_OK )
            {
                printk(KERN_ERR "Error in fsa928x_read_reg! Read retry failed!\n");
                
                printk(KERN_ERR "[T][ARM]Event:0x%02X Info:0x%02X\n", FSA928X_ALERM_EVENT, FSA928X_ALERM_INFO_I2C_READ);
                
                return FSA928X_NG;
            }
        }
        else
        {
           
        }
    }
    
    return FSA928X_OK;
}









static int fsa928x_write_reg(const fsa928x_reg_type* reg_p)
{
    int ret = FSA928X_I2C_TRANSFER_NG;      
    int retry_counter = 0;                  
    
    if(reg_p == NULL )
    {
        printk(KERN_ERR "Error in fsa928x_write_reg! reg_p == NULL" );
        return FSA928X_NG;
    }
    else
    {
        
        ret = fsa928x_i2c_write( reg_p->address , reg_p->value );

        
        if( ret != FSA928X_I2C_TRANSFER_OK )
        {
            
            while( ret ==  FSA928X_I2C_TRANSFER_NG && retry_counter < I2C_RETRY_MAX_COUNT ){
                
                ret = fsa928x_i2c_write( reg_p->address , reg_p->value );
                
                retry_counter++;
            }
            
            if( ret != FSA928X_I2C_TRANSFER_OK )
            {
                printk(KERN_ERR "Error in fsa928x_write_reg! Write retry failed!\n");
                
                printk(KERN_ERR "[T][ARM]Event:0x%02X Info:0x%02X\n", FSA928X_ALERM_EVENT, FSA928X_ALERM_INFO_I2C_WRITE);
                
                return FSA928X_NG;
            }
        }
        else
        {
           
        }
    }
    return FSA928X_OK;
}








static void fsa928x_avoid_errata( void )
{
    printk(KERN_INFO "%s: start", __FUNCTION__);

    
    if(fsa928x_read_device_id_info() == FSA928X_NG)
    {
        printk(KERN_ERR "%s:end call fsa928x_read_device_id_info() ERROR", __FUNCTION__);
        return;
    }
    
    fsa928x_set_manual_switch_detected_device();
    
    
    
    if(fsa928x_write_reg(&g_write_device_info.switch_path_info.manual_sw1) == FSA928X_NG )
    {
        printk(KERN_ERR "%s:end manual_sw1 re-write ERROR", __FUNCTION__);
        return;
    }

    
    if( fsa928x_write_reg(&g_write_device_info.init_info.interrupt_mask1) == FSA928X_NG )
    {
        printk(KERN_ERR "%s:end interrupt_mask1 re-write ERROR", __FUNCTION__);
        return;
    }
    if( fsa928x_write_reg(&g_write_device_info.init_info.interrupt_mask2) == FSA928X_NG )
    {
        printk(KERN_ERR "%s:end interrupt_mask2 re-write ERROR", __FUNCTION__);
        return;
    }
    
    if( fsa928x_write_reg(&g_write_device_info.init_info.control) == FSA928X_NG )
    {
        printk(KERN_ERR "%s:end control re-write ERROR", __FUNCTION__);
        return;
    }
}





































































































































































































































































































































































































































































































































































































































































































