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



































































#include <linux/delay.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <media/msm_camera.h>
#include <mach/gpio.h>
#include <mach/vreg.h>  
#include <mach/camera.h>
#include "ius006f.h"
#include "camcmp_cmdsender.h"  










#include <linux/clk.h>














#define IUS006F_CHECK_STATE_WAITMAX	800			 
#define IUS006F_CHECK_STATE_WAIT	1			 
#define IUS006F_FRAME_RATE_WAIT		3           
#define IUS006F_AF_STATE_ERR		255			
#define IUS006F_AF_LOCK_DONE		0x00000010	 

static struct timer_list timer;					





enum ius006f_fps_mode {
	FPS_MODE_MONI = 0,	
	
	FPS_MODE_CAPT,		
	FPS_MODE_MOVIE,		
	

	FPS_MODE_NUM
};



enum otp_area_1{
	OTP0 = 0,
	OTP1 = 1
};

enum otp_area_2{
	OTP_L = 0,
	OTP_M,
	OTP_H
};



#define IUS006F_WAIT_20					20		
#define IUS006F_WAIT_50					50		
#define IUS006F_POWER_WAIT				5			
#define IUS006F_POWER_OFF_IOVD			15			
#define IUS006F_POWER_ON_NCYC			5		
#define IUS006F_POWER_ON_T1				5		
#define IUS006F_POWER_ON_T2				200		
#define IUS006F_POWER_ON_T3				15		
#define IUS006F_POWER_ON_T4				6		
#define IUS006F_POWER_OFF_T1			41		











#define IUS006F_GPIO_CAM_STBY			25		













#define IUS006F_FPS_15					300		
#define IUS006F_FPS_75					75		
#define IUS006F_FRAME_DEF				34		









#define IUS006F_DIAG_SUCCESS            0
#define IUS006F_DIAG_ACT_ERR            1
#define IUS006F_DIAG_PARAM_ERR          2
#define IUS006F_DIAG_STATE_ERR          3
#define IUS006F_OTP_BIT_MIN             0		
#define IUS006F_OTP_BIT_MAX             31		


#define IUS006F_SENSOR_PAT_CHG_SLEEP	5		
#define IUS006F_SENSOR_PAT_CHG_COUNT	300		


#define IUS006F_GPIO_HIGH		1
#define IUS006F_GPIO_LOW		0
#define IUS006F_GPIO_4			4
#define IUS006F_GPIO_5			5
#define IUS006F_GPIO_6			6
#define IUS006F_GPIO_7			7
#define IUS006F_GPIO_8			8
#define IUS006F_GPIO_9			9
#define IUS006F_GPIO_10			10
#define IUS006F_GPIO_11			11
#define IUS006F_GPIO_CNT		8





#define D_CAM_SHSPEED_SUB		 1	
#define D_CAM_SHSPEED_MAIN		32	
#define D_CAM_REDUCT_SUB		 1  
#define D_CAM_REDUCT_MAIN		 2  
#define D_CAM_RIZE_SUB			 2  
#define D_CAM_RIZE_MAIN			 1  





static int ius006f_set_af_mode(struct msm_sync *sync,struct af_mode_cfg *af_mode_chg);		
static int ius006f_set_default_focus(void);													
static int ius006f_af_start(struct msm_sync *sync);											
static int ius006f_get_af_pos(struct get_af_pos_cfg *af_pos);								
static int ius006f_get_moni_gain(struct get_monigain_cfg *moni_gain);						
static int ius006f_get_reg_ver(struct get_reg_ver_cfg *get_reg_ver);						
static int ius006f_set_wb(int8_t wb);														
static int ius006f_set_jpeg_quality(int8_t jpeg_quality);									

int ius006f_sensor_release(void);															




static int ius006f_get_afc_status(uint8_t *p_get_afc_status);
static int ius006f_get_af_state(uint8_t *p_af_state);
static void ius006f_afc_single(int8_t lens_position, uint8_t set_saf_mode);
static int ius006f_set_saf_mode(uint8_t set_saf_mode);
static int ius006f_set_afc_lens(int8_t lens_position);
static void ius006f_afc_otp_read(int8_t otp_num, uint16_t *p_otp_data);
static uint32_t ius006f_getDacCode(int aDacType);
static void ius006f_set_afc_single(void);
static int ius006f_get_afc_result(uint8_t *p_af_result);
static int ius006f_get_saf_mode(uint8_t *p_saf_mode);
static int ius006f_set_awb_hold(uint8_t set_awb_hold);
static int ius006f_set_ae_hold(uint8_t set_ae_hold);
static int ius006f_get_af_wnd3a(uint16_t *p_af_step);
static int ius006f_set_af_search_area(int lens_position, uint32_t *low, uint32_t *higt);
static void ius006f_af_status_change(sensor_af_status_t next_af_status);
static void ius006f_frame_pos_constraint(struct t_FramePosition_DRV *frame_position);
static uint16_t ius006f_af_search_step_cal(uint16_t VCMslope, uint8_t cam_search);
static int ius006f_set_weightmode(struct T_AfSettingInfo set_af_setting_info);
static int ius006f_set_free_weight(int8_t free_weight_f);
static int ius006f_afs_stop(void);


static int ius006f_poweroff(void);
static void ius006f_probe_init_done(const struct msm_camera_sensor_info *data);




struct ius006f_work {
	struct work_struct work;
};
static struct ius006f_work *ius006f_sensorw;
static struct i2c_client *ius006f_client;

struct ius006f_ctrl {
	const struct msm_camera_sensor_info *sensordata;	

	int sensormode;									
	int af_mode;									
	uint32_t otp_rom_data[CAMCMP_OTP_ROM_NUM];		
	int prev_res;									 
	uint8_t af_cancel_onoff;						
	uint16_t init_curr_lens_pos;					
    int8_t night_mode;								



	int8_t afc_mode;									
	int8_t inf_over_search;							



};






static uint16_t ius006f_fps_list[] = { IUS006F_FPS_15, IUS006F_FPS_75, IUS006F_FPS_15};





static struct ius006f_ctrl *ius006f_ctrl;
static DECLARE_WAIT_QUEUE_HEAD(ius006f_wait_queue);
DEFINE_MUTEX(ius006f_mut);

static uint32_t af_start_after_cnt = 0;				 




static uint32_t afc_lock_wait_cnt  = 0;










static uint16_t ius006f_calc_msec_from_fps(uint8_t frame)
{
	uint32_t msec = 0;	
	uint32_t calc = 0;
	uint16_t mode_fps = 0;	
	uint8_t vcnt = 1;

	
	switch (ius006f_ctrl->sensormode) {
	case SENSOR_PREVIEW_MODE:
	case SENSOR_HALF_MODE:
		mode_fps = ius006f_fps_list[FPS_MODE_MONI];
		vcnt = 1;    
		break;
	case SENSOR_SNAPSHOT_MODE:
		mode_fps = ius006f_fps_list[FPS_MODE_CAPT];
		vcnt = 1;    
		break;
	case SENSOR_MOVIE_MODE:
		mode_fps = ius006f_fps_list[FPS_MODE_MOVIE];
		break;
	default:
		return 0;
	}

	
	if (ius006f_ctrl->night_mode == CAMERA_SCENE_MODE_NIGHT) {
		vcnt = 4;
	}

	
	
	msec  = CAMCMP_CALC_1000 * frame * CAMCMP_CALC_10;
	calc = msec;
	msec = (msec / mode_fps) * vcnt;
	if((calc % mode_fps) != 0) {
		msec++;			
	}

	return msec;
}























static int32_t ius006f_change_mode_af(int mode, enum msm_sensor_onoff af_on)
{
	int32_t rc = 0;
	
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type intclr   = {0, NULL};
	camcmp_blank_info_type modechg  = {0, NULL};

	
	
	intclr.blank_id = CAMCMP_BID_CLR_MODE;
	if (af_on == SENSOR_ON) { 
		intclr.blank_id = CAMCMP_BID_CLR_MODE_AF;
	}
	
	cmd_info[0].cmd_id = CAMCMP_CID_INT_CLR;
	cmd_info[0].p_blank_info = &intclr;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(intclr);


	
	
	switch (mode) {
	
	case SENSOR_PREVIEW_MODE:
	case SENSOR_MOVIE_MODE:
		if ( (ius006f_ctrl->sensormode == SENSOR_PREVIEW_MODE) || 
		     (ius006f_ctrl->sensormode == SENSOR_MOVIE_MODE) ) {
			
			modechg.blank_id = CAMCMP_BID_MONI_REFRESH;
		}
		else {
			
			modechg.blank_id = CAMCMP_BID_MONI_MODE;
		}
		break;
	
	case SENSOR_HALF_MODE:
		modechg.blank_id = CAMCMP_BID_HALF_MODE;
		break;
	
	case SENSOR_SNAPSHOT_MODE:
		modechg.blank_id = CAMCMP_BID_CAP_MODE;
		break;




	
	case SENSOR_VIDEO_120FPS_MODE:
		modechg.blank_id = CAMCMP_BID_MOVIE_MODE;
		break;




	default:
		CAMCMP_LOG_ERR("input failed! mode=%d\n", mode);
		
		return -EINVAL;
	}

	
	cmd_info[1].cmd_id = CAMCMP_CID_MODE_CHG;
	cmd_info[1].p_blank_info = &modechg;
	cmd_info[1].blank_num = CAMCMP_SIZE_BLKINF(modechg);

	CAMCMP_LOG_DBG("%d -> %d \n", ius006f_ctrl->sensormode, mode);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	
	ius006f_ctrl->sensormode = mode;

	return 0;
}












static int32_t ius006f_change_mode(int mode)
{
	return ius006f_change_mode_af(mode, SENSOR_OFF); 
}








static E_IMAGE_SHAKE_KIND ius006f_image_shake_judge(uint32_t shut_speed_high, uint32_t shut_speed_low)
{
	uint32_t           sht_time      = 0;                       
	uint32_t           sht_threshold = 0;                       
	E_IMAGE_SHAKE_KIND ret           = E_IMAGE_SHAKE_ERROR;     
	
	
    sht_time = (((shut_speed_high & 0x0000FFFF)<<16) | (shut_speed_low & 0x0000FFFF));
    
    CAMCMP_LOG_DBG("sht_time =%x \n", sht_time);
    
    
    
    sht_threshold = (D_CAM_SHSPEED_SUB * 1000000) / D_CAM_SHSPEED_MAIN;

    CAMCMP_LOG_DBG("sht_threshold =%x \n", sht_threshold);

	
    if( sht_threshold < sht_time )
    {
		
		ret = E_IMAGE_SHAKE_ON;
	}
	else
	{
		
		ret = E_IMAGE_SHAKE_OFF;
	}
	
    CAMCMP_LOG_DBG("judge ret =%d \n", ret);
	
	return ret;
	
}


static void ius006f_cal_manual_ae(uint32_t shut_speed0, uint32_t shut_speed1, uint32_t agc_scl, uint32_t *p_set_speed, uint32_t *p_set_agc)
{
	uint32_t           sht_time          = 0;                       
	uint32_t           reduct_threshold  = 0;                       
	uint32_t           rize_threshold    = 0;                       
	uint32_t           cap_sht           = 0;                       
	uint32_t           cap_agc           = 0;                       
	uint32_t           much              = 0;
	
	
    sht_time = (((shut_speed0 & 0x0000FFFF)<<16) | (shut_speed1 & 0x0000FFFF));
    CAMCMP_LOG_DBG("sht_time =%x \n", sht_time);

    
    reduct_threshold = (D_CAM_REDUCT_SUB * 10000) / D_CAM_REDUCT_MAIN;
    CAMCMP_LOG_DBG("reduct_threshold =%x \n", reduct_threshold);

    
    cap_sht = (sht_time / 100) * reduct_threshold;
    CAMCMP_LOG_DBG("cap_sht =%x \n", cap_sht);

    
    much = cap_sht % 10000;

    
    if( much < 5000)
    {
        cap_sht = cap_sht / 10000;
    }
    else
    {
        cap_sht = (cap_sht / 10000) + 1;
    }

    CAMCMP_LOG_DBG("cap_sht =%x \n", cap_sht);

    
    
    rize_threshold =  (D_CAM_RIZE_SUB * 10000) / D_CAM_RIZE_MAIN;
    CAMCMP_LOG_DBG("rize_threshold =%x \n", rize_threshold);

    
    rize_threshold *= 1024;

    
    much = rize_threshold % 10000;

    
    if( much < 5000)
    {
        cap_agc = agc_scl + (rize_threshold / 10000);
    }
    else
    {
        cap_agc = agc_scl + ((rize_threshold / 10000) + 1);
    }
    CAMCMP_LOG_DBG("cap_agc =%x \n", cap_agc);
    
    
    *p_set_speed = cap_sht;
    *p_set_agc   = cap_agc;
    
}





static int ius006f_get_exif_param(struct get_exif_param_cfg* exif_param)
{
	int rc                  = 0;
	uint32_t shut_speed0    = 0;           
	uint32_t shut_speed1    = 0;           
	uint32_t sht_time       = 0;           
    int      agc_scl        = 0;           

	camcmp_cmd_info_type cmd_info1[] = {{0, NULL, 0, NULL, 0}};

	
	
	
	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_H;
	cmd_info1[0].p_recieve_data = &shut_speed0;
	cmd_info1[0].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans error rc = %d\n LINE = %d\n",
							rc, __LINE__);
		return -EFAULT;
	}else
	{
		
	}

	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_L;
	cmd_info1[0].p_recieve_data = &shut_speed1;
	cmd_info1[0].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans error rc = %d\n LINE = %d\n",
							rc, __LINE__);
		return -EFAULT;
	}else
	{
		
	}

	
	sht_time = (((shut_speed0 & 0x0000FFFF)<<16) | (shut_speed1 & 0x0000FFFF));
	CAMCMP_LOG_DBG("sht_time =%x \n", sht_time);

	
	exif_param->shutter_speed = sht_time;

	
	
	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_AGC_SCL;
	cmd_info1[0].p_recieve_data = &agc_scl;
	cmd_info1[0].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("camcmp_isp_trans error rc = %d\n LINE = %d\n",
							rc, __LINE__);
		return -EFAULT;
	}
	else
	{
		
	}

	CAMCMP_LOG_DBG("AGC_gain_0=%x \n", agc_scl);

	
	exif_param->AGC_gain = agc_scl;

	return rc;
}



static int ius006f_poweroff(void)
{
	uint16_t power_off_t1 = 0;	
	uint16_t calc = 0;
	uint32_t low = 0;
	uint32_t higt = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type mf_pos = {0, NULL};
	camcmp_blank_info_type af_mode = {0, NULL};
	camcmp_blank_info_type search_area[] = {{0, NULL}, {0, NULL}};
	uint32_t af_lens_pos = 0;
	int rc;

	CAMCMP_LOG_DBG("%s start\n", __func__);
	
	
	if(ius006f_ctrl)
	{
    	
    	cmd_info[0].cmd_id = CAMCMP_CID_GET_LENSPOS;
    	cmd_info[0].p_recieve_data = &af_lens_pos;
    	cmd_info[0].recieve_num = 1;

    	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    	if (rc < 0) {
    		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
    		return -EFAULT;
    	}

        
        if(af_lens_pos != 0)
        {
    		
    		search_area[0].blank_id     = CAMCMP_BID_AF_AREA_LOW_TYPE1;
    		search_area[0].p_blank_data = &low;
    		search_area[1].blank_id     = CAMCMP_BID_AF_AREA_HIGH_TYPE1;
    		search_area[1].p_blank_data = &higt;
    		cmd_info[0].cmd_id = CAMCMP_CID_SEARCH_AREA;
    		cmd_info[0].p_blank_info = search_area;
    		cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(search_area);
    		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    		if (rc < 0) {
    			CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",rc);
    		}

    		
    		af_mode.blank_id = CAMCMP_BID_MODE_MONI_MF;
    		cmd_info[0].cmd_id = CAMCMP_CID_AF_MODE_MONI;
    		cmd_info[0].p_blank_info = &af_mode;
    		cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(af_mode);

    		
    		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    		if (rc < 0) {
    			CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
    		}

    		
    		ius006f_change_mode(SENSOR_PREVIEW_MODE);

    		
    		mf_pos.blank_id = CAMCMP_BID_MF_0;
    		cmd_info[0].cmd_id = CAMCMP_CID_MF_START;
    		cmd_info[0].p_blank_info = &mf_pos;
    		cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(mf_pos);

    		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    		if (rc < 0) {
    			CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
    		}
        }
		
		gpio_direction_output(IUS006F_GPIO_CAM_STBY, 0);
		gpio_free(IUS006F_GPIO_CAM_STBY);

		
		power_off_t1 = ius006f_calc_msec_from_fps(IUS006F_POWER_OFF_T1);
		calc = power_off_t1;
		power_off_t1 /= CAMCMP_CALC_10;
		if((calc % CAMCMP_CALC_10) != 0) {
			power_off_t1++;		
		}
		CAMCMP_LOG_DBG("T1: Sleep wait time = %d\n", power_off_t1);
		msleep(power_off_t1);

		ius006f_probe_init_done(ius006f_ctrl->sensordata);

		if (ius006f_ctrl) {
			kfree(ius006f_ctrl);
			ius006f_ctrl = NULL;
		}
	}

	CAMCMP_LOG_DBG("%s completed\n", __func__);
	
	return 0;
}



















static int32_t ius006f_video_config(int prev_mode, int res, int set_camera_mode)





{


	int32_t rc = 0;




	int mode = SENSOR_PREVIEW_MODE;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type moni_size = {0, NULL};





	
	if(set_camera_mode == MODE_SPEED_MOVIE) {
		
		
		cmd_info[0].cmd_id = CAMCMP_CID_SPEEDMOVIE;
		
		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (rc != 0) {
			CAMCMP_LOG_ERR("camcmp_isp_trans error:%d\n", __LINE__);
			return -EFAULT;
		}
	}





	
	


	
	switch (res)
	{
		case SENSOR_CAMERA_HD_SIZE:			
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_HD;
			mode = SENSOR_PREVIEW_MODE;
			break;

        case SENSOR_CAMERA_1MP_SIZE:
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_1M;
			mode = SENSOR_PREVIEW_MODE;
			break;


	    case SENSOR_CAMERA_FWVGA_SIZE:     
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_FWVGA;
			mode = SENSOR_PREVIEW_MODE;
			break;

        case SENSOR_CAMERA_HD_HALF_SIZE :
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_HD_HALF;
			mode = SENSOR_PREVIEW_MODE;
            break;

		case SENSOR_CAMERA_VGA_SIZE:		
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_VGA;
			mode = SENSOR_PREVIEW_MODE;
			break;

		case SENSOR_CAMERA_QVGA_SIZE:		
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_QVGA;
			mode = SENSOR_PREVIEW_MODE;
			break;

		case SENSOR_CAMERA_QCIF_SIZE:		
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_QCIF;
			mode = SENSOR_PREVIEW_MODE;
			break;









		case SENSOR_CAMERA_HD_SIZE_SHAKE:
			break;
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_HD_SHAKE;
			mode               = SENSOR_PREVIEW_MODE;
		case SENSOR_CAMERA_VGA_SIZE_SHAKE:
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_VGA_SHAKE;
			mode               = SENSOR_PREVIEW_MODE;
			break;
		case SENSOR_CAMERA_QVGA_SIZE_SHAKE:
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_QVGA_SHAKE;
			mode               = SENSOR_PREVIEW_MODE;
			break;
		case SENSOR_CAMERA_QCIF_SIZE_SHAKE:
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_QCIF_SHAKE;
			mode               = SENSOR_PREVIEW_MODE;
			break;









		case SENSOR_854X480_SIZE:
			moni_size.blank_id = CAMCMP_BID_MONI_SIZE_854X480;
			mode               = SENSOR_PREVIEW_MODE;
			break;

		default:
			return -EINVAL;
	}





















    
    if(prev_mode == SENSOR_PREVIEW_MODE || prev_mode == SENSOR_MOVIE_MODE)
    {
        
        mode = SENSOR_PREVIEW_MODE;
    

        
        if(prev_mode == SENSOR_MOVIE_MODE && set_camera_mode == MODE_SPEED_MOVIE)
        {
            
			mode = SENSOR_VIDEO_120FPS_MODE;
        }

    }
    else
    {
		CAMCMP_LOG_ERR("sensor previwe mode -failed-\n");
        return -EINVAL;
    }






















	
	cmd_info[0].cmd_id = CAMCMP_CID_MONI_SIZE;
	cmd_info[0].p_blank_info = &moni_size;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(moni_size);

	CAMCMP_LOG_DBG("sensor mode %d->%d\n", ius006f_ctrl->sensormode, mode);
	CAMCMP_LOG_DBG("moni size %d->%d\n", ius006f_ctrl->prev_res, res);


    
    if(ius006f_ctrl->sensormode != mode || ius006f_ctrl->prev_res != res)
    {
        
		rc = camcmp_isp_trans(cmd_info, 1);






		if (rc < 0) {
			CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
			return -EFAULT;
		}
		ius006f_ctrl->prev_res = res;		

		
		rc = ius006f_change_mode(mode);
		if (rc < 0) {
			CAMCMP_LOG_ERR("ius006f_change_mode failed. rc = %d\n", rc);
			return -EFAULT;
		}
	}









	return rc;
}























static int32_t ius006f_snapshot_config(int32_t res)
{

	camcmp_cmd_info_type cmd_info[]  = { {0, NULL, 0, NULL, 0} }; 
	camcmp_blank_info_type cap_size  = {0, NULL};












	int32_t ret = 0;

	CAMCMP_LOG_DBG("start here !!!\n");

	


	switch (res)
	{
		case SENSOR_CAMERA_VGA_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_VGA;
			break;
		case SENSOR_CAMERA_1MP_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_1M;
			break;
		case SENSOR_CAMERA_2MP_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_2M;
			break;
		case SENSOR_CAMERA_WQHD_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_WQHD;
			break;
		case SENSOR_CAMERA_5MP_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_5M;
			break;
		default:
			return -EINVAL;
	}





















	
	cmd_info[0].cmd_id = CAMCMP_CID_CAP_SIZE;
	cmd_info[0].p_blank_info = &cap_size;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(cap_size);

	
	ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (ret < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans error [ret:%d ]\n",ret);
		return ret;
	}

	
	CAMCMP_LOG_DBG("start mode change => capture\n");
	ret = ius006f_change_mode(SENSOR_SNAPSHOT_MODE);
	if (ret < 0) {
		CAMCMP_LOG_ERR("ius006f_change_mode error [ret:%d ]\n",ret);
		return ret;
	}





























































































	CAMCMP_LOG_DBG("succsess\n");
	return ret;


}

























static int32_t ius006f_raw_snapshot_config(int res)
{
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0} }; 
	camcmp_blank_info_type cap_size  = {0, NULL};
	
	uint32_t               jpg_sts       = 0;    
	uint32_t               jpg_retry     = 0;    
	int32_t                cap_cnt       = 0;    
	uint8_t                intsts_clear  = false;
	uint32_t               intsts        = 0;    
	int32_t                check_cnt     = 0;
	

	int32_t                ret = 0;              
	CAMCMP_LOG_DBG("start here !!!\n");

	


	switch (res)
	{
		case SENSOR_CAMERA_VGA_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_VGA;
			break;
		case SENSOR_CAMERA_1MP_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_1M;
			break;
		case SENSOR_CAMERA_2MP_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_2M;
			break;
		case SENSOR_CAMERA_WQHD_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_WQHD;
			break;
		case SENSOR_CAMERA_5MP_SIZE:		
			cap_size.blank_id = CAMCMP_BID_CAP_SIZE_5M;
			break;
		default:
			return -EINVAL;
	}





















	
	
	cmd_info[0].cmd_id = CAMCMP_CID_CAP_SIZE;
	cmd_info[0].p_blank_info = &cap_size;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(cap_size);

	
	ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (ret < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans fail [RC:%d]\n",ret);
		return -EFAULT;
	}

	
	
	CAMCMP_LOG_DBG("start mode change => capture\n");
	ret = ius006f_change_mode(SENSOR_SNAPSHOT_MODE);
	if (ret < 0) {
		CAMCMP_LOG_ERR("ius006f_change_mode fail [RC:%d]\n",ret);
		return ret;
	}

	
	
	
	
	memset( cmd_info, 0, sizeof(cmd_info) );
	cmd_info[0].cmd_id         = CAMCMP_CID_GET_JPG_RETRY_CTL;
	cmd_info[0].p_recieve_data = &jpg_retry;
	cmd_info[0].recieve_num    = 1;
	
	ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (ret < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
		return ret;
	}

	if ( (jpg_retry&0x00000080) ) {
		
		jpg_retry     = jpg_retry & 0x0000007F;
	} else {
		
		jpg_retry = 0;
	}

	for (cap_cnt=0; cap_cnt < jpg_retry+1; cap_cnt++) {
		memset( cmd_info, 0, sizeof(cmd_info) );
		cmd_info[0].cmd_id       = CAMCMP_CID_JPEG_INTSTS;
		cmd_info[0].p_blank_info = NULL;
		cmd_info[0].blank_num    = 0;
		
		ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (ret < 0) {
			CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
			return ret;
		}

		memset( cmd_info, 0, sizeof(cmd_info) );
		cmd_info[0].cmd_id       = CAMCMP_CID_GET_INTSTS;
		cmd_info[0].p_recieve_data = &intsts;
		cmd_info[0].recieve_num    = 1;
		intsts_clear = true;
		check_cnt    = 0;
		while(intsts_clear) {
			msleep(10);
			
			CAMCMP_LOG_DBG("CAMCMP_CID_GET_INTSTS Clear Check \n");
			ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
			if (ret < 0) {
				CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
				return ret;
			}
			if ((intsts & 0x00000004)==0){
				CAMCMP_LOG_DBG("CAMCMP_CID_GET_INTSTS Clear Check OK \n");
				intsts_clear = false;
			}
			check_cnt++;
			if ( check_cnt == 13 ){
				CAMCMP_LOG_DBG("CAMCMP_CID_GET_INTSTS Clear Check Over \n");
				intsts_clear = false;
			}
		}

		memset( cmd_info, 0, sizeof(cmd_info) );
		cmd_info[0].cmd_id       = CAMCMP_CID_GET_JPG_STS;
		cmd_info[0].p_recieve_data = &jpg_sts;
		cmd_info[0].recieve_num    = 1;
		
		ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (ret < 0) {
			CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
			return -EFAULT;
		}

		CAMCMP_LOG_DBG("jpg_sts [%d] cap_cnt[%d] \n",jpg_sts, cap_cnt);
		if ( jpg_sts == 0x00000000 ) {
			CAMCMP_LOG_DBG("image start \n");
			break;
		} else if ( jpg_sts == 0x00000002 || jpg_sts == 0x00000003 ) {
			CAMCMP_LOG_DBG("retry \n");
			continue;
		} else {
			CAMCMP_LOG_ERR("jpeg sts err \n");
			return -EFAULT;
		}
	}
	if ( cap_cnt == jpg_retry+1 )	{
		CAMCMP_LOG_DBG("jpeg retry over image start \n");
	}
	


	CAMCMP_LOG_DBG("succsess\n");
	return ret;
}











static int ius006f_set_mode(int mode, int res, int set_camera_mode)





{
	int rc = 0;		

	CAMCMP_LOG_DBG("start here !!!\n");

	switch (mode) {

	case SENSOR_PREVIEW_MODE:
	case SENSOR_MOVIE_MODE:
		CAMCMP_LOG_DBG("SENSOR_MODE mode = %d\n", mode);



		rc = ius006f_video_config(mode, res, set_camera_mode);





		break;



	case SENSOR_RAW_SNAPSHOT_MODE:
		CAMCMP_LOG_DBG("SENSOR_RAW_SNAPSHOT_MODE\n");
		rc = ius006f_raw_snapshot_config(res);
		break;



	case SENSOR_SNAPSHOT_MODE:
		rc = ius006f_snapshot_config(res);
		break;


	default:
		CAMCMP_LOG_ERR("param error. default\n");
		rc = -EINVAL;
		break;
	}

	return rc;
}





























static int ius006f_set_af_mode_off(struct af_mode_cfg *af_mode_chg) 
{
	int rc = 0;  
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type mf_pos = {0, NULL};
	camcmp_blank_info_type af_mode = {0, NULL}; 

	
	
	
	af_mode.blank_id = CAMCMP_BID_MODE_MF;
	cmd_info[0].cmd_id = CAMCMP_CID_AF_MODE;
	cmd_info[0].p_blank_info = &af_mode;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(af_mode);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}
	

	
	rc = ius006f_change_mode(SENSOR_HALF_MODE);
	if (rc < 0) {
		return rc;
	}

	
	switch (af_mode_chg->af_mode) 
	{
	case CAMERA_AF_MODE_NORMAL:     
		mf_pos.blank_id = CAMCMP_BID_MF_1M;
		break;
	case CAMERA_AF_MODE_MACRO:      
		mf_pos.blank_id = CAMCMP_BID_MF_MACRO;
		break;
	case CAMERA_AF_MODE_INFINITY:   
		mf_pos.blank_id = CAMCMP_BID_MF_INF;
		break;
	default:
		mf_pos.blank_id = CAMCMP_BID_MF_INF;
		break;
	}

	
	cmd_info[0].cmd_id = CAMCMP_CID_MF_START;
	cmd_info[0].p_blank_info = &mf_pos;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(mf_pos);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	return rc;
}





















static int ius006f_set_af_mode_on(struct msm_sync *sync) 
{
    int rc = 0;  

	
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type af_mode = {0, NULL};

	
	
	af_mode.blank_id = CAMCMP_BID_MODE_SAF;
	cmd_info[0].cmd_id = CAMCMP_CID_AF_MODE;
	cmd_info[0].p_blank_info = &af_mode;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(af_mode);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}
	

    rc = ius006f_af_start(sync); 
    
    return rc;
}
























static int ius006f_set_af_mode(struct msm_sync *sync, struct af_mode_cfg *af_mode_chg)  
{
	int rc = 0; 


    
	if (ius006f_ctrl->sensormode == SENSOR_HALF_MODE)
	{
		
		rc = ius006f_set_default_focus();
		
		if (rc < 0) {
			CAMCMP_LOG_ERR("ius006f_set_default_focus failed. rc = %d\n", rc);
			return -EFAULT;
		}
		
	}
	else
	{
		
	}


	
	if ((af_mode_chg->af_ends) == SENSOR_OFF) {	 
		rc = ius006f_set_af_mode_off(af_mode_chg);  
	}
	else if ((af_mode_chg->af_ends) == SENSOR_ON) {	 
		rc = ius006f_set_af_mode_on(sync);  
	}
	else {						
		rc = -EINVAL;
	}
	return rc;
}








static int ius006f_get_otp(struct get_otp_cfg *get_otp)   
{
	int  rc  = 0;		
	int8_t   idx = 0; 
	int8_t   i   = 0;
	uint32_t read_otp_data = 0;
	uint32_t read_mask = 0x1;  
	uint32_t get_otp_data = 0;

	
	if(get_otp->rom_area_1 > OTP1){

		get_otp->result = IUS006F_DIAG_PARAM_ERR;

		CAMCMP_LOG_ERR("error root %d\n", __LINE__);
		return -EINVAL;
	}
	if(get_otp->rom_area_2 > OTP_H){

		get_otp->result = IUS006F_DIAG_PARAM_ERR;

		CAMCMP_LOG_ERR("error root %d\n", __LINE__);
		return -EINVAL;
	}
	if(get_otp->start_bit > (IUS006F_OTP_BIT_MAX - 1)){

		get_otp->result = IUS006F_DIAG_PARAM_ERR;

		CAMCMP_LOG_ERR("error root %d\n", __LINE__);
		return -EINVAL;
	}
	if(get_otp->end_bit > IUS006F_OTP_BIT_MAX || 
	   get_otp->end_bit < (IUS006F_OTP_BIT_MIN + 1)){

		get_otp->result = IUS006F_DIAG_PARAM_ERR;

		CAMCMP_LOG_ERR("error root %d\n", __LINE__);
		return -EINVAL;
	}

	idx = (get_otp->rom_area_1 * 3) + get_otp->rom_area_2;
	read_otp_data = ius006f_ctrl->otp_rom_data[idx];

	
	for(i = 0; i <= IUS006F_OTP_BIT_MAX; i++){
		if(i >= get_otp->start_bit && i <= get_otp->end_bit){
			get_otp_data |= read_otp_data & read_mask;
		}
		read_mask = read_mask << 1;
	}

	
	get_otp_data = get_otp_data >> get_otp->start_bit;

	
	get_otp->data_0 = (get_otp_data & 0xff000000) >> 24;
	get_otp->data_1 = (get_otp_data & 0x00ff0000) >> 16;
	get_otp->data_2 = (get_otp_data & 0x0000ff00) >> 8;
	get_otp->data_3 = (get_otp_data & 0x000000ff);

	return rc;
}







static int ius006f_sensor_pat_chg(struct sensor_pat_chg *pat_chg)  
{
	int      rc            = 0;    
	int32_t  i             = 0;
	int32_t  j             = 0;
	uint8_t  port_high_chk = 0x00; 
	uint8_t  port_low_chk  = 0x00; 
	uint8_t  port_chk      = 0x00; 
	uint8_t  mask          = 0x01;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};

	CAMCMP_LOG_DBG("start\n");

	
	cmd_info[0].cmd_id = CAMCMP_CID_PTNCHK_ON;
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}

	
	for(i = 0; i < IUS006F_SENSOR_PAT_CHG_COUNT; i++){
		msleep(IUS006F_SENSOR_PAT_CHG_SLEEP);

		
		for(j = IUS006F_GPIO_4, mask = 0x01; j <= IUS006F_GPIO_11; j++, mask = mask << 1){
			if(gpio_get_value(j)){
				port_high_chk |= mask;
			}
			else{
				port_low_chk |= mask;
			}
		}

		port_chk = (port_high_chk & port_low_chk);

		
		if(port_chk == 0xff){
			break;
		}
	}

	
	if(port_chk != 0xff){
		for(i = 0, mask = 0x01; i < IUS006F_GPIO_CNT; i++, mask = mask << 1){
			if((port_chk & mask) == 0){
				pat_chg->port_no[pat_chg->err_num] = i+IUS006F_GPIO_4;
				pat_chg->err_num++;
			}
		}
	}

	
	cmd_info[0].cmd_id = CAMCMP_CID_PTNCHK_OFF;
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		return -EFAULT;
	}

	CAMCMP_LOG_DBG("end\n");

	return rc;
}




static int ius006f_get_af_pos(struct get_af_pos_cfg *af_pos)
{
	int rc = 0;
	uint32_t af_evaluate = 0;
	uint32_t af_result = 0;        
	uint32_t af_lens_pos = 0;      
	uint32_t af_adjust_step = 0;   
	
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};

	
	
	cmd_info[0].cmd_id = CAMCMP_CID_GET_EVALUATE;
	cmd_info[0].p_recieve_data = &af_evaluate;
	cmd_info[0].recieve_num = 1;

	
	cmd_info[1].cmd_id = CAMCMP_CID_GET_AF_RESULT;
	cmd_info[1].p_recieve_data = &af_result;
	cmd_info[1].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	CAMCMP_LOG_DBG("af_evaluate=%x, \n", af_evaluate);
	CAMCMP_LOG_DBG("af_result=%x, \n", af_result);

	
	af_pos->af_evaluate_0 = (af_evaluate & 0xff000000) >> 24;
	af_pos->af_evaluate_1 = (af_evaluate & 0x00ff0000) >> 16;
	af_pos->af_evaluate_2 = (af_evaluate & 0x0000ff00) >> 8;
	af_pos->af_evaluate_3 = (af_evaluate & 0x000000ff);

	
	if (af_result == AF_RESULT_OK) {
		af_pos->af_result = AF_SUCCESS;     
	} else {
		af_pos->af_result = AF_FAILED;      
	}
	

    
	
	cmd_info[0].cmd_id = CAMCMP_CID_GET_LENSPOS;
	cmd_info[0].p_recieve_data = &af_lens_pos;
	cmd_info[0].recieve_num = 1; 
    
	cmd_info[1].cmd_id = CAMCMP_CID_GET_AF_STEP;
	cmd_info[1].p_recieve_data = &af_adjust_step;
	cmd_info[1].recieve_num = 1; 

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	CAMCMP_LOG_DBG("af_lens_pos=%x, \n", af_lens_pos);
	CAMCMP_LOG_DBG("af_adjust_step=%x, \n", af_adjust_step);

	
	af_pos->af_lens_pos_0 = (af_lens_pos & 0x0000ff00) >> 8;  
	af_pos->af_lens_pos_1 = (af_lens_pos & 0x000000ff);       
	af_pos->af_adjust_step_0 = (af_adjust_step & 0x0000ff00) >> 8;  
	af_pos->af_adjust_step_1 = (af_adjust_step & 0x000000ff);       

	return rc;
}


static int ius006f_get_moni_gain(struct get_monigain_cfg *moni_gain)
{
	int rc = 0;
	uint32_t shut_speed0 = 0;    
	uint32_t shut_speed1 = 0;    
	uint32_t aescl = 0 ;         
	uint32_t agc_scl = 0 ;       
	camcmp_cmd_info_type cmd_info1[] = {{0, NULL, 0, NULL, 0}};
	camcmp_cmd_info_type cmd_info2[] = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};

	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_H;
	cmd_info1[0].p_recieve_data = &shut_speed0;
	cmd_info1[0].recieve_num = 1; 

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	
	moni_gain->shutter_speed_0 = (shut_speed0 & 0x0000ff00) >> 8;
	moni_gain->shutter_speed_1 = (shut_speed0 & 0x000000ff);
	CAMCMP_LOG_DBG("shut_speed0=%x\n", shut_speed0);

	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_L;
	cmd_info1[0].p_recieve_data = &shut_speed1;
	cmd_info1[0].recieve_num = 1; 

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	
	moni_gain->shutter_speed_2 = (shut_speed1 & 0x0000ff00) >> 8;
	moni_gain->shutter_speed_3 = (shut_speed1 & 0x000000ff);
	CAMCMP_LOG_DBG("shut_speed1=%x \n", shut_speed1);


    
	cmd_info2[0].cmd_id = CAMCMP_CID_GET_AGC_SCL;
	cmd_info2[0].p_recieve_data = &agc_scl;
	cmd_info2[0].recieve_num = 1; 

    
	cmd_info2[1].cmd_id = CAMCMP_CID_GET_AESCL;
	cmd_info2[1].p_recieve_data = &aescl;
	cmd_info2[1].recieve_num = 1; 

	rc = camcmp_isp_trans(cmd_info2, CAMCMP_SIZE_CMD(cmd_info2));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}

	
	moni_gain->AGC_gain_0 = (agc_scl & 0x0000ff00) >> 8;
	moni_gain->AGC_gain_1 = (agc_scl & 0x000000ff);

	moni_gain->aescl_0 = (aescl & 0x0000ff00) >> 8;
	moni_gain->aescl_1 = (aescl & 0x000000ff);

	CAMCMP_LOG_DBG("AGC_gain_0=%x \n", agc_scl);
	CAMCMP_LOG_DBG("aescl=%x \n", aescl);

	return rc;

}


static int ius006f_get_reg_ver(struct get_reg_ver_cfg *get_reg_ver)     
{
	int			rc = 0;       
	uint8_t		sd_type=0;    
	uint16_t	reg_ver=0;    

	
	camcmp_makecmd_get_version(&reg_ver, &sd_type);

	
	get_reg_ver->reg_ver_0 = (reg_ver&0xFF00)>>8;
	get_reg_ver->reg_ver_1 = reg_ver&0xFF;
	get_reg_ver->sd_type = sd_type;
	return rc;
}




















static int ius006f_set_manual_step(struct set_manual_step_cfg *set_manual_step)
{
	int      rc = 0;
	uint32_t af_evaluate = 0;
	int32_t  manual_step_val=0;
	int32_t  af_lens_pos = 0;
	int32_t  serch_area_max=0;
	int32_t  serch_area_min=0;
	
	camcmp_cmd_info_type cmd_info1[] = {{0, NULL, 0, NULL, 0}};
	camcmp_cmd_info_type cmd_info2[] = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type mf_pos = {0, NULL};
	camcmp_blank_info_type af_mode = {0, NULL};

	
	
	cmd_info2[0].cmd_id = CAMCMP_CID_GET_AREA_LOW_TYPE1;
	cmd_info2[0].p_recieve_data = &serch_area_min;
	cmd_info2[0].recieve_num = 1;
	
	cmd_info2[1].cmd_id = CAMCMP_CID_GET_AREA_HIGH_TYPE1;
	cmd_info2[1].p_recieve_data = &serch_area_max;
	cmd_info2[1].recieve_num = 1;
	
	rc = camcmp_isp_trans(cmd_info2, CAMCMP_SIZE_CMD(cmd_info2));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}

	
	
	cmd_info2[0].cmd_id = CAMCMP_CID_GET_MANUAL_STEP;
	cmd_info2[0].p_recieve_data = &manual_step_val;
	cmd_info2[0].recieve_num = 1;
	
	cmd_info2[1].cmd_id = CAMCMP_CID_GET_LENSPOS;
	cmd_info2[1].p_recieve_data = &af_lens_pos;
	cmd_info2[1].recieve_num = 1;
	
	rc = camcmp_isp_trans(cmd_info2, CAMCMP_SIZE_CMD(cmd_info2));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EINVAL;
	}

	
	if(set_manual_step->direct){		
		af_lens_pos -= (set_manual_step->step*manual_step_val);
	}
	else{                               
		af_lens_pos += (set_manual_step->step*manual_step_val);
	}
	
	
	if ((af_lens_pos<serch_area_min)||
	    (af_lens_pos>serch_area_max)){
		
		set_manual_step->step_check = 0;
		CAMCMP_LOG_ERR("af_lens_pos invalid. af_lens_pos=%d.\n", af_lens_pos);
		return rc;
	}
	
	
	rc = ius006f_change_mode(SENSOR_PREVIEW_MODE);
	if (rc < 0) {
		CAMCMP_LOG_ERR("ius006f_change_mode failed. rc = %d\n", rc);
		return -EFAULT;
	}

	
	
	af_mode.blank_id = CAMCMP_BID_MODE_MF;
	cmd_info1[0].cmd_id = CAMCMP_CID_AF_MODE;
	cmd_info1[0].p_blank_info = &af_mode;
	cmd_info1[0].blank_num = CAMCMP_SIZE_BLKINF(af_mode);

	
	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	
	rc = ius006f_change_mode(SENSOR_HALF_MODE);
	if (rc < 0) {
		return rc;
	}

	
	
	mf_pos.blank_id = CAMCMP_BID_MF_CUSTOM;
	mf_pos.p_blank_data = &af_lens_pos;
	cmd_info1[0].cmd_id = CAMCMP_CID_MF_START;
	cmd_info1[0].p_blank_info = &mf_pos;
	cmd_info1[0].blank_num = CAMCMP_SIZE_BLKINF(mf_pos);

	
	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	
	
	cmd_info2[0].cmd_id = CAMCMP_CID_GET_EVALUATE;
	cmd_info2[0].p_recieve_data = &af_evaluate;
	cmd_info2[0].recieve_num = 1;
    
	cmd_info2[1].cmd_id = CAMCMP_CID_GET_LENSPOS;
	cmd_info2[1].p_recieve_data = &af_lens_pos;
	cmd_info2[1].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info2, CAMCMP_SIZE_CMD(cmd_info2));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}

	
	set_manual_step->step_check = 1;
	set_manual_step->af_evaluate_0 = (af_evaluate & 0xff000000) >> 24;   
	set_manual_step->af_evaluate_1 = (af_evaluate & 0x00ff0000) >> 16;   
	set_manual_step->af_evaluate_2 = (af_evaluate & 0x0000ff00) >> 8;    
	set_manual_step->af_evaluate_3 = (af_evaluate & 0x000000ff);         

	
	set_manual_step->af_lens_pos_0 = (af_lens_pos & 0x0000ff00) >> 8;    
	set_manual_step->af_lens_pos_1 = (af_lens_pos & 0x000000ff);         

	return rc;
}





























static int ius006f_set_default_focus(void) 
{
	
	int rc = 0;
	uint32_t af_lens_pos = 0;    
	

	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type mf_pos = {0, NULL};





	CAMCMP_LOG_DBG("start\n"); 

	
	if ( (ius006f_ctrl->sensormode != SENSOR_PREVIEW_MODE) && 
	     (ius006f_ctrl->sensormode != SENSOR_MOVIE_MODE) ) {
		
		rc = ius006f_change_mode(SENSOR_PREVIEW_MODE);
		if (rc < 0) {
			CAMCMP_LOG_ERR("ius006f_change_mode failed. rc = %d\n", rc);
			return rc;
		}
	}
	

	
	
	cmd_info[0].cmd_id = CAMCMP_CID_GET_LENSPOS;
	cmd_info[0].p_recieve_data = &af_lens_pos;
	cmd_info[0].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	if ((af_lens_pos == 0) ||
	    (ius006f_ctrl->init_curr_lens_pos != af_lens_pos)){
		
		mf_pos.blank_id = CAMCMP_BID_MF_INF; 
		cmd_info[0].cmd_id = CAMCMP_CID_MF_START;
		cmd_info[0].p_blank_info = &mf_pos;
		cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(mf_pos);
		cmd_info[0].p_recieve_data = NULL;
		cmd_info[0].recieve_num = 0;

		
		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (rc < 0) {
			CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
			return -EFAULT;
		}

		
		if(ius006f_ctrl->init_curr_lens_pos == 0){
			
			cmd_info[0].cmd_id = CAMCMP_CID_GET_LENSPOS;
			cmd_info[0].p_recieve_data = &af_lens_pos;
			cmd_info[0].recieve_num = 1;
			cmd_info[0].p_blank_info = NULL;
			cmd_info[0].blank_num = 0;

			rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
			if (rc < 0) {
				CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
				return -EFAULT;
			}
			
			ius006f_ctrl->init_curr_lens_pos = (uint16_t)af_lens_pos;    
		}
		
	}

	CAMCMP_LOG_DBG("end\n");
	





	return rc;
}




















static int ius006f_af_start(struct msm_sync *sync) 
{

	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}}; 

	CAMCMP_LOG_DBG("start\n");

	
	ius006f_ctrl->af_cancel_onoff = SENSOR_OFF;

	
	if(ius006f_ctrl->sensormode == SENSOR_HALF_MODE){
		
		cmd_info[0].cmd_id = CAMCMP_CID_AF_RESTART_F;

		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (rc < 0) {
			CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
			return rc;
		}
	} else {
		
		rc = ius006f_change_mode_af(SENSOR_HALF_MODE, SENSOR_ON);
		if (rc < 0) {
			CAMCMP_LOG_ERR("ius006f_change_mode_af failed. rc = %d\n", rc);
			return rc;
		}
	}
	

	
	init_timer(&timer);
	timer.expires = jiffies + IUS006F_CHECK_STATE_WAIT;
	timer.data=(unsigned long)sync;
	timer.function = msm_af_start_poll;
	add_timer(&timer);

	CAMCMP_LOG_DBG("end rc = %d\n",rc);


	return rc;
}



























static int ius006f_af_start_after(struct msm_sync *sync)
{

	int rc = 0;
	uint32_t af_result = 0;				 
	uint32_t af_state  = 0;				 
	uint32_t af_lock   = 0;				 
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0},{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type intclr   = {0, NULL};

	CAMCMP_LOG_DBG("start\n");

	
	if ((ius006f_ctrl->af_cancel_onoff) == SENSOR_ON) {
		CAMCMP_LOG_ERR("cancel. cancel = %d\n", ius006f_ctrl->af_cancel_onoff);
		af_start_after_cnt = 0;
		return AF_RESULT_NG;
	}

	
	af_start_after_cnt++;
	if (af_start_after_cnt > IUS006F_CHECK_STATE_WAITMAX){
		CAMCMP_LOG_ERR("cut over. cnt = %d\n", af_start_after_cnt);
		af_start_after_cnt = 0;
		return -EFAULT;
	}

	
	cmd_info[0].cmd_id = CAMCMP_CID_GET_AF_STATE;
	cmd_info[0].p_recieve_data = &af_state;
	cmd_info[0].recieve_num = 1;

	
	
	cmd_info[1].cmd_id = CAMCMP_CID_GET_INTSTS;
	cmd_info[1].p_recieve_data = &af_lock;
	cmd_info[1].recieve_num = 1;
	

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		af_start_after_cnt = 0;
		return -EFAULT;
	}

	if(af_state == IUS006F_AF_STATE_ERR){
		
		CAMCMP_LOG_ERR("AF_STATE_ERR\n");
		af_start_after_cnt = 0;
		return -EFAULT; 
	}

	if((af_lock & IUS006F_AF_LOCK_DONE ) > 0){ 
		
		CAMCMP_LOG_DBG("AF_LOCK_DONE\n");

		
		af_start_after_cnt = 0;

		
		intclr.blank_id = CAMCMP_BID_CLR_AF_LOCK;
		cmd_info[0].cmd_id = CAMCMP_CID_INT_CLR;
		cmd_info[0].p_blank_info = &intclr;
		cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(intclr);
		cmd_info[0].p_recieve_data = NULL;
		cmd_info[0].recieve_num = 0;

	    
		cmd_info[1].cmd_id = CAMCMP_CID_GET_AF_RESULT;
		cmd_info[1].p_recieve_data = &af_result;
		cmd_info[1].recieve_num = 1;

		
		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (rc < 0) {
			CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
			return -EFAULT;
		}

		CAMCMP_LOG_DBG("af_result = %d\n", af_result);

		if (af_result == AF_RESULT_OK) {
			
			rc = AF_RESULT_OK;
		} else if (af_result == AF_RESULT_NG) {
			
			
			rc = ius006f_change_mode(SENSOR_PREVIEW_MODE);
			if (rc < 0) {
				CAMCMP_LOG_ERR("AF_RESULT_NG Change mode failed. rc = %d\n", rc);
				return -EFAULT;
			}
			
			
			rc = AF_RESULT_NG;
		} else {
			
			rc = -EFAULT;
			CAMCMP_LOG_ERR("af_result failed. rc = %d\n", rc);
		}
	}else{
		
		CAMCMP_LOG_DBG("AF_CHK_POOLING\n");

		
		timer.expires = jiffies + IUS006F_CHECK_STATE_WAIT;
		timer.data=(unsigned long)sync;
		timer.function = msm_af_start_poll;
		add_timer(&timer);
		rc = AF_RESULT_DURING;
	}

	CAMCMP_LOG_DBG("end rc = %d\n",rc);
	return rc;
}




















static int ius006f_af_cancel(void)
{
	int rc = 0;

	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};

	CAMCMP_LOG_DBG("start\n");

	
	ius006f_ctrl->af_cancel_onoff = SENSOR_ON; 

	
	cmd_info[0].cmd_id = CAMCMP_CID_AF_CANCEL;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return rc;
	}

	
	rc = ius006f_set_default_focus();

	CAMCMP_LOG_DBG("end rc = %d\n",rc);

	return rc;
}























static int ius006f_afc_stop(void)
{
	int rc = 0;

	camcmp_cmd_info_type cmd_info[]  = 
	{
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0}
	};
	camcmp_blank_info_type af_mode_moni = {0, NULL};
	camcmp_blank_info_type clr_mode     = {0, NULL};

	CAMCMP_LOG_DBG("start here !!!\n");
	
	
	if(ius006f_ctrl->afc_mode == SENSOR_AF_STATUS_MOVE)
	{
		
		
		cmd_info[0].cmd_id       = CAMCMP_CID_AF_MODE_MONI;
		af_mode_moni.blank_id    = CAMCMP_BID_MODE_MONI_AF_OFF;
		cmd_info[0].p_blank_info = &af_mode_moni;
		cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(af_mode_moni);

		
		cmd_info[1].cmd_id       = CAMCMP_CID_INT_CLR;
		clr_mode.blank_id        = CAMCMP_BID_CLR_MODE;
		cmd_info[1].p_blank_info = &clr_mode;
		cmd_info[1].blank_num    = CAMCMP_SIZE_BLKINF(clr_mode);

		
		cmd_info[2].cmd_id       = CAMCMP_CID_MONI_REFLESH;

		
		cmd_info[3].cmd_id       = CAMCMP_CID_CHK_MODE_STS;
		
		
		cmd_info[4].cmd_id       = CAMCMP_CID_INT_CLR;
		clr_mode.blank_id        = CAMCMP_BID_CLR_MODE;
		cmd_info[4].p_blank_info = &clr_mode;
		cmd_info[4].blank_num    = CAMCMP_SIZE_BLKINF(clr_mode);

		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (rc < 0)
		{
			CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
			return -EFAULT;
		}
		
		ius006f_af_status_change(SENSOR_AF_STATUS_IDLE);
	}
	
	else
	{
		
	}

	return rc;
}
















static int ius006f_afc_lock_start(struct msm_sync *sync, struct af_lock_req_t *p_set_af_lock)
{
    int      rc              = 0;
	uint8_t  afc_status      = 0;
	uint8_t  peak_detection  = 0;

	CAMCMP_LOG_DBG("start here !!!\n");
	
	
	if(ius006f_ctrl->afc_mode == SENSOR_AF_STATUS_MOVE)
	{
    	
    	ius006f_ctrl->af_cancel_onoff = SENSOR_OFF;
		
		ius006f_get_afc_status(&afc_status);
		
		
		if(p_set_af_lock->af_c_mode == SENSER_AFC_CHANGEABILITY)
		{
			
			if(ius006f_get_af_state(&peak_detection) != 0)
			{
                
                peak_detection = 0;
			}
			
			
			if(peak_detection == 0x0F)
			{
				
				ius006f_afc_single(p_set_af_lock->lens_position, (uint8_t)SENSOR_AFS_FINE);
			}
			
			else
			{
				
				if(p_set_af_lock->af_s_mode == SENSOR_AFS_SINGLE)
				{
					
					ius006f_afc_single(p_set_af_lock->lens_position, (uint8_t)SENSOR_AFS_SINGLE);
				}
				else
				{
				
					
					ius006f_afc_single(p_set_af_lock->lens_position, (uint8_t)SENSOR_AFS_DOUBLE);
				}
			}
			
			rc = AF_RESULT_DURING;
			
			
			ius006f_af_status_change(SENSOR_AF_STATUS_LOCK_MOVE);
			
            
			afc_lock_wait_cnt = 0;

			CAMCMP_LOG_DBG("start kernel timer\n");
			
			init_timer(&timer);
			timer.expires  = jiffies + IUS006F_FRAME_RATE_WAIT;
			timer.data     = (unsigned long)sync;
			timer.function = msm_af_start_poll;
			add_timer(&timer);			
		}
		
		else
		{
			rc = AF_RESULT_NG;
			
			if(ius006f_get_af_state(&peak_detection) == 0)
			{
                
    			if(peak_detection == 0x0F)
    			{
    				rc = AF_RESULT_OK;
                }
			}
            
            ius006f_afc_stop();
			
			ius006f_af_status_change(SENSOR_AF_STATUS_LOCK);
		}
	}
	else
	{
		CAMCMP_LOG_ERR("%s Invalit State : %d\n", __func__, __LINE__);
	}
	
	CAMCMP_LOG_DBG("focus status = %d\n", rc);

	return rc;
}















static int ius006f_afc_get_result(struct msm_sync *sync, struct af_move_req_t *p_set_af_move)
{
	int rc = 0;
	uint8_t af_result = 0;
	uint8_t saf_mode  = 0;

	
	if(ius006f_ctrl->afc_mode == SENSOR_AF_STATUS_LOCK_MOVE)
	{
		
		if(ius006f_get_afc_result(&af_result) != 0)
		{
			return AF_RESULT_ERR;
		}
    	
    	if ((ius006f_ctrl->af_cancel_onoff) == SENSOR_ON) 
    	{
    		CAMCMP_LOG_ERR("cancel. cancel = %d\n", ius006f_ctrl->af_cancel_onoff);
    		ius006f_ctrl->af_cancel_onoff = SENSOR_OFF;
    		p_set_af_move->focus_status = AF_RESULT_NG;
    		
    		ius006f_af_status_change(SENSOR_AF_STATUS_IDLE);
    	}
        
        else
        {
    		CAMCMP_LOG_DBG("ius006f_afc_get_result result = %d\n", af_result);

    		switch(af_result)
    		{
    			
    			case 0x00:
    				
    				rc = AF_RESULT_NG;
    				
    				if(ius006f_get_saf_mode(&saf_mode) == 0)
    				{
        				
        				if(saf_mode == 0x01)
        				{
        					
        					rc |= E_AF_MOVE_YES;
        				}
    				}
    				break;
    			
    			case 0x01:
    				
    				rc = AF_RESULT_OK;
    				break;
    			
    			case 0x02:
                    
                    if(++afc_lock_wait_cnt <= IUS006F_CHECK_STATE_WAITMAX)
                    {
        				
        				rc = AF_RESULT_DURING;
        				
        				timer.expires  = jiffies + IUS006F_FRAME_RATE_WAIT;
        				timer.data     =(unsigned long)sync;
        				timer.function = msm_af_start_poll;
        				add_timer(&timer);
        		    }
        		    
        		    else
        		    {
                        
                        afc_lock_wait_cnt = 0;
                        
        				rc = AF_RESULT_ERR;
                    }
    				break;
    			default:
    				CAMCMP_LOG_ERR("%s failed : %d \n", __func__, __LINE__);
    				break;
    		}
        }
	}
	else
	{
		
	}

	return rc;
}















static int ius006f_afc_hold_request(int8_t set_af_hold_status)
{
	int rc = 0;
	
	
	if(set_af_hold_status == E_QUALITY_STATUS_SETTING)
	{
		
		if(ius006f_set_awb_hold(CAMCMP_BID_AWB_ON) != 0)
		{
			return -EFAULT;
		}
		
		if(ius006f_set_ae_hold(CAMCMP_BID_AE_ON) != 0)
		{
			return -EFAULT;
		}
		
		
		ius006f_af_status_change(SENSOR_AF_STATUS_LOCK);
	}
	
	else
	{
		
		if(ius006f_set_ae_hold(CAMCMP_BID_AE_OFF) != 0)
		{
			return -EFAULT;
		}
		
		ius006f_af_status_change(SENSOR_AF_STATUS_IDLE);
	}
	
	return rc;
}

















static int ius006f_afc_start(int lens_position)
{
    int rc = 0;
    int ret = 0;
    uint32_t low = 0;
    uint32_t higt = 0;
    camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};
    camcmp_blank_info_type af_mode = {0, NULL};
    camcmp_blank_info_type intclr = {0, NULL};
    camcmp_blank_info_type search_area[] = {{0, NULL}, {0, NULL}};

    if(ius006f_ctrl->afc_mode == SENSOR_AF_STATUS_IDLE)
    {
        
        ius006f_set_af_search_area(lens_position, &low, &higt);
        
        af_mode.blank_id = CAMCMP_BID_MODE_MONI_AFC;
        cmd_info[0].cmd_id = CAMCMP_CID_AF_MODE_MONI;
        cmd_info[0].p_blank_info = &af_mode;
        cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(af_mode);
        
        search_area[0].blank_id     = CAMCMP_BID_AF_AREA_LOW_TYPE1;
        search_area[0].p_blank_data = &low;
        search_area[1].blank_id     = CAMCMP_BID_AF_AREA_HIGH_TYPE1;
        search_area[1].p_blank_data = &higt;
        cmd_info[1].cmd_id = CAMCMP_CID_SEARCH_AREA;
        cmd_info[1].p_blank_info = search_area;
        cmd_info[1].blank_num = CAMCMP_SIZE_BLKINF(search_area);
        
        intclr.blank_id = CAMCMP_BID_CLR_MODE;
        cmd_info[2].cmd_id = CAMCMP_CID_INT_CLR;
        cmd_info[2].p_blank_info = &intclr;
        cmd_info[2].blank_num = CAMCMP_SIZE_BLKINF(intclr);
        
        cmd_info[3].cmd_id = CAMCMP_CID_MONI_REFLESH;
        
        cmd_info[4].cmd_id = CAMCMP_CID_CHK_MODE_STS;
        
        intclr.blank_id = CAMCMP_BID_CLR_MODE;
        cmd_info[5].cmd_id = CAMCMP_CID_INT_CLR;
        cmd_info[5].p_blank_info = &intclr;
        cmd_info[5].blank_num = CAMCMP_SIZE_BLKINF(intclr);
        
        ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
        if (ret < 0) {
            CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
            return -EFAULT;
        }
        
        ius006f_af_status_change(SENSOR_AF_STATUS_MOVE);
    }

    return rc;
}

















static int ius006f_set_frame_pos(struct t_FramePosition_DRV frame_position)
{
    int rc = 0;
    int ret = 0;
    camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};
    camcmp_blank_info_type set_frame_pos[] = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}};

    
    ius006f_frame_pos_constraint(&frame_position);

    
    set_frame_pos[0].blank_id     = CAMCMP_BID_AF_OPD4_HDELAY;
    set_frame_pos[0].p_blank_data = &frame_position.StartPos_X;
    set_frame_pos[1].blank_id     = CAMCMP_BID_AF_OPD4_VDELAY;
    set_frame_pos[1].p_blank_data = &frame_position.StartPos_Y;
    set_frame_pos[2].blank_id     = CAMCMP_BID_AF_OPD4_HVALID;
    set_frame_pos[2].p_blank_data = &frame_position.EndPos_X;
    set_frame_pos[3].blank_id     = CAMCMP_BID_AF_OPD4_VVALID;
    set_frame_pos[3].p_blank_data = &frame_position.EndPos_Y;
    cmd_info[0].cmd_id       = CAMCMP_CID_FRAME_POS;
    cmd_info[0].p_blank_info = set_frame_pos;
    cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(set_frame_pos);
    ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    if (ret < 0) {
        CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
        return -EFAULT;
    }

    return rc;
}

















static int ius006f_set_m_focus(int lens_position, uint32_t dac_code)
{
    int rc = 0;
    int ret = 0;
    uint32_t low = 0;
    uint32_t higt = 0;
    camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};
    camcmp_blank_info_type af_mode  = {0, NULL};
    camcmp_blank_info_type intclr   = {0, NULL};
    camcmp_blank_info_type mf_pos   = {0, NULL};
    camcmp_blank_info_type search_area[] = {{0, NULL}, {0, NULL}};

    CAMCMP_LOG_DBG("ius006f_set_m_focus start af status = %d\n", ius006f_ctrl->afc_mode);

    
    if(ius006f_ctrl->afc_mode != SENSOR_AF_STATUS_MOVE)
    {
        
        
        ius006f_set_af_search_area(lens_position, &low, &higt);
        CAMCMP_LOG_DBG("ius006f_set_m_focus start low = %d higt = %d\n", low, higt);
        
        
        af_mode.blank_id = CAMCMP_BID_MODE_MONI_MF;
        cmd_info[0].cmd_id = CAMCMP_CID_AF_MODE_MONI;
        cmd_info[0].p_blank_info = &af_mode;
        cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(af_mode);
        
        search_area[0].blank_id     = CAMCMP_BID_AF_AREA_LOW_TYPE1;
        search_area[0].p_blank_data = &low;
        search_area[1].blank_id     = CAMCMP_BID_AF_AREA_HIGH_TYPE1;
        search_area[1].p_blank_data = &higt;
        cmd_info[1].cmd_id = CAMCMP_CID_SEARCH_AREA;
        cmd_info[1].p_blank_info = search_area;
        cmd_info[1].blank_num = CAMCMP_SIZE_BLKINF(search_area);
        
        intclr.blank_id = CAMCMP_BID_CLR_MODE;
        cmd_info[2].cmd_id = CAMCMP_CID_INT_CLR;
        cmd_info[2].p_blank_info = &intclr;
        cmd_info[2].blank_num = CAMCMP_SIZE_BLKINF(intclr);
        
        cmd_info[3].cmd_id = CAMCMP_CID_MONI_REFLESH;
        
        cmd_info[4].cmd_id = CAMCMP_CID_CHK_MODE_STS;
        
        mf_pos.blank_id = CAMCMP_BID_MF_CUSTOM;
        mf_pos.p_blank_data = &dac_code;
        cmd_info[5].cmd_id = CAMCMP_CID_MF_START;
        cmd_info[5].p_blank_info = &mf_pos;
        cmd_info[5].blank_num = CAMCMP_SIZE_BLKINF(mf_pos);
        ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
        if (ret < 0) {
            CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
            return -EFAULT;
        }
    }

    return rc;
}

















static int ius006f_set_lens_position(int lens_position)
{
    int rc = 0;
    uint32_t dac_code = 0;
    int     VE299;

    CAMCMP_LOG_DBG("ius006f_set_lens_position = %d\n", lens_position);
    
    if(ius006f_ctrl->afc_mode == SENSOR_AF_STATUS_IDLE)
    {
        
        if(lens_position == SENSOR_LENS_STANDARD_POSITION)  VE299 = DAC_CODE_INF;
        else                                                VE299 = DAC_CODE_10CM;
        
        dac_code = ius006f_getDacCode(VE299);

        CAMCMP_LOG_DBG("ius006f_set_lens_position daccode = %d\n", dac_code);
        
        ius006f_set_m_focus(lens_position, dac_code);
    }
    return rc;
}
















static int ius006f_afc_focal_length(int16_t *p_get_lens_pos)
{
    int rc = 0;
	uint8_t  af_state    = 0;
	uint8_t  saf_mode    = 3;
	uint8_t  cam_search  = 0;
	uint16_t VCMslope    = 0;
	uint16_t af_step     = 0;
	uint16_t af_search   = 0;
	
	
	if(ius006f_get_af_state(&af_state) != 0)
	{
		return -EFAULT;
	}
	
	
	switch(af_state)
	{
		
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:
		case 0x09:
			
			if(ius006f_get_saf_mode(&saf_mode) != 0)
			{
				return -EFAULT;
			}
			
			if(saf_mode == 0x00)
			{
				cam_search = SENSOR_AFS_SINGLE;
			}
			
			else if(saf_mode == 0x01)
			{
				cam_search = SENSOR_AFS_FINE;
			}
			
			else
			{
				cam_search = SENSOR_AFS_DOUBLE;
			}
			break;
		
		case 0x0C:
		case 0x0D:
		case 0x0F:
			cam_search = SENSOR_AFC;
			break;
		default:
			break;
	}
	
	
	ius006f_afc_otp_read(CAMCMP_OTP1H, &VCMslope);
	
	
	af_search = ius006f_af_search_step_cal(VCMslope, cam_search);
	
	
	if(ius006f_get_af_wnd3a(&af_step) != 0)
	{
		return -EFAULT;
	}
	
	
	if(af_step != 0xFFFF)
	{
		
		*p_get_lens_pos = af_search * af_step;
	}
	else
	{

		*p_get_lens_pos = 0xFFFF;
	}
	
    return rc;
}
















static int ius006f_set_weightmode(struct T_AfSettingInfo set_af_setting_info)
{
    int rc = 0;
    int ret = 0;
    camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};
    camcmp_blank_info_type set_photometry[] = {{0, NULL}, {0, NULL}, {0, NULL}, {0, NULL}};

    
    if(set_af_setting_info.weightmode == true)
    {
        
        set_photometry[0].blank_id     = CAMCMP_BID_AE_OPD_HDELAY;
        set_photometry[0].p_blank_data = &set_af_setting_info.afposition.StartPos_X;
        set_photometry[1].blank_id     = CAMCMP_BID_AE_OPD_VDELAY;
        set_photometry[1].p_blank_data = &set_af_setting_info.afposition.StartPos_Y;
        set_photometry[2].blank_id     = CAMCMP_BID_AE_OPD_HVALID;
        set_photometry[2].p_blank_data = &set_af_setting_info.afposition.EndPos_X;
        set_photometry[3].blank_id     = CAMCMP_BID_AE_OPD_VVALID;
        set_photometry[3].p_blank_data = &set_af_setting_info.afposition.EndPos_Y;
        cmd_info[0].cmd_id       = CAMCMP_CID_PHOTOMETRY;
        cmd_info[0].p_blank_info = set_photometry;
        cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(set_photometry);
        ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
        if (ret < 0) {
            CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
            return -EFAULT;
        }
    }
    return rc;
}
















static int ius006f_set_free_weight(int8_t free_weight_f)
{
    int rc = 0;
    int ret = 0;
    camcmp_cmd_info_type cmd_info[] = {{0, NULL}};
    camcmp_blank_info_type set_free_weight[] = {{0, NULL}};

    
    set_free_weight[0].blank_id     = CAMCMP_BID_AE_FREE_WEIGHT;
    set_free_weight[0].p_blank_data = &free_weight_f;
    cmd_info[0].cmd_id       = CAMCMP_CID_FREE_WEIGHT;
    cmd_info[0].p_blank_info = set_free_weight;
    cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(set_free_weight);
    ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    if (ret < 0) {
        CAMCMP_LOG_ERR("camcmp_isp_trans failed [RC:%d]\n",ret);
        rc = -EFAULT;
    }
    return rc;

}

















static int ius006f_afs_stop(void)
{
    int rc = 0;
 
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};

	CAMCMP_LOG_DBG("start\n");

	
	ius006f_ctrl->af_cancel_onoff = SENSOR_ON;

	
	cmd_info[0].cmd_id = CAMCMP_CID_AF_CANCEL;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return rc;
	}

	CAMCMP_LOG_DBG("end rc = %d\n",rc);

	return rc;
}


















static void ius006f_af_status_change(sensor_af_status_t next_af_status)
{
  
  if(ius006f_ctrl->afc_mode != next_af_status)
  {
    CAMCMP_LOG_DBG("ius006f_af_status_change %d -> %d\n", ius006f_ctrl->afc_mode, next_af_status);
    ius006f_ctrl->afc_mode = next_af_status;
  }
}














static int ius006f_get_afc_status(uint8_t *p_get_afc_status)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	
	
	cmd_info[0].cmd_id         = CAMCMP_CID_AFC_STATUS;
	cmd_info[0].p_recieve_data = p_get_afc_status;
	cmd_info[0].recieve_num    = 1;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}
	else
	{
		
	}
	
	return rc;
}













static int ius006f_get_af_state(uint8_t *p_af_state)
{
	
	int rc = 0;
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};
	
	
	cmd_info[0].cmd_id         = CAMCMP_CID_GET_AF_STATE;
	cmd_info[0].p_recieve_data = p_af_state;
	cmd_info[0].recieve_num    = 1;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}
	else
	{
		
	}
	
	return rc;
}













static void ius006f_afc_single(int8_t lens_position, uint8_t set_saf_mode)
{
	
	
	if(!ius006f_set_saf_mode(set_saf_mode))
	{
        
	    if(!ius006f_set_afc_lens(lens_position))
	    {
            
	        ius006f_set_afc_single();
	    }
	}
}













static int ius006f_set_saf_mode(uint8_t set_saf_mode)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_saf   = {0, NULL};

	
	
	switch(set_saf_mode)
	{
		
		case SENSOR_AFS_FINE:
			set_saf.blank_id = CAMCMP_BID_SET_SAF_MODE_FINE;
			break;
		
		case SENSOR_AFS_SINGLE:
			set_saf.blank_id = CAMCMP_BID_SET_SAF_MODE_SINGLE;
			break;
		
		case SENSOR_AFS_DOUBLE:
			set_saf.blank_id = CAMCMP_BID_SET_SAF_MODE_DOUBLE;
			break;
		default:
			set_saf.blank_id = CAMCMP_BID_SET_SAF_MODE_DOUBLE;
			CAMCMP_LOG_ERR("%s failed : %d \n", __func__, __LINE__);
			break;
	}

	
	cmd_info[0].cmd_id       = CAMCMP_CID_SET_SAF_MODE;
	cmd_info[0].p_blank_info = &set_saf;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(set_saf);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
	}
	else
	{
		
	}
	return rc;
}













static int ius006f_set_afc_lens(int8_t lens_position)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_dac   = {0, NULL};
	uint32_t dac_code = 0;
	
	
	if(lens_position == SENSOR_LENS_STANDARD_POSITION)
	{
		
		dac_code = ius006f_getDacCode(DAC_CODE_INF);
	}
	
	else
	{
		
		dac_code = ius006f_getDacCode(DAC_CODE_10CM);
	}

	cmd_info[0].cmd_id       = CAMCMP_CID_DAC_CODE;
	set_dac.blank_id         = CAMCMP_BID_DAC_CODE;
	set_dac.p_blank_data     = &dac_code;
	cmd_info[0].p_blank_info = &set_dac;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(set_dac);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
	}
	else
	{
		
	}
	return rc;
}













static void ius006f_afc_otp_read(int8_t otp_num, uint16_t *p_otp_data)
{
	
	
	switch(otp_num)
	{
		
		case CAMCMP_OTP0L:
			*p_otp_data = (uint16_t)(((ius006f_ctrl->otp_rom_data[otp_num] >> 16) & 0x000003FF));
			break;
		
		case CAMCMP_OTP1L:
			*p_otp_data = (uint16_t)(((ius006f_ctrl->otp_rom_data[otp_num] >> 5) & 0x000003FF));
			break;
		
		case CAMCMP_OTP1H:
			*p_otp_data = (uint16_t)(((ius006f_ctrl->otp_rom_data[otp_num] >> 6) & 0x000003FF));
			break;
		default:
			CAMCMP_LOG_ERR("%s failed : %d \n", __func__, __LINE__);
			break;
	}
    CAMCMP_LOG_DBG("ius006f_afc_otp_read OTP DATA = %08x\n", *p_otp_data);
}














static uint32_t ius006f_getDacCode(int aDacType)
{
	uint16_t dac_code = 0;
	uint16_t DAC10cm,DAC1m;

	
	ius006f_afc_otp_read(CAMCMP_OTP0L, &DAC10cm);
	ius006f_afc_otp_read(CAMCMP_OTP1L, &DAC1m);
	CAMCMP_LOG_DBG("DacType = %d DAC10cm = %d DAC1m = %d\n", aDacType, DAC10cm, DAC1m);

	switch(aDacType)
	{
        
    case    DAC_CODE_INF    :
        
		dac_code = ((DAC1m * 100) - ((DAC10cm * 100) - (DAC1m * 100)) * D_CAM_AF_Z1M / 
				   (D_CAM_AF_Z10CM - D_CAM_AF_Z1M) - (D_CAM_AF_POSTURE_OFFSET * 100));
	    dac_code = (dac_code + 50) / 100;
		break;
	
    case    DAC_CODE_15CM   :
        
        dac_code = (((DAC1m * 100) + ((DAC10cm * 100) - (DAC1m * 100)) * (D_CAM_AF_Z15CM - D_CAM_AF_Z1M) / 
                   (D_CAM_AF_Z10CM - D_CAM_AF_Z1M) - (D_CAM_AF_POSTURE_OFFSET * 100))) + 50;
        dac_code = dac_code / 100;
        break;
    
    case    DAC_CODE_10CM   :
        
		dac_code = ((((DAC10cm * 100) - (D_CAM_AF_POSTURE_OFFSET * 100))) + 50) / 100;
		break;
    
	default:
		CAMCMP_LOG_ERR("%s failed : %d \n", __func__, __LINE__);
		break;
	}
	CAMCMP_LOG_DBG("DacCode = %d\n", dac_code);	
	return dac_code;
}














static uint16_t ius006f_af_search_step_cal(uint16_t VCMslope, uint8_t cam_search)
{
	uint16_t af_search = 0;
	
	switch(cam_search)
	{
		
		case SENSOR_AFS_SINGLE:
			af_search = ((D_FSTEP * 100) * (VCMslope * 100)) / (100 * 100);
			break;
		
		
		case SENSOR_AFS_FINE:
			af_search = ((D_SSTEP * 100) * (VCMslope * 100)) / (100 * 100);
			break;

		
		case SENSOR_AFS_DOUBLE:
			af_search = (((D_FSTEP * 100) * (VCMslope * 100)) / (100 * 100)) + 
							(((D_SSTEP * 100) * (VCMslope * 100)) / (100 * 100));
			break;
		
		case SENSOR_AFC:
			af_search = ((D_CSTEP * 100) * (VCMslope * 100)) / (100 * 100);
			break;
		default:
			CAMCMP_LOG_ERR("%s failed : %d \n", __func__, __LINE__);
			break;
	}
	
	return af_search;
}














static void ius006f_set_afc_single(void)
{
	int rc = 0;

	camcmp_cmd_info_type cmd_info[]  = 
	{
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0},
		{0, NULL, 0, NULL, 0}
	};
	camcmp_blank_info_type af_mode_moni = {0, NULL};
	camcmp_blank_info_type clr_mode = {0, NULL};

	CAMCMP_LOG_DBG("start here !!!\n");
	
	
	cmd_info[0].cmd_id       = CAMCMP_CID_AF_MODE_MONI;
	af_mode_moni.blank_id    = CAMCMP_BID_MODE_MONI_AFS;
	cmd_info[0].p_blank_info = &af_mode_moni;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(af_mode_moni);

	
	cmd_info[1].cmd_id       = CAMCMP_CID_INT_CLR;
	clr_mode.blank_id        = CAMCMP_BID_CLR_MODE;
	cmd_info[1].p_blank_info = &clr_mode;
	cmd_info[1].blank_num    = CAMCMP_SIZE_BLKINF(clr_mode);

	
	cmd_info[2].cmd_id       = CAMCMP_CID_MONI_REFLESH;

	
	cmd_info[3].cmd_id       = CAMCMP_CID_CHK_MODE_STS;

	
	cmd_info[4].cmd_id       = CAMCMP_CID_INT_CLR;
	clr_mode.blank_id        = CAMCMP_BID_CLR_MODE;
	cmd_info[4].p_blank_info = &clr_mode;
	cmd_info[4].blank_num    = CAMCMP_SIZE_BLKINF(clr_mode);

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
	}
	else
	{
		
	}
	CAMCMP_LOG_DBG("single af end !!!\n");
}













static int ius006f_get_afc_result(uint8_t *p_af_result)
{
	int rc = 0;
	uint32_t               intsts        = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};

    
    *p_af_result = 2;

    
    cmd_info[0].cmd_id       = CAMCMP_CID_GET_INTSTS;
	cmd_info[0].p_recieve_data = &intsts;
	cmd_info[0].recieve_num    = 1;
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    
    if(rc >= 0 && (intsts & 0x10))
    {
    	
    	cmd_info[0].cmd_id         = CAMCMP_CID_AFC_RESULT;
    	cmd_info[0].p_recieve_data = p_af_result;
    	cmd_info[0].recieve_num    = 1;

    	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
    	if (rc < 0)
    	{
    		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
    		return -EFAULT;
    	}
    	else
    	{
    		
    	}
    }
	return rc;
}













static int ius006f_get_saf_mode(uint8_t *p_saf_mode)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	
	
	cmd_info[0].cmd_id         = CAMCMP_CID_GET_SAF_MODE;
	cmd_info[0].p_recieve_data = p_saf_mode;
	cmd_info[0].recieve_num    = 1;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}
	else
	{
		
	}
	
	return rc;
}













static int ius006f_set_awb_hold(uint8_t set_awb_hold)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_awb   = {0, NULL};

	
	cmd_info[0].cmd_id       = CAMCMP_CID_AWB_HOLD;
	set_awb.blank_id         = set_awb_hold;
	cmd_info[0].p_blank_info = &set_awb;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(set_awb);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}
	else
	{
		
	}
	
	return rc;
}













static int ius006f_set_ae_hold(uint8_t set_ae_hold)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_ae    = {0, NULL};

	
	cmd_info[0].cmd_id       = CAMCMP_CID_AE_HOLD;
	set_ae.blank_id          = set_ae_hold;
	cmd_info[0].p_blank_info = &set_ae;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(set_ae);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}
	else
	{
		
	}
	
	return rc;
}













static int ius006f_get_af_wnd3a(uint16_t *p_af_step)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};

    
	cmd_info[0].cmd_id = CAMCMP_CID_GET_AF_STEP;
	cmd_info[0].p_recieve_data = p_af_step;
	cmd_info[0].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	return rc;
}



















static int ius006f_set_af_search_area(int lens_position, uint32_t *low, uint32_t *higt)
{
    int rc = 0;
    camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};

    
    if(ius006f_ctrl->inf_over_search == -1)
    {
        
        cmd_info[0].cmd_id = CAMCMP_CID_GET_MANUAL_STEP;
        cmd_info[0].p_recieve_data = &ius006f_ctrl->inf_over_search;
        cmd_info[0].recieve_num = 1;
        rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
        if (rc < 0)
        {
            CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
            return -EFAULT;
        }
    }
    
    *low = ius006f_getDacCode(DAC_CODE_INF);
    *low -= ius006f_ctrl->inf_over_search;

    switch(lens_position)
    {
        case SENSOR_LENS_STANDARD_POSITION:
            
            *higt = ius006f_getDacCode(DAC_CODE_15CM);
            *higt += D_CAM_AF_MACRO_OVER_SEARCH;
            break;
        case SENSOR_LENS_MACRO_POSITION:
            
            *higt = ius006f_getDacCode(DAC_CODE_10CM);
            *higt += D_CAM_AF_MACRO_OVER_SEARCH;
            break;
        default:
            CAMCMP_LOG_ERR("ius006f_set_af_search_area param error\n");
            return -EINVAL;
    }
    return rc;
}


















static void ius006f_frame_pos_constraint(struct t_FramePosition_DRV *frame_position)
{
    uint16_t over_size = 0; 

    
    if((frame_position->StartPos_X + frame_position->EndPos_X) >
       (SENSOR_VALID_PIXELS_WIDTH - FRAME_POS_H_DEAD_SPACE))
    {
        over_size = ((frame_position->StartPos_X + frame_position->EndPos_X) - (SENSOR_VALID_PIXELS_WIDTH - FRAME_POS_H_DEAD_SPACE));
        if(frame_position->StartPos_X - over_size >= 0)
        {
            frame_position->StartPos_X -= over_size;
        }
        else
        {
            frame_position->EndPos_X -= over_size;
        }
    }
    if((frame_position->StartPos_Y + frame_position->EndPos_Y) >
       (SENSOR_VALID_PIXELS_HEIGHT - FRAME_POS_V_DEAD_SPACE))
    {
        over_size = ((frame_position->StartPos_Y + frame_position->EndPos_Y) - (SENSOR_VALID_PIXELS_HEIGHT - FRAME_POS_V_DEAD_SPACE));
        if(frame_position->StartPos_Y - over_size >= 0)
        {
            frame_position->StartPos_Y -= over_size;
        }
        else
        {
            frame_position->EndPos_Y -= over_size;
        }
    }
    
    frame_position->StartPos_X += FRAME_POS_H_OFFSET;
    

    CAMCMP_LOG_DBG("frame_position->StartPos_X   = %d\n", frame_position->StartPos_X);
    CAMCMP_LOG_DBG("frame_position->StartPos_Y   = %d\n", frame_position->StartPos_Y);
    CAMCMP_LOG_DBG("frame_position->EndPos_X     = %d\n", frame_position->EndPos_X);
    CAMCMP_LOG_DBG("frame_position->EndPos_Y     = %d\n", frame_position->EndPos_Y);

}































static int ius006f_set_brightness(int8_t brightness)
{
    int rc = 0;
    camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
    camcmp_blank_info_type set_brightness = {0, NULL};

	
	if ((brightness < CAMCMP_BID_BRIGHTNESS_0) || (brightness > CAMCMP_BID_BRIGHTNESS_12))
	{
		CAMCMP_LOG_ERR("param error. brightness=%d\n", brightness);
		return -EINVAL;
	}

	
	
	set_brightness.blank_id = (camcmp_blank_contrast_enum)brightness;
	cmd_info[0].cmd_id = CAMCMP_CID_VE023;
	cmd_info[0].p_blank_info = &set_brightness;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(set_brightness);


















	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}

	return rc;
}

















static int ius006f_set_effect(int8_t effect)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_effect = {0, NULL};

	CAMCMP_LOG_DBG("effect=%x \n", effect);

	
	switch (effect)
	{
		case CAMERA_EFFECT_OFF:			
			set_effect.blank_id = CAMCMP_BID_EFFECT_OFF;
			break;
		case CAMERA_EFFECT_MONO:		
			set_effect.blank_id = CAMCMP_BID_EFFECT_MONO;
			break;
		case CAMERA_EFFECT_NEGATIVE:	
			set_effect.blank_id = CAMCMP_BID_EFFECT_NEGA;
			break;
		case CAMERA_EFFECT_SEPIA:		
			set_effect.blank_id = CAMCMP_BID_EFFECT_SEPIA;
			break;
		default:
			CAMCMP_LOG_DBG("param error. default\n");
			return -EINVAL;
	}

	
	
	cmd_info[0].cmd_id = CAMCMP_CID_EFFECT;
	cmd_info[0].p_blank_info = &set_effect;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(set_effect);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}

	return rc;
}























static int32_t ius006f_set_zoom(struct set_zoom_cfg *set_zoom, int size)





{
	int32_t rc = 0;

	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type zoom_blank = {0, NULL};

	CAMCMP_LOG_DBG("start\n");



	CAMCMP_LOG_DBG("zoom = %d, mode = %d, size = %d \n",
						set_zoom->zoom, set_zoom->mode, size);

	if(set_zoom->mode == ZOOM_PICTURE){				
		
		switch (size)
		{
			case SENSOR_CAMERA_5MP_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_5M;
				break;
			case SENSOR_CAMERA_WQHD_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_WQHD;
				break;
			case SENSOR_CAMERA_2MP_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_2M;
				break;
			case SENSOR_CAMERA_1MP_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_1M;
				break;
			case SENSOR_CAMERA_VGA_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_VGA;
				break;
			default:
				CAMCMP_LOG_ERR("size failed.\n");
				return -EINVAL;
		}
	}else{											
		
		switch (size)
		{
			case SENSOR_CAMERA_HD_SIZE:				
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_HD_MV;
				break;
			case SENSOR_CAMERA_VGA_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_VGA_MV;
				break;
			case SENSOR_CAMERA_QVGA_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_QVGA_MV;
				break;
			case SENSOR_CAMERA_QCIF_SIZE:			
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_QCIF_MV;
				break;



			case SENSOR_CAMERA_HD_SIZE_SHAKE:		
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_HD_MV;
				break;
			case SENSOR_CAMERA_VGA_SIZE_SHAKE:		
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_VGA_MV;
				break;
			case SENSOR_CAMERA_QVGA_SIZE_SHAKE:		
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_QVGA_MV;
				break;
			case SENSOR_CAMERA_QCIF_SIZE_SHAKE:		
				cmd_info[0].cmd_id = CAMCMP_CID_ZOOM_QCIF_MV;
				break;


			default:
				CAMCMP_LOG_ERR("size failed.\n");
				return -EINVAL;
		}
	}

	if ((cmd_info[0].cmd_id == CAMCMP_CID_ZOOM_5M) ||
		(cmd_info[0].cmd_id == CAMCMP_CID_ZOOM_WQHD) ||
		(cmd_info[0].cmd_id == CAMCMP_CID_ZOOM_1M) ||
		(cmd_info[0].cmd_id == CAMCMP_CID_ZOOM_HD_MV))
	{
		if (set_zoom->zoom > 0) {
			CAMCMP_LOG_ERR("zoom param err\n");
			return -EINVAL;
		}
	}

	
	zoom_blank.blank_id = (camcmp_blank_zoom_enum)set_zoom->zoom;







































































	cmd_info[0].p_blank_info = &zoom_blank;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(zoom_blank);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	CAMCMP_LOG_DBG("end rc = %d\n", rc);

	return rc;
}


















static int32_t ius006f_set_picture_mode(struct T_pict_info *scene_info)




{
	int32_t rc = 0;

	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};



	camcmp_blank_info_type scene  = {0, NULL};
	int8_t  tbl_no;
	int8_t  set_scene;




	CAMCMP_LOG_DBG("start here !!!\n");



	
	
	if(scene_info->camera_mode == MODE_CONTINUOUS || scene_info->camera_mode == MODE_SPEED_MOVIE)
	{
		tbl_no = CAMCMP_BID_SCENE_MODE_AUTO_FIXATION;
	}
	
	else
	{
		tbl_no = CAMCMP_BID_SCENE_MODE_AUTO;
	}
	
	set_scene = scene_info->scene_mode + tbl_no;

	scene.blank_id           = set_scene;
	cmd_info[0].cmd_id       = CAMCMP_CID_SCENE_CHANGE;
	cmd_info[0].p_blank_info = &scene;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(scene);

























	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	CAMCMP_LOG_DBG("end rc = %d\n", rc);

	return rc;
}





















static int32_t ius006f_set_scene_angle(struct T_scene_angle_info *pict_angle)
{
	int32_t rc        = 0;

	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type scene_angle  = {0, NULL};

	CAMCMP_LOG_DBG("start here !!!\n");

	
	switch(pict_angle->scene_mode)
	{
		
		case CAMERA_SCENE_MODE_AUTO:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_AUTO;
			break;
		
		case CAMERA_SCENE_MODE_PORTRAIT:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_PORTRAIT;
			break;
		
		case CAMERA_SCENE_MODE_PORTRAIT_ILLUMI:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_PORTRAIT_ILLUMI;
			break;
		
		case CAMERA_SCENE_MODE_LANDSCAPE:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_LANDSCAPE;
			break;
		
		case CAMERA_SCENE_MODE_BACKLIGHT:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_BACKLIGHT;
			break;
		
		case CAMERA_SCENE_MODE_NIGHT:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_NIGHT;
			break;
		
		case CAMERA_SCENE_MODE_PET:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_PET;
			break;
		
		case CAMERA_SCENE_MODE_COOKING:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_COOKING;
			break;
		
		case CAMERA_SCENE_MODE_SPORTS:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_SPORTS;
			break;
		
		case CAMERA_SCENE_MODE_OFF:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_OFF;
			break;
		
		case CAMERA_SCENE_MODE_HIGH_SENSITIVITY:
			cmd_info[0].cmd_id = CAMCMP_CID_SCENE_ANGLE_HIGH_SENSITIVITY;
			break;
		default:
			break;
	}
	
	
	scene_angle.blank_id     = pict_angle->scene_angle;
	
	cmd_info[0].p_blank_info = &scene_angle;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(scene_angle);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	CAMCMP_LOG_DBG("end rc = %d\n", rc);

	return rc;
}





















static int ius006f_set_wb(int8_t wb)
{
	int32_t rc = -EFAULT;
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};

	switch (wb) {
		case MSM_CAM_WB_AUTO:            
			cmd_info[0].cmd_id = CAMCMP_CID_WB_AUTO;
			break;

		case MSM_CAM_WB_INCANDESCENT:    
			cmd_info[0].cmd_id = CAMCMP_CID_WB_INCAND;
			break;

		case MSM_CAM_WB_FLUORESCENT:     
			cmd_info[0].cmd_id = CAMCMP_CID_WB_FLUORE;
			break;

		case MSM_CAM_WB_DAYLIGHT:        
			cmd_info[0].cmd_id = CAMCMP_CID_WB_DAYLIGHT;
			break;

		case MSM_CAM_WB_CLOUDY:          
			cmd_info[0].cmd_id = CAMCMP_CID_WB_CLOUDY;
			break;

		case MSM_CAM_WB_LED:             
			cmd_info[0].cmd_id = CAMCMP_CID_WB_LED;
			break;

		default:
			CAMCMP_LOG_ERR("%s: invalid parameter (%d)\n", __func__, wb);
			return -EINVAL;
	}

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));

	if (rc != 0) {
		CAMCMP_LOG_ERR("%s: camcmp_isp_trans failed (%d)\n", __func__, rc);
		return -EFAULT;  
	}

	return 0;  
}



















static int ius006f_set_jpeg_quality(int8_t jpeg_quality)
{
	int32_t rc = -EFAULT;
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type quality  = {0, NULL};     

	switch (jpeg_quality) {
		case SENSOR_JPEG_Q_SUPER_FINE:  
			quality.blank_id = CAMCMP_BID_Q_SFINE;   
			break;

		case SENSOR_JPEG_Q_FINE:        
			quality.blank_id = CAMCMP_BID_Q_FINE;    
			break;

		case SENSOR_JPEG_Q_STANDARD:    
			quality.blank_id = CAMCMP_BID_Q_NORMAL;  
			break;

		default:
			CAMCMP_LOG_ERR("%s: invalid parameter (%d)\n", __func__, jpeg_quality);
			return -EINVAL;
	}


	cmd_info[0].cmd_id       = CAMCMP_CID_QUALITY;
	cmd_info[0].p_blank_info = &quality;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(quality);


	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));

	if (rc != 0) {
		CAMCMP_LOG_ERR("%s: camcmp_isp_trans failed (%d)\n", __func__, rc);
		return -EFAULT;  
	}

	rc = ius006f_change_mode(SENSOR_PREVIEW_MODE);
	if (rc != 0) {
		CAMCMP_LOG_ERR("ius006f_change_mode failed (%d)\n", rc); 
		return -EFAULT;
	}

	return 0;  
}


















static int ius006f_set_pict_size( int pict_size ) 
{
	int32_t rc = -EFAULT;
	camcmp_cmd_info_type cmd_info[] = { {0, NULL, 0, NULL, 0} };
	camcmp_blank_info_type jpeg_limit = {0, NULL};

	CAMCMP_LOG_DBG("start\n"); 

	
	switch (pict_size)
	{
		case SENSOR_CAMERA_1MP_SIZE:		
			jpeg_limit.blank_id = CAMCMP_BID_JPEG_LIMIT_SIZE_1M;
			break;










		case SENSOR_CAMERA_5MP_SIZE:		
			jpeg_limit.blank_id = CAMCMP_BID_JPEG_LIMIT_SIZE_5M;
			break;
		default:
			return -EINVAL;
	}

	
	cmd_info[0].cmd_id = CAMCMP_CID_JPEG_LIMIT;
	cmd_info[0].p_blank_info = &jpeg_limit;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(jpeg_limit);

	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));

	if (rc != 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed (%d)\n",rc);     
		return -EFAULT;
	}


	rc = ius006f_change_mode(SENSOR_PREVIEW_MODE);
	if (rc != 0) {
		CAMCMP_LOG_ERR("ius006f_change_mode failed (%d)\n", rc); 
		return -EFAULT;
	}

	CAMCMP_LOG_DBG("end rc = %d\n",rc);                          

	return rc;
}






















static int32_t ius006f_set_camera_mode(int8_t camera_mode)
{
	int32_t rc       = 0;

	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type cam_mode  = {0, NULL};

	CAMCMP_LOG_DBG("start here !!!\n");

	if(camera_mode >= MODE_MAX)
	{
		CAMCMP_LOG_ERR("camera_mode failed.\n");
		return -EINVAL;
	}
	else
	{
		
	}

	cam_mode.blank_id        = CAMCMP_BID_SCENE_SELECT_00;
	cmd_info[0].cmd_id       = CAMCMP_CID_CAMERA_MODE;
	cmd_info[0].p_blank_info = &cam_mode;
	cmd_info[0].blank_num    = CAMCMP_SIZE_BLKINF(cam_mode);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("camcmp_isp_trans failed. rc = %d\n", rc);
		return -EFAULT;
	}

	CAMCMP_LOG_DBG("end rc = %d\n", rc);

	return rc;
}















static int32_t ius006f_set_initialize(int8_t aFocusMove)
{
	int32_t rc = 0;

	
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};





	
	
	
	
	cmd_info[0].cmd_id = CAMCMP_CID_INIT_SET_5;
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("S7,8:af drv Initial failed. rc = %d\n", rc);

		ALARM_LOG("Event:0x%02X Info:0x%02X \n", ALARM_EVENT_CAM_FW_DOWN_ERR, ALARM_INFO_CAMERA);

		return -EFAULT;
	}
    
    if(aFocusMove != MODE_QUICK_SHOT)	rc = ius006f_set_default_focus();





	return rc;
}












static int32_t ius006f_set_flc(uint8_t flc_mode)
{
	int32_t ret = 0;

	
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_flc = {0, NULL};

	CAMCMP_LOG_DBG("ius006f_set_flc:flc_mode=%x \n", flc_mode);

  
  switch(flc_mode)
  {
  case  CAMERA_FLC_MODE_OFF       :
    set_flc.blank_id = CAMCMP_BID_FLC_MODE_OFF;
    break;
  case  CAMERA_FLC_MODE_50HZ      :
    set_flc.blank_id = CAMCMP_BID_FLC_MODE_50HZ;
    break;
  case  CAMERA_FLC_MODE_60HZ      :
    set_flc.blank_id = CAMCMP_BID_FLC_MODE_60HZ;
    break;
  case  CAMERA_FLC_MODE_AUTO      :
    set_flc.blank_id = CAMCMP_BID_FLC_MODE_AUTO;
    break;
  default                         :
		CAMCMP_LOG_DBG("ius006f_set_flc param error");
		ret = -EINVAL;
		break;
  }
  	
	cmd_info[0].cmd_id = CAMCMP_CID_FLC_MODE;
	cmd_info[0].p_blank_info = &set_flc;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(set_flc);
	
	ret = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (ret < 0) 
	{
		CAMCMP_LOG_ERR("ius006f_set_flc failed. rc = %d\n", ret);
		ret = -EFAULT;
  }
	return ret;
}





















static int ius006f_get_shutter_speed(struct get_shutter_speed_cfg *p_get_shutter_speed)
{
	int                  rc             = 0;
	uint32_t             shut_speed0    = 0;
	uint32_t             shut_speed1    = 0;
	E_IMAGE_SHAKE_KIND   image_shake    = E_IMAGE_SHAKE_ERROR;
	T_image_shake_judge  *p_shake_judge = p_get_shutter_speed->p_image_shake_judge;
	camcmp_cmd_info_type cmd_info1[]    = {{0, NULL, 0, NULL, 0}};

	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_H;
	cmd_info1[0].p_recieve_data = &shut_speed0;
	cmd_info1[0].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	else
	{
		
	}
	
	
	p_get_shutter_speed->shutter_speed_0 = (shut_speed0 & 0x0000ff00) >> 8;
	p_get_shutter_speed->shutter_speed_1 = (shut_speed0 & 0x000000ff);
	CAMCMP_LOG_DBG("shut_speed0=%x\n", shut_speed0);

	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_L;
	cmd_info1[0].p_recieve_data = &shut_speed1;
	cmd_info1[0].recieve_num = 1;

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	else
	{
		
	}
	
	
	p_get_shutter_speed->shutter_speed_2 = (shut_speed1 & 0x0000ff00) >> 8;
	p_get_shutter_speed->shutter_speed_3 = (shut_speed1 & 0x000000ff);
	CAMCMP_LOG_DBG("shut_speed1=%x \n", shut_speed1);

	
	image_shake = ius006f_image_shake_judge(shut_speed0,shut_speed1);
	
	
	p_shake_judge->shake = image_shake;
	

	if(p_shake_judge->shake == E_IMAGE_SHAKE_OFF)
	{
		p_shake_judge->result = E_SET_OK;
	}

	
	return rc;
}
















static int ius006f_get_shutter_speed_gain(struct get_shutter_speed_gain_cfg *p_get_shutter_speed_gain)
{
	int                  rc               = 0;
	uint32_t             shut_speed0      = 0;
	uint32_t             shut_speed1      = 0;
	uint32_t             agc_scl          = 0;
	uint32_t             set_speed        = 0;
	uint32_t             set_agcage       = 0;
	T_image_shake_judge  *p_shake_judge   = p_get_shutter_speed_gain->p_image_shake_judge;
	camcmp_cmd_info_type cmd_info1[]      = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_shut_speed = {0, NULL};
	camcmp_blank_info_type set_agc        = {0, NULL};


	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_CAP_HALF_AE_CTRL;
	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		p_shake_judge->result = E_SET_NG;
		return -EFAULT;
	}
	else
	{
		
	}

	
	
	
	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_H;
	cmd_info1[0].p_recieve_data = &shut_speed0;
	cmd_info1[0].recieve_num = 1; 

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		p_shake_judge->result = E_SET_NG;
		return -EFAULT;
	}
	else
	{
		
	}
	
	
	p_get_shutter_speed_gain->shutter_speed_0 = (shut_speed0 & 0x0000ff00) >> 8;
	p_get_shutter_speed_gain->shutter_speed_1 = (shut_speed0 & 0x000000ff);
	CAMCMP_LOG_DBG("shut_speed0=%x\n", shut_speed0);
	cmd_info1[0].cmd_id         = 0;
	cmd_info1[0].p_blank_info   = NULL;
	cmd_info1[0].blank_num      = 0;
	cmd_info1[0].p_recieve_data = NULL;
	cmd_info1[0].recieve_num    = 0;

	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_SHT_TIME_L;
	cmd_info1[0].p_recieve_data = &shut_speed1;
	cmd_info1[0].recieve_num = 1; 

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		p_shake_judge->result = E_SET_NG;
		return -EFAULT;
	}
	else
	{
		
	}
	
	
	p_get_shutter_speed_gain->shutter_speed_2 = (shut_speed1 & 0x0000ff00) >> 8;
	p_get_shutter_speed_gain->shutter_speed_3 = (shut_speed1 & 0x000000ff);
	CAMCMP_LOG_DBG("shut_speed1=%x \n", shut_speed1);
	cmd_info1[0].cmd_id         = 0;
	cmd_info1[0].p_blank_info   = NULL;
	cmd_info1[0].blank_num      = 0;
	cmd_info1[0].p_recieve_data = NULL;
	cmd_info1[0].recieve_num    = 0;

	
	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_GET_AGC_SCL;
	cmd_info1[0].p_recieve_data = &agc_scl;
	cmd_info1[0].recieve_num = 1; 

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		p_shake_judge->result = E_SET_NG;
		return -EFAULT;
	}
	else
	{
		
	}

	
	p_get_shutter_speed_gain->AGC_gain_0 = (agc_scl & 0x0000ff00) >> 8;
	p_get_shutter_speed_gain->AGC_gain_1 = (agc_scl & 0x000000ff);
	cmd_info1[0].cmd_id         = 0;
	cmd_info1[0].p_blank_info   = NULL;
	cmd_info1[0].blank_num      = 0;
	cmd_info1[0].p_recieve_data = NULL;
	cmd_info1[0].recieve_num    = 0;

	CAMCMP_LOG_DBG("AGC_gain_0=%x \n", agc_scl);

	
	
	
	ius006f_cal_manual_ae(shut_speed0, shut_speed1, agc_scl, &set_speed, &set_agcage);
    CAMCMP_LOG_DBG("set_speed = %d  set_agc = %d", set_speed, set_agcage);

	
	
	
	
	set_shut_speed.blank_id = CAMCMP_BID_SET_SHUT;
	set_shut_speed.p_blank_data = &set_speed;
	cmd_info1[0].cmd_id = CAMCMP_CID_SET_SHUT;
	cmd_info1[0].p_blank_info = &set_shut_speed;
	cmd_info1[0].blank_num = CAMCMP_SIZE_BLKINF(set_shut_speed);

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		p_shake_judge->result = E_SET_NG;
		return -EFAULT;
	}
	else
	{
		
	}
	
	cmd_info1[0].cmd_id         = 0;
	cmd_info1[0].p_blank_info   = NULL;
	cmd_info1[0].blank_num      = 0;
	cmd_info1[0].p_recieve_data = NULL;
	cmd_info1[0].recieve_num    = 0;

	
	
	
	
	set_agc.blank_id = CAMCMP_BID_SET_GAIN;
	set_agc.p_blank_data = &set_agcage;
	cmd_info1[0].cmd_id = CAMCMP_CID_SET_GAIN;
	cmd_info1[0].p_blank_info = &set_agc;
	cmd_info1[0].blank_num = CAMCMP_SIZE_BLKINF(set_agc);

	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		p_shake_judge->result = E_SET_NG;
		return -EFAULT;
	}
	else
	{
		
	}
	
	cmd_info1[0].cmd_id         = 0;
	cmd_info1[0].p_blank_info   = NULL;
	cmd_info1[0].blank_num      = 0;
	cmd_info1[0].p_recieve_data = NULL;
	cmd_info1[0].recieve_num    = 0;

	
	
	cmd_info1[0].cmd_id = CAMCMP_CID_CAP_GAINOFFSET;
	rc = camcmp_isp_trans(cmd_info1, CAMCMP_SIZE_CMD(cmd_info1));
	if (rc < 0)
	{
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		p_shake_judge->result = E_SET_NG;
		return -EFAULT;
	}
	else
	{
		
	}
	
	
	p_shake_judge->result = E_SET_OK;

	return rc;
}















static int ius006f_set_capture_num(E_SET_PICTUER_NUM set_capture_num)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_cap_num = {0, NULL};

	CAMCMP_LOG_DBG("capture num = %d \n", set_capture_num);
	
	
	if ((set_capture_num != E_SET_PICTUER_NUM_1) && (set_capture_num != E_SET_PICTUER_NUM_2))
	{
		CAMCMP_LOG_ERR("param error. set_capture_num=%d\n", set_capture_num);
		return -EINVAL;
	}
	else
	{
		
	}

	
	
	set_cap_num.blank_id = set_capture_num;
	cmd_info[0].cmd_id = CAMCMP_CID_PICTUER_NUM;
	cmd_info[0].p_blank_info = &set_cap_num;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(set_cap_num);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("error root:%d\n", __LINE__);
		return -EFAULT;
	}
	else
	{
		
	}

	return rc;
}















static int ius006f_set_ae_stop(void)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};

	
	cmd_info[0].cmd_id = CAMCMP_CID_AE_STOP;

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans failed.  %d\n", __LINE__);
		return -EFAULT;
	}
	else
	{
		
	}

	return rc;
}




















static int ius006f_set_isotype(int8_t iso_type)
{
	int rc = 0;
	camcmp_cmd_info_type cmd_info[]  = {{0, NULL, 0, NULL, 0}};
	camcmp_blank_info_type set_isotype = {0, NULL};

	CAMCMP_LOG_DBG("iso_type=%x \n", iso_type);
	
	
	switch (iso_type)
	{
		case MSM_CAMERA_ISO_1600:		
			set_isotype.blank_id = CAMCMP_BID_ISO_1600;
			break;
		case MSM_CAMERA_ISO_3200:		
			set_isotype.blank_id = CAMCMP_BID_ISO_3200;
			break;
		case MSM_CAMERA_ISO_12800:		
			set_isotype.blank_id = CAMCMP_BID_ISO_12800;
			break;
		default:
			CAMCMP_LOG_DBG("param error. default\n");
			return -EINVAL;
	}

	
	
	cmd_info[0].cmd_id = CAMCMP_CID_ISO;
	cmd_info[0].p_blank_info = &set_isotype;
	cmd_info[0].blank_num = CAMCMP_SIZE_BLKINF(set_isotype);

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc != 0) {
		CAMCMP_LOG_ERR("camcmp_isp_trans error:%d\n", __LINE__);
		return -EFAULT;
	}

	return rc;
}
















static int32_t ius006f_setting(void)
{
	int32_t rc = 0;
	uint16_t power_on_t4 = 0;	

	
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}};

	
	struct timeval starttv = {0};	
	struct timeval endtv   = {0};	
	uint32_t elapsedtime   = 0;	





	
	
	
	cmd_info[0].cmd_id = CAMCMP_CID_INIT_SET_2;
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("S3:Initial Setting2 pict out off failed. rc = %d\n", rc);
		return -EFAULT;
	}

	
	
	
	if ( (ius006f_ctrl->otp_rom_data[CAMCMP_OTP0M] & 0x0003FFC0) != 0 ) {
		cmd_info[0].cmd_id = CAMCMP_CID_INIT_SET_3;
		rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
		if (rc < 0) {
			CAMCMP_LOG_ERR("S4:Initial Setting3 failed. rc = %d\n", rc);
			return -EFAULT;
		}
	}















	
	
	
	rc = gpio_request(IUS006F_GPIO_CAM_STBY, "ius006f");
	if (!rc) {
		gpio_direction_output(IUS006F_GPIO_CAM_STBY, 1);
	}
	else {
		return -EINVAL;
	}

	
	mdelay(IUS006F_POWER_ON_T3);

	
	
	do_gettimeofday(&starttv);

	
	
	
	cmd_info[0].cmd_id = CAMCMP_CID_INIT_SET_4;
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("S6:Initial Setting4 failed. rc = %d\n", rc);
		return -EFAULT;
	}

	
	power_on_t4 = IUS006F_FRAME_DEF * IUS006F_POWER_ON_T4;
	
	do_gettimeofday(&endtv);
	
	elapsedtime = ((endtv.tv_sec - starttv.tv_sec) * CAMCMP_CALC_1000) +
		      ((endtv.tv_usec - starttv.tv_usec) / CAMCMP_CALC_1000);
	CAMCMP_LOG_DBG("T4: output time = %d, elapsed time = %d\n", power_on_t4, elapsedtime);
	
	if (elapsedtime < power_on_t4) {
		



	}




















	return rc;
}




















static int ius006f_vreg_control_lvs1(enum msm_sensor_onoff onoff)
{
	struct vreg *sensor_vreg;
	int rc = 0;

	
	sensor_vreg = vreg_get(NULL, "lvsw1");
	if ( IS_ERR(sensor_vreg) || sensor_vreg == NULL ) {
		CAMCMP_LOG_ERR("vreg_get(%s) failed (%ld)\n", "lvsw1", PTR_ERR(sensor_vreg));
		return -EFAULT;
	}

	
	if (onoff == SENSOR_ON) { 
		
		rc = vreg_set_level(sensor_vreg, 1800);
		if (rc) {
			CAMCMP_LOG_ERR("vreg_set_level failed (%d)\n", rc);
			return -EFAULT;
		}
		rc = vreg_enable(sensor_vreg);
		if (rc) {
			CAMCMP_LOG_ERR("vreg_enable failed = (%d)\n", rc);
			return -EFAULT;
		}
	
	} else {
		rc = vreg_disable(sensor_vreg);
		if (rc) {
			CAMCMP_LOG_ERR("vreg disable failed (%d)\n", rc);
			return -EFAULT;
		}
	}

	return 0;
}
























static int ius006f_vreg_control(enum msm_sensor_onoff onoff, const char *id)
{
	struct vreg *sensor_vreg;
	int rc = 0;

	
	sensor_vreg = vreg_get(NULL, id);
	if ( IS_ERR(sensor_vreg) || sensor_vreg == NULL ) {
		CAMCMP_LOG_ERR("vreg_get(%s) failed (%ld)\n", id, PTR_ERR(sensor_vreg));
		return -EFAULT;
	}

	
	if (onoff == SENSOR_ON) {
		
		if (strcmp(id, "gp15") == 0) {
			rc = vreg_set_level(sensor_vreg, 1200);
		} else if (strcmp(id, "gp2") == 0) {
			rc = vreg_set_level(sensor_vreg, 2700);
		} else if (strcmp(id, "gp6") == 0) {
			rc = vreg_set_level(sensor_vreg, 2800);
		} else {
			rc = 1;
		}
		if (rc) {
			CAMCMP_LOG_ERR("vreg_set_level failed (%d)\n", rc);
			return -EFAULT;
		}
		rc = vreg_enable(sensor_vreg);
		if (rc) {
			CAMCMP_LOG_ERR("vreg_enable failed = (%d)\n", rc);
			return -EFAULT;
		}
	
	} else {
		rc = vreg_disable(sensor_vreg);
		if (rc) {
			CAMCMP_LOG_ERR("vreg disable failed (%d)\n", rc);
			return -EFAULT;
		}
	}

	return 0;
}









static void ius006f_probe_init_done(const struct msm_camera_sensor_info *data)
{





	static struct clk *cam_clk;
	cam_clk  = clk_get(NULL, "cam_m_clk");




	
	gpio_direction_output(data->sensor_reset, 0);
	gpio_free(data->sensor_reset);

	




	clk_disable(cam_clk);
	clk_put(cam_clk);


















	
	mdelay(IUS006F_POWER_WAIT);














	
	(void)ius006f_vreg_control(SENSOR_OFF, "gp6");

	mdelay(IUS006F_POWER_WAIT);

	
	(void)ius006f_vreg_control(SENSOR_OFF, "gp2");





	mdelay(IUS006F_POWER_WAIT);
	(void)ius006f_vreg_control_lvs1(SENSOR_OFF); 





	mdelay(IUS006F_POWER_OFF_IOVD);

	
	(void)ius006f_vreg_control(SENSOR_OFF, "gp15");





	mdelay(IUS006F_POWER_OFF_IOVD);
	
	gpio_direction_output(data->sensor_pwd, 0);
	gpio_free(data->sensor_pwd);
}






static int ius006f_probe_init_sensor(const struct msm_camera_sensor_info *data)
{
	int32_t rc = 0;
	
	camcmp_cmd_info_type cmd_info[] = {{0, NULL, 0, NULL, 0}, {0, NULL, 0, NULL, 0}};






	static struct clk *cam_clk;
	cam_clk  = clk_get(NULL, "cam_m_clk");
	clk_set_rate(cam_clk, 25600000);




	
	rc = gpio_request(data->sensor_pwd, "ius006f");
	if (!rc) {
		gpio_direction_output(data->sensor_pwd, 1);
	}
	else {
		CAMCMP_LOG_ERR("sensor_pwd Error, rc = %d\n", rc);
		return -EFAULT;
	}



	
	mdelay(IUS006F_POWER_WAIT);



	
	rc = ius006f_vreg_control(SENSOR_ON, "gp15");
	if (rc < 0) {
		
		ius006f_probe_init_done(data);
		CAMCMP_LOG_ERR("DVDD(1.2V) Error, rc = %d\n", rc);
		return -EFAULT;
	}

	mdelay(IUS006F_POWER_WAIT);









	
	rc = ius006f_vreg_control_lvs1(SENSOR_ON); 
	if (rc < 0) {
		
		ius006f_probe_init_done(data);


		CAMCMP_LOG_ERR("IOVDD(1.8V) Error, rc = %d\n", rc);




		return -EFAULT;
	}

	mdelay(IUS006F_POWER_WAIT);

	





















	rc = ius006f_vreg_control(SENSOR_ON, "gp2");
	if (rc < 0) {
		
		ius006f_probe_init_done(data);
		CAMCMP_LOG_ERR("AVDD(2.7V) Error, rc = %d\n", rc);
		return -EFAULT;
	}





	mdelay(IUS006F_POWER_WAIT);
	

	





















	rc = ius006f_vreg_control(SENSOR_ON, "gp6");
	if (rc < 0) {
		
		ius006f_probe_init_done(data);
		CAMCMP_LOG_ERR("VCM_VDD(2.8V) Error, rc = %d\n", rc);
		return -EFAULT;
	}





	mdelay(IUS006F_POWER_WAIT);		

	




	clk_enable(cam_clk);
















	
	mdelay(IUS006F_POWER_ON_NCYC);

	
	rc = gpio_request(data->sensor_reset, "ius006f");
	if (!rc) {
		gpio_direction_output(data->sensor_reset, 1);
	}
	else {
		
		ius006f_probe_init_done(data);
		CAMCMP_LOG_ERR("sensor_reset Error, rc = %d\n", rc);
		return -EFAULT;
	}

	
	mdelay(IUS006F_POWER_ON_T1);

	
	cmd_info[0].cmd_id = CAMCMP_CID_CHK_DEV_STS;
	
	cmd_info[1].cmd_id = CAMCMP_CID_INIT_SET_1;

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("Read I2C status or S1:Initial Setting1_inclk failed. rc = %d\n", rc);
		ius006f_probe_init_done(data);
		return -EFAULT;
	}

	
	udelay(IUS006F_POWER_ON_T2);

	
	cmd_info[0].cmd_id = CAMCMP_CID_CHK_DEV_STS;
	
	cmd_info[1].cmd_id = CAMCMP_CID_GET_OTP;
	cmd_info[1].p_recieve_data = (void*)ius006f_ctrl->otp_rom_data;
	cmd_info[1].recieve_num = CAMCMP_OTP_ROM_NUM;

	
	rc = camcmp_isp_trans(cmd_info, CAMCMP_SIZE_CMD(cmd_info));
	if (rc < 0) {
		CAMCMP_LOG_ERR("Read I2C status or S2:OTP Read failed. rc = %d\n", rc);
		ius006f_probe_init_done(data);
		return -EFAULT;
	}

	
	
	
	rc = camcmp_makecmd_correction((void*)ius006f_ctrl->otp_rom_data, CAMCMP_OTP_ROM_NUM);
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_makecmd_correction failed. rc = %d\n", rc);
		ius006f_probe_init_done(data);
		return -EFAULT;
	}

	return 0;
}






static int ius006f_sensor_open_init(const struct msm_camera_sensor_info *data)
{
	int32_t rc;




	struct msm_camera_csi_params ius006f_csi_params;




	
	ius006f_ctrl = kzalloc(sizeof(struct ius006f_ctrl), GFP_KERNEL);
	if (!ius006f_ctrl) {
		CAMCMP_LOG_ERR("ius006f_init failed!\n");


		kfree(ius006f_ctrl);


		return -ENOMEM;
	}
	
	if (data) {
		ius006f_ctrl->sensordata = data;
	}

	
	ius006f_ctrl->sensormode = SENSOR_PREVIEW_MODE;

	
	ius006f_ctrl->prev_res = SENSOR_CAMERA_VGA_SIZE;

	
	
	ius006f_ctrl->init_curr_lens_pos = 0;

	
	ius006f_ctrl->af_cancel_onoff = SENSOR_OFF;

	
	ius006f_ctrl->night_mode = 0;




	
	ius006f_ctrl->afc_mode = SENSOR_AF_STATUS_IDLE;
	
	ius006f_ctrl->inf_over_search = -1;



	


	af_start_after_cnt =0;
	





	
	ius006f_csi_params.data_format = CSI_8BIT;
	ius006f_csi_params.lane_cnt = 2;
	ius006f_csi_params.lane_assign = 0xe4;
	ius006f_csi_params.dpcm_scheme = 0;
	ius006f_csi_params.settle_cnt = 10;
	rc = msm_camio_csi_config(&ius006f_csi_params);
	if (rc < 0) {
		CAMCMP_LOG_ERR("config csi controller failed \n");
		return -EFAULT;
	}







	mdelay(IUS006F_WAIT_20);

	
	
	rc = camcmp_makecmd_init();
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_makecmd_init failed\n");
		return -EFAULT;
	}
	

	
	rc = ius006f_probe_init_sensor(data);
	if (rc < 0) {
		if (ius006f_ctrl) {
			kfree(ius006f_ctrl);
			ius006f_ctrl = NULL;
		}
		return rc;
	}

	
	rc = ius006f_setting();
	if (rc < 0) {
		CAMCMP_LOG_ERR("ius006f_setting failed. rc = %d\n", rc);
		ius006f_sensor_release();    
	}

	return rc;
}






int ius006f_sensor_release(void)
{








	mutex_lock(&ius006f_mut);
	


    
    ius006f_poweroff();
























	CAMCMP_LOG_DBG("ius006f_release completed\n");

	mutex_unlock(&ius006f_mut);

	return 0;
}













int ius006f_sensor_config(void *__sync, void __user *argp) 
{
	struct sensor_cfg_data cdata;
	struct msm_sync *sync = (struct msm_sync *) __sync; 
	int rc = 0;

	CAMCMP_LOG_DBG("start here !!!\n");
	if (copy_from_user(&cdata,
			   (void *)argp, sizeof(struct sensor_cfg_data))) {
		return -EFAULT;
	}




    
	if(!ius006f_ctrl)
	{
        CAMCMP_LOG_DBG("ius006f Control Buffer Noting!!\n");
        return 0;
    }



	mutex_lock(&ius006f_mut);

	CAMCMP_LOG_DBG("cfgtype = %d\n", cdata.cfgtype);
	switch (cdata.cfgtype) {
	case CFG_SET_MODE:
	
		CAMCMP_LOG_DBG("CFG_SET_MODE\n");



		rc = ius006f_set_mode(cdata.mode, cdata.rs, cdata.cfg.set_camera_mode);





		break;

	case  CFG_SET_AF_MODE:
		CAMCMP_LOG_DBG("CFG_SET_AF_MODE\n");
		rc = ius006f_set_af_mode(sync, &(cdata.cfg.af_mode)); 

		if (copy_to_user((void *)argp, &cdata,
				 sizeof(struct sensor_cfg_data))) {
			rc = -EFAULT;
		}

		break;


	case CFG_GET_EEPROM_READ:
		rc = ius006f_get_otp(&(cdata.cfg.get_otp));
		if (copy_to_user((void *)argp, &cdata,
				 sizeof(struct sensor_cfg_data))) {
			rc = -EFAULT;
		}
		break;
	case CFG_SENSOR_PAT_CHG:
		rc = ius006f_sensor_pat_chg(&(cdata.cfg.pat_chg));
		if (copy_to_user((void *)argp, &cdata,
				 sizeof(struct sensor_cfg_data))) {
			rc = -EFAULT;
		}
		break;



    case CFG_GET_AF_POS:
		CAMCMP_LOG_DBG("CFG_GET_AF_POS\n");
		rc = ius006f_get_af_pos(&(cdata.cfg.get_af_pos));
		if (rc >= 0) {
			if (copy_to_user((void *)argp, &cdata,
					 sizeof(struct sensor_cfg_data))) {
				rc = -EFAULT;
			}
		}
		break;
    case CFG_GET_MONI_GAIN:
		CAMCMP_LOG_DBG("CFG_GET_MONI_GAIN\n");
		rc = ius006f_get_moni_gain(&(cdata.cfg.get_monigain));
		if (rc >= 0) {
			if (copy_to_user((void *)argp, &cdata,
					 sizeof(struct sensor_cfg_data))) {
				rc = -EFAULT;
			}
		}
		break;
    case CFG_GET_REGVER:
		CAMCMP_LOG_DBG("CFG_GET_REGVER\n");
		rc = ius006f_get_reg_ver(&(cdata.cfg.get_reg_ver));
		if (rc >= 0) {
			if (copy_to_user((void *)argp, &cdata,
					 sizeof(struct sensor_cfg_data))) {
				rc = -EFAULT;
			}
		}
		break;



	case CFG_SET_DEFAULT_FOCUS:
		CAMCMP_LOG_DBG("CFG_SET_DEFAULT_FOCUS\n");
		rc = ius006f_set_default_focus();
		break;

	case CFG_AUTO_FOCUS:
		CAMCMP_LOG_DBG("CFG_AUTO_FOCUS\n");
        
    	if(ius006f_ctrl->sensormode == SENSOR_HALF_MODE)
    	{
            
    		rc = ius006f_change_mode(SENSOR_PREVIEW_MODE);
    		
    		msleep(38*10);
        }
        
		rc = ius006f_af_start(sync); 
		break;

	case CFG_AUTO_FOCUS_AFTER:
		CAMCMP_LOG_DBG("CFG_AUTO_FOCUS_AFTER\n");
		rc = ius006f_af_start_after(sync); 
		break;

	case CFG_AUTO_FOCUS_CANCEL:
		CAMCMP_LOG_DBG("CFG_AUTO_FOCUS_CANCEL\n");
		rc = ius006f_af_cancel();
		break;



	case CFG_SET_BRIGHTNESS:
		CAMCMP_LOG_DBG("CFG_SET_BRIGHTNESS\n");
		rc = ius006f_set_brightness(cdata.cfg.brightness);
		break;

	case CFG_SET_EFFECT:
		CAMCMP_LOG_DBG("CFG_SET_EFFECT\n");
		rc = ius006f_set_effect(cdata.cfg.effect);
		break;



    case CFG_SET_ZOOM:
		CAMCMP_LOG_DBG("CFG_SET_ZOOM\n");



		rc = ius006f_set_zoom( &(cdata.cfg.set_zoom) , cdata.rs);





		break;

    case CFG_SET_PICTURE_MODE:
		CAMCMP_LOG_DBG("CFG_SET_PICTURE_MODE\n");


		rc = ius006f_set_picture_mode( &(cdata.cfg.scene_info) );




		break;



	case CFG_SET_WB:
		CAMCMP_LOG_DBG("ius006f_sensor_config CFG_SET_WB\n");
		rc = ius006f_set_wb(cdata.cfg.wb);
		break;



	case CFG_SET_JPEG_QUALITY:
		CAMCMP_LOG_DBG("ius006f_sensor_config CFG_SET_JPEG_QUALITY\n");
		rc = ius006f_set_jpeg_quality(cdata.cfg.jpeg_quality);
		break;


    case CFG_SET_MANUAL_STEP:
		CAMCMP_LOG_DBG("CFG_SET_MANUAL_STEP\n");
		rc = ius006f_set_manual_step(&(cdata.cfg.set_manual_step));
		if (rc >= 0) {
			if (copy_to_user((void *)argp, &cdata,
					 sizeof(struct sensor_cfg_data))) {
				rc = -EFAULT;
			}
		}
		break;


	case CFG_SET_PICTURE_SIZE:
		CAMCMP_LOG_DBG("CFG_SET_PICTURE_SIZE\n");
		rc = ius006f_set_pict_size( cdata.rs );
		break;




	case CFG_SET_INITIALIZE:
		CAMCMP_LOG_DBG("CFG_SET_INITIALIZE\n");
		rc = ius006f_set_initialize(cdata.cfg.set_camera_mode);
		break;


	case CFG_SET_FLC:
		CAMCMP_LOG_DBG("CFG_SET_FLC\n");
		rc = ius006f_set_flc(cdata.cfg.flc_mode);
		break;


	
	case CFG_GET_SHAKE_JUDGE:
		CAMCMP_LOG_DBG("CFG_GET_SHAKE_JUDGE\n");
		rc = ius006f_get_shutter_speed(&(cdata.cfg.get_shutter_speed));
		break;

	
	case CFG_GET_SHUTTER_SPEED_GAIN:
		CAMCMP_LOG_DBG("CFG_GET_SHUTTER_SPEED_GAIN\n");
		rc = ius006f_get_shutter_speed_gain(&(cdata.cfg.get_shutter_speed_gain));
		break;
		
	
	case CFG_SET_CAP_NUM:
		CAMCMP_LOG_DBG("CFG_SET_CAP_NUM\n");
		rc = ius006f_set_capture_num(cdata.cfg.set_capture_num);
		break;
		
	
	case CFG_SET_AE_STOP:
		CAMCMP_LOG_DBG("CFG_SET_AE_STOP\n");
		rc = ius006f_set_ae_stop();
		break;



	
	case CFG_SET_SCENE_ANGLE:
		CAMCMP_LOG_DBG("CFG_SET_SCENE_ANGLE\n");
		rc = ius006f_set_scene_angle(&(cdata.cfg.set_angle_info));
		break;



	
	case CFG_SET_CAM_MODE:
		CAMCMP_LOG_DBG("CFG_SET_CAM_MODE\n");
		rc = ius006f_set_camera_mode(cdata.cfg.set_camera_mode);
		break;



	
	case CFG_AFC_STOP:
		CAMCMP_LOG_DBG("CFG_AFC_STOP\n");
		rc = ius006f_afc_stop();
		break;
	
	case CFG_AFC_START:
		CAMCMP_LOG_DBG("CFG_AFC_START\n");
		rc = ius006f_afc_start(cdata.cfg.set_af_lens_position);
		break;
	
	case CFG_SET_M_FOCUS:
		CAMCMP_LOG_DBG("CFG_SET_M_FOCUS %d\n", cdata.cfg.set_af_lens_position);
		rc = ius006f_set_lens_position(cdata.cfg.set_af_lens_position);
		break;
	
	case CFG_SET_FRAME_POS:
		CAMCMP_LOG_DBG("CFG_SET_FRAME_POS\n");
		rc = ius006f_set_frame_pos(cdata.cfg.set_frame_position);
		break;
	
	case CFG_AFC_LOCK_START:
		CAMCMP_LOG_DBG("CFG_AFC_LOCK_START\n");
		rc = ius006f_afc_lock_start(sync, &(cdata.cfg.set_af_lock));
		CAMCMP_LOG_DBG("CFG_AFC_LOCK_START End result = %d\n", rc);
		break;
	
	case CFG_AFC_GET_RESULT:
		CAMCMP_LOG_DBG("CFG_AFC_GET_RESULT\n");
		rc = ius006f_afc_get_result(sync, &(cdata.cfg.set_af_move));
		CAMCMP_LOG_DBG("CFG_AFC_GET_RESULT End result = %d\n", rc);
		break;
	
	case CFG_AFC_HOLD_REQUEST:
		CAMCMP_LOG_DBG("CFG_AFC_HOLD_REQUEST\n");
		rc = ius006f_afc_hold_request(cdata.cfg.set_af_hold_status);
		break;
	
	case CFG_GET_FOCALLENGTH:
		CAMCMP_LOG_DBG("CFG_GET_FOCALLENGTH\n");
		rc = ius006f_afc_focal_length(&(cdata.cfg.get_lens_pos));
		break;
    
	case CFG_SET_WEIGHTMODE:
		CAMCMP_LOG_DBG("CFG_SET_WEIGHTMODE\n");
		rc = ius006f_set_weightmode(cdata.cfg.set_af_setting_info);
		break;
    
    case CFG_SET_FREE_WEIGHT:
		CAMCMP_LOG_DBG("CFG_SET_FREE_WEIGHT %d\n", cdata.cfg.free_weight);
		rc = ius006f_set_free_weight(cdata.cfg.free_weight);
        break;
    
    case CFG_AFS_STOP       :
		CAMCMP_LOG_DBG("CFG_SET_FREE_WEIGHT %d\n", cdata.cfg.free_weight);
		rc = ius006f_afs_stop();
        break;



	case CFG_SET_ISO:
		CAMCMP_LOG_DBG("CFG_SET_ISO\n");
		rc = ius006f_set_isotype(cdata.cfg.iso_type);
		break;





	case CFG_GET_PARAM_EXIF:
		CAMCMP_LOG_DBG("CFG_GET_PARAM_EXIF\n");
		rc = ius006f_get_exif_param(&(cdata.cfg.get_exif_param));
		if (rc >= 0) {
			if (copy_to_user((void *)argp, &cdata,
					 sizeof(struct sensor_cfg_data))) {
				rc = -EFAULT;
			}
		}
		break;



    case    CFG_POWER_OFF   :
		CAMCMP_LOG_DBG("CFG_POWER_OFF\n");
		rc = ius006f_poweroff();
        break;




	default:
		rc = -EINVAL;
		break;
	}

	mutex_unlock(&ius006f_mut);
	return rc;
}






static void ius006f_init_client(struct i2c_client *client)
{
	
	init_waitqueue_head(&ius006f_wait_queue);
}








static int ius006f_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	int rc = 0;
	CAMCMP_LOG_DBG("ius006f_probe called!\n");

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		CAMCMP_LOG_ERR("i2c_check_functionality failed\n");
		rc = -EFAULT;
		goto probe_failure;
	}

	ius006f_sensorw = kzalloc(sizeof(struct ius006f_work), GFP_KERNEL);
	if (!ius006f_sensorw) {
		CAMCMP_LOG_ERR("kzalloc failed.\n");
		rc = -ENOMEM;
		goto probe_failure;
	}

	i2c_set_clientdata(client, ius006f_sensorw);
	ius006f_init_client(client);
	ius006f_client = client;
	
	
	
	rc = camcmp_i2c_init((void*)client);
	if (rc < 0) {
		CAMCMP_LOG_ERR("camcmp_i2c_init failed\n");
		rc = -EFAULT;
		goto probe_failure;
	}
	

	mdelay(IUS006F_WAIT_50);

	CAMCMP_LOG_DBG("ius006f_probe successed! rc = %d\n", rc);
	return rc;

probe_failure:
	CAMCMP_LOG_ERR("ius006f_probe failed! rc = %d\n", rc);
	return rc;
}



static const struct i2c_device_id ius006f_i2c_id[] = {
	{"ius006f", 0},
	{}
};


static struct i2c_driver ius006f_i2c_driver = {
	.id_table = ius006f_i2c_id,
	.probe = ius006f_i2c_probe,
	.remove = __exit_p(ius006f_i2c_remove),
	.driver = {
		   .name = "ius006f",
		   },
};







static int ius006f_sensor_probe(const struct msm_camera_sensor_info *info,
				struct msm_sensor_ctrl *ctrl)
{
	int rc = i2c_add_driver(&ius006f_i2c_driver);
	if (rc < 0 || ius006f_client == NULL) {
		rc = -ENOTSUPP;
		goto probe_done;
	}








	ctrl->s_init = ius006f_sensor_open_init;	
	ctrl->s_release = ius006f_sensor_release;	

	ctrl->s_config = NULL;						
	ctrl->s_config2 = ius006f_sensor_config;	 



	ctrl->s_camera_type = BACK_CAMERA_2D;
	ctrl->s_mount_angle = 0;


probe_done:
	CAMCMP_LOG_ERR("%s\n", __FILE__);
	return rc;
}





static int __ius006f_probe(struct platform_device *pdev)
{
	return msm_camera_drv_start(pdev, ius006f_sensor_probe);
}



static struct platform_driver msm_camera_driver = {
	.probe = __ius006f_probe,
	.driver = {
		   .name = "msm_camera_ius006f",
		   .owner = THIS_MODULE,
		   },
};





static int __init ius006f_init(void)
{
	return platform_driver_register(&msm_camera_driver);
}



module_init(ius006f_init);
