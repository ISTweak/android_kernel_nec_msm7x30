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

#ifndef MDDI_TA8851_H
#define MDDI_TA8851_H


#define INITIALIZE_SINGLE_SEQ (0)
#define SET_DISP_ON_SINGLE_SEQ (1)
#define SET_DISP_OFF_SINGLE_SEQ (2)
#define ENTER_SLEEP_SINGLE_SEQ (3)
#define EXIT_SLEEP_SINGLE_SEQ (4)
#define ENTER_DSTANDBY_SINGLE_SEQ (5)


typedef enum {
    TA8851_STATE_OFF,     
    TA8851_READY,         
    TA8851_STANDBY,       
    TA8851_DEEP_STANDBY,  
    TA8851_NORMAL_MODE,   
} mddi_ta8851_state_t;

typedef struct
{
    uint32  reg_addr;          
    uint32  set_data;          
} mddi_ta8851_regset;

#define mddi_ta8851_write(__X, __Y, __Z) {\
  mddi_queue_register_write(__X, __Y, TRUE, 0);\
}


int mddi_ta8851_device_register(struct msm_panel_info *pinfo, u32 channel, u32 panel);


void mddi_ta8851_set_idle_state( void );
int  mddi_ta8851_standby_ctl( int on );
int  mddi_ta8851_deep_standby_ctl( int on );

void mddi_ta8851_register_access_packet( uint32_t reg_addr, uint32_t set_data );



int mddi_ta8851_lcd_vsync_mintomax_average( struct msmfb_vsync_ave *vsync_ave );


int mddi_ta8851_mdp_vsync_freq_check( struct msmfb_vsync_ave *vsync_ave );





void mddi_ta8851_set_vsync_freq( struct msmfb_vsync_parame *vsync_parame, void* data );



void mddi_ta8851_enable_display( void );



int mddi_ta8851_user_request_ctrl( struct msmfb_request_parame *data );



boolean mddi_ta8851_displaying_chk( void );



void mddi_ta8851_set_standby_ctl( int on );



int mddi_ta8851_single_seq(int diag_cmd);




void mddi_ta8851_notify_reboot( void );




#endif 
