/*
 * include/linux/synaptics_ncm.h
 *
 * - Synaptics Touchscreen RMI4 SPI driver
 *
 * Copyright (C) NEC CASIO Mobile Communications, Ltd.
 *
 */
#ifndef _LINUX_SYNAPTICS_NCM_H
#define _LINUX_SYNAPTICS_NCM_H

struct synaptics_ncm_platform_data {
	int (*setup)(struct device *);
	void (*teardown)(struct device *);
	int (*powerdown)(struct device *);
	int (*poweroff)(struct device *);
};

#endif 
