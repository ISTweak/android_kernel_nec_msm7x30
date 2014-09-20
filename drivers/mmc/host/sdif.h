/*
 *  linux/drivers/mmc/host/sdif.h - SD card extended interface.
 *
 *  Copyright (C) 2010 NEC CASIO Mobile Communications, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef _SDIF_H
#define _SDIF_H


#define SDIF_STATE_NOCARD		0x0000
#define SDIF_STATE_EXISTCARD	0x0001
#define SDIF_STATE_STARTINIT	0x0003
#define SDIF_STATE_INITDONE		0x0007
#define SDIF_STATE_SUSPEND		0x4000
#define SDIF_STATE_IOBUSY		0x8000


typedef struct sdif_host_info {
	void __iomem *base;
} sdif_host_info_t;


typedef struct sdif_card_info {
	unsigned long raw_cid[4];	
	unsigned long raw_csd[4];	
	unsigned long raw_scr[2];	
	unsigned short       rca;	
} sdif_card_info_t;


int sdif_lock(void);
int sdif_unlock(void);

#endif 
