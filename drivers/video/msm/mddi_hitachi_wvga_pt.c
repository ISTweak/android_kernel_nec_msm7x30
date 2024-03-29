/* Copyright (c) 2009, Code Aurora Forum. All rights reserved.
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
#include "mddi_ta8851.h"

static int __init mddi_hitachi_wvga_pt_init(void)
{
    int ret;
    struct msm_panel_info pinfo;


    ret = msm_fb_detect_client("mddi_hitachi_wvga_pt");
    if (ret)
        return 0;


    pinfo.xres = 480;
    pinfo.yres = 800;
    pinfo.type = MDDI_PANEL;
    pinfo.pdest = DISPLAY_1;
    pinfo.mddi.vdopkt = MDDI_DEFAULT_PRIM_PIX_ATTR;
    pinfo.wait_cycle = 0;
    pinfo.bpp = 16; 


    pinfo.mode2_xres = 0;
    pinfo.mode2_yres = 0;
    pinfo.mode2_bpp = 0;


    
    pinfo.lcd.vsync_enable = TRUE;
    
    pinfo.lcd.hw_vsync_mode = TRUE;
    pinfo.lcd.refx100 = 6000;
    pinfo.lcd.v_back_porch = 10; 
    pinfo.lcd.v_front_porch = 8;
    pinfo.lcd.v_pulse_width = 13;
    

    pinfo.lcd.vsync_notifier_period = (1 * HZ);
    pinfo.lcd.rev = 1;


    




    pinfo.bl_max = 0x64; 
    pinfo.bl_min = 0x00; 

    
    pinfo.clk_rate = 192000000;
    pinfo.clk_min =  190000000;
    pinfo.clk_max =  200000000;

    pinfo.fb_num = 2;

    ret = mddi_ta8851_device_register(&pinfo, 1, 1);
    if (ret)
        printk(KERN_ERR "%s: failed to register device!\n", __func__);

    return ret;
}


module_init(mddi_hitachi_wvga_pt_init);
