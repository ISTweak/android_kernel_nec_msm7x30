/*
 *  linux/drivers/mmc/host/sdif.c - SD card extended interface.
 *
 *  Copyright (C) 2010 NEC CASIO Mobile Communications, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/module.h>
#include <linux/irq.h>
#include <linux/err.h>
#include <linux/semaphore.h>

#include "sdif_host.h"
#include "sdif_driver.h"

#define PR_DBG(fmt, args...)	\
	pr_debug("%s: " fmt "\n", __func__ , args)
#define PR_INF(fmt, args...)	\
	pr_info("%s: " fmt "\n", __func__ , args)
#define PR_ERR(fmt, args...)	\
	pr_err("%s: " fmt "\n", __func__ , args)

struct mmc_mn66829rf_sdif {
	sdif_host_t		*host;
	sdif_driver_t	*driver;
	unsigned char	enable_irq;
	unsigned char	power;
	struct semaphore sem;
};

static struct mmc_mn66829rf_sdif g_sdif = {
	.host		= NULL,
	.driver		= NULL,
	.enable_irq	= 0,
	.power		= 0,
};

int sdif_power_on(void)
{
	int ret = 0;

	if (!g_sdif.host || !g_sdif.host->ops.power_on) {
		ret = -ENODEV;
		PR_ERR("No host address! ret = %d", ret);
		goto out;
	}

	if (g_sdif.power) {
		PR_DBG("Already power on! ret = %d", ret);
		goto out;
	}

	ret = g_sdif.host->ops.power_on(g_sdif.host->host);
	if (ret) {
		PR_ERR("Failed power_on callback. ret = %d", ret);
		goto out;
	}
	g_sdif.power = 1;
	PR_DBG("Power ON! ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_power_on);

int sdif_power_off(void)
{
	int ret = 0;

	if (!g_sdif.host || !g_sdif.host->ops.power_off) {
		ret = -ENODEV;
		PR_ERR("No host address! ret = %d", ret);
		goto out;
	}

	if (!g_sdif.power) {
		PR_DBG("Already power off! ret = %d", ret);
		goto out;
	}

	ret = g_sdif.host->ops.power_off(g_sdif.host->host);
	if (ret) {
		PR_ERR("Failed power_off callback. ret = %d", ret);
		goto out;
	}
	g_sdif.power = 0;
	PR_DBG("Power OFF! ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_power_off);

int sdif_enable_irq(void)
{
	int ret = 0;

	if (!g_sdif.driver || !g_sdif.driver->sdif_irq) {
		ret = -ENODEV;
		PR_ERR("No IRQ handler! ret = %d", ret);
		goto out;
	}

	g_sdif.enable_irq = 1;
	PR_DBG("IRQ Enabled! ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_enable_irq);

int sdif_disable_irq(void)
{
	int ret = 0;

	if (!g_sdif.driver || !g_sdif.driver->sdif_irq) {
		ret = -ENODEV;
		PR_ERR("No IRQ handler! ret = %d", ret);
		goto out;
	}

	g_sdif.enable_irq = 0;
	PR_DBG("IRQ Disabled! ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_disable_irq);

int sdif_get_host_info(sdif_host_info_t *host_info) {
	int ret = 0;

	if (!host_info) {
		ret = -EINVAL;
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	if (!g_sdif.host) {
		ret = -ENODEV;
		PR_ERR("No host address! ret = %d", ret);
		goto out;
	}

	host_info->base = g_sdif.host->info.base;
	PR_DBG("End. ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_get_host_info);

int sdif_get_card_info(sdif_card_info_t *card_info)
{
	int ret = 0;

	if (!card_info) {
		ret = -EINVAL;
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	if (!g_sdif.host || !g_sdif.host->ops.get_card_info) {
		ret = -ENODEV;
		PR_ERR("No host address! ret = %d", ret);
		goto out;
	}

	ret = g_sdif.host->ops.get_card_info(card_info, g_sdif.host->host);
	if (ret) {
		PR_ERR("Failed get_card_info callback. ret = %d", ret);
		goto out;
	}
	PR_DBG("End. ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_get_card_info);

int sdif_get_state(unsigned short *state)
{
	int ret = 0;

	if (!state) {
		ret = -EINVAL;
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	*state = SDIF_STATE_NOCARD;

	if (!g_sdif.host || !g_sdif.host->ops.get_state) {
		ret = -ENODEV;
		PR_ERR("No host address! ret = %d", ret);
		goto out;
	}

	ret = g_sdif.host->ops.get_state(state, g_sdif.host->host);
	if (ret) {
		PR_ERR("Failed get_state callback. ret = %d", ret);
		goto out;
	}
	PR_DBG("End. ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_get_state);

int sdif_driver_register(sdif_driver_t *sdif_drv)
{
	int ret = 0;

	if (!sdif_drv || !sdif_drv->sdif_irq) {
		ret = -EINVAL;
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	if (!g_sdif.host) {
		ret = -ENODEV;
		PR_ERR("No host address! ret = %d", ret);
		goto out;
	}

	if (g_sdif.driver) {
		ret = -EBUSY;
		PR_ERR("Already registered! ret = %d", ret);
		goto out;
	}

	g_sdif.enable_irq = 0;
	g_sdif.driver = sdif_drv;
	PR_DBG("SDIF driver registered. ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_driver_register);

int sdif_driver_unregister(sdif_driver_t *sdif_drv)
{
	int ret = 0;

	if (sdif_drv != g_sdif.driver) {
		ret = -EINVAL;
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	g_sdif.enable_irq = 0;
	g_sdif.driver = NULL;
	PR_DBG("SDIF driver unregistered. ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_driver_unregister);

int sdif_lock(void) {
	PR_DBG("%s START", "Lock");
	down(&g_sdif.sem);
	PR_DBG("%s END", "Lock");
	return 0;
}
EXPORT_SYMBOL(sdif_lock);

int sdif_unlock(void) {
	PR_DBG("%s START", "Unlock");
	up(&g_sdif.sem);
	PR_DBG("%s END", "Unlock");
	return 0;
}
EXPORT_SYMBOL(sdif_unlock);

int sdif_host_irq(int irq, void *dev_id)
{
	int ret = IRQ_NONE;

	if (!g_sdif.driver) {
		PR_DBG("SDIF driver is not registered. ret = %d", ret);
		goto out;
	}

	if (!g_sdif.host) {
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	if (g_sdif.driver->sdif_irq && g_sdif.enable_irq) {
		g_sdif.driver->sdif_irq(irq, dev_id);
		ret = IRQ_HANDLED;
		PR_DBG("IRQ_HANDLED! ret = %d", ret);
		goto out;
	}
	PR_DBG("IRQ_NONE! ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_host_irq);

int sdif_host_register(sdif_host_t *sdif_host)
{
	int ret = 0;

	if (!sdif_host || !sdif_host->host ||
			!sdif_host->info.base ||
			!sdif_host->ops.power_on ||
			!sdif_host->ops.power_off ||
			!sdif_host->ops.get_card_info ||
			!sdif_host->ops.get_state) {
		ret = -EINVAL;
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	if (g_sdif.host) {
		ret = -EBUSY;
		PR_ERR("Already registered! ret = %d", ret);
		goto out;
	}

	init_MUTEX(&g_sdif.sem);
	g_sdif.power = 0;
	g_sdif.host = sdif_host;
	PR_DBG("SDIF host registered. ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_host_register);

int sdif_host_unregister(sdif_host_t *sdif_host)
{
	int ret = 0;

	if (sdif_host != g_sdif.host) {
		ret = -EINVAL;
		PR_ERR("Invalid address! ret = %d", ret);
		goto out;
	}

	if (g_sdif.power) {
		sdif_power_off();
		g_sdif.power = 0;
	}

	g_sdif.host = NULL;
	PR_DBG("SDIF host unregistered. ret = %d", ret);

out:
	return ret;
}
EXPORT_SYMBOL(sdif_host_unregister);

MODULE_DESCRIPTION("SD card extended interface.");
MODULE_AUTHOR("NEC CASIO Mobile Communications, Ltd.");
MODULE_LICENSE("GPL");
