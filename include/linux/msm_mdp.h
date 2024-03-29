/* include/linux/msm_mdp.h
 *
 * Copyright (C) 2007 Google Incorporated
 * Copyright (c) 2009-2011, Code Aurora Forum. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/
#ifndef _MSM_MDP_H_
#define _MSM_MDP_H_

#include <linux/types.h>
#include <linux/fb.h>


































#define MSMFB_IOCTL_MAGIC 'm'
#define MSMFB_GRP_DISP          _IOW(MSMFB_IOCTL_MAGIC, 1, unsigned int)
#define MSMFB_BLIT              _IOW(MSMFB_IOCTL_MAGIC, 2, unsigned int)
#define MSMFB_SUSPEND_SW_REFRESHER _IOW(MSMFB_IOCTL_MAGIC, 128, unsigned int)
#define MSMFB_RESUME_SW_REFRESHER _IOW(MSMFB_IOCTL_MAGIC, 129, unsigned int)
#define MSMFB_CURSOR _IOW(MSMFB_IOCTL_MAGIC, 130, struct fb_cursor)
#define MSMFB_SET_LUT _IOW(MSMFB_IOCTL_MAGIC, 131, struct fb_cmap)
#define MSMFB_HISTOGRAM _IOWR(MSMFB_IOCTL_MAGIC, 132, struct mdp_histogram)
/* new ioctls's for set/get ccs matrix */
#define MSMFB_GET_CCS_MATRIX  _IOWR(MSMFB_IOCTL_MAGIC, 133, struct mdp_ccs)
#define MSMFB_SET_CCS_MATRIX  _IOW(MSMFB_IOCTL_MAGIC, 134, struct mdp_ccs)
#define MSMFB_OVERLAY_SET       _IOWR(MSMFB_IOCTL_MAGIC, 135, \
						struct mdp_overlay)
#define MSMFB_OVERLAY_UNSET     _IOW(MSMFB_IOCTL_MAGIC, 136, unsigned int)
#define MSMFB_OVERLAY_PLAY      _IOW(MSMFB_IOCTL_MAGIC, 137, \
						struct msmfb_overlay_data)
#define MSMFB_GET_PAGE_PROTECTION _IOR(MSMFB_IOCTL_MAGIC, 138, \
					struct mdp_page_protection)
#define MSMFB_SET_PAGE_PROTECTION _IOW(MSMFB_IOCTL_MAGIC, 139, \
					struct mdp_page_protection)
#define MSMFB_OVERLAY_GET      _IOR(MSMFB_IOCTL_MAGIC, 140, \
						struct mdp_overlay)
#define MSMFB_OVERLAY_PLAY_ENABLE     _IOW(MSMFB_IOCTL_MAGIC, 141, unsigned int)
#define MSMFB_OVERLAY_BLT       _IOWR(MSMFB_IOCTL_MAGIC, 142, \
						struct msmfb_overlay_blt)
#define MSMFB_OVERLAY_BLT_OFFSET     _IOW(MSMFB_IOCTL_MAGIC, 143, unsigned int)
#define MSMFB_HISTOGRAM_START	_IO(MSMFB_IOCTL_MAGIC, 144)
#define MSMFB_HISTOGRAM_STOP	_IO(MSMFB_IOCTL_MAGIC, 145)

#define MSMFB_OVERLAY_3D       _IOWR(MSMFB_IOCTL_MAGIC, 146, \
						struct msmfb_overlay_3d)

#define MSMFB_SET_VG_CCS_MATRIX  _IOW(MSMFB_IOCTL_MAGIC, 147, struct mdp4_vg_csc_matrix) 


#define MDP_IMGTYPE2_START 0x10000


#define MSMFB_CUSTOM_1    _IO(MSMFB_IOCTL_MAGIC, 150)
#define MSMFB_CUSTOM_2    _IO(MSMFB_IOCTL_MAGIC, 151)
#define MSMFB_CUSTOM_3    _IO(MSMFB_IOCTL_MAGIC, 152)
#define MSMFB_CUSTOM_4    _IO(MSMFB_IOCTL_MAGIC, 153)
#define MSMFB_CUSTOM_5    _IO(MSMFB_IOCTL_MAGIC, 154)


#define MSMFB_CUSTOM_6    _IOW(MSMFB_IOCTL_MAGIC, 155, struct msmfb_regset *)


#define MSMFB_CUSTOM_7    _IOR(MSMFB_IOCTL_MAGIC, 156, struct msmfb_vsync_ave *)


#define MSMFB_CUSTOM_8    _IOW(MSMFB_IOCTL_MAGIC, 157, struct msmfb_vsync_parame *)


#define MSMFB_CUSTOM_9    _IOW(MSMFB_IOCTL_MAGIC, 158, struct msmfb_request_parame *)



#define MSMFB_CUSTOM_10   _IO(MSMFB_IOCTL_MAGIC, 159)
#define MSMFB_CUSTOM_11   _IO(MSMFB_IOCTL_MAGIC, 160)


#define MSMFB_CUSTOM_100  _IO(MSMFB_IOCTL_MAGIC, 180)
#define MSMFB_CUSTOM_101  _IO(MSMFB_IOCTL_MAGIC, 181)


#define MSMFB_CUSTOM_102  _IOW(MSMFB_IOCTL_MAGIC, 182, struct msmfb_request_regset *)



#define MSMFB_CUSTOM_103  _IO(MSMFB_IOCTL_MAGIC, 183)
#define MSMFB_CUSTOM_104  _IO(MSMFB_IOCTL_MAGIC, 184)



#define MSMFB_CUSTOM_150  _IO(MSMFB_IOCTL_MAGIC, 185)
#define MSMFB_CUSTOM_151  _IO(MSMFB_IOCTL_MAGIC, 186)
#define MSMFB_CUSTOM_152  _IO(MSMFB_IOCTL_MAGIC, 187)
#define MSMFB_CUSTOM_153  _IO(MSMFB_IOCTL_MAGIC, 188)
#define MSMFB_CUSTOM_154  _IO(MSMFB_IOCTL_MAGIC, 189)
#define MSMFB_CUSTOM_155  _IO(MSMFB_IOCTL_MAGIC, 190)



#define MSMFB_CUSTOM_156  _IO(MSMFB_IOCTL_MAGIC, 191)
#define MSMFB_CUSTOM_157  _IO(MSMFB_IOCTL_MAGIC, 192)


enum {
	MDP_RGB_565,      /* RGB 565 planer */
	MDP_XRGB_8888,    /* RGB 888 padded */
	MDP_Y_CBCR_H2V2,  /* Y and CbCr, pseudo planer w/ Cb is in MSB */
	MDP_ARGB_8888,    /* ARGB 888 */
	MDP_RGB_888,      /* RGB 888 planer */
	MDP_Y_CRCB_H2V2,  /* Y and CrCb, pseudo planer w/ Cr is in MSB */
	MDP_YCRYCB_H2V1,  /* YCrYCb interleave */
	MDP_Y_CRCB_H2V1,  /* Y and CrCb, pseduo planer w/ Cr is in MSB */
	MDP_Y_CBCR_H2V1,   /* Y and CrCb, pseduo planer w/ Cr is in MSB */
	MDP_RGBA_8888,    /* ARGB 888 */
	MDP_BGRA_8888,	  /* ABGR 888 */
	MDP_RGBX_8888,	  /* RGBX 888 */
	MDP_Y_CRCB_H2V2_TILE,  /* Y and CrCb, pseudo planer tile */
	MDP_Y_CBCR_H2V2_TILE,  /* Y and CbCr, pseudo planer tile */
	MDP_Y_CR_CB_H2V2,  /* Y, Cr and Cb, planar */
	MDP_Y_CB_CR_H2V2,  /* Y, Cb and Cr, planar */
	MDP_IMGTYPE_LIMIT,
	MDP_BGR_565 = MDP_IMGTYPE2_START,      /* BGR 565 planer */
	MDP_FB_FORMAT,    /* framebuffer format */
	MDP_IMGTYPE_LIMIT2 /* Non valid image type after this enum */
};

enum {
	PMEM_IMG,
	FB_IMG,
};



enum {
	MSM_FB_REQUEST_OVERLAY_ALPHA,
	MSM_FB_REQUEST_MAX
};



typedef enum {
	MSM_FB_REQUEST_DISABLE,
	MSM_FB_REQUEST_ENABLE
} MSM_FB_REQUEST_FLAG;



/* mdp_blit_req flag values */
#define MDP_ROT_NOP 0
#define MDP_FLIP_LR 0x1
#define MDP_FLIP_UD 0x2
#define MDP_ROT_90 0x4
#define MDP_ROT_180 (MDP_FLIP_UD|MDP_FLIP_LR)
#define MDP_ROT_270 (MDP_ROT_90|MDP_FLIP_UD|MDP_FLIP_LR)
#define MDP_DITHER 0x8
#define MDP_BLUR 0x10
#define MDP_BLEND_FG_PREMULT 0x20000
#define MDP_DEINTERLACE 0x80000000
#define MDP_SHARPENING  0x40000000
#define MDP_NO_DMA_BARRIER_START	0x20000000
#define MDP_NO_DMA_BARRIER_END		0x10000000
#define MDP_NO_BLIT			0x08000000
#define MDP_BLIT_WITH_DMA_BARRIERS	0x000
#define MDP_BLIT_WITH_NO_DMA_BARRIERS    \
	(MDP_NO_DMA_BARRIER_START | MDP_NO_DMA_BARRIER_END)
#define MDP_BLIT_SRC_GEM                0x04000000
#define MDP_BLIT_DST_GEM                0x02000000
#define MDP_BLIT_NON_CACHED		0x01000000
#define MDP_OV_PIPE_SHARE		0x00800000
#define MDP_DEINTERLACE_ODD		0x00400000
#define MDP_OV_PLAY_NOWAIT		0x00200000

#define MDP_TRANSP_NOP 0xffffffff
#define MDP_ALPHA_NOP 0xff

#define MDP_FB_PAGE_PROTECTION_NONCACHED         (0)
#define MDP_FB_PAGE_PROTECTION_WRITECOMBINE      (1)
#define MDP_FB_PAGE_PROTECTION_WRITETHROUGHCACHE (2)
#define MDP_FB_PAGE_PROTECTION_WRITEBACKCACHE    (3)
#define MDP_FB_PAGE_PROTECTION_WRITEBACKWACACHE  (4)
/* Sentinel: Don't use! */
#define MDP_FB_PAGE_PROTECTION_INVALID           (5)
/* Count of the number of MDP_FB_PAGE_PROTECTION_... values. */
#define MDP_NUM_FB_PAGE_PROTECTION_VALUES        (5)

struct mdp_rect {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
};

struct mdp_img {
	uint32_t width;
	uint32_t height;
	uint32_t format;
	uint32_t offset;
	int memory_id;		/* the file descriptor */
	uint32_t priv;
};

/*
 * {3x3} + {3} ccs matrix
 */

#define MDP_CCS_RGB2YUV 	0
#define MDP_CCS_YUV2RGB 	1

#define MDP_CCS_SIZE	9
#define MDP_BV_SIZE	3

struct mdp_ccs {
	int direction;			/* MDP_CCS_RGB2YUV or YUV2RGB */
	uint16_t ccs[MDP_CCS_SIZE];	/* 3x3 color coefficients */
	uint16_t bv[MDP_BV_SIZE];	/* 1x3 bias vector */
};

/* The version of the mdp_blit_req structure so that
 * user applications can selectively decide which functionality
 * to include
 */

#define MDP_BLIT_REQ_VERSION 2

struct mdp_blit_req {
	struct mdp_img src;
	struct mdp_img dst;
	struct mdp_rect src_rect;
	struct mdp_rect dst_rect;
	uint32_t alpha;
	uint32_t transp_mask;
	uint32_t flags;
	int sharpening_strength;  /* -127 <--> 127, default 64 */
};

struct mdp_blit_req_list {
	uint32_t count;
	struct mdp_blit_req req[];
};

#define MSMFB_DATA_VERSION 2

struct msmfb_data {
	uint32_t offset;
	int memory_id;
	int id;
	uint32_t flags;
	uint32_t priv;
};

#define MSMFB_NEW_REQUEST -1

struct msmfb_overlay_data {
	uint32_t id;
	struct msmfb_data data;
};

struct msmfb_img {
	uint32_t width;
	uint32_t height;
	uint32_t format;
};

struct mdp_overlay {
	struct msmfb_img src;
	struct mdp_rect src_rect;
	struct mdp_rect dst_rect;
	uint32_t z_order;	/* stage number */
	uint32_t is_fg;		/* control alpha & transp */
	uint32_t alpha;
	uint32_t transp_mask;
	uint32_t flags;
	uint32_t id;
	uint32_t user_data[8];
};

struct msmfb_overlay_3d {
	uint32_t is_3d;
	uint32_t width;
	uint32_t height;
};


struct msmfb_overlay_blt {
	uint32_t enable;
	struct msmfb_data data;
};

struct mdp_histogram {
	uint32_t frame_cnt;
	uint32_t bin_cnt;
	uint32_t *r;
	uint32_t *g;
	uint32_t *b;
};

struct mdp_page_protection {
	uint32_t page_protection;
};

#ifdef __KERNEL__

/* get the framebuffer physical address information */
int get_fb_phys_info(unsigned long *start, unsigned long *len, int fb_num);

#endif



struct msmfb_regset {
	uint32_t  reg_addr;  
	uint32_t  set_data;  
};



struct msmfb_vsync_ave {
	uint32_t integer;    
	uint32_t decimal;    
};



struct msmfb_vsync_parame {
    uint32_t  set_data;  
};



struct msmfb_request_parame {
    uint32_t  request;    
    void*     data;   
};




struct mdp4_vg_csc_matrix {
  int VG_id;
  uint32_t csc_mv[9];
  uint32_t csc_pre_bv[3];
  uint32_t csc_post_bv[3];
  uint32_t csc_pre_lv[6];
  uint32_t csc_post_lv[6];
};


#endif /*_MSM_MDP_H_*/
