/* Copyright (c) 2008-2009, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Code Aurora Forum nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * Alternatively, provided that this notice is retained in full, this software
 * may be relicensed by the recipient under the terms of the GNU General Public
 * License version 2 ("GPL") and only version 2, in which case the provisions of
 * the GPL apply INSTEAD OF those given above.  If the recipient relicenses the
 * software under the GPL, then the identification text in the MODULE_LICENSE
 * macro must be changed to reflect "GPLv2" instead of "Dual BSD/GPL".  Once a
 * recipient changes the license terms to the GPL, subsequent recipients shall
 * not relicense under alternate licensing terms, including the BSD or dual
 * BSD/GPL terms.  In addition, the following license statement immediately
 * below and between the words START and END shall also then apply when this
 * software is relicensed under the GPL:
 *
 * START
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2 and only version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * END
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/

#include "msm_fb.h"
#include "mddihost.h"
#include "mddihosti.h"
#include "mddi_nt35560.h"
#include <mach/gpio.h>
#include <linux/leds-bd6082gul.h> 
#include <linux/unistd.h>
#include <linux/time.h>


#include <mach/vreg.h>
#include <linux/err.h>
#include <mach/rpc_pmapp.h>






#include <linux/oemnc_info.h>


#define NT35560_LCD_BACKLIGHT_OFF (0)
#define NT35560_LCD_BACKLIGHT_ON  (1)
#define NT35560_LCD_CABC_OFF (0)
#define NT35560_LCD_CABC_ON  (1)


#define NT35560_STOP_CMD (0x0000FFFF)



static mddi_nt35560_state_t mddi_nt35560_state = NT35560_NORMAL_MODE; 

static struct msm_panel_common_pdata *mddi_nt35560_pdata;

#define MDDI_NT35560_VSYNC_TIMEOUT (HZ * 10) 


static int   mddi_nt35560_lcd_isr_cnt = 0;
struct timeval mddi_nt35560_timetemp[8];
unsigned int mddi_nt35560_difftemp[5] = {0, 0, 0, 0, 0};
static wait_queue_head_t mddi_nt35560_vsync_wait;
spinlock_t mddi_nt35560_spin_lock;


static int nt35560_cabc_sts = NT35560_LCD_CABC_ON;











static DEFINE_SPINLOCK(mddi_nt35560_vsync_spin_lock);


unsigned int mddi_nt35560_standby_ctl_flag = 1;



static boolean nt35560_vreg_initialize_flg = FALSE;





static mddi_nt35560_regset lcd_set_power_on[] = {
    
    { 0x0000C980,       0x00000001 },
    { 0x00007DC0,       0x00000001 },
    { 0x00000180,       0x00000014 },
    { 0x00000280,       0x00000000 },
    { 0x00000380,       0x00000033 },
    { 0x00000480,       0x00000048 },
    { 0x00000780,       0x00000000 },
    { 0x00000880,       0x00000044 },
    { 0x00000980,       0x00000054 },
    { 0x00000A80,       0x00000012 },
    { 0x00001280,       0x00000000 },
    { 0x00001380,       0x00000010 },
    { 0x00001480,       0x0000000D },
    { 0x00001580,       0x000000A0 },
    { 0x00001A80,       0x00000062 },
    { 0x00001F80,       0x00000000 },
    { 0x00002080,       0x00000001 },
    { 0x00002180,       0x00000066 },
    { 0x00009480,       0x000000BF },
    { 0x00009580,       0x00000000 },
    { 0x00009680,       0x00000000 },
    { 0x00009780,       0x000000B4 },
    { 0x00009880,       0x0000000D },
    { 0x00009980,       0x0000002C },
    { 0x00009A80,       0x0000000A },
    { 0x00009B80,       0x00000001 },
    { 0x00009C80,       0x00000001 },
    { 0x00009D80,       0x00000000 },
    { 0x00009E80,       0x00000000 },
    { 0x00009F80,       0x00000000 },
    { 0x0000A080,       0x0000000A },
    { 0x0000A280,       0x00000000 }, 
    { 0x0000A380,       0x0000002E },
    { 0x0000A480,       0x0000000E },
    { 0x0000A580,       0x000000C0 },
    { 0x0000A680,       0x00000001 },
    { 0x0000A780,       0x00000000 },
    { 0x0000A980,       0x00000000 },
    { 0x0000AA80,       0x00000000 },
    { 0x0000E780,       0x00000000 },
    { 0x0000ED80,       0x00000000 },
    { 0x0000FB80,       0x00000000 },
    { 0x0000F380,       0x000000CC },
    { 0x0000EE80,       0x00000000 },
    { 0x00002480,       0x0000007F },
    { 0x00002580,       0x0000007E },
    { 0x00002680,       0x00000085 },
    { 0x00002780,       0x0000008A },
    { 0x00002880,       0x00000001 },
    { 0x00002980,       0x0000001B },
    { 0x00002A80,       0x00000057 },
    { 0x00002B80,       0x00000092 },
    { 0x00002D80,       0x00000022 },
    { 0x00002F80,       0x0000002D },
    { 0x00003080,       0x000000D8 },
    { 0x00003180,       0x0000001C },
    { 0x00003280,       0x00000045 },
    { 0x00003380,       0x00000079 },
    { 0x00003480,       0x000000BC },
    { 0x00003580,       0x000000D9 },
    { 0x00003680,       0x000000F2 },
    { 0x00003780,       0x00000073 },
    { 0x00003880,       0x00000020 },
    { 0x00003980,       0x00000021 },
    { 0x00003A80,       0x0000003A },
    { 0x00003B80,       0x00000057 },
    { 0x00003D80,       0x00000007 },
    { 0x00003F80,       0x0000003E },
    { 0x00004080,       0x00000066 },
    { 0x00004180,       0x00000031 },
    { 0x00004280,       0x00000010 },
    { 0x00004380,       0x0000001A },
    { 0x00004480,       0x0000006E },
    { 0x00004580,       0x0000002E },
    { 0x00004680,       0x0000007E },
    { 0x00004780,       0x0000007F },
    { 0x00004880,       0x0000005F },
    { 0x00004980,       0x0000007E },
    { 0x00004A80,       0x0000007F },
    { 0x00004B80,       0x00000000 },
    { 0x00004C80,       0x0000007F },
    { 0x00004D80,       0x0000007F },
    { 0x00004E80,       0x0000009D },
    { 0x00004F80,       0x0000009B },
    { 0x00005080,       0x00000001 },
    { 0x00005180,       0x00000035 },
    { 0x00005280,       0x00000062 },
    { 0x00005380,       0x000000AC },
    { 0x00005480,       0x00000020 },
    { 0x00005580,       0x00000027 },
    { 0x00005680,       0x000000E4 },
    { 0x00005780,       0x0000001B },
    { 0x00005880,       0x0000004B },
    { 0x00005980,       0x00000078 },
    { 0x00005A80,       0x000000BB },
    { 0x00005B80,       0x000000D7 },
    { 0x00005C80,       0x000000F2 },
    { 0x00005D80,       0x00000073 },
    { 0x00005E80,       0x00000020 },
    { 0x00005F80,       0x00000022 },
    { 0x00006080,       0x0000003B },
    { 0x00006180,       0x00000058 },
    { 0x00006280,       0x00000007 },
    { 0x00006380,       0x00000034 },
    { 0x00006480,       0x00000063 },
    { 0x00006580,       0x00000030 },
    { 0x00006680,       0x00000018 },
    { 0x00006780,       0x0000001D },
    { 0x00006880,       0x00000069 },
    { 0x00006980,       0x00000031 },
    { 0x00006A80,       0x00000079 },
    { 0x00006B80,       0x0000007B },
    { 0x00006C80,       0x00000045 },
    { 0x00006D80,       0x00000043 },
    { 0x00006E80,       0x00000046 },
    { 0x00006F80,       0x00000000 },
    { 0x00007080,       0x0000007B },
    { 0x00007180,       0x0000007F },
    { 0x00007280,       0x000000BC },
    { 0x00007380,       0x000000F6 },
    { 0x00007480,       0x00000001 },
    { 0x00007580,       0x0000000A },
    { 0x00007680,       0x0000004D },
    { 0x00007780,       0x000000C3 },
    { 0x00007880,       0x00000020 },
    { 0x00007980,       0x00000023 },
    { 0x00007A80,       0x000000EF },
    { 0x00007B80,       0x00000011 },
    { 0x00007C80,       0x00000034 },
    { 0x00007D80,       0x00000073 },
    { 0x00007E80,       0x000000FE },
    { 0x00007F80,       0x000000FC },
    { 0x00008080,       0x000000FD },
    { 0x00008180,       0x0000007E },
    { 0x00008280,       0x00000020 },
    { 0x00008380,       0x00000021 },
    { 0x00008480,       0x00000022 },
    { 0x00008580,       0x00000020 },
    { 0x00008680,       0x00000008 },
    { 0x00008780,       0x00000046 },
    { 0x00008880,       0x00000070 },
    { 0x00008980,       0x00000026 },
    { 0x00008A80,       0x00000019 },
    { 0x00008B80,       0x00000020 },
    { 0x00008C80,       0x00000053 },
    { 0x00008D80,       0x00000030 },
    { 0x00008E80,       0x00000076 },
    { 0x00008F80,       0x0000007E },
    { 0x00009080,       0x0000001C },
    { 0x00009180,       0x0000005C },
    { 0x00009280,       0x0000005D },
    { 0x00009380,       0x00000021 },
    { 0x00003500,       0x00000000 }, 
    { 0x00004400,       0x00000000 }, 
    { 0x00004401,       0x00000000 }, 
    { 0x00003600,       0x00000000 }, 
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_disp_on[] = {
    
    { 0x00002900,       0x00000000 }, 
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_disp_off[] = {
    
    { 0x00002800,       0x00000000 }, 
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_enter_stb[] = {
    
    { 0x00001000,       0x00000000 }, 
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_exit_stb[] = {
    
    { 0x00001100,       0x00000000 }, 
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_enter_deep_stb[] = {
    
    { 0x00004F00,       0x00000001 }, 
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_exit_deep_stb[] = {
    
    
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_cabc_on[] = {
    
    { 0x000082C0,       0x000000B0 },
    { 0x000083C1,       0x00000040 },
    { 0x000083C2,       0x00000000 },
    { 0x00005100,       0x000000FF },
    { 0x00005300,       0x0000002F },
    { 0x00005500,       0x00000002 },
    { 0x00005E00,       0x00000095 },
    { 0x000022C0,       0x00000022 },
    { 0x000072C0,       0x0000000A },
    { 0x000073C0,       0x00000004 },
    { NT35560_STOP_CMD, 0x00000000 }  
};


static mddi_nt35560_regset lcd_set_cabc_off[] = {
    
    { 0x00005300,       0x00000003 },
    { 0x00005500,       0x00000002 },
    { NT35560_STOP_CMD, 0x00000000 }  
};

static unsigned mddi_nt35560_lcd_reset =
  GPIO_CFG(122, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,   GPIO_CFG_2MA);

static int mddi_nt35560_on(struct platform_device *pdev);
static int mddi_nt35560_off(struct platform_device *pdev);
static void mddi_nt35560_backlight_ctl(int flg);










static void mddi_nt35560_state_transition(mddi_nt35560_state_t current_value,
                                          mddi_nt35560_state_t set_value)
{
    if (mddi_nt35560_state != current_value)
    {
        
        MDDI_MSG_ERR("NT35560 state trans. (%d->%d) found %d.\n",
                      current_value, set_value, mddi_nt35560_state);
    }

    mddi_nt35560_state = set_value;
    return;
}










static int mddi_nt35560_power_ctl( boolean power_flg )
{
    struct vreg *vreg_ldo8 = NULL;
    struct vreg *vreg_ldo20 = NULL;
    int rc = 0;


    if( (power_flg == FALSE) && (mddi_nt35560_standby_ctl_flag == 0) )
        return 0;


    
    rc = gpio_tlmm_config(mddi_nt35560_lcd_reset, GPIO_CFG_ENABLE);
    if(rc)
    {
        printk(KERN_ERR "mddi_nt35560_power_on gpioconf failed!! \n");
        return rc;
    }

    
    
    gpio_set_value(122, 0);

    if(power_flg != TRUE)
        mddi_wait(10);

    
    
    vreg_ldo8 = vreg_get(NULL, "gp7");

    if(IS_ERR(vreg_ldo8))
    {
        rc = PTR_ERR(vreg_ldo8);
        printk(KERN_ERR "%s: gp7 vreg get failed (%d)\n", __func__, rc);
        return rc;
    }

    
    vreg_ldo20 = vreg_get(NULL, "gp13");

    if(IS_ERR(vreg_ldo20))
    {
        rc = PTR_ERR(vreg_ldo20);
        printk(KERN_ERR "%s: gp13 vreg get failed (%d)\n", __func__, rc);
        return rc;
    }

    rc = vreg_set_level(vreg_ldo8, 2800);
    if(rc)
    {
        printk(KERN_ERR "%s: vreg LDO8 set level failed (%d)\n", __func__, rc);
        return rc;
    }

    rc = vreg_set_level(vreg_ldo20, 1800);
    if(rc)
    {
        printk(KERN_ERR "%s: vreg LDO20 set level failed (%d)\n", __func__, rc);
        return rc;
    }

    
    if( (nt35560_vreg_initialize_flg == FALSE) && (power_flg == FALSE) )
    {
        
        rc = vreg_enable(vreg_ldo8);
        if(rc)
            printk(KERN_ERR "%s: LDO8 vreg enable failed (%d)\n", __func__, rc);

        rc = vreg_enable(vreg_ldo20);
        if(rc)
            printk(KERN_ERR "%s: LDO20 vreg enable failed (%d)\n", __func__, rc);

        nt35560_vreg_initialize_flg = TRUE;
    }
    

    
    if(power_flg == TRUE)
        rc = vreg_enable(vreg_ldo8);
    else
        rc = vreg_disable(vreg_ldo8);

    if(rc)
    {
        printk(KERN_ERR "%s: LDO8 vreg enable failed (%d)\n", __func__, rc);
        return rc;
    }

    
    if(power_flg == TRUE)
        rc = vreg_enable(vreg_ldo20);
    else
        rc = vreg_disable(vreg_ldo20);

    if(rc)
    {
        printk(KERN_ERR "%s: LDO12 vreg enable failed (%d)\n", __func__, rc);
        return rc;
    }

    
    if(power_flg == TRUE)
    {
        mddi_wait(21);

        
        gpio_set_value(122, 1);

        
        mddi_wait(120);
    }

    if(power_flg == TRUE )
        rc = pmapp_display_clock_config(1);
    else
        rc = pmapp_display_clock_config(0);

    if(rc)
    {
        printk(KERN_ERR "%s pmapp_display_clock_config rc=%d\n", __func__, rc);
        return rc;
    }

    return rc;
}










static void mddi_nt35560_initial_setup(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;

    regtbl = (mddi_nt35560_regset*)lcd_set_power_on;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    mddi_wait(20); 

    
    if(nt35560_cabc_sts == NT35560_LCD_CABC_ON)
        mddi_nt35560_cabc_ctl(1);
    

    return;
}











static void mddi_nt35560_set_disp_on(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;

    regtbl = (mddi_nt35560_regset*)lcd_set_disp_on;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    mddi_nt35560_backlight_ctl(NT35560_LCD_BACKLIGHT_ON);









    return;
}










static void mddi_nt35560_set_disp_off(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;


    if( mddi_nt35560_standby_ctl_flag == 0 )
        return;


    mddi_nt35560_backlight_ctl(NT35560_LCD_BACKLIGHT_OFF);

    regtbl = (mddi_nt35560_regset*)lcd_set_disp_off;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    mddi_wait(17); 

    return;
}










static int mddi_nt35560_enter_standby(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;


    if( mddi_nt35560_standby_ctl_flag == 0 )
        return 0;


    regtbl = (mddi_nt35560_regset*)lcd_set_enter_stb;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    mddi_wait(70); 

    return 0;
}










static int mddi_nt35560_exit_standby(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;

    regtbl = (mddi_nt35560_regset*)lcd_set_exit_stb;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    mddi_wait(130); 

    return 0;
}










static int mddi_nt35560_enter_deep_standby(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;


    if( mddi_nt35560_standby_ctl_flag == 0 )
        return 0;


    regtbl = (mddi_nt35560_regset*)lcd_set_enter_deep_stb;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    mddi_wait(2); 

    return 0;
}











static int mddi_nt35560_exit_deep_standby(void)
{
    int ret;
    int cnt;
    mddi_nt35560_regset *regtbl;

    regtbl = (mddi_nt35560_regset*)lcd_set_exit_deep_stb;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    
    ret = gpio_tlmm_config(mddi_nt35560_lcd_reset, GPIO_CFG_ENABLE);
    if (ret)
    {
        MDDI_MSG_ERR("%s(%d): GPIO(122) config Error. (ret=%d)\n",
                     __func__, __LINE__, ret);

        return -ENODEV;
    }

    
    gpio_set_value(122, 1);

    
    gpio_set_value(122, 0);

    
    mddi_wait(3);

    
    gpio_set_value(122, 1);

    mddi_wait(20); 

    return 0;
}










static int mddi_nt35560_set_cabc_off(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;

    regtbl = (mddi_nt35560_regset*)lcd_set_cabc_off;
    for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
    {
        
        mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
    }

    return 0;
}










static int mddi_nt35560_set_cabc_on(void)
{
    int cnt;
    mddi_nt35560_regset *regtbl;

    if (nt35560_cabc_sts == NT35560_LCD_CABC_ON)
    {

        regtbl = (mddi_nt35560_regset*)lcd_set_cabc_on;
        for (cnt = 0; regtbl[cnt].reg_addr != NT35560_STOP_CMD; cnt++)
        {
            
            mddi_nt35560_write(regtbl[cnt].reg_addr, regtbl[cnt].set_data, TRUE);
        }
    }
    else
    {
        (void)mddi_nt35560_set_cabc_off();
    }

    return 0;
}












int mddi_nt35560_standby_ctl(int on)
{
    int ret = 0;
    mddi_nt35560_state_t curr_stat;

    
    curr_stat = mddi_nt35560_state;

    switch (curr_stat)
    {
        case NT35560_STANDBY :
            if (!on)
            {
                ret = mddi_nt35560_exit_standby();

                
                mddi_nt35560_set_disp_on();

                
                mddi_nt35560_state_transition(curr_stat, NT35560_NORMAL_MODE);
            }
            break;

        case NT35560_NORMAL_MODE :
            if (on)
            {
                
                mddi_nt35560_set_disp_off();

                ret = mddi_nt35560_enter_standby();

                
                mddi_nt35560_state_transition(curr_stat, NT35560_STANDBY);
            }
            break;

        case NT35560_STATE_OFF :
            
        case NT35560_DEEP_STANDBY :
            
        case NT35560_READY :
            
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n",
                         __func__, __LINE__, curr_stat);
            ret = -EINVAL;
            break;

        default :
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n",
                         __func__, __LINE__, curr_stat);
            ret = -ENODEV;
            break;
    }

    return ret;
}












int mddi_nt35560_deep_standby_ctl(int on)
{
    int ret = 0;
    mddi_nt35560_state_t curr_stat;

    curr_stat = mddi_nt35560_state;

    switch (curr_stat)
    {
        case NT35560_NORMAL_MODE :
            if (on)
            {
                
                mddi_nt35560_set_disp_off();

                
                (void)mddi_nt35560_enter_standby();

                
                ret = mddi_nt35560_enter_deep_standby();

                
                mddi_nt35560_state_transition(curr_stat, NT35560_DEEP_STANDBY);
            }
            break;

        case NT35560_DEEP_STANDBY :
            if (!on)
            {
                
                ret = mddi_nt35560_exit_deep_standby();

                
                mddi_nt35560_initial_setup();


                
                (void)mddi_nt35560_set_cabc_on();


                
                (void)mddi_nt35560_exit_standby();

                
                mddi_nt35560_set_disp_on();

                
                mddi_nt35560_state_transition(curr_stat, NT35560_NORMAL_MODE);
            }
            break;

        case NT35560_STATE_OFF :
            
        case NT35560_STANDBY :
            
        case NT35560_READY :
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n",
                         __func__, __LINE__, curr_stat);
            ret = -EINVAL;
            break;

        default :
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n",
                         __func__, __LINE__, curr_stat);
            ret = -ENODEV;
            break;
    }

    return ret;
}










void mddi_nt35560_set_idle_state(void)
{
    mddi_nt35560_state_t curr_stat;

    
    curr_stat = mddi_nt35560_state;

    switch (curr_stat)
    {
        case NT35560_STATE_OFF :
            
            (void)mddi_nt35560_power_ctl(1);
            
            mddi_nt35560_initial_setup();
            
            (void)mddi_nt35560_set_cabc_on();
            
            (void)mddi_nt35560_exit_standby();

            
        case NT35560_READY :
            
            mddi_nt35560_set_disp_on();
            break;

        case NT35560_NORMAL_MODE :
            
            break;

        case NT35560_STANDBY :
            
            (void)mddi_nt35560_set_cabc_on();
            
            (void)mddi_nt35560_exit_standby();
            
            mddi_nt35560_set_disp_on();
            break;

        case NT35560_DEEP_STANDBY :
            
            (void)mddi_nt35560_exit_deep_standby();
            
            mddi_nt35560_initial_setup();
            
            (void)mddi_nt35560_set_cabc_on();
            
            (void)mddi_nt35560_exit_standby();
            
            mddi_nt35560_set_disp_on();
            break;

        default :
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n",
                         __func__, __LINE__, curr_stat);
            break;
    }

    
    mddi_nt35560_state_transition(curr_stat, NT35560_NORMAL_MODE);

    return;
}












int mddi_nt35560_power_seq(int on)
{
    mddi_nt35560_state_t curr_stat;

    
    curr_stat = mddi_nt35560_state;

    switch (curr_stat)
    {
        case NT35560_STATE_OFF :
            if ( on )
            {
                
                if( mddi_nt35560_power_ctl(1) != 0 )
                    return -ENODEV;

                
                mddi_nt35560_initial_setup();

                
                (void)mddi_nt35560_set_cabc_on();

                
                (void)mddi_nt35560_exit_standby();

                
                mddi_nt35560_state_transition(curr_stat, NT35560_READY);
            }
            break;

        case NT35560_READY :
            if ( !on )
            {
                
                MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n", __func__, __LINE__, curr_stat);
            }
            break;

        case NT35560_NORMAL_MODE :
            if ( !on )
            {
                
                mddi_nt35560_set_disp_off();

                
                (void)mddi_nt35560_enter_standby();

                
                if( mddi_nt35560_power_ctl(0) != 0 )
                    return -ENODEV;

                
                mddi_nt35560_state_transition(curr_stat, NT35560_STATE_OFF);
            }
            break;

        case NT35560_STANDBY :
            
        case NT35560_DEEP_STANDBY :
            
        default :
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n", __func__, __LINE__, curr_stat);
            break;
    }

    return 0;
}











static void mddi_nt35560_backlight_ctl(int flg)
{
    int ret;
    struct led_backlight_ctrl led_req;

    
    memset(&led_req, 0x00, sizeof(led_req));

    if (flg == NT35560_LCD_BACKLIGHT_OFF)
    {
        
        led_req.mleden = BD6082GUL_LED_OFF;
        
        led_req.wpwmen = BD6082GUL_LED_OFF;
    }
    else
    {
        
        led_req.mleden = BD6082GUL_LED_ON;
        if (nt35560_cabc_sts == NT35560_LCD_CABC_ON)
        {
            
            led_req.wpwmen = BD6082GUL_LED_ON;
        }
        else
        {
            
            led_req.wpwmen = BD6082GUL_LED_OFF;
        }
    }

    
    ret = bd6082gul_main_lcd_set(&led_req);
    if (ret == BD6082GUL_LED_SET_RESERVED)
    {
        MDDI_MSG_NOTICE("%s(%d): main_lcd_set Command reserved.\n",
                        __func__, __LINE__);
    }
    else if (ret != BD6082GUL_LED_SET_OK)
    {
        MDDI_MSG_ERR("%s(%d): main_lcd_set %s failed! (ret=0x%08x)\n",
                     __func__, __LINE__,
                     (flg == NT35560_LCD_BACKLIGHT_OFF ? "OFF" : "ON"), ret);
    }

    return;
}










static void mddi_nt35560_set_backlight(struct msm_fb_data_type *mfd)
{
    int ret;
    int bl_level;
    int flg_sw = NT35560_LCD_BACKLIGHT_OFF;

    if(mfd == NULL)
    {
        MDDI_MSG_ERR("%s(%d): NULL parameter.\n", __func__, __LINE__);
        return;
    }

    
    bl_level = mfd->bl_level - 1;
    if (bl_level >= 0)
    {
        ret = bd6082gul_main_lcd_bright((unsigned char)(bl_level));
        if (ret == BD6082GUL_LED_SET_RESERVED)
        {
            MDDI_MSG_NOTICE("%s(%d): main_lcd_bright set reserved.\n",
                            __func__, __LINE__);
        }
        else if (ret != BD6082GUL_LED_SET_OK)
        {
            MDDI_MSG_ERR("%s(%d): main_lcd_bright error. (ret=0x%08X)\n",
                         __func__, __LINE__, ret);
            return;
        }

        flg_sw = NT35560_LCD_BACKLIGHT_ON;
    }

    
    mddi_nt35560_backlight_ctl(flg_sw);

    return;
}











int mddi_nt35560_cabc_ctl(int flg)
{

    if (flg == 0)
    {
        
        nt35560_cabc_sts = NT35560_LCD_CABC_OFF;
        mddi_nt35560_backlight_ctl(NT35560_LCD_BACKLIGHT_ON);
    }
    else
    {
        
        nt35560_cabc_sts = NT35560_LCD_CABC_ON;
        mddi_nt35560_backlight_ctl(NT35560_LCD_BACKLIGHT_ON);
    }

    return 0;
}










static void mddi_nt35560_vsync_set_handler(msm_fb_vsync_handler_type  handler,
                                           void                      *arg)
{
    
    return;
}










static void mddi_nt35560_vsync_detected(boolean detected)
{
    
    return;
}












static int mddi_nt35560_on(struct platform_device *pdev)
{
    struct msm_fb_data_type *mfd;
    mddi_nt35560_state_t curr_stat;

    mfd = platform_get_drvdata(pdev);
    if (!mfd)
        return -ENODEV;

    if (mfd->key != MFD_KEY)
        return -EINVAL;

    
    curr_stat = mddi_nt35560_state;

    switch (curr_stat)
    {
        case NT35560_STATE_OFF :
            if( mddi_nt35560_power_ctl(1) != 0 )
                return -ENODEV;

            
        case NT35560_STANDBY :
            
            mddi_nt35560_initial_setup();

            
            (void)mddi_nt35560_set_cabc_on();

            
            (void)mddi_nt35560_exit_standby();
            break;

        case NT35560_DEEP_STANDBY :
            
            (void)mddi_nt35560_exit_deep_standby();

            
            mddi_nt35560_initial_setup();

            
            (void)mddi_nt35560_set_cabc_on();

            
            (void)mddi_nt35560_exit_standby();
            break;

        case NT35560_READY :
            

        case NT35560_NORMAL_MODE :
            
            break;

        default :
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n",
                         __func__, __LINE__, curr_stat);
            break;
    }

    
    if (curr_stat != NT35560_NORMAL_MODE)
        mddi_nt35560_state_transition(curr_stat, NT35560_READY);

    return 0;
}












static int mddi_nt35560_off(struct platform_device *pdev)
{
    struct msm_fb_data_type *mfd;
    mddi_nt35560_state_t curr_stat;

    mfd = platform_get_drvdata(pdev);
    if (!mfd)
        return -ENODEV;

    if (mfd->key != MFD_KEY)
        return -EINVAL;

    
    curr_stat = mddi_nt35560_state;

    switch (curr_stat)
    {
        case NT35560_STATE_OFF :
            break;

        case NT35560_READY :
            
            (void)mddi_nt35560_enter_standby();

            
            if( mddi_nt35560_power_ctl(0) != 0 )
                return -ENODEV;
            break;

        case NT35560_NORMAL_MODE :
            
            mddi_nt35560_set_disp_off();
            
            (void)mddi_nt35560_enter_standby();

            
            if( mddi_nt35560_power_ctl(0) != 0 )
                return -ENODEV;
            break;

        case NT35560_STANDBY :
            
            if( mddi_nt35560_power_ctl(0) != 0 )
                return -ENODEV;
            break;

        case NT35560_DEEP_STANDBY :
            
            (void)mddi_nt35560_exit_deep_standby();
            
            mddi_nt35560_initial_setup();
            
            if( mddi_nt35560_power_ctl(0) != 0 )
                return -ENODEV;
            break;

        default :
            
            MDDI_MSG_ERR("%s(%d): curr_stat=%d.\n",
                         __func__, __LINE__, curr_stat);
            break;
    }

    
    mddi_nt35560_state_transition(curr_stat, NT35560_STATE_OFF);

    return 0;
}












static int __devinit mddi_nt35560_probe(struct platform_device *pdev)

{

    if (pdev->id == 0)
    {
        mddi_nt35560_pdata = pdev->dev.platform_data;
        return 0;
    }

    msm_fb_add_device(pdev);

    return 0;
}


static struct platform_driver this_driver = {

    .probe  = mddi_nt35560_probe,
    .driver = {
        .name = "mddi_nt35560"
    },
};

static struct msm_fb_panel_data mddi_nt35560_panel_data = {
    .on  = mddi_nt35560_on,
    .off = mddi_nt35560_off
};










void mddi_nt35560_enable_display(void)
{
    mddi_nt35560_state_t curr_stat = mddi_nt35560_state;

    if (curr_stat == NT35560_READY)
    {
        
        mddi_nt35560_set_disp_on();

        
        mddi_nt35560_state_transition(curr_stat, NT35560_NORMAL_MODE);
    }

    return;
}











boolean mddi_nt35560_displaying_chk( void )
{
    if( mddi_nt35560_state == NT35560_NORMAL_MODE )
        return TRUE;
    else
        return FALSE;
}













int mddi_nt35560_device_register(struct msm_panel_info *pinfo,
                                 u32 channel, u32 panel)
{
    struct platform_device *pdev = NULL;
    int ret;

    pdev = platform_device_alloc("mddi_nt35560", (panel << 8)|channel);
    if (!pdev)
        return -ENOMEM;

    mddi_nt35560_panel_data.set_backlight = mddi_nt35560_set_backlight;

    if (pinfo->lcd.vsync_enable)
    {
        mddi_nt35560_panel_data.set_vsync_notifier = mddi_nt35560_vsync_set_handler;
        mddi_lcd.vsync_detected = mddi_nt35560_vsync_detected;
    }

    mddi_nt35560_panel_data.panel_info = *pinfo;

    ret = platform_device_add_data(pdev, &mddi_nt35560_panel_data, sizeof(mddi_nt35560_panel_data));
    if (ret)
    {
        
        MDDI_MSG_ERR("%s(%d): platform_device_add_data failed! ret=%d.\n",
                     __func__, __LINE__, ret);
        goto err_device_put;
    }

    ret = platform_device_add(pdev);
    if (ret)
    {
        MDDI_MSG_ERR("%s(%d): platform_device_add failed! ret=%d.\n",
                     __func__, __LINE__, ret);
        goto err_device_put;
    }

    return 0;

err_device_put:
    platform_device_put(pdev);
    return ret;
}










void mddi_nt35560_register_access_packet(uint32_t reg_addr, uint32_t set_data)
{
    mddi_nt35560_write(reg_addr, set_data, TRUE);

    return;
}










irqreturn_t mddi_nt35560_lcd_vsync_isr( int irq, void *data )
{
    unsigned int   channel_irq;
    wait_queue_head_t *wq = &mddi_nt35560_vsync_wait;

    
    do_gettimeofday(&mddi_nt35560_timetemp[mddi_nt35560_lcd_isr_cnt]);

    mddi_nt35560_lcd_isr_cnt++;

    
    if (mddi_nt35560_lcd_isr_cnt > 7)
    {
        channel_irq = MSM_GPIO_TO_INT( 30 );
        disable_irq_nosync( channel_irq );
        wake_up( wq );
    }

    return IRQ_HANDLED;

}










int mddi_nt35560_lcd_vsync_mintomax_average( struct msmfb_vsync_ave *vsync_ave )
{
    int           i, j;
    int           ret = 0;
    uint32        temp_val = 0;
    uint32        total_val = 0;
    uint32        ave_val = 0;
    uint32        integer = 0;
    uint32        decimal = 0;
    unsigned long flags;

    spin_lock_irqsave( &mddi_nt35560_spin_lock, flags);
    
    for (i = 1; i < 6; i++)
    {
        mddi_nt35560_difftemp[i-1] = mddi_nt35560_timetemp[i+1].tv_usec - mddi_nt35560_timetemp[i].tv_usec;
    }

    
    for (i = 5; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (mddi_nt35560_difftemp[j] > mddi_nt35560_difftemp[j+1])
            {
                temp_val = mddi_nt35560_difftemp[j];
                mddi_nt35560_difftemp[j] = mddi_nt35560_difftemp[j+1];
                mddi_nt35560_difftemp[j+1] = temp_val;
            }
        }
    }

    
    for (i = 1; i < 4; i++)
    {
        total_val += mddi_nt35560_difftemp[i];
    }

    
    if (total_val != 0)
    {
        ave_val = total_val / 3;                             
        integer = (1000 * 1000) / ave_val;                   
        decimal = ((1000 * 1000) % ave_val) * 10 / ave_val;  
    }
    spin_unlock_irqrestore( &mddi_nt35560_spin_lock, flags );
    
    vsync_ave->integer = integer;
    vsync_ave->decimal = decimal;
    return ret;
}














int mddi_nt35560_mdp_vsync_freq_check( struct msmfb_vsync_ave *vsync_ave )
{
    int            ret = 0;
    long           timeout;
    unsigned int   channel_irq;

    mddi_nt35560_lcd_isr_cnt = 0;

    
    channel_irq = MSM_GPIO_TO_INT( 30 );

    
    disable_irq_nosync( channel_irq );

    
    ret = gpio_tlmm_config(GPIO_CFG
            (30,
            0,
            GPIO_CFG_INPUT,
            GPIO_CFG_PULL_DOWN,
            GPIO_CFG_2MA),
            GPIO_CFG_ENABLE);

    ret = request_irq( channel_irq,
                       mddi_nt35560_lcd_vsync_isr,
                       IRQF_TRIGGER_RISING,
                       "VSYNC_GPIO",
                       0 );

    
    enable_irq( channel_irq );

    
    init_waitqueue_head( &mddi_nt35560_vsync_wait );
    timeout = wait_event_timeout( mddi_nt35560_vsync_wait, mddi_nt35560_lcd_isr_cnt > 7, MDDI_NT35560_VSYNC_TIMEOUT );
    
    
    free_irq( channel_irq, 0 );
    
    
    if(timeout == 0)
    {
        printk(KERN_ERR "mddi_nt35560_mdp_vsync_freq_check time out! \n");
        ret = -ENODEV;
    } 
    else
    {
        
        ret = mddi_nt35560_lcd_vsync_mintomax_average( vsync_ave );
    }
    

    return ret;
}











void mddi_nt35560_set_vsync_freq(struct msmfb_vsync_parame *vsync_parame, void* data)
{
    unsigned int vsync_freq;
    struct msm_fb_data_type *mfd = (struct msm_fb_data_type *)data;

    if(vsync_parame->set_data == 0x0000FFFF)
    {
        return;
    }

    
    vsync_freq = (vsync_parame->set_data >> 8);
    vsync_freq = (vsync_freq * 100) + (vsync_parame->set_data & 0xFF)*10;

    spin_lock( &mddi_nt35560_vsync_spin_lock );

    
    mfd->panel_info.lcd.refx100 = vsync_freq;
    mfd->lcd_ref_usec_time = 100000000 / mfd->panel_info.lcd.refx100;

    spin_unlock( &mddi_nt35560_vsync_spin_lock );


    mdp_hw_vsync_update_config(mfd);


    return;
}











static int __init mddi_nt35560_init(void)
{
    return platform_driver_register(&this_driver);
}











int mddi_nt35560_user_request_ctrl( struct msmfb_request_parame *data )
{
    int ret = 0;

    switch( data->request )
    {
        case MSM_FB_REQUEST_OVERLAY_ALPHA:
            ret = copy_from_user(&mdp4_overlay_argb_enable, data->data, sizeof(mdp4_overlay_argb_enable));
            break;

        default:
            
            MDDI_MSG_ERR("%s user_request error", __func__);
            break;
    }
    
    return ret;
}










void mddi_nt35560_set_standby_ctl( int on )
{
    mddi_nt35560_standby_ctl_flag = on;
    return;
}











int mddi_nt35560_set_cabc(struct msmfb_regset regset[])
{

    
    lcd_set_cabc_on[5].set_data = regset[5].set_data; 
    lcd_set_cabc_on[6].set_data = regset[6].set_data; 
    lcd_set_cabc_on[7].set_data = regset[7].set_data; 
    
    return 0;
}









void mddi_nt35560_notify_reboot( void )
{
    mddi_nt35560_state_t curr_stat;

    
    curr_stat = mddi_nt35560_state;

    
    switch ( curr_stat )
    {
        case NT35560_READY :
            
            (void)mddi_nt35560_enter_standby();
            break;

        case NT35560_NORMAL_MODE :
            
            mddi_nt35560_set_disp_off();
            
            (void)mddi_nt35560_enter_standby();
            break;

        case NT35560_DEEP_STANDBY :
            
        case NT35560_STANDBY :
            
        case NT35560_STATE_OFF :
            
            break;

        default :
            
            MDDI_MSG_ERR("mddi_nt35560_notify_reboot status error!!\n");
            break;
    }

    if((curr_stat == NT35560_READY ) || (curr_stat == NT35560_NORMAL_MODE ))
    {
        
        mddi_nt35560_state_transition(curr_stat, NT35560_STANDBY);
    }

    return;
}


module_init(mddi_nt35560_init);
