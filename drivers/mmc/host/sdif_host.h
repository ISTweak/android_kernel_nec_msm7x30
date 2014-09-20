/*
 *  linux/drivers/mmc/host/sdif_host.h - SD card extended interface.
 *
 *  Copyright (C) 2010 NEC CASIO Mobile Communications, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef _SDIF_HOST_H
#define _SDIF_HOST_H

#include "sdif.h"


typedef struct sdif_host_ops {
	int (*power_on)(void *);
	int (*power_off)(void *);
	int (*get_card_info)(sdif_card_info_t *, void *);
	int (*get_state)(unsigned short *, void *);
} sdif_host_ops_t;

typedef struct sdif_host {
	sdif_host_info_t info;
	sdif_host_ops_t  ops;
	void            *host;
} sdif_host_t;


int sdif_host_register(sdif_host_t *sdif_host);
int sdif_host_unregister(sdif_host_t *sdif_host);
int sdif_host_irq(int irq, void *dev_id);

#endif 
