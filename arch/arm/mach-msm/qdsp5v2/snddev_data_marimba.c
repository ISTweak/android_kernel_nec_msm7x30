/* Copyright (c) 2009-2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/
#include <linux/platform_device.h>
#include <linux/debugfs.h>
#include <linux/mfd/msm-adie-codec.h>
#include <linux/uaccess.h>
#include <mach/qdsp5v2/snddev_icodec.h>


#include <mach/qdsp5v2/aux_pcm.h>
#include <mach/qdsp5v2/snddev_ecodec.h>
#include <mach/qdsp5v2/audio_dev_ctl.h>
#include <mach/qdsp5v2/snddev_virtual.h>
#include <mach/board.h>
#include <asm/mach-types.h>
#include <mach/gpio.h>
#include <mach/qdsp5v2/snddev_mi2s.h>
#include <mach/qdsp5v2/mi2s.h>
#include <mach/qdsp5v2/audio_acdb_def.h>


#include "Diag_com_appl.h"


#include "yda160_sndamp.h"





#include "linux/audio_compile_switch_apps.h"
#include "ak7837a_sndamp.h"


















    
    #include <mach/qdsp5v2/marimba_profile.h>
    












/* define the value for BT_SCO */
#define BT_SCO_PCM_CTL_VAL (PCM_CTL__RPCM_WIDTH__LINEAR_V |\
        PCM_CTL__TPCM_WIDTH__LINEAR_V)
#define BT_SCO_DATA_FORMAT_PADDING (DATA_FORMAT_PADDING_INFO__RPCM_FORMAT_V |\
        DATA_FORMAT_PADDING_INFO__TPCM_FORMAT_V)
#define BT_SCO_AUX_CODEC_INTF   AUX_CODEC_INTF_CTL__PCMINTF_DATA_EN_V






#define BT_A2DP_PCM_CTL_VAL (PCM_CTL__RPCM_WIDTH__LINEAR_V |\
				PCM_CTL__TPCM_WIDTH__LINEAR_V)
#define BT_A2DP_DATA_FORMAT_PADDING (DATA_FORMAT_PADDING_INFO__RPCM_FORMAT_V |\
				DATA_FORMAT_PADDING_INFO__TPCM_FORMAT_V)
#define BT_A2DP_AUX_CODEC_INTF   AUX_CODEC_INTF_CTL__PCMINTF_DATA_EN_V





#ifdef CONFIG_DEBUG_FS
static struct dentry *debugfs_hsed_config;
static void snddev_hsed_config_modify_setting(int type);
static void snddev_hsed_config_restore_setting(void);
#endif

static struct adie_codec_action_unit iearpiece_48KHz_osr256_actions[] =
  HANDSET_RX_48000_OSR_256;

static struct adie_codec_hwsetting_entry iearpiece_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = iearpiece_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(iearpiece_48KHz_osr256_actions),
  }
};





struct adie_codec_dev_profile iearpiece_profile = {


  .path_type = ADIE_CODEC_RX,
  .settings = iearpiece_settings,
  .setting_sz = ARRAY_SIZE(iearpiece_settings),
};

static struct snddev_icodec_data snddev_iearpiece_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "handset_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HANDSET_SPKR,
  .profile = &iearpiece_profile,
  .channel_mode = 1,
  .pmctl_id = NULL,
  .pmctl_id_sz = 0,
  .default_sample_rate = 48000,






	.pamp_on  = &ak7837a_power_on_handset,
	.pamp_off = &ak7837a_power_off,

















  .property = SIDE_TONE_MASK,

  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = -2100,  
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = -2100   

};

static struct platform_device msm_iearpiece_device = {
  .name = "snddev_icodec",
  .id = 0,
  .dev = { .platform_data = &snddev_iearpiece_data },
};





static struct adie_codec_action_unit imic_8KHz_osr256_actions[] =

  HANDSET_TX_8000_OSR_256_VE329;













static struct adie_codec_action_unit imic_16KHz_osr256_actions[] =
  HANDSET_TX_16000_OSR_256;

static struct adie_codec_action_unit imic_48KHz_osr256_actions[] =
  HANDSET_TX_48000_OSR_256;

static struct adie_codec_hwsetting_entry imic_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = imic_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(imic_8KHz_osr256_actions),
  },
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = imic_16KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(imic_16KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = imic_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(imic_48KHz_osr256_actions),
  }
};





struct adie_codec_dev_profile imic_profile = {


  .path_type = ADIE_CODEC_TX,
  .settings = imic_settings,
  .setting_sz = ARRAY_SIZE(imic_settings),
};

static enum hsed_controller imic_pmctl_id[] = {PM_HSED_CONTROLLER_0};

static struct snddev_icodec_data snddev_imic_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "handset_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HANDSET_MIC,
  .profile = &imic_profile,
  .channel_mode = 1,
  .pmctl_id = imic_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(imic_pmctl_id),
  .default_sample_rate = 48000,
  .pamp_on = NULL,
  .pamp_off = NULL,
};

static struct platform_device msm_imic_device = {
  .name = "snddev_icodec",
  .id = 1,
  .dev = { .platform_data = &snddev_imic_data },
};





static struct adie_codec_action_unit ihs_stereo_rx_48KHz_osr256_actions[] =


	HEADSET_STEREO_RX_LEGACY_48000_OSR_256_HPH;













static struct adie_codec_hwsetting_entry ihs_stereo_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ihs_stereo_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ihs_stereo_rx_48KHz_osr256_actions),
  }
};



         struct adie_codec_dev_profile ihs_stereo_rx_profile = {

  .path_type = ADIE_CODEC_RX,
  .settings = ihs_stereo_rx_settings,
  .setting_sz = ARRAY_SIZE(ihs_stereo_rx_settings),
};

static struct snddev_icodec_data snddev_ihs_stereo_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "headset_stereo_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HEADSET_SPKR_STEREO,
  .profile = &ihs_stereo_rx_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,









	.pamp_on  = NULL,
	.pamp_off = NULL,





















  .property = SIDE_TONE_MASK,
  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = -2100,  
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = -2100   

};

static struct platform_device msm_ihs_stereo_rx_device = {
  .name = "snddev_icodec",
  .id = 2,
  .dev = { .platform_data = &snddev_ihs_stereo_rx_data },
};





static struct adie_codec_action_unit ihs_mono_rx_48KHz_osr256_actions[] =

	HEADSET_RX_LEGACY_48000_OSR_256_HPH;













static struct adie_codec_hwsetting_entry ihs_mono_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ihs_mono_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ihs_mono_rx_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile ihs_mono_rx_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ihs_mono_rx_settings,
  .setting_sz = ARRAY_SIZE(ihs_mono_rx_settings),
};

static struct snddev_icodec_data snddev_ihs_mono_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "headset_mono_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HEADSET_SPKR_MONO,
  .profile = &ihs_mono_rx_profile,
  .channel_mode = 1,
  .default_sample_rate = 48000,
  .pamp_on = NULL,
  .pamp_off = NULL,
  .property = SIDE_TONE_MASK,





  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = -2100,    
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = -2100,    


};

static struct platform_device msm_ihs_mono_rx_device = {
  .name = "snddev_icodec",
  .id = 3,
  .dev = { .platform_data = &snddev_ihs_mono_rx_data },
};

static struct adie_codec_action_unit ihs_ffa_stereo_rx_48KHz_osr256_actions[] =
  HEADSET_STEREO_RX_CAPLESS_48000_OSR_256;

static struct adie_codec_hwsetting_entry ihs_ffa_stereo_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ihs_ffa_stereo_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ihs_ffa_stereo_rx_48KHz_osr256_actions),
  }
};

#ifdef CONFIG_DEBUG_FS
static struct adie_codec_action_unit
  ihs_ffa_stereo_rx_class_d_legacy_48KHz_osr256_actions[] =
  HEADSET_STEREO_RX_CLASS_D_LEGACY_48000_OSR_256;

static struct adie_codec_hwsetting_entry
  ihs_ffa_stereo_rx_class_d_legacy_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions =
    ihs_ffa_stereo_rx_class_d_legacy_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE
    (ihs_ffa_stereo_rx_class_d_legacy_48KHz_osr256_actions),
  }
};

static struct adie_codec_action_unit
  ihs_ffa_stereo_rx_class_ab_legacy_48KHz_osr256_actions[] =
  HEADSET_STEREO_RX_LEGACY_48000_OSR_256;

static struct adie_codec_hwsetting_entry
  ihs_ffa_stereo_rx_class_ab_legacy_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions =
    ihs_ffa_stereo_rx_class_ab_legacy_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE
    (ihs_ffa_stereo_rx_class_ab_legacy_48KHz_osr256_actions),
  }
};
#endif

static struct adie_codec_dev_profile ihs_ffa_stereo_rx_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ihs_ffa_stereo_rx_settings,
  .setting_sz = ARRAY_SIZE(ihs_ffa_stereo_rx_settings),
};

static struct snddev_icodec_data snddev_ihs_ffa_stereo_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "headset_stereo_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HEADSET_SPKR_STEREO,
  .profile = &ihs_ffa_stereo_rx_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,
  .voltage_on = msm_snddev_hsed_voltage_on,
  .voltage_off = msm_snddev_hsed_voltage_off,
  .max_voice_rx_vol[VOC_NB_INDEX] = -700,
  .min_voice_rx_vol[VOC_NB_INDEX] = -2200,
  .max_voice_rx_vol[VOC_WB_INDEX] = -900,
  .min_voice_rx_vol[VOC_WB_INDEX] = -2400,
};

static struct platform_device msm_ihs_ffa_stereo_rx_device = {
  .name = "snddev_icodec",
  .id = 4,
  .dev = { .platform_data = &snddev_ihs_ffa_stereo_rx_data },
};

static struct adie_codec_action_unit ihs_ffa_mono_rx_48KHz_osr256_actions[] =
  HEADSET_RX_CAPLESS_48000_OSR_256;

static struct adie_codec_hwsetting_entry ihs_ffa_mono_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ihs_ffa_mono_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ihs_ffa_mono_rx_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile ihs_ffa_mono_rx_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ihs_ffa_mono_rx_settings,
  .setting_sz = ARRAY_SIZE(ihs_ffa_mono_rx_settings),
};

static struct snddev_icodec_data snddev_ihs_ffa_mono_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "headset_mono_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HEADSET_SPKR_MONO,
  .profile = &ihs_ffa_mono_rx_profile,
  .channel_mode = 1,
  .default_sample_rate = 48000,
  .pamp_on = msm_snddev_hsed_voltage_on,
  .pamp_off = msm_snddev_hsed_voltage_off,
  .max_voice_rx_vol[VOC_NB_INDEX] = -700,
  .min_voice_rx_vol[VOC_NB_INDEX] = -2200,
  .max_voice_rx_vol[VOC_WB_INDEX] = -900,
  .min_voice_rx_vol[VOC_WB_INDEX] = -2400,
};

static struct platform_device msm_ihs_ffa_mono_rx_device = {
  .name = "snddev_icodec",
  .id = 5,
  .dev = { .platform_data = &snddev_ihs_ffa_mono_rx_data },
};

static struct adie_codec_action_unit ihs_mono_tx_8KHz_osr256_actions[] =
  HEADSET_MONO_TX_8000_OSR_256;






static struct adie_codec_action_unit ihs_mono_tx_16KHz_osr256_actions[] =


  HEADSET_MONO_TX_16000_OSR_256_VE329;













static struct adie_codec_action_unit ihs_mono_tx_48KHz_osr256_actions[] =
  HEADSET_MONO_TX_48000_OSR_256;

static struct adie_codec_hwsetting_entry ihs_mono_tx_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ihs_mono_tx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ihs_mono_tx_8KHz_osr256_actions),
  },
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = ihs_mono_tx_16KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ihs_mono_tx_16KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ihs_mono_tx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ihs_mono_tx_48KHz_osr256_actions),
  }
};





struct adie_codec_dev_profile ihs_mono_tx_profile = {


  .path_type = ADIE_CODEC_TX,
  .settings = ihs_mono_tx_settings,
  .setting_sz = ARRAY_SIZE(ihs_mono_tx_settings),
};

static struct snddev_icodec_data snddev_ihs_mono_tx_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "headset_mono_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HEADSET_MIC,
  .profile = &ihs_mono_tx_profile,
  .channel_mode = 1,
  .pmctl_id = NULL,
  .pmctl_id_sz = 0,
  .default_sample_rate = 48000,
  .pamp_on = msm_snddev_tx_route_config,
  .pamp_off = msm_snddev_tx_route_deconfig,
};

static struct platform_device msm_ihs_mono_tx_device = {
  .name = "snddev_icodec",
  .id = 6,
  .dev = { .platform_data = &snddev_ihs_mono_tx_data },
};

static struct adie_codec_action_unit ifmradio_handset_VE313_actions[] =
  FM_HANDSET_OSR_64;

static struct adie_codec_hwsetting_entry ifmradio_handset_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ifmradio_handset_VE313_actions,
    .action_sz = ARRAY_SIZE(ifmradio_handset_VE313_actions),
  }
};

static struct adie_codec_dev_profile ifmradio_handset_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ifmradio_handset_settings,
  .setting_sz = ARRAY_SIZE(ifmradio_handset_settings),
};

static struct snddev_icodec_data snddev_ifmradio_handset_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_FM),
  .name = "fmradio_handset_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_LP_FM_SPKR_PHONE_STEREO_RX,
  .profile = &ifmradio_handset_profile,
  .channel_mode = 1,
  .default_sample_rate = 8000,





	.pamp_on  = &ak7837a_power_on_fmradio_handset,
	.pamp_off = &ak7837a_power_off,













  .dev_vol_type = SNDDEV_DEV_VOL_DIGITAL,
};

static struct platform_device msm_ifmradio_handset_device = {
  .name = "snddev_icodec",
  .id = 7,
  .dev = { .platform_data = &snddev_ifmradio_handset_data },
};





static struct adie_codec_action_unit ispeaker_rx_48KHz_osr256_actions[] =

   SPEAKER_PHONE_MONO_RX_48000_OSR_256;













static struct adie_codec_hwsetting_entry ispeaker_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,







    .actions = ispeaker_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispeaker_rx_48KHz_osr256_actions),













  }
};





struct adie_codec_dev_profile ispeaker_rx_profile = {


  .path_type = ADIE_CODEC_RX,
  .settings = ispeaker_rx_settings,
  .setting_sz = ARRAY_SIZE(ispeaker_rx_settings),
};

static struct snddev_icodec_data snddev_ispeaker_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "speaker_stereo_rx",
  .copp_id = 0,





  .acdb_id = ACDB_ID_SPKR_PHONE_MONO,







  .profile = &ispeaker_rx_profile,



  .channel_mode = 1,













  .pmctl_id = NULL,
  .pmctl_id_sz = 0,
  .default_sample_rate = 48000,













	.pamp_on  = &ak7837a_power_on_speaker_stereo,
	.pamp_off = &ak7837a_power_off,























  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = -2100,  
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = -2100,  

};

static struct platform_device msm_ispeaker_rx_device = {
  .name = "snddev_icodec",
  .id = 8,
  .dev = { .platform_data = &snddev_ispeaker_rx_data },

};






static struct adie_codec_action_unit ifmradio_speaker_VE313_actions[] =


	FM_SPEAKER_MONO_OSR_64;













static struct adie_codec_hwsetting_entry ifmradio_speaker_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ifmradio_speaker_VE313_actions,
    .action_sz = ARRAY_SIZE(ifmradio_speaker_VE313_actions),
  }
};

static struct adie_codec_dev_profile ifmradio_speaker_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ifmradio_speaker_settings,
  .setting_sz = ARRAY_SIZE(ifmradio_speaker_settings),
};

static struct snddev_icodec_data snddev_ifmradio_speaker_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_FM),
  .name = "fmradio_speaker_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_LP_FM_SPKR_PHONE_STEREO_RX,
  .profile = &ifmradio_speaker_profile,
  .channel_mode = 1,
  .default_sample_rate = 8000,






	.pamp_on  = &ak7837a_power_on_fmradio_speaker,
	.pamp_off = &ak7837a_power_off,
























  .dev_vol_type = SNDDEV_DEV_VOL_DIGITAL,
};

static struct platform_device msm_ifmradio_speaker_device = {
  .name = "snddev_icodec",
  .id = 9,
  .dev = { .platform_data = &snddev_ifmradio_speaker_data },
};

static struct adie_codec_action_unit ifmradio_headset_VE313_actions[] =
  FM_HEADSET_STEREO_CLASS_D_LEGACY_OSR_64;

static struct adie_codec_hwsetting_entry ifmradio_headset_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ifmradio_headset_VE313_actions,
    .action_sz = ARRAY_SIZE(ifmradio_headset_VE313_actions),
  }
};

static struct adie_codec_dev_profile ifmradio_headset_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ifmradio_headset_settings,
  .setting_sz = ARRAY_SIZE(ifmradio_headset_settings),
};

static struct snddev_icodec_data snddev_ifmradio_headset_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_FM),
  .name = "fmradio_headset_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_LP_FM_HEADSET_SPKR_STEREO_RX,
  .profile = &ifmradio_headset_profile,
  .channel_mode = 1,
  .default_sample_rate = 8000,
  .pamp_on = NULL,
  .pamp_off = NULL,
  .dev_vol_type = SNDDEV_DEV_VOL_DIGITAL,
};

static struct platform_device msm_ifmradio_headset_device = {
  .name = "snddev_icodec",
  .id = 10,
  .dev = { .platform_data = &snddev_ifmradio_headset_data },
};


static struct adie_codec_action_unit ifmradio_ffa_headset_VE313_actions[] =
  FM_HEADSET_CLASS_AB_STEREO_CAPLESS_OSR_64;

static struct adie_codec_hwsetting_entry ifmradio_ffa_headset_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ifmradio_ffa_headset_VE313_actions,
    .action_sz = ARRAY_SIZE(ifmradio_ffa_headset_VE313_actions),
  }
};

static struct adie_codec_dev_profile ifmradio_ffa_headset_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ifmradio_ffa_headset_settings,
  .setting_sz = ARRAY_SIZE(ifmradio_ffa_headset_settings),
};

static struct snddev_icodec_data snddev_ifmradio_ffa_headset_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_FM),
  .name = "fmradio_headset_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_LP_FM_HEADSET_SPKR_STEREO_RX,
  .profile = &ifmradio_ffa_headset_profile,
  .channel_mode = 1,
  .default_sample_rate = 8000,
  .pamp_on = msm_snddev_hsed_voltage_on,
  .pamp_off = msm_snddev_hsed_voltage_off,
  .dev_vol_type = SNDDEV_DEV_VOL_DIGITAL,
};

static struct platform_device msm_ifmradio_ffa_headset_device = {
  .name = "snddev_icodec",
  .id = 11,
  .dev = { .platform_data = &snddev_ifmradio_ffa_headset_data },
};

static struct snddev_ecodec_data snddev_bt_sco_earpiece_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "bt_sco_rx",
  .copp_id = 1,
  .acdb_id = ACDB_ID_BT_SCO_SPKR,
  .channel_mode = 1,
  .conf_pcm_ctl_val = BT_SCO_PCM_CTL_VAL,
  .conf_aux_codec_intf = BT_SCO_AUX_CODEC_INTF,
  .conf_data_format_padding_val = BT_SCO_DATA_FORMAT_PADDING,







  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = -2100,  
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = -2100,  

};

static struct snddev_ecodec_data snddev_bt_sco_mic_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "bt_sco_tx",
  .copp_id = 1,
  .acdb_id = ACDB_ID_BT_SCO_MIC,
  .channel_mode = 1,
  .conf_pcm_ctl_val = BT_SCO_PCM_CTL_VAL,
  .conf_aux_codec_intf = BT_SCO_AUX_CODEC_INTF,
  .conf_data_format_padding_val = BT_SCO_DATA_FORMAT_PADDING,
};

struct platform_device msm_bt_sco_earpiece_device = {
  .name = "msm_snddev_ecodec",
  .id = 0,
  .dev = { .platform_data = &snddev_bt_sco_earpiece_data },
};

struct platform_device msm_bt_sco_mic_device = {
  .name = "msm_snddev_ecodec",
  .id = 1,
  .dev = { .platform_data = &snddev_bt_sco_mic_data },
};





static struct adie_codec_action_unit idual_mic_endfire_8KHz_osr256_actions[] =

    MIC1_LEFT_LINE_IN_RIGHT_8000_OSR_256_VE329;













static struct adie_codec_hwsetting_entry idual_mic_endfire_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = idual_mic_endfire_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(idual_mic_endfire_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = idual_mic_endfire_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(idual_mic_endfire_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = idual_mic_endfire_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(idual_mic_endfire_8KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile idual_mic_endfire_profile = {
  .path_type = ADIE_CODEC_TX,
  .settings = idual_mic_endfire_settings,
  .setting_sz = ARRAY_SIZE(idual_mic_endfire_settings),
};

static enum hsed_controller idual_mic_endfire_pmctl_id[] = {
  PM_HSED_CONTROLLER_0, PM_HSED_CONTROLLER_2
};

static struct snddev_icodec_data snddev_idual_mic_endfire_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "handset_dual_mic_endfire_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HANDSET_MIC_ENDFIRE,
  .profile = &idual_mic_endfire_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,
  .pmctl_id = idual_mic_endfire_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(idual_mic_endfire_pmctl_id),
  .pamp_on = NULL,
  .pamp_off = NULL,
};

static struct platform_device msm_idual_mic_endfire_device = {
  .name = "snddev_icodec",
  .id = 12,
  .dev = { .platform_data = &snddev_idual_mic_endfire_data },
};


static struct snddev_icodec_data\
		snddev_idual_mic_endfire_real_stereo_data = {
	.capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
	.name = "handset_dual_mic_endfire_tx_real_stereo",
	.copp_id = 0,
	.acdb_id = PSEUDO_ACDB_ID,
	.profile = &idual_mic_endfire_profile,
	.channel_mode = REAL_STEREO_CHANNEL_MODE,
	.default_sample_rate = 48000,
	.pmctl_id = idual_mic_endfire_pmctl_id,
	.pmctl_id_sz = ARRAY_SIZE(idual_mic_endfire_pmctl_id),
	.pamp_on = NULL,
	.pamp_off = NULL,
};

static struct platform_device msm_real_stereo_tx_device = {
	.name = "snddev_icodec",
	.id = 26,
	.dev = { .platform_data =
			&snddev_idual_mic_endfire_real_stereo_data },
};




static struct adie_codec_action_unit idual_mic_bs_8KHz_osr256_actions[] =

    MIC1_LEFT_AUX_IN_RIGHT_8000_OSR_256_VE329;













static struct adie_codec_hwsetting_entry idual_mic_broadside_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = idual_mic_bs_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(idual_mic_bs_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = idual_mic_bs_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(idual_mic_bs_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = idual_mic_bs_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(idual_mic_bs_8KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile idual_mic_broadside_profile = {
  .path_type = ADIE_CODEC_TX,
  .settings = idual_mic_broadside_settings,
  .setting_sz = ARRAY_SIZE(idual_mic_broadside_settings),
};

static enum hsed_controller idual_mic_broadside_pmctl_id[] = {
  PM_HSED_CONTROLLER_0, PM_HSED_CONTROLLER_2
};

static struct snddev_icodec_data snddev_idual_mic_broadside_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "handset_dual_mic_broadside_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HANDSET_MIC_BROADSIDE,
  .profile = &idual_mic_broadside_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,
  .pmctl_id = idual_mic_broadside_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(idual_mic_broadside_pmctl_id),
  .pamp_on = NULL,
  .pamp_off = NULL,
};

static struct platform_device msm_idual_mic_broadside_device = {
  .name = "snddev_icodec",
  .id = 13,
  .dev = { .platform_data = &snddev_idual_mic_broadside_data },
};




static struct adie_codec_action_unit ispk_dual_mic_ef_8KHz_osr256_actions[] =

    SPEAKER_MIC1_LEFT_LINE_IN_RIGHT_8000_OSR_256_VE329;













static struct adie_codec_hwsetting_entry ispk_dual_mic_ef_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ispk_dual_mic_ef_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispk_dual_mic_ef_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = ispk_dual_mic_ef_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispk_dual_mic_ef_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ispk_dual_mic_ef_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispk_dual_mic_ef_8KHz_osr256_actions),
  },
};

static struct adie_codec_dev_profile ispk_dual_mic_ef_profile = {
  .path_type = ADIE_CODEC_TX,
  .settings = ispk_dual_mic_ef_settings,
  .setting_sz = ARRAY_SIZE(ispk_dual_mic_ef_settings),
};

static struct snddev_icodec_data snddev_spk_idual_mic_endfire_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "speaker_dual_mic_endfire_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_SPKR_PHONE_MIC_ENDFIRE,
  .profile = &ispk_dual_mic_ef_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,
  .pmctl_id = idual_mic_endfire_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(idual_mic_endfire_pmctl_id),
  .pamp_on = NULL,
  .pamp_off = NULL,
};

static struct platform_device msm_spk_idual_mic_endfire_device = {
  .name = "snddev_icodec",
  .id = 14,
  .dev = { .platform_data = &snddev_spk_idual_mic_endfire_data },
};





static struct adie_codec_action_unit ispk_dual_mic_bs_8KHz_osr256_actions[] =


    SPEAKER_MIC1_LEFT_AUX_IN_RIGHT_8000_OSR_256_VE329;













static struct adie_codec_hwsetting_entry ispk_dual_mic_bs_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ispk_dual_mic_bs_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispk_dual_mic_bs_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = ispk_dual_mic_bs_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispk_dual_mic_bs_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ispk_dual_mic_bs_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispk_dual_mic_bs_8KHz_osr256_actions),
  },
};

static struct adie_codec_dev_profile ispk_dual_mic_bs_profile = {
  .path_type = ADIE_CODEC_TX,
  .settings = ispk_dual_mic_bs_settings,
  .setting_sz = ARRAY_SIZE(ispk_dual_mic_bs_settings),
};
static struct snddev_icodec_data snddev_spk_idual_mic_broadside_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "speaker_dual_mic_broadside_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_SPKR_PHONE_MIC_BROADSIDE,
  .profile = &ispk_dual_mic_bs_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,
  .pmctl_id = idual_mic_broadside_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(idual_mic_broadside_pmctl_id),
  .pamp_on = NULL,
  .pamp_off = NULL,
};

static struct platform_device msm_spk_idual_mic_broadside_device = {
  .name = "snddev_icodec",
  .id = 15,
  .dev = { .platform_data = &snddev_spk_idual_mic_broadside_data },
};

static struct adie_codec_action_unit itty_hs_mono_tx_8KHz_osr256_actions[] =
  TTY_HEADSET_MONO_TX_8000_OSR_256;

static struct adie_codec_hwsetting_entry itty_hs_mono_tx_settings[] = {
  
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = itty_hs_mono_tx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(itty_hs_mono_tx_8KHz_osr256_actions),
  },
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = itty_hs_mono_tx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(itty_hs_mono_tx_8KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = itty_hs_mono_tx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(itty_hs_mono_tx_8KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile itty_hs_mono_tx_profile = {
  .path_type = ADIE_CODEC_TX,
  .settings = itty_hs_mono_tx_settings,
  .setting_sz = ARRAY_SIZE(itty_hs_mono_tx_settings),
};

static struct snddev_icodec_data snddev_itty_hs_mono_tx_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE | SNDDEV_CAP_TTY),
  .name = "tty_headset_mono_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_TTY_HEADSET_MIC,
  .profile = &itty_hs_mono_tx_profile,
  .channel_mode = 1,
  .default_sample_rate = 48000,
  .pmctl_id = NULL,
  .pmctl_id_sz = 0,
  .pamp_on = NULL,
  .pamp_off = NULL,
};

static struct platform_device msm_itty_hs_mono_tx_device = {
  .name = "snddev_icodec",
  .id = 16,
  .dev = { .platform_data = &snddev_itty_hs_mono_tx_data },
};

static struct adie_codec_action_unit itty_hs_mono_rx_8KHz_osr256_actions[] =
  TTY_HEADSET_MONO_RX_CLASS_D_8000_OSR_256;

static struct adie_codec_action_unit itty_hs_mono_rx_16KHz_osr256_actions[] =
  TTY_HEADSET_MONO_RX_CLASS_D_16000_OSR_256;

static struct adie_codec_action_unit itty_hs_mono_rx_48KHz_osr256_actions[] =
  TTY_HEADSET_MONO_RX_CLASS_D_48000_OSR_256;

static struct adie_codec_hwsetting_entry itty_hs_mono_rx_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = itty_hs_mono_rx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(itty_hs_mono_rx_8KHz_osr256_actions),
  },
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = itty_hs_mono_rx_16KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(itty_hs_mono_rx_16KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = itty_hs_mono_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(itty_hs_mono_rx_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile itty_hs_mono_rx_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = itty_hs_mono_rx_settings,
  .setting_sz = ARRAY_SIZE(itty_hs_mono_rx_settings),
};

static struct snddev_icodec_data snddev_itty_hs_mono_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE | SNDDEV_CAP_TTY),
  .name = "tty_headset_mono_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_TTY_HEADSET_SPKR,
  .profile = &itty_hs_mono_rx_profile,
  .channel_mode = 1,
  .default_sample_rate = 48000,









	.pamp_on  = NULL,
	.pamp_off = NULL,
















  .max_voice_rx_vol[VOC_NB_INDEX] = 0,
  .min_voice_rx_vol[VOC_NB_INDEX] = 0,
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,
  .min_voice_rx_vol[VOC_WB_INDEX] = 0,
};

static struct platform_device msm_itty_hs_mono_rx_device = {
  .name = "snddev_icodec",
  .id = 17,
  .dev = { .platform_data = &snddev_itty_hs_mono_rx_data },
};







static struct adie_codec_action_unit ispeaker_tx_8KHz_osr256_actions[] =



    
    

        HANDSET_TX_8000_OSR_256_VE329;



    
























static struct adie_codec_action_unit ispeaker_tx_48KHz_osr256_actions[] =

    
	HANDSET_TX_48000_OSR_256;















static struct adie_codec_hwsetting_entry ispeaker_tx_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = ispeaker_tx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispeaker_tx_8KHz_osr256_actions),
  },
  { 
    .freq_plan = 16000,
    .osr = 256,
    .actions = ispeaker_tx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispeaker_tx_8KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ispeaker_tx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(ispeaker_tx_48KHz_osr256_actions),
  }
};



struct adie_codec_dev_profile ispeaker_tx_profile = {


  .path_type = ADIE_CODEC_TX,
  .settings = ispeaker_tx_settings,
  .setting_sz = ARRAY_SIZE(ispeaker_tx_settings),
};














static enum hsed_controller ispk_pmctl_id[] = {PM_HSED_CONTROLLER_0};




static struct snddev_icodec_data snddev_ispeaker_tx_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "speaker_mono_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_SPKR_PHONE_MIC,
  .profile = &ispeaker_tx_profile,
  .channel_mode = 1,
  .pmctl_id = ispk_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(ispk_pmctl_id),
  .default_sample_rate = 48000,
  .pamp_on = msm_snddev_tx_route_config,
  .pamp_off = msm_snddev_tx_route_deconfig,
};

static struct platform_device msm_ispeaker_tx_device = {
  .name = "snddev_icodec",
  .id = 18,
  .dev = { .platform_data = &snddev_ispeaker_tx_data },
};

static struct adie_codec_action_unit iearpiece_ffa_48KHz_osr256_actions[] =
  HANDSET_RX_48000_OSR_256_FFA;

static struct adie_codec_hwsetting_entry iearpiece_ffa_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = iearpiece_ffa_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(iearpiece_ffa_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile iearpiece_ffa_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = iearpiece_ffa_settings,
  .setting_sz = ARRAY_SIZE(iearpiece_ffa_settings),
};

static struct snddev_icodec_data snddev_iearpiece_ffa_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "handset_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HANDSET_SPKR,
  .profile = &iearpiece_ffa_profile,
  .channel_mode = 1,
  .pmctl_id = NULL,
  .pmctl_id_sz = 0,
  .default_sample_rate = 48000,
  .pamp_on = NULL,
  .pamp_off = NULL,
  .max_voice_rx_vol[VOC_NB_INDEX] = -700,
  .min_voice_rx_vol[VOC_NB_INDEX] = -2200,
  .max_voice_rx_vol[VOC_WB_INDEX] = -1400,
  .min_voice_rx_vol[VOC_WB_INDEX] = -2900,
};

static struct platform_device msm_iearpiece_ffa_device = {
  .name = "snddev_icodec",
  .id = 19,
  .dev = { .platform_data = &snddev_iearpiece_ffa_data },
};

static struct adie_codec_action_unit imic_ffa_8KHz_osr256_actions[] =
  HANDSET_TX_8000_OSR_256_FFA;

static struct adie_codec_action_unit imic_ffa_16KHz_osr256_actions[] =
  HANDSET_TX_16000_OSR_256_FFA;

static struct adie_codec_action_unit imic_ffa_48KHz_osr256_actions[] =
  HANDSET_TX_48000_OSR_256_FFA;

static struct adie_codec_hwsetting_entry imic_ffa_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = imic_ffa_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(imic_ffa_8KHz_osr256_actions),
  },
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = imic_ffa_16KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(imic_ffa_16KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = imic_ffa_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(imic_ffa_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile imic_ffa_profile = {
  .path_type = ADIE_CODEC_TX,
  .settings = imic_ffa_settings,
  .setting_sz = ARRAY_SIZE(imic_ffa_settings),
};

static struct snddev_icodec_data snddev_imic_ffa_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "handset_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HANDSET_MIC,
  .profile = &imic_ffa_profile,
  .channel_mode = 1,
  .pmctl_id = imic_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(imic_pmctl_id),
  .default_sample_rate = 48000,
  .pamp_on = NULL,
  .pamp_off = NULL,
};

static struct platform_device msm_imic_ffa_device = {
  .name = "snddev_icodec",
  .id = 20,
  .dev = { .platform_data = &snddev_imic_ffa_data },
};







static struct adie_codec_action_unit
	ihs_stereo_speaker_stereo_rx_48KHz_osr256_actions[] =






		HEADSET_STEREO_SPEAKER_MONO_RX_CAPLESS_48000_OSR_256_HPH;

























static struct adie_codec_hwsetting_entry
  ihs_stereo_speaker_stereo_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = ihs_stereo_speaker_stereo_rx_48KHz_osr256_actions,
    .action_sz =
    ARRAY_SIZE(ihs_stereo_speaker_stereo_rx_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile ihs_stereo_speaker_stereo_rx_profile = {
  .path_type = ADIE_CODEC_RX,
  .settings = ihs_stereo_speaker_stereo_rx_settings,
  .setting_sz = ARRAY_SIZE(ihs_stereo_speaker_stereo_rx_settings),
};

static struct snddev_icodec_data snddev_ihs_stereo_speaker_stereo_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "headset_stereo_speaker_stereo_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_HEADSET_STEREO_PLUS_SPKR_STEREO_RX,
  .profile = &ihs_stereo_speaker_stereo_rx_profile,





  .channel_mode = 1,











  .default_sample_rate = 48000,





	.pamp_on  = &ak7837a_power_on_headset_stereo_speaker_stereo,
	.pamp_off = &ak7837a_power_off,























  .voltage_on = msm_snddev_hsed_voltage_on,
  .voltage_off = msm_snddev_hsed_voltage_off,







  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = -2100,  
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = -2100,  

};

static struct platform_device msm_ihs_stereo_speaker_stereo_rx_device = {
  .name = "snddev_icodec",
  .id = 21,
  .dev = { .platform_data = &snddev_ihs_stereo_speaker_stereo_rx_data },
};








static struct adie_codec_action_unit isubmic_8KHz_osr256_actions[] =

    SUBMIC_TX_8000_OSR_256_VE329;










static struct adie_codec_action_unit isubmic_48KHz_osr256_actions[] =
  SUBMIC_TX_48000_OSR_256;

static struct adie_codec_hwsetting_entry isubmic_tx_settings[] = {
  {
    .freq_plan = 8000,
    .osr       = 256,
    .actions   = isubmic_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(isubmic_8KHz_osr256_actions),
  },
  {
    .freq_plan = 16000,
    .osr       = 256,
    .actions   = isubmic_8KHz_osr256_actions,  
    .action_sz = ARRAY_SIZE(isubmic_8KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr       = 256,
    .actions   = isubmic_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(isubmic_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile isubmic_profile = {
  .path_type  = ADIE_CODEC_TX,
  .settings   = isubmic_tx_settings,
  .setting_sz = ARRAY_SIZE(isubmic_tx_settings),
};


















static enum hsed_controller isubmic_pmctl_id[] = {PM_HSED_CONTROLLER_0};




static struct snddev_icodec_data snddev_isubmic_tx_data = {
  .capability          = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name                = "submic_tx",
  .copp_id             = 0,






  .acdb_id             = ACDB_ID_TX_SUBMIC,


  .profile             = &isubmic_profile,
  .channel_mode        = 1,
  .pmctl_id            = isubmic_pmctl_id,
  .pmctl_id_sz         = ARRAY_SIZE(isubmic_pmctl_id),
  .default_sample_rate = 48000,
  .pamp_on             = NULL,
  .pamp_off            = NULL,
};

static struct platform_device msm_isubmic_tx_device = {
  .name = "snddev_icodec",
  .id   = 30,
  .dev  = { .platform_data = &snddev_isubmic_tx_data },
};




static struct adie_codec_action_unit iusb_stereo_rx_48KHz_osr256_actions[] =
  USB_RX_48000_OSR_256;

static struct adie_codec_hwsetting_entry iusb_stereo_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr       = 256,
    .actions   = iusb_stereo_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(iusb_stereo_rx_48KHz_osr256_actions),
  },
};





         struct adie_codec_dev_profile iusb_stereo_rx = {





  .path_type  = ADIE_CODEC_RX,
  .settings   = iusb_stereo_rx_settings,
  .setting_sz = ARRAY_SIZE(iusb_stereo_rx_settings),
};

static struct snddev_icodec_data snddev_iusb_stereo_rx_data = {
  .capability          = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name                = "usb_stereo_rx",
  .copp_id             = 0,


  .acdb_id             = ACDB_ID_RX_USB_AUDIO,

  .profile             = &iusb_stereo_rx,
  .channel_mode        = 2,
  .pmctl_id            = NULL,
  .pmctl_id_sz         = 0,
  .default_sample_rate = 48000,
  .pamp_on             = NULL,
  .pamp_off            = NULL,
  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = 0,    
};

static struct platform_device msm_iusb_stereo_rx_device = {
  .name = "snddev_icodec",
  .id = 31,
  .dev = { .platform_data = &snddev_iusb_stereo_rx_data },
};




static struct adie_codec_action_unit iptt_speaker_tx_8KHz_osr256_actions[] =
  PTT_SPEAKER_TX_8000_OSR_256;

static struct adie_codec_action_unit iptt_speaker_tx_48KHz_osr256_actions[] =
  PTT_SPEAKER_TX_48000_OSR_256;

static struct adie_codec_hwsetting_entry iptt_speaker_tx_settings[] = {
  {
    .freq_plan = 8000,
    .osr       = 256,
    .actions   = iptt_speaker_tx_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(iptt_speaker_tx_8KHz_osr256_actions),
  },
  {
    .freq_plan = 16000,
    .osr       = 256,
    .actions   = iptt_speaker_tx_8KHz_osr256_actions,    
    .action_sz = ARRAY_SIZE(iptt_speaker_tx_8KHz_osr256_actions),
  },
  {
    .freq_plan = 48000,
    .osr       = 256,
    .actions   = iptt_speaker_tx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(iptt_speaker_tx_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile iptt_speaker_tx_profile = {
  .path_type  = ADIE_CODEC_TX,
  .settings   = iptt_speaker_tx_settings,
  .setting_sz = ARRAY_SIZE(iptt_speaker_tx_settings),
};

static enum hsed_controller iptt_spk_pmctl_id[] = {PM_HSED_CONTROLLER_0};

static struct snddev_icodec_data snddev_iptt_speaker_tx_data = {
  .capability          = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name                = "ptt_speaker_mono_tx",
  .copp_id             = 0,


  .acdb_id             = ACDB_ID_TX_PTT_SPEAKER,

  .profile             = &iptt_speaker_tx_profile,
  .channel_mode        = 1,
  .pmctl_id            = iptt_spk_pmctl_id,
  .pmctl_id_sz         = ARRAY_SIZE(iptt_spk_pmctl_id),
  .default_sample_rate = 48000,
  .pamp_on             = NULL,
  .pamp_off            = NULL,
};

static struct platform_device msm_iptt_speaker_tx_device = {
  .name = "snddev_icodec",
  .id   = 32,
  .dev  = { .platform_data = &snddev_iptt_speaker_tx_data },
};









static struct adie_codec_action_unit iptt_speaker_rx_48KHz_osr256_actions[] =

   PTT_SPEAKER_MONO_RX_48000_OSR_256;










static struct adie_codec_hwsetting_entry iptt_speaker_rx_settings[] = {
  {
    .freq_plan = 48000,
    .osr       = 256,
    .actions   = iptt_speaker_rx_48KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(iptt_speaker_rx_48KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile iptt_speaker_rx_profile = {
  .path_type  = ADIE_CODEC_RX,
  .settings   = iptt_speaker_rx_settings,
  .setting_sz = ARRAY_SIZE(iptt_speaker_rx_settings),
};

static struct snddev_icodec_data snddev_iptt_speaker_rx_data = {
  .capability          = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name                = "ptt_speaker_stereo_rx",
  .copp_id             = 0,


  .acdb_id             = ACDB_ID_RX_PTT_SPEAKER,

  .profile             = &iptt_speaker_rx_profile,




  .channel_mode = 1,








  .pmctl_id            = NULL,
  .pmctl_id_sz         = 0,
  .default_sample_rate = 48000,




	.pamp_on             = &ak7837a_power_on_ptt_speaker_stereo,
	.pamp_off            = &ak7837a_power_off,


















  .max_voice_rx_vol[VOC_NB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_NB_INDEX] = -2100,  
  .max_voice_rx_vol[VOC_WB_INDEX] = 0,    
  .min_voice_rx_vol[VOC_WB_INDEX] = -2100,  
};

static struct platform_device msm_iptt_speaker_rx_device = {
  .name = "snddev_icodec",
  .id   = 33,
  .dev  = { .platform_data = &snddev_iptt_speaker_rx_data },
};


static struct snddev_mi2s_data snddev_mi2s_stereo_rx_data = {
  .capability = SNDDEV_CAP_RX ,
  .name = "hdmi_stereo_rx",
  .copp_id = 3,
  .acdb_id = ACDB_ID_HDMI,
  .channel_mode = 2,
  .sd_lines = MI2S_SD_0,
  .route = msm_snddev_tx_route_config,
  .deroute = msm_snddev_tx_route_deconfig,
  .default_sample_rate = 48000,
};

static struct platform_device msm_snddev_mi2s_stereo_rx_device = {
  .name = "snddev_mi2s",
  .id = 0,
  .dev = { .platform_data = &snddev_mi2s_stereo_rx_data },
};


static struct snddev_mi2s_data snddev_mi2s_fm_tx_data = {
  .capability = SNDDEV_CAP_TX ,
  .name = "fmradio_stereo_tx",
  .copp_id = 2,
  .acdb_id = ACDB_ID_FM_TX,
  .channel_mode = 2,
  .sd_lines = MI2S_SD_3,
  .route = NULL,
  .deroute = NULL,
  .default_sample_rate = 48000,
};

static struct platform_device  msm_snddev_mi2s_fm_tx_device = {
  .name = "snddev_mi2s",
  .id = 1,
  .dev = { .platform_data = &snddev_mi2s_fm_tx_data},
};

static struct snddev_icodec_data snddev_fluid_imic_tx_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "handset_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_SPKR_PHONE_MIC,
  .profile = &ispeaker_tx_profile,
  .channel_mode = 1,
  .pmctl_id = ispk_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(ispk_pmctl_id),
  .default_sample_rate = 48000,
  .pamp_on = msm_snddev_tx_route_config,
  .pamp_off = msm_snddev_tx_route_deconfig,
};

static struct platform_device msm_fluid_imic_tx_device = {
  .name = "snddev_icodec",
  .id = 22,
  .dev = { .platform_data = &snddev_fluid_imic_tx_data },
};

static struct snddev_icodec_data snddev_fluid_iearpiece_rx_data = {
  .capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
  .name = "handset_rx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_SPKR_PHONE_STEREO,
  .profile = &ispeaker_rx_profile,
  .channel_mode = 2,
  .pmctl_id = NULL,
  .pmctl_id_sz = 0,
  .default_sample_rate = 48000,
  .pamp_on = &msm_snddev_poweramp_on,
  .pamp_off = &msm_snddev_poweramp_off,
  .max_voice_rx_vol[VOC_NB_INDEX] = -500,
  .min_voice_rx_vol[VOC_NB_INDEX] = -1000,
  .max_voice_rx_vol[VOC_WB_INDEX] = -500,
  .min_voice_rx_vol[VOC_WB_INDEX] = -1000,
};

static struct platform_device msm_fluid_iearpeice_rx_device = {
  .name = "snddev_icodec",
  .id = 23,
  .dev = { .platform_data = &snddev_fluid_iearpiece_rx_data },
};




static struct adie_codec_action_unit fluid_idual_mic_ef_8KHz_osr256_actions[] =

    MIC1_LEFT_AUX_IN_RIGHT_8000_OSR_256_VE329;













static struct adie_codec_hwsetting_entry fluid_idual_mic_endfire_settings[] = {
  {
    .freq_plan = 8000,
    .osr = 256,
    .actions = fluid_idual_mic_ef_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(fluid_idual_mic_ef_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 16000,
    .osr = 256,
    .actions = fluid_idual_mic_ef_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(fluid_idual_mic_ef_8KHz_osr256_actions),
  }, 
  {
    .freq_plan = 48000,
    .osr = 256,
    .actions = fluid_idual_mic_ef_8KHz_osr256_actions,
    .action_sz = ARRAY_SIZE(fluid_idual_mic_ef_8KHz_osr256_actions),
  }
};

static struct adie_codec_dev_profile fluid_idual_mic_endfire_profile = {
  .path_type = ADIE_CODEC_TX,
  .settings = fluid_idual_mic_endfire_settings,
  .setting_sz = ARRAY_SIZE(fluid_idual_mic_endfire_settings),
};

static enum hsed_controller fluid_idual_mic_endfire_pmctl_id[] = {
  PM_HSED_CONTROLLER_0, PM_HSED_CONTROLLER_2
};

static struct snddev_icodec_data snddev_fluid_idual_mic_endfire_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "handset_dual_mic_endfire_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_SPKR_PHONE_MIC_ENDFIRE,
  .profile = &fluid_idual_mic_endfire_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,
  .pmctl_id = fluid_idual_mic_endfire_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(fluid_idual_mic_endfire_pmctl_id),
  .pamp_on = msm_snddev_tx_route_config,
  .pamp_off = msm_snddev_tx_route_deconfig,
};

static struct platform_device msm_fluid_idual_mic_endfire_device = {
  .name = "snddev_icodec",
  .id = 24,
  .dev = { .platform_data = &snddev_fluid_idual_mic_endfire_data },
};

static struct snddev_icodec_data snddev_fluid_spk_idual_mic_endfire_data = {
  .capability = (SNDDEV_CAP_TX | SNDDEV_CAP_VOICE),
  .name = "speaker_dual_mic_endfire_tx",
  .copp_id = 0,
  .acdb_id = ACDB_ID_SPKR_PHONE_MIC_ENDFIRE,
  .profile = &fluid_idual_mic_endfire_profile,
  .channel_mode = 2,
  .default_sample_rate = 48000,
  .pmctl_id = fluid_idual_mic_endfire_pmctl_id,
  .pmctl_id_sz = ARRAY_SIZE(fluid_idual_mic_endfire_pmctl_id),
  .pamp_on = msm_snddev_tx_route_config,
  .pamp_off = msm_snddev_tx_route_deconfig,
};

static struct platform_device msm_fluid_spk_idual_mic_endfire_device = {
  .name = "snddev_icodec",
  .id = 25,
  .dev = { .platform_data = &snddev_fluid_spk_idual_mic_endfire_data },
};

static struct snddev_virtual_data snddev_a2dp_tx_data = {
  .capability = SNDDEV_CAP_TX,
  .name = "a2dp_tx",
  .copp_id = 5,
  .acdb_id = PSEUDO_ACDB_ID,
};

static struct snddev_virtual_data snddev_a2dp_rx_data = {
  .capability = SNDDEV_CAP_RX,
  .name = "a2dp_rx",
  .copp_id = 2,
  .acdb_id = PSEUDO_ACDB_ID,
};

static struct platform_device msm_a2dp_rx_device = {
  .name = "snddev_virtual",
  .id = 0,
  .dev = { .platform_data = &snddev_a2dp_rx_data },
};

static struct platform_device msm_a2dp_tx_device = {
  .name = "snddev_virtual",
  .id = 1,
  .dev = { .platform_data = &snddev_a2dp_tx_data },
};

static struct snddev_virtual_data snddev_uplink_rx_data = {
  .capability = SNDDEV_CAP_RX,
  .name = "uplink_rx",
  .copp_id = 5,
  .acdb_id = PSEUDO_ACDB_ID,
};

static struct platform_device msm_uplink_rx_device = {
  .name = "snddev_virtual",
  .id = 2,
  .dev = { .platform_data = &snddev_uplink_rx_data },
};




static struct snddev_ecodec_data snddev_bt_a2dp_rx_data = {
	.capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
	.name = "bt_a2dp_rx",
	.copp_id = 1,
	.acdb_id = ACDB_ID_BT_A2DP_SPKR,
	.channel_mode = 2,
	.conf_pcm_ctl_val               = BT_A2DP_PCM_CTL_VAL,
	.conf_aux_codec_intf            = BT_A2DP_AUX_CODEC_INTF,
	.conf_data_format_padding_val   = BT_A2DP_DATA_FORMAT_PADDING,
	.max_voice_rx_vol[VOC_NB_INDEX] = 0,
	.min_voice_rx_vol[VOC_NB_INDEX] = -2100,
	.max_voice_rx_vol[VOC_WB_INDEX] = 0,
	.min_voice_rx_vol[VOC_WB_INDEX] = -2100
};

static struct platform_device msm_bt_a2dp_rx_device = {
	.name = "msm_snddev_ecodec",
	.id   = 2,
	.dev  =  { .platform_data = &snddev_bt_a2dp_rx_data }
};



static struct adie_codec_action_unit ispeaker_mono_rx_48KHz_osr256_actions[] =
	SPEAKER_PHONE_MONO_RX_48000_OSR_256;

static struct adie_codec_hwsetting_entry ispeaker_mono_rx_settings[] = {
	{
		.freq_plan  = 48000,
		.osr        = 256,
		.actions    = ispeaker_mono_rx_48KHz_osr256_actions,
		.action_sz  = ARRAY_SIZE(ispeaker_mono_rx_48KHz_osr256_actions),
	}
};

static struct adie_codec_dev_profile ispeaker_mono_rx_profile = {
	.path_type  = ADIE_CODEC_RX,
	.settings   = ispeaker_mono_rx_settings,
	.setting_sz = ARRAY_SIZE(ispeaker_mono_rx_settings)
};

static struct snddev_icodec_data snddev_ispaker_mono_rx_data = {
	.capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
	.name = "speaker_mono_rx",
	.copp_id = 0,
	.acdb_id = ACDB_ID_SPKR_PHONE_MONO,
	.profile = &ispeaker_mono_rx_profile,
	.channel_mode = 1,
	.pmctl_id     = NULL,
	.pmctl_id_sz  = 0,
	.default_sample_rate = 48000,

	.pamp_on      = &ak7837a_power_on_speaker_stereo,
	.pamp_off     = &ak7837a_power_off,









	.max_voice_rx_vol[VOC_NB_INDEX] = 0,
	.min_voice_rx_vol[VOC_NB_INDEX] = -2100,
	.max_voice_rx_vol[VOC_WB_INDEX] = 0,
	.min_voice_rx_vol[VOC_WB_INDEX] = -2100
};

static struct platform_device msm_ispeaker_mono_rx_device = {
	.name = "snddev_icodec",
	.id   = 34,
	.dev  =  { .platform_data = &snddev_ispaker_mono_rx_data }
};



static struct adie_codec_action_unit ihs_mono_speaker_mono_rx_48KHz_osr256_actions[] =

	HEADSET_MONO_SPEAKER_MONO_RX_CAPLESS_48000_OSR_256_HPH;




static struct adie_codec_hwsetting_entry ihs_mono_speaker_mono_rx_settings[] = {
	{
		.freq_plan = 48000,
		.osr       = 256,
		.actions   = ihs_mono_speaker_mono_rx_48KHz_osr256_actions,
		.action_sz = ARRAY_SIZE(ihs_mono_speaker_mono_rx_48KHz_osr256_actions),
	}
};

static struct adie_codec_dev_profile ihs_mono_speaker_mono_rx_profile = {
	.path_type  = ADIE_CODEC_RX,
	.settings   = ihs_mono_speaker_mono_rx_settings,
	.setting_sz = ARRAY_SIZE(ihs_mono_speaker_mono_rx_settings)
};
 
static struct snddev_icodec_data snddev_ihs_mono_speaker_mono_rx_data = {
	.capability = (SNDDEV_CAP_RX | SNDDEV_CAP_VOICE),
	.name    = "headset_mono_speaker_mono_rx",
	.copp_id = 0,
	.acdb_id = ACDB_ID_HEADSET_MONO_PLUS_SPKR_MONO_RX,
	.profile = &ihs_mono_speaker_mono_rx_profile,
	.channel_mode = 1,
	.default_sample_rate = 48000,


	.pamp_on  = &ak7837a_power_on_headset_stereo_speaker_stereo,
	.pamp_off = &ak7837a_power_off,









	.max_voice_rx_vol[VOC_NB_INDEX] = 0,      
	.min_voice_rx_vol[VOC_NB_INDEX] = -2100,  
	.max_voice_rx_vol[VOC_WB_INDEX] = 0,      
	.min_voice_rx_vol[VOC_WB_INDEX] = -2100   
};


static struct platform_device msm_ihs_mono_speaker_mono_rx_device = {
	.name = "snddev_icodec",
	.id   = 35,
	.dev  =  { .platform_data = &snddev_ihs_mono_speaker_mono_rx_data }
};




















































































































































































































































static struct platform_device *snd_devices_ffa[] __initdata = {
  &msm_iearpiece_ffa_device,
  &msm_imic_ffa_device,
  &msm_ifmradio_handset_device,
  &msm_ihs_ffa_stereo_rx_device,
  &msm_ihs_ffa_mono_rx_device,
  &msm_ihs_mono_tx_device,
  &msm_bt_sco_earpiece_device,
  &msm_bt_sco_mic_device,
  &msm_ispeaker_rx_device,
  &msm_ifmradio_speaker_device,
  &msm_ifmradio_ffa_headset_device,
  &msm_idual_mic_endfire_device,
  &msm_idual_mic_broadside_device,
  &msm_spk_idual_mic_endfire_device,
  &msm_spk_idual_mic_broadside_device,
  &msm_itty_hs_mono_tx_device,
  &msm_itty_hs_mono_rx_device,
  &msm_ispeaker_tx_device,
  &msm_ihs_stereo_speaker_stereo_rx_device,
  &msm_a2dp_rx_device,
  &msm_a2dp_tx_device,
  &msm_snddev_mi2s_stereo_rx_device,
  &msm_snddev_mi2s_fm_tx_device,
  &msm_uplink_rx_device,
  &msm_real_stereo_tx_device,
};

static struct platform_device *snd_devices_surf[] __initdata = {
  &msm_iearpiece_device,
  &msm_imic_device,
  &msm_ihs_stereo_rx_device,
  &msm_ihs_mono_rx_device,
  &msm_ihs_mono_tx_device,
  &msm_bt_sco_earpiece_device,
  &msm_bt_sco_mic_device,
  &msm_ifmradio_handset_device,
  &msm_ispeaker_rx_device,
  &msm_ifmradio_speaker_device,
  &msm_ifmradio_headset_device,
  &msm_itty_hs_mono_tx_device,
  &msm_itty_hs_mono_rx_device,
  &msm_ispeaker_tx_device,
  &msm_ihs_stereo_speaker_stereo_rx_device,
  &msm_a2dp_rx_device,
  &msm_a2dp_tx_device,
  &msm_snddev_mi2s_stereo_rx_device,
  &msm_snddev_mi2s_fm_tx_device,
  &msm_uplink_rx_device,

  
  &msm_isubmic_tx_device,
  &msm_iusb_stereo_rx_device,
  &msm_iptt_speaker_tx_device,
  &msm_iptt_speaker_rx_device,
  











	&msm_ispeaker_mono_rx_device,



	&msm_bt_a2dp_rx_device,



    &msm_ihs_mono_speaker_mono_rx_device,




};

static struct platform_device *snd_devices_fluid[] __initdata = {
  &msm_ihs_stereo_rx_device,
  &msm_ihs_mono_rx_device,
  &msm_ihs_mono_tx_device,
  &msm_ispeaker_rx_device,
  &msm_ispeaker_tx_device,
  &msm_fluid_imic_tx_device,
  &msm_fluid_iearpeice_rx_device,
  &msm_fluid_idual_mic_endfire_device,
  &msm_fluid_spk_idual_mic_endfire_device,
  &msm_a2dp_rx_device,
  &msm_a2dp_tx_device,
  &msm_snddev_mi2s_stereo_rx_device,
  &msm_uplink_rx_device,
  &msm_ifmradio_speaker_device,
  &msm_ifmradio_headset_device,
};


#define ACT_TAB(ACT_NAME) { .actions = ACT_NAME, .action_sz = ARRAY_SIZE(ACT_NAME) }
static struct adie_codec_hwsetting_entry diag_snddev_calibration[] = {
  ACT_TAB(iearpiece_48KHz_osr256_actions),          
  ACT_TAB(imic_8KHz_osr256_actions),              
  ACT_TAB(imic_16KHz_osr256_actions),             
  ACT_TAB(imic_48KHz_osr256_actions),             
  ACT_TAB(ihs_stereo_rx_48KHz_osr256_actions),        
  ACT_TAB(ihs_mono_rx_48KHz_osr256_actions),          
  ACT_TAB(ihs_mono_tx_8KHz_osr256_actions),         
  ACT_TAB(ihs_mono_tx_16KHz_osr256_actions),          
  ACT_TAB(ihs_mono_tx_48KHz_osr256_actions),          
  ACT_TAB(ifmradio_handset_VE313_actions),          
  ACT_TAB(ispeaker_rx_48KHz_osr256_actions),          
  ACT_TAB(ifmradio_speaker_VE313_actions),          
  ACT_TAB(ifmradio_headset_VE313_actions),          
  ACT_TAB(idual_mic_endfire_8KHz_osr256_actions),       
  ACT_TAB(idual_mic_bs_8KHz_osr256_actions),          
  ACT_TAB(ispk_dual_mic_ef_8KHz_osr256_actions),        
  ACT_TAB(ispk_dual_mic_bs_8KHz_osr256_actions),        
  ACT_TAB(itty_hs_mono_tx_8KHz_osr256_actions),       
  ACT_TAB(itty_hs_mono_rx_8KHz_osr256_actions),       
  ACT_TAB(itty_hs_mono_rx_16KHz_osr256_actions),        
  ACT_TAB(itty_hs_mono_rx_48KHz_osr256_actions),        
  ACT_TAB(ispeaker_tx_8KHz_osr256_actions),         
  ACT_TAB(ispeaker_tx_48KHz_osr256_actions),          
  ACT_TAB(ihs_stereo_speaker_stereo_rx_48KHz_osr256_actions), 
  ACT_TAB(isubmic_8KHz_osr256_actions),           
  ACT_TAB(isubmic_48KHz_osr256_actions),            
  ACT_TAB(iusb_stereo_rx_48KHz_osr256_actions),       
  ACT_TAB(iptt_speaker_tx_8KHz_osr256_actions),       
  ACT_TAB(iptt_speaker_tx_48KHz_osr256_actions),        
  ACT_TAB(iptt_speaker_rx_48KHz_osr256_actions),        
  ACT_TAB(ihs_ffa_stereo_rx_48KHz_osr256_actions),      













  ACT_TAB(ispeaker_mono_rx_48KHz_osr256_actions),        
  ACT_TAB(ihs_mono_speaker_mono_rx_48KHz_osr256_actions),



};

u8 Diag_Audio_qtr_cal(Diag_Audio_qtr_cal_type *cal_info )
{ 
  u8  modeRW;
  u8  act_idx;
  u8  in_act_idx;
  struct adie_codec_action_unit *cur_act;

  act_idx = cal_info->act_idx;
  if( ARRAY_SIZE(diag_snddev_calibration) <= act_idx ){
    printk(KERN_INFO "[diag] Diag_Audio_qtr_cal: act_idx overflow\n");
    return 1;
  }

  in_act_idx = cal_info->in_act_idx;
  if( diag_snddev_calibration[act_idx].action_sz <= in_act_idx ){
    printk(KERN_INFO "[diag] Diag_Audio_qtr_cal: in_act_idx overflow\n");
    return 1;
  }

  cur_act = &diag_snddev_calibration[act_idx].actions[in_act_idx];

  modeRW = cal_info->modeRW;
  printk(KERN_INFO "[diag] Diag_Audio_qtr_cal rw=%02d act_idx=%02x in_act=%02x type=%08x data=%08x\n",
    modeRW, act_idx, in_act_idx,cal_info->act_type,cal_info->data);
  switch( modeRW ){
  case 0x00:  
    cur_act->type   = cal_info->act_type;
    cur_act->action = cal_info->data;
    break;
  case 0x01:  
    cal_info->act_type = cur_act->type;
    cal_info->data     = cur_act->action;
    break;
  default:
    break;
  }

  printk(KERN_INFO "[diag] Diag_Audio_qtr_cal cur_act_type=%08x cur_act_data=%08x\n",
    cur_act->type, cur_act->action);

  return 0;
}

static struct snddev_icodec_data * diag_snddev_vol_limit_dev[] = {
  &snddev_iearpiece_data,           
  &snddev_imic_data,              
  &snddev_ihs_stereo_rx_data,         
  &snddev_ihs_mono_rx_data,         
  &snddev_ihs_mono_tx_data,         
  &snddev_ifmradio_handset_data,        
  &snddev_ispeaker_rx_data,         
  &snddev_ifmradio_speaker_data,        
  &snddev_ifmradio_headset_data,        
  &snddev_itty_hs_mono_tx_data,       
  &snddev_itty_hs_mono_rx_data,       
  &snddev_ispeaker_tx_data,         
  &snddev_ihs_stereo_speaker_stereo_rx_data,  
  &snddev_isubmic_tx_data,          
  &snddev_iusb_stereo_rx_data,        
  &snddev_iptt_speaker_tx_data,       
  &snddev_iptt_speaker_rx_data,       











  &snddev_ispaker_mono_rx_data,         
  &snddev_ihs_mono_speaker_mono_rx_data,



};

u8 Diag_Audio_vol_limit( Diag_Audio_vol_limit_type *vol_info )
{
  u8  modeRW;
  u8  dev_idx;
  struct snddev_icodec_data * cur_dev;
  struct msm_snddev_info * dev_info;
  int i;

  dev_idx = vol_info->dev_idx;
  if( ARRAY_SIZE(diag_snddev_vol_limit_dev) <= dev_idx ){
    printk(KERN_INFO "[diag] Diag_Audio_vol_limit: dev_idx overflow\n");
    return 1;
  }

  cur_dev = diag_snddev_vol_limit_dev[dev_idx];

  modeRW = vol_info->modeRW;
  printk(KERN_INFO "[diag] Diag_Audio_vol_limit rw=%02d dev_idx=%02x max_nb=%d min_nb=%d max_wb=%d min_wb=%d\n",
    modeRW,dev_idx, vol_info->max_nb, vol_info->min_nb, vol_info->max_wb, vol_info->min_wb);
  
  switch( modeRW ) {
  case 0x00:  
    cur_dev->max_voice_rx_vol[VOC_NB_INDEX] = vol_info->max_nb;
    cur_dev->min_voice_rx_vol[VOC_NB_INDEX] = vol_info->min_nb;
    cur_dev->max_voice_rx_vol[VOC_WB_INDEX] = vol_info->max_wb;
    cur_dev->min_voice_rx_vol[VOC_WB_INDEX] = vol_info->min_wb;

    
    dev_info = msm_snddev_get_dev_info(cur_dev->name);
    if ( dev_info ) { 
      
      for (i = 0; i < VOC_RX_VOL_ARRAY_NUM; i++) {
        printk(KERN_INFO "[diag] Diag_Audio_vol_limit update(before):%s idx=%d, max=%d, min=%d\n",
          cur_dev->name, i, dev_info->max_voc_rx_vol[i], dev_info->min_voc_rx_vol[i]);
        dev_info->max_voc_rx_vol[i] =
          cur_dev->max_voice_rx_vol[i];
        dev_info->min_voc_rx_vol[i] =
          cur_dev->min_voice_rx_vol[i];
      }
    } else {
      printk(KERN_ERR "[diag] Diag_Audio_vol_limit dev_info:%s not found\n", cur_dev->name);
    }
    break;
  case 0x01:  
    vol_info->max_nb = cur_dev->max_voice_rx_vol[VOC_NB_INDEX];
    vol_info->min_nb = cur_dev->min_voice_rx_vol[VOC_NB_INDEX];
    vol_info->max_wb = cur_dev->max_voice_rx_vol[VOC_WB_INDEX];
    vol_info->min_wb = cur_dev->min_voice_rx_vol[VOC_WB_INDEX];
    break;
  default:
    break;
  }

  printk(KERN_INFO "[diag] Diag_Audio_vol_limit  cur_max_nb=%d  cur_min_nb=%d cur_max_wb=%d cur_min_wb=%d\n\n",
    cur_dev->max_voice_rx_vol[VOC_NB_INDEX], cur_dev->min_voice_rx_vol[VOC_NB_INDEX],
    cur_dev->max_voice_rx_vol[VOC_WB_INDEX], cur_dev->min_voice_rx_vol[VOC_WB_INDEX]);

  return 0;
}



#ifdef CONFIG_DEBUG_FS
static void snddev_hsed_config_modify_setting(int type)
{
  struct platform_device *device;
  struct snddev_icodec_data *icodec_data;

  device = &msm_ihs_ffa_stereo_rx_device;
  icodec_data = (struct snddev_icodec_data *)device->dev.platform_data;

  if (icodec_data) {
    if (type == 1) {
      icodec_data->voltage_on = NULL;
      icodec_data->voltage_off = NULL;
      icodec_data->profile->settings =
        ihs_ffa_stereo_rx_class_d_legacy_settings;
      icodec_data->profile->setting_sz =
      ARRAY_SIZE(ihs_ffa_stereo_rx_class_d_legacy_settings);
    } else if (type == 2) {
      icodec_data->voltage_on = NULL;
      icodec_data->voltage_off = NULL;
      icodec_data->profile->settings =
        ihs_ffa_stereo_rx_class_ab_legacy_settings;
      icodec_data->profile->setting_sz =
      ARRAY_SIZE(ihs_ffa_stereo_rx_class_ab_legacy_settings);
    }
  }
}

static void snddev_hsed_config_restore_setting(void)
{
  struct platform_device *device;
  struct snddev_icodec_data *icodec_data;

  device = &msm_ihs_ffa_stereo_rx_device;
  icodec_data = (struct snddev_icodec_data *)device->dev.platform_data;

  if (icodec_data) {
    icodec_data->voltage_on = msm_snddev_hsed_voltage_on;
    icodec_data->voltage_off = msm_snddev_hsed_voltage_off;
    icodec_data->profile->settings = ihs_ffa_stereo_rx_settings;
    icodec_data->profile->setting_sz =
      ARRAY_SIZE(ihs_ffa_stereo_rx_settings);
  }
}

static ssize_t snddev_hsed_config_debug_write(struct file *filp,
  const char __user *ubuf, size_t cnt, loff_t *ppos)
{
  char *lb_str = filp->private_data;
  char cmd;

  if (get_user(cmd, ubuf))
    return -EFAULT;

  if (!strcmp(lb_str, "msm_hsed_config")) {
    switch (cmd) {
    case '0':
      snddev_hsed_config_restore_setting();
      break;

    case '1':
      snddev_hsed_config_modify_setting(1);
      break;

    case '2':
      snddev_hsed_config_modify_setting(2);
      break;

    default:
      break;
    }
  }
  return cnt;
}

static int snddev_hsed_config_debug_open(struct inode *inode, struct file *file)
{
  file->private_data = inode->i_private;
  return 0;
}

static const struct file_operations snddev_hsed_config_debug_fops = {
  .open = snddev_hsed_config_debug_open,
  .write = snddev_hsed_config_debug_write
};
#endif

void __ref msm_snddev_init(void)
{
  if (machine_is_msm7x30_ffa() || machine_is_msm8x55_ffa() ||
    machine_is_msm8x55_svlte_ffa()) {
    platform_add_devices(snd_devices_ffa,
    ARRAY_SIZE(snd_devices_ffa));

#ifdef CONFIG_DEBUG_FS
    debugfs_hsed_config = debugfs_create_file("msm_hsed_config",
          S_IFREG | S_IRUGO, NULL,
    (void *) "msm_hsed_config", &snddev_hsed_config_debug_fops);
#endif
  } else if (machine_is_msm7x30_surf() || machine_is_msm8x55_surf() ||
    machine_is_msm8x55_svlte_surf())
    platform_add_devices(snd_devices_surf,
    ARRAY_SIZE(snd_devices_surf));
  else if (machine_is_msm7x30_fluid())
    platform_add_devices(snd_devices_fluid,
    ARRAY_SIZE(snd_devices_fluid));
  else
    pr_err("%s: Unknown machine type\n", __func__);
}
