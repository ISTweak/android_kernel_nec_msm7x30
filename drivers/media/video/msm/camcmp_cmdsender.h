/* Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/











































#ifndef CAMCMP_CMDSENDER_H
#define CAMCMP_CMDSENDER_H




#include <linux/types.h>
#include <linux/kernel.h>


#include <media/camera_function.h>











#define CAMCOMBINE2(a,b) a##b
#define CAMCOMBINE3(a,b,c) a##b##c

















#define CAMCMP_LOG_DBG(fmt, args...) do { } while (0)
#define CAMCMP_LOG_INF(fmt, args...) do { } while (0)



#define CAMCMP_LOG_ERR(fmt, args...) pr_err("msm_camera:%s(%d) " fmt, __func__, __LINE__, ##args)




#define ALARM_LOG(fmt, args...) printk("[T][ARM]" fmt, ##args)
#define ALARM_EVENT_CAMERA  0x60
#define ALARM_EVENT_CAM_FW_DOWN_ERR  0x43
#define ALARM_INFO_CAMERA   0x10







#define CAMCMP_CALC_10000		10000	 
#define CAMCMP_CALC_1000		1000	
#define CAMCMP_CALC_100			100		
#define CAMCMP_CALC_10			10		
#define CAMCMP_CALC_ROUND_OFF	5		





enum otp_rom {
	CAMCMP_OTP0L = 0,		
	CAMCMP_OTP0M,			
	CAMCMP_OTP0H,			
	CAMCMP_OTP1L,			
	CAMCMP_OTP1M,			
	CAMCMP_OTP1H,			

	CAMCMP_OTP_ROM_NUM		
};






typedef enum {


	
	CAMCMP_CID_CHK_DEV_STS,			
	CAMCMP_CID_INIT_SET_1,			
	CAMCMP_CID_INIT_SET_2,			
	CAMCMP_CID_INIT_SET_3,			
	CAMCMP_CID_ROM_CORCT,			
	CAMCMP_CID_INIT_SET_4,			
	CAMCMP_CID_INIT_SET_5,			
	CAMCMP_CID_WB_AUTO,				
	CAMCMP_CID_WB_INCAND,			
	CAMCMP_CID_WB_DAYLIGHT,			
	CAMCMP_CID_WB_FLUORE,			
	CAMCMP_CID_WB_CLOUDY,			
	CAMCMP_CID_WB_LED,				
	CAMCMP_CID_NIGHT_OFF,			
	CAMCMP_CID_NIGHT_ON,			
	CAMCMP_CID_MOVIE,				
	CAMCMP_CID_CAP_SIZE,			
	CAMCMP_CID_MONI_SIZE,			
	CAMCMP_CID_MODE_CHG,			


	CAMCMP_CID_ZOOM_5M,				
	CAMCMP_CID_ZOOM_WQHD,			
	CAMCMP_CID_ZOOM_2M,				
	CAMCMP_CID_ZOOM_1M,				
	CAMCMP_CID_ZOOM_VGA,			
	CAMCMP_CID_ZOOM_HD_MV,			
	CAMCMP_CID_ZOOM_VGA_MV,			
	CAMCMP_CID_ZOOM_QVGA_MV,		
	CAMCMP_CID_ZOOM_QCIF_MV,		









	CAMCMP_CID_BRIGHTNESS,			
	CAMCMP_CID_EFFECT,				
	CAMCMP_CID_QUALITY,				
	CAMCMP_CID_INT_CLR,				
	CAMCMP_CID_AF_CANCEL,			
	CAMCMP_CID_AF_MODE,				
	CAMCMP_CID_MF_START,			
	CAMCMP_CID_AE_NOMAL,			
	CAMCMP_CID_AE_LONG,				
	CAMCMP_CID_PTNCHK_OFF,			
	CAMCMP_CID_PTNCHK_ON,			
	CAMCMP_CID_CHK_AF_LOCK,			
	CAMCMP_CID_CONF_THUMBNAIL,		
	CAMCMP_CID_JPEG_LIMIT,  		
	CAMCMP_CID_AF_RESTART_F, 		
	CAMCMP_CID_JPEG_INTSTS,			

	CAMCMP_CID_FLC_MODE,			


	CAMCMP_CID_CHK_MODE_STS,		
	CAMCMP_CID_MONI_REFLESH,		
	CAMCMP_CID_AF_MODE_MONI,		
	CAMCMP_CID_FRAME_POS,			
	CAMCMP_CID_SEARCH_AREA,			
	CAMCMP_CID_SET_AE_SUB,			
	CAMCMP_CID_PHOTOMETRY,          
	CAMCMP_CID_FREE_WEIGHT,         


	
	CAMCMP_CID_GET_OTP0L,			
	CAMCMP_CID_GET_OTP0M,			
	CAMCMP_CID_GET_OTP0H,			
	CAMCMP_CID_GET_OTP1L,			
	CAMCMP_CID_GET_OTP1M,			
	CAMCMP_CID_GET_OTP1H,			
	CAMCMP_CID_GET_OTP,				
	CAMCMP_CID_GET_INTSTS,			


	CAMCMP_CID_GET_EVALUATE,		
	CAMCMP_CID_GET_LENSPOS,			
	CAMCMP_CID_GET_AF_STEP,			
	CAMCMP_CID_GET_AESCL,			
	CAMCMP_CID_GET_SHT_TIME_H,		
	CAMCMP_CID_GET_SHT_TIME_L,		
	CAMCMP_CID_GET_AGC_SCL,			


	CAMCMP_CID_GET_AF_RESULT,		
	CAMCMP_CID_GET_AF_STATE,		



	CAMCMP_CID_GET_MANUAL_STEP,		
	CAMCMP_CID_GET_AREA_LOW_TYPE1,	
	CAMCMP_CID_GET_AREA_HIGH_TYPE1,	

	CAMCMP_CID_GET_JPG_STS,			
	CAMCMP_CID_GET_JPG_RETRY_CTL,	

	CAMCMP_CID_CAP_HALF_AE_CTRL,	
	CAMCMP_CID_SET_SHUT,			
	CAMCMP_CID_SET_GAIN,			
	CAMCMP_CID_CAP_GAINOFFSET,		
	CAMCMP_CID_PICTUER_NUM,			
	CAMCMP_CID_AE_STOP,				



	CAMCMP_CID_SCENE_CHANGE,					
	CAMCMP_CID_SCENE_ANGLE_AUTO,				
	CAMCMP_CID_SCENE_ANGLE_PORTRAIT,			
	CAMCMP_CID_SCENE_ANGLE_PORTRAIT_ILLUMI,		
	CAMCMP_CID_SCENE_ANGLE_LANDSCAPE,			
	CAMCMP_CID_SCENE_ANGLE_BACKLIGHT,			
	CAMCMP_CID_SCENE_ANGLE_NIGHT,				
	CAMCMP_CID_SCENE_ANGLE_PET,					
	CAMCMP_CID_SCENE_ANGLE_COOKING,				
	CAMCMP_CID_SCENE_ANGLE_SPORTS,				
	CAMCMP_CID_SCENE_ANGLE_OFF,					
	CAMCMP_CID_SCENE_ANGLE_HIGH_SENSITIVITY,	



	CAMCMP_CID_CAMERA_MODE,			



	CAMCMP_CID_HSIZE_MONI,			
	CAMCMP_CID_VSIZE_MONI,			
	CAMCMP_CID_AFC_STATUS,			
	CAMCMP_CID_SET_SAF_MODE,		
	CAMCMP_CID_DAC_CODE,			
	CAMCMP_CID_AFC_RESULT,			
	CAMCMP_CID_GET_SAF_MODE,		
	CAMCMP_CID_AWB_HOLD,			
	CAMCMP_CID_AE_HOLD,				
	CAMCMP_CID_GET_AE_SUB_STS,		



	CAMCMP_CID_VE023,			





	CAMCMP_CID_ISO,					





	CAMCMP_CID_SPEEDMOVIE,			


	
	CAMCMP_CID_MAX					












































































} camcmp_cmd_id_enum;




typedef enum {



	CAMCMP_BID_CAP_SIZE_5M,			
	CAMCMP_BID_CAP_SIZE_WQHD,		
	CAMCMP_BID_CAP_SIZE_2M,			
	CAMCMP_BID_CAP_SIZE_1M,			
	CAMCMP_BID_CAP_SIZE_VGA			













} camcmp_blank_cap_size_enum;




typedef enum {



	CAMCMP_BID_MONI_SIZE_HD,		

    CAMCMP_BID_MONI_SIZE_1M,

    CAMCMP_BID_MONI_SIZE_FWVGA,     
    CAMCMP_BID_MONI_SIZE_HD_HALF,   
	CAMCMP_BID_MONI_SIZE_VGA,		
	CAMCMP_BID_MONI_SIZE_QVGA,		
    CAMCMP_BID_MONI_SIZE_QCIF,		

    CAMCMP_BID_MONI_SIZE_854X480,










	        CAMCMP_BID_MONI_SIZE_HD_SHAKE,
	        CAMCMP_BID_MONI_SIZE_VGA_SHAKE,
	        CAMCMP_BID_MONI_SIZE_QVGA_SHAKE,
	        CAMCMP_BID_MONI_SIZE_QCIF_SHAKE













} camcmp_blank_moni_size_enum;




typedef enum {


	CAMCMP_BID_MONI_MODE,			
	CAMCMP_BID_MONI_REFRESH,		
	CAMCMP_BID_HALF_MODE,			
	CAMCMP_BID_CAP_MODE,			


	CAMCMP_BID_MOVIE_MODE,			









} camcmp_blank_chg_mode_enum;




typedef enum {


	CAMCMP_BID_ZOOM_0,				
	CAMCMP_BID_ZOOM_1,				
	CAMCMP_BID_ZOOM_2,				
	CAMCMP_BID_ZOOM_3,				
	CAMCMP_BID_ZOOM_4,				
	CAMCMP_BID_ZOOM_5,				
	CAMCMP_BID_ZOOM_6,				
	CAMCMP_BID_ZOOM_7,				
	CAMCMP_BID_ZOOM_8,				
	CAMCMP_BID_ZOOM_9,				


	CAMCMP_BID_ZOOM_10,				
	CAMCMP_BID_ZOOM_11,				
	CAMCMP_BID_ZOOM_12,				
	CAMCMP_BID_ZOOM_13,				
	CAMCMP_BID_ZOOM_14,				
	CAMCMP_BID_ZOOM_15				















} camcmp_blank_zoom_enum;




typedef enum {
	CAMCMP_BID_BRIGHT_M5,			
	CAMCMP_BID_BRIGHT_M4,			
	CAMCMP_BID_BRIGHT_M3,			
	CAMCMP_BID_BRIGHT_M2,			
	CAMCMP_BID_BRIGHT_M1,			
	CAMCMP_BID_BRIGHT_0,			
	CAMCMP_BID_BRIGHT_P1,			
	CAMCMP_BID_BRIGHT_P2,			
	CAMCMP_BID_BRIGHT_P3,			
	CAMCMP_BID_BRIGHT_P4,			
	CAMCMP_BID_BRIGHT_P5			
} camcmp_blank_bright_enum;




typedef enum {
	CAMCMP_BID_EFFECT_OFF,			
	CAMCMP_BID_EFFECT_MONO,			
	CAMCMP_BID_EFFECT_SEPIA,		
	CAMCMP_BID_EFFECT_NEGA			
} camcmp_blank_effect_enum;




typedef enum {
	CAMCMP_BID_Q_NORMAL,			
	CAMCMP_BID_Q_FINE,				
	CAMCMP_BID_Q_SFINE				
} camcmp_blank_quality_enum;




typedef enum {
	CAMCMP_BID_CLR_MODE,			
	CAMCMP_BID_CLR_AF_LOCK,			
	CAMCMP_BID_CLR_MODE_AF			
} camcmp_blank_int_clr_enum;




typedef enum {
	CAMCMP_BID_MODE_OFF,			 
	CAMCMP_BID_MODE_SAF,			
	CAMCMP_BID_MODE_MF				
} camcmp_blank_af_mode_enum;




typedef enum {
	CAMCMP_BID_MF_1M,				
	CAMCMP_BID_MF_MACRO,			
	CAMCMP_BID_MF_INF,				
	CAMCMP_BID_MF_0,				
	CAMCMP_BID_MF_CUSTOM			
} camcmp_blank_mf_pos_enum;




typedef enum {
	CAMCMP_BID_JPEG_LIMIT_SIZE_5M,			
	CAMCMP_BID_JPEG_LIMIT_SIZE_3M,			
	CAMCMP_BID_JPEG_LIMIT_SIZE_2M,			
	CAMCMP_BID_JPEG_LIMIT_SIZE_1M			
} camcmp_blank_jpeg_size_enum;








typedef enum {
  CAMCMP_BID_FLC_MODE_OFF   ,
  CAMCMP_BID_FLC_MODE_50HZ ,
  CAMCMP_BID_FLC_MODE_60HZ ,
	CAMCMP_BID_FLC_MODE_AUTO  
} camcmp_blank_flc_mode_enum;






typedef enum {
	CAMCMP_BID_SET_SHUT
}camcmp_blank_set_shut_enum;



typedef enum {
	CAMCMP_BID_SET_GAIN
}camcmp_blank_set_gain_enum;



typedef enum {
	CAMCMP_BID_CAP_NUM_1,			
	CAMCMP_BID_CAP_NUM_2			
} camcmp_blank_cap_num_enum;






typedef enum {
	CAMCMP_BID_SCENE_MODE_AUTO,						
	CAMCMP_BID_SCENE_MODE_PORTRAIT,					
	CAMCMP_BID_SCENE_MODE_PORTRAIT_ILLUMI,			
	CAMCMP_BID_SCENE_MODE_LANDSCAPE,				
	CAMCMP_BID_SCENE_MODE_BACKLIGHT,				
	CAMCMP_BID_SCENE_MODE_NIGHT,					
	CAMCMP_BID_SCENE_MODE_PET,						
	CAMCMP_BID_SCENE_MODE_COOKING,					
	CAMCMP_BID_SCENE_MODE_SPORTS,					
	CAMCMP_BID_SCENE_MODE_OFF,						
	CAMCMP_BID_SCENE_HIGH_SENSITIVITY,				
	CAMCMP_BID_SCENE_MODE_AUTO_FIXATION,			
	CAMCMP_BID_SCENE_MODE_PORTRAIT_FIXATION,		
	CAMCMP_BID_SCENE_MODE_PORTRAIT_ILLUMI_FIXATION,	
	CAMCMP_BID_SCENE_MODE_LANDSCAPE_FIXATION,		
	CAMCMP_BID_SCENE_MODE_BACKLIGHT_FIXATION,		
	CAMCMP_BID_SCENE_MODE_NIGHT_FIXATION,			
	CAMCMP_BID_SCENE_MODE_PET_FIXATION,				
	CAMCMP_BID_SCENE_MODE_COOKING_FIXATION,			
	CAMCMP_BID_SCENE_MODE_SPORTS_FIXATION,			
	CAMCMP_BID_SCENE_MODE_OFF_FIXATION,				
	CAMCMP_BID_SCENE_HIGH_SENSITIVITY_FIXATION		
} camcmp_blank_scene_enum;




typedef enum {
	CAMCMP_BID_SCENE_ANGLE_000,				
	CAMCMP_BID_SCENE_ANGLE_270,				
	CAMCMP_BID_SCENE_ANGLE_180,				
	CAMCMP_BID_SCENE_ANGLE_090				
} camcmp_blank_scene_angle_enum;



typedef enum {
	CAMCMP_BID_SCENE_SELECT_00
} camcmp_blank_camera_mode_enum;






typedef enum {
	CAMCMP_BID_SET_SAF_MODE_FINE,		
	CAMCMP_BID_SET_SAF_MODE_SINGLE,		
	CAMCMP_BID_SET_SAF_MODE_DOUBLE		
} camcmp_blank_set_saf_mode_enum;




typedef enum {
	CAMCMP_BID_DAC_CODE
} camcmp_blank_dac_code_enum;




typedef enum {
	CAMCMP_BID_AWB_AUTO,			
	CAMCMP_BID_AWB_INCAND,			
	CAMCMP_BID_AWB_FLUORE,			
	CAMCMP_BID_AWB_DAYLIGHT,		
	CAMCMP_BID_AWB_CLOUDY,			
	CAMCMP_BID_AWB_ON,				
} camcmp_blank_awb_kind_enum;




typedef enum {
	CAMCMP_BID_AE_ON,				
	CAMCMP_BID_AE_OFF				
} camcmp_blank_ae_kind_enum;




typedef enum {
	CAMCMP_BID_MODE_MONI_AFS,			
	CAMCMP_BID_MODE_MONI_AFC,			
	CAMCMP_BID_MODE_MONI_MF,			
	CAMCMP_BID_MODE_MONI_AF_OFF			
} camcmp_blank_af_mode_moni_enum;



typedef enum {
	CAMCMP_BID_AF_OPD4_HDELAY,
	CAMCMP_BID_AF_OPD4_VDELAY,
	CAMCMP_BID_AF_OPD4_HVALID,
	CAMCMP_BID_AF_OPD4_VVALID
} camcmp_blank_frame_pos_enum;



typedef enum {
	CAMCMP_BID_AF_AREA_LOW_TYPE1,
	CAMCMP_BID_AF_AREA_HIGH_TYPE1
} camcmp_blank_search_area_enum;



typedef enum {
	CAMCMP_BID_SET_AE_SUB,
}camcmp_blank_set_ae_sub_enum;




typedef enum {
	CAMCMP_BID_AE_OPD_HDELAY,
	CAMCMP_BID_AE_OPD_VDELAY,
	CAMCMP_BID_AE_OPD_HVALID,
	CAMCMP_BID_AE_OPD_VVALID,
} camcmp_blank_photometry;




typedef enum {
	CAMCMP_BID_AE_FREE_WEIGHT
} camcmp_blank_free_weight;








typedef enum {
	CAMCMP_BID_BRIGHTNESS_0,		
	CAMCMP_BID_BRIGHTNESS_1,		
	CAMCMP_BID_BRIGHTNESS_2,		
	CAMCMP_BID_BRIGHTNESS_3,		
    CAMCMP_BID_BRIGHTNESS_4,        
	CAMCMP_BID_BRIGHTNESS_5,		
	CAMCMP_BID_BRIGHTNESS_6,		
	CAMCMP_BID_BRIGHTNESS_7,		
	CAMCMP_BID_BRIGHTNESS_8,		
	CAMCMP_BID_BRIGHTNESS_9,		
	CAMCMP_BID_BRIGHTNESS_10,		
	CAMCMP_BID_BRIGHTNESS_11,		
	CAMCMP_BID_BRIGHTNESS_12		
} camcmp_blank_contrast_enum;








typedef enum {
	CAMCMP_BID_ISO_1600,			
	CAMCMP_BID_ISO_3200,			
	CAMCMP_BID_ISO_12800			
} camcmp_blank_iso_enum;











typedef struct {
	unsigned char*	p_buff;			
	uint32_t		size;			
} camcmp_buff_type;




typedef struct {
	uint32_t		blank_id;		
	void*			p_blank_data;	
} camcmp_blank_info_type;




typedef struct {
	uint32_t					cmd_id;				
	camcmp_blank_info_type*		p_blank_info;		
	uint32_t					blank_num;			
	void*						p_recieve_data;		
	uint32_t					recieve_num;		
} camcmp_cmd_info_type;


#define CAMCMP_SIZE_CMD(a)     (sizeof(a)/sizeof(camcmp_cmd_info_type))


#define CAMCMP_SIZE_BLKINF(a)  (sizeof(a)/sizeof(camcmp_blank_info_type))


#define CAMCMP_SIZE_REVINF(a)  (sizeof(a)/sizeof(uint32_t))




















int32_t camcmp_i2c_init(void* p_client);















int32_t camcmp_makecmd_init(void);















void camcmp_makecmd_get_version(uint16_t* p_ver, uint8_t* p_flg);

















int32_t camcmp_makecmd_correction(void* p_val, uint32_t num);
























int32_t camcmp_isp_trans(camcmp_cmd_info_type* p_info, uint32_t num);

#endif 
