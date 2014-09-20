/*
 *  linux/drivers/mmc/host/sdif_driver.h - SD card extended interface.
 *
 *  Copyright (C) 2010 NEC CASIO Mobile Communications, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef _SDIF_DRIVER_H
#define _SDIF_DRIVER_H

#include "sdif.h"


typedef struct sdif_driver {
	int (*sdif_irq)(int, void *);
} sdif_driver_t;


int sdif_driver_register(sdif_driver_t *sdif_drv);
int sdif_driver_unregister(sdif_driver_t *sdif_drv);


int sdif_get_host_info(sdif_host_info_t *host_info);
int sdif_get_card_info(sdif_card_info_t *card_info);
int sdif_get_state(unsigned short *state);


int sdif_power_on(void);
int sdif_power_off(void);
int sdif_enable_irq(void);
int sdif_disable_irq(void);

#endif 
