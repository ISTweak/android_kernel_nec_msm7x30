


#ifndef _AK7837A_SNDAMPI_H
#define _AK7837A_SNDAMPI_H
/*===========================================================================
 FILENAME : ak7837a_sndampi.h

 Copyright (C) 2010 NEC Corporation.
 No permission to use, copy, modify and distribute this software
 and its documentation for any purpose is granted.
 This software is provided under applicable license agreement only.
===========================================================================*/
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/






























#define AK7837A_STARTUP_WAIT_TIME                   35                            

#define AK7837A_ALC_CTRL_ON                         1                             
#define AK7837A_ALC_CTRL_OFF                        0                             


#define AK7837A_PM_OBS_SPEAKER_OFF           0                             
#define AK7837A_PM_OBS_SPEAKER_ON            100                           





#define AK7837A_ADDR_BASE                           0x00                          
#define AK7837A_ADDR(offset)                        (AK7837A_ADDR_BASE + offset)  
#define AK7837A_BUF(offset)                         (ak7837a_reg_buffer[offset])  
#define AK7837A_BUFFER_LENGTH                       1                             
#define AK7837A_REG_ON                              1                             
#define AK7837A_REG_OFF                             0                             

#define AK7837A_MODESELCT_SNDSEL_HANDSET            0x35
#define AK7837A_MODESELCT_SNDSEL_SPEAKER            0xCA





#define AK7837A_REG_01_SYSRST_SRST                  0xFF      
#define AK7837A_REG_02_PDNMODE_MUTE                 0x04      
#define AK7837A_REG_02_PDNMODE_PDN                  0x01      
#define AK7837A_REG_03_ALCCTRL4_VE253                0x1F      
#define AK7837A_REG_04_ALCCTRL1_SREFP               0x2F      
#define AK7837A_REG_05_ALCCTRL2_ZELMRVN             0x40      
#define AK7837A_REG_05_ALCCTRL2_ZELMSDN             0x20      
#define AK7837A_REG_05_ALCCTRL2_ZETM                0x18      
#define AK7837A_REG_05_ALCCTRL2_LMATP               0x06      
#define AK7837A_REG_06_ALCCTRL3_ALC                 0x80      
#define AK7837A_REG_06_ALCCTRL3_GAPSEL              0x20      
#define AK7837A_REG_06_ALCCTRL3_FRSEL               0x10      
#define AK7837A_REG_06_ALCCTRL3_FR                  0x08      
#define AK7837A_REG_06_ALCCTRL3_WTMP                0x06      
#define AK7837A_REG_06_ALCCTRL3_RGAINP              0x01      
#define AK7837A_REG_07_MODESELCT_SNDSEL             0xFF      
#define AK7837A_REG_08_GAIN4ALCOFF_GAIN             0x3F      
#define AK7837A_REG_09_FLAG_INTERR                  0x10      
#define AK7837A_REG_09_FLAG_VMROPEN                 0x08      
#define AK7837A_REG_09_FLAG_SHORT                   0x04      
#define AK7837A_REG_09_FLAG_LVLERR                  0x02      
#define AK7837A_REG_09_FLAG_THERR                   0x01      
#define AK7837A_REG_0A_ALCCTRL5_RTGT                0x0F      
#define AK7837A_REG_0B_ALCCTRL6_RREFP               0x3F      





#define AK7837A_GPIO_AUD_AMP_RST                     82       

#define AK7837A_GPIO_HIGH_VALUE                      1        
#define AK7837A_GPIO_LOW_VALUE                       0        






#define AK7837A_REG_00_RESERVED_INIT_VAL            0x00      
#define AK7837A_REG_01_SYSRST_INIT_VAL              0x00      
#define AK7837A_REG_02_PDNMODE_INIT_VAL             0x00      
#define AK7837A_REG_03_ALCCTRL4_INIT_VAL            0x12      
#define AK7837A_REG_04_ALCCTRL1_INIT_VAL            0x18      
#define AK7837A_REG_05_ALCCTRL2_INIT_VAL            0x40      
#define AK7837A_REG_06_ALCCTRL3_INIT_VAL            0x00      
#define AK7837A_REG_07_MODESELCT_INIT_VAL           0x35      
#define AK7837A_REG_08_GAIN4ALCOFF_INIT_VAL         0x18      
#define AK7837A_REG_09_FLAG_INIT_VAL                0x00      
#define AK7837A_REG_0A_ALCCTRL5_INIT_VAL            0x0B      
#define AK7837A_REG_0B_ALCCTRL6_INIT_VAL            0x1C      
#define AK7837A_REG_0C_RESERVED_INIT_VAL            0x00      
#define AK7837A_REG_0D_RESERVED_INIT_VAL            0x00      
#define AK7837A_REG_0E_RESERVED_INIT_VAL            0x00      
#define AK7837A_REG_0F_REVISION_INIT_VAL            0x01      






#define AK7837A_SET_REG_BUF(offset, data, bit, mask) \
        AK7837A_BUF( offset ) \
        = ( ( AK7837A_BUF( offset ) & (unsigned char)(~mask) ) | ( ( data << bit ) & mask) )



#define AK7837A_SET_REG_01_SYSRST_SRST(data) \
        MM_DBG("SET REG01 SYSRST[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_01_SYSRST     , data, AK7837A_REG_BIT_D0, AK7837A_REG_01_SYSRST_SRST      )

#define AK7837A_SET_REG_02_PDNMODE_MUTE(data) \
        MM_DBG("SET REG02 PDNMODE[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_02_PDNMODE    , data, AK7837A_REG_BIT_D2, AK7837A_REG_02_PDNMODE_MUTE     )

#define AK7837A_SET_REG_02_PDNMODE_PDN(data) \
        MM_DBG("SET REG02 PDNMODE[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_02_PDNMODE    , data, AK7837A_REG_BIT_D0, AK7837A_REG_02_PDNMODE_PDN      )

#define AK7837A_SET_REG_03_ALCCTRL4_VE253(data) \
        MM_DBG("SET REG03 ALCCTRL4[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_03_ALCCTRL4   , data, AK7837A_REG_BIT_D0, AK7837A_REG_03_ALCCTRL4_VE253    )

#define AK7837A_SET_REG_04_ALCCTRL1_SREFP(data) \
        MM_DBG("SET REG04 ALCCTRL1[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_04_ALCCTRL1   , data, AK7837A_REG_BIT_D0, AK7837A_REG_04_ALCCTRL1_SREFP   )

#define AK7837A_SET_REG_05_ALCCTRL2_ZELMRVN(data) \
        MM_DBG("SET REG05 ALCCTRL2[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_05_ALCCTRL2   , data, AK7837A_REG_BIT_D6, AK7837A_REG_05_ALCCTRL2_ZELMRVN )

#define AK7837A_SET_REG_05_ALCCTRL2_ZELMSDN(data) \
        MM_DBG("SET REG05 ALCCTRL2[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_05_ALCCTRL2   , data, AK7837A_REG_BIT_D5, AK7837A_REG_05_ALCCTRL2_ZELMSDN )

#define AK7837A_SET_REG_05_ALCCTRL2_ZETM(data) \
        MM_DBG("SET REG05 ALCCTRL2[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_05_ALCCTRL2   , data, AK7837A_REG_BIT_D3, AK7837A_REG_05_ALCCTRL2_ZETM    )

#define AK7837A_SET_REG_05_ALCCTRL2_LMATP(data) \
        MM_DBG("SET REG05 ALCCTRL2[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_05_ALCCTRL2   , data, AK7837A_REG_BIT_D1, AK7837A_REG_05_ALCCTRL2_LMATP   )

#define AK7837A_SET_REG_06_ALCCTRL3_ALC(data) \
        MM_DBG("SET REG06 ALCCTRL3[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_06_ALCCTRL3   , data, AK7837A_REG_BIT_D7, AK7837A_REG_06_ALCCTRL3_ALC     )

#define AK7837A_SET_REG_06_ALCCTRL3_GAPSEL(data) \
        MM_DBG("SET REG05 ALCCTRL2[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_06_ALCCTRL3   , data, AK7837A_REG_BIT_D5, AK7837A_REG_06_ALCCTRL3_GAPSEL  )

#define AK7837A_SET_REG_06_ALCCTRL3_FRSEL(data) \
        MM_DBG("SET REG06 ALCCTRL3[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_06_ALCCTRL3   , data, AK7837A_REG_BIT_D4, AK7837A_REG_06_ALCCTRL3_FRSEL   )

#define AK7837A_SET_REG_06_ALCCTRL3_FR(data) \
        MM_DBG("SET REG06 ALCCTRL3[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_06_ALCCTRL3   , data, AK7837A_REG_BIT_D3, AK7837A_REG_06_ALCCTRL3_FR      )

#define AK7837A_SET_REG_06_ALCCTRL3_WTMP(data) \
        MM_DBG("SET REG06 ALCCTRL3[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_06_ALCCTRL3   , data, AK7837A_REG_BIT_D1, AK7837A_REG_06_ALCCTRL3_WTMP    )

#define AK7837A_SET_REG_06_ALCCTRL3_RGAINP(data) \
        MM_DBG("SET REG06 ALCCTRL3[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_06_ALCCTRL3   , data, AK7837A_REG_BIT_D0, AK7837A_REG_06_ALCCTRL3_RGAINP  )

#define AK7837A_SET_REG_07_MODESELCT_SNDSEL(data) \
        MM_DBG("SET REG07 MODESELCT[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_07_MODESELCT  , data, AK7837A_REG_BIT_D0, AK7837A_REG_07_MODESELCT_SNDSEL )

#define AK7837A_SET_REG_08_GAIN4ALCOFF_GAIN(data) \
        MM_DBG("SET REG08 GAIN4ALCOFF[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_08_GAIN4ALCOFF, data, AK7837A_REG_BIT_D0, AK7837A_REG_08_GAIN4ALCOFF_GAIN )

#define AK7837A_SET_REG_0A_ALCCTRL5_RTGT(data) \
        MM_DBG("SET VE240 ALCCTRL5[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_0A_ALCCTRL5   , data, AK7837A_REG_BIT_D0, AK7837A_REG_0A_ALCCTRL5_RTGT    )

#define AK7837A_SET_REG_0B_ALCCTRL6_RREFP(data) \
        MM_DBG("SET REG0B ALCCTRL6[0x%x]\n", data); \
        AK7837A_SET_REG_BUF( AK7837A_REG_0B_ALCCTRL6   , data, AK7837A_REG_BIT_D0, AK7837A_REG_0B_ALCCTRL6_RREFP   )






#define AK7837A_GET_REG(offset, bit, mask) \
        ( ( AK7837A_BUF( offset ) & mask ) >> bit )


#define AK7837A_GET_REG_09_FLAG_INTERR \
        AK7837A_GET_REG( AK7837A_REG_09_FLAG, AK7837A_REG_BIT_D4, AK7837A_REG_09_FLAG_INTERR  )

#define AK7837A_GET_REG_09_FLAG_VMROPEN \
        AK7837A_GET_REG( AK7837A_REG_09_FLAG, AK7837A_REG_BIT_D3, AK7837A_REG_09_FLAG_VMROPEN )

#define AK7837A_GET_REG_09_FLAG_SHORT \
        AK7837A_GET_REG( AK7837A_REG_09_FLAG, AK7837A_REG_BIT_D2, AK7837A_REG_09_FLAG_SHORT   )

#define AK7837A_GET_REG_09_FLAG_LVLERR \
        AK7837A_GET_REG( AK7837A_REG_09_FLAG, AK7837A_REG_BIT_D1, AK7837A_REG_09_FLAG_LVLERR  )

#define AK7837A_GET_REG_09_FLAG_THERR \
        AK7837A_GET_REG( AK7837A_REG_09_FLAG, AK7837A_REG_BIT_D0, AK7837A_REG_09_FLAG_THERR   )







typedef enum {
  AK7837A_REG_00_RESERVED,          
  AK7837A_REG_01_SYSRST,            
  AK7837A_REG_02_PDNMODE,           
  AK7837A_REG_03_ALCCTRL4,          
  AK7837A_REG_04_ALCCTRL1,          
  AK7837A_REG_05_ALCCTRL2,          
  AK7837A_REG_06_ALCCTRL3,          
  AK7837A_REG_07_MODESELCT,         
  AK7837A_REG_08_GAIN4ALCOFF,       
  AK7837A_REG_09_FLAG,              
  AK7837A_REG_0A_ALCCTRL5,          
  AK7837A_REG_0B_ALCCTRL6,          
  AK7837A_REG_0C_RESERVED,          
  AK7837A_REG_0D_RESERVED,          
  AK7837A_REG_0E_RESERVED,          
  AK7837A_REG_0F_REVISION,          
  AK7837A_REG_MAX,
} ak7837a_register_type;


typedef enum {
  AK7837A_REG_BIT_D0,                
  AK7837A_REG_BIT_D1,                
  AK7837A_REG_BIT_D2,                
  AK7837A_REG_BIT_D3,                
  AK7837A_REG_BIT_D4,                
  AK7837A_REG_BIT_D5,                
  AK7837A_REG_BIT_D6,                
  AK7837A_REG_BIT_D7,                
} ak7837a_reg_bit_type;


typedef enum {
  AK7837A_DEVICE_HANDSET = 0,                          
  AK7837A_DEVICE_FMRADIO_HANDSET,                      
  AK7837A_DEVICE_SPEAKER_STEREO,                       
  AK7837A_DEVICE_FMRADIO_SPEAKER,                      
  AK7837A_DEVICE_HEADSET_STEREO_SPEAKER_STEREO,        
  AK7837A_DEVICE_PTT_SPEAKER_STEREO,                   
  AK7837A_DEVICE_MAX,                                  
} ak7837a_device_type;


typedef enum {
  AK7837A_PROC_DEVICE_HANDSET = 0,                     
  AK7837A_PROC_DEVICE_SPEAKER,                         
  AK7837A_PROC_DEVICE_MAX,                             
  AK7837A_PROC_DEVICE_INVALID = AK7837A_DEVICE_MAX,    
} ak7837a_proc_device_type;







typedef struct{
  unsigned char   spk_rec_mode;         
  unsigned char   alc_ctrl3;            
  unsigned char   alc_ctrl2;            
  unsigned char   alc_ctrl5;            
  unsigned char   alc_ctrl6;            
  unsigned char   alc_ctrl4;            
  unsigned char   alc_ctrl1;            
  unsigned char   gain_4_alc_off;       
} ak7837a_cal_type;



typedef enum {
  AK7837A_SP_OFF = 0,                
  AK7837A_SP_ON,                     
} ak7837a_sp_state_type;


#endif 



