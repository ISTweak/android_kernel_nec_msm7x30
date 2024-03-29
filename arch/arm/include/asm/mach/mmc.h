/**********************************************************************
* File Name: arch/arm/include/asm/mach/mmc.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/
/*
 *  arch/arm/include/asm/mach/mmc.h
 */
#ifndef ASMARM_MACH_MMC_H
#define ASMARM_MACH_MMC_H

#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>


enum {
	MMC_HOST_INIT = 0,
	MMC_HOST_EXIT,
	MMC_MCLK_ON,
	MMC_MCLK_OFF,
	MMC_CARD_ON,
	MMC_CARD_OFF,
};


#define SDC_DAT1_DISABLE 0
#define SDC_DAT1_ENABLE  1
#define SDC_DAT1_ENWAKE  2
#define SDC_DAT1_DISWAKE 3

struct embedded_sdio_data {
	struct sdio_cis cis;
	struct sdio_cccr cccr;
	struct sdio_embedded_func *funcs;
	int num_funcs;
};

struct mmc_platform_data {
	unsigned int ocr_mask;          
	u32 (*translate_vdd)(struct device *, unsigned int);
	unsigned int (*status)(struct device *);
	unsigned int status_irq;
	struct embedded_sdio_data *embedded_sdio;
	unsigned int sdiowakeup_irq;
	int (*register_status_notify)(void (*callback)(int card_present, void *dev_id), void *dev_id);
	unsigned long irq_flags;
	unsigned long mmc_bus_width;
	int (*wpswitch) (struct device *);
	int dummy52_required;
	unsigned int msmsdcc_fmin;
	unsigned int msmsdcc_fmid;
	unsigned int msmsdcc_fmax;
	bool nonremovable;
	bool pclk_src_dfab;
	int (*cfg_mpm_sdiowakeup)(struct device *, unsigned);
};

#endif
