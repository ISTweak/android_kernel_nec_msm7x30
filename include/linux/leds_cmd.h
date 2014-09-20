/**********************************************************************
* File Name: include/linux/leds_cmd.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/


#ifndef __LINUX_LEDS_CMD_H
#define __LINUX_LEDS_CMD_H














#define LEDS_CMD_TYPE_RGB_RED		0x01
#define LEDS_CMD_TYPE_RGB_GREEN		0x02
#define LEDS_CMD_TYPE_RGB_BLUE		0x03
#define LEDS_CMD_TYPE_KEY			0x04
#define LEDS_CMD_TYPE_FLASH			0x05


#define LEDS_CMD_RET_OK				1
#define LEDS_CMD_RET_NG				0


extern unsigned char leds_cmd(unsigned char type, unsigned char val);


#define BD6082GUL_IOCTL_MAGIC 'l'

#define LED_CLASS_WRAPPER_FD_PATH    "/dev/led_class_wrapper"

struct bd6082gul_led_flash_parame {
	char still;
	char video;
	char torch;
};












struct bd6082gul_led_prevent_peeping_parame {
	char prevent_peeping ;
};



#define BD6082GUL_CUSTOM_N40    _IOW(BD6082GUL_IOCTL_MAGIC, 0x40, struct bd6082gul_led_flash_parame *)





#define BD6082GUL_CUSTOM_N43    _IOW(BD6082GUL_IOCTL_MAGIC, 0x43, struct bd6082gul_led_prevent_peeping_parame *)




#endif 
