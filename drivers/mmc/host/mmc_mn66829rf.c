/*
 *  linux/drivers/mmc/host/mmc_mn66829rf.c - Panasonic MN66829RF SD Host Controller Driver
 *
 *  Copyright (C) 2010-2011 NEC CASIO Mobile Communications, Ltd.
 *  Copyright (C) 2007 Google Inc,
 *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Based on mmci.c
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/highmem.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sdio.h>
#include <linux/scatterlist.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/mutex.h>
#include <linux/pm_runtime.h>
#include <linux/cpufreq.h>
#include <asm/mach/mmc.h>
#include "../card/block.h"
#include "../core/core.h"
#include "sdif_host.h"
#include "mmc_mn66829rf.h"

#define DRIVER_NAME "mmc_mn66829rf"
#define SDIF_NAME	"sdif"



static struct mmc_mn66829rf_diag g_diag = {
	.pdev	= NULL,
	.host	= NULL,
	.state	= DIAG_OFF,
	.count	= 0,
};
static DEFINE_MUTEX(g_diag_lock);

static int mmc_mn66829rf_sdif_power_on(void *addr)
{
	struct mmc_mn66829rf_host *host =
			(struct mmc_mn66829rf_host *) addr;

	int ret = 0;

	if (!host) {
		ret = -EINVAL;
		pr_err("%s: Invalid address!\n", __func__);
		goto out;
	}

	if (host->eject) {
		ret = -ENODEV;
		PR_ERR(host, "No card exist! ret = %d", ret);
		goto out;
	}

	if (host->mmc) {
		mmc_claim_host(host->mmc);
		if (host->pending_resume) {
			PR_INF(host, "pending_resume=%d", host->pending_resume);
			host->pending_resume = 0;
			ret = mmc_resume_host(host->mmc);
		}
		mmc_release_host(host->mmc);
	}

	wake_lock(&host->sdif_wake_lock);

	PR_DBG(host, "End. ret = %d", ret);

out:
	return ret;
}

static int mmc_mn66829rf_sdif_power_off(void *addr)
{
	struct mmc_mn66829rf_host *host =
			(struct mmc_mn66829rf_host *) addr;
	int ret = 0;

	if (!host) {
		ret = -EINVAL;
		pr_err("%s: Invalid address!\n", __func__);
		goto out;
	}

	wake_unlock(&host->sdif_wake_lock);

	PR_DBG(host, "End. ret = %d", ret);

out:
	return ret;
}

static int
mmc_mn66829rf_sdif_get_card_info(sdif_card_info_t *info, void *addr)
{
	struct mmc_mn66829rf_host *host =
			(struct mmc_mn66829rf_host *) addr;
	int ret = 0;

	if (!info || !host || !host->mmc) {
		ret = -EINVAL;
		pr_err("%s: Invalid address!\n", __func__);
		goto out;
	}

	if (!host->mmc->card ||
			!mmc_card_present(host->mmc->card)) {
		ret = -ENODEV;
		PR_ERR(host, "No initialized card! ret = %d", ret);
		goto out;
	}

	memcpy(&info->raw_cid[0],
			&host->mmc->card->raw_cid[0], sizeof(unsigned long)*4);
	memcpy(&info->raw_csd[0],
			&host->mmc->card->raw_csd[0], sizeof(unsigned long)*4);
	memcpy(&info->raw_scr[0],
			&host->mmc->card->raw_scr[0], sizeof(unsigned long)*2);
	info->rca = (unsigned short) host->mmc->card->rca; 

	PR_DBG(host, "End. ret = %d", ret);

out:
	return ret;
}

static int
mmc_mn66829rf_sdif_get_state(unsigned short *state, void *addr)
{
	struct mmc_mn66829rf_host *host =
			(struct mmc_mn66829rf_host *) addr;
	int ret = 0;

	if (!state || !host || !host->mmc) {
		ret = -EINVAL;
		pr_err("%s: Invalid address!\n", __func__);
		goto out;
	}

	*state = SDIF_STATE_NOCARD;

	if (!host->eject) {
		if ((host->state == SDIF_STATE_STARTINIT) &&
				host->mmc->card &&
				mmc_card_present(host->mmc->card)) {
			host->state |= SDIF_STATE_INITDONE;
		}
		*state = host->state;
	}

	PR_DBG(host, "End(state=%08x)", *state);

out:
	return ret;
}

static sdif_host_t sdif_host = {
	.info	= {
		.base	= NULL,
	},
	.ops	= {
		.power_on		= mmc_mn66829rf_sdif_power_on,
		.power_off		= mmc_mn66829rf_sdif_power_off,
		.get_card_info	= mmc_mn66829rf_sdif_get_card_info,
		.get_state		= mmc_mn66829rf_sdif_get_state,
	},
	.host	= NULL,
};

static inline void
mmc_mn66829rf_get_sdif_lock(struct mmc_mn66829rf_host *host)
{
	if (host->sdif_lock_ref == 0) {
		host->sdif_lock_ref++;
		host->state |= SDIF_STATE_IOBUSY;
		sdif_lock();
		wake_lock(&host->sd_wake_lock);
		mmc_claim_host(host->mmc);
		if (host->pending_resume) {
			PR_INF(host, "pending_resume=%d", host->pending_resume);
			host->pending_resume = 0;
			mmc_resume_host(host->mmc);
		}
		mmc_release_host(host->mmc);
	} else {
		host->sdif_lock_ref++;
	}
}

static inline void
mmc_mn66829rf_put_sdif_lock(struct mmc_mn66829rf_host *host)
{
	if (host->sdif_lock_ref > 0) {
		host->sdif_lock_ref--;
		if (host->sdif_lock_ref == 0) {
			wake_unlock(&host->sd_wake_lock);
			sdif_unlock();
			host->state &= ~SDIF_STATE_IOBUSY;
		}
	}
}

static inline void
mmc_mn66829rf_wait_for_busy(struct mmc_mn66829rf_host *host)
{
	u16 sd_info2 = 0;
	unsigned int count = 0;

	do {
		sd_info2 = RD_REG(host, SD_INFO2);
		if ((sd_info2 & SD_INFO2_SCLKDIVEN) &&
				!(sd_info2 & (SD_INFO2_IFBSY | SD_INFO2_CBSY)))
		{
			break;
		}
		PR_DBG(host, "Wait for busy. SD_INFO2 = %04x", sd_info2);
		mdelay(1);
		count++;
	} while (count < SD_BUSY_TIMEOUT);
}

static inline void
mmc_mn66829rf_abort_data(struct mmc_mn66829rf_host *host)
{
	u16 sd_stop = RD_REG(host, SD_STOP);
	WT_REG(sd_stop | SD_STOP_STP, host, SD_STOP);
	WT_REG(sd_stop, host, SD_STOP);
}

static void
mmc_mn66829rf_start_command(struct mmc_mn66829rf_host *host,
			struct mmc_command *cmd)
{
	u16 c = (u16) cmd->opcode;

	PR_DBG(host, "op %02x arg %08x flags %08x",
		cmd->opcode, cmd->arg, cmd->flags);

	
	if (cmd->data) {
		c |= SD_CMD_WITH_DATA;
		if (cmd->data->flags & MMC_DATA_READ) {
			c |= SD_CMD_READ_BLK;
		}
		if (cmd->data->blocks > 1) {
			c |= SD_CMD_MULTI_BLK;
		}
	}

	
	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			c |= SD_CMD_RSPTYPE6;
		} else if (cmd->flags & MMC_RSP_BUSY) {
			c |= SD_CMD_RSPTYPE5;
		} else if (cmd->flags & (MMC_RSP_CRC | MMC_RSP_OPCODE)) {
			c |= SD_CMD_RSPTYPE4;
		} else {
			c |= SD_CMD_RSPTYPE7;
		}
	}

	
	if (host->acmd_req) {
		c |= SD_CMD_APP_CMD;
		host->acmd_req = 0;
		mmc_mn66829rf_put_sdif_lock(host);
	}

	if (host->curr.cmd != NULL) {
		SD_ARM_LOG(SD_ARM_CMD_OVERLAP);
		PR_ERR(host, "Overlapping command requests. %s",
					"host->curr.cmd != NULL");
	}
	host->curr.cmd = cmd;

	WT_REG((u16) cmd->arg, host, SD_ARG0);
	WT_REG((u16)(cmd->arg >> 16), host, SD_ARG1);
	WT_REG(c, host, SD_CMD);
	PR_DBG(host, "SD_CMD = %04x", RD_REG(host, SD_CMD));
	PR_DBG(host, "SD_ARG = %04x%04x",
			RD_REG(host, SD_ARG1), RD_REG(host, SD_ARG0));
}

static void
mmc_mn66829rf_start_data(struct mmc_mn66829rf_host *host,
			struct mmc_data *data)
{
	if (!data) {
		return;
	}

	PR_DBG(host, "%s Size = %u",
			data->flags & MMC_DATA_READ ? "Read" : "Write",
			data->blksz * data->blocks);

	if (host->curr.data != NULL) {
		SD_ARM_LOG(SD_ARM_DATA_OVERLAP);
		PR_ERR(host, "Overlapping data requests. %s",
					"host->curr.data != NULL");
	}

	host->curr.data = data;
	host->curr.xfer_size = data->blksz * data->blocks;
	host->curr.xfer_remain = host->curr.xfer_size;
	host->curr.data_xfered = 0;

	memset(&host->pio, 0, sizeof(host->pio));

	host->pio.sg = data->sg;
	host->pio.sg_len = data->sg_len;
	host->pio.sg_off = 0;

	
	if (data->flags & MMC_DATA_READ) {
		WT_REG(SD_INFO2_MASK_BWE, host, SD_INFO2_MASK);
	} else {
		WT_REG(SD_INFO2_MASK_BRE, host, SD_INFO2_MASK);
	}

	
	WT_REG(data->blksz < SD_BUF_MAX_SIZE ?
			data->blksz : SD_BUF_MAX_SIZE, host, SD_SIZE);

	
	if (data->blocks > 1) {
		WT_REG(data->blocks < host->mmc->max_blk_count ?
				data->blocks : 0, host, SD_SECCNT);
		WT_REG(RD_REG(host, SD_STOP) | SD_STOP_SEC,
				host, SD_STOP);
	} else {
		WT_REG(RD_REG(host, SD_STOP) & ~SD_STOP_SEC,
				host, SD_STOP);
	}
}

static void
mmc_mn66829rf_stop_data(struct mmc_mn66829rf_host *host)
{
	host->curr.data = NULL;
	WT_REG(0, host, SD_STOP);
	WT_REG(0, host, SD_SECCNT);
	WT_REG(SD_INFO2_MASK_MASK, host, SD_INFO2_MASK);

	PR_DBG(host, "%s END", "R/W");
}

static int
mmc_mn66829rf_request_end(struct mmc_mn66829rf_host *host,
			struct mmc_request *mrq)
{
	int ret = 0;

	BUG_ON(host->curr.data);

	if (!(host->state & SDIF_STATE_IOBUSY)) {
		PR_INF(host, "Already handled. ret = %d", ret);
		goto out;
	}

	if (host->timer_active) {
		host->timer_active = 0;
		del_timer(&host->req_timer);
	}

	host->curr.mrq = NULL;
	host->curr.cmd = NULL;

	if (mrq->data) {
		mrq->data->bytes_xfered = host->curr.data_xfered;
	}
	if (mrq->cmd->error == -ETIMEDOUT) {
		mdelay(5);
	}

	host->req_flag = 0;

	spin_unlock(&host->lock);
	mmc_request_done(host->mmc, mrq);
	spin_lock(&host->lock);
	mmc_mn66829rf_put_sdif_lock(host);

out:
	return ret;
}

static void
mmc_mn66829rf_data_err(struct mmc_mn66829rf_host *host,
		struct mmc_data *data, u16  status)
{
	u16 sd_err_sts1 = RD_REG(host, SD_ERR_STS1);
	u16 sd_err_sts2 = RD_REG(host, SD_ERR_STS2);
	PR_DBG(host, "SD_ERR_STS1 = %04x, SD_ERR_STS2 = %04x",
				sd_err_sts1, sd_err_sts2);

	if (status & SD_INFO2_ERR0) {
		PR_ERR(host, "Command error. status=0x%04x",
					status);
		data->error = -EILSEQ;
	} else if (status & SD_INFO2_ERR1) {
		PR_ERR(host, "Data CRC error. status=0x%04x",
					status);
		PR_ERR(host, "opcode 0x%.8x",
				data->mrq->cmd->opcode);
		PR_ERR(host, "blksz %d, blocks %d",
				data->blksz, data->blocks);
		data->error = -EILSEQ;
	} else if (status & SD_INFO2_ERR2) {
		PR_ERR(host, "END bit error. status=0x%04x",
					status);
		data->error = -EIO;
	} else if (status & SD_INFO2_ERR3) {
		if (!(data->mrq->cmd->opcode == MMC_BUSTEST_W
			|| data->mrq->cmd->opcode == MMC_BUSTEST_R)) {
			PR_ERR(host, "Other cause timeout. status=0x%04x",
						status);
			mmc_mn66829rf_abort_data(host);
			data->error = -ETIMEDOUT;
		}
	} else if (status & SD_INFO2_ERR4) {
		PR_ERR(host, "Illegal write error. status=0x%04x",
					status);
		data->error = -EIO;
	} else if (status & SD_INFO2_ERR5) {
		PR_ERR(host, "Illegal read error. status=0x%04x",
					status);
		data->error = -EIO;
	} else if (status & SD_INFO2_ERR6) {
		PR_ERR(host, "Response timeout. status=0x%04x",
					status);
		mmc_mn66829rf_abort_data(host);
		data->error = -ETIMEDOUT;
	} else if (status & SD_INFO2_ILA) {
		PR_ERR(host, "Illegal access error. status=0x%04x",
					status);
		data->error = -EIO;
	} else {
		PR_ERR(host, "Unknown Data error (0x%.8x)",
					status);
		data->error = -EIO;
	}
}

static void
mmc_mn66829rf_cmd_err(struct mmc_mn66829rf_host *host,
		struct mmc_command *cmd, u16  status)
{
	u16 sd_err_sts1 = RD_REG(host, SD_ERR_STS1);
	u16 sd_err_sts2 = RD_REG(host, SD_ERR_STS2);
	PR_DBG(host, "SD_ERR_STS1 = %04x, SD_ERR_STS2 = %04x",
				sd_err_sts1, sd_err_sts2);

	if (status & SD_INFO2_ERR6) {




		cmd->error = -ETIMEDOUT;
	} else if (status & SD_INFO2_ERR2) {
		PR_ERR(host, "END bit error. status=0x%04x",
					status);
		cmd->error = -EIO;
	} else if (status & SD_INFO2_ERR1 &&
				cmd->flags & MMC_RSP_CRC) {
		PR_ERR(host, "Command CRC error. status=0x%04x",
					status);
		cmd->error = -EILSEQ;
	} else if (status & (SD_INFO2_ERR0 | SD_INFO2_ERR3 |
				SD_INFO2_ERR4 | SD_INFO2_ERR5 | SD_INFO2_ILA)) {
		PR_ERR(host, "Command I/O error. status=0x%04x",
					status);
		cmd->error = -EIO;
	} else {
		PR_ERR(host, "Unknown Command error(0x%.8x)",
					status);
	}
}

static void
mmc_mn66829rf_set_timer(struct mmc_mn66829rf_host *host)
{
	unsigned int timeout_ms = SD_HW_TIMEOUT;

	PR_DBG(host, "timeout_ms = %u", timeout_ms);

	host->timer_active = 1;
	host->mmc->timer = timeout_ms;
	mod_timer(&host->req_timer,
				jiffies + msecs_to_jiffies(timeout_ms));
}

static void
mmc_mn66829rf_pio(unsigned long data)
{
	struct mmc_mn66829rf_host *host = (struct mmc_mn66829rf_host *)data;
	unsigned long flags;
	unsigned int remain, len, direction;
	char *buffer;
	u16 *ptr;
	u16 sd_size = RD_REG(host, SD_SIZE);

	if (!host || (host->direction != MMC_DATA_READ &&
					host->direction != MMC_DATA_WRITE)) {
		pr_err("%s: failed.\n", __func__);
		return;
	}

	direction = host->direction;
	host->direction = 0;

	PR_DBG(host, "START. direction = %u", direction);

	if (sd_size > host->curr.xfer_remain) {
		PR_DBG(host, "sd_size(%04x) > xfer_remain(%04x)",
				sd_size, host->curr.xfer_remain);
		sd_size = host->curr.xfer_remain;
	}

	if (sd_size & 1) { 
		
		sd_size ++;
	}

	while (sd_size > 0 && host->pio.sg) {
		
		local_irq_save(flags);
		buffer = kmap_atomic(sg_page(host->pio.sg),
					KM_BIO_SRC_IRQ) + host->pio.sg->offset;
		buffer += host->pio.sg_off;
		remain = host->pio.sg->length - host->pio.sg_off;

		if (remain & 1) { 
			
			remain ++;
		}

		PR_DBG(host, "sd_size = %04x, remain = %04x",
					sd_size, remain);

		len = 0;
		ptr = (u16 *) buffer;
		if (direction == MMC_DATA_READ) {
			while (len < sd_size && remain > 0 && ptr) {
				*ptr = RD_REG(host, SD_BUF);
				
				ptr ++;
				len += sizeof(u16);
				remain -= sizeof(u16);
			}
		} else {
			while (len < sd_size && remain > 0 && ptr) {
				WT_REG(*ptr, host, SD_BUF);
				
				ptr ++;
				len += sizeof(u16);
				remain -= sizeof(u16);
			}
		}

		
		

		
		kunmap_atomic(buffer, KM_BIO_SRC_IRQ);
		local_irq_restore(flags);

		host->pio.sg_off += len;
		host->curr.xfer_remain -= len;
		host->curr.data_xfered += len;

		if (remain) {
			break;
		}

		if (direction == MMC_DATA_READ) {
			flush_dcache_page(sg_page(host->pio.sg));
		}

		if (!--host->pio.sg_len) {
			memset(&host->pio, 0, sizeof(host->pio));
			break;
		}

		
		host->pio.sg++;
		host->pio.sg_off = 0;

		sd_size -= len;
	}

	PR_DBG(host, "END. direction = %u", direction);
	return;
}

static irqreturn_t mmc_mn66829rf_irq(int irq, void *dev_id)
{
	struct mmc_mn66829rf_host	*host = dev_id;
	u16			sd_info1, sd_info2;
	u16			sd_info1_mask, sd_info2_mask;
	u16			resp[8];
	irqreturn_t	ret;
	int			i;

	PR_DBG(host, "Start(irq=%d)", irq);
	spin_lock(&host->lock);

	ret = sdif_host_irq(irq, dev_id);
	if (ret == IRQ_HANDLED) {
		PR_DBG(host, "SDIF Handled! ret = %d", ret);
		if (host->curr.cmd != NULL || host->curr.data != NULL) {
			SD_ARM_LOG(SD_ARM_IRQ_ERROR);
			PR_ERR(host, "IRQ Error. %s", "Illegal assignment!");
		}
		goto out;
	}

	do {
		struct mmc_command *cmd = host->curr.cmd;
		struct mmc_data *data = host->curr.data;
		ret = IRQ_HANDLED;

		sd_info1 = RD_REG(host, SD_INFO1);
		sd_info2 = RD_REG(host, SD_INFO2);
		sd_info1_mask = RD_REG(host, SD_INFO1_MASK);
		sd_info2_mask = RD_REG(host, SD_INFO2_MASK);
		PR_DBG(host, "SD_INFO1 = %04x, SD_INFO2 = %04x",
				sd_info1, sd_info2);
		PR_DBG(host, "SD_INFO1_MASK = %04x, SD_INFO2_MASK = %04x",
				sd_info1_mask, sd_info2_mask);

		sd_info1 &= ~sd_info1_mask;
		sd_info2 &= ~sd_info2_mask;
		WT_REG(~sd_info1, host, SD_INFO1);
		WT_REG(~sd_info2, host, SD_INFO2);

		if (!host->req_flag) {
			host->timeout_irq = 0;
			PR_DBG(host, "Already handled. ret = %d", ret);
			break;
		}

		mmc_mn66829rf_set_timer(host);

		
		if (sd_info2 & SD_INFO2_ERR_MASK) {
			host->timeout_irq = 0;
			
			if (data) {
				mmc_mn66829rf_data_err(host, data, sd_info2);

				if (data->error) {
					SD_ARM_LOG(SD_ARM_CMD2INFO(data->mrq->cmd->opcode,
											host->acmd_req));
					
					if (host->acmd_req) {
						host->acmd_req = 0;
						mmc_mn66829rf_put_sdif_lock(host);
					}
					host->curr.data_xfered = 0;
					mmc_mn66829rf_stop_data(host);
					mmc_mn66829rf_request_end(host, data->mrq);
					break;
				}
			} else if (cmd) {
				mmc_mn66829rf_cmd_err(host, cmd, sd_info2);

				if (cmd->error) {
					if (cmd->error != -ETIMEDOUT) {
						SD_ARM_LOG(SD_ARM_CMD2INFO(cmd->opcode,
												host->acmd_req));
						
					}
					if (host->acmd_req) {
						host->acmd_req = 0;
						mmc_mn66829rf_put_sdif_lock(host);
					}
					host->curr.data = NULL;
					mmc_mn66829rf_request_end(host, cmd->mrq);
					break;
				}
			}
			sd_info2 &= ~SD_INFO2_ERR_MASK;
		}

		
		if (sd_info1 & SD_INFO1_INFO0) {
			host->timeout_irq = 0;
			if (cmd && cmd->flags & MMC_RSP_PRESENT) {
				if (cmd->flags & MMC_RSP_136) {
					for (i = 0; i < 8; i++) {
						resp[i] = RD_REG(host, SD_RSP0
								+ SD_RSP_OFFSET*i);
					}

					cmd->resp[0] = ((u32)resp[7] << 24)
							| (resp[6] << 8) | (resp[5] >> 8);
					cmd->resp[1] = ((u32)resp[5] << 24)
							| (resp[4] << 8) | (resp[3] >> 8);
					cmd->resp[2] = ((u32)resp[3] << 24)
							| (resp[2] << 8) | (resp[1] >> 8);
					cmd->resp[3] = ((u32)resp[1] << 24)
							| (resp[0] << 8);
					PR_DBG(host, "resp[0] = %08x", cmd->resp[0]);
					PR_DBG(host, "resp[1] = %08x", cmd->resp[1]);
					PR_DBG(host, "resp[2] = %08x", cmd->resp[2]);
					PR_DBG(host, "resp[3] = %08x", cmd->resp[3]);
				} else {
					for (i = 0; i < 2; i++) {
						resp[i] = RD_REG(host,
									SD_RSP0 + SD_RSP_OFFSET*i);
					}

					cmd->resp[0] = ((u32)resp[1] << 16) | resp[0];
					PR_DBG(host, "resp[0] = %08x", cmd->resp[0]);
				}

				
				if ((cmd->opcode == MMC_APP_CMD) &&
						(cmd->resp[0] & R1_APP_CMD)) {
					host->acmd_req = 1;
					mmc_mn66829rf_get_sdif_lock(host);
					PR_DBG(host, "Next command is ACMD. acmd_req=%d",
								host->acmd_req);
				}
			}

			if (cmd && !cmd->data) {
				mmc_mn66829rf_request_end(host, cmd->mrq);
				break;
			}

			host->curr.cmd = NULL;
			sd_info1 &= ~SD_INFO1_INFO0;
		}

		
		if (sd_info2 & SD_INFO2_BRWE_MASK) {
			host->timeout_irq = 0;
			if (sd_info2 & SD_INFO2_BRE) {
				host->direction = MMC_DATA_READ;
			} else {
				host->direction = MMC_DATA_WRITE;
			}

			
			mmc_mn66829rf_pio((unsigned long) host);
			sd_info2 &= ~SD_INFO2_BRWE_MASK;
		}

		
		if (sd_info1 & SD_INFO1_INFO2) {
			host->timeout_irq = 0;
			mmc_mn66829rf_stop_data(host);
			if (data) {
				mmc_mn66829rf_request_end(host, data->mrq);
				break;
			}
			sd_info1 &= ~SD_INFO1_INFO2;
		}

	} while ((sd_info1 & SD_INFO1_END_MASK) ||
				(sd_info2 & SD_INFO2_INT_MASK));

out:
	spin_unlock(&host->lock);
	PR_DBG(host, "End(irq=%d)", irq);

	return ret;
}

static void mmc_mn66829rf_timeout(unsigned long addr)
{
	struct mmc_mn66829rf_host *host =
				(struct mmc_mn66829rf_host *) addr;
	struct mmc_command *cmd = host->curr.cmd;
	struct mmc_data *data = host->curr.data;

	pr_err("%s: Hardware timeout.", __func__);
	SD_ARM_LOG(SD_ARM_HW_TIMEOUT);

	spin_lock(&host->lock);

	if (!host->timer_active) {
		goto out;
	}

	PR_INF(host, "SD_INFO1 = %04x, SD_INFO2 = %04x, "
			"SD_INFO1_MASK = %04x, SD_INFO2_MASK = %04x",
			RD_REG(host, SD_INFO1), RD_REG(host, SD_INFO2),
			RD_REG(host, SD_INFO1_MASK), RD_REG(host, SD_INFO2_MASK));

	host->timer_active = 0;
	host->timeout_irq = 1;

	spin_unlock(&host->lock);

	mmc_mn66829rf_irq(0, (void *)host);
	if (!host->timeout_irq) {
		PR_INF(host, "Recovered. timeout_irq = %d", host->timeout_irq);
		return;
	}

	spin_lock(&host->lock);

	if (host->timer_active) {
		host->timer_active = 0;
		del_timer(&host->req_timer);
	}

	
	host->oldstat = 0;
	host->eject = !host->oldstat;
	mmc_detect_change(host->mmc, 0);
	mmc_err_info_set();

	if (host->acmd_req) {
		host->acmd_req = 0;
		mmc_mn66829rf_put_sdif_lock(host);
		pr_err("%s: ACMD requested", __func__);
	}

	if (data) {
		pr_err("%s: timeout CMD: 0x%02X", __func__, data->mrq->cmd->opcode);
		data->error = -ETIME;
		data->mrq->cmd->retries = 0;
		host->curr.data_xfered = 0;
		mmc_mn66829rf_abort_data(host);
		mmc_mn66829rf_stop_data(host);
		mmc_mn66829rf_request_end(host, data->mrq);
	} else if (cmd) {
		pr_err("%s: timeout CMD: 0x%02X", __func__, cmd->opcode);
		cmd->error = -ETIME;
		cmd->retries = 0;
		mmc_mn66829rf_request_end(host, cmd->mrq);
	}

out:
	spin_unlock(&host->lock);
}

static void
mmc_mn66829rf_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);
	unsigned long		flags;
	struct cpufreq_policy policy;

	if (host->eject) {
		mrq->cmd->error = -ENOMEDIUM;
		mmc_request_done(mmc, mrq);
		return;
	}

	if (host->pwr != MMC_CARD_ON) {
		if (!host->pending_resume) {
			mrq->cmd->error = -EFAULT;
			mmc_request_done(mmc, mrq);
			return;
		}
	}

	mmc_mn66829rf_get_sdif_lock(host);
	spin_lock_irqsave(&host->lock, flags);

	
	host->req_flag = 1;

	WT_REG(SD_INFO1_MASK_MASK, host, SD_INFO1_MASK);
	WT_REG(SD_INFO2_MASK_MASK, host, SD_INFO2_MASK);

	host->curr.mrq = mrq;
	mmc_mn66829rf_set_timer(host);
	mmc_mn66829rf_start_data(host, mrq->data);
	mmc_mn66829rf_start_command(host, mrq->cmd);

	spin_unlock_irqrestore(&host->lock, flags);

	if (mrq->data) {
		if (cpufreq_get_policy(&policy, 0)) {
			PR_ERR(host, "failed: %s", "cpufreq_get_policy");
		} else {
			__cpufreq_driver_target(&policy, policy.max, CPUFREQ_RELATION_H);
			PR_DBG(host, "cpufreq = %u", policy.max);
		}
	}
}

static void
mmc_mn66829rf_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);
	unsigned long flags;
	unsigned int rc = 0, pwr = 0, clk = 0;
	u16 sd_clk_ctrl = 0;
	int is_err_occur = 0;

	PR_DBG(host, "ios->power_mode = %u, host->pwr = %u",
				ios->power_mode, host->pwr);
	PR_DBG(host, "ios->clock = %u, host->clk = %u",
				ios->clock, host->clk);
	PR_DBG(host, "ios->bus_width = %u, host->bus_width = %u",
				ios->bus_width, host->bus_width);

	if (!host->plat->translate_vdd) {
		return;
	}

	if (ios->bus_width != host->bus_width) {
		spin_lock_irqsave(&host->lock, flags);
		if (ios->bus_width == MMC_BUS_WIDTH_4) {
			WT_REG(RD_REG(host, SD_OPTION) & ~SD_OPTION_WIDTH_1,
					host, SD_OPTION);
			host->bus_width = MMC_BUS_WIDTH_4;
		} else {
			WT_REG(RD_REG(host, SD_OPTION) | SD_OPTION_WIDTH_1,
					host, SD_OPTION);
			host->bus_width = MMC_BUS_WIDTH_1;
		}
		PR_DBG(host, "SD_OPTION = %04x", RD_REG(host, SD_OPTION));
		spin_unlock_irqrestore(&host->lock, flags);
	}

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		pwr = MMC_CARD_OFF;
		if (host->pwr != pwr) {
			mmc_mn66829rf_wait_for_busy(host);

			spin_lock_irqsave(&host->lock, flags);
			sd_clk_ctrl = RD_REG(host, SD_CLK_CTRL)
					& ~SD_CLK_CTRL_SCLKEN;
			WT_REG(sd_clk_ctrl, host, SD_CLK_CTRL);
			WT_REG(sd_clk_ctrl & ~SD_CLK_CTRL_MASK,
					host, SD_CLK_CTRL);
			PR_DBG(host, "SD_CLK_CTRL = %04x",
					RD_REG(host, SD_CLK_CTRL));
			WT_REG(RD_REG(host, SD_EXT_MODE) & ~SD_EXT_MODE_SDINEN,
					host, SD_EXT_MODE);
			PR_DBG(host, "SD_EXT_MODE = %04x",
					RD_REG(host, SD_EXT_MODE));
			spin_unlock_irqrestore(&host->lock, flags);

			rc = host->plat->translate_vdd(mmc_dev(mmc), pwr);
			if (rc) {
				PR_ERR(host, "translate_vdd(pwr) = %d ", rc);
			}

			spin_lock_irqsave(&host->lock, flags);
			if (!host->suspended) {
				host->suspended = 1;
				WT_REG(host->suspended, host, SUSPEND_CTRL);
				host->state |= SDIF_STATE_SUSPEND;
			}
			spin_unlock_irqrestore(&host->lock, flags);
			udelay(10);

			rc = host->plat->translate_vdd(mmc_dev(mmc), MMC_MCLK_OFF);
			if (rc) {
				PR_ERR(host, "translate_vdd(clk) = %d ", rc);
			}

			host->pwr = pwr;
			host->clk = SD_CLK_OFF;
			mdelay(10);
		}
		break;

	case MMC_POWER_ON:
		pwr = MMC_CARD_ON;

		mmc_err_info_get(&is_err_occur);
		if (is_err_occur) {
			PR_ERR(host,
					"Broken SD card. Power on blocked. err=%d",
					is_err_occur);
			break;
		}

		if (ios->clock >= host->mmc->f_max) {
			clk = SD_CLK_HIGH_SPEED_MODE;
		} else if (ios->clock > host->mmc->f_min) {
			clk = SD_CLK_DEFAULT_MODE;
		} else if (ios->clock > 0) {
			clk = SD_CLK_INITIAL_MODE;
		} else {
			PR_ERR(host,
					"Requested power on, but clock is off(%d).",
					ios->clock);
			break;
		}

		if (host->pwr != pwr) {
			if (host->suspended) {
				rc = host->plat->translate_vdd(mmc_dev(mmc), MMC_MCLK_ON);
				if (rc) {
					PR_ERR(host, "translate_vdd(clk) = %d ", rc);
				}
				spin_lock_irqsave(&host->lock, flags);
				host->suspended = 0;
				WT_REG(host->suspended, host, SUSPEND_CTRL);
				spin_unlock_irqrestore(&host->lock, flags);

				udelay(50);
			}

			rc = host->plat->translate_vdd(mmc_dev(mmc), pwr);
			if (rc) {
				PR_ERR(host, "translate_vdd(pwr) = %d ", rc);
			}
			msleep(250);

			spin_lock_irqsave(&host->lock, flags);
			WT_REG(RD_REG(host, SD_EXT_MODE)
					| SD_EXT_MODE_SDINEN,
					host, SD_EXT_MODE);
			PR_DBG(host, "SD_EXT_MODE = %04x",
					RD_REG(host, SD_EXT_MODE));

			WT_REG(RD_REG(host, SD_CLK_CTRL)
					| SD_CLK_CTRL_SCLKEN
					| SD_CLK_CTRL_DIV_128,
					host, SD_CLK_CTRL);
			PR_DBG(host, "SD_CLK_CTRL = %04x",
					RD_REG(host, SD_CLK_CTRL));

			host->pwr = pwr;
			host->clk = SD_CLK_INITIAL_MODE;
			spin_unlock_irqrestore(&host->lock, flags);
		}

		if (clk != SD_CLK_OFF && clk != host->clk) {
			mmc_mn66829rf_wait_for_busy(host);

			spin_lock_irqsave(&host->lock, flags);
			
			sd_clk_ctrl = RD_REG(host, SD_CLK_CTRL)
					& ~SD_CLK_CTRL_SCLKEN;
			WT_REG(sd_clk_ctrl, host, SD_CLK_CTRL);

			
			if (clk == SD_CLK_HIGH_SPEED_MODE) {
				
				sd_clk_ctrl |= SD_CLK_CTRL_SDCLKSEL;
			} else {
				
				sd_clk_ctrl &= ~SD_CLK_CTRL_SDCLKSEL;
			}

			
			sd_clk_ctrl &= ~SD_CLK_CTRL_DIV_MASK;
			if (clk == SD_CLK_INITIAL_MODE) {
				
				sd_clk_ctrl |= SD_CLK_CTRL_DIV_128;
			}

			WT_REG(sd_clk_ctrl, host, SD_CLK_CTRL);

			
			sd_clk_ctrl |= SD_CLK_CTRL_SCLKEN;
			WT_REG(sd_clk_ctrl, host, SD_CLK_CTRL);

			host->clk = clk;
			PR_DBG(host, "SD_CLK_CTRL = %04x",
					RD_REG(host, SD_CLK_CTRL));
			spin_unlock_irqrestore(&host->lock, flags);
		}
		break;

	case MMC_POWER_UP:
	default:
		
		break;
	}

	PR_DBG(host,
		"host->pwr = %u, host->clk = %u, host->bus_width = %u",
		host->pwr, host->clk, host->bus_width);
}








static int mmc_mn66829rf_get_ro(struct mmc_host *mmc)
{
	int wpswitch_status = 0;
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);

	if (host->plat->wpswitch) {
		wpswitch_status = host->plat->wpswitch(mmc_dev(mmc));
		if (wpswitch_status < 0) {
			wpswitch_status = -ENOSYS;
		}
	}
	PR_DBG(host, "Card read-only status %d", wpswitch_status);
	return wpswitch_status;
}





































#define mmc_mn66829rf_enable NULL
#define mmc_mn66829rf_disable NULL


static const struct mmc_host_ops mmc_mn66829rf_ops = {
	.request	= mmc_mn66829rf_request,
	.set_ios	= mmc_mn66829rf_set_ios,
	.get_ro		= mmc_mn66829rf_get_ro,
	.enable		= mmc_mn66829rf_enable,
	.disable	= mmc_mn66829rf_disable,
};

static void mmc_mn66829rf_early_suspend(struct early_suspend *h)
{
	pr_debug("%s: Called.\n", __func__);
};

static void mmc_mn66829rf_late_resume(struct early_suspend *h)
{
	struct mmc_mn66829rf_host *host =
		container_of(h, struct mmc_mn66829rf_host, early_suspend);

	pr_debug("%s: Called.\n", __func__);

	if (host) {
		mmc_claim_host(host->mmc);
		if (host->pending_resume) {
			PR_INF(host, "pending_resume=%d", host->pending_resume);
			host->pending_resume = 0;
			mmc_resume_host(host->mmc);
		}
		mmc_release_host(host->mmc);
	}
};







































int mmc_mn66829rf_host_init(struct platform_device *pdev)
{
	struct mmc_platform_data *plat;
	struct mmc_host *mmc;
	struct mmc_mn66829rf_host *host;
	struct resource *irqres = NULL;
	struct resource *memres = NULL;
	int ret = 0;
	int i;

	if (g_diag.state) {
		pr_info("%s: Host is already on\n", __func__);
		goto out;
	}

	if (!pdev) {
		pr_err("%s: Platform device is nothing\n", __func__);
		ret = -ENODEV;
		goto out;
	}

	plat = pdev->dev.platform_data;
	if (!plat) {
		pr_err("%s: Platform data not available\n", __func__);
		ret = -EINVAL;
		goto out;
	}

	if (!pdev->resource) {
		pr_err("%s: Invalid resource\n", __func__);
		ret = -ENXIO;
		goto out;
	}

	for (i = 0; i < pdev->num_resources; i++) {
		if (pdev->resource[i].flags & IORESOURCE_MEM) {
			memres = &pdev->resource[i];
		}
		if (pdev->resource[i].flags & IORESOURCE_IRQ) {
			irqres = &pdev->resource[i];
		}
	}
	if (!irqres || !memres) {
		pr_err("%s: Invalid resource\n", __func__);
		ret = -ENXIO;
		goto out;
	}

	mmc = mmc_alloc_host(sizeof(struct mmc_mn66829rf_host),
			&pdev->dev);
	if (!mmc) {
		pr_err("%s: mmc_alloc_host failed.\n", __func__);
		ret = -ENOMEM;
		goto out;
	}

	host = mmc_priv(mmc);
	host->plat = plat;
	host->mmc = mmc;
	host->curr.cmd = NULL;
	host->curr.data = NULL;
	host->irqres = irqres;
	host->memres = memres;
	host->pwr = MMC_CARD_OFF;
	host->clk = SD_CLK_OFF;
	host->bus_width = MMC_BUS_WIDTH_4;
	host->acmd_req = 0;
	host->direction = 0;
	host->state = SDIF_STATE_NOCARD;
	host->req_flag = 0;
	host->timer_active = 0;
	host->timeout_irq = 0;
	host->sdif_lock_ref = 0;
	host->pending_resume = 0;
	spin_lock_init(&host->lock);
	wake_lock_init(&host->sd_wake_lock, WAKE_LOCK_SUSPEND, DRIVER_NAME);
	wake_lock_init(&host->sdif_wake_lock, WAKE_LOCK_SUSPEND, SDIF_NAME);
	setup_timer(&host->req_timer, mmc_mn66829rf_timeout,
		(unsigned long)host);
	tasklet_init(&host->pio_tlet, mmc_mn66829rf_pio,
			(unsigned long)host);

	host->base = ioremap(memres->start,
			memres->end - memres->start + 1);
	if (!host->base) {
		PR_ERR(host, "Ioremap failed. %s", "!host->base");
		ret = -ENOMEM;
		goto host_free;
	}

	if (host->plat->translate_vdd) {
		if (host->plat->translate_vdd(mmc_dev(mmc),
				MMC_HOST_INIT)) {
			PR_ERR(host, "Translate_vdd failed. %s",
						"MMC_HOST_INIT");
			ret = -ENXIO;
			goto ioremap_free;
		}
	}

	WT_REG(SET_PLL_FREQ_MASK, host, SET_PLL_FREQ);
	PR_DBG(host, "SET_PLL_FREQ = %04x",
			RD_REG(host, SET_PLL_FREQ));

	host->suspended = 0;
	WT_REG(host->suspended, host, SUSPEND_CTRL);
	udelay(50);

	WT_REG(0, host, SOFT_RST);
	WT_REG(SOFT_RST_MASK, host, SOFT_RST);
	PR_DBG(host, "SOFT_RST = %04x",
			RD_REG(host, SOFT_RST));

	WT_REG(SD_PULLUP_MASK, host, SD_PULLUP);
	PR_DBG(host, "SD_PULLUP = %04x",
			RD_REG(host, SD_PULLUP));

	WT_REG(SD_INFO1_MASK_MASK, host, SD_INFO1_MASK);
	PR_DBG(host, "SD_INFO1_MASK = %04x",
			RD_REG(host, SD_INFO1_MASK));

	WT_REG(SD_INFO2_MASK_MASK, host, SD_INFO2_MASK);
	PR_DBG(host, "SD_INFO2_MASK = %04x",
			RD_REG(host, SD_INFO2_MASK));

	mmc->ops = &mmc_mn66829rf_ops;
	mmc->f_min = MMC_MN66829RF_F_MIN;
	mmc->f_max = MMC_MN66829RF_F_MAX;
	mmc->ocr_avail = plat->ocr_mask;

	mmc->caps |= plat->mmc_bus_width;
	mmc->caps |= MMC_CAP_SD_HIGHSPEED;
	if (plat->nonremovable) {
		mmc->caps |= MMC_CAP_NONREMOVABLE;
	}

	mmc->max_hw_segs = 32;
	mmc->max_phys_segs = mmc->max_hw_segs;
	mmc->max_blk_size = 512;
	mmc->max_blk_count = 0x10000;
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_seg_size = mmc->max_req_size;

	mmc_set_drvdata(pdev, mmc);

	ret = pm_runtime_set_active(&(pdev)->dev);
	if (ret < 0) {
		PR_INF(host, "failed with error %d", ret);
	}
	pm_suspend_ignore_children(&(pdev)->dev, true);


	mmc->caps |= MMC_CAP_DISABLE;
	pm_runtime_enable(&(pdev)->dev);







	mmc_add_host(mmc);

	if (plat->status) {
		host->eject = host->plat->status(mmc_dev(host->mmc));
		host->oldstat = !host->eject;
	}















	ret = request_irq(irqres->start, mmc_mn66829rf_irq,
				IRQF_SHARED | IRQF_TRIGGER_LOW,
				DRIVER_NAME " (cmd)", host);
	if (ret) {
		PR_ERR(host, "Request_irq(cmd) failed. ret = %d", ret);
		goto irq_free;
	}

	sdif_host.info.base = host->base;
	sdif_host.host = host;

	ret = sdif_host_register(&sdif_host);
	if (ret) {
		PR_ERR(host, "sdif_host_register failed. ret = %d", ret);
		goto sdif_fail;
	}

	PR_INF(host, "Slot current status = %d", host->oldstat);
	if (!host->eject) {
		host->state = SDIF_STATE_STARTINIT;
	}
	g_diag.host = host;
	g_diag.state = DIAG_ON;
	host->early_suspend.suspend = mmc_mn66829rf_early_suspend;
	host->early_suspend.resume  = mmc_mn66829rf_late_resume;
	host->early_suspend.level   = EARLY_SUSPEND_LEVEL_DISABLE_FB;
	register_early_suspend(&host->early_suspend);
	return 0;

 sdif_fail:
	sdif_host.host = NULL;
	sdif_host.info.base = NULL;
	free_irq(host->irqres->start, host);

 irq_free:







	pm_runtime_disable(&(pdev)->dev);
	pm_runtime_set_suspended(&(pdev)->dev);

	if (host->plat->translate_vdd) {
		host->plat->translate_vdd(mmc_dev(mmc),
				MMC_HOST_EXIT);
	}
	mmc_remove_host(mmc);

 ioremap_free:
	iounmap(host->base);

 host_free:
	tasklet_kill(&host->pio_tlet);
	del_timer_sync(&host->req_timer);
	wake_lock_destroy(&host->sdif_wake_lock);
	wake_lock_destroy(&host->sd_wake_lock);
	mmc_free_host(mmc);

 out:
	pr_err("%s: failed. ret = %d\n", __func__, ret);
	return ret;
}

int mmc_mn66829rf_host_exit(struct platform_device *pdev)
{
	struct mmc_host *mmc;
	struct mmc_platform_data *plat;
	struct mmc_mn66829rf_host *host;
	int ret = 0;

	if (!g_diag.state) {
		pr_info("%s: Host is already off\n", __func__);
		goto out;
	}

	g_diag.state = DIAG_OFF;
	g_diag.host = NULL;
	sdif_host_unregister(&sdif_host);
	sdif_host.host = NULL;
	sdif_host.info.base = NULL;

	if (!pdev) {
		pr_err("%s: Platform device is nothing\n", __func__);
		ret = -ENODEV;
		goto out;
	}

	if (pm_runtime_suspended(&(pdev)->dev)) {
		pm_runtime_resume(&(pdev)->dev);
	}

	mmc = mmc_get_drvdata(pdev);
	if (!mmc) {
		ret = -ENXIO;
		goto out;
	}

	host = mmc_priv(mmc);
	if (host->pwr != MMC_CARD_OFF) {
		mmc_power_off(mmc);
	}

	tasklet_kill(&host->pio_tlet);
	disable_irq(host->irqres->start);

	plat = host->plat;






	free_irq(host->irqres->start, host);






	if (plat->translate_vdd) {
		ret = plat->translate_vdd(mmc_dev(mmc), MMC_HOST_EXIT);
	}

	mmc_remove_host(mmc);
	iounmap(host->base);
	del_timer_sync(&host->req_timer);
	wake_lock_destroy(&host->sdif_wake_lock);
	wake_lock_destroy(&host->sd_wake_lock);
	mmc_free_host(mmc);
	unregister_early_suspend(&host->early_suspend);
	pm_runtime_disable(&(pdev)->dev);
	pm_runtime_set_suspended(&(pdev)->dev);

 out:
	if (ret) {
		pr_err("%s: failed. ret = %d\n", __func__, ret);
	}
	return ret;
}

static int mmc_mn66829rf_probe(struct platform_device *pdev)
{
	int ret;

	mutex_lock(&g_diag_lock);
	g_diag.pdev = pdev;

	ret = mmc_mn66829rf_host_init(pdev);
	if (ret) {
		pr_err("%s: failed. ret = %d\n", __func__, ret);
		g_diag.pdev = NULL;
	}

	mutex_unlock(&g_diag_lock);
	return ret;
}

static int mmc_mn66829rf_remove(struct platform_device *pdev)
{
	int ret;

	mutex_lock(&g_diag_lock);

	ret = mmc_mn66829rf_host_exit(pdev);
	if (ret) {
		pr_err("%s: failed. ret = %d\n", __func__, ret);
	}

	g_diag.pdev = NULL;
	mutex_unlock(&g_diag_lock);
	return ret;
}


static int
mmc_mn66829rf_runtime_suspend(struct device *dev)
{
	struct mmc_host *mmc = dev_get_drvdata(dev);
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);
	int rc = 0;

	PR_INF(host, "Suspend START. suspended=%d", host->suspended);

	mutex_lock(&g_diag_lock);
	mmc->suspend_task = current;

	if (mmc && mmc->card) {
		if (!host->sdif_lock_ref) {
			mmc_claim_host(mmc);
			if (host->pending_resume) {
				host->pending_resume = 0;
			} else  {
				pm_runtime_get_noresume(dev);
				rc = mmc_suspend_host(mmc);
				pm_runtime_put_noidle(dev);
			}
			mmc_release_host(mmc);
		} else {
			rc = -EBUSY;
		}
	}

	mmc->suspend_task = NULL;
	mutex_unlock(&g_diag_lock);

	PR_INF(host, "Suspend END(rc=%d,state=%d). suspended=%d",
				 rc, host->state, host->suspended);
	return rc;
}

static int
mmc_mn66829rf_runtime_resume(struct device *dev)
{
	struct mmc_host *mmc = dev_get_drvdata(dev);
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);
	int rc = 0;

	PR_INF(host, "Resume START. suspended=%d", host->suspended);

	mutex_lock(&g_diag_lock);

	if (mmc) {
		if (host->eject) {
			host->state = SDIF_STATE_NOCARD;
		} else {
			host->state = SDIF_STATE_STARTINIT;
		}

		if (mmc->card) {
			host->pending_resume = 1;
		}
	}

	mutex_unlock(&g_diag_lock);

	PR_INF(host, "Resume END(rc=%d,state=%d). suspended=%d",
				 rc, host->state, host->suspended);
	return 0;
}

static int mmc_mn66829rf_runtime_idle(struct device *dev)
{
	struct mmc_host *mmc = dev_get_drvdata(dev);
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);

	PR_DBG(host, "Runtime-Idle called. suspended=%d",
				pm_runtime_suspended(dev));

	
	pm_schedule_suspend(dev, SD_IDLE_TIMEOUT);

	PR_DBG(host, "Runtime-Idle return. suspended=%d",
				pm_runtime_suspended(dev));
	return -EAGAIN;
}

static int mmc_mn66829rf_pm_suspend(struct device *dev)
{
	struct mmc_host *mmc = dev_get_drvdata(dev);
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);
	int rc = 0;

	PR_DBG(host, "PM-Suspend requested. suspended=%d",
				pm_runtime_suspended(dev));







	if (!pm_runtime_suspended(dev)) {
		rc = mmc_mn66829rf_runtime_suspend(dev);
	}

	PR_DBG(host, "PM-Suspend done(rc=%d). suspended=%d",
				 rc, pm_runtime_suspended(dev));
	return rc;
}

static int mmc_mn66829rf_pm_resume(struct device *dev)
{
	struct mmc_host *mmc = dev_get_drvdata(dev);
	struct mmc_mn66829rf_host *host = mmc_priv(mmc);
	int rc = 0;

	PR_DBG(host, "PM-Resume requested. suspended=%d",
				pm_runtime_suspended(dev));

	rc = mmc_mn66829rf_runtime_resume(dev);






	
	pm_runtime_disable(dev);
	rc = pm_runtime_set_active(dev);
	if (rc < 0) {
		PR_INF(host, "failed with error %d", rc);
	}
	pm_runtime_enable(dev);

	PR_DBG(host, "PM-Resume done(rc=%d). suspended=%d",
				 rc, pm_runtime_suspended(dev));
	return rc;
}








static ssize_t
mmc_mn66829rf_diag_write(struct file *file,
		const char __user *data, size_t len, loff_t *ppos)
{
	struct mmc_mn66829rf_host *host = g_diag.host;
	int ret = 0;

	printk(KERN_INFO ">>  %s: mmc diag write (%s)!\n",
			__func__, (data[0] != '0') ? "ON":"OFF");

	if (!g_diag.state || !host) {
		pr_err("%s: Diag state error.\n", __func__);
		ret = -1;
		goto out;
	}

	mmc_mn66829rf_get_sdif_lock(host);
	mutex_lock(&g_diag_lock);

	if (data[0] != '0') {
		host->oldstat = 1;
	} else {
		host->oldstat = 0;
	}
	host->eject = !host->oldstat;
	mmc_err_info_clear();
	mmc_detect_change(host->mmc, 0);

	mutex_unlock(&g_diag_lock);
	mmc_mn66829rf_put_sdif_lock(host);

	printk(KERN_INFO ">>  %s: mmc (%s) ret=(%d)\n",
			__func__, (data[0] != '0') ? "ON":"OFF", ret);

	msleep(50);

out:
	return (ssize_t)ret;
}

static int mmc_mn66829rf_diag_open(struct inode *inode,
		struct file *file)
{
	printk(KERN_INFO ">>  %s: mmc diag open!\n", __func__);
	if (g_diag.count > 0) {
		printk(KERN_INFO ">>  %s: Already opened!\n", __func__);
		return -EBUSY;
	}
	g_diag.count++;
	return 0;
}

static int mmc_mn66829rf_diag_release(struct inode *inode,
		struct file *file)
{
	printk(KERN_INFO ">>  %s: mmc diag close!\n", __func__);
	if (g_diag.count > 0) {
		g_diag.count = 0;
		return 0;
	}

	printk(KERN_INFO ">>  %s: Already closed!\n", __func__);
	return -EBUSY;
}

static struct file_operations mmc_mn66829rf_diag_fops = {
	.owner		= THIS_MODULE,
	.write		= mmc_mn66829rf_diag_write,
	.open		= mmc_mn66829rf_diag_open,
	.release	= mmc_mn66829rf_diag_release,
};

static struct miscdevice mmc_mn66829rf_diag_device = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "mmcdiag",
	.fops	= &mmc_mn66829rf_diag_fops,
};

static const struct dev_pm_ops mmc_mn66829rf_dev_pm_ops = {
	.runtime_suspend	= mmc_mn66829rf_runtime_suspend,
	.runtime_resume		= mmc_mn66829rf_runtime_resume,
	.runtime_idle		= mmc_mn66829rf_runtime_idle,
	.suspend	= mmc_mn66829rf_pm_suspend,
	.resume		= mmc_mn66829rf_pm_resume,
};

static struct platform_driver mmc_mn66829rf_driver = {
	.probe		= mmc_mn66829rf_probe,
	.remove		= mmc_mn66829rf_remove,
	.driver		= {
		.name	= DRIVER_NAME,
		.pm		= &mmc_mn66829rf_dev_pm_ops,
	},
};

static int __init mmc_mn66829rf_init(void)
{
	misc_register(&mmc_mn66829rf_diag_device);
	return platform_driver_register(&mmc_mn66829rf_driver);
}

static void __exit mmc_mn66829rf_exit(void)
{
	platform_driver_unregister(&mmc_mn66829rf_driver);
	misc_deregister(&mmc_mn66829rf_diag_device);
}

module_init(mmc_mn66829rf_init);
module_exit(mmc_mn66829rf_exit);

MODULE_DESCRIPTION("Panasonic MN66829RF SD Host Controller Driver");
MODULE_AUTHOR("NEC CASIO Mobile Communications, Ltd.");
MODULE_LICENSE("GPL");

