/**********************************************************************
* File Name: arch/arm/mach-msm/qdsp5v2/NvRegister.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/



#ifndef _NV_REGISTER_H
#define _NV_REGISTER_H



















#include <linux/types.h>
#include <linux/ioctl.h>
#include <asm/sizes.h>

#include "linux/audio_compile_switch_apps.h"
#include "ak7837a_sndampi.h"




#define NV_REGISTER_DATA_FLAG_NO       0             
#define NV_REGISTER_DATA_FLAG_OK       1             
#define NV_REGISTER_DATA_FLAG_NG       2             


#define NV_REGISTER_VOICE_STATE_OFF    0             
#define NV_REGISTER_VOICE_STATE_ON     1             

#define NV_REGISTER_VE004_STATE_OFF    0           
#define NV_REGISTER_VE004_STATE_ON     1           





typedef struct NvRegister_NONCLIP_struct
{
    unsigned char                 ucDefault;                             
    unsigned char                 ucVoice;                               
    unsigned char                 ucAudio;                               
}NvRegister_NONCLIP;





typedef struct NvRegister_AK7837A_REC_struct
{
    unsigned char                 ucAlcOnOff;                            
    unsigned char                 ucGain4AlcOff;                         
    unsigned char                 ucAlcCtrl3;                            
    unsigned char                 ucAlcCtrl2;                            
    unsigned char                 ucAlcCtrl5;                            
    unsigned char                 ucAlcCtrl6;                            
}NvRegister_AK7837A_REC;




typedef struct NvRegister_AK7837A_SPK_struct
{
    unsigned char                 ucAlcOnOff;                            
    unsigned char                 ucGain4AlcOff;                         
    unsigned char                 ucAlcCtrl3;                            
    unsigned char                 ucAlcCtrl2;                            
    unsigned char                 ucAlcCtrl4;                            
    unsigned char                 ucAlcCtrl1;                            
}NvRegister_AK7837A_SPK;




typedef struct NvRegister_VE110_struct
{
    unsigned short                usScCurrentThreshold;                  
    unsigned short                usOcCurrentThreshold;                  
}NvRegister_VE110;






typedef struct NvRegister_ADIE_Gain_struct
{
    signed char                 cAdieCodecRxGain;                     
    signed char                 cAdieCodecTxGain;                     
}NvRegister_ADIE_Gain;






typedef struct NvRegister_struct
{
    unsigned char                 ucDataFlag;                            






    NvRegister_AK7837A_REC        stAk7837aRecV;                         
    NvRegister_AK7837A_REC        stAk7837aRecA;                         
    NvRegister_AK7837A_SPK        stAk7837aSpkV;                         
    NvRegister_AK7837A_SPK        stAk7837aSpkA;                         








    NvRegister_ADIE_Gain          stAdieGain;                            



}NvRegister;





extern void NvRegister_InitData( void );

extern unsigned char NvRegister_GetNonClip_Default( void );
extern unsigned char NvRegister_GetNonClip_Voice( void );
extern unsigned char NvRegister_GetNonClip_Audio( void );

extern unsigned char NvRegister_GetAK7837A_REC_ALCONOFF( void );
extern unsigned char NvRegister_GetAK7837A_REC_GAIN4ALCOFF( void );
extern unsigned char NvRegister_GetAK7837A_REC_ALCCTRL3( void );
extern unsigned char NvRegister_GetAK7837A_REC_ALCCTRL2( void );
extern unsigned char NvRegister_GetAK7837A_REC_ALCCTRL5( void );
extern unsigned char NvRegister_GetAK7837A_REC_ALCCTRL6( void );
extern unsigned char NvRegister_GetAK7837A_SPK_ALCONOFF( void );
extern unsigned char NvRegister_GetAK7837A_SPK_GAIN4ALCOFF( void );
extern unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL3( void );
extern unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL2( void );
extern unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL4( void );
extern unsigned char NvRegister_GetAK7837A_SPK_ALCCTRL1( void );

extern unsigned short NvRegister_GetHsed_ScCurrentThreshold( void );
extern unsigned short NvRegister_GetHsed_OcCurrentThreshold( void );



extern signed char NvRegister_GetAdieGain_AdieCodecRxGain( void );
extern signed char NvRegister_GetAdieGain_AdieCodecTxGain( void );




extern unsigned char NvRegister_GetDataFlag( void );
extern int  NvRegister_GetVoiceState( void );
extern void NvRegister_GetNvRegister( NvRegister* pstNvRegister );

extern void NvRegister_SetDataFlag( unsigned char ucDataFlag );
extern void NvRegister_SetVoiceState( int iVoiceState );
extern void NvRegister_SetNvRegister( NvRegister stNvRegister );


extern void NvRegister_SetAkPowerState( int iAkPowerState );
extern int  NvRegister_GetAkPowerState( void );



#endif 



