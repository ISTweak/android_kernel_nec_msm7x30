/* Copyright (c) 2009, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Code Aurora nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/

#ifndef MDDI_NT35560_H
#define MDDI_NT35560_H

typedef enum {
    NT35560_STATE_OFF,     
    NT35560_READY,         
    NT35560_STANDBY,       
    NT35560_DEEP_STANDBY,  
    NT35560_NORMAL_MODE,   
} mddi_nt35560_state_t;

typedef struct
{
    uint32  reg_addr;      
    uint32  set_data;      
} mddi_nt35560_regset;

#define mddi_nt35560_write(__X, __Y, __Z) {\
    mddi_queue_register_write(__X, __Y, __Z, 0);\
}


int mddi_nt35560_device_register(struct msm_panel_info *pinfo, u32 channel, u32 panel);


void mddi_nt35560_set_idle_state(void);
int  mddi_nt35560_standby_ctl(int on);
int  mddi_nt35560_deep_standby_ctl(int on);
void mddi_nt35560_register_access_packet(uint32_t reg_addr, uint32_t set_data);
int  mddi_nt35560_lcd_vsync_mintomax_average(struct msmfb_vsync_ave *vsync_ave);
int  mddi_nt35560_mdp_vsync_freq_check(struct msmfb_vsync_ave *vsync_ave);
void mddi_nt35560_set_vsync_freq(struct msmfb_vsync_parame *vsync_parame, void* data);
void mddi_nt35560_enable_display(void);
int  mddi_nt35560_cabc_ctl(int flg);
boolean mddi_nt35560_displaying_chk( void );


int mddi_nt35560_user_request_ctrl( struct msmfb_request_parame *data );
void mddi_nt35560_set_standby_ctl( int on );



int  mddi_nt35560_set_cabc(struct msmfb_regset regset[]);



int mddi_nt35560_power_seq(int on);



void mddi_nt35560_notify_reboot( void );


#endif 
