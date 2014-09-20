


#ifndef _AK7837A_SNDAMP_H
#define _AK7837A_SNDAMP_H
/*===========================================================================
 FILENAME : ak7837a_sndamp.h

 Copyright (C) 2010 NEC Corporation.
 No permission to use, copy, modify and distribute this software
 and its documentation for any purpose is granted.
 This software is provided under applicable license agreement only.
===========================================================================*/
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/





















#include "ak7837a_sndampi.h"    

#include "Diag_acad.h"















extern void ak7837a_power_on_handset( void );
extern void ak7837a_power_on_fmradio_handset( void );
extern void ak7837a_power_on_speaker_stereo( void );
extern void ak7837a_power_on_fmradio_speaker( void );
extern void ak7837a_power_on_headset_stereo_speaker_stereo( void );
extern void ak7837a_power_on_ptt_speaker_stereo( void );
extern void ak7837a_power_off( void );

extern char Diag_Audio_ak7837a_drive(diag_acad_ak7837a_drive stAk7837aDrive);


extern ak7837a_proc_device_type ak7837a_getCurrentDevice( void );


#endif 



