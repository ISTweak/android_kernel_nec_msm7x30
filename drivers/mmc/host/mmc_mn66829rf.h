/*
 *  linux/drivers/mmc/host/mmc_mn66829rf.h - Panasonic MN66829RF SD Host Controller Driver
 *
 *  Copyright (C) 2010-2011 NEC CASIO Mobile Communications, Ltd.
 *  Copyright (C) 2008 Google, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * - Based on mmci.h
 */

#ifndef _MMC_MN66829RF_H
#define _MMC_MN66829RF_H

#include <linux/wakelock.h>

#define SD_EVENT_ID				0x4E

#define SD_ARM_HW_TIMEOUT		0xE0
#define SD_ARM_CMD_ERROR		0xE1
#define SD_ARM_DATA_ERROR		0xE2
#define SD_ARM_CMD_OVERLAP		0xE3
#define SD_ARM_DATA_OVERLAP		0xE4
#define SD_ARM_IRQ_ERROR		0xE5

#define SD_ARM_CMD2INFO(cmd, acmd)	\
	((acmd)?((cmd)&0x3F)+0x40:((cmd)&0x3F))
#define SD_ARM_LOG(info)	\
	pr_info("[T][ARM]Event:0x%02X Info:0x%02X", SD_EVENT_ID, info)

#define SD_IDLE_TIMEOUT		10000 
#define SD_BUSY_TIMEOUT		 1000 
#define SD_HW_TIMEOUT		 3000 

#define MN_REG_SD_CMD			0x0000
#define MN_REG_SD_ARG0			0x0008
#define MN_REG_SD_ARG1			0x000C
#define MN_REG_SD_STOP			0x0010
#define MN_REG_SD_SECCNT		0x0014
#define MN_REG_SD_RSP0			0x0018
#define MN_REG_SD_RSP1			0x001C
#define MN_REG_SD_RSP2			0x0020
#define MN_REG_SD_RSP3			0x0024
#define MN_REG_SD_RSP4			0x0028
#define MN_REG_SD_RSP5			0x002C
#define MN_REG_SD_RSP6			0x0030
#define MN_REG_SD_RSP7			0x0034
#define MN_REG_SD_INFO1			0x0038
#define MN_REG_SD_INFO2			0x003C
#define MN_REG_SD_INFO1_MASK	0x0040
#define MN_REG_SD_INFO2_MASK	0x0044
#define MN_REG_SD_CLK_CTRL		0x0048
#define MN_REG_SD_SIZE			0x004C
#define MN_REG_SD_OPTION		0x0050
#define MN_REG_SD_ERR_STS1		0x0058
#define MN_REG_SD_ERR_STS2		0x005C
#define MN_REG_SD_BUF			0x0060
#define MN_REG_SOFT_RST			0x01C0
#define MN_REG_VERSION			0x01C4
#define MN_REG_SD_EXT_MODE		0x01E0
#define MN_REG_STANDBY_CTRL		0x01E4
#define MN_REG_SUSPEND_CTRL		0x01E8
#define MN_REG_SET_PLL_FREQ		0x01EC
#define MN_REG_SD_PULLUP		0x01F0


#define SD_CMD_APP_CMD		(1<<6)
#define SD_CMD_RSPTYPE1		(1<<8)
#define SD_CMD_RSPTYPE2		(2<<8)
#define SD_CMD_RSPTYPE3		(3<<8)
#define SD_CMD_RSPTYPE4		(4<<8)
#define SD_CMD_RSPTYPE5		(5<<8)
#define SD_CMD_RSPTYPE6		(6<<8)
#define SD_CMD_RSPTYPE7		(7<<8)
#define SD_CMD_WITH_DATA	(1<<11)
#define SD_CMD_READ_BLK		(1<<12)
#define SD_CMD_MULTI_BLK	(1<<13)


#define SD_STOP_STP			(1<<0)
#define SD_STOP_SEC			(1<<8)


#define SD_RSP_OFFSET		(MN_REG_SD_RSP1-MN_REG_SD_RSP0)


#define SD_INFO1_INFO0		(1<<0)
#define SD_INFO1_INFO2		(1<<2)
#define SD_INFO1_END_MASK	\
	(SD_INFO1_INFO0 | SD_INFO1_INFO2)


#define SD_INFO2_ERR0		(1<<0)
#define SD_INFO2_ERR1		(1<<1)
#define SD_INFO2_ERR2		(1<<2)
#define SD_INFO2_ERR3		(1<<3)
#define SD_INFO2_ERR4		(1<<4)
#define SD_INFO2_ERR5		(1<<5)
#define SD_INFO2_ERR6		(1<<6)
#define SD_INFO2_DAT0		(1<<7)
#define SD_INFO2_BRE		(1<<8)
#define SD_INFO2_BWE		(1<<9)
#define SD_INFO2_IFBSY		(1<<12)
#define SD_INFO2_SCLKDIVEN	(1<<13)
#define SD_INFO2_CBSY		(1<<14)
#define SD_INFO2_ILA		(1<<15)
#define SD_INFO2_BRWE_MASK	(SD_INFO2_BRE | SD_INFO2_BWE)
#define SD_INFO2_ERR_MASK	\
	(SD_INFO2_ERR0 | SD_INFO2_ERR1 | SD_INFO2_ERR2 | SD_INFO2_ERR3 | \
	SD_INFO2_ERR4 | SD_INFO2_ERR5 | SD_INFO2_ERR6 | SD_INFO2_ILA)
#define SD_INFO2_INT_MASK	(SD_INFO2_BRWE_MASK | SD_INFO2_ERR_MASK)


#define SD_INFO1_MASK_MASK	0x0318


#define SD_INFO2_MASK_BRE	(1<<8)
#define SD_INFO2_MASK_BWE	(1<<9)
#define SD_INFO2_MASK_MASK	(SD_INFO2_MASK_BRE | SD_INFO2_MASK_BWE)


#define SD_CLK_CTRL_DIV_2		0x0000
#define SD_CLK_CTRL_DIV_128		0x000A
#define SD_CLK_CTRL_DIV_MASK	0x000F
#define SD_CLK_CTRL_SCLKEN		(1<<8)
#define SD_CLK_CTRL_SDCLKSEL	(1<<10)
#define SD_CLK_CTRL_MASK	(SD_CLK_CTRL_DIV_MASK | SD_CLK_CTRL_SDCLKSEL)


#define SD_BUF_MAX_SIZE		0x0200	


#define SD_OPTION_WIDTH_1	(1<<15)


#define SOFT_RST_MASK		0x0007	


#define SD_EXT_MODE_SDINEN	(1<<2)


#define SET_PLL_FREQ_MASK	0x8004	


#define SD_PULLUP_MASK		0x001F	

#define MMC_MN66829RF_F_MIN		384000
#define MMC_MN66829RF_F_MID		24576000
#define MMC_MN66829RF_F_MAX		49152000

#define DIAG_OFF 0
#define DIAG_ON  1

#define RD_REG(host, reg)	\
	readw((host)->base + MN_REG_##reg)
#define WT_REG(val, host, reg)	\
	writew((val), (host)->base + MN_REG_##reg)

#define PR_DBG(host, fmt, args...)	\
	pr_debug("%s: %s: " fmt "\n", mmc_hostname(host->mmc),	\
			__func__ , args)
#define PR_INF(host, fmt, args...)	\
	pr_info("%s: %s: " fmt "\n", mmc_hostname(host->mmc),	\
			__func__ , args)
#define PR_ERR(host, fmt, args...)	\
	pr_err("%s: %s: " fmt "\n", mmc_hostname(host->mmc),	\
			__func__ , args)

enum {
	SD_CLK_OFF = 0,
	SD_CLK_INITIAL_MODE,
	SD_CLK_DEFAULT_MODE,
	SD_CLK_HIGH_SPEED_MODE,
};

struct mmc_mn66829rf_pio_data {
	struct scatterlist	*sg;
	unsigned int		sg_len;
	unsigned int		sg_off;
};

struct mmc_mn66829rf_curr_req {
	struct mmc_request	*mrq;
	struct mmc_command	*cmd;
	struct mmc_data		*data;
	unsigned int		xfer_size;	
	unsigned int		xfer_remain;	
	unsigned int		data_xfered;
};

struct mmc_mn66829rf_host {
	struct resource		*irqres;
	struct resource		*memres;
	void __iomem		*base;

	struct mmc_host		*mmc;
	unsigned int		eject;
	unsigned int		oldstat;
	unsigned int		suspended;
	unsigned int		acmd_req;	

	struct mmc_mn66829rf_curr_req	curr;
	struct mmc_platform_data	*plat;
	struct mmc_mn66829rf_pio_data	pio;
	struct tasklet_struct 	pio_tlet;
	unsigned int		direction;

	spinlock_t			lock;
	unsigned int		pwr;
	unsigned int		clk;
	unsigned int		bus_width;

	unsigned short		state;
	struct wake_lock	sd_wake_lock;
	struct wake_lock	sdif_wake_lock;
	struct timer_list	req_timer;
	unsigned int		req_flag;
	unsigned int		timer_active;
	unsigned int		timeout_irq;
	unsigned int		sdif_lock_ref;

	struct early_suspend early_suspend;
	unsigned char		pending_resume;
};

struct mmc_mn66829rf_diag {
	struct platform_device	*pdev;
	struct mmc_mn66829rf_host	*host;
	int					state;
	int					count;
};

#endif 
