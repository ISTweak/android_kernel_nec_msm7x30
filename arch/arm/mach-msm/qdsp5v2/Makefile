#/**********************************************************************
#* File Name: arch/arm/mach-msm/qdsp5v2/Makefile
#* 
#* (C) NEC CASIO Mobile Communications, Ltd. 2011
#**********************************************************************/
obj-y += afe.o audio_interct.o mi2s.o audio_dev_ctl.o voice.o

ifeq ($(CONFIG_TIMPANI_CODEC), y)
obj-y += snddev_icodec.o
else ifeq ($(CONFIG_MARIMBA_CODEC), y)
obj-y += snddev_icodec.o
endif

obj-$(CONFIG_MARIMBA_CODEC) += snddev_data_marimba.o
obj-$(CONFIG_TIMPANI_CODEC) += snddev_data_timpani.o

obj-y += audio_pcm.o audpp.o audio_mp3.o audio_wma.o audio_aac.o audio_amrnb.o
obj-y += audio_amrwb.o audio_wmapro.o audio_adpcm.o audio_evrc.o audio_qcelp.o
obj-y += aux_pcm.o snddev_ecodec.o audio_out.o
obj-y += audio_lpa.o mp3_funcs.o pcm_funcs.o
obj-y += audpreproc.o audio_pcm_in.o audio_aac_in.o audio_amrnb_in.o audio_a2dp_in.o
obj-y += audio_evrc_in.o audio_qcelp_in.o
obj-y += adsp.o adsp_driver.o adsp_info.o
obj-y += audio_acdb.o snddev_virtual.o
obj-y += audio_fm.o
obj-y += lpa.o snddev_mi2s.o
obj-y += audio_mvs.o

obj-y += yda160_i2c_driver.o
obj-y += yda160_sndamp.o
obj-y += Diag_comd_appl.o
obj-y += Diag_acad.o


obj-y += NvRegister.o
obj-y += ak7837a_sndamp.o
obj-y += ak7837a_i2c_driver.o










