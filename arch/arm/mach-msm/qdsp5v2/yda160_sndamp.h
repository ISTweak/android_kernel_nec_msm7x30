#ifndef _YDA160_SNDAMP_H
#define _YDA160_SNDAMP_H
/*===========================================================================
 FILENAME : yda160_sndamp.h

 Copyright (C) 2010 NEC Corporation.
 No permission to use, copy, modify and distribute this software
 and its documentation for any purpose is granted.
 This software is provided under applicable license agreement only.
===========================================================================*/
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/










































#define SNDAMP_MAJOR                0
                                      
#define SNDAMP_DEVICECHR_NAME       "yda160amp"
                                      

#define SOUNDAMP_IOCTL_MAGIC        'a'
                         

























extern void sndamp_headset_stereo_power_on( void );


















extern void sndamp_speaker_stereo_power_on( void );


















extern void sndamp_fmradio_speaker_power_on( void );


















extern void sndamp_tty_headset_mono_power_on( void );


















extern void sndamp_headset_stereo_speaker_stereo_power_on( void );


















extern void sndamp_ptt_speaker_stereo_power_on( void );


















extern void sndamp_power_off( void );

#endif 

