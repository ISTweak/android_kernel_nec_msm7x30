/**********************************************************************
* File Name: arch/arm/mach-msm/qdsp5v2/NvRegister.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/





















#include <asm/uaccess.h>         
#include <linux/types.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/fs.h>            
#include <linux/kernel.h>        
#include <linux/miscdevice.h>
#include <linux/smp_lock.h>      

#include "linux/audio_compile_switch_apps.h"
#include "NvRegister.h"

static NvRegister g_stNvRegister;
static int        g_iVoiceState;
static int        g_iAkPowerState = NV_REGISTER_VE004_STATE_OFF;	

















































































void NvRegister_InitData( void )
{




    g_stNvRegister.ucDataFlag                    = NV_REGISTER_DATA_FLAG_NO;


    
    g_stNvRegister.stAk7837aRecV.ucAlcOnOff      = 0;
    g_stNvRegister.stAk7837aRecV.ucGain4AlcOff   = AK7837A_REG_08_GAIN4ALCOFF_INIT_VAL;
    g_stNvRegister.stAk7837aRecV.ucAlcCtrl3      = AK7837A_REG_06_ALCCTRL3_INIT_VAL;
    g_stNvRegister.stAk7837aRecV.ucAlcCtrl2      = AK7837A_REG_05_ALCCTRL2_INIT_VAL;
    g_stNvRegister.stAk7837aRecV.ucAlcCtrl5      = AK7837A_REG_0A_ALCCTRL5_INIT_VAL;
    g_stNvRegister.stAk7837aRecV.ucAlcCtrl6      = AK7837A_REG_0B_ALCCTRL6_INIT_VAL;
    g_stNvRegister.stAk7837aRecA.ucAlcOnOff      = 0;
    g_stNvRegister.stAk7837aRecA.ucGain4AlcOff   = AK7837A_REG_08_GAIN4ALCOFF_INIT_VAL;
    g_stNvRegister.stAk7837aRecA.ucAlcCtrl3      = AK7837A_REG_06_ALCCTRL3_INIT_VAL;
    g_stNvRegister.stAk7837aRecA.ucAlcCtrl2      = AK7837A_REG_05_ALCCTRL2_INIT_VAL;
    g_stNvRegister.stAk7837aRecA.ucAlcCtrl5      = AK7837A_REG_0A_ALCCTRL5_INIT_VAL;
    g_stNvRegister.stAk7837aRecA.ucAlcCtrl6      = AK7837A_REG_0B_ALCCTRL6_INIT_VAL;

    
    g_stNvRegister.stAk7837aSpkV.ucAlcOnOff      = 0;
    g_stNvRegister.stAk7837aSpkV.ucGain4AlcOff   = AK7837A_REG_08_GAIN4ALCOFF_INIT_VAL;
    g_stNvRegister.stAk7837aSpkV.ucAlcCtrl3      = AK7837A_REG_06_ALCCTRL3_INIT_VAL;
    g_stNvRegister.stAk7837aSpkV.ucAlcCtrl2      = AK7837A_REG_05_ALCCTRL2_INIT_VAL;
    g_stNvRegister.stAk7837aSpkV.ucAlcCtrl4      = AK7837A_REG_03_ALCCTRL4_INIT_VAL;
    g_stNvRegister.stAk7837aSpkV.ucAlcCtrl1      = AK7837A_REG_04_ALCCTRL1_INIT_VAL;
    g_stNvRegister.stAk7837aSpkA.ucAlcOnOff      = 0;
    g_stNvRegister.stAk7837aSpkA.ucGain4AlcOff   = AK7837A_REG_08_GAIN4ALCOFF_INIT_VAL;
    g_stNvRegister.stAk7837aSpkA.ucAlcCtrl3      = AK7837A_REG_06_ALCCTRL3_INIT_VAL;
    g_stNvRegister.stAk7837aSpkA.ucAlcCtrl2      = AK7837A_REG_05_ALCCTRL2_INIT_VAL;
    g_stNvRegister.stAk7837aSpkA.ucAlcCtrl4      = AK7837A_REG_03_ALCCTRL4_INIT_VAL;
    g_stNvRegister.stAk7837aSpkA.ucAlcCtrl1      = AK7837A_REG_04_ALCCTRL1_INIT_VAL;








    return;
}















unsigned char NvRegister_GetNonClip( void )
{
    unsigned char ucNonclip = 0;

    














    return ucNonclip;
}














unsigned char NvRegister_GetAK7837A_REC_ALCONOFF( void )
{
    unsigned char ucAlcOnOff = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcOnOff = g_stNvRegister.stAk7837aRecV.ucAlcOnOff;
    }
    
    else {
        ucAlcOnOff = g_stNvRegister.stAk7837aRecA.ucAlcOnOff;
    }



    return ucAlcOnOff;
}














unsigned char NvRegister_GetAK7837A_REC_GAIN4ALCOFF( void )
{
    unsigned char ucGain4AlcOff = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucGain4AlcOff = g_stNvRegister.stAk7837aRecV.ucGain4AlcOff;
printk( KERN_INFO "<DRVSOUND> REC_GAIN4ALCOFF 1 %x\n",ucGain4AlcOff);

    }
    
    else {
        ucGain4AlcOff = g_stNvRegister.stAk7837aRecA.ucGain4AlcOff;
printk( KERN_INFO "<DRVSOUND> REC_GAIN4ALCOFF 2 %x\n",ucGain4AlcOff);
    }



    return ucGain4AlcOff;
}














unsigned char NvRegister_GetAK7837A_REC_ALCCTRL3( void )
{
    unsigned char ucAlcCtrl3 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl3 = g_stNvRegister.stAk7837aRecV.ucAlcCtrl3;
    }
    
    else {
        ucAlcCtrl3 = g_stNvRegister.stAk7837aRecA.ucAlcCtrl3;
    }



    return ucAlcCtrl3;
}














unsigned char NvRegister_GetAK7837A_REC_ALCCTRL2( void )
{
    unsigned char ucAlcCtrl2 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl2 = g_stNvRegister.stAk7837aRecV.ucAlcCtrl2;
    }
    
    else {
        ucAlcCtrl2 = g_stNvRegister.stAk7837aRecA.ucAlcCtrl2;
    }



    return ucAlcCtrl2;
}














unsigned char NvRegister_GetAK7837A_REC_ALCCTRL5( void )
{
    unsigned char ucAlcCtrl5 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl5 = g_stNvRegister.stAk7837aRecV.ucAlcCtrl5;
    }
    
    else {
        ucAlcCtrl5 = g_stNvRegister.stAk7837aRecA.ucAlcCtrl5;
    }



    return ucAlcCtrl5;
}














unsigned char NvRegister_GetAK7837A_REC_ALCCTRL6( void )
{
    unsigned char ucAlcCtrl6 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl6 = g_stNvRegister.stAk7837aRecV.ucAlcCtrl6;
    }
    
    else {
        ucAlcCtrl6 = g_stNvRegister.stAk7837aRecA.ucAlcCtrl6;
    }



    return ucAlcCtrl6;
}














unsigned char NvRegister_GetAK7837A_SPK_ALCONOFF( void )
{
    unsigned char ucAlcOnOff = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcOnOff = g_stNvRegister.stAk7837aSpkV.ucAlcOnOff;
    }
    
    else {
        ucAlcOnOff = g_stNvRegister.stAk7837aSpkA.ucAlcOnOff;
    }



    return ucAlcOnOff;
}














unsigned char NvRegister_GetAK7837A_SPK_GAIN4ALCOFF( void )
{
    unsigned char ucGain4AlcOff = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucGain4AlcOff = g_stNvRegister.stAk7837aSpkV.ucGain4AlcOff;
    }
    
    else {
        ucGain4AlcOff = g_stNvRegister.stAk7837aSpkA.ucGain4AlcOff;
    }



    return ucGain4AlcOff;
}














unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL3( void )
{
    unsigned char ucAlcCtrl3 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl3 = g_stNvRegister.stAk7837aSpkV.ucAlcCtrl3;
    }
    
    else {
        ucAlcCtrl3 = g_stNvRegister.stAk7837aSpkA.ucAlcCtrl3;
    }



    return ucAlcCtrl3;
}














unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL2( void )
{
    unsigned char ucAlcCtrl2 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl2 = g_stNvRegister.stAk7837aSpkV.ucAlcCtrl2;
    }
    
    else {
        ucAlcCtrl2 = g_stNvRegister.stAk7837aSpkA.ucAlcCtrl2;
    }



    return ucAlcCtrl2;
}














unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL4( void )
{
    unsigned char ucAlcCtrl4 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl4 = g_stNvRegister.stAk7837aSpkV.ucAlcCtrl4;
    }
    
    else {
        ucAlcCtrl4 = g_stNvRegister.stAk7837aSpkA.ucAlcCtrl4;
    }



    return ucAlcCtrl4;
}














unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL1( void )
{
    unsigned char ucAlcCtrl1 = 0;



    
    if(g_iVoiceState == NV_REGISTER_VOICE_STATE_ON) {
        ucAlcCtrl1 = g_stNvRegister.stAk7837aSpkV.ucAlcCtrl1;
    }
    
    else {
        ucAlcCtrl1 = g_stNvRegister.stAk7837aSpkA.ucAlcCtrl1;
    }



    return ucAlcCtrl1;
}














unsigned short NvRegister_GetHsed_ScCurrentThreshold( void )
{
    unsigned short usScCurrentThreshold = 0;







    return usScCurrentThreshold;
}














unsigned short NvRegister_GetHsed_OcCurrentThreshold( void )
{
    unsigned short usOcCurrentThreshold = 0;







    return usOcCurrentThreshold;
}















signed char NvRegister_GetAdieGain_AdieCodecRxGain( void )
{
    signed char cAdieCodecRxGain = 0;

    cAdieCodecRxGain = g_stNvRegister.stAdieGain.cAdieCodecRxGain;

    return cAdieCodecRxGain;
}














signed char NvRegister_GetAdieGain_AdieCodecTxGain( void )
{
    signed char cAdieCodecTxGain = 0;

    cAdieCodecTxGain = g_stNvRegister.stAdieGain.cAdieCodecTxGain;

    return cAdieCodecTxGain;
}
















unsigned char NvRegister_GetDataFlag( void )
{
    return g_stNvRegister.ucDataFlag;
}














int NvRegister_GetVoiceState( void )
{
    return g_iVoiceState;
}














void NvRegister_GetNvRegister( NvRegister* pstNvRegister )
{
    memcpy(pstNvRegister, &g_stNvRegister, sizeof(g_stNvRegister));
}















void NvRegister_SetDataFlag( unsigned char ucDataFlag )
{
    g_stNvRegister.ucDataFlag = ucDataFlag;
}














void NvRegister_SetVoiceState( int iVoiceState )
{
    g_iVoiceState = iVoiceState;
}














void NvRegister_SetNvRegister( NvRegister stNvRegister )
{
    memcpy(&g_stNvRegister, &stNvRegister, sizeof(g_stNvRegister));
}














void NvRegister_SetAkPowerState( int iAkPowerState )
{
    g_iAkPowerState = iAkPowerState;



}












int NvRegister_GetAkPowerState( void )
{



    return g_iAkPowerState;
}





