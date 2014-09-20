/*
 * leds-bd6082gul.c - platform data structure for bd6082gul led controller
 *
 * Copyright (C) 2010 NEC NEC Corporation
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/
 
#include <linux/device.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <mach/gpio.h>

#include <mach/msm_battery.h>			
#include <linux/oemnc_info.h>

#include <linux/leds-bd6082gul.h>













#define LED_REG_SOFTWARE_RESET					0x00
#define LED_REG_BACKLIGHT_ALLOC					0x01
#define LED_REG_BACKLIGHT_CONTROL				0x02
#define LED_REG_BACKLIGHT_MAIN_CURRENT			0x03
#define LED_REG_BACKLIGHT_SUB_CURRENT			0x04
#define LED_REG_BACKLIGHT_CURRENT_CHANGE		0x05

#define LED_REG_RGB_CLOCK_SETTING				0x06
#define LED_REG_RGB_CONTROL						0x07
#define LED_REG_RGB_TIME_SETTING				0x08

#define LED_REG_RGB_R1_CURRENT_SETTING			0x09
#define LED_REG_RGB_R2_CURRENT_SETTING			0x0A
#define LED_REG_RGB_R1_CORRUGATION_PATTERN_SETTING	0x0B

#define LED_REG_RGB_G1_CURRENT_SETTING			0x0C
#define LED_REG_RGB_G2_CURRENT_SETTING			0x0D
#define LED_REG_RGB_G1_CORRUGATION_PATTERN_SETTING	0x0E

#define LED_REG_RGB_B1_CURRENT_SETTING			0x0F
#define LED_REG_RGB_B2_CURRENT_SETTING			0x10
#define LED_REG_RGB_B1_CORRUGATION_PATTERN_SETTING	0x11

#define LED_REG_DEC_LED1_3_SETTING				0x12
#define LED_REG_DEC_LED4_6_SETTING				0x13
#define LED_REG_DEC_GRP1_CONTROL				0x14
#define LED_REG_DEC_GRP2_CONTROL				0x15
#define LED_REG_DEC_GRP1_CURRENT_SETTING		0x16
#define LED_REG_DEC_GRP2_CURRENT_SETTING		0x17

#define LED_REG_DEC_LED1_CURRENT_SETTING		0x18
#define LED_REG_DEC_LED2_CURRENT_SETTING		0x19
#define LED_REG_DEC_LED3_CURRENT_SETTING		0x1A
#define LED_REG_DEC_LED4_CURRENT_SETTING		0x1B
#define LED_REG_DEC_LED5_CURRENT_SETTING		0x1C
#define LED_REG_DEC_LED6_CURRENT_SETTING		0x1D

#define LED_REG_DEC_MOBILE_LIGHT_LOW_SETTING	0x1E
#define LED_REG_DEC_MOBILE_LIGHT_HIGH_SETTING	0x1F

#define LED_REG_BACKLIGHT_ALLOC_INI				0x80
#define LED_REG_BACKLIGHT_CURRENT_CHANGE_INI	0x77

#define LED_REG_DEC_LED1_3_SETTING_INI			0x0F
#define LED_REG_DEC_LED1_3_SETTING_INI_VE402		0x1F
#define LED_REG_DEC_LED4_6_SETTING_INI_VE402		0x01

#define LED_REG_BACKLIGHT_CONTROL_INI			0x00
#define LED_REG_BACKLIGHT_BRIGHT_INI			0x00
#define LED_REG_RGB_CONTROL_INI					0x00
#define LED_REG_DEC_GRP1_CONTROL_INI			0x00
#define LED_REG_DEC_GRP2_CONTROL_INI			0x00
#define LED_REG_DEC__FLASH_BRIGHT_INI			0x00

#define LED_REG_RGB_CURRENT_SETTING_SIZE		0x02
#define LED_REG_DEC_MOBILE_LIGHT_SETTING_SIZE	0x02
#define LED_REG_DEC_LED3_CURRENT_SETTING_SIZE	0x02
#define LED_REG_DEC_LED5_CURRENT_SETTING_SIZE	0x02

#define LED_REG_GPIO_RESET						83
#define LED_REG_GPIO_WAIT						1


#define LED_RGB_LED_BRIGHT_RED_MAX				0x7F
#define LED_RGB_LED_BRIGHT_GREEN_MAX			100
#define LED_RGB_LED_BRIGHT_BLUE_MAX				100



#define LED_DEC_LED1_BRIGHT_MAX					19
#define LED_DEC_LED2_BRIGHT_MAX					19



#define LED_DEC_LED3_BRIGHT_MAX					0x1F
#define LED_DEC_LED4_BRIGHT_MAX					0


enum led_state_num{
	LED_STATE_STOP = 0,						
	LED_STATE_INITIALIZATION_WAIT,			
	LED_STATE_INITIALIZATION,				
	LED_STATE_IDLE,							
	LED_STATE_ENDING,						
};
enum led_hw_rev_num{
	LED_HW_REV_TR1 = 0,
	LED_HW_REV_TR2,
	LED_HW_REV_TR3,
	LED_HW_REV_TR4,
	LED_HW_REV_HA1,
	LED_HW_REV_HA2,
	LED_HW_REV_BR,
};



struct bd6082gcl_led_data {
	spinlock_t data_lock;
};

struct bd6082gcl_work {
	struct work_struct work;
};

struct bd6082gcl_reg_init{
	unsigned char adr	; 
	unsigned char wdata	; 
};

union u_led_backlight_ctrl{
	struct led_backlight_ctrl	st;
	u8							uc;
};

union u_led_main_slope_ctrl{
	struct led_main_slope_ctrl	st;
	u8							uc;
};

union u_led_rgb_ctrl{
	struct led_rgb_ctrl			st;
	u8							uc;
};

union u_led_rgb_bright{
	struct led_rgb_bright		st;
	u8							uc;
};

union u_led_led1_3_group_ctrl{
	struct led_led1_3_group_ctrl	st;
	u8							uc;
};

union u_led_rgb_cnf_ctrl{
	struct led_rgb_cnf_ctrl		st;
	u8							uc;
};

union u_led_group1_ctrl{
	struct led_group1_ctrl		st;
	u8							uc;
};

union u_led_group2_ctrl{
	struct led_group2_ctrl		st;
	u8							uc;
};

union u_led_key_bright {
	struct led_key_bright		st;
	u8							uc;
};

union u_led_indicator_bright {
	struct led_indicator_bright	st;
	u8							uc;
};

union u_led_flash_bright {
	struct led_flash_bright		st;
	u8							uc;
};

union u_led_group_ctrl {
	struct led_group1_ctrl		st1;
	struct led_group2_ctrl		st2;
	u8							uc;
};


struct led_lcd_ctrl {
	unsigned char lcd_main_backlight_exec;
	union u_led_backlight_ctrl lcd_main_backlight;
	unsigned char lcd_bright_exec;
	unsigned char lcd_bright;
	unsigned char slope_exec;
	union u_led_main_slope_ctrl slope;
};

struct led_lcd_ctrl_don {
	unsigned char lcd_main_backlight_exec;
	unsigned char lcd_main_backlight_status;
};

struct bd6082gcl_reg_tbl{
	
	enum led_hw_rev_num			hw_rev;
	
	union u_led_backlight_ctrl	backlight_control;
	
	unsigned char				lcd_bright;
	
	union u_led_rgb_ctrl		rgb_control;
	
	union u_led_group1_ctrl		dec_grp1_control;
	
	union u_led_group2_ctrl		dec_grp2_control;
	
	union u_led_flash_bright	dec_flash_bright;
	
	struct led_lcd_ctrl			lcd_res;
	
	struct led_lcd_ctrl_don		lcd_don;
};




static struct bd6082gcl_reg_tbl bd6082gcl_reg = {
	.hw_rev = LED_HW_REV_TR1,
	.backlight_control = {
		.uc = LED_REG_BACKLIGHT_CONTROL_INI,
	},
	.lcd_bright = LED_REG_BACKLIGHT_BRIGHT_INI,
	.rgb_control = {
		.uc = LED_REG_RGB_CONTROL_INI,
	},
	.dec_grp1_control = {
		.uc = LED_REG_DEC_GRP1_CONTROL_INI,
	},
	.dec_grp2_control = {
		.uc = LED_REG_DEC_GRP2_CONTROL_INI,
	},
	.dec_flash_bright ={
		.uc = LED_REG_DEC__FLASH_BRIGHT_INI,
	},
	.lcd_res = {
		.lcd_main_backlight_exec = BD6082GUL_LED_OFF,
		.lcd_bright_exec         = BD6082GUL_LED_OFF,
		.slope_exec              = BD6082GUL_LED_OFF,
	},
	.lcd_don = {
		.lcd_main_backlight_exec   = BD6082GUL_LED_OFF,
		.lcd_main_backlight_status = BD6082GUL_LED_OFF,
	},
};

static struct bd6082gcl_work *bd6082gcl_led;		
static struct i2c_client	 *bd6082gcl_client;		


static unsigned int led_starte = LED_STATE_STOP ;




int bd6082gul_i2c_smbus_write(u8 command, u8 value)
{
	s32	ret ;
	
	if( led_starte != LED_STATE_IDLE ){
		printk(KERN_WARNING
			   "BD6082GUL_LED: bd6082gul It isn't initialized.\n" );
		return BD6082GUL_LED_SET_NG;
	}
	
	
	ret = i2c_smbus_write_byte_data(bd6082gcl_client, command, value);
	
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c_smbus_write_byte_data Error %x\n", ret );
	}
	return ret;
}


int bd6082gul_i2c_smbus_write_block(u8 command, u8 length, u8 *values )
{
	s32	ret ;
	
	if( led_starte != LED_STATE_IDLE ){
		printk(KERN_WARNING
			   "BD6082GUL_LED: bd6082gul It isn't initialized.\n" );
		return BD6082GUL_LED_SET_NG;
	}
	
	
	ret = i2c_smbus_write_block_data(bd6082gcl_client, command, length, values);
	
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c_smbus_write_byte_data Error %x\n", ret );
	}
	return ret;
}

static void bd6082gul_pm_obs_a_lcdbacklight(void)
{
	
	if( bd6082gcl_reg.backlight_control.st.mleden == BD6082GUL_LED_ON ){
		pm_obs_a_lcdbacklight( bd6082gcl_reg.lcd_bright );
		printk(KERN_INFO
		   "BD6082GUL_LED: pm_obs_a_lcdbacklight( %d )\n", bd6082gcl_reg.lcd_bright );
	}
	else{
		pm_obs_a_lcdbacklight( BD6082GUL_LED_OFF );
		printk(KERN_INFO
		   "BD6082GUL_LED: pm_obs_a_lcdbacklight( %d )\n", BD6082GUL_LED_OFF );
	}
	return;
}

static void bd6082gul_pm_obs_a_keybacklight(void)
{
	
	switch( bd6082gcl_reg.hw_rev ){
	  case LED_HW_REV_HA1:
	  case LED_HW_REV_HA2:
		if( bd6082gcl_reg.dec_grp1_control.st.grp1en ==  BD6082GUL_LED_ON ){
			pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE, TRUE );	
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE(%d), TRUE(%d) )\n", PM_OBS_KEYBACKLIGHT_MODE, TRUE );
		}
		else{
			pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE, FALSE );	
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE(%d), FALSE(%d) )\n", PM_OBS_KEYBACKLIGHT_MODE, FALSE );
		}
		break;
	  default:
		if(( bd6082gcl_reg.dec_grp2_control.st.led3en == BD6082GUL_LED_ON )
		|| ( bd6082gcl_reg.dec_grp2_control.st.led4en == BD6082GUL_LED_ON )){
			pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE, TRUE );	
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE(%d), TRUE(%d) )\n", PM_OBS_KEYBACKLIGHT_MODE, TRUE );
		}
		else{
			pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE, FALSE );	
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_keybacklight( PM_OBS_KEYBACKLIGHT_MODE(%d), FALSE(%d) )\n", PM_OBS_KEYBACKLIGHT_MODE, FALSE );
		}
	}
	return;
}

static void bd6082gul_pm_obs_a_camlight(void)
{
	














	if(bd6082gcl_reg.dec_grp1_control.st.flmd == BD6082GUL_LED_OFF ){
		if( bd6082gcl_reg.dec_grp1_control.st.flleden !=  BD6082GUL_LED_OFF ){
			pm_obs_a_camlight( PM_OBS_MOBILELIGHT_MODE, TRUE );
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_camlight( PM_OBS_MOBILELIGHT_MODE(%d), %d ) \n", PM_OBS_MOBILELIGHT_MODE, TRUE );
		}
		else{
			pm_obs_a_camlight( PM_OBS_MOBILELIGHT_MODE, FALSE );
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_camlight( PM_OBS_MOBILELIGHT_MODE(%d), %d ) \n", PM_OBS_MOBILELIGHT_MODE, FALSE );
		}
	}

	else{
		if( bd6082gcl_reg.dec_grp1_control.st.flleden !=  BD6082GUL_LED_OFF ){
			pm_obs_a_camlight( PM_OBS_CAMERALIGHT_MODE, TRUE );
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_camlight( PM_OBS_CAMERALIGHT_MODE(%d), %d ) \n", PM_OBS_CAMERALIGHT_MODE, TRUE );
		}
		else{
			pm_obs_a_camlight( PM_OBS_CAMERALIGHT_MODE, FALSE );
			printk(KERN_INFO
				   "BD6082GUL_LED: pm_obs_a_camlight( PM_OBS_CAMERALIGHT_MODE(%d), %d ) \n", PM_OBS_CAMERALIGHT_MODE, FALSE );
		}
	}
	return;
}


int bd6082gul_main_lcd_set(struct led_backlight_ctrl *request)
{
	int	ret;
	u8	rw_adr = LED_REG_BACKLIGHT_CONTROL ;
	union u_led_backlight_ctrl	rw_data;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	spin_lock(&spin_lock_status);
	
	if( bd6082gcl_reg.lcd_don.lcd_main_backlight_exec == BD6082GUL_LED_ON ){
		request->mleden = bd6082gcl_reg.lcd_don.lcd_main_backlight_status;
	}
	
	rw_data.st.dmy1 = 0 ;
	rw_data.st.dmy2 = 0 ;



	rw_data.st.sleden = bd6082gcl_reg.backlight_control.st.sleden ;
	
	rw_data.st.mleden = request->mleden ;

	rw_data.st.wpwmen = request->wpwmen ;

	spin_unlock(&spin_lock_status);
	
	if( led_starte == LED_STATE_IDLE ){
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		
		spin_lock(&spin_lock_status);
		bd6082gcl_reg.backlight_control.st.mleden = request->mleden ;
		spin_unlock(&spin_lock_status);
		
		
		bd6082gul_pm_obs_a_lcdbacklight();
		
		return BD6082GUL_LED_SET_OK;
	}
	else if( led_starte < LED_STATE_IDLE ){
		spin_lock(&spin_lock_status);
		bd6082gcl_reg.lcd_res.lcd_main_backlight.uc = rw_data.uc ;
		bd6082gcl_reg.lcd_res.lcd_main_backlight_exec = BD6082GUL_LED_ON ;
		spin_unlock(&spin_lock_status);
		printk(KERN_INFO
			   "BD6082GUL_LED: lcd_set Reserved\n" );
		
		return BD6082GUL_LED_SET_RESERVED;
	}
	else{
		printk(KERN_WARNING
			   "BD6082GUL_LED: bd6082gul status Error %d\n" , led_starte );
		return BD6082GUL_LED_SET_NG;
	}
}
EXPORT_SYMBOL(bd6082gul_main_lcd_set);


int bd6082gul_main_lcd_bright (unsigned char lcd_bright)
{
	int	ret;
	u8	rw_adr = LED_REG_BACKLIGHT_MAIN_CURRENT;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	if( bd6082gcl_reg.lcd_don.lcd_main_backlight_exec == BD6082GUL_LED_ON ){
		lcd_bright = 0x63;
	}
	
	if( led_starte == LED_STATE_IDLE ){
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, (u8)lcd_bright);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		
		spin_lock(&spin_lock_status);
		bd6082gcl_reg.lcd_bright = lcd_bright ;
		spin_unlock(&spin_lock_status);
		
		
		bd6082gul_pm_obs_a_lcdbacklight();
		
		return BD6082GUL_LED_SET_OK;
	}
	else if( led_starte < LED_STATE_IDLE ){
		spin_lock(&spin_lock_status);
		bd6082gcl_reg.lcd_res.lcd_bright = lcd_bright ;
		bd6082gcl_reg.lcd_res.lcd_bright_exec = BD6082GUL_LED_ON ;
		spin_unlock(&spin_lock_status);
		printk(KERN_INFO
			   "BD6082GUL_LED: lcd_bright Reserved\n" );
		
		return BD6082GUL_LED_SET_RESERVED;
	}
	else{
		printk(KERN_WARNING
			   "BD6082GUL_LED: bd6082gul status Error %d\n" , led_starte );
		return BD6082GUL_LED_SET_NG;
	}
}
EXPORT_SYMBOL(bd6082gul_main_lcd_bright);


int bd6082gul_main_lcd_slope (struct led_main_slope_ctrl *slope)
{
	int	ret;
	u8	rw_adr = LED_REG_BACKLIGHT_CURRENT_CHANGE;
	union u_led_main_slope_ctrl	rw_data;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	rw_data.st.dmy1 = 0 ;
	rw_data.st.dmy2 = 0 ;
	
	rw_data.st.thl = slope->thl ;
	rw_data.st.tlh = slope->tlh ;
	
	if( led_starte == LED_STATE_IDLE ){
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		
		return BD6082GUL_LED_SET_OK;
	}
	else if( led_starte < LED_STATE_IDLE ){
		spin_lock(&spin_lock_status);
		bd6082gcl_reg.lcd_res.slope.uc = rw_data.uc ;
		bd6082gcl_reg.lcd_res.slope_exec = BD6082GUL_LED_ON ;
		spin_unlock(&spin_lock_status);
		printk(KERN_INFO
			   "BD6082GUL_LED: lcd_slope Reserved\n" );
		
		return BD6082GUL_LED_SET_RESERVED;
	}
	else{
		printk(KERN_WARNING
			   "BD6082GUL_LED: bd6082gul status Error %d\n" , led_starte );
		return BD6082GUL_LED_SET_NG;
	}
}
EXPORT_SYMBOL(bd6082gul_main_lcd_slope);


int bd6082gul_sub_lcd_set(struct led_backlight_ctrl *request)
{
	int	ret;
	u8	rw_adr = LED_REG_BACKLIGHT_CONTROL;
	union u_led_backlight_ctrl	rw_data;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	spin_lock(&spin_lock_status);
	rw_data.st.dmy1 = 0 ;
	rw_data.st.dmy2 = 0 ;
	rw_data.st.wpwmen = bd6082gcl_reg.backlight_control.st.wpwmen ;
	rw_data.st.mleden = bd6082gcl_reg.backlight_control.st.mleden ;
	
	rw_data.st.sleden = request->sleden ;
	spin_unlock(&spin_lock_status);
	
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	spin_lock(&spin_lock_status);
	bd6082gcl_reg.backlight_control.st.sleden = request->sleden ;
	spin_unlock(&spin_lock_status);
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_sub_lcd_set);


int bd6082gul_sub_lcd_bright (unsigned char lcd_bright)
{
	int	ret;
	u8	rw_adr = LED_REG_BACKLIGHT_SUB_CURRENT ;
	
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, (u8)lcd_bright);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_sub_lcd_bright);


int bd6082gul_rgb_led_set(struct led_rgb_ctrl *request)
{
	int	ret;
	u8	rw_adr = LED_REG_RGB_CONTROL ;
	union u_led_rgb_ctrl	rw_data;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	spin_lock(&spin_lock_status);
	rw_data.st.dmy1 = 0 ;
	rw_data.st.rgb1eml = bd6082gcl_reg.rgb_control.st.rgb1eml ;

	
	rw_data.st.rgb1os = request->rgb1os ;
	rw_data.st.rgb1en = request->rgb1en ;
	spin_unlock(&spin_lock_status);
	
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	spin_lock(&spin_lock_status);
	bd6082gcl_reg.rgb_control.st.rgb1en = request->rgb1en ;
	spin_unlock(&spin_lock_status);
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_rgb_led_set);


int bd6082gul_rgb_led_bright(struct led_rgb_bright *red_bright,
							 struct led_rgb_bright *green_bright,
							 struct led_rgb_bright *blue_bright)
{
	int	ret;
	u8	rw_adr;
	union u_led_rgb_bright	rw_data[LED_REG_RGB_CURRENT_SETTING_SIZE];
	
	if( red_bright->set_flag == BD6082GUL_LED_ON ){

		if( red_bright->bright > LED_RGB_LED_BRIGHT_RED_MAX ){
			red_bright->bright = LED_RGB_LED_BRIGHT_RED_MAX;
		}

		rw_adr = LED_REG_RGB_R1_CURRENT_SETTING ;
		rw_data[0].st.set_flag = 0 ;
		rw_data[0].st.bright = red_bright->bright ;
		rw_data[1].uc = rw_data[0].uc ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[0].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}










	}
	if( green_bright->set_flag == BD6082GUL_LED_ON ){

		if( green_bright->bright > LED_RGB_LED_BRIGHT_GREEN_MAX ){
			green_bright->bright = LED_RGB_LED_BRIGHT_GREEN_MAX;
		}

		rw_adr = LED_REG_RGB_G1_CURRENT_SETTING ;
		rw_data[0].st.set_flag = 0 ;
		rw_data[0].st.bright = green_bright->bright ;
		rw_data[1].uc = rw_data[0].uc ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[0].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}










	}
	if( blue_bright->set_flag == BD6082GUL_LED_ON ){

		if( blue_bright->bright > LED_RGB_LED_BRIGHT_BLUE_MAX ){
			blue_bright->bright = LED_RGB_LED_BRIGHT_BLUE_MAX;
		}

		rw_adr = LED_REG_RGB_B1_CURRENT_SETTING ;
		rw_data[0].st.set_flag = 0 ;
		rw_data[0].st.bright = blue_bright->bright ;
		rw_data[1].uc = rw_data[0].uc ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[0].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}










	}
	
	return BD6082GUL_LED_SET_OK;	
}
EXPORT_SYMBOL(bd6082gul_rgb_led_bright);


int bd6082gul_rgb_led_cnf(struct led_rgb_cnf_ctrl *request)
{
	int	ret;
	u8	rw_adr = LED_REG_RGB_TIME_SETTING ;
	union u_led_rgb_cnf_ctrl rw_data ;
	
	rw_data.st.sfrgb = request->sfrgb ;
	rw_data.st.srrgb = request->srrgb ;
	rw_data.st.VE317  = request->VE317 ;
	rw_data.st.dmy1  = 0 ;
	
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_rgb_led_cnf);


int bd6082gul_rgb_led_patern(unsigned char red_patern,
							 unsigned char green_patern,
							 unsigned char blue_patern)
{
	int	ret;
	u8	rw_adr;
	
	rw_adr = LED_REG_RGB_R1_CORRUGATION_PATTERN_SETTING ;
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, (u8)red_patern);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	rw_adr = LED_REG_RGB_G1_CORRUGATION_PATTERN_SETTING ;
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, (u8)green_patern);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	

	rw_adr = LED_REG_RGB_B1_CORRUGATION_PATTERN_SETTING ;
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, (u8)blue_patern);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}

	
	return BD6082GUL_LED_SET_OK;	
}
EXPORT_SYMBOL(bd6082gul_rgb_led_patern);


int bd6082gul_flash_led_set(struct led_group1_ctrl *request)
{
	int	ret;
	u8	rw_adr = LED_REG_DEC_GRP1_CONTROL ;
	union u_led_group1_ctrl	rw_data;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	spin_lock(&spin_lock_status);
	rw_data.st.dmy1 = 0 ;
	rw_data.st.grp1en = bd6082gcl_reg.dec_grp1_control.st.grp1en ;
	rw_data.st.grp2en = bd6082gcl_reg.dec_grp1_control.st.grp2en ;
	
	rw_data.st.flleden = request->flleden ;
    rw_data.st.flmd = request->flmd ;
	spin_unlock(&spin_lock_status);
	
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	spin_lock(&spin_lock_status);
	bd6082gcl_reg.dec_grp1_control.st.flleden = request->flleden ;
    bd6082gcl_reg.dec_grp1_control.st.flmd = request->flmd ;
	spin_unlock(&spin_lock_status);
	
	
	bd6082gul_pm_obs_a_camlight();
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_flash_led_set);


int bd6082gul_flash_led_bright(struct led_flash_bright *led_low_bright,
							   struct led_flash_bright *led_high_bright)
{
	int	ret;
	u8	rw_adr ;
	union u_led_flash_bright	rw_data[LED_REG_DEC_MOBILE_LIGHT_SETTING_SIZE];
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	rw_data[0].st.bright = led_low_bright->bright ;
	rw_data[0].st.set_flag = 0 ;
	rw_data[0].st.dmy1 = 0 ;
	rw_data[1].st.bright = led_high_bright->bright ;
	rw_data[1].st.set_flag = 0 ;
	rw_data[1].st.dmy1 = 0 ;
	
	if( led_low_bright->set_flag == BD6082GUL_LED_ON ){

		if( rw_data[0].st.bright > LED_DEC_LED1_BRIGHT_MAX ){
			rw_data[0].st.bright = LED_DEC_LED1_BRIGHT_MAX;
		}

		rw_adr = LED_REG_DEC_MOBILE_LIGHT_LOW_SETTING ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[0].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		
		spin_lock(&spin_lock_status);
    	bd6082gcl_reg.dec_flash_bright.uc = rw_data[0].uc;
		spin_unlock(&spin_lock_status);
	}
	if( led_high_bright->set_flag == BD6082GUL_LED_ON ){

		if( rw_data[1].st.bright > LED_DEC_LED2_BRIGHT_MAX ){
			rw_data[1].st.bright = LED_DEC_LED2_BRIGHT_MAX;
		}

		rw_adr = LED_REG_DEC_MOBILE_LIGHT_HIGH_SETTING ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[1].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		
		spin_lock(&spin_lock_status);
    	bd6082gcl_reg.dec_flash_bright.uc = rw_data[1].uc;
		spin_unlock(&spin_lock_status);
	}
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_flash_led_bright);


int bd6082gul_indicator_led_set(struct led_group2_ctrl *request)
{
	int	ret;
	u8	rw_adr = LED_REG_DEC_GRP2_CONTROL ;
	union u_led_group2_ctrl	rw_data;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	spin_lock(&spin_lock_status);
	rw_data.st.dmy1 = 0 ;
	rw_data.st.led4en = bd6082gcl_reg.dec_grp2_control.st.led4en ;
	rw_data.st.led3en = bd6082gcl_reg.dec_grp2_control.st.led3en ;
	rw_data.st.led2en = bd6082gcl_reg.dec_grp2_control.st.led2en ;
	rw_data.st.led1en = bd6082gcl_reg.dec_grp2_control.st.led1en ;
	
	rw_data.st.led6en = request->led6en ;
	rw_data.st.led5en = request->led5en ;
	spin_unlock(&spin_lock_status);
	
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	spin_lock(&spin_lock_status);
	bd6082gcl_reg.dec_grp2_control.st.led6en = request->led6en ;
	bd6082gcl_reg.dec_grp2_control.st.led5en = request->led5en ;
	spin_unlock(&spin_lock_status);
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_indicator_led_set);


int bd6082gul_indicator_led_bright(struct led_indicator_bright *led_ind_red_bright,
								   struct led_indicator_bright *led_ind_green_bright)
{
	int	ret;
    u8    rw_adr ;
	union u_led_indicator_bright rw_data[LED_REG_DEC_LED5_CURRENT_SETTING_SIZE];
	
	rw_data[0].st.bright = led_ind_green_bright->bright ;
	rw_data[0].st.set_flag = 0 ;
	rw_data[0].st.dmy1 = 0 ;
	rw_data[1].st.bright = led_ind_red_bright->bright ;
	rw_data[1].st.set_flag = 0 ;
	rw_data[1].st.dmy1 = 0 ;
	
    if( led_ind_green_bright->set_flag == BD6082GUL_LED_ON ){
        rw_adr = LED_REG_DEC_LED5_CURRENT_SETTING ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[0].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
	}
    if( led_ind_red_bright->set_flag == BD6082GUL_LED_ON ){
        rw_adr = LED_REG_DEC_LED6_CURRENT_SETTING ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[1].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
	}
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_indicator_led_bright);


int bd6082gul_key_led_set(struct led_group2_ctrl *request)
{
	int	ret = BD6082GUL_LED_OFF ;
	u8	rw_adr;
	union u_led_group_ctrl	rw_data;
	
	
	spinlock_t	spin_lock_flag = SPIN_LOCK_UNLOCKED;

	switch( bd6082gcl_reg.hw_rev ){
	  case LED_HW_REV_HA1:
	  case LED_HW_REV_HA2:
		rw_adr = LED_REG_DEC_GRP1_CONTROL ;
		spin_lock(&spin_lock_flag);
		rw_data.st1.dmy1 = 0 ;
		rw_data.st1.flleden = bd6082gcl_reg.dec_grp1_control.st.flleden ;
	    rw_data.st1.flmd = bd6082gcl_reg.dec_grp1_control.st.flmd ;
		rw_data.st1.grp2en = bd6082gcl_reg.dec_grp1_control.st.grp2en ;
		
		rw_data.st1.grp1en = request->led3en ;
		spin_unlock(&spin_lock_flag);
		
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		
		spin_lock(&spin_lock_flag);
		bd6082gcl_reg.dec_grp1_control.st.grp1en = request->led3en ;
		spin_unlock(&spin_lock_flag);
		break;
	  default:
		rw_adr = LED_REG_DEC_GRP2_CONTROL ;
		spin_lock(&spin_lock_flag);
		rw_data.st2.dmy1 = 0 ;
		rw_data.st2.led6en = bd6082gcl_reg.dec_grp2_control.st.led6en ;
		rw_data.st2.led5en = bd6082gcl_reg.dec_grp2_control.st.led5en ;
		rw_data.st2.led2en = bd6082gcl_reg.dec_grp2_control.st.led2en ;
		rw_data.st2.led1en = bd6082gcl_reg.dec_grp2_control.st.led1en ;
		
		rw_data.st2.led4en = request->led4en ;
		rw_data.st2.led3en = request->led3en ;
		if(( bd6082gcl_reg.dec_grp2_control.st.led4en == request->led4en )
		&& ( bd6082gcl_reg.dec_grp2_control.st.led3en == request->led3en )){
			ret = BD6082GUL_LED_ON ;
		}
		spin_unlock(&spin_lock_flag);
		if( ret == BD6082GUL_LED_ON ){
			return BD6082GUL_LED_SET_OK;
		}
		
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		
		spin_lock(&spin_lock_flag);
		bd6082gcl_reg.dec_grp2_control.st.led4en = request->led4en ;
		bd6082gcl_reg.dec_grp2_control.st.led3en = request->led3en ;
		spin_unlock(&spin_lock_flag);
		break;
	}

	
	bd6082gul_pm_obs_a_keybacklight();
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_key_led_set);


int bd6082gul_key_led_bright (struct led_key_bright *led_key_bright1,
							  struct led_key_bright *led_key_bright2)
{
	int	ret;
	u8	rw_adr ;
	union u_led_key_bright	rw_data[LED_REG_DEC_LED3_CURRENT_SETTING_SIZE];
	
	rw_data[0].st.bright = led_key_bright1->bright ;
	rw_data[0].st.set_flag = 0 ;
	rw_data[0].st.dmy1 = 0 ;
	rw_data[1].st.bright = led_key_bright2->bright ;
	rw_data[1].st.set_flag = 0 ;
	rw_data[1].st.dmy1 = 0 ;
	
	if( led_key_bright1->set_flag == BD6082GUL_LED_ON ){

		if( rw_data[0].st.bright > LED_DEC_LED3_BRIGHT_MAX ){
			rw_data[0].st.bright = LED_DEC_LED3_BRIGHT_MAX;
		}

		switch( bd6082gcl_reg.hw_rev ){
		  case LED_HW_REV_HA1:
		  case LED_HW_REV_HA2:
			rw_adr = LED_REG_DEC_GRP1_CURRENT_SETTING ;
			break;
		  default:
			rw_adr = LED_REG_DEC_LED3_CURRENT_SETTING ;
			break;
		}
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[0].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
	}
	 if( led_key_bright2->set_flag == BD6082GUL_LED_ON ){

		if( rw_data[1].st.bright > LED_DEC_LED4_BRIGHT_MAX ){
			rw_data[1].st.bright = LED_DEC_LED4_BRIGHT_MAX;
		}

		rw_adr = LED_REG_DEC_LED4_CURRENT_SETTING ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data[1].uc);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
	}
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_key_led_bright);


int bd6082gul_reg_write(unsigned char sub2,
						unsigned char inf1)
{
	int	ret;
	
	ret = bd6082gul_i2c_smbus_write(sub2, (u8)inf1);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", sub2, ret );
        return BD6082GUL_LED_REG_WRITE_NG;
	}
    return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_reg_write);

int bd6082gul_dec_led1_3_setting(struct led_led1_3_group_ctrl *request )
{
	int	ret = BD6082GUL_LED_OFF ;
	u8	rw_adr = LED_REG_DEC_LED1_3_SETTING ;
	union u_led_led1_3_group_ctrl	rw_data;
	
	switch( bd6082gcl_reg.hw_rev ){
	  case LED_HW_REV_HA1:
	  case LED_HW_REV_HA2:
		rw_data.uc = LED_REG_DEC_LED1_3_SETTING_INI_VE402 ;
		break;
	  default:
		rw_data.uc = LED_REG_DEC_LED1_3_SETTING_INI ;
		break;
	}
	rw_data.st.led2md = request->led2md;
	
	
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data.uc);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	
	return BD6082GUL_LED_SET_OK;
}
EXPORT_SYMBOL(bd6082gul_dec_led1_3_setting);

int bd6082gul_main_lcd_don(unsigned char sub2)
{
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	struct led_backlight_ctrl request;
	int	ret;
	
	spin_lock(&spin_lock_status);
	bd6082gcl_reg.lcd_don.lcd_main_backlight_exec   = BD6082GUL_LED_ON;
	bd6082gcl_reg.lcd_don.lcd_main_backlight_status = sub2;
	spin_unlock(&spin_lock_status);
	
	ret = bd6082gul_main_lcd_bright(0x63);
	if( ret != BD6082GUL_LED_SET_OK ){
		return ret ;
	}
	
	memset(&request, 0, sizeof(request));
	request.mleden = bd6082gcl_reg.lcd_don.lcd_main_backlight_status;
	ret = bd6082gul_main_lcd_set(&request);
	
	return ret ;
}
EXPORT_SYMBOL(bd6082gul_main_lcd_don);


static void bd6082gcl_init_client_hw_rev(void)
{




	uint32_t ret;
	
	ret = hw_revision_read ();
	if( ret == HW_REVISION_READ_ERR ){
		printk(KERN_WARNING
			   "BD6082GUL_LED: hw_revision_read retcode Error %x \n", ret );
		return ;
	}
	printk(KERN_INFO
		   "BD6082GUL_LED: hw_revision_read retcode %08x \n", ret );
	if( ret < HW_REV_VE358 ){
		if( ret == HW_REV_0P1 ){
			bd6082gcl_reg.hw_rev = LED_HW_REV_TR1;
		}
		else if( ret == HW_REV_0P2 ){
			bd6082gcl_reg.hw_rev = LED_HW_REV_TR2;
		}
		else if( ret == HW_REV_0P3 ){
			bd6082gcl_reg.hw_rev = LED_HW_REV_TR3;
		}
		else if( ret == HW_REV_0P4 ){
			bd6082gcl_reg.hw_rev = LED_HW_REV_TR4;
		}
		else{
			bd6082gcl_reg.hw_rev = LED_HW_REV_TR4;
		}
	}
	else if( ret < HW_REV_2P0 ){
		if( ret == HW_REV_VE358 ){
			bd6082gcl_reg.hw_rev = LED_HW_REV_HA1;
		}
		else if( ret == HW_REV_1P1 ){
			bd6082gcl_reg.hw_rev = LED_HW_REV_HA2;
		}
		else{
			bd6082gcl_reg.hw_rev = LED_HW_REV_HA2;
		}
	}
	else{
		bd6082gcl_reg.hw_rev = LED_HW_REV_HA2;
		printk(KERN_WARNING
			   "BD6082GUL_LED: hw_revision_read range Error %x \n", ret );
	}

}


static int bd6082gcl_init_client(struct i2c_client *client)
{
	int	ret ;
	u8	rw_adr ;
	u8	rw_data ;
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	
	rw_adr = LED_REG_BACKLIGHT_ALLOC;
	rw_data = LED_REG_BACKLIGHT_ALLOC_INI ;
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	rw_adr = LED_REG_DEC_LED1_3_SETTING;
	switch( bd6082gcl_reg.hw_rev ){
	  case LED_HW_REV_HA1:
	  case LED_HW_REV_HA2:
		rw_data = LED_REG_DEC_LED1_3_SETTING_INI_VE402 ;
		break;
	  default:
		rw_data = LED_REG_DEC_LED1_3_SETTING_INI ;
		break;
	}
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	switch( bd6082gcl_reg.hw_rev ){
	  case LED_HW_REV_HA1:
	  case LED_HW_REV_HA2:
		rw_adr = LED_REG_DEC_LED4_6_SETTING;
		rw_data = LED_REG_DEC_LED4_6_SETTING_INI_VE402 ;
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		break;
	  default:
		break;
	}
	
	rw_adr = LED_REG_BACKLIGHT_CURRENT_CHANGE;
	rw_data = LED_REG_BACKLIGHT_CURRENT_CHANGE_INI ;
	ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data);
	if(ret < 0){
		printk(KERN_WARNING
			   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
		return BD6082GUL_LED_SET_NG;
	}
	
	if( bd6082gcl_reg.lcd_res.slope_exec == BD6082GUL_LED_ON ){
		
		rw_adr = LED_REG_BACKLIGHT_CURRENT_CHANGE;
		rw_data = bd6082gcl_reg.lcd_res.slope.uc ;
		bd6082gcl_reg.lcd_res.slope_exec = BD6082GUL_LED_OFF ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
	}
	
	if(bd6082gcl_reg.lcd_res.lcd_bright_exec == BD6082GUL_LED_ON){
		
		rw_adr = LED_REG_BACKLIGHT_MAIN_CURRENT;
		rw_data = bd6082gcl_reg.lcd_res.lcd_bright ;
		bd6082gcl_reg.lcd_res.lcd_bright_exec = BD6082GUL_LED_OFF ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		spin_lock(&spin_lock_status);
		bd6082gcl_reg.lcd_bright = rw_data ;
		spin_unlock(&spin_lock_status);
	}
	
	if(bd6082gcl_reg.lcd_res.lcd_main_backlight_exec == BD6082GUL_LED_ON){
		
		rw_adr = LED_REG_BACKLIGHT_CONTROL;
		rw_data = bd6082gcl_reg.lcd_res.lcd_main_backlight.uc ;
		bd6082gcl_reg.lcd_res.lcd_main_backlight_exec = BD6082GUL_LED_OFF ;
		
		ret = bd6082gul_i2c_smbus_write(rw_adr, rw_data);
		if(ret < 0){
			printk(KERN_WARNING
				   "BD6082GUL_LED: i2c Write Reg %x Error %x \n", rw_adr, ret );
			return BD6082GUL_LED_SET_NG;
		}
		spin_lock(&spin_lock_status);
		bd6082gcl_reg.backlight_control.uc = rw_data ;
		spin_unlock(&spin_lock_status);
	}
	
	bd6082gul_pm_obs_a_lcdbacklight();
	
	
	bd6082gul_pm_obs_a_keybacklight();
	
	
	bd6082gul_pm_obs_a_camlight();
	
	
	return BD6082GUL_LED_SET_OK;
}

static int bd6082gcl_init_client_data( void )
{
	spinlock_t	spin_lock_status = SPIN_LOCK_UNLOCKED;
	
	
	spin_lock(&spin_lock_status);
	
	bd6082gcl_reg.backlight_control.uc = LED_REG_BACKLIGHT_CONTROL_INI ;
	
	bd6082gcl_reg.lcd_bright = LED_REG_BACKLIGHT_BRIGHT_INI,
	
	bd6082gcl_reg.rgb_control.uc = LED_REG_RGB_CONTROL_INI ;
	
	bd6082gcl_reg.dec_grp1_control.uc = LED_REG_DEC_GRP1_CONTROL_INI ;
	
	bd6082gcl_reg.dec_grp2_control.uc = LED_REG_DEC_GRP2_CONTROL_INI ;
	
	
	bd6082gcl_reg.lcd_res.lcd_main_backlight_exec = BD6082GUL_LED_OFF ;
	bd6082gcl_reg.lcd_res.lcd_bright_exec = BD6082GUL_LED_OFF ;
	bd6082gcl_reg.lcd_res.slope_exec = BD6082GUL_LED_OFF ;
	spin_unlock(&spin_lock_status);
	
	
	return BD6082GUL_LED_SET_OK;
}


static int bd6082gcl_i2c_probe(struct i2c_client *client,
							   const struct i2c_device_id *id)
{
	int rc = 0;
	led_starte = LED_STATE_INITIALIZATION;
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		rc = -ENOTSUPP;
		goto probe_failure;
	}
	
	bd6082gcl_led =
		kzalloc(sizeof(struct bd6082gcl_work), GFP_KERNEL);
	
	if (!bd6082gcl_led) {
		rc = -ENOMEM;
		goto probe_failure;
	}
	gpio_set_value(LED_REG_GPIO_RESET, BD6082GUL_LED_ON);
	mdelay(LED_REG_GPIO_WAIT);
	
	bd6082gcl_client = client;			
	i2c_set_clientdata(client, bd6082gcl_led);
	bd6082gcl_init_client_hw_rev();
	led_starte = LED_STATE_IDLE;
	bd6082gcl_init_client(client);
	printk(KERN_INFO
		   "BD6082GUL_LED: bd6082gcl_probe succeeded!\n" );
	return 0;
	
probe_failure:
	led_starte = LED_STATE_ENDING;
	printk(KERN_WARNING
		   "BD6082GUL_LED: bd6082gcl_probe failed!\n" );
	return rc;
}


static int bd6082gcl_i2c_remove(struct i2c_client *client)
{
	gpio_set_value(LED_REG_GPIO_RESET, BD6082GUL_LED_OFF);
	kfree(i2c_get_clientdata(client));
	bd6082gcl_led = NULL;
	return 0;
}

static const struct i2c_device_id bd6082gcl_i2c_id[] = {
	{ "msm_led_bd6082gcl", 0},
	{ },
};

static struct i2c_driver msm_led_bd6082gcl_driver = {
	.id_table = bd6082gcl_i2c_id,
	.probe	  = bd6082gcl_i2c_probe,
	.remove	  = bd6082gcl_i2c_remove,
	
	.driver = {
			.name = "msm_led_bd6082gcl",
			.owner = THIS_MODULE,
	},
};

static int __init bd6082gcl_led_init(void)
{
	led_starte = LED_STATE_INITIALIZATION_WAIT;
	return i2c_add_driver(&msm_led_bd6082gcl_driver);
}

static void __exit bd6082gcl_led_exit(void)
{
	led_starte = LED_STATE_ENDING;
	i2c_del_driver(&msm_led_bd6082gcl_driver); 
	bd6082gcl_init_client_data() ;
}

module_init(bd6082gcl_led_init);
module_exit(bd6082gcl_led_exit);


