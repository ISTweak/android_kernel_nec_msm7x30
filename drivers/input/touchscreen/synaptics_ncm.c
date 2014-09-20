/*
 * drivers/input/touchscreen/synaptics_ncm.c
 *
 * - Synaptics Touchscreen RMI4 SPI driver
 *
 * Copyright (C) NEC CASIO Mobile Communications, Ltd.
 *
 */
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/kthread.h>
#include <mach/gpio.h>
#include <linux/synaptics_ncm.h>
#include <linux/touch_panel_cmd.h>

#include <linux/earlysuspend.h>

#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/firmware.h>
#include <linux/oemnc_info.h>






#include <linux/debugfs.h>
#include <linux/delay.h>














#define SYNAPTICS_FINGER_NUM				5


#define SYNAPTICS_BUTTON_NUM				3
#define SYNAPTICS_MODE_BUTTON2				0x04
#define SYNAPTICS_MODE_BUTTON1				0x02
#define SYNAPTICS_MODE_BUTTON0				0x01
#define SYNAPTICS_TOUCH_FIELD_Y				1782
#define SYNAPTICS_BUTTON0_MIN_X				117
#define SYNAPTICS_BUTTON0_MAX_X				255
#define SYNAPTICS_BUTTON1_MIN_X				431
#define SYNAPTICS_BUTTON1_MAX_X				569
#define SYNAPTICS_BUTTON2_MIN_X				745
#define SYNAPTICS_BUTTON2_MAX_X				883
#define SYNAPTICS_BUTTON_MIN_Y				1816
#define SYNAPTICS_BUTTON_MAX_Y				1892

#define SYNAPTICS_MAG_X						100
#define SYNAPTICS_MAG_Y						100
#define SYNAPTICS_ABS_MAX_X					479



#define SYNAPTICS_ABS_MAX_Y					853

#define SYNAPTICS_ABS_MAX_PRESS				255

#define SYNAPTICS_LCD_MAX_X					480
#define SYNAPTICS_LCD_MAX_Y					854
#define SYNAPTICS_KEY_AREA_Y				110

#define SYNAPTICS_KEY_CANCEL_Y				1682

#define SYNAPTICS_TIMEOUT_KEY_DELAY			(13*HZ)/1000
#define SYNAPTICS_TIMEOUT_KEY_CANCEL		(200*HZ)/1000
#define SYNAPTICS_TIMEOUT_400				(400*HZ)/1000
#define SYNAPTICS_TIMEOUT_600				(600*HZ)/1000
#define SYNAPTICS_TIMEOUT_1000				(1000*HZ)/1000
#define SYNAPTICS_TIMEOUT_2000				(2000*HZ)/1000

#define SYNAPTICS_CONTROL_BASE_ADDR			0x00E5

#define SYNAPTICS_SPI_DELAY_TIME			30
#define SYNAPTICS_SPI_DELAY_TIME_READ		70
#define SYNAPTICS_INIT_WAIT_TIME			100
#define SYNAPTICS_INIT_WAIT_LOOP_CNT		100
#define SYNAPTICS_RESET_WAIT_TIME			10
#define SYNAPTICS_POW_ON_WAIT_LOOP_CNT		4
#define SYNAPTICS_SPI_RETRY_CNT				4

#define SYNAPTICS_SPI_READ_ADR				0x80

#define SYNAPTICS_RTN_ERR					-1
#define SYNAPTICS_RTN_VAL_FF				0xFF

#define SYNAPTICS_LEFT_SIFT_4				4
#define SYNAPTICS_LEFT_SIFT_8				8
#define SYNAPTICS_LEFT_SIFT_16				16
#define SYNAPTICS_RIGHT_SIFT_4				4
#define SYNAPTICS_RIGHT_SIFT_8				8

#define SYNAPTICS_MASK_DAT_0F				0x0F
#define SYNAPTICS_MASK_DAT_FF				0xFF
#define SYNAPTICS_MASK_DAT_FF00				0xFF00

#define SYNAPTICS_FINGER_STATE_BASE			0x01
#define SYNAPTICS_NEXT_FINGER				0x05
#define SYNAPTICS_ABS_INIT_VAL				0xFFFF



#define SYNAPTICS_FINGER_STATE_ALL			0xFFFF


#define F01_RMI_CTRL00_SET_INIT_DAT			0x80
#define F01_RMI_CTRL01_00_SET_INIT_DAT		0x07
#define F11_2D_CTRL00_SET_INIT_DAT			0x00
#define F11_2D_CTRL01_SET_INIT_DAT			0x00
#define F11_2D_CTRL02_SET_INIT_DAT			0x02
#define F11_2D_CTRL03_SET_INIT_DAT			0x02
#define F11_2D_CTRL11_SET_INIT_DAT			0x00

#define F01_RMI_CMD00_RESET					0x01
#define F01_RMI_CTRL00_ENTER_SLEEP			0x01
#define F01_RMI_CTRL00_EXIT_SLEEP			0x00

#define F01_RMI_CTRL00_CONF_END				0x00
#define F11_2D_CTRL14_MAX_VAL				0x1F

#define SYNAPTICS_ERR_RESET_OCCURRED		0x01
#define SYNAPTICS_ERR_INVALID_CONFIG		0x02
#define SYNAPTICS_ERR_DEVICE_FAILURE		0x03

#define SYNAPTICS_FWUP_RET_OK				0x00
#define SYNAPTICS_FWUP_RET_ERR				0x01
#define SYNAPTICS_FWUP_RET_ERR_FW_NO_FILE	0x20


#define CTL_REG_OFFSET_F01_RMI_CTRL00		0x00
#define CTL_REG_OFFSET_F01_RMI_CTRL01_00	0x01
#define CTL_REG_OFFSET_F11_2D_CTRL00		0x02
#define CTL_REG_OFFSET_F11_2D_CTRL01		0x03
#define CTL_REG_OFFSET_F11_2D_CTRL02		0x04
#define CTL_REG_OFFSET_F11_2D_CTRL03		0x05
#define CTL_REG_OFFSET_F11_2D_CTRL04		0x06
#define CTL_REG_OFFSET_F11_2D_CTRL05		0x07
#define CTL_REG_OFFSET_F11_2D_CTRL06		0x08
#define CTL_REG_OFFSET_F11_2D_CTRL07		0x09
#define CTL_REG_OFFSET_F11_2D_CTRL08		0x0A
#define CTL_REG_OFFSET_F11_2D_CTRL09		0x0B
#define CTL_REG_OFFSET_F11_2D_CTRL11		0x0C
#define CTL_REG_OFFSET_F11_2D_CTRL12_01		0x0D
#define CTL_REG_OFFSET_F11_2D_CTRL12_02		0x0E
#define CTL_REG_OFFSET_F11_2D_CTRL12_03		0x0F
#define CTL_REG_OFFSET_F11_2D_CTRL12_04		0x10
#define CTL_REG_OFFSET_F11_2D_CTRL12_05		0x11
#define CTL_REG_OFFSET_F11_2D_CTRL12_06		0x12
#define CTL_REG_OFFSET_F11_2D_CTRL12_07		0x13
#define CTL_REG_OFFSET_F11_2D_CTRL12_08		0x14
#define CTL_REG_OFFSET_F11_2D_CTRL12_09		0x15
#define CTL_REG_OFFSET_F11_2D_CTRL12_10		0x16
#define CTL_REG_OFFSET_F11_2D_CTRL12_11		0x17
#define CTL_REG_OFFSET_F11_2D_CTRL12_12		0x18
#define CTL_REG_OFFSET_F11_2D_CTRL12_13		0x19
#define CTL_REG_OFFSET_F11_2D_CTRL12_14		0x1A
#define CTL_REG_OFFSET_F11_2D_CTRL12_15		0x1B
#define CTL_REG_OFFSET_F11_2D_CTRL12_16		0x1C
#define CTL_REG_OFFSET_F11_2D_CTRL12_17		0x1D
#define CTL_REG_OFFSET_F11_2D_CTRL12_18		0x1E
#define CTL_REG_OFFSET_F11_2D_CTRL12_19		0x1F
#define CTL_REG_OFFSET_F11_2D_CTRL12_20		0x20
#define CTL_REG_OFFSET_F11_2D_CTRL12_21		0x21
#define CTL_REG_OFFSET_F11_2D_CTRL12_22		0x22
#define CTL_REG_OFFSET_F11_2D_CTRL12_23		0x23
#define CTL_REG_OFFSET_F11_2D_CTRL12_24		0x24
#define CTL_REG_OFFSET_F11_2D_CTRL12_25		0x25
#define CTL_REG_OFFSET_F11_2D_CTRL12_26		0x26
#define CTL_REG_OFFSET_F11_2D_CTRL12_27		0x27
#define CTL_REG_OFFSET_F11_2D_CTRL12_28		0x28
#define CTL_REG_OFFSET_F11_2D_CTRL12_29		0x29
#define	CTL_REG_OFFSET_F11_2D_CTRL14		0x47
#define	CTL_REG_OFFSET_CFGBLK_CRC1			0x1FC
#define	CTL_REG_OFFSET_CFGBLK_CRC2			0x1FB
#define	CTL_REG_OFFSET_CFGBLK_CRC3			0x1FE
#define	CTL_REG_OFFSET_CFGBLK_CRC4			0x1FF


#define FLASH_REG_OFFSET_F34_FLASH_DATA00		0x00
#define FLASH_REG_OFFSET_F34_FLASH_DATA01		0x01
#define FLASH_REG_OFFSET_F34_FLASH_DATA02_00	0x02
#define FLASH_REG_OFFSET_F34_FLASH_DATA02_01	0x03
#define FLASH_REG_OFFSET_F34_FLASH_DATA03		0x12
#define FLASH_REG_OFFSET_F34_FLASH_QUERY00		0x00
#define FLASH_REG_OFFSET_F34_FLASH_QUERY01		0x01


#define	DATA_REG_OFFSET_F01_RMI_DATA00		0x00
#define	DATA_REG_OFFSET_F01_RMI_DATA01_00	0x01


#define QUERY_REG_OFFSET_F01_RMI_QUERY03	0x03


#define CMD_REG_F01_RMI_CMD00				0x7A
#define CMD_REG_F11_2D_CMD00				0x7A


#define QUERY_REG_F01_RMI_QUERY00			0x84
#define QUERY_REG_F01_RMI_QUERY01			0x85
#define QUERY_REG_F01_RMI_QUERY02			0x86
#define QUERY_REG_F01_RMI_QUERY03			0x87
#define QUERY_REG_F01_RMI_QUERY04			0x88
#define QUERY_REG_F01_RMI_QUERY05			0x89
#define QUERY_REG_F01_RMI_QUERY06			0x8A
#define QUERY_REG_F01_RMI_QUERY07			0x8B
#define QUERY_REG_F01_RMI_QUERY08			0x8C
#define QUERY_REG_F01_RMI_QUERY09			0x8D
#define QUERY_REG_F01_RMI_QUERY10			0x8E
#define QUERY_REG_F01_RMI_QUERY11			0x8F
#define QUERY_REG_F01_RMI_QUERY12			0x90
#define QUERY_REG_F01_RMI_QUERY13			0x91
#define QUERY_REG_F01_RMI_QUERY14			0x92
#define QUERY_REG_F01_RMI_QUERY15			0x93
#define QUERY_REG_F01_RMI_QUERY16			0x94
#define QUERY_REG_F01_RMI_QUERY17			0x95
#define QUERY_REG_F01_RMI_QUERY18			0x96
#define QUERY_REG_F01_RMI_QUERY19			0x97
#define QUERY_REG_F01_RMI_QUERY20			0x98
#define QUERY_REG_F11_2D_QUERY00			0x99
#define QUERY_REG_F11_2D_QUERY01			0x9B
#define QUERY_REG_F11_2D_QUERY02			0x9B
#define QUERY_REG_F11_2D_QUERY03			0x9C
#define QUERY_REG_F11_2D_QUERY04			0x9D
#define QUERY_REG_F11_2D_QUERY05			0x9E


#define	DATA_REG_F01_RMI_DATA00				0x13
#define	DATA_REG_F01_RMI_DATA01_00			0x14
#define	DATA_REG_F11_2D_DATA00_00			0x15
#define	DATA_REG_F11_2D_DATA00_01			0X16




#define	DATA_REG_F11_2D_DATA01_00			0x17
#define	DATA_REG_F11_2D_DATA02_00			0x18
#define	DATA_REG_F11_2D_DATA03_00			0x19
#define	DATA_REG_F11_2D_DATA04_00			0x1A
#define	DATA_REG_F11_2D_DATA05_00			0x1B
#define	DATA_REG_F11_2D_DATA01_01			0x1C
#define	DATA_REG_F11_2D_DATA02_01			0x1D
#define	DATA_REG_F11_2D_DATA03_01			0x1E
#define	DATA_REG_F11_2D_DATA04_01			0x1F
#define	DATA_REG_F11_2D_DATA05_01			0x20
#define	DATA_REG_F11_2D_DATA01_02			0x21
#define	DATA_REG_F11_2D_DATA02_02			0x22
#define	DATA_REG_F11_2D_DATA03_02			0x23
#define	DATA_REG_F11_2D_DATA04_02			0x24
#define	DATA_REG_F11_2D_DATA05_02			0x25
#define	DATA_REG_F11_2D_DATA01_03			0x26
#define	DATA_REG_F11_2D_DATA02_03			0x27
#define	DATA_REG_F11_2D_DATA03_03			0x28
#define	DATA_REG_F11_2D_DATA04_03			0x29
#define	DATA_REG_F11_2D_DATA05_03			0x2A
#define	DATA_REG_F11_2D_DATA01_04			0x2B
#define	DATA_REG_F11_2D_DATA02_04			0x2C
#define	DATA_REG_F11_2D_DATA03_04			0x2D
#define	DATA_REG_F11_2D_DATA04_04			0x2E
#define	DATA_REG_F11_2D_DATA05_04			0x2F
#define	DATA_REG_F11_2D_DATA09				0x30



#define	BASE_REG_F11_2D_QUERY_BASE			0xDD
#define	BASE_REG_F01_RMI_QUERY_BASE			0xE3
#define	BASE_REG_F01_RMI_DATA_BASE			0xE6
#define	BASE_REG_F34_FLASH_QUERY_BASE		0xE9
#define	BASE_REG_F34_FLASH_DATA_BASE		0xEC

typedef enum {
	SYNAPTICS_STATE_NONE		= 0,
	SYNAPTICS_STATE_INIT_IRQ1,
	SYNAPTICS_STATE_INIT_IRQ2,
	SYNAPTICS_STATE_RUN,
	SYNAPTICS_STATE_SUSPEND,
	SYNAPTICS_STATE_RESET
} state_enum;

typedef enum {
	SYNAPTICS_INIT_STATE_NONE	= 0,
	SYNAPTICS_INIT_STATE_DONE,
	SYNAPTICS_INIT_STATE_SUSPEND
} g_touch_state_enum;

typedef enum {
	SYNAPTICS_FWUP_STATE_NONE	= 0,
	SYNAPTICS_FWUP_STATE_EXEC
} fwup_state_enum;

typedef enum {
	SYNAPTICS_KEY_UP			= 0,
	SYNAPTICS_KEY_DOWN			= 5, 
	SYNAPTICS_KEY_DOWN_CANCEL
} ekey_state;



typedef struct sensor_abs_struct {
	int		xxx;
	int		Dx;
	int		Rx;
	int		yyy;
	int		Dy;
	int		Ry;
} sensor_abs_type;

typedef struct ts_abs_struct {
	int		max_x;
	int		min_x;
	int		max_y;
	int		min_y;
	int		max_press;
	int		min_press;
} ts_abs_type;

typedef struct ts_hw_key_struct {
	int		button0_min_x;
	int		button0_max_x;
	int		button1_min_x;
	int		button1_max_x;
	int		button2_min_x;
	int		button2_max_x;
	int		min_y;
	int		max_y;
	int		key_code[SYNAPTICS_BUTTON_NUM];
	u8		key_down[SYNAPTICS_BUTTON_NUM];
} ts_hw_key_type;

typedef struct synaptics_abs_struct {
	int		X;
	int		Y;
	int		Wx;
	int		Wy;
	int		Z;
} synaptics_abs_type;


typedef struct debugfs_synaptics_env_struct {
	const char *p_name;
	mode_t mode;
	void *p_data;
} debugfs_synaptics_env_type;

static u32 g_sensitivity_work = 0;
static u32 g_sensitivity      = 0;
static u32 g_spidelay1        = SYNAPTICS_SPI_DELAY_TIME_READ;
static u32 g_spidelay2        = SYNAPTICS_SPI_DELAY_TIME;

static const debugfs_synaptics_env_type debugfs_synaptics_env[] = {
	{"g_sensitivity",  S_IRUGO | S_IWUSR, &g_sensitivity},
	{"g_spidelay1",    S_IRUGO | S_IWUSR, &g_spidelay1},
	{"g_spidelay2",    S_IRUGO | S_IWUSR, &g_spidelay2},
};


typedef struct synaptics_ncm_data_struct {
	struct spi_device			*p_spi;
	struct input_dev			*p_input_dev;
	struct work_struct			work;
	struct work_struct			work_timer;
	struct work_struct			work_key_timer;
	int							key_timer_state;
	int							hw_key_mode;
	ts_abs_type					abs;
	ts_hw_key_type				hw_key;
	uint32_t					hw_rev;
	sensor_abs_type				ss_abs;
	synaptics_abs_type 			finger_scoord[SYNAPTICS_FINGER_NUM];
	state_enum					state;
	int							fs[SYNAPTICS_FINGER_NUM];
	unsigned short				ctl_base;
	unsigned short				f01_rmi_query_base;
	unsigned short				f01_rmi_data_base;
	unsigned short				f34_flash_query_base;
	unsigned short				f34_flash_data_base;
	u8							key_cancel;

	struct dentry 				*p_dent_synaptics_root;
	struct dentry				*p_dent_synaptics_env[ARRAY_SIZE(debugfs_synaptics_env)];



	struct early_suspend		early_suspend;

} synaptics_ncm_data_type;





static void synaptics_ncm_early_suspend(struct early_suspend *p_h);
static void synaptics_ncm_late_resume(struct early_suspend *p_h);

static void synaptics_ncm_timer_handler( unsigned long data );
static int synaptics_ncm_enter_sleep(struct spi_device *p_spi);
static int synaptics_ncm_exit_sleep(struct spi_device *p_spi);
static int synaptics_ncm_soft_reset(struct spi_device *p_spi);
static int synaptics_ncm_fw_update(struct spi_device *p_spi);
static unsigned char synaptics_ncm_rev(struct spi_device *p_spi);
static int rmi_spi_read(struct spi_device *p_spi, unsigned short address, u8 *p_valp);
static int synaptics_ncm_abs_read(unsigned long status,
		synaptics_ncm_data_type *p_ts, synaptics_abs_type abs[]);
static int synaptics_ncm_suspend(struct spi_device *p_spi, pm_message_t mesg);
static int synaptics_ncm_timer_init(synaptics_ncm_data_type *p_ts);



static int synaptics_ncm_power_off(struct spi_device *p_spi);
static int synaptics_ncm_get_sensor_abs_config(synaptics_ncm_data_type *p_ts);
static int synaptics_ncm_configure(synaptics_ncm_data_type *p_ts);




static struct workqueue_struct  *gp_synaptics_ncm_wq = NULL;
static struct workqueue_struct	*gp_synaptics_ncm_timer_wq = NULL;
static struct spi_device		*gp_spi = NULL;
static struct timer_list		g_synaptics_ncm_timer;
static struct timer_list		g_synaptics_ncm_key_timer;
static struct timer_list		g_synaptics_ncm_key_cancel_timer;
static struct workqueue_struct	*gp_synaptics_ncm_key_timer_wq = NULL;
static unsigned char 			g_diagtype = 0;
static void (*gp_tp_cmd_callback)(void *) = NULL;
static touch_diag_result g_touch_result;
static volatile g_touch_state_enum g_touch_state = SYNAPTICS_INIT_STATE_NONE;
static u32 g_spidelay1_time = SYNAPTICS_SPI_DELAY_TIME_READ;
static u32 g_spidelay2_time = SYNAPTICS_SPI_DELAY_TIME;
static wait_queue_head_t g_synaptics_ncm_fwup_wait;
static int g_synaptics_ncm_fwup_state     = SYNAPTICS_FWUP_STATE_NONE;
static int g_synaptics_ncm_fwup_condition = 0;






unsigned char touch_panel_cmd( unsigned char type, void *p_val )
{
	unsigned char	ret    = SYNAPTICS_RTN_VAL_FF; 
	int				finger = 0;
	synaptics_ncm_data_type *p_ts;
	synaptics_abs_type abs[SYNAPTICS_FINGER_NUM];
	touch_diag_result *p_result;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter type = %d\n", __func__, type);

	p_result = (touch_diag_result*)p_val;

	if ( gp_spi == NULL )
	{
		printk(KERN_DEBUG "[synaptics_ncm]%s: Exit gp_spi = NULL \n", __func__);
		
		return ret;
	}

	switch ( type )
	{
		case TOUCH_PANEL_CMD_TYPE_ENTR_SLEEP:
			ret = synaptics_ncm_enter_sleep( gp_spi );
			break;

		case TOUCH_PANEL_CMD_TYPE_EXIT_SLEEP:
			ret = synaptics_ncm_exit_sleep( gp_spi );
			break;

		case TOUCH_PANEL_CMD_TYPE_GET_REVISION:
			ret = synaptics_ncm_rev( gp_spi );
			break;

		case TOUCH_PANEL_CMD_TYPE_RESET:
			ret = synaptics_ncm_soft_reset( gp_spi );
			break;

		case TOUCH_PANEL_CMD_TYPE_GET_COORD:
			p_ts = spi_get_drvdata(gp_spi);
			ret = synaptics_ncm_abs_read( SYNAPTICS_FINGER_STATE_ALL, p_ts, abs );

			if ( ( ret == 0 ) && ( p_result != NULL ) )
			{
				p_result->ret = 0;

				for ( finger = 0; finger < SYNAPTICS_FINGER_NUM ; finger++ )
				{
					p_result->finger[finger].finger_data_x[0] =
							(u8)( abs[finger].X >> SYNAPTICS_RIGHT_SIFT_8 );
					p_result->finger[finger].finger_data_x[1] =
							(u8)( abs[finger].X & SYNAPTICS_MASK_DAT_FF );
					p_result->finger[finger].finger_data_y[0] =
							(u8)( abs[finger].Y >> SYNAPTICS_RIGHT_SIFT_8 );
					p_result->finger[finger].finger_data_y[1] =
							(u8)( abs[finger].Y & SYNAPTICS_MASK_DAT_FF );











				}
			}
			else if ( p_result != NULL )
			{
				printk(KERN_DEBUG "[synaptics_ncm]%s: synaptics_ncm_abs_read\n",
						__func__);
				p_result->ret = SYNAPTICS_RTN_VAL_FF;
				ret = SYNAPTICS_RTN_VAL_FF;
			}
			else
			{
				printk(KERN_DEBUG "[synaptics_ncm]%s: p_result = NULL Error\n",
						__func__);
				ret = SYNAPTICS_RTN_VAL_FF;
			}
			break;

		case TOUCH_PANEL_CMD_TYPE_FW_UPDATE:
			ret = synaptics_ncm_fw_update( gp_spi );
			break;

		default:
			printk(KERN_DEBUG "[synaptics_ncm]%s: NG type = %d\n", __func__, type);
			break;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit ret = %d\n", __func__, ret);

	return ret;

}
EXPORT_SYMBOL( touch_panel_cmd );



unsigned char touch_panel_cmd_callback( unsigned char type,
                                        unsigned char val,
                                        void (*func)(void *) )
{
	unsigned char ret = SYNAPTICS_RTN_VAL_FF; 

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter type = %d\n", __func__, type);

	if ( func == NULL )
	{
		printk(KERN_DEBUG "[synaptics_ncm]%s: func = NULL\n", __func__);
		return ret;
	}

	switch ( type )
	{
		case TOUCH_PANEL_CMD_TYPE_LINE_TEST:
			gp_tp_cmd_callback = func;
			g_diagtype = TOUCH_PANEL_CMD_TYPE_LINE_TEST;
			ret = 0;
			break;

		default:
			printk(KERN_DEBUG "[synaptics_ncm]%s: NG type = %d\n", __func__, type);
			break;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit ret = %d\n", __func__, ret);

	return ret;

}
EXPORT_SYMBOL(touch_panel_cmd_callback);



static void touch_panel_callback( u8 data[] )
{
	int		finger = 0;
	synaptics_ncm_data_type *p_ts;

	if ( gp_tp_cmd_callback == NULL )
	{
		return;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter g_diagtype = %d\n",
			__func__,
			g_diagtype);

	p_ts = spi_get_drvdata( gp_spi );

	switch ( g_diagtype )
	{
		case TOUCH_PANEL_CMD_TYPE_LINE_TEST:
			g_touch_result.ret = 0;

			for ( finger = 0; finger < SYNAPTICS_FINGER_NUM ; finger++ )
			{
				g_touch_result.finger[finger].finger_data_x[0] =
						(u8)( p_ts->finger_scoord[finger].X >> SYNAPTICS_RIGHT_SIFT_8 );
				g_touch_result.finger[finger].finger_data_x[1] =
						(u8)( p_ts->finger_scoord[finger].X & SYNAPTICS_MASK_DAT_FF );
				g_touch_result.finger[finger].finger_data_y[0] =
						(u8)( p_ts->finger_scoord[finger].Y >> SYNAPTICS_RIGHT_SIFT_8 );
				g_touch_result.finger[finger].finger_data_y[1] =
						(u8)( p_ts->finger_scoord[finger].Y & SYNAPTICS_MASK_DAT_FF );











			}
			break;

		default:
			g_touch_result.ret = SYNAPTICS_RTN_VAL_FF;
			printk(KERN_DEBUG "[synaptics_ncm]%s: NG g_diagtype = %d\n",
					__func__,
					g_diagtype);
			break;
	}

	gp_tp_cmd_callback( &g_touch_result );
	gp_tp_cmd_callback = NULL;
	g_diagtype = 0;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);

	return ;

}







static int synaptics_debugfs_env_set( void *p_data, u64 val )
{
	*(u32*)p_data = (u32)val;
	return 0;
}



static int synaptics_debugfs_env_get( void *p_data, u64 *p_val )
{
	*p_val = (u64)(*(u32*)p_data);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE( synaptics_debugfs_fops,
						 synaptics_debugfs_env_get,
						 synaptics_debugfs_env_set,
						 "0x%08llx\n" );



static void __devinit synaptics_debugfs_init( synaptics_ncm_data_type *p_ts )
{
	int i = 0;

	p_ts->p_dent_synaptics_root = debugfs_create_dir( dev_name(&p_ts->p_spi->dev), NULL );
	if ( p_ts->p_dent_synaptics_root )
	{
		for ( i = 0; i < ARRAY_SIZE(debugfs_synaptics_env); i++ )
		{
			p_ts->p_dent_synaptics_env[i] =
					debugfs_create_file(
							debugfs_synaptics_env[i].p_name,
							debugfs_synaptics_env[i].mode,
							p_ts->p_dent_synaptics_root,
							debugfs_synaptics_env[i].p_data,
							&synaptics_debugfs_fops );
		}
	}
}



static void __devexit synaptics_debugfs_remove( synaptics_ncm_data_type *p_ts )
{
	int i = 0;

	if ( p_ts->p_dent_synaptics_root )
	{
		debugfs_remove_recursive( p_ts->p_dent_synaptics_root );
		p_ts->p_dent_synaptics_root = NULL;
		for ( i = 0; i < ARRAY_SIZE(debugfs_synaptics_env); i++ )
		{
			p_ts->p_dent_synaptics_env[i] = NULL;
		}
	}
}




static int spi_xfer( struct spi_device *p_spi,
					 const u8 *p_txbuf,
					 unsigned n_tx,
					 u8 *p_rxbuf,
					 unsigned n_rx )
{
	struct spi_message 		m;
	struct spi_transfer 	t;
	int						rc     = 0;
	unsigned int			rx_cnt = 0;
	char					rx_tmp = 0;

	memset( &t, 0, sizeof(t) );

	udelay( g_spidelay2_time );

	if ( n_tx )
	{
		t.tx_buf = p_txbuf;
		t.rx_buf = 0;
		t.len    = n_tx;

		spi_message_init( &m );
		spi_message_add_tail( &t, &m );

		rc = spi_sync( p_spi, &m );
		if (rc)
		{
			printk(KERN_DEBUG "[synaptics_ncm]%s: spi_xfer faild\n", __func__);
		}
	}

	if ( n_rx )
	{
		t.tx_buf = 0;
		t.rx_buf = &rx_tmp;
		t.len    = 1;

		for ( rx_cnt = 0; rx_cnt < n_rx; rx_cnt++ )
		{
			udelay( g_spidelay1_time );

			spi_message_init( &m );
			spi_message_add_tail( &t, &m );

			rc = spi_sync( p_spi, &m );
			if ( rc )
			{
				printk(KERN_DEBUG "[synaptics_ncm]%s: spi_xfer faild\n", __func__);
			}

			*( p_rxbuf + rx_cnt ) = rx_tmp;
		}
	}
	return rc;
}



static int rmi_spi_read( struct spi_device *p_spi, unsigned short address, u8 *p_valp )
{
	u8 rxbuf[2];
	int retval = 0;
	unsigned short addr = address;
	int retry_cnt = 0;

	addr = (unsigned short)( ( addr & SYNAPTICS_MASK_DAT_FF00 ) >> SYNAPTICS_RIGHT_SIFT_8 );
	address = (unsigned short)( ( address & SYNAPTICS_MASK_DAT_FF ) << SYNAPTICS_LEFT_SIFT_8 );
	addr |= address;
	addr |= (unsigned short)SYNAPTICS_SPI_READ_ADR;		

	retval = spi_xfer( p_spi, (u8*)&addr, 2, rxbuf, 1 );

	*p_valp = rxbuf[0];








	if( retval )
	{
		for( retry_cnt = 0; retry_cnt < SYNAPTICS_SPI_RETRY_CNT; retry_cnt++)
		{
			printk(KERN_ERR "[synaptics_ncm]%s: retry ! (%d)\n",__func__,retry_cnt);
			udelay(50);
			retval = spi_xfer( p_spi, (u8*)&addr, 2, rxbuf, 1 );
			*p_valp = rxbuf[0];
			if( retval == 0 )
			{
				break;
			}
		}
	}
	return retval;
}



static int rmi_spi_write( struct spi_device *p_spi, unsigned short address, u8 data )
{
	u8  txbuf[4];
	int retval = 0;
	int retry_cnt = 0;

	txbuf[2]  = data; 
	txbuf[1]  = (unsigned char)address;
	txbuf[0]  = (unsigned char)( address >> SYNAPTICS_RIGHT_SIFT_8 );

	retval = spi_xfer( p_spi, txbuf, 3, NULL, 0 );








	if( retval )
	{
		for( retry_cnt = 0; retry_cnt < SYNAPTICS_SPI_RETRY_CNT; retry_cnt++)
		{
			printk(KERN_ERR "[synaptics_ncm]%s: retry ! (%d)\n",__func__,retry_cnt);
			udelay(50);
			retval = spi_xfer( p_spi, txbuf, 3, NULL, 0 );
			if( retval == 0 )
			{
				break;
			}
		}
	}
	return retval;
}



static int synaptics_ncm_soft_reset( struct spi_device *p_spi )
{
	unsigned short 	address = 0;
	u8				val = 0;
	int				rc  = 0;
	synaptics_ncm_data_type *p_ts;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = spi_get_drvdata( p_spi );

	address = (unsigned short)CMD_REG_F01_RMI_CMD00;
	val = F01_RMI_CMD00_RESET;
	rc = rmi_spi_write( p_spi, address, val );

	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: W:[%d]F01_RMI_CMD00 Error!\n",
				__func__,
				address);
		return SYNAPTICS_RTN_ERR;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);

	return 0;
}



static int synaptics_ncm_fw_update_id_rw( synaptics_ncm_data_type *p_ts )
{
	unsigned short 	address = 0;
	u8				val     = 0;
	int				rc      = 0;
	int				rtn     = 0;
	u8				bootloader_id0 = 0;
	u8				bootloader_id1 = 0;

	address = p_ts->f34_flash_query_base + FLASH_REG_OFFSET_F34_FLASH_QUERY00;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	bootloader_id0 = val;






	address = p_ts->f34_flash_query_base + FLASH_REG_OFFSET_F34_FLASH_QUERY01;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	bootloader_id1 = val;






	address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA02_00;
	rc = rmi_spi_write( p_ts->p_spi, address, bootloader_id0 );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F34_FLASH_DATA02_00 write error(%x)! \n",
				__func__,
				address,
				bootloader_id0);
		goto END_ERR;
	}

	address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA02_01;
	rc = rmi_spi_write( p_ts->p_spi, address, bootloader_id1 );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F34_FLASH_DATA02_01 write error(%x)! \n",
				__func__,
				address,
				bootloader_id1);
		goto END_ERR;
	}

	return rtn;

END_ERR:
	rtn = SYNAPTICS_FWUP_RET_ERR;
	return rtn;
}



static int synaptics_ncm_fw_update_dt_write( synaptics_ncm_data_type *p_ts, 
											 const struct firmware *p_fw_entry )
{
	unsigned short 	address   = 0;
	u8				val       = 0;
	int				rc        = 0;
	long			timeout   = 0;
	int				block_num = 0;
	int				data_num  = 0;
	unsigned long	flags     = 0;
	unsigned long	temp_len  = 0;
	unsigned char	status    = 0;
	unsigned long	fw_tatal_size     = 0;
	unsigned long	fw_image_size     = 0;
	unsigned long	config_image_size = 0;
	const u8		*fw_data;
	unsigned long	*temp;
	const u8		*temp_data;
	spinlock_t		spin_lock_state;

	spin_lock_init( &spin_lock_state );

	if( p_fw_entry  == NULL )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: parameter error (fw_data)!\n",__func__);
		return SYNAPTICS_FWUP_RET_ERR;
	}

	if( p_fw_entry->data == NULL )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: parameter error (fw_data->data)!\n",__func__);
		return SYNAPTICS_FWUP_RET_ERR;
	}

	if( p_fw_entry->size == 0 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: parameter error (fw_data->size)!\n",__func__);
		return SYNAPTICS_FWUP_RET_ERR;
	}

	fw_data				= p_fw_entry->data;
	fw_tatal_size		= p_fw_entry->size;

	temp				= (unsigned long *)( fw_data + 8 );
	fw_image_size		= *temp;
	temp				= (unsigned long *)( fw_data + 12 );
	config_image_size	= *temp;

	if( (fw_image_size % 16) || (config_image_size % 16) )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: image size error (%ld/%ld)!\n",__func__,fw_image_size,config_image_size);
		return SYNAPTICS_FWUP_RET_ERR;
	}

	



	temp_data	= fw_data + 256;
	temp_len	= fw_image_size;
	block_num	= 0;






	do { 

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA00;
		val     = (unsigned char)( block_num & 0x00FF ); 
		rc = rmi_spi_write( p_ts->p_spi, address, val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA01;
		val     = (unsigned char)( ( block_num & 0xFF00 ) >> 8 );
		rc = rmi_spi_write( p_ts->p_spi, address, val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
			return SYNAPTICS_FWUP_RET_ERR;
		}
		
		block_num++;

		


		for( data_num = 0; data_num < 16; data_num++,temp_data++)
		{
			address = p_ts->f34_flash_data_base + (unsigned short)(FLASH_REG_OFFSET_F34_FLASH_DATA02_00 + data_num);
			val     = (unsigned char)*(temp_data);





			rc = rmi_spi_write( p_ts->p_spi, address, val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
				return SYNAPTICS_FWUP_RET_ERR;
			}
		}

		


		spin_lock_irqsave( &spin_lock_state, flags );
		g_synaptics_ncm_fwup_condition = 0;
		spin_unlock_irqrestore( &spin_lock_state, flags );

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
		val     = 0x02;
		rc = rmi_spi_write( p_ts->p_spi, address, val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		timeout = wait_event_timeout(g_synaptics_ncm_fwup_wait, g_synaptics_ncm_fwup_condition, SYNAPTICS_TIMEOUT_2000);

		if( timeout == 0 )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: Data Write timeout error 1(%x)! \n", __func__, (unsigned int)timeout );
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			return SYNAPTICS_FWUP_RET_ERR;
		}
		status = val;

		


		address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		if( status != 0x80 )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: Device Status Error(%x)!\n", __func__, status);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		temp_len = temp_len -16;






	}while( temp_len > 0);


	



	temp_data	= fw_data + 256 + fw_image_size;
	temp_len	= config_image_size;
	block_num	= 0;






	do { 

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA00;
		val     = (unsigned char)( block_num & 0x00FF ); 
		rc = rmi_spi_write( p_ts->p_spi, address, val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA01;
		val     = (unsigned char)( ( block_num & 0xFF00 ) >> 8 );
		rc = rmi_spi_write( p_ts->p_spi, address, val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
			return SYNAPTICS_FWUP_RET_ERR;
		}
		
		block_num++;

		


		for( data_num = 0; data_num < 16; data_num++,temp_data++)
		{
			address = p_ts->f34_flash_data_base + (unsigned short)(FLASH_REG_OFFSET_F34_FLASH_DATA02_00 + data_num);
			val     = (unsigned char)*(temp_data);





			rc = rmi_spi_write( p_ts->p_spi, address, val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
				return SYNAPTICS_FWUP_RET_ERR;
			}
		}

		


		spin_lock_irqsave( &spin_lock_state, flags );
		g_synaptics_ncm_fwup_condition = 0;
		spin_unlock_irqrestore( &spin_lock_state, flags );

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
		val     = 0x06;
		rc = rmi_spi_write( p_ts->p_spi, address, val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: W:[%x] %x Error!\n", __func__, address,val);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		timeout = wait_event_timeout(g_synaptics_ncm_fwup_wait, g_synaptics_ncm_fwup_condition, SYNAPTICS_TIMEOUT_2000);

		if( timeout == 0 )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: Data Write timeout error 2(%x)! \n", __func__, (unsigned int)timeout );
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			return SYNAPTICS_FWUP_RET_ERR;
		}
		status = val;

		


		address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		


		if( status != 0x80 )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: Device Status Error(%x)!\n", __func__, status);
			return SYNAPTICS_FWUP_RET_ERR;
		}

		temp_len = temp_len -16;






	}while( temp_len > 0);

	return SYNAPTICS_FWUP_RET_OK;
}



static int synaptics_ncm_fw_update( struct spi_device *p_spi )
{
	unsigned short 	address    = 0;
	u8				val        = 0;
	int				rc         = 0;
	long			timeout    = 0;
	int				regcnt     = 0;
	unsigned long	flags      = 0;
	synaptics_ncm_data_type *p_ts;
	const struct firmware   *p_fw_entry;
	spinlock_t		spin_lock_state;
	unsigned char	hw_rev     = 0;
	unsigned char	fw_rev     = 0;
	int				gpio       = 0;
	int				loop       = 0;
	const u8		*fw_data;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = spi_get_drvdata( p_spi );

	if ( p_ts->hw_rev < 0x00010000 )
	{
		printk(KERN_DEBUG "[synaptics_ncm]%s: VE399 No_Fw_Update\n", __func__);
		return SYNAPTICS_FWUP_RET_OK;
	}

	spin_lock_init( &spin_lock_state );

	spin_lock_irqsave( &spin_lock_state, flags );
	g_synaptics_ncm_fwup_state     = SYNAPTICS_FWUP_STATE_EXEC;
	spin_unlock_irqrestore( &spin_lock_state, flags );

	rc = cancel_work_sync( &p_ts->work );
	if ( rc )
	{
		printk(KERN_DEBUG "[synaptics_ncm]%s: cancel work rc(%x)\n", __func__, rc);
	}

	address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL01_00;
	val     = 0x01;
	rc = rmi_spi_write( p_ts->p_spi, address, val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F01_RMI_CTRL01_00 write error(%x)! \n", __func__, address, val);
		goto END_ERR2;
	}






	rc = request_firmware(&p_fw_entry, "synaptics_fw.img", &p_spi->dev);
	if ( rc != 0 )
	{
		spin_lock_irqsave( &spin_lock_state, flags );
		g_synaptics_ncm_fwup_state     = SYNAPTICS_FWUP_STATE_NONE;
		g_synaptics_ncm_fwup_condition = 0;
		spin_unlock_irqrestore( &spin_lock_state, flags );

		address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL01_00;
		val     = F01_RMI_CTRL01_00_SET_INIT_DAT;
		rc = rmi_spi_write( p_ts->p_spi, address, val );

		address = (unsigned short)BASE_REG_F01_RMI_DATA_BASE;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		p_ts->f01_rmi_data_base = (unsigned short)val;

		address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );

		printk(KERN_ERR "[synaptics_ncm]%s firmware read failed: %x\n", __func__, rc);
		return SYNAPTICS_FWUP_RET_ERR_FW_NO_FILE;
	}

	hw_rev = synaptics_ncm_rev(p_ts->p_spi);

	fw_data = p_fw_entry->data;

	fw_rev = (unsigned char)*(fw_data + 31);
	
	printk(KERN_DEBUG "[synaptics_ncm]%s: hw_rev:%x,fw_rev:%x\n",__func__, hw_rev, fw_rev );
	
	if( hw_rev == fw_rev )
	{
		printk(KERN_DEBUG "[synaptics_ncm]%s: The same firmwares !\n",__func__ );
		spin_lock_irqsave( &spin_lock_state, flags );
		g_synaptics_ncm_fwup_state     = SYNAPTICS_FWUP_STATE_NONE;
		g_synaptics_ncm_fwup_condition = 0;
		spin_unlock_irqrestore( &spin_lock_state, flags );

		release_firmware(p_fw_entry);

		address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL01_00;
		val     = F01_RMI_CTRL01_00_SET_INIT_DAT;
		rc = rmi_spi_write( p_ts->p_spi, address, val );

		address = (unsigned short)BASE_REG_F01_RMI_DATA_BASE;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		p_ts->f01_rmi_data_base = (unsigned short)val;

		address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );

		return SYNAPTICS_FWUP_RET_OK;
	}






	for( regcnt = 0; regcnt < 6; regcnt++ )
	{
		address = (unsigned short)(BASE_REG_F34_FLASH_QUERY_BASE + regcnt);
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			goto END_ERR;
		}

		if ( address == (unsigned short)BASE_REG_F34_FLASH_QUERY_BASE )
		{
			p_ts->f34_flash_query_base = (unsigned short)val;




		}
		else if  ( address == (unsigned short)BASE_REG_F34_FLASH_DATA_BASE )
		{
			p_ts->f34_flash_data_base = (unsigned short)val;




		}
	}

	for( regcnt = 0; regcnt < 6; regcnt++ )
	{
		address = (unsigned short)(BASE_REG_F01_RMI_QUERY_BASE + regcnt);
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			goto END_ERR;
		}

		if  ( address == (unsigned short)BASE_REG_F01_RMI_DATA_BASE )
		{
			p_ts->f01_rmi_data_base = (unsigned short)val;




		}
	}

	for( regcnt = 0; regcnt < 6; regcnt++ )
	{
		address = (unsigned short)(BASE_REG_F11_2D_QUERY_BASE + regcnt);
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			goto END_ERR;
		}
	}

	rc = synaptics_ncm_fw_update_id_rw( p_ts );
	if ( rc == SYNAPTICS_FWUP_RET_ERR )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_fw_update_id_rw error\n", __func__);
		goto END_ERR;
	}

	spin_lock_irqsave( &spin_lock_state, flags );
	g_synaptics_ncm_fwup_condition = 0;
	spin_unlock_irqrestore( &spin_lock_state, flags );

	address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
	val     = 0x0F;
	rc = rmi_spi_write( p_ts->p_spi, address, val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F34_FLASH_DATA03 write error(%x)! \n",
				__func__,
				address,
				val);
		goto END_ERR;
	}

	timeout = wait_event_timeout(g_synaptics_ncm_fwup_wait, g_synaptics_ncm_fwup_condition, SYNAPTICS_TIMEOUT_2000);

	if( timeout == 0 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: ATTN wait timeout error 1(%x)! \n", __func__, (unsigned int)timeout );
		goto END_ERR;
	}






	address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	if ( val != 0x01 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: F01_RMI_DATA01_00 Error(%x)!\n", __func__, val);
		goto END_ERR;
	}

	for( regcnt = 0; regcnt < 6; regcnt++ )
	{
		address = (unsigned short)(BASE_REG_F34_FLASH_QUERY_BASE + regcnt);
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			goto END_ERR;
		}

		if ( address == (unsigned short)BASE_REG_F34_FLASH_QUERY_BASE )
		{
			p_ts->f34_flash_query_base = (unsigned short)val;




		}
		else if  ( address == (unsigned short)BASE_REG_F34_FLASH_DATA_BASE )
		{
			p_ts->f34_flash_data_base = (unsigned short)val;




		}
	}

	for( regcnt = 0; regcnt < 6; regcnt++ )
	{
		address = (unsigned short)(BASE_REG_F01_RMI_QUERY_BASE + regcnt);
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			goto END_ERR;
		}

		if  ( address == (unsigned short)BASE_REG_F01_RMI_DATA_BASE )
		{
			p_ts->f01_rmi_data_base = (unsigned short)val;




		}
	}

	for( regcnt = 0; regcnt < 6; regcnt++ )
	{
		address = (unsigned short)(BASE_REG_F11_2D_QUERY_BASE + regcnt);
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			goto END_ERR;
		}

	}

	address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	if ( val != 0x80 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: F34_FLASH_DATA03 Error(%x)!\n", __func__, val);
		goto END_ERR;
	}

	rc = synaptics_ncm_fw_update_id_rw( p_ts );
	if ( rc == SYNAPTICS_FWUP_RET_ERR )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_fw_update_id_rw error\n", __func__);
		goto END_ERR;
	}

	spin_lock_irqsave( &spin_lock_state, flags );
	g_synaptics_ncm_fwup_condition = 0;
	spin_unlock_irqrestore( &spin_lock_state, flags );






	address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
	val     = 0x03;
	rc = rmi_spi_write( p_ts->p_spi, address, val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F34_FLASH_DATA03 write error(%x)! \n",
				__func__,
				address,
				val);
		goto END_ERR;
	}

	timeout = wait_event_timeout(g_synaptics_ncm_fwup_wait, g_synaptics_ncm_fwup_condition, SYNAPTICS_TIMEOUT_2000);

	if( timeout == 0 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: ATTN wait timeout error 2(%x)! \n", __func__, (unsigned int)timeout );
		goto END_ERR;
	}






	address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	if ( val != 0x01 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: F01_RMI_DATA01_00 Error(%x)!\n", __func__, val);
		goto END_ERR;
	}

	address = p_ts->f34_flash_data_base + FLASH_REG_OFFSET_F34_FLASH_DATA03;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	if ( val != 0x80 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: F34_FLASH_DATA03 Error(%x)!\n", __func__, val);
		goto END_ERR;
	}

	rc = synaptics_ncm_fw_update_dt_write( p_ts, p_fw_entry );
	if ( rc == SYNAPTICS_FWUP_RET_ERR )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_fw_update_dt_write error\n", __func__);
		goto END_ERR;
	}




















	


	gpio_set_value(106, 0);

	mdelay(100);















	p_ts->state   = SYNAPTICS_STATE_NONE;

	


	spin_lock_irqsave( &spin_lock_state, flags );
	g_synaptics_ncm_fwup_condition = 0;
	spin_unlock_irqrestore( &spin_lock_state, flags );

	gpio_set_value(106, 1);

	timeout = wait_event_timeout(g_synaptics_ncm_fwup_wait, g_synaptics_ncm_fwup_condition, SYNAPTICS_TIMEOUT_1000);
	if( timeout == 0 )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: Pow on timeout error 1(%x)! \n", __func__, (unsigned int)timeout );
		goto END_ERR;
	}

	spin_lock_irqsave( &spin_lock_state, flags );
	g_synaptics_ncm_fwup_condition = 0;
	spin_unlock_irqrestore( &spin_lock_state, flags );

	timeout = wait_event_timeout(g_synaptics_ncm_fwup_wait, g_synaptics_ncm_fwup_condition, SYNAPTICS_TIMEOUT_1000);
	if( timeout == 0 )
	{
		printk(KERN_DEBUG "[synaptics_ncm]%s: Pow on timeout(%x)! \n", __func__, (unsigned int)timeout );

		for ( loop = 0; loop < SYNAPTICS_POW_ON_WAIT_LOOP_CNT; loop++ )
		{
			gpio = gpio_get_value(92);
			if ( gpio == 0 )
			{
				printk(KERN_DEBUG "[synaptics_ncm]%s: gpio_vale(%x) OK\n", __func__, gpio );
				break;
			}
			printk(KERN_DEBUG "[synaptics_ncm]%s: gpio_vale(%x) loop(%x)\n", __func__, gpio, loop );
			mdelay(500);
		}

		if ( loop >= SYNAPTICS_POW_ON_WAIT_LOOP_CNT )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: Pow on timeout error 2! \n", __func__);
			goto END_ERR;
		}
	}




















	p_ts->state = SYNAPTICS_STATE_RUN;

	address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	rc = synaptics_ncm_configure( p_ts );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_configure Error!\n",__func__);
		goto END_ERR;
	}

	rc = synaptics_ncm_get_sensor_abs_config( p_ts );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_get_sensor_abs Error!\n",__func__);
		goto END_ERR;
	}

	spin_lock_irqsave( &spin_lock_state, flags );
	g_synaptics_ncm_fwup_state     = SYNAPTICS_FWUP_STATE_NONE;
	spin_unlock_irqrestore( &spin_lock_state, flags );

	if ( ( g_touch_state & SYNAPTICS_INIT_STATE_SUSPEND ) ==
			SYNAPTICS_INIT_STATE_SUSPEND )
	{
		g_touch_state = SYNAPTICS_INIT_STATE_DONE;
		synaptics_ncm_suspend( p_ts->p_spi, PMSG_SUSPEND );
	}

	g_touch_state = SYNAPTICS_INIT_STATE_DONE;






	release_firmware(p_fw_entry);

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return SYNAPTICS_FWUP_RET_OK;

END_ERR:
	release_firmware(p_fw_entry);

END_ERR2:
	spin_lock_irqsave( &spin_lock_state, flags );
	g_synaptics_ncm_fwup_state     = SYNAPTICS_FWUP_STATE_NONE;
	g_synaptics_ncm_fwup_condition = 0;
	spin_unlock_irqrestore( &spin_lock_state, flags );

	address = (unsigned short)SYNAPTICS_CONTROL_BASE_ADDR;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	p_ts->ctl_base = (unsigned short)val;

	address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL01_00;
	val     = F01_RMI_CTRL01_00_SET_INIT_DAT;
	rc = rmi_spi_write( p_ts->p_spi, address, val );

	address = (unsigned short)BASE_REG_F01_RMI_DATA_BASE;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	p_ts->f01_rmi_data_base = (unsigned short)val;

	address = p_ts->f01_rmi_data_base + DATA_REG_OFFSET_F01_RMI_DATA01_00;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );




















	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return SYNAPTICS_FWUP_RET_ERR;
}






































































static int synaptics_ncm_enter_sleep( struct spi_device *p_spi )
{
	unsigned short 	address = 0;
	u8				val = 0;
	int				rc  = 0;
	synaptics_ncm_data_type *p_ts;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = spi_get_drvdata( p_spi );

	val = F01_RMI_CTRL00_ENTER_SLEEP;
	address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL00;

	rc = rmi_spi_write( gp_spi, address, val );

	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: W:[%d]F01_RMI_CTRL00 Error!\n",
				__func__,
				address);
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);

	return rc;
}



static int synaptics_ncm_exit_sleep( struct spi_device *p_spi )
{
	unsigned short 	address = 0;
	u8				val = 0;
	int				rc  = 0;
	synaptics_ncm_data_type *p_ts;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = spi_get_drvdata( p_spi );

	val = F01_RMI_CTRL00_EXIT_SLEEP;
	address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL00;

	rc = rmi_spi_write( gp_spi, address, val );

	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: W:[%d]F01_RMI_CTRL00 Error!\n",
				__func__,
				address);
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);

	return rc;
}



static unsigned char synaptics_ncm_rev( struct spi_device *p_spi )
{
	unsigned short 	address = 0;
	u8				val = 0;
	int				rc  = 0;
	synaptics_ncm_data_type *p_ts;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = spi_get_drvdata( p_spi );

	address = p_ts->f01_rmi_query_base + (unsigned short)QUERY_REG_OFFSET_F01_RMI_QUERY03;
	rc = rmi_spi_read( p_spi, address, &val);

	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%d]Firmware Revision Error!\n",
				__func__,
				address);
		val = SYNAPTICS_RTN_VAL_FF;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Firmware Revision = %x \n",
			__func__,
			val);

	return val;
}



static int synaptics_ncm_power_off( struct spi_device *p_spi )
{

	int		rc  = 0;
	int		ret = 0;
	synaptics_ncm_data_type *p_ts;
	struct synaptics_ncm_platform_data *p_data = p_spi->dev.platform_data;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = spi_get_drvdata( p_spi );

	rc = cancel_work_sync( &p_ts->work );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: cancel work\n", __func__);
		ret = SYNAPTICS_RTN_ERR;
	}

	rc = synaptics_ncm_enter_sleep( p_spi );

	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: enter sleep\n", __func__);
		ret = SYNAPTICS_RTN_ERR;
	}

	disable_irq( p_spi->irq );

	if ( p_data && p_data->poweroff )
	{
		p_data->poweroff( &p_spi->dev );
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);

	return ret;
}



static int synaptics_ncm_configure( synaptics_ncm_data_type *p_ts )
{
	struct spi_device *p_spi;
	unsigned short 	address = 0;
	u8				val  = 0;
	int				rc   = 0;
	int				loop = 0;

	if( p_ts == NULL )
	{
		rc = SYNAPTICS_RTN_ERR;
		goto END_ERR;
	}

	p_spi = p_ts->p_spi;

	
	address = SYNAPTICS_CONTROL_BASE_ADDR;
	rc = rmi_spi_read( p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x Control base address read error! \n",
				__func__,
				address);
		goto END_ERR;
	}
	p_ts->ctl_base = (unsigned short)val;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Control base  : %04x\n", __func__, p_ts->ctl_base);

	address = BASE_REG_F01_RMI_QUERY_BASE;
	rc = rmi_spi_read( p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x RMI Query base address read error! \n",
				__func__,
				address);
		goto END_ERR;
	}
	p_ts->f01_rmi_query_base = (unsigned short)val;

	address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL00;
	val     = F01_RMI_CTRL00_SET_INIT_DAT;
	rc = rmi_spi_write( p_spi, address, val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F01_RMI_CTRL00 write error(%x)! \n",
				__func__,
				address,
				val);
		goto END_ERR;
	}

	address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL01_00;
	val     = F01_RMI_CTRL01_00_SET_INIT_DAT;
	rc = rmi_spi_write( p_spi, address, val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F01_RMI_CTRL01_00 write error(%x)! \n",
				__func__,
				address,
				val);
		goto END_ERR;
	}

	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL02;
	val     = F11_2D_CTRL02_SET_INIT_DAT;
	rc = rmi_spi_write( p_spi, address, val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F01_RMI_CTRL02 write error(%x)! \n",
				__func__,
				address,
				val);
		goto END_ERR;
	}

	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL03;
	val     = F11_2D_CTRL03_SET_INIT_DAT;
	rc = rmi_spi_write( p_spi, address, val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F01_RMI_CTRL03 write error(%x)! \n",
				__func__,
				address,
				val);
		goto END_ERR;
	}

	address = p_ts->ctl_base + CTL_REG_OFFSET_F01_RMI_CTRL00;

	for ( loop = 0; loop < SYNAPTICS_INIT_WAIT_LOOP_CNT; loop++ )
	{
		rc = rmi_spi_read( p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: %04x F01_RMI_CTRL00 read error! \n",
					__func__,
					address);
			goto END_ERR;
		}
		if ( val == F01_RMI_CTRL00_CONF_END )
		{
			printk(KERN_DEBUG "[synaptics_ncm]%s: F01_RMI_CTRL00 OK (%d)\n",
					__func__,
					loop);
			break;
		}
		udelay( SYNAPTICS_INIT_WAIT_TIME );
	}

	if( loop >= SYNAPTICS_INIT_WAIT_LOOP_CNT )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: F01_RMI_CTRL00 wait error!\n",
				__func__);
		rc = SYNAPTICS_RTN_ERR;
	}

END_ERR:
	return rc;
}



static int synaptics_ncm_get_sensor_abs_config( synaptics_ncm_data_type *p_ts )
{
	unsigned short 	address = 0;
	u8				val = 0;
	int				rc  = 0;

	
	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL06;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL06 read error! \n",
				__func__,
				address);
		goto END_ERR;
	}

	p_ts->ss_abs.xxx = (int)val;

	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL07;
	rc = rmi_spi_read(p_ts->p_spi, address, &val);
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL07 read error! \n",
				__func__,
				address);
		goto END_ERR;
	}

	p_ts->ss_abs.xxx += (int)( val << SYNAPTICS_LEFT_SIFT_8 );

	printk(KERN_DEBUG "[synaptics_ncm]%s: SensorMax2D X:%d\n", __func__, p_ts->ss_abs.xxx);

	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL02;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL02 read error! \n",
				__func__,
				address);
		goto END_ERR;
	}

	p_ts->ss_abs.Dx = (int)val;

	printk(KERN_DEBUG "[synaptics_ncm]%s: 2D Delta-X Thresh:%d\n", __func__, p_ts->ss_abs.Dx);

	p_ts->ss_abs.Rx = SYNAPTICS_MAG_X;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Magnification percentage:%d\n",
			__func__,
			p_ts->ss_abs.Rx);

	
	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL08;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL08 read error! \n",
				__func__,
				address);
		goto END_ERR;
	}

	p_ts->ss_abs.yyy = (int)val;

	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL09;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL09 read error! \n",
				__func__,
				address);
		goto END_ERR;
	}

	p_ts->ss_abs.yyy += (int)( val << SYNAPTICS_LEFT_SIFT_8 );

	printk(KERN_DEBUG "[synaptics_ncm]%s: SensorMax2D Y:%d\n", __func__, p_ts->ss_abs.yyy);

	address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL03;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL03 read error! \n",
				__func__,
				address);
		goto END_ERR;
	}

	p_ts->ss_abs.Dy = (int)val;

	printk(KERN_DEBUG "[synaptics_ncm]%s: 2D Delta-Y Thresh:%d\n",
			__func__,
			p_ts->ss_abs.Dy);

	p_ts->ss_abs.Ry = SYNAPTICS_MAG_Y;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Magnification percentage:%d\n",
			__func__,
			p_ts->ss_abs.Ry);

END_ERR:
	return rc;
}



static int synaptics_ncm_key_scan(synaptics_ncm_data_type *p_ts, int x, int y)
{
	int var = 0;

	
	if( (x >= p_ts->hw_key.button0_min_x) && (x <= p_ts->hw_key.button0_max_x)
		&& (y >= p_ts->hw_key.min_y) && (y <= p_ts->hw_key.max_y) )
	{
		var = SYNAPTICS_MODE_BUTTON0;





	}
	else
	{
		
	}

	
	if( (x >= p_ts->hw_key.button1_min_x) && (x <= p_ts->hw_key.button1_max_x)
		&& (y >= p_ts->hw_key.min_y) && (y <= p_ts->hw_key.max_y) )
	{
		var = SYNAPTICS_MODE_BUTTON1;





	}
	else
	{
		
	}

	
	if( (x >= p_ts->hw_key.button2_min_x) && (x <= p_ts->hw_key.button2_max_x)
		&& (y >= p_ts->hw_key.min_y) && (y <= p_ts->hw_key.max_y) )
	{
		var = SYNAPTICS_MODE_BUTTON2;





	}
	else
	{
		
	}

	return var;
}



static u8 synaptics_ncm_key_chg_hw_state(synaptics_ncm_data_type *p_ts)
{
	u8		ret = 0;
	int		key_mode;





	key_mode = p_ts->hw_key_mode;

	
	if( (key_mode & SYNAPTICS_MODE_BUTTON0) && (p_ts->hw_key.key_down[0] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[0] = (u8)SYNAPTICS_KEY_DOWN;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[0], 1);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON0) && (p_ts->hw_key.key_down[0] == (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[0] = (u8)SYNAPTICS_KEY_UP;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[0], 0);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON0) && (p_ts->hw_key.key_down[0] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[0] = (u8)SYNAPTICS_KEY_UP;




	}

	
	if( (key_mode & SYNAPTICS_MODE_BUTTON1) && (p_ts->hw_key.key_down[1] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[1] = (u8)SYNAPTICS_KEY_DOWN;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[1], 1);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON1) && (p_ts->hw_key.key_down[1] == (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[1] = (u8)SYNAPTICS_KEY_UP;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[1], 0);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON1) && (p_ts->hw_key.key_down[1] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[1] = (u8)SYNAPTICS_KEY_UP;




	}

	
	if( (key_mode & SYNAPTICS_MODE_BUTTON2) && (p_ts->hw_key.key_down[2] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[2] = (u8)SYNAPTICS_KEY_DOWN;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[2], 1);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON2) && (p_ts->hw_key.key_down[2] == (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[2] = (u8)SYNAPTICS_KEY_UP;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[2], 0);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON2) && (p_ts->hw_key.key_down[2] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[2] = (u8)SYNAPTICS_KEY_UP;




	}













	return ret;
}



static void synaptics_ncm_abs_report( synaptics_ncm_data_type *p_ts,
									  int x,
									  int y,
									  int wx,
									  int wy,
									  int z )
{





	input_report_abs( p_ts->p_input_dev, ABS_MT_POSITION_X, x );
	input_report_abs( p_ts->p_input_dev, ABS_MT_POSITION_Y, y );
	input_report_abs( p_ts->p_input_dev, ABS_MT_WIDTH_MAJOR, wx > wy ? wx : wy );
	input_report_abs( p_ts->p_input_dev, ABS_MT_TOUCH_MAJOR, z );
	input_mt_sync( p_ts->p_input_dev);




}



static int synaptics_ncm_abs_read( unsigned long status,
								   synaptics_ncm_data_type *p_ts,
								   synaptics_abs_type abs[] )
{
	int				key_mode     = 0;
	unsigned short 	address      = 0;
	unsigned long	finger_state = 0;
	unsigned int 	finger       = 0;
	int				rc    = 0;
	u8	 			val   = 0;
	int				x     = 0;
	int				y     = 0;
	int				x2    = 0;
	int				y2    = 0;
	int				wx    = 0;
	int				wy    = 0;
	int				z     = 0;
	long			work1 = 0;
	long			work2 = 0;





	for ( finger = 0 ; finger < SYNAPTICS_FINGER_NUM ; finger++ )
	{
		x2 = SYNAPTICS_ABS_INIT_VAL;
		y2 = SYNAPTICS_ABS_INIT_VAL;
		wx = SYNAPTICS_ABS_INIT_VAL;
		wy = SYNAPTICS_ABS_INIT_VAL;
		z  = SYNAPTICS_ABS_INIT_VAL;

		finger_state = (unsigned long)( SYNAPTICS_FINGER_STATE_BASE << (finger * 2) );

		if( ( status & finger_state ) | ( status & (finger_state * 2) ) )
		{
			address =
					(unsigned short)(DATA_REG_F11_2D_DATA01_00 +
							( finger * SYNAPTICS_NEXT_FINGER ));









			rc = rmi_spi_read( p_ts->p_spi, address, &val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n",
						__func__,
						address);
				goto END_ERR;
			}
			x = (int)(val << SYNAPTICS_LEFT_SIFT_4);

			rc = rmi_spi_read( p_ts->p_spi, ( address + 0x01 ), &val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n",
						__func__,
						(address + 0x01));
				goto END_ERR;
			}
			y = (int)(val << SYNAPTICS_LEFT_SIFT_4);

			rc = rmi_spi_read( p_ts->p_spi, ( address + 0x02 ), &val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n",
						__func__,
						(address + 0x02));
				goto END_ERR;
			}
			x += (int)(val & SYNAPTICS_MASK_DAT_0F);
			y += (int)(val >> SYNAPTICS_RIGHT_SIFT_4);

			rc = rmi_spi_read( p_ts->p_spi, ( address + 0x03 ), &val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n",
						__func__,
						(address + 0x03));
				goto END_ERR;
			}
			wx = (int)(val & SYNAPTICS_MASK_DAT_0F);
			wy = (int)(val >> SYNAPTICS_RIGHT_SIFT_4);

			rc = rmi_spi_read( p_ts->p_spi, ( address + 0x04 ), &val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n",
						__func__,
						(address + 0x04));
				goto END_ERR;
			}
			z = (int)val;






			if( x )
			{
				work1 = ( (long)x + 1 ) * (SYNAPTICS_LCD_MAX_X - 1);
				work2 = work1 / (long)p_ts->ss_abs.xxx;





				x2 = (int)work2;

				if( x2 > p_ts->abs.max_x )
				{
					x2 = p_ts->abs.max_x;
				}
				else if ( x2 <= 0 )
				{
					x2 = 0;
				}
			}
			else
			{
				x2 = x;
			}

			if( y )
			{
				work1 = ( (long)y + 1 ) * (SYNAPTICS_LCD_MAX_Y - 1);

				if (( p_ts->hw_rev >= 0x00010000 ) && ( p_ts->hw_rev <= 0x00010009 ))
				{
					work2 = work1 / ( (long)p_ts->ss_abs.yyy - SYNAPTICS_KEY_AREA_Y );
				}
				else
				{
					work2 = work1 / (long)p_ts->ss_abs.yyy;
				}






				y2 = (int)work2;

				if( y2 > p_ts->abs.max_y )
				{
					y2 = p_ts->abs.max_y;
				}
				else if ( y2 <= 0 )
				{
					y2 = 0;
				}
			}
			else
			{
				y2 = y;
			}

			if (abs == NULL)
			{
				if (( p_ts->hw_rev >= 0x00010000 ) && ( p_ts->hw_rev <= 0x00010009 ))
				{
					if ( y > SYNAPTICS_TOUCH_FIELD_Y )
					{
						key_mode |= synaptics_ncm_key_scan( p_ts, x, y );
					}
					else
					{
						if( y >= SYNAPTICS_KEY_CANCEL_Y )
						{



							p_ts->key_cancel = 1;
							mod_timer( &g_synaptics_ncm_key_cancel_timer, jiffies + SYNAPTICS_TIMEOUT_KEY_CANCEL );
						}
						synaptics_ncm_abs_report( p_ts, x2, y2, wx, wy, z );
						p_ts->fs[finger] = 1;
					}
				}
				else
				{
					synaptics_ncm_abs_report( p_ts, x2, y2, wx, wy, z );
					p_ts->fs[finger] = 1;
				}
			}
		}
		else
		{
			if (abs == NULL)
			{
				if (p_ts->fs[finger])
				{
					synaptics_ncm_abs_report( p_ts, 0, 0, 0, 0, 0 );
					p_ts->fs[finger] = 0;
				}
			}
		}

		p_ts->finger_scoord[finger].X = x2;
		p_ts->finger_scoord[finger].Y = y2;

		if ( abs != NULL )
		{
			abs[finger].X  = x2;
			abs[finger].Y  = y2;
			abs[finger].Wx = wx;
			abs[finger].Wy = wy;
			abs[finger].Z  = z;























		}
	}
	if ( abs == NULL )
	{
		input_sync ( p_ts->p_input_dev );

		if (( p_ts->hw_rev >= 0x00010000 ) && ( p_ts->hw_rev <= 0x00010009 ))
		{
			p_ts->hw_key_mode = key_mode;

			if( key_mode )
			{
				if( p_ts->key_timer_state == 0 )
				{
					p_ts->key_timer_state = 1;	
					queue_work( gp_synaptics_ncm_key_timer_wq, &p_ts->work_key_timer );
	





				}




			}
		}
	}

END_ERR:





	return rc;
}



static int synaptics_ncm_abs_read_and_report( synaptics_ncm_data_type *p_ts )
{
	unsigned short 	address = 0;
	unsigned long	status  = 0;
	u8				val = 0;
	int				rc  = 0;
	int				cnt = 0;

	address = (unsigned short)DATA_REG_F11_2D_DATA00_00;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	status = (unsigned long)val;

	address = (unsigned short)DATA_REG_F11_2D_DATA00_01;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	status += (unsigned long)(val << SYNAPTICS_LEFT_SIFT_8);

	address = (unsigned short)DATA_REG_F11_2D_DATA09;
	rc = rmi_spi_read( p_ts->p_spi, address, &val );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

















	if (status == 0)
	{
		address = (unsigned short)DATA_REG_F01_RMI_DATA00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
			goto END_ERR;
		}




		switch ( val & SYNAPTICS_MASK_DAT_0F )
		{
			case SYNAPTICS_ERR_RESET_OCCURRED:
				printk(KERN_ERR "[T][ARM]Event:0x45 Info:0x01\n");
				break;
			case SYNAPTICS_ERR_INVALID_CONFIG:
				printk(KERN_ERR "[T][ARM]Event:0x45 Info:0x02\n");
				break;
			case SYNAPTICS_ERR_DEVICE_FAILURE:
				printk(KERN_ERR "[T][ARM]Event:0x45 Info:0x03\n");
				break;
			default:
				break;
		}
	}

	rc = synaptics_ncm_abs_read( status, p_ts, NULL );
	
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: R:[%x] Error!\n", __func__, address);
		goto END_ERR;
	}

	return rc;

END_ERR:
	for ( cnt = 0; cnt < SYNAPTICS_FINGER_NUM; cnt++ )
	{
		if ( p_ts->fs[cnt] )
		{
			synaptics_ncm_abs_report( p_ts, 0, 0, 0, 0, 0 );
		}
		p_ts->fs[cnt] = 0;
	}
	input_sync( p_ts->p_input_dev );

	return rc;
}



static void synaptics_ncm_do_work( struct work_struct *p_work )
{
	synaptics_ncm_data_type *p_ts = container_of( p_work, synaptics_ncm_data_type, work );

	unsigned short 	address = 0;
	u8				val = 0;
	int				rc  = 0;

	u8				dat = 0;






	if ( p_ts->state == SYNAPTICS_STATE_INIT_IRQ2 )
	{

		del_timer_sync( &g_synaptics_ncm_timer );

		rc = cancel_work_sync( &p_ts->work_timer );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: cancel_work_sync Error!\n", __func__);
			goto END_ERR;
		}

		p_ts->state = SYNAPTICS_STATE_RUN;

		address = (unsigned short)DATA_REG_F01_RMI_DATA01_00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[0x0014]F01_RMI_DATA01.00 Interrupt Status Error!\n",
					__func__);
			goto END_ERR;
		}
		printk(KERN_DEBUG "[synaptics_ncm]%s: Interrupt Status:%x\n",
				__func__,
				val);

		rc = synaptics_ncm_configure( p_ts );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_configure Error!\n",
					__func__);
			goto END_ERR;
		}

		rc = synaptics_ncm_get_sensor_abs_config( p_ts );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_get_sensor_abs Error!\n",
					__func__);
			goto END_ERR;
		}

		printk(KERN_DEBUG "[synaptics_ncm]%s: SYNAPTICS_STATE_INIT_IRQ2 > SYNAPTICS_STATE_RUN\n",
				__func__);


		address = (unsigned short)QUERY_REG_F11_2D_QUERY01;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: F11_2D_QUERY01 Read Error \n",
					__func__);
			goto END_ERR;
		}







	}
	else if ( p_ts->state == SYNAPTICS_STATE_RUN )
	{


		if ( g_sensitivity_work != g_sensitivity )
		{
			printk(KERN_DEBUG "[synaptics_ncm]%s: g_sensitivity_work:0x%08x g_sensitivity:0x%08x \n",
					__func__,
					g_sensitivity_work,
					g_sensitivity);
			address = p_ts->ctl_base + CTL_REG_OFFSET_F11_2D_CTRL14;
			if ( g_sensitivity > F11_2D_CTRL14_MAX_VAL )
			{
				dat = F11_2D_CTRL14_MAX_VAL;
			}
			else
			{
				dat = (u8)( g_sensitivity & F11_2D_CTRL14_MAX_VAL );
			}
			rc = rmi_spi_write( p_ts->p_spi, address, dat );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL14 write error(%x)! \n",
						__func__,
						address,
						dat);
				goto END_ERR;
			}
			printk(KERN_DEBUG "[synaptics_ncm]%s: %04x F11_2D_CTRL14 (g_sensitivity:%02x Write) \n",
					__func__,
					address,
					dat);

			rc = rmi_spi_read( p_ts->p_spi, address, &val );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: %04x F11_2D_CTRL14 read error(%x)! \n",
						__func__,
						address,
						val);
				goto END_ERR;
			}
			printk(KERN_DEBUG "[synaptics_ncm]%s: %04x F11_2D_CTRL14 (g_sensitivity:%02x Read) \n",
					__func__,
					address,
					( val & F11_2D_CTRL14_MAX_VAL ));

			g_sensitivity_work = g_sensitivity;
			printk(KERN_DEBUG "[synaptics_ncm]%s: g_sensitivity_work:0x%08x g_sensitivity:0x%08x \n",
					__func__,
					g_sensitivity_work,
					g_sensitivity);
		}

		if ( g_spidelay1_time != g_spidelay1 )
		{
			printk(KERN_DEBUG "[synaptics_ncm]%s: Before g_spidelay1_time:0x%08x g_spidelay1:0x%08x \n",
					__func__,
					g_spidelay1_time,
					g_spidelay1);
			g_spidelay1_time = g_spidelay1;
			printk(KERN_DEBUG "[synaptics_ncm]%s: After  g_spidelay1_time:0x%08x g_spidelay1:0x%08x \n",
					__func__,
					g_spidelay1_time,
					g_spidelay1);
		}

		if ( g_spidelay2_time != g_spidelay2 )
		{
			printk(KERN_DEBUG "[synaptics_ncm]%s: Before g_spidelay2_time:0x%08x g_spidelay2:0x%08x \n",
					__func__,
					g_spidelay2_time,
					g_spidelay2);
			g_spidelay2_time = g_spidelay2;
			printk(KERN_DEBUG "[synaptics_ncm]%s: After  g_spidelay2_time:0x%08x g_spidelay2:0x%08x \n",
					__func__,
					g_spidelay2_time,
					g_spidelay2);
		}


		address = (unsigned short)DATA_REG_F01_RMI_DATA01_00;
		rc = rmi_spi_read( p_ts->p_spi, address, &val );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[0x0014]F01_RMI_DATA01.00 Interrupt Status Error!\n",
					__func__);
			goto END_ERR;
		}

		rc = synaptics_ncm_abs_read_and_report( p_ts );
		if ( rc )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_abs_read_and_report Error!\n",
					__func__);
			goto END_ERR;
		}

		touch_panel_callback( NULL );





		return;

	}

















	if ( ( g_touch_state & SYNAPTICS_INIT_STATE_SUSPEND ) ==
			SYNAPTICS_INIT_STATE_SUSPEND )
	{
		g_touch_state = SYNAPTICS_INIT_STATE_DONE;
		synaptics_ncm_suspend( p_ts->p_spi, PMSG_SUSPEND );
	}

	g_touch_state = SYNAPTICS_INIT_STATE_DONE;





END_ERR:
	return;
}



static irqreturn_t synaptics_ncm_irq( int irq, void *p_dev_id )
{
	wait_queue_head_t   *wq = &g_synaptics_ncm_fwup_wait;

	synaptics_ncm_data_type *p_ts = p_dev_id;





	if ( g_synaptics_ncm_fwup_state == SYNAPTICS_FWUP_STATE_EXEC )
	{




		g_synaptics_ncm_fwup_condition = 1;
		wake_up(wq);
	}
	else
	{
		queue_work( gp_synaptics_ncm_wq, &p_ts->work );
	}





	return IRQ_HANDLED;
}



static int synaptics_ncm_suspend( struct spi_device *p_spi, pm_message_t mesg )
{
	int ret = 0;
	synaptics_ncm_data_type *p_ts;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	if (( g_touch_state != SYNAPTICS_INIT_STATE_DONE) ||
			( g_synaptics_ncm_fwup_state == SYNAPTICS_FWUP_STATE_EXEC ))
	{
		g_touch_state |= SYNAPTICS_INIT_STATE_SUSPEND;
		printk(KERN_DEBUG "[synaptics_ncm]%s: g_touch_state = %d\n",
				__func__,
				g_touch_state);
	}
	else
	{
		disable_irq( p_spi->irq );

		p_ts = spi_get_drvdata( p_spi );

		ret = cancel_work_sync( &p_ts->work );

		if (( p_ts->hw_rev >= 0x00010000 ) && ( p_ts->hw_rev <= 0x00010009 ))
		{
			p_ts->key_timer_state = 0;		
			del_timer_sync( &g_synaptics_ncm_key_timer );
			cancel_work_sync( &p_ts->work_key_timer );
			synaptics_ncm_key_chg_hw_state( p_ts );
		}

		if ( ret )
		{
			printk(KERN_DEBUG "[synaptics_ncm]%s: cancel work ret(%x)\n", __func__, ret);
		}

		ret = synaptics_ncm_enter_sleep( p_spi );

		if ( ret )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: enter sleep NG\n",__func__);
			return ret;
		}
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return 0;
}



static int synaptics_ncm_resume( struct spi_device *p_spi )
{
	int ret = 0;
	synaptics_ncm_data_type *p_ts;
	unsigned short 	address = 0;
	u8				val = 0;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	if ( ( g_touch_state & SYNAPTICS_INIT_STATE_SUSPEND ) ==
			SYNAPTICS_INIT_STATE_SUSPEND )
	{
		g_touch_state ^= SYNAPTICS_INIT_STATE_SUSPEND;
		printk(KERN_DEBUG "[synaptics_ncm]%s: g_touch_state = %d\n",
				__func__,
				g_touch_state);
	}
	else
	{
		p_ts = spi_get_drvdata( p_spi );

		ret = synaptics_ncm_exit_sleep( p_spi );

		if ( ret )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: exit sleep NG\n", __func__);
			return ret;
		}

		enable_irq( p_spi->irq );

		address = (unsigned short)DATA_REG_F01_RMI_DATA01_00;
		ret = rmi_spi_read( p_ts->p_spi, address, &val );




		if ( ret )
		{
			printk(KERN_ERR "[synaptics_ncm]%s: R:[0x0014]F01_RMI_DATA01.00 Interrupt Status Error!\n",
					__func__);
			return ret;
		}
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return 0;
}




static void synaptics_ncm_early_suspend( struct early_suspend *p_h )
{
	synaptics_ncm_data_type *p_ts;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = container_of( p_h, synaptics_ncm_data_type, early_suspend );
	synaptics_ncm_suspend( p_ts->p_spi, PMSG_SUSPEND );

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
}



static void synaptics_ncm_late_resume( struct early_suspend *p_h )
{
	synaptics_ncm_data_type *p_ts;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = container_of( p_h, synaptics_ncm_data_type, early_suspend );
	synaptics_ncm_resume( p_ts->p_spi );

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
}




static synaptics_ncm_data_type* synaptics_ncm_init_data( void )
{
	synaptics_ncm_data_type	*p_ts = NULL;
	int						cnt   = 0;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = kzalloc( sizeof(synaptics_ncm_data_type), GFP_KERNEL );
	if ( p_ts == NULL )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: No memory for synaptics_ncm_data_type\n",
				__func__);
		return NULL;
	}

	p_ts->abs.min_x     = 0;
	p_ts->abs.max_x     = SYNAPTICS_ABS_MAX_X;
	p_ts->abs.min_y     = 0;
	p_ts->abs.max_y     = SYNAPTICS_ABS_MAX_Y;
	p_ts->abs.min_press = 0;
	p_ts->abs.max_press = SYNAPTICS_ABS_MAX_PRESS;

	p_ts->ss_abs.xxx    = 0;
	p_ts->ss_abs.Dx     = 0;
	p_ts->ss_abs.Rx     = 0;
	p_ts->ss_abs.yyy    = 0;
	p_ts->ss_abs.Dy     = 0;
	p_ts->ss_abs.Ry     = 0;

	p_ts->hw_rev = hw_revision_read();
	printk(KERN_DEBUG "[synaptics_ncm]%s: Hardware Revision = 0x%08x\n", __func__, p_ts->hw_rev);

	if( p_ts->hw_rev == HW_REVISION_READ_ERR )
	{
		p_ts->hw_rev = 0x00;  
	}

	if (( p_ts->hw_rev >= 0x00010000 ) && ( p_ts->hw_rev <= 0x00010009 ))
	{
		p_ts->hw_key.button0_min_x = SYNAPTICS_BUTTON0_MIN_X;
		p_ts->hw_key.button0_max_x = SYNAPTICS_BUTTON0_MAX_X;
		p_ts->hw_key.button1_min_x = SYNAPTICS_BUTTON1_MIN_X;
		p_ts->hw_key.button1_max_x = SYNAPTICS_BUTTON1_MAX_X;
		p_ts->hw_key.button2_min_x = SYNAPTICS_BUTTON2_MIN_X;
		p_ts->hw_key.button2_max_x = SYNAPTICS_BUTTON2_MAX_X;
		p_ts->hw_key.min_y         = SYNAPTICS_BUTTON_MIN_Y;
		p_ts->hw_key.max_y         = SYNAPTICS_BUTTON_MAX_Y;
	}
	else
	{
		p_ts->hw_key.button0_min_x = 0;
		p_ts->hw_key.button0_max_x = 0;
		p_ts->hw_key.button1_min_x = 0;
		p_ts->hw_key.button1_max_x = 0;
		p_ts->hw_key.button2_min_x = 0;
		p_ts->hw_key.button2_max_x = 0;
		p_ts->hw_key.min_y         = 0;
		p_ts->hw_key.max_y         = 0;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: abs.min_x     : %d\n",
			__func__,
			p_ts->abs.min_x);
	printk(KERN_DEBUG "[synaptics_ncm]%s: abs.max_x     : %d\n",
			__func__,
			p_ts->abs.max_x);
	printk(KERN_DEBUG "[synaptics_ncm]%s: abs.min_y     : %d\n",
			__func__,
			p_ts->abs.min_y);
	printk(KERN_DEBUG "[synaptics_ncm]%s: abs.max_y     : %d\n",
			__func__,
			p_ts->abs.max_y);
	printk(KERN_DEBUG "[synaptics_ncm]%s: abs.min_press : %d\n",
			__func__,
			p_ts->abs.min_press);
	printk(KERN_DEBUG "[synaptics_ncm]%s: abs.max_press : %d\n",
			__func__,
			p_ts->abs.max_press);

	for ( cnt = 0; cnt < SYNAPTICS_FINGER_NUM; cnt++ )
	{
		p_ts->fs[cnt] = 0;
	}

	p_ts->state = SYNAPTICS_STATE_NONE;
	p_ts->key_cancel = 0;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return p_ts;
}



static int synaptics_ncm_init_input( synaptics_ncm_data_type *p_ts )
{
	int				rc  = 0;
	int 			cnt = 0;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	if (( p_ts->hw_rev >= 0x00010000 ) && ( p_ts->hw_rev <= 0x00010009 ))
	{
		p_ts->hw_key.key_code[0] = KEY_MENU;
		p_ts->hw_key.key_code[1] = KEY_HOME;
		p_ts->hw_key.key_code[2] = KEY_BACK;
		p_ts->hw_key.key_down[0] = (u8)SYNAPTICS_KEY_UP;
		p_ts->hw_key.key_down[1] = (u8)SYNAPTICS_KEY_UP;
		p_ts->hw_key.key_down[2] = (u8)SYNAPTICS_KEY_UP;
	}
	else
	{
		p_ts->hw_key.key_code[0] = 0;
		p_ts->hw_key.key_code[1] = 0;
		p_ts->hw_key.key_code[2] = 0;
		p_ts->hw_key.key_down[0] = 0;
		p_ts->hw_key.key_down[1] = 0;
		p_ts->hw_key.key_down[2] = 0;
	}

	if ( p_ts == NULL )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: failed to synaptics_ncm_data_type\n",
				__func__);
		return SYNAPTICS_RTN_ERR;
	}

	p_ts->p_input_dev = input_allocate_device( );
	if ( p_ts->p_input_dev == NULL )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: failed to allocate touchscreen input device\n",
				__func__);
		return SYNAPTICS_RTN_ERR;
	}

	p_ts->p_input_dev->name = "synaptics_ncm_touchscreen";
	input_set_drvdata( p_ts->p_input_dev, p_ts );

	set_bit( EV_SYN, p_ts->p_input_dev->evbit );
	set_bit( EV_ABS, p_ts->p_input_dev->evbit );
	set_bit( EV_KEY, p_ts->p_input_dev->evbit );

	if (( p_ts->hw_rev >= 0x00010000 ) && ( p_ts->hw_rev <= 0x00010009 ))
	{
		for ( cnt = 0; cnt < SYNAPTICS_BUTTON_NUM; cnt++ )
		{
			set_bit( p_ts->hw_key.key_code[cnt], p_ts->p_input_dev->keybit );
		}
	}

	input_set_abs_params( p_ts->p_input_dev, ABS_MT_POSITION_X,
						  p_ts->abs.min_x, p_ts->abs.max_x, 0, 0 );
	input_set_abs_params( p_ts->p_input_dev, ABS_MT_POSITION_Y,
						  p_ts->abs.min_y, p_ts->abs.max_y, 0, 0 );
	input_set_abs_params( p_ts->p_input_dev, ABS_MT_TOUCH_MAJOR,
						  p_ts->abs.min_press, p_ts->abs.max_press, 0, 0 );
	input_set_abs_params( p_ts->p_input_dev, ABS_MT_WIDTH_MAJOR, 0, 15, 0, 0 );

	rc = input_register_device( p_ts->p_input_dev );


	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return rc;
}



static void synaptics_ncm_key_timer_do_work( struct work_struct *p_work_key_timer )
{
	synaptics_ncm_data_type *p_ts =
			container_of( p_work_key_timer, synaptics_ncm_data_type, work_key_timer );

	int		key_mode;





	key_mode = p_ts->hw_key_mode;

	
	if( (key_mode & SYNAPTICS_MODE_BUTTON0) && (p_ts->hw_key.key_down[0] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[0] = p_ts->hw_key.key_down[0] + 1;

		if( p_ts->hw_key.key_down[0] >= (u8)SYNAPTICS_KEY_DOWN )
		{
			if( p_ts->key_cancel == 0 )
			{
				input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[0], 1);
				input_sync(p_ts->p_input_dev);
			}
			else
			{
				p_ts->hw_key.key_down[0] = SYNAPTICS_KEY_DOWN_CANCEL;
			}



		}
	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON0) && (p_ts->hw_key.key_down[0] == (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[0] = (u8)SYNAPTICS_KEY_UP;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[0], 0);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON0) &&
			  ( (p_ts->hw_key.key_down[0] < (u8)SYNAPTICS_KEY_DOWN) || (p_ts->hw_key.key_down[0] == (u8)SYNAPTICS_KEY_DOWN_CANCEL) ) )
	{
		p_ts->hw_key.key_down[0] = (u8)SYNAPTICS_KEY_UP;




	}

	
	if( (key_mode & SYNAPTICS_MODE_BUTTON1) && (p_ts->hw_key.key_down[1] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[1] = p_ts->hw_key.key_down[1] + 1;

		if( p_ts->hw_key.key_down[1] >= (u8)SYNAPTICS_KEY_DOWN )
		{
			if( p_ts->key_cancel == 0 )
			{
				input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[1], 1);
				input_sync(p_ts->p_input_dev);
			}
			else
			{
				p_ts->hw_key.key_down[1] = SYNAPTICS_KEY_DOWN_CANCEL;
			}




		}
	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON1) && (p_ts->hw_key.key_down[1] == (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[1] = (u8)SYNAPTICS_KEY_UP;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[1], 0);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON1) && 
			  ( (p_ts->hw_key.key_down[1] < (u8)SYNAPTICS_KEY_DOWN) || (p_ts->hw_key.key_down[1] == (u8)SYNAPTICS_KEY_DOWN_CANCEL) ) )
	{
		p_ts->hw_key.key_down[1] = (u8)SYNAPTICS_KEY_UP;




	}

	
	if( (key_mode & SYNAPTICS_MODE_BUTTON2) && (p_ts->hw_key.key_down[2] < (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[2] = p_ts->hw_key.key_down[2] + 1;

		if( p_ts->hw_key.key_down[2] >= (u8)SYNAPTICS_KEY_DOWN )
		{
			if( p_ts->key_cancel == 0 )
			{
				input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[2], 1);
				input_sync(p_ts->p_input_dev);
			}
			else
			{
				p_ts->hw_key.key_down[2] = SYNAPTICS_KEY_DOWN_CANCEL;
			}




		}
	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON2) && (p_ts->hw_key.key_down[2] == (u8)SYNAPTICS_KEY_DOWN) )
	{
		p_ts->hw_key.key_down[2] = (u8)SYNAPTICS_KEY_UP;
		input_report_key(p_ts->p_input_dev, p_ts->hw_key.key_code[2], 0);
		input_sync(p_ts->p_input_dev);




	}
	else if( !(key_mode & SYNAPTICS_MODE_BUTTON2) &&
			  ( (p_ts->hw_key.key_down[2] < (u8)SYNAPTICS_KEY_DOWN) || (p_ts->hw_key.key_down[2] == (u8)SYNAPTICS_KEY_DOWN_CANCEL) ) )
	{
		p_ts->hw_key.key_down[2] = (u8)SYNAPTICS_KEY_UP;




	}

	if( p_ts->key_timer_state && key_mode )
	{
		if( timer_pending( &g_synaptics_ncm_key_timer ) == 0 )
		{
			mod_timer( &g_synaptics_ncm_key_timer, jiffies + SYNAPTICS_TIMEOUT_KEY_DELAY );
		}
	}
	else
	{
		p_ts->key_timer_state = 0;		
	}















}



static void synaptics_ncm_timer_do_work( struct work_struct *p_work_timer )
{
	synaptics_ncm_data_type *p_ts =
			container_of( p_work_timer, synaptics_ncm_data_type, work_timer );
	int	rc = 0;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter p_ts->state:%x\n",
			__func__,
			p_ts->state);
	switch ( p_ts->state )
	{
		case SYNAPTICS_STATE_INIT_IRQ1:
			p_ts->state = SYNAPTICS_STATE_INIT_IRQ2;
			mod_timer( &g_synaptics_ncm_timer, jiffies + SYNAPTICS_TIMEOUT_600 );
			rc = request_irq(
					p_ts->p_spi->irq,
					synaptics_ncm_irq,
					IRQF_TRIGGER_FALLING | IRQF_DISABLED,
					"synaptics_ncm_irq",
					p_ts);
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: request_irq Error! rc:%x\n",
						__func__,
						rc);
			}
			break;
		case SYNAPTICS_STATE_INIT_IRQ2:
			printk(KERN_ERR "[T][ARM]Event:0x46 Info:0x00\n");
			p_ts->state = SYNAPTICS_STATE_NONE;
			rc = synaptics_ncm_power_off( p_ts->p_spi );
			if ( rc )
			{
				printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_power_off Error! rc:%x\n",
						__func__,
						rc);
			}
			break;





		default:
			printk(KERN_ERR "[synaptics_ncm]%s: NG state:%x\n", __func__, p_ts->state);
			break;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit  p_ts->state:%x\n", __func__, p_ts->state);
}



static void synaptics_ncm_timer_handler( unsigned long data )
{
	synaptics_ncm_data_type *p_ts = (synaptics_ncm_data_type *)data;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter p_ts->state:%x\n",
			__func__,
			p_ts->state);

	queue_work( gp_synaptics_ncm_timer_wq, &p_ts->work_timer );

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
}



static void synaptics_ncm_key_timer_handler( unsigned long data )
{
	synaptics_ncm_data_type *p_ts = (synaptics_ncm_data_type *)data;





	queue_work( gp_synaptics_ncm_key_timer_wq, &p_ts->work_key_timer );




}


static void synaptics_ncm_key_cancel_timer_handler( unsigned long data )
{
	synaptics_ncm_data_type *p_ts = (synaptics_ncm_data_type *)data;




	p_ts->key_cancel = 0;

}



static int synaptics_ncm_timer_init( synaptics_ncm_data_type *p_ts )
{
	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	init_timer( &g_synaptics_ncm_timer );

	g_synaptics_ncm_timer.function = synaptics_ncm_timer_handler;
	g_synaptics_ncm_timer.data     = (unsigned long)p_ts;
	g_synaptics_ncm_timer.expires  = jiffies + SYNAPTICS_TIMEOUT_400;

	add_timer( &g_synaptics_ncm_timer );

	init_timer( &g_synaptics_ncm_key_timer );

	g_synaptics_ncm_key_timer.function = synaptics_ncm_key_timer_handler;
	g_synaptics_ncm_key_timer.data     = (unsigned long)p_ts;
	g_synaptics_ncm_key_timer.expires  = jiffies + SYNAPTICS_TIMEOUT_KEY_DELAY;

	init_timer( &g_synaptics_ncm_key_cancel_timer );

	g_synaptics_ncm_key_cancel_timer.function = synaptics_ncm_key_cancel_timer_handler;
	g_synaptics_ncm_key_cancel_timer.data     = (unsigned long)p_ts;
	g_synaptics_ncm_key_cancel_timer.expires  = jiffies + SYNAPTICS_TIMEOUT_KEY_CANCEL;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return 0;
}



static int __devinit synaptics_ncm_probe( struct spi_device *p_spi )
{
	int								rc    = 0;
	synaptics_ncm_data_type			*p_ts = NULL;
	struct synaptics_ncm_platform_data	*p_data = p_spi->dev.platform_data;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = synaptics_ncm_init_data( );
	if ( p_ts == NULL )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_init_data error\n",
				__func__);
		goto END_ERR;
	}
	spi_set_drvdata( p_spi, p_ts );

	rc = synaptics_ncm_init_input( p_ts );
	if ( rc )
	{
		printk(KERN_ERR "[synaptics_ncm]%s: synaptics_ncm_init_input error\n",
				__func__);
		goto END_ERR;
	}

	INIT_WORK( &p_ts->work, synaptics_ncm_do_work );
	INIT_WORK( &p_ts->work_timer, synaptics_ncm_timer_do_work );
	INIT_WORK( &p_ts->work_key_timer, synaptics_ncm_key_timer_do_work );
	p_ts->key_timer_state = 0;
	p_ts->hw_key_mode     = 0;

	p_ts->p_spi = p_spi;

	gp_spi      = p_spi;

	g_touch_state = SYNAPTICS_INIT_STATE_NONE;

	if ( p_data && p_data->setup )
	{
		rc = p_data->setup( &p_spi->dev );
		if ( rc )
		{
			goto END_ERR;
		}
	}

	p_ts->state = SYNAPTICS_STATE_INIT_IRQ1;

	init_waitqueue_head( &g_synaptics_ncm_fwup_wait );

	synaptics_ncm_timer_init( p_ts );


	g_sensitivity_work = g_sensitivity;
	g_spidelay1_time   = g_spidelay1;
	g_spidelay2_time   = g_spidelay2;
















	synaptics_debugfs_init( p_ts );



	p_ts->early_suspend.level   = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
	p_ts->early_suspend.suspend = synaptics_ncm_early_suspend;
	p_ts->early_suspend.resume  = synaptics_ncm_late_resume;
	register_early_suspend( &p_ts->early_suspend );


	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);

	return 0;

END_ERR:

	if ( p_ts != NULL )
	{
		kfree( p_ts );
	}

	return rc;
}



static int __devexit synaptics_ncm_remove( struct spi_device *p_spi )
{
	synaptics_ncm_data_type	*p_ts = NULL;

	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	p_ts = spi_get_drvdata( p_spi );

	del_timer_sync( &g_synaptics_ncm_timer );
	cancel_work_sync( &p_ts->work_timer );

	p_ts->key_timer_state = 0;		
	del_timer_sync( &g_synaptics_ncm_key_timer );
	cancel_work_sync( &p_ts->work_key_timer );

	del_timer_sync( &g_synaptics_ncm_key_cancel_timer );


	synaptics_debugfs_remove( p_ts );


	synaptics_ncm_power_off( p_spi );

	input_unregister_device( p_ts->p_input_dev );
	input_free_device( p_ts->p_input_dev );

	spi_set_drvdata( p_spi, NULL );
	kfree( p_ts );

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return 0;
}



static struct spi_driver synaptics_ncm_driver =
{
	.driver =
	{
		.name = "synaptics_ncm_touchscreen",
		.owner = THIS_MODULE,
	},
	.probe = synaptics_ncm_probe,
	.remove = __devexit_p( synaptics_ncm_remove ),




};



static int __init synaptics_ncm_init( void )
{
	int rc = 0;
	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	gp_synaptics_ncm_wq = create_singlethread_workqueue("gp_synaptics_ncm_wq");
	if ( !gp_synaptics_ncm_wq )
	{
		return -ENOMEM;
	}

	gp_synaptics_ncm_timer_wq = create_singlethread_workqueue("gp_synaptics_ncm_timer_wq");
	if ( !gp_synaptics_ncm_timer_wq )
	{
		destroy_workqueue( gp_synaptics_ncm_wq );
		gp_synaptics_ncm_wq = NULL;
		return -ENOMEM;
	}

	gp_synaptics_ncm_key_timer_wq = create_singlethread_workqueue("gp_synaptics_ncm_key_timer_wq");
	if ( !gp_synaptics_ncm_key_timer_wq )
	{
		destroy_workqueue( gp_synaptics_ncm_wq );
		gp_synaptics_ncm_wq = NULL;
		destroy_workqueue( gp_synaptics_ncm_timer_wq );
		gp_synaptics_ncm_timer_wq = NULL;
		return -ENOMEM;
	}

	rc = spi_register_driver( &synaptics_ncm_driver );
	if ( rc )
	{
		destroy_workqueue( gp_synaptics_ncm_wq );
		gp_synaptics_ncm_wq = NULL;
		destroy_workqueue( gp_synaptics_ncm_timer_wq );
		gp_synaptics_ncm_timer_wq = NULL;
		destroy_workqueue( gp_synaptics_ncm_key_timer_wq );
		gp_synaptics_ncm_key_timer_wq = NULL;
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
	return rc;
}



static void __exit synaptics_ncm_exit( void )
{
	printk(KERN_DEBUG "[synaptics_ncm]%s: Enter\n", __func__);

	spi_unregister_driver( &synaptics_ncm_driver );
	if ( gp_synaptics_ncm_wq )
	{
		destroy_workqueue( gp_synaptics_ncm_wq );
	}
	if ( gp_synaptics_ncm_timer_wq )
	{
		destroy_workqueue( gp_synaptics_ncm_timer_wq );
	}
	if ( gp_synaptics_ncm_key_timer_wq )
	{
		destroy_workqueue( gp_synaptics_ncm_key_timer_wq );
	}

	printk(KERN_DEBUG "[synaptics_ncm]%s: Exit\n", __func__);
}



module_init(synaptics_ncm_init);
module_exit(synaptics_ncm_exit);
MODULE_DESCRIPTION("Qualcomm MSM/QSD Touchscreen controller driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:synaptics_ncm_touchscreen");
