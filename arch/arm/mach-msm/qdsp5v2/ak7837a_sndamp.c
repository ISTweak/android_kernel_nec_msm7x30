


/*===========================================================================
 FILENAME : AK7837A_sndamp.c

 Copyright (C) 2010 NEC Corporation.
 No permission to use, copy, modify and distribute this software
 and its documentation for any purpose is granted.
 This software is provided under applicable license agreement only.
===========================================================================*/
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/




























#include <asm/uaccess.h>

#include <linux/types.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/mfd/pmic8058.h>
#include <asm/param.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/workqueue.h>

#define MSM_MM_DEBUG_LEVEL 2
#define MSM_MM_MODULE "AK7837A-sndamp" 
#include <mach/debug_mm.h>

#include "mach/msm_battery.h"    

#include "ak7837a_sndamp.h"
#include "ak7837a_sndampi.h"
#include "ak7837a_i2c_driver.h"
#include "NvRegister.h"














static  unsigned char  ak7837a_reg_buffer[AK7837A_REG_MAX] = {
    AK7837A_REG_00_RESERVED_INIT_VAL,         
    AK7837A_REG_01_SYSRST_INIT_VAL,           
    AK7837A_REG_02_PDNMODE_INIT_VAL,          
    AK7837A_REG_03_ALCCTRL4_INIT_VAL,         
    AK7837A_REG_04_ALCCTRL1_INIT_VAL,         
    AK7837A_REG_05_ALCCTRL2_INIT_VAL,         
    AK7837A_REG_06_ALCCTRL3_INIT_VAL,         
    AK7837A_REG_07_MODESELCT_INIT_VAL,        
    AK7837A_REG_08_GAIN4ALCOFF_INIT_VAL,      
    AK7837A_REG_09_FLAG_INIT_VAL,             
    AK7837A_REG_0A_ALCCTRL5_INIT_VAL,         
    AK7837A_REG_0B_ALCCTRL6_INIT_VAL,         
    AK7837A_REG_0C_RESERVED_INIT_VAL,         
    AK7837A_REG_0D_RESERVED_INIT_VAL,         
    AK7837A_REG_0E_RESERVED_INIT_VAL,         
    AK7837A_REG_0F_REVISION_INIT_VAL          
};



ak7837a_device_type   g_ak7837a_cur_path = AK7837A_DEVICE_HANDSET;


bool                  g_ak7837a_init_enable = false;



ak7837a_sp_state_type g_ak7837a_sp_state = AK7837A_SP_OFF;




























































































static int ak7837a_GpioSetValue(int iAddr, int iValue)
{




    

    
    gpio_set_value( iAddr, iValue );

    
    mdelay( AK7837A_STARTUP_WAIT_TIME );
















    return true;
}


















ak7837a_proc_device_type ak7837a_getCurrentDevice( void )
{
    ak7837a_proc_device_type device;    

    

    
    switch( g_ak7837a_cur_path )
    {
    
    case AK7837A_DEVICE_HANDSET :
    case AK7837A_DEVICE_FMRADIO_HANDSET :






        
        device = AK7837A_PROC_DEVICE_HANDSET;
        break;

    
    case AK7837A_DEVICE_SPEAKER_STEREO :
    case AK7837A_DEVICE_FMRADIO_SPEAKER :
    case AK7837A_DEVICE_PTT_SPEAKER_STEREO :
    case AK7837A_DEVICE_HEADSET_STEREO_SPEAKER_STEREO :






        
        device = AK7837A_PROC_DEVICE_SPEAKER;
        break;


    
    default:
        
        printk( KERN_ERR "[ak7837a] Current Device <ERROR> : OTHER (%d) \n",
                g_ak7837a_cur_path );
        device = AK7837A_PROC_DEVICE_HANDSET;
        break;
    }

    
    return device;

}





















static int ak7837a_WriteReg(ak7837a_register_type r)
{




    

    
    if ( 0 > ak7837a_write( (u8)AK7837A_ADDR(r), (u8)AK7837A_BUF(r) ) ) 
    {
        

        printk( KERN_ERR "[ak7837a] Write REG <ERROR> : ADDR=0x%02x DATA=0x%02x \n",
                AK7837A_ADDR(r),
                AK7837A_BUF(r) );

        return false;
    }





















    return true;

}





















static int ak7837a_ReadReg(ak7837a_register_type r)
{
    unsigned char          read_buf;    

    

    
    if( 0 > ak7837a_read( (u8)(AK7837A_ADDR(r)), (u8 *)&(read_buf) ) )
    {
        

        printk( KERN_ERR "[ak7837a] Read REG <ERROR> : ADDR=0x%02x DATA=0x%02x \n",
                AK7837A_ADDR(r),
                AK7837A_BUF(r) );

        return false;
    }

    

    
    memcpy( (void *)&AK7837A_BUF(r), (void*)&read_buf, AK7837A_BUFFER_LENGTH );







    return true;

} 




















static void ak7837a_check_reg09_flag(void)
{




    
    if( ak7837a_ReadReg(AK7837A_REG_09_FLAG) == false ) {
        
        return;
    }

    
    if( AK7837A_GET_REG_09_FLAG_THERR   == AK7837A_REG_ON ) {



        
        printk( KERN_ERR "[T][ARM]Event:0x4F Info:0x00\n");

    }
    
    
    if( AK7837A_GET_REG_09_FLAG_LVLERR  == AK7837A_REG_ON ) {



        
        printk( KERN_ERR "[T][ARM]Event:0x4F Info:0x01\n");

    }
    
    
    if( AK7837A_GET_REG_09_FLAG_SHORT   == AK7837A_REG_ON ) {



        
        printk( KERN_ERR "[T][ARM]Event:0x4F Info:0x02\n");

    }
    
    
    if( AK7837A_GET_REG_09_FLAG_VMROPEN == AK7837A_REG_ON ) {



        
        printk( KERN_ERR "[T][ARM]Event:0x4F Info:0x03\n");

    }
    
    
    if( AK7837A_GET_REG_09_FLAG_INTERR  == AK7837A_REG_ON ) {



        
        printk( KERN_ERR "[T][ARM]Event:0x4F Info:0x04\n");

    }
    

} 





















static int ak7837a_alc_ctrl_handset( void )
{




    
    if( NvRegister_GetAK7837A_REC_ALCONOFF() ) {





        
        ak7837a_reg_buffer[AK7837A_REG_06_ALCCTRL3] = NvRegister_GetAK7837A_REC_ALCCTRL3();
        ak7837a_reg_buffer[AK7837A_REG_05_ALCCTRL2] = NvRegister_GetAK7837A_REC_ALCCTRL2();
        ak7837a_reg_buffer[AK7837A_REG_0A_ALCCTRL5] = NvRegister_GetAK7837A_REC_ALCCTRL5();
        ak7837a_reg_buffer[AK7837A_REG_0B_ALCCTRL6] = NvRegister_GetAK7837A_REC_ALCCTRL6();

        
        if( ak7837a_WriteReg( AK7837A_REG_06_ALCCTRL3 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_05_ALCCTRL2 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_0A_ALCCTRL5 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_0B_ALCCTRL6 ) == false ) {
            return false;
        }

        
        AK7837A_SET_REG_06_ALCCTRL3_ALC( AK7837A_REG_ON );

        
        if( ak7837a_WriteReg( AK7837A_REG_06_ALCCTRL3 ) == false ) {
            return false;
        }
    }
    
    else{





        
        ak7837a_reg_buffer[AK7837A_REG_08_GAIN4ALCOFF] = NvRegister_GetAK7837A_REC_GAIN4ALCOFF();

        
        AK7837A_SET_REG_06_ALCCTRL3_ALC( AK7837A_REG_OFF );

        
        if( ak7837a_WriteReg( AK7837A_REG_06_ALCCTRL3 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_08_GAIN4ALCOFF ) == false ) {
            return false;
        }
    }


    return true;
} 





















static int ak7837a_alc_ctrl_speaker( void )
{




    
    if( NvRegister_GetAK7837A_SPK_ALCONOFF() ) {






        
        ak7837a_reg_buffer[AK7837A_REG_06_ALCCTRL3] = NvRegister_GetAK7837A_SPK_ALCCTRL3();
        ak7837a_reg_buffer[AK7837A_REG_05_ALCCTRL2] = NvRegister_GetAK7837A_SPK_ALCCTRL2();
        ak7837a_reg_buffer[AK7837A_REG_03_ALCCTRL4] = NvRegister_GetAK7837A_SPK_ALCCTRL4();
        ak7837a_reg_buffer[AK7837A_REG_04_ALCCTRL1] = NvRegister_GetAK7837A_SPK_ALCCTRL1();
        
        
        if( ak7837a_WriteReg( AK7837A_REG_06_ALCCTRL3 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_05_ALCCTRL2 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_03_ALCCTRL4 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_04_ALCCTRL1 ) == false ) {
            return false;
        }

        
        AK7837A_SET_REG_06_ALCCTRL3_ALC( AK7837A_REG_ON );

        
        if( ak7837a_WriteReg( AK7837A_REG_06_ALCCTRL3 ) == false ) {
            return false;
        }

    }
    
    else{





        
        ak7837a_reg_buffer[AK7837A_REG_08_GAIN4ALCOFF] = NvRegister_GetAK7837A_SPK_GAIN4ALCOFF();

        
        AK7837A_SET_REG_06_ALCCTRL3_ALC( AK7837A_REG_OFF );

        
        if( ak7837a_WriteReg( AK7837A_REG_06_ALCCTRL3 ) == false ) {
            return false;
        }

        if( ak7837a_WriteReg( AK7837A_REG_08_GAIN4ALCOFF ) == false ) {
            return false;
        }
    }

    return true;
} 





















static int ak7837a_alc_ctrl( void )
{
    ak7837a_proc_device_type   device;

    

    device = ak7837a_getCurrentDevice();

    
    switch(device)
    {
    
    
    
    case AK7837A_PROC_DEVICE_SPEAKER:





        
        AK7837A_SET_REG_07_MODESELCT_SNDSEL( AK7837A_MODESELCT_SNDSEL_SPEAKER );

        
        if( ak7837a_WriteReg( AK7837A_REG_07_MODESELCT ) == false) {
            
            return false;
        }

        
        if( ak7837a_alc_ctrl_speaker() == false ) {
            
            return false;
        }
        break;

    
    
    
    case AK7837A_PROC_DEVICE_HANDSET:
        
    default:    





        
        AK7837A_SET_REG_07_MODESELCT_SNDSEL( AK7837A_MODESELCT_SNDSEL_HANDSET );

        
        if( ak7837a_WriteReg( AK7837A_REG_07_MODESELCT ) == false ) {
            
            return false;
        }
        
        
        if( ak7837a_alc_ctrl_handset() == false ) {
            
            return false;
        }
        break;
    }

    return true;
}



















void ak7837a_set_sp_state( ak7837a_sp_state_type state )
{




    
    g_ak7837a_sp_state = state;

    if( g_ak7837a_sp_state == AK7837A_SP_ON )
    {
        

        
        pm_obs_a_speaker( AK7837A_PM_OBS_SPEAKER_ON );
    }
    else
    {
        

        
        pm_obs_a_speaker( AK7837A_PM_OBS_SPEAKER_OFF );
    }
} 

























































static void ak7837a_startup( ak7837a_device_type path )
{
    
    g_ak7837a_cur_path = path;





    
    
    
    if( NvRegister_GetDataFlag() != NV_REGISTER_DATA_FLAG_OK ) {
        
        printk( KERN_ERR "[ak7837a] ak7837a_startup : NV-data is not ready. (%d)\n", NvRegister_GetDataFlag() );

        
        ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_LOW_VALUE );
        return;
    }

    
    
    

    
    ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_LOW_VALUE );

    
    ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_HIGH_VALUE );















    
    
    
    if( ak7837a_alc_ctrl() == false) {

        
        
        ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_LOW_VALUE );
        return;
    }

    
    
    
    
    AK7837A_SET_REG_02_PDNMODE_PDN( AK7837A_REG_ON );

    
    if( ak7837a_WriteReg( AK7837A_REG_02_PDNMODE ) == false ) {

        
        
        ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_LOW_VALUE );
        return;
    }

    
    
    




    mdelay( AK7837A_STARTUP_WAIT_TIME );






    
    ak7837a_set_sp_state( AK7837A_SP_ON );



    NvRegister_SetAkPowerState( NV_REGISTER_VE004_STATE_ON );


} 




















static void ak7837a_shutdown( void )
{





    NvRegister_SetAkPowerState( NV_REGISTER_VE004_STATE_OFF );




    
    
    
    ak7837a_check_reg09_flag();


    
    
    
    
    AK7837A_SET_REG_02_PDNMODE_PDN( AK7837A_REG_OFF );

    
    ak7837a_WriteReg( AK7837A_REG_02_PDNMODE );








    
    
    
    
    ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_LOW_VALUE );


    
    ak7837a_set_sp_state( AK7837A_SP_OFF );


} 




















void ak7837a_power_on_handset( void )
{
    
    ak7837a_startup( AK7837A_DEVICE_HANDSET );
    return;

} 




















void ak7837a_power_on_fmradio_handset( void )
{
    
    ak7837a_startup( AK7837A_DEVICE_FMRADIO_HANDSET );
    return;

} 




















void ak7837a_power_on_speaker_stereo( void )
{
    
    ak7837a_startup( AK7837A_DEVICE_SPEAKER_STEREO );
    return;

} 




















void ak7837a_power_on_fmradio_speaker( void )
{
    
    ak7837a_startup( AK7837A_DEVICE_FMRADIO_SPEAKER );
    return;

} 




















void ak7837a_power_on_headset_stereo_speaker_stereo( void )
{
    
    ak7837a_startup( AK7837A_DEVICE_HEADSET_STEREO_SPEAKER_STEREO );
    return;

} 




















void ak7837a_power_on_ptt_speaker_stereo( void )
{
    
    ak7837a_startup( AK7837A_DEVICE_PTT_SPEAKER_STEREO );
    return;

} 




















void ak7837a_power_off( void )
{
    
    ak7837a_shutdown();
    return;

} 




















char Diag_Audio_ak7837a_drive(diag_acad_ak7837a_drive stAk7837aDrive)
{
    char   cRet  = 0;

    

    
    switch(stAk7837aDrive.power) {
    
    
    
    case DIAG_AK7837A_DRV_POWER_ON:




        
        if( gpio_get_value(AK7837A_GPIO_AUD_AMP_RST) == AK7837A_GPIO_HIGH_VALUE ) {

            
            if( ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_LOW_VALUE ) == false ) {

                printk( KERN_ERR "[ak7837a] Diag Ak7837A drive <ERROR> : PDN switch failure.\n");
                cRet = 1;
                break;
            }
        }

        
        if( ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_HIGH_VALUE ) == false ) {

            printk( KERN_ERR "[ak7837a] Diag Ak7837A drive <ERROR> : PDN switch failure.\n");
            cRet = 1;
        }

        break;
    
    
    
    case DIAG_AK7837A_DRV_POWER_OFF:




        
        if( ak7837a_GpioSetValue( AK7837A_GPIO_AUD_AMP_RST, AK7837A_GPIO_LOW_VALUE ) == false ) {

            printk( KERN_ERR "[ak7837a] Diag Ak7837A drive <ERROR> : PDN switch failure.\n");
            cRet = 1;
        }

        break;



























































    
    
    
    default:
        printk( KERN_ERR "[ak7837a] Diag Ak7837A drive <ERROR> : Command Error. (power = 0x%02X)\n", stAk7837aDrive.power);
        cRet = 1;
        break;
    }


    return cRet;
}



