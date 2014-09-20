/*
 * This software program is licensed subject to the GNU General Public License
 * (GPL).Version 2,June 1991, available at http://www.fsf.org/copyleft/gpl.html

 * (C) Copyright 2011 Bosch Sensortec GmbH
 * All Rights Reserved
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/


 








#ifndef __SMB380_H__
#define __SMB380_H__





























#define SMB380_WR_FUNC_PTR int (* bus_write)(unsigned char, unsigned char *, unsigned char)




















#define SMB380_BUS_WRITE_FUNC(dev_addr, reg_addr, reg_data, wr_len)\
           bus_write(reg_addr, reg_data, wr_len)


















#define SMB380_SPI_RD_MASK 0x80   



#define SMB380_RD_FUNC_PTR int (* bus_read)( unsigned char, unsigned char *, unsigned char)




















#define SMB380_BUS_READ_FUNC(dev_addr, reg_addr, reg_data, r_len)\
           bus_read(reg_addr | SMB380_SPI_RD_MASK, reg_data, r_len)










#define SMB380_I2C_ADDR		0x38






#define E_SMB_NULL_PTR		(char)-127
#define E_COMM_RES		    (char)-1
#define E_OUT_OF_RANGE		(char)-2









#define SMB380_EEP_OFFSET   0x20
#define SMB380_IMAGE_BASE	0x0b
#define SMB380_IMAGE_LEN	19

#define SMB380_CHIP_ID_REG			0x00
#define SMB380_VERSION_REG			0x01
#define SMB380_X_AXIS_LSB_REG		0x02
#define SMB380_X_AXIS_MSB_REG		0x03
#define SMB380_Y_AXIS_LSB_REG		0x04
#define SMB380_Y_AXIS_MSB_REG		0x05
#define SMB380_Z_AXIS_LSB_REG		0x06
#define SMB380_Z_AXIS_MSB_REG		0x07
#define SMB380_TEMP_RD_REG			0x08
#define SMB380_STATUS_REG	0x09
#define SMB380_CTRL_REG		0x0a
#define SMB380_CONF1_REG	0x0b
#define SMB380_LG_THRESHOLD_REG	0x0c
#define SMB380_LG_DURATION_REG		0x0d
#define SMB380_HG_THRESHOLD_REG	0x0e
#define SMB380_HG_DURATION_REG		0x0f
#define SMB380_MOTION_THRS_REG		0x10
#define SMB380_HYSTERESIS_REG		0x11
#define SMB380_CUSTOMER1_REG		0x12
#define SMB380_CUSTOMER2_REG		0x13
#define SMB380_RANGE_BWIDTH_REG	0x14
#define SMB380_CONF2_REG	0x15

#define SMB380_OFFS_GAIN_X_REG		0x16
#define SMB380_OFFS_GAIN_Y_REG		0x17
#define SMB380_OFFS_GAIN_Z_REG		0x18
#define SMB380_OFFS_GAIN_T_REG		0x19
#define SMB380_OFFSET_X_REG		0x1a
#define SMB380_OFFSET_Y_REG		0x1b
#define SMB380_OFFSET_Z_REG		0x1c
#define SMB380_OFFSET_T_REG		0x1d




#define SMB380_MDELAY_DATA_TYPE	unsigned int
#define SMB380_EE_W_DELAY 28	








typedef struct  {
		short x, 
			  y, 
			  z; 
} smb380acc_t;







typedef struct  {
		unsigned char	
		smb380_conf1 ,  
		lg_threshold,	
		lg_duration,	
		hg_threshold,	
		hg_duration,	
		motion_thrs,	
		hysteresis,		
		customer1,		
		customer2,		
		range_bwidth,	
		smb380_conf2,	
		offs_gain_x,	
		offs_gain_y,	
		offs_gain_z,	
		offs_gain_t,	
		offset_x,		
		offset_y,		 
		offset_z,		 
		offset_t;		 
} smb380regs_t;






typedef struct {	
	smb380regs_t * image;	
	unsigned char mode;		
	unsigned char chip_id,	
				  ml_version, 	
				  al_version; 
	unsigned char dev_addr;   
	unsigned char int_mask;	  
	SMB380_WR_FUNC_PTR;		  
	SMB380_RD_FUNC_PTR;		  
	void (*delay_msec)( SMB380_MDELAY_DATA_TYPE ); 
} smb380_t;




	








#define SMB380_CHIP_ID__POS		0
#define SMB380_CHIP_ID__MSK		0x07
#define SMB380_CHIP_ID__LEN		3
#define SMB380_CHIP_ID__REG		SMB380_CHIP_ID_REG


#define SMB380_ML_VERSION__POS		0
#define SMB380_ML_VERSION__LEN		4
#define SMB380_ML_VERSION__MSK		0x0F
#define SMB380_ML_VERSION__REG		SMB380_VERSION_REG



#define SMB380_AL_VERSION__POS  	4
#define SMB380_AL_VERSION__LEN  	4
#define SMB380_AL_VERSION__MSK		0xF0
#define SMB380_AL_VERSION__REG		SMB380_VERSION_REG





#define SMB380_NEW_DATA_X__POS  	0
#define SMB380_NEW_DATA_X__LEN  	1
#define SMB380_NEW_DATA_X__MSK  	0x01
#define SMB380_NEW_DATA_X__REG		SMB380_X_AXIS_LSB_REG

#define SMB380_ACC_X_LSB__POS   	6
#define SMB380_ACC_X_LSB__LEN   	2
#define SMB380_ACC_X_LSB__MSK		0xC0
#define SMB380_ACC_X_LSB__REG		SMB380_X_AXIS_LSB_REG

#define SMB380_ACC_X_MSB__POS   	0
#define SMB380_ACC_X_MSB__LEN   	8
#define SMB380_ACC_X_MSB__MSK		0xFF
#define SMB380_ACC_X_MSB__REG		SMB380_X_AXIS_MSB_REG

#define SMB380_NEW_DATA_Y__POS  	0
#define SMB380_NEW_DATA_Y__LEN  	1
#define SMB380_NEW_DATA_Y__MSK  	0x01
#define SMB380_NEW_DATA_Y__REG		SMB380_Y_AXIS_LSB_REG

#define SMB380_ACC_Y_LSB__POS   	6
#define SMB380_ACC_Y_LSB__LEN   	2
#define SMB380_ACC_Y_LSB__MSK   	0xC0
#define SMB380_ACC_Y_LSB__REG		SMB380_Y_AXIS_LSB_REG

#define SMB380_ACC_Y_MSB__POS   	0
#define SMB380_ACC_Y_MSB__LEN   	8
#define SMB380_ACC_Y_MSB__MSK   	0xFF
#define SMB380_ACC_Y_MSB__REG		SMB380_Y_AXIS_MSB_REG

#define SMB380_NEW_DATA_Z__POS  	0
#define SMB380_NEW_DATA_Z__LEN  	1
#define SMB380_NEW_DATA_Z__MSK		0x01
#define SMB380_NEW_DATA_Z__REG		SMB380_Z_AXIS_LSB_REG

#define SMB380_ACC_Z_LSB__POS   	6
#define SMB380_ACC_Z_LSB__LEN   	2
#define SMB380_ACC_Z_LSB__MSK		0xC0
#define SMB380_ACC_Z_LSB__REG		SMB380_Z_AXIS_LSB_REG

#define SMB380_ACC_Z_MSB__POS   	0
#define SMB380_ACC_Z_MSB__LEN   	8
#define SMB380_ACC_Z_MSB__MSK		0xFF
#define SMB380_ACC_Z_MSB__REG		SMB380_Z_AXIS_MSB_REG

#define SMB380_TEMPERATURE__POS 	0
#define SMB380_TEMPERATURE__LEN 	8
#define SMB380_TEMPERATURE__MSK 	0xFF
#define SMB380_TEMPERATURE__REG		SMB380_TEMP_RD_REG






#define SMB380_STATUS_HG__POS		0
#define SMB380_STATUS_HG__LEN		1
#define SMB380_STATUS_HG__MSK		0x01
#define SMB380_STATUS_HG__REG		SMB380_STATUS_REG

#define SMB380_STATUS_LG__POS		1
#define SMB380_STATUS_LG__LEN		1
#define SMB380_STATUS_LG__MSK		0x02
#define SMB380_STATUS_LG__REG		SMB380_STATUS_REG

#define SMB380_HG_LATCHED__POS  	2
#define SMB380_HG_LATCHED__LEN  	1
#define SMB380_HG_LATCHED__MSK		0x04
#define SMB380_HG_LATCHED__REG		SMB380_STATUS_REG

#define SMB380_LG_LATCHED__POS		3
#define SMB380_LG_LATCHED__LEN		1
#define SMB380_LG_LATCHED__MSK		8
#define SMB380_LG_LATCHED__REG		SMB380_STATUS_REG

#define SMB380_ALERT_PHASE__POS		4
#define SMB380_ALERT_PHASE__LEN		1
#define SMB380_ALERT_PHASE__MSK		0x10
#define SMB380_ALERT_PHASE__REG		SMB380_STATUS_REG


#define SMB380_ST_RESULT__POS		7
#define SMB380_ST_RESULT__LEN		1
#define SMB380_ST_RESULT__MSK		0x80
#define SMB380_ST_RESULT__REG		SMB380_STATUS_REG




#define SMB380_SLEEP__POS			0
#define SMB380_SLEEP__LEN			1
#define SMB380_SLEEP__MSK			0x01
#define SMB380_SLEEP__REG			SMB380_CTRL_REG

#define SMB380_SOFT_RESET__POS		1
#define SMB380_SOFT_RESET__LEN		1
#define SMB380_SOFT_RESET__MSK		0x02
#define SMB380_SOFT_RESET__REG		SMB380_CTRL_REG





#define SMB380_SELF_TEST__POS		2
#define SMB380_SELF_TEST__LEN		2
#define SMB380_SELF_TEST__MSK		0x0C
#define SMB380_SELF_TEST__REG		SMB380_CTRL_REG




#define SMB380_SELF_TEST0__POS		2
#define SMB380_SELF_TEST0__LEN		1
#define SMB380_SELF_TEST0__MSK		0x04
#define SMB380_SELF_TEST0__REG		SMB380_CTRL_REG

#define SMB380_SELF_TEST1__POS		3
#define SMB380_SELF_TEST1__LEN		1
#define SMB380_SELF_TEST1__MSK		0x08
#define SMB380_SELF_TEST1__REG		SMB380_CTRL_REG




#define SMB380_EE_W__POS			4
#define SMB380_EE_W__LEN			1
#define SMB380_EE_W__MSK			0x10
#define SMB380_EE_W__REG			SMB380_CTRL_REG

#define SMB380_UPDATE_IMAGE__POS	5
#define SMB380_UPDATE_IMAGE__LEN	1
#define SMB380_UPDATE_IMAGE__MSK	0x20
#define SMB380_UPDATE_IMAGE__REG	SMB380_CTRL_REG

#define SMB380_RESET_INT__POS		6
#define SMB380_RESET_INT__LEN		1
#define SMB380_RESET_INT__MSK		0x40
#define SMB380_RESET_INT__REG		SMB380_CTRL_REG


#define SMB380_CTRL_REG_RSVD__POS	7
#define SMB380_CTRL_REG_RSVD__LEN	1
#define SMB380_CTRL_REG_RSVD__MSK	0x80
#define SMB380_CTRL_REG_RSVD__REG	SMB380_CTRL_REG








#define SMB380_ENABLE_LG__POS		0
#define SMB380_ENABLE_LG__LEN		1
#define SMB380_ENABLE_LG__MSK		0x01
#define SMB380_ENABLE_LG__REG		SMB380_CONF1_REG




#define SMB380_ENABLE_HG__POS		1
#define SMB380_ENABLE_HG__LEN		1
#define SMB380_ENABLE_HG__MSK		0x02
#define SMB380_ENABLE_HG__REG		SMB380_CONF1_REG




	

#define SMB380_COUNTER_LG__POS			2
#define SMB380_COUNTER_LG__LEN			2
#define SMB380_COUNTER_LG__MSK			0x0C
#define SMB380_COUNTER_LG__REG			SMB380_CONF1_REG
	
#define SMB380_COUNTER_HG__POS			4
#define SMB380_COUNTER_HG__LEN			2
#define SMB380_COUNTER_HG__MSK			0x30
#define SMB380_COUNTER_HG__REG			SMB380_CONF1_REG






#define SMB380_LG_DUR__POS			0
#define SMB380_LG_DUR__LEN			8
#define SMB380_LG_DUR__MSK			0xFF
#define SMB380_LG_DUR__REG			SMB380_LG_DURATION_REG

#define SMB380_HG_DUR__POS			0
#define SMB380_HG_DUR__LEN			8
#define SMB380_HG_DUR__MSK			0xFF
#define SMB380_HG_DUR__REG			SMB380_HG_DURATION_REG




				

#define SMB380_LG_THRES__POS		0
#define SMB380_LG_THRES__LEN		8
#define SMB380_LG_THRES__MSK		0xFF
#define SMB380_LG_THRES__REG		SMB380_LG_THRESHOLD_REG





#define SMB380_HG_THRES__POS		0
#define SMB380_HG_THRES__LEN		8
#define SMB380_HG_THRES__MSK		0xFF
#define SMB380_HG_THRES__REG		SMB380_HG_THRESHOLD_REG








#define SMB380_LG_HYST__POS			0
#define SMB380_LG_HYST__LEN			3
#define SMB380_LG_HYST__MSK			0x07
#define SMB380_LG_HYST__REG			SMB380_HYSTERESIS_REG




#define SMB380_HG_HYST__POS			3
#define SMB380_HG_HYST__LEN			3
#define SMB380_HG_HYST__MSK			0x38
#define SMB380_HG_HYST__REG			SMB380_HYSTERESIS_REG




#define SMB380_EN_ANY_MOTION__POS		6
#define SMB380_EN_ANY_MOTION__LEN		1
#define SMB380_EN_ANY_MOTION__MSK		0x40
#define SMB380_EN_ANY_MOTION__REG		SMB380_CONF1_REG





#define SMB380_ALERT__POS			7
#define SMB380_ALERT__LEN			1
#define SMB380_ALERT__MSK			0x80
#define SMB380_ALERT__REG			SMB380_CONF1_REG







#define SMB380_ANY_MOTION_THRES__POS	0
#define SMB380_ANY_MOTION_THRES__LEN	8
#define SMB380_ANY_MOTION_THRES__MSK	0xFF
#define SMB380_ANY_MOTION_THRES__REG	SMB380_MOTION_THRS_REG




#define SMB380_ANY_MOTION_DUR__POS		6
#define SMB380_ANY_MOTION_DUR__LEN		2
#define SMB380_ANY_MOTION_DUR__MSK		0xC0	
#define SMB380_ANY_MOTION_DUR__REG		SMB380_HYSTERESIS_REG


#define SMB380_CUSTOMER_RESERVED1__POS		0
#define SMB380_CUSTOMER_RESERVED1__LEN	 	8
#define SMB380_CUSTOMER_RESERVED1__MSK		0xFF
#define SMB380_CUSTOMER_RESERVED1__REG		SMB380_CUSTOMER1_REG

#define SMB380_CUSTOMER_RESERVED2__POS		0
#define SMB380_CUSTOMER_RESERVED2__LEN	 	8
#define SMB380_CUSTOMER_RESERVED2__MSK		0xFF
#define SMB380_CUSTOMER_RESERVED2__REG		SMB380_CUSTOMER2_REG





#define SMB380_BANDWIDTH__POS				0
#define SMB380_BANDWIDTH__LEN			 	3
#define SMB380_BANDWIDTH__MSK			 	0x07
#define SMB380_BANDWIDTH__REG				SMB380_RANGE_BWIDTH_REG






#define SMB380_RANGE__POS				3
#define SMB380_RANGE__LEN				2
#define SMB380_RANGE__MSK				0x18	
#define SMB380_RANGE__REG				SMB380_RANGE_BWIDTH_REG





#define SMB380_RANGE_BWIDTH_REG_RSVD__POS	5
#define SMB380_RANGE_BWIDTH_REG_RSVD__LEN	3
#define SMB380_RANGE_BWIDTH_REG_RSVD__MSK	0xE0
#define SMB380_RANGE_BWIDTH_REG_RSVD__REG	SMB380_RANGE_BWIDTH_REG








#define SMB380_WAKE_UP__POS			0
#define SMB380_WAKE_UP__LEN			1
#define SMB380_WAKE_UP__MSK			0x01
#define SMB380_WAKE_UP__REG			SMB380_CONF2_REG




#define SMB380_WAKE_UP_PAUSE__POS		1
#define SMB380_WAKE_UP_PAUSE__LEN		2
#define SMB380_WAKE_UP_PAUSE__MSK		0x06
#define SMB380_WAKE_UP_PAUSE__REG		SMB380_CONF2_REG






#define SMB380_SHADOW_DIS__POS			3
#define SMB380_SHADOW_DIS__LEN			1
#define SMB380_SHADOW_DIS__MSK			0x08
#define SMB380_SHADOW_DIS__REG			SMB380_CONF2_REG






#define SMB380_LATCH_INT__POS			4
#define SMB380_LATCH_INT__LEN			1
#define SMB380_LATCH_INT__MSK			0x10
#define SMB380_LATCH_INT__REG			SMB380_CONF2_REG




#define SMB380_NEW_DATA_INT__POS		5
#define SMB380_NEW_DATA_INT__LEN		1
#define SMB380_NEW_DATA_INT__MSK		0x20
#define SMB380_NEW_DATA_INT__REG		SMB380_CONF2_REG



#define SMB380_ENABLE_ADV_INT__POS		6
#define SMB380_ENABLE_ADV_INT__LEN		1
#define SMB380_ENABLE_ADV_INT__MSK		0x40
#define SMB380_ENABLE_ADV_INT__REG		SMB380_CONF2_REG


#define SMB380_SMB380_SPI4_OFF	0
#define SMB380_SMB380_SPI4_ON	1

#define SMB380_SPI4__POS				7
#define SMB380_SPI4__LEN				1
#define SMB380_SPI4__MSK				0x80
#define SMB380_SPI4__REG				SMB380_CONF2_REG


#define SMB380_OFFSET_X_LSB__POS	6
#define SMB380_OFFSET_X_LSB__LEN	2
#define SMB380_OFFSET_X_LSB__MSK	0xC0
#define SMB380_OFFSET_X_LSB__REG	SMB380_OFFS_GAIN_X_REG

#define SMB380_GAIN_X__POS			0
#define SMB380_GAIN_X__LEN			6
#define SMB380_GAIN_X__MSK			0x3f
#define SMB380_GAIN_X__REG			SMB380_OFFS_GAIN_X_REG


#define SMB380_OFFSET_Y_LSB__POS	6
#define SMB380_OFFSET_Y_LSB__LEN	2
#define SMB380_OFFSET_Y_LSB__MSK	0xC0
#define SMB380_OFFSET_Y_LSB__REG	SMB380_OFFS_GAIN_Y_REG

#define SMB380_GAIN_Y__POS			0
#define SMB380_GAIN_Y__LEN			6
#define SMB380_GAIN_Y__MSK			0x3f
#define SMB380_GAIN_Y__REG			SMB380_OFFS_GAIN_Y_REG


#define SMB380_OFFSET_Z_LSB__POS	6
#define SMB380_OFFSET_Z_LSB__LEN	2
#define SMB380_OFFSET_Z_LSB__MSK	0xC0
#define SMB380_OFFSET_Z_LSB__REG	SMB380_OFFS_GAIN_Z_REG

#define SMB380_GAIN_Z__POS			0
#define SMB380_GAIN_Z__LEN			6
#define SMB380_GAIN_Z__MSK			0x3f
#define SMB380_GAIN_Z__REG			SMB380_OFFS_GAIN_Z_REG

#define SMB380_OFFSET_T_LSB__POS	6
#define SMB380_OFFSET_T_LSB__LEN	2
#define SMB380_OFFSET_T_LSB__MSK	0xC0
#define SMB380_OFFSET_T_LSB__REG	SMB380_OFFS_GAIN_T_REG

#define SMB380_GAIN_T__POS			0
#define SMB380_GAIN_T__LEN			6
#define SMB380_GAIN_T__MSK			0x3f
#define SMB380_GAIN_T__REG			SMB380_OFFS_GAIN_T_REG

#define SMB380_OFFSET_X_MSB__POS	0
#define SMB380_OFFSET_X_MSB__LEN	8
#define SMB380_OFFSET_X_MSB__MSK	0xFF
#define SMB380_OFFSET_X_MSB__REG	SMB380_OFFSET_X_REG


#define SMB380_OFFSET_Y_MSB__POS	0
#define SMB380_OFFSET_Y_MSB__LEN	8
#define SMB380_OFFSET_Y_MSB__MSK	0xFF
#define SMB380_OFFSET_Y_MSB__REG	SMB380_OFFSET_Y_REG

#define SMB380_OFFSET_Z_MSB__POS	0
#define SMB380_OFFSET_Z_MSB__LEN	8
#define SMB380_OFFSET_Z_MSB__MSK	0xFF
#define SMB380_OFFSET_Z_MSB__REG	SMB380_OFFSET_Z_REG

#define SMB380_OFFSET_T_MSB__POS	0
#define SMB380_OFFSET_T_MSB__LEN	8
#define SMB380_OFFSET_T_MSB__MSK	0xFF
#define SMB380_OFFSET_T_MSB__REG	SMB380_OFFSET_T_REG





#define SMB380_GET_BITSLICE(regvar, bitname)\
			(regvar & bitname##__MSK) >> bitname##__POS


#define SMB380_SET_BITSLICE(regvar, bitname, val)\
		  (regvar & ~bitname##__MSK) | ((val<<bitname##__POS)&bitname##__MSK)  










#define SMB380_RANGE_2G			0 
#define SMB380_RANGE_4G			1 
#define SMB380_RANGE_8G			2 


#define SMB380_BW_25HZ		0	
#define SMB380_BW_50HZ		1	
#define SMB380_BW_100HZ		2	
#define SMB380_BW_190HZ		3	
#define SMB380_BW_375HZ		4	
#define SMB380_BW_750HZ		5	
#define SMB380_BW_1500HZ	6	



#define SMB380_MODE_NORMAL      0
#define SMB380_MODE_SLEEP       2
#define SMB380_MODE_WAKE_UP     3



#define SMB380_WAKE_UP_PAUSE_20MS		0
#define SMB380_WAKE_UP_PAUSE_80MS		1
#define SMB380_WAKE_UP_PAUSE_320MS		2
#define SMB380_WAKE_UP_PAUSE_2560MS		3





#define SMB380_SELF_TEST0_ON		1
#define SMB380_SELF_TEST1_ON		2

#define SMB380_EE_W_OFF			0
#define SMB380_EE_W_ON			1






#define SMB380_COUNTER_LG_RST		0
#define SMB380_COUNTER_LG_0LSB		SMB380_COUNTER_LG_RST
#define SMB380_COUNTER_LG_VE001		1
#define SMB380_COUNTER_LG_2LSB		2
#define SMB380_COUNTER_LG_3LSB		3

#define SMB380_COUNTER_HG_RST		0
#define SMB380_COUNTER_HG_0LSB		SMB380_COUNTER_HG_RST
#define SMB380_COUNTER_HG_VE001		1
#define SMB380_COUNTER_HG_2LSB		2
#define SMB380_COUNTER_HG_3LSB		3

#define SMB380_COUNTER_RST			0
#define SMB380_COUNTER_0LSB			SMB380_COUNTER_RST
#define SMB380_COUNTER_VE001			1
#define SMB380_COUNTER_2LSB			2
#define SMB380_COUNTER_3LSB			3







#define SMB380_LG_THRES_IN_G( gthres, range)			((256 * gthres ) / range)





#define SMB380_HG_THRES_IN_G(gthres, range)				((256 * gthres ) / range)





#define SMB380_LG_HYST_IN_G( ghyst, range )				((32 * ghyst) / range)





#define SMB380_HG_HYST_IN_G( ghyst, range )				((32 * ghyst) / range)







#define SMB380_ANY_MOTION_THRES_IN_G( gthres, range)	((128 * gthres ) / range)


#define SMB380_ANY_MOTION_DUR_1		0
#define SMB380_ANY_MOTION_DUR_3		1
#define SMB380_ANY_MOTION_DUR_5		2
#define SMB380_ANY_MOTION_DUR_7		3



#define SMB380_SHADOW_DIS_OFF	0
#define SMB380_SHADOW_DIS_ON	1

#define SMB380_LATCH_INT_OFF	0
#define SMB380_LATCH_INT_ON		1

#define SMB380_NEW_DATA_INT_OFF	0
#define SMB380_NEW_DATA_INT_ON	1

#define SMB380_ENABLE_ADV_INT_OFF	0
#define SMB380_ENABLE_ADV_INT_ON	1

#define SMB380_EN_ANY_MOTION_OFF 	0
#define SMB380_EN_ANY_MOTION_ON 	1


#define SMB380_ALERT_OFF	0
#define SMB380_ALERT_ON		1

#define SMB380_ENABLE_LG_OFF	0
#define SMB380_ENABLE_LG_ON		1

#define SMB380_ENABLE_HG_OFF	0
#define SMB380_ENABLE_HG_ON		1



#define SMB380_INT_ALERT		(1<<7)
#define SMB380_INT_ANY_MOTION	(1<<6)
#define SMB380_INT_EN_ADV_INT	(1<<5)
#define SMB380_INT_NEW_DATA		(1<<4)
#define SMB380_INT_LATCH		(1<<3)
#define SMB380_INT_HG			(1<<1)
#define SMB380_INT_LG			(1<<0)


#define SMB380_INT_STATUS_HG			(1<<0)
#define SMB380_INT_STATUS_LG			(1<<1)
#define SMB380_INT_STATUS_HG_LATCHED	(1<<2)
#define SMB380_INT_STATUS_LG_LATCHED	(1<<3)
#define SMB380_INT_STATUS_ALERT			(1<<4)
#define SMB380_INT_STATUS_ST_RESULT		(1<<7)


#define SMB380_CONF1_INT_MSK	((1<<SMB380_ALERT__POS) | (1<<SMB380_EN_ANY_MOTION__POS) | (1<<SMB380_ENABLE_HG__POS) | (1<<SMB380_ENABLE_LG__POS))
#define SMB380_CONF2_INT_MSK	((1<<SMB380_ENABLE_ADV_INT__POS) | (1<<SMB380_NEW_DATA_INT__POS) | (1<<SMB380_LATCH_INT__POS))














int smb380_init(smb380_t *);

int smb380_set_image (smb380regs_t *);

int smb380_get_image(smb380regs_t *);

int smb380_get_offset(unsigned char, unsigned short *); 

int smb380_set_offset(unsigned char, unsigned short ); 

int smb380_set_offset_eeprom(unsigned char, unsigned short);

int smb380_soft_reset(void); 

int smb380_update_image(void); 

int smb380_write_ee(unsigned char , unsigned char ) ;

int smb380_set_ee_w(unsigned char);

int smb380_get_ee_w(unsigned char*);

int smb380_selftest(unsigned char);





int smb380_set_range(char); 

int smb380_get_range(unsigned char*);

int smb380_set_mode(unsigned char); 









int smb380_set_bandwidth(char);

int smb380_get_bandwidth(unsigned char *);

















































int smb380_read_temperature(unsigned char*);

int smb380_read_accel_xyz(smb380acc_t *);

int smb380_get_interrupt_status(unsigned char *);























int smb380_pause(int);

int smb380_read_reg(unsigned char , unsigned char *, unsigned char);

int smb380_write_reg(unsigned char , unsigned char*, unsigned char );




#endif   





