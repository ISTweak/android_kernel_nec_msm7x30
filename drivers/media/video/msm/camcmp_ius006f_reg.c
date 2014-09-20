/* Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
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

























































#include <linux/types.h>
#include "camcmp_cmdmaker_ius006f.h"





#define CAMCMP_REG(a)       CAMCOMBINE2(camcmp_reg_,a)
#define CAMCMP_CMD(a)       CAMCOMBINE2(camcmp_cmd_,a)
#define CAMCMP_BLK(a)       CAMCOMBINE2(camcmp_blk_,a)
#define CAMCMP_BTBL(a)      CAMCOMBINE2(camcmp_btbl_,a)
#define CAMCMP_POLL(a)      CAMCOMBINE2(camcmp_poll_,a)
#define CAMCMP_DAT(a)       CAMCOMBINE2(camcmp_dat_,a)


#define CAMCMP_SIZE_REG(a)  (sizeof(a)/sizeof(camcmp_ius006f_reg_val_type))
#define CAMCMP_SIZE_BLK(a)  (sizeof(a)/sizeof(camcmp_ius006f_blank_val_type))
#define CAMCMP_SIZE_DAT(a)  (sizeof(a)/sizeof(camcmp_data_type))


#define CAMCAMP_BLK_SIZE_DEF 1


















static camcmp_ius006f_reg_val_type CAMCMP_REG(chk_dev_sts)[] =
{
	{CAMCMP_REG_POLL1, 0x00F8, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE}       
};












static camcmp_ius006f_reg_val_type CAMCMP_REG(init_set_1)[] =
{
	



	{CAMCMP_REG_WRITE, 0x02FA, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FB, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FC, 0x0000002F, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FD, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FE, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0300, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0302, 0x00006400, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0304, 0x00092E00, NULL,                CAMCMP_D_LEN_LWORD},     
	{CAMCMP_REG_WRITE, 0x0009, 0x0000001F, NULL,                CAMCMP_D_LEN_BYTE},      















};




static camcmp_ius006f_reg_val_type CAMCMP_REG(init_set_2)[] =
{




	{CAMCMP_REG_WRITE, 0x000B, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x033E, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      

	{CAMCMP_REG_WRITE, 0x4044, 0x00001D60, NULL,                CAMCMP_D_LEN_WORD},      



	{CAMCMP_REG_WRITE, 0x4046, 0x00002A30, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4048, 0x000032A0, NULL,                CAMCMP_D_LEN_WORD},      

	{CAMCMP_REG_WRITE, 0x402B, 0x00000085, NULL,                CAMCMP_D_LEN_BYTE},      



	{CAMCMP_REG_WRITE, 0x402C, 0x0000012F, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4050, 0x0000025D, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x405C, 0x000009B8, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x405E, 0x000008C6, NULL,                CAMCMP_D_LEN_WORD},      

	{CAMCMP_REG_WRITE, 0x4060, 0x00001D60, NULL,                CAMCMP_D_LEN_WORD},      



	{CAMCMP_REG_WRITE, 0x4062, 0x00002A30, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4064, 0x000032A0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02A2, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02A4, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02A6, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02A8, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0364, 0x00000027, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0366, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C14, 0x000003C0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C16, 0x000003C0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C18, 0x000001E0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C1A, 0x000000E0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C1C, 0x00000420, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C1E, 0x000002C0, NULL,                CAMCMP_D_LEN_WORD},      

	{CAMCMP_REG_WRITE, 0x403E, 0x0000218C, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4040, 0x0000207F, NULL,                CAMCMP_D_LEN_WORD},      




	{CAMCMP_REG_WRITE, 0x4074, 0x0000242D, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4076, 0x00002320, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4078, 0x0000253A, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x407A, 0x0000242D, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02C7, 0x00000003, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02B8, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02B9, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02BA, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02BB, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02BC, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02BD, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02BE, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0348, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0349, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x034A, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x034B, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x034C, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x034D, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02C4, 0x0000010A, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C86, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x444A, 0x00007BFE, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x444C, 0x00007FE6, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4039, 0x00000022, NULL,                CAMCMP_D_LEN_BYTE},      

	{CAMCMP_REG_WRITE, 0x3E04, 0x00000005, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E05, 0x00000004, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E06, 0x00000013, NULL,                CAMCMP_D_LEN_BYTE},      





	{CAMCMP_REG_WRITE, 0x3E07, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E08, 0x0000000D, NULL,                CAMCMP_D_LEN_BYTE},      

	{CAMCMP_REG_WRITE, 0x3E09, 0x00000006, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E0A, 0x00000009, NULL,                CAMCMP_D_LEN_BYTE},      




	{CAMCMP_REG_WRITE, 0x3E0B, 0x00000005, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E0C, 0x00000008, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E0D, 0x00000007, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0014, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x001C, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      


	{CAMCMP_REG_WRITE, 0x001D, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      




	{CAMCMP_REG_WRITE, 0x001E, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x001F, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0020, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0021, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      


	{CAMCMP_REG_WRITE, 0x0022, 0x00000280, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0024, 0x00000A00, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0026, 0x00000280, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0028, 0x000001E0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x002A, 0x00000780, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x002C, 0x000001E0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x021A, 0x00000140, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x021C, 0x000000F0, NULL,                CAMCMP_D_LEN_WORD},      











	{CAMCMP_REG_WRITE, 0x0032, 0x00000100, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0039, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3201, 0x00000006, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0038, 0x0000000F, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x003A, 0x00000200, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x021E, 0x00001169, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0200, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      



























	{CAMCMP_REG_WRITE, 0x0011, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0380, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0381, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0382, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0383, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0384, 0x00000003, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0385, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      































































































































};




static camcmp_ius006f_reg_val_type CAMCMP_REG(init_set_3)[] =
{
	{CAMCMP_REG_WRITE, 0x4A04, 0x00000F61, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4A06, 0x0000121B, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4A08, 0x0000013F, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4A0A, 0x0000022E, NULL,                CAMCMP_D_LEN_WORD}       
};











static unsigned char CAMCMP_DAT(rom_cor)[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(rom_correct)[] =
{
	{CAMCMP_REG_WRITE, 0xB000, 0x00000000, CAMCMP_DAT(rom_cor), sizeof(CAMCMP_DAT(rom_cor))},  
};














static unsigned char CAMCMP_DAT(ae_frm_1)[] =
{
	0x05, 0x09, 0x0D, 0x11, 0x13, 0x11, 0x0D, 0x09, 0x05, 0x09, 0x0B, 0x17, 0x27, 0x32, 0x27, 0x17, 
	0x0B, 0x09, 0x0A, 0x0D, 0x23, 0x52, 0x64, 0x52, 0x23, 0x0D, 0x0A, 0x0A, 0x0D, 0x23, 0x52, 0x64, 
	0x52, 0x23, 0x0D, 0x0A, 0x09, 0x0B, 0x17, 0x27, 0x3F, 0x27, 0x17, 0x0B, 0x09, 0x08, 0x09, 0x0D, 
	0x0E, 0x10, 0x0E, 0x0D, 0x09, 0x08, 0x05, 0x08, 0x0A, 0x0B, 0x0D, 0x0B, 0x0A, 0x08, 0x05, 
};



static unsigned char CAMCMP_DAT(ae_frm_2)[] =
{
	0x07, 0x0D, 0x0E, 0x10, 0x0E, 0x0B, 0x07, 0x04, 0x03, 0x0D, 0x14, 0x1B, 0x21, 0x1B, 0x14, 0x09, 
	0x05, 0x05, 0x12, 0x26, 0x47, 0x4E, 0x47, 0x26, 0x0E, 0x08, 0x06, 0x14, 0x32, 0x58, 0x64, 0x58, 
	0x32, 0x13, 0x09, 0x07, 0x12, 0x26, 0x47, 0x4E, 0x47, 0x26, 0x0E, 0x08, 0x06, 0x0D, 0x14, 0x1B, 
	0x21, 0x1B, 0x14, 0x09, 0x05, 0x05, 0x07, 0x0D, 0x0E, 0x10, 0x0E, 0x0B, 0x07, 0x04, 0x03, 
};




























































static unsigned char CAMCMP_DAT(cxc_data)[] =
{
	0x01, 0x10, 0x04, 0x40, 0x10, 0x20, 0xc1, 0x80, 0x05, 0x03, 0x1a, 0x0c, 0x70, 0x20, 0xa0, 0x41, 
	0x00, 0x06, 0x01, 0x18, 0x04, 0x40, 0x10, 0x00, 0x41, 0x80, 0x04, 0x03, 0x16, 0x0c, 0x68, 0x30, 
	0xc0, 0x81, 0x80, 0x06, 0x01, 0x18, 0x04, 0x60, 0x00, 0x60, 0x01, 0x80, 0x05, 0x02, 0x10, 0x00, 
	0x40, 0x40, 0x20, 0x41, 0x00, 0x05, 0x01, 0x16, 0x08, 0x58, 0x20, 0x60, 0xc1, 0x00, 0x04, 0x03, 
	0x10, 0x08, 0x28, 0x20, 0xa0, 0x00, 0x80, 0x02, 0xff, 0x0f, 0x00, 0x40, 0x20, 0x40, 0x81, 0x00, 
	0x05, 0x02, 0x0a, 0x08, 0x28, 0x20, 0x80, 0xc0, 0x80, 0x01, 0x02, 0x08, 0x04, 0x20, 0x10, 0xc0, 
	0x80, 0x80, 0x04, 0x02, 0x12, 0x10, 0x20, 0x40, 0x80, 0xc0, 0x80, 0x01, 0x02, 0x00, 0x04, 0x00, 
	0x10, 0x00, 0x40, 0x80, 0x02, 0xff, 0x0d, 0xfc, 0x37, 0x10, 0x80, 0x40, 0x00, 0x02, 0x03, 0x04, 
	0x04, 0x08, 0x10, 0x20, 0x80, 0x80, 0x00, 0x01, 0x06, 0x00, 0x38, 0x00, 0xe0, 0x80, 0x00, 0x02, 
	0x02, 0x08, 0x0c, 0x08, 0x20, 0x20, 0x80, 0x80, 0x00, 0x02, 0x04, 0x08, 0x10, 0x30, 0xe0, 0xc0, 
	0x80, 0x03, 0xfe, 0x07, 0xf8, 0x1f, 0x40, 0x60, 0x00, 0x01, 0x01, 0x04, 0x06, 0x04, 0x10, 0x30, 
	0xa0, 0x00, 0x01, 0x03, 0x04, 0x0c, 0x0c, 0x18, 0x30, 0x60, 0x40, 0x80, 0x02, 0x02, 0x0a, 0x10, 
	0x18, 0x30, 0xa0, 0x00, 0x01, 0x02, 0x04, 0x10, 0x10, 0x40, 0x30, 0x80, 0xc0, 0x00, 0x02, 0x04, 
	0x0a, 0x10, 0x30, 0x40, 0xe0, 0x00, 0x01, 0x03, 0x03, 0x0c, 0x10, 0x38, 0x40, 0xe0, 0xc0, 0x00, 
	0x02, 0x03, 0x08, 0x10, 0x28, 0x40, 0xc0, 0x00, 0x81, 0x03, 0x04, 0x0c, 0x0c, 0x30, 0x40, 0xe0, 
	0x00, 0x81, 0x03, 0x05, 0xec, 0x17, 0xb0, 0x4f, 0x20, 0xbf, 0x80, 0xfc, 0x01, 0xf2, 0x0b, 0xd8, 
	0x1f, 0x40, 0x7f, 0x00, 0x00, 0x01, 0x00, 0x14, 0xb0, 0x5f, 0xc0, 0x3e, 0x81, 0xfc, 0x02, 0xf2, 
	0x07, 0xc8, 0x2f, 0x60, 0x7f, 0x00, 0xfd, 0x01, 0x00, 0x04, 0x00, 0x40, 0x60, 0x3e, 0x81, 0xf9, 
	0x02, 0xf2, 0x0b, 0xd8, 0x0f, 0x20, 0x3f, 0x00, 0xfb, 0x01, 0xf0, 0x07, 0xd0, 0x1f, 0x40, 0x3f, 
	0x81, 0xfa, 0x04, 0xea, 0x0b, 0xc0, 0x0f, 0x40, 0x3f, 0x00, 0xfd, 0xff, 0xf1, 0xfb, 0xc7, 0x0f, 
	0x80, 0x3f, 0x00, 0xfe, 0x05, 0xf0, 0x17, 0xc0, 0x2f, 0x00, 0x3f, 0x00, 0xfc, 0xff, 0xfb, 0xff, 
	0xdf, 0x0f, 0xa0, 0xff, 0xff, 0xfe, 0xff, 0xfb, 0x13, 0xd0, 0x4f, 0x40, 0x3f, 0x81, 0xfc, 0x01, 
	0xf6, 0x03, 0xe0, 0x0f, 0xe0, 0xff, 0x7f, 0xff, 0x00, 0xfa, 0x03, 0xe8, 0x5f, 0x80, 0x7f, 0x01, 
	0xfe, 0x04, 0xfa, 0x0b, 0xf8, 0x1f, 0x00, 0x40, 0x80, 0x00, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xdf, 
	0xbf, 0x81, 0xfe, 0x06, 0xfa, 0x1b, 0x10, 0x30, 0x60, 0x80, 0x80, 0x00, 0x00, 0x08, 0x0c, 0x18, 
	0x20, 0xc0, 0x80, 0x00, 0x03, 0x09, 0xfe, 0x27, 0xf8, 0x8f, 0x80, 0x00, 0x01, 0x01, 0x04, 0x1a, 
	0x08, 0x30, 0x40, 0xc0, 0x40, 0x81, 0x03, 0x05, 0x0e, 0x24, 0x28, 0x90, 0xa0, 0x40, 0x02, 0x02, 
	0x07, 0x0a, 0x20, 0x30, 0x50, 0x20, 0x81, 0x81, 0x04, 0x05, 0x12, 0x14, 0x48, 0x90, 0x00, 0x41, 
	0x02, 0x04, 0x07, 0x16, 0x1c, 0x40, 0x80, 0x00, 0x41, 0x01, 0x05, 0x06, 0x12, 0x18, 0x28, 0x60, 
	0xa0, 0x40, 0x02, 0x04, 0x09, 0x10, 0x1c, 0x58, 0x70, 0x00, 0x01, 0x02, 0x04, 0x05, 0x14, 0x18, 
	0x48, 0x60, 0xa0, 0x80, 0x81, 0x02, 
};




static unsigned char CAMCMP_DAT(shd_data)[] =
{
	0x24, 0x7a, 0x54, 0x7d, 0xa6, 0x84, 0x1c, 0x0e, 0xed, 0x26, 0x42, 0xb6, 0x79, 0x90, 0x6f, 0x3a, 
	0xa4, 0x1c, 0x16, 0x81, 0xa7, 0x48, 0xe9, 0x89, 0x12, 0x7f, 0xbc, 0xc4, 0x1d, 0x19, 0xf5, 0x46, 
	0x41, 0xaf, 0xe9, 0x4f, 0x6a, 0xf0, 0x33, 0x9b, 0x03, 0x09, 0x87, 0x43, 0xd9, 0xb9, 0x11, 0x78, 
	0x86, 0x44, 0x9c, 0x0e, 0xc5, 0xa6, 0x3f, 0x8c, 0x31, 0x4e, 0x5d, 0x50, 0xf3, 0x16, 0xd0, 0xd8, 
	0x85, 0x35, 0x90, 0x89, 0x0e, 0x6e, 0x0a, 0x44, 0x1c, 0x0c, 0x99, 0x26, 0x3d, 0x8b, 0x11, 0xce, 
	0x57, 0x04, 0xe3, 0x93, 0xab, 0xd0, 0x84, 0x29, 0x3d, 0xc9, 0x8a, 0x57, 0x0e, 0xe3, 0x18, 0xe4, 
	0xa0, 0xc6, 0x3d, 0x8c, 0xf9, 0xcd, 0x5a, 0x24, 0x93, 0x93, 0xa7, 0x68, 0xa4, 0x24, 0x0e, 0xb1, 
	0x48, 0x46, 0x4a, 0x82, 0x13, 0xa8, 0xac, 0xe5, 0x32, 0x8b, 0x21, 0xce, 0x5f, 0x58, 0xb3, 0x15, 
	0xbe, 0x9c, 0xc4, 0x26, 0x09, 0x61, 0x88, 0x3f, 0xfc, 0x91, 0x90, 0x85, 0x98, 0xc4, 0x26, 0x59, 
	0xe1, 0xcb, 0x5e, 0x58, 0xf3, 0x97, 0xd8, 0x70, 0xe5, 0x2f, 0x2a, 0xc9, 0xc9, 0x42, 0x20, 0x12, 
	0x90, 0x80, 0x34, 0xe4, 0x21, 0x2a, 0xc1, 0x49, 0x57, 0x02, 0xf3, 0x17, 0xd9, 0x40, 0x06, 0x39, 
	0x71, 0xd9, 0x8c, 0x50, 0xac, 0x32, 0x92, 0x96, 0x5c, 0xc4, 0x23, 0x23, 0x61, 0x89, 0x50, 0xac, 
	0x62, 0x17, 0xd0, 0x58, 0xa6, 0x39, 0xab, 0x59, 0xcf, 0x64, 0x94, 0xc3, 0x16, 0xc8, 0x30, 0xa5, 
	0x2c, 0x43, 0xc1, 0xca, 0x52, 0xc6, 0xe2, 0x16, 0xc9, 0x78, 0x86, 0x3a, 0xb6, 0xb9, 0x4f, 0x74, 
	0x34, 0xe4, 0x1b, 0x01, 0x6d, 0x06, 0x3b, 0x85, 0xc9, 0x0d, 0x60, 0x5c, 0x73, 0x98, 0xdc, 0x84, 
	0x66, 0x3b, 0xc8, 0x99, 0x50, 0x75, 0x4c, 0x44, 0xa0, 0x2f, 0xa1, 0x87, 0x47, 0xcc, 0xd1, 0x90, 
	0x6f, 0x18, 0x74, 0x1b, 0x02, 0x05, 0xc7, 0x41, 0xd2, 0x19, 0x91, 0x7a, 0x84, 0x04, 0x9f, 0x25, 
	0x99, 0x88, 0x50, 0xf8, 0x99, 0xd2, 0x74, 0x50, 0x64, 0x9c, 0x0d, 0x05, 0xa7, 0x42, 0xca, 0xf9, 
	0xd0, 0x75, 0x5a, 0xd4, 0x1e, 0x24, 0xb5, 0xe7, 0x48, 0xfb, 0x29, 0x51, 0x75, 0xec, 0xd3, 0x9a, 
	0xe6, 0x8c, 0x26, 0x38, 0x9f, 0xd9, 0xcd, 0x6a, 0x88, 0x73, 0x1b, 0xe9, 0x28, 0x87, 0x3d, 0xd2, 
	0xa9, 0x0f, 0x76, 0xf6, 0xc3, 0x1b, 0xee, 0x8c, 0x26, 0x38, 0x99, 0xa1, 0x0d, 0x65, 0x5a, 0x13, 
	0x9a, 0xdc, 0xbc, 0x46, 0x39, 0xc4, 0x19, 0x4f, 0x72, 0xd6, 0x33, 0x9a, 0xe0, 0x50, 0x06, 0x36, 
	0x76, 0x81, 0x8c, 0x59, 0xf6, 0x22, 0x96, 0xb9, 0xb0, 0x65, 0x2f, 0x82, 0xa9, 0xcc, 0x69, 0x7c, 
	0x03, 0x9b, 0xe4, 0x14, 0x06, 0x34, 0x71, 0x41, 0xcc, 0x53, 0xc0, 0x52, 0x93, 0xa0, 0xc4, 0x24, 
	0x27, 0x39, 0x09, 0x8a, 0x55, 0xc6, 0xe2, 0x97, 0xc8, 0x44, 0x26, 0x35, 0x6f, 0x41, 0x8c, 0x55, 
	0xd0, 0xf2, 0x92, 0x9c, 0x54, 0x64, 0x23, 0x0e, 0x89, 0x88, 0x46, 0x3a, 0x42, 0x93, 0x9d, 0x74, 
	0xa5, 0x2d, 0x74, 0x51, 0x4c, 0x58, 0xf2, 0x72, 0x94, 0xab, 0x80, 0xc4, 0x24, 0x07, 0x49, 0xc8, 
	0x3f, 0xfe, 0xb1, 0x10, 0x85, 0x90, 0xe4, 0x24, 0x4d, 0xc9, 0xca, 0x59, 0xf2, 0x42, 0x96, 0xbc, 
	0x24, 0x05, 0x2b, 0x21, 0x41, 0x09, 0x42, 0x16, 0x02, 0x10, 0x80, 0x2c, 0x64, 0x21, 0x24, 0x41, 
	0x09, 0x53, 0xb4, 0x52, 0x96, 0xbd, 0xd8, 0x25, 0x31, 0x5e, 0x59, 0x8b, 0x4d, 0x7c, 0xc2, 0x91, 
	0x90, 0x44, 0x84, 0x22, 0x1c, 0x01, 0xc9, 0x4d, 0x7e, 0xf2, 0x95, 0xb9, 0xd8, 0x45, 0x32, 0x94, 
	0x29, 0x4d, 0x60, 0x1c, 0xd3, 0x15, 0xb3, 0xfc, 0x04, 0x29, 0x37, 0x09, 0x4a, 0x4f, 0x92, 0xa2, 
	0x95, 0xb5, 0xfc, 0x65, 0x33, 0x91, 0x99, 0x8d, 0x6d, 0x98, 0x63, 0x1a, 0xdd, 0x24, 0x26, 0x33, 
	0x74, 0x21, 0x0c, 0x5c, 0xfe, 0x22, 0x17, 0xc4, 0x10, 0x26, 0x34, 0xa3, 0x41, 0x0e, 0x6b, 0xa6, 
	0x43, 0x1e, 0x00, 0x2d, 0xe7, 0x3c, 0xb2, 0x69, 0xce, 0x69, 0x82, 0x13, 0x9a, 0xdd, 0x98, 0xc6, 
	0x38, 0xb0, 0xa9, 0x4e, 0x70, 0xce, 0x53, 0x1c, 0xf5, 0xfc, 0x27, 0x44, 0xda, 0xb9, 0x0f, 0x6e, 
	0xaa, 0xe3, 0x9a, 0xe5, 0xa8, 0xe6, 0x38, 0xad, 0x81, 0x8e, 0x6d, 0xb8, 0x63, 0x9c, 0xf4, 0x14, 
	0x07, 0x3d, 0x6a, 0x9a, 0xd1, 0x7e, 0xdc, 0xd3, 0x1e, 0xfc, 0x10, 0x68, 0x43, 0x26, 0xe2, 0x51, 
	0x84, 0xd4, 0xa3, 0x9d, 0xea, 0x88, 0xa7, 0x3e, 0x0e, 0xba, 0x10, 0x7f, 0xba, 0xa3, 0x9a, 0xc6, 
	0x14, 0x06, 0x32, 0xb0, 0x09, 0x4f, 0x7c, 0x98, 0x73, 0x1a, 0xb7, 0x20, 0xc5, 0x27, 0x48, 0x79, 
	0x4b, 0x6a, 0x96, 0x73, 0x9a, 0xbe, 0x08, 0xc5, 0x23, 0x11, 0xe9, 0x48, 0x50, 0xfc, 0x72, 0x1a, 
	0xcb, 0xa8, 0xc5, 0x25, 0x0a, 0xf1, 0x47, 0x42, 0x5a, 0xa2, 0x16, 0xca, 0x64, 0xa6, 0x2d, 0x31, 
	0x69, 0x48, 0x40, 0x18, 0x02, 0x13, 0xb7, 0x64, 0x06, 0x36, 0x86, 0x51, 0x8a, 0x49, 0x32, 0x62, 
	0x12, 0xa5, 0x24, 0x46, 0x36, 0xd4, 0x91, 0x4d, 0x5f, 0xae, 0xc2, 0x14, 0xab, 0xf8, 0x25, 0x37, 
	0xd9, 0x09, 0x50, 0x7a, 0x7a, 0x13, 0x9a, 0xcb, 0x80, 0xe6, 0x37, 0xf3, 0x29, 0x50, 0x90, 0x3e, 
	0xd4, 0x9f, 0xf6, 0x90, 0xc7, 0x3d, 0x01, 0xf2, 0x50, 0x89, 0xcc, 0x34, 0xa3, 0x03, 0xe5, 0xa7, 
	0x3e, 0xfd, 0x51, 0xd0, 0x88, 0x44, 0x04, 0x13, 0xbc, 0x04, 0x10, 0xa6, 0xd8, 0xca, 0xd4, 0x96, 
	0x96, 0x74, 0xa4, 0x2b, 0x99, 0x09, 0x50, 0x8e, 0x2a, 0x15, 0x9d, 0x88, 0x24, 0x23, 0x15, 0xed, 
	0xa8, 0x4a, 0x75, 0x0a, 0x14, 0x96, 0x66, 0x14, 0x1f, 0xe5, 0xf8, 0xa6, 0x39, 0xf9, 0xe1, 0x51, 
	0x95, 0x38, 0xb4, 0x9e, 0xce, 0xa0, 0x05, 0x2b, 0x68, 0xf9, 0x0c, 0x7c, 0x42, 0xc4, 0x9e, 0xd8, 
	0x74, 0x65, 0x25, 0x19, 0x51, 0x49, 0x57, 0x68, 0x03, 0x9f, 0xea, 0x54, 0x06, 0x28, 0x0e, 0xf1, 
	0x47, 0x43, 0x7c, 0x52, 0x19, 0xeb, 0x68, 0x47, 0x33, 0x43, 0x91, 0x48, 0x40, 0x22, 0x22, 0x94, 
	0xcd, 0x70, 0xe7, 0x3e, 0xbd, 0x39, 0x4b, 0x4d, 0x46, 0x42, 0x93, 0xb3, 0x04, 0xe7, 0x3f, 0x25, 
	0xca, 0xcf, 0x6b, 0xf2, 0x92, 0x16, 0xbc, 0xc4, 0x86, 0x40, 0x33, 0xfa, 0x52, 0x90, 0x10, 0x24, 
	0x1e, 0xea, 0x88, 0xa7, 0x41, 0x53, 0x52, 0x13, 0xab, 0x0a, 0xc5, 0xa5, 0x24, 0xf9, 0x88, 0x49, 
	0x65, 0x42, 0x94, 0xa4, 0xa2, 0xc5, 0x29, 0x36, 0x75, 0xa9, 0x4a, 0x61, 0x82, 0xd3, 0xa2, 0x10, 
	0x85, 0x22, 0xfe, 0x2c, 0x27, 0x37, 0x28, 0xe2, 0xcf, 0x72, 0x72, 0x23, 0x9b, 0xe0, 0x38, 0xc7, 
	0x3c, 0xf4, 0xe9, 0x0f, 0x77, 0x7a, 0xd3, 0x9a, 0xd2, 0xd0, 0xa6, 0x38, 0xde, 0x31, 0x0f, 0x70, 
	0x5a, 0xa3, 0x18, 0xbb, 0xbc, 0x25, 0x2f, 0x93, 0xd9, 0x8d, 0x71, 0x36, 0x63, 0x98, 0xae, 0xfc, 
	0x04, 0x27, 0x40, 0x01, 0x0b, 0x63, 0x48, 0x33, 0x18, 0xb4, 0xe8, 0x64, 0x23, 0x11, 0xe9, 0xc8, 
	0x4e, 0xd0, 0x22, 0x18, 0xb9, 0x58, 0x25, 0x25, 0x0a, 0xf9, 0x07, 0x43, 0x4e, 0x62, 0x15, 0xba, 
	0xd4, 0x05, 0x2b, 0x2a, 0x59, 0x08, 0x40, 0x16, 0x72, 0x12, 0xaa, 0xc8, 0x25, 0x31, 0x6e, 0x09, 
	0x0a, 0x48, 0x24, 0xd2, 0x91, 0x9e, 0xb0, 0x05, 0x31, 0xac, 0xb1, 0x0c, 0x5b, 0x8e, 0xd2, 0x93, 
	0xa1, 0x98, 0x65, 0x32, 0xa9, 0x89, 0x8e, 0x6f, 0x36, 0x23, 0x98, 0xbe, 0x00, 0xe6, 0x32, 0xbb, 
	0x41, 0x4e, 0x81, 0xce, 0x63, 0x9c, 0xdc, 0xcc, 0xe6, 0x36, 0xc7, 0xe1, 0x4e, 0x79, 0x44, 0xb4, 
	0x1f, 0xe7, 0x08, 0xe7, 0x37, 0xc2, 0x71, 0xce, 0x78, 0xce, 0x03, 0x03, 0x18, 0xc4, 0x80, 0x0b, 
};




static unsigned char CAMCMP_DAT(ap_gain)[] =
{
	0x30, 0x30, 0x30, 0x38, 0x38, 0x38, 0x00, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x66, 0x66, 0x00, 
	0x00, 0x40, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x10, 0x10, 
	0x10, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 
	0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x50, 0x50, 0x20, 0x00, 
	0x00, 0x00, 0x20, 0x20, 0x20, 0x50, 0x50, 0x20, 0x00, 0x00, 0x00, 0x20, 0x20, 0x30, 0x50, 0x50, 
	0x20, 0x80, 0x80, 0x40, 0x40, 0x40, 0x64, 0x64, 0x64, 0x0A, 0x16, 0x16, 0x21, 0x17, 0x0A, 0x21, 
	0x17, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
};






static unsigned char CAMCMP_DAT(init_set_4_0x4F04_0x4F20)[] =
{
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4636_0x463B)[] =
{
	0x70, 
	0x6B, 
	0x68, 
	0x65, 
	0x61, 
	0x5D, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4706_0x470C)[] =
{
	0x46, 
	0x44, 
	0x41, 
	0x3E, 
	0x3D, 
	0x3B, 
	0x39, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x472C_0x4732)[] =
{
	0x4A, 
	0x48, 
	0x45, 
	0x42, 
	0x41, 
	0x3F, 
	0x3D, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x5000_0x5061)[] =
{

	0xF0, 0xFF, 
	0x02, 0x00, 
	0xF8, 0xFF, 
	0xFA, 0xFF, 
	0xFE, 0xFF, 
	0xE4, 0xFF, 








	0xFF, 0xFF, 

	0xFC, 0xFF, 
	0xFA, 0xFF, 
	0xF2, 0xFF, 
	0xFF, 0xFF, 
	0xE6, 0xFF, 







	0xCB, 0xFF, 
	0x01, 0x00, 
	0xFF, 0xFF, 
	0xF9, 0xFF, 
	0x08, 0x00, 
	0xDB, 0xFF, 
	0xB3, 0xFF, 
	0xF1, 0xFF, 
	0xF5, 0xFF, 
	0xFB, 0xFF, 
	0x07, 0x00, 
	0x98, 0xFF, 
	0xF0, 0xFF, 
	0xF3, 0xFF, 
	0xEA, 0xFF, 
	0xFA, 0xFF, 
	0xEE, 0xFF, 
	0xB8, 0xFF, 
	0xF0, 0xFF, 
	0x02, 0x00, 
	0xEA, 0xFF, 
	0xF8, 0xFF, 
	0xF2, 0xFF, 
	0xC0, 0xFF, 
	0xF8, 0xFF, 
	0xDC, 0xFF, 
	0xE0, 0xFF, 
	0xFF, 0xFF, 
	0xF6, 0xFF, 
	0xD8, 0xFF, 
	0x23, 
	0x1D, 
	0x2A, 
	0x1B, 
	0x63, 
	0x10, 
	0x75, 
	0x0D, 
	0x99, 
	0x0B, 
	0x4A, 
	0x11, 
	0x44, 
	0x0F, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x5092_0x50C1)[] =
{

	0xF8, 0xFF, 



	0xEA, 0xFF, 

	0xF8, 0xFF, 
	0xEA, 0xFF, 
	0xF8, 0xFF, 
	0xEA, 0xFF, 
	0xF8, 0xFF, 







	0xEA, 0xFF, 
	0x5F, 
	0x57, 
	0x5F, 

	0x57, 
	0x5F, 
	0x57, 
	0x5F, 






	0x57, 
	0xF8, 0xFF, 
	0xEA, 0xFF, 
	0xF8, 0xFF, 
	0xEA, 0xFF, 
	0xF8, 0xFF, 
	0xEA, 0xFF, 
	0xF8, 0xFF, 
	0xEA, 0xFF, 

	0x5F, 
	0x57, 
	0x5F, 
	0x57, 
	0x5F, 
	0x57, 
	0x5F, 
	0x57, 










};




static unsigned char CAMCMP_DAT(init_set_4_0x5436_0x546A)[] =
{
	0x00, 0x00, 
	0x0A, 0x00, 
	0x14, 0x00, 
	0x20, 0x00, 
	0x26, 0x00, 
	0x34, 0x00, 
	0x38, 0x00, 
	0x44, 0x00, 
	0x4A, 0x00, 
	0x54, 0x00, 
	0x58, 0x00, 
	0x64, 0x00, 
	0x66, 0x00, 
	0x70, 0x00, 
	0x72, 0x00, 
	0x7C, 0x00, 
	0x7E, 0x00, 
	0x86, 0x00, 
	0x5B, 0x00, 
	0xA9, 0x00, 
	0xCF, 0x00, 
	0xE3, 0x00, 
	0xF1, 0x00, 
	0xF7, 0x00, 
	0x01, 0x01, 
	0x03, 0x01, 
	0x0D, 0x01, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x54A2_0x54AE)[] =
{
	0x10, 0x04, 
	0x05, 0x40, 
	0x10, 0x04, 
	0x05, 0x40, 
	0x10, 0x04, 
	0x05, 0x40, 
	0x00, 0x23, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x5636_0x566A)[] =
{
	0x00, 0x00, 
	0x00, 0x00, 
	0x01, 0x00, 
	0x06, 0x00, 
	0x0C, 0x00, 
	0x15, 0x00, 
	0x1D, 0x00, 
	0x27, 0x00, 
	0x31, 0x00, 
	0x3A, 0x00, 
	0x43, 0x00, 
	0x4B, 0x00, 
	0x53, 0x00, 
	0x5B, 0x00, 
	0x63, 0x00, 
	0x6A, 0x00, 
	0x71, 0x00, 
	0x7B, 0x00, 
	0x3E, 0x00, 
	0xAC, 0x00, 
	0xD4, 0x00, 
	0xE6, 0x00, 
	0xF2, 0x00, 
	0xF8, 0x00, 
	0xFE, 0x00, 
	0x01, 0x01, 
	0x04, 0x01, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x56A2_0x56AE)[] =
{
	0x00, 0x19, 
	0x05, 0x40, 
	0x00, 0x19, 
	0x05, 0x40, 
	0x00, 0x19, 
	0x05, 0x40, 
	0x00, 0x23, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4016_0x4020)[] =
{

	0xA0, 0x28, 



	0x31, 0x03, 

	0x60, 0x05, 



	0x00, 0x04, 

	0x5F, 0x02, 



	0x00, 0x04, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4098_0x40A0)[] =
{
	0x01, 
	0x10, 
	0x02, 
	0x64, 
	0x20, 
	0x07, 
	0x06, 
	0x62, 
	0x64, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4964_0x4968)[] =
{
	0xF4, 0x01, 
	0xF4, 0x01, 
	0x02, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4442_0x4448)[] =
{

	0xB2, 0x0C, 
	0xE6, 0x14, 
	0x7E, 0x11, 
	0xAF, 0x0E, 






};




static unsigned char CAMCMP_DAT(init_set_4_0x4826_0x4836)[] =
{
	0x05, 0x00, 
	0x05, 0x00, 
	0x00, 0x00, 
	0x1E, 0x00, 
	0x00, 0x00, 
	0x1E, 0x00, 
	0xF4, 0x01, 
	0xF4, 0x01, 
	0x64, 0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x483C_0x483F)[] =
{
	0x01, 
	0x04, 
	0x02, 
	0x01, 
	0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4846_0x484F)[] =
{
	0x01, 
	0x01, 
	0x02, 
	0x02, 
	0x03, 
	0x03, 
	0x03, 
	0x03, 
	0x08, 
	0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4C2C_0x4C85)[] =
{
	0xCE, 0x04, 
	0x41, 0x01, 
	0xE6, 0x00, 
	0xE6, 0x00, 
	0xBA, 0x04, 
	0x2D, 0x01, 
	0x0E, 0x01, 
	0x0E, 0x01, 
	0xB2, 0x02, 
	0x5D, 0x03, 
	0xE6, 0x00, 
	0xE6, 0x00, 
	0x9E, 0x02, 
	0x49, 0x03, 
	0x0E, 0x01, 
	0x0E, 0x01, 
	0xCE, 0x04, 
	0x5D, 0x03, 
	0xE6, 0x00, 
	0xE6, 0x00, 
	0xBA, 0x04, 
	0x49, 0x03, 
	0x0E, 0x01, 
	0x0E, 0x01, 
	0xEA, 0x06, 
	0x5D, 0x03, 
	0xE6, 0x00, 
	0xE6, 0x00, 
	0xD6, 0x06, 
	0x49, 0x03, 
	0x0E, 0x01, 
	0x0E, 0x01, 
	0xCE, 0x04, 
	0x79, 0x05, 
	0xE6, 0x00, 
	0xE6, 0x00, 
	0xBA, 0x04, 
	0x65, 0x05, 
	0x0E, 0x01, 
	0x0E, 0x01, 
	0x00, 
	0x00, 
	0x00, 
	0x00, 
	0x0A, 
	0x00, 
	0x00, 
	0x00, 
	0x00, 
	0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x6E02_0x6E14)[] =
{
	0x01, 0x00, 
	0x04, 0x00, 
	0x04, 
	0x01, 
	0x64, 0x00, 
	0x03, 
	0x02, 
	0xF4, 0x01, 
	0xF4, 0x01, 
	0x00, 0x00, 
	0x64, 0x00, 
	0x02, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x6E8E_0x6E94)[] =
{
	0x64, 0x00, 
	0x2C, 0x01, 
	0x64, 0x00, 
	0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x4F2C_0x4F41)[] =
{
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x08, 
	0x0E, 
	0x14, 
	0x0A, 
	0x10, 
	0x16, 
	0x08, 
	0x18, 
	0x20, 
	0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x5858_0x585C)[] =
{
	0x29, 0x0B, 
	0x2D, 0x07, 
	0x00, 0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x5888_0x596A)[] =
{
	0x14, 0x00, 

	0x06, 0x00, 
	0x03, 0x00, 




	0x40, 0x00, 
	0x40, 0x00, 
	0x40, 0x00, 
	0x05, 0x00, 
	0x03, 0x00, 
	0x02, 0x00, 
	0x09, 0x00, 
	0x07, 0x00, 
	0x06, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x05, 0x00, 
	0x03, 0x00, 
	0x02, 0x00, 
	0x09, 0x00, 
	0x07, 0x00, 
	0x06, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x03, 0x00, 
	0x04, 0x00, 
	0x01, 0x00, 
	0x07, 0x00, 
	0x08, 0x00, 
	0x05, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x03, 0x00, 
	0x04, 0x00, 
	0x01, 0x00, 
	0x07, 0x00, 
	0x08, 0x00, 
	0x05, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x05, 0x00, 
	0x04, 0x00, 
	0x02, 0x00, 
	0x09, 0x00, 
	0x08, 0x00, 
	0x06, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x09, 0x00, 
	0x04, 0x00, 
	0x02, 0x00, 
	0x09, 0x00, 
	0x08, 0x00, 
	0x06, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x5E, 0x01, 
	0x5E, 0x01, 
	0x5E, 0x01, 
	0xF4, 0x01, 
	0xF4, 0x01, 
	0x20, 0x03, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x03, 0x00, 
	0x03, 0x00, 
	0x01, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x5E, 0x01, 
	0x5E, 0x01, 
	0x5E, 0x01, 
	0xF4, 0x01, 
	0xF4, 0x01, 
	0x20, 0x03, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x03, 0x00, 
	0x03, 0x00, 
	0x01, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x5E, 0x01, 
	0x5E, 0x01, 
	0x32, 0x00, 
	0xF4, 0x01, 
	0xF4, 0x01, 
	0xC8, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x00, 0x00, 
	0x03, 0x00, 
	0x03, 0x00, 
	0x01, 0x00, 
};




static unsigned char CAMCMP_DAT(init_set_4_0x59D4_0x59F4)[] =
{
	0xDF, 0xFF, 
	0xE9, 0xFF, 
	0xF6, 0xFF, 
	0xDF, 0xFF, 
	0xE9, 0xFF, 
	0xF6, 0xFF, 
	0xE0, 0xFF, 
	0xE0, 0xFF, 
	0xE0, 0xFF, 
	0xE0, 0xFF, 
	0xE0, 0xFF, 
	0xE0, 0xFF, 
	0xF9, 
	0xF9, 
	0xF9, 
	0xFE, 
	0xFE, 
	0xFE, 
	0xF9, 
	0xF9, 
	0xF9, 
};





static camcmp_ius006f_reg_val_type CAMCMP_REG(init_set_4)[] =
{




	{CAMCMP_REG_WRITE, 0x4F04, 0x00000000, CAMCMP_DAT(init_set_4_0x4F04_0x4F20), sizeof(CAMCMP_DAT(init_set_4_0x4F04_0x4F20))},      















	{CAMCMP_REG_WRITE, 0x423F, 0x00000000, CAMCMP_DAT(ae_frm_1),  sizeof(CAMCMP_DAT(ae_frm_1))},   
	{CAMCMP_REG_WRITE, 0x42BD, 0x00000000, CAMCMP_DAT(ae_frm_2),  sizeof(CAMCMP_DAT(ae_frm_2))},   







	{CAMCMP_REG_WRITE, 0x4636, 0x00000000, CAMCMP_DAT(init_set_4_0x4636_0x463B), sizeof(CAMCMP_DAT(init_set_4_0x4636_0x463B))},      








	{CAMCMP_REG_WRITE, 0x4686, 0x00000064, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4687, 0x00000064, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4688, 0x00000062, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x469D, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x46EC, 0x0000001D, NULL,                CAMCMP_D_LEN_BYTE},      

	{CAMCMP_REG_WRITE, 0x4706, 0x00000000, CAMCMP_DAT(init_set_4_0x4706_0x470C), sizeof(CAMCMP_DAT(init_set_4_0x4706_0x470C))},      
	{CAMCMP_REG_WRITE, 0x472C, 0x00000000, CAMCMP_DAT(init_set_4_0x472C_0x4732), sizeof(CAMCMP_DAT(init_set_4_0x472C_0x4732))},      
















	{CAMCMP_REG_WRITE, 0x473C, 0x0000001C, NULL,                CAMCMP_D_LEN_BYTE},      










	{CAMCMP_REG_WRITE, 0x9000, 0x00008282, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x9002, 0x00000000, CAMCMP_DAT(cxc_data),sizeof(CAMCMP_DAT(cxc_data))}, 
	{CAMCMP_REG_WRITE, 0xA000, 0x00009191, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0xA002, 0x00000000, CAMCMP_DAT(shd_data),sizeof(CAMCMP_DAT(shd_data))}, 






	{CAMCMP_REG_WRITE, 0x0068, 0x0000005F, NULL,                CAMCMP_D_LEN_BYTE},      

	{CAMCMP_REG_WRITE, 0x5000, 0x00000000, CAMCMP_DAT(init_set_4_0x5000_0x5061),  sizeof(CAMCMP_DAT(init_set_4_0x5000_0x5061))},  
















































































	{CAMCMP_REG_WRITE, 0x5092, 0x00000000, CAMCMP_DAT(init_set_4_0x5092_0x50C1), sizeof(CAMCMP_DAT(init_set_4_0x5092_0x50C1))},  















































































	{CAMCMP_REG_WRITE, 0x0105, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      








































	{CAMCMP_REG_WRITE, 0x52AE, 0x00002100, NULL,                CAMCMP_D_LEN_WORD},      





	{CAMCMP_REG_WRITE, 0x5436, 0x00000000, CAMCMP_DAT(init_set_4_0x5436_0x546A), sizeof(CAMCMP_DAT(init_set_4_0x5436_0x546A))},  
	{CAMCMP_REG_WRITE, 0x54A2, 0x00000000, CAMCMP_DAT(init_set_4_0x54A2_0x54AE), sizeof(CAMCMP_DAT(init_set_4_0x54A2_0x54AE))},  
	{CAMCMP_REG_WRITE, 0x5636, 0x00000000, CAMCMP_DAT(init_set_4_0x5636_0x566A), sizeof(CAMCMP_DAT(init_set_4_0x5636_0x566A))},  
	{CAMCMP_REG_WRITE, 0x56A2, 0x00000000, CAMCMP_DAT(init_set_4_0x56A2_0x56AE), sizeof(CAMCMP_DAT(init_set_4_0x56A2_0x56AE))},  






































































	{CAMCMP_REG_WRITE, 0x0105, 0x00000040, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0387, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4A00, 0x00000110, NULL,                CAMCMP_D_LEN_WORD},      









	{CAMCMP_REG_WRITE, 0x4016, 0x00000000, CAMCMP_DAT(init_set_4_0x4016_0x4020), sizeof(CAMCMP_DAT(init_set_4_0x4016_0x4020))},  



































	{CAMCMP_REG_WRITE, 0x4042, 0x00000056, NULL,                CAMCMP_D_LEN_BYTE},      











	{CAMCMP_REG_WRITE, 0x404D, 0x000000A0, NULL,                CAMCMP_D_LEN_BYTE},      













	{CAMCMP_REG_WRITE, 0x4098, 0x00000000, CAMCMP_DAT(init_set_4_0x4098_0x40A0), sizeof(CAMCMP_DAT(init_set_4_0x4098_0x40A0))},      


















	{CAMCMP_REG_WRITE, 0x480E, 0x000000FA, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4810, 0x000000FA, NULL,                CAMCMP_D_LEN_WORD},      











	{CAMCMP_REG_WRITE, 0x481C, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      


	{CAMCMP_REG_WRITE, 0x481D, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      










	{CAMCMP_REG_WRITE, 0x4856, 0x0000000A, NULL,                CAMCMP_D_LEN_BYTE},      













	{CAMCMP_REG_WRITE, 0x4874, 0x00000200, NULL,                CAMCMP_D_LEN_WORD},      

















	{CAMCMP_REG_WRITE, 0x4898, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      



















	{CAMCMP_REG_WRITE, 0x4964, 0x00000000, CAMCMP_DAT(init_set_4_0x4964_0x4968), sizeof(CAMCMP_DAT(init_set_4_0x4964_0x4968))},      





	{CAMCMP_REG_WRITE, 0x496E, 0x000003E8, NULL,                CAMCMP_D_LEN_WORD},      











































	{CAMCMP_REG_WRITE, 0x4424, 0x00000018, NULL,                CAMCMP_D_LEN_BYTE},      














	{CAMCMP_REG_WRITE, 0x442E, 0x00000C7C, NULL,                CAMCMP_D_LEN_WORD},      














	{CAMCMP_REG_WRITE, 0x4442, 0x00000000, CAMCMP_DAT(init_set_4_0x4442_0x4448), sizeof(CAMCMP_DAT(init_set_4_0x4442_0x4448))},      
























	{CAMCMP_REG_WRITE, 0x4453, 0x0000007B, NULL,                CAMCMP_D_LEN_BYTE},      




















































	{CAMCMP_REG_WRITE, 0x4826, 0x00000000, CAMCMP_DAT(init_set_4_0x4826_0x4836), sizeof(CAMCMP_DAT(init_set_4_0x4826_0x4836))},      



















	{CAMCMP_REG_WRITE, 0x483C, 0x00000000, CAMCMP_DAT(init_set_4_0x483C_0x483F), sizeof(CAMCMP_DAT(init_set_4_0x483C_0x483F))},  














	{CAMCMP_REG_WRITE, 0x4846, 0x00000000, CAMCMP_DAT(init_set_4_0x4846_0x484F), sizeof(CAMCMP_DAT(init_set_4_0x4846_0x484F))},  


















	{CAMCMP_REG_WRITE, 0x4854, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      






	{CAMCMP_REG_WRITE, 0x4858, 0x0000000A, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4859, 0x00000005, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x485A, 0x00002710, NULL,                CAMCMP_D_LEN_WORD},      









	{CAMCMP_REG_WRITE, 0x4888, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4969, 0x00000003, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x496A, 0x00000003, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x496B, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x496C, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      









	{CAMCMP_REG_WRITE, 0x4C2C, 0x00000000, CAMCMP_DAT(init_set_4_0x4C2C_0x4C85), sizeof(CAMCMP_DAT(init_set_4_0x4C2C_0x4C85))},  




















































	{CAMCMP_REG_WRITE, 0x6E00, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      

	{CAMCMP_REG_WRITE, 0x6E02, 0x00000000, CAMCMP_DAT(init_set_4_0x6E02_0x6E14), sizeof(CAMCMP_DAT(init_set_4_0x6E02_0x6E14))},  
























	{CAMCMP_REG_WRITE, 0x6E8E, 0x00000000, CAMCMP_DAT(init_set_4_0x6E8E_0x6E94), sizeof(CAMCMP_DAT(init_set_4_0x6E8E_0x6E94))},  






	{CAMCMP_REG_WRITE, 0x4F24, 0x00000032, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4F25, 0x00000009, NULL,                CAMCMP_D_LEN_BYTE},      

	{CAMCMP_REG_WRITE, 0x4F2C, 0x00000000, CAMCMP_DAT(init_set_4_0x4F2C_0x4F41), sizeof(CAMCMP_DAT(init_set_4_0x4F2C_0x4F41))},  
	{CAMCMP_REG_WRITE, 0x5858, 0x00000000, CAMCMP_DAT(init_set_4_0x5858_0x585C), sizeof(CAMCMP_DAT(init_set_4_0x5858_0x585C))},  






















	{CAMCMP_REG_WRITE, 0x5888, 0x00000000, CAMCMP_DAT(init_set_4_0x5888_0x596A), sizeof(CAMCMP_DAT(init_set_4_0x5888_0x596A))},  



























































































































	{CAMCMP_REG_WRITE, 0x596C, 0x00000000, CAMCMP_DAT(ap_gain), sizeof(CAMCMP_DAT(ap_gain))},  

	{CAMCMP_REG_WRITE, 0x59D4, 0x00000000, CAMCMP_DAT(init_set_4_0x59D4_0x59F4), sizeof(CAMCMP_DAT(init_set_4_0x59D4_0x59F4))},  

























	{CAMCMP_REG_WRITE, 0x4822, 0x00000004, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4824, 0x00000008, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4838, 0x00000008, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4844, 0x00000020, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x486C, 0x00000010, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4870, 0x00000010, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x486E, 0x00000008, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4872, 0x00000008, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4876, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4878, 0x000002F6, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4852, 0x000000AF, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x486A, 0x000000AF, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x487A, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x487C, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x487E, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4880, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      


};












static unsigned char CAMCMP_DAT(af_drv)[] =
{
	0xF7, 0xB5, 0x0E, 0x4D, 0x0E, 0x4C, 0x0F, 0x4A, 0x0F, 0x4F, 0x10, 0x4B, 0x00, 0x21, 0x00, 0x2A,
	0x04, 0xD9, 0x6E, 0x5C, 0x66, 0x54, 0x01, 0x31, 0x91, 0x42, 0xFA, 0xD3, 0x00, 0x21, 0x00, 0x2B,
	0x04, 0xD9, 0x00, 0x22, 0x7A, 0x54, 0x01, 0x31, 0x99, 0x42, 0xFB, 0xD3, 0x08, 0x49, 0x88, 0x60,
	0x01, 0x99, 0x08, 0x48, 0x08, 0x60, 0x03, 0xB0, 0x01, 0x20, 0xF0, 0xBD, 0x14, 0x0D, 0x18, 0x00,
	0x14, 0x0D, 0x18, 0x00, 0x04, 0x00, 0x00, 0x00, 0x18, 0x0D, 0x18, 0x00, 0x0C, 0x00, 0x00, 0x00,
	0x18, 0x0D, 0x18, 0x00, 0x14, 0x0D, 0x18, 0x00, 0x80, 0xB5, 0x1F, 0x78, 0x00, 0x2F, 0x02, 0xD1,
	0x00, 0xF0, 0xB2, 0xF8, 0x80, 0xBD, 0x00, 0xF0, 0x01, 0xF8, 0xFB, 0xE7, 0xFF, 0xB5, 0x83, 0xB0,
	0x0C, 0x1C, 0x1F, 0x1C, 0x00, 0x25, 0x08, 0x23, 0xF8, 0x5E, 0xEB, 0x43, 0x51, 0x4E, 0x98, 0x42,
	0x25, 0xD1, 0xF2, 0x80, 0xA0, 0x1A, 0x02, 0xD5, 0x40, 0x42, 0x01, 0x21, 0x00, 0xE0, 0x00, 0x21,
	0x31, 0x70, 0x00, 0x04, 0x00, 0x0C, 0x70, 0x80, 0xB0, 0x80, 0x18, 0xD1, 0x20, 0x03, 0x30, 0x30,
	0x00, 0x90, 0x00, 0xF0, 0xE4, 0xF8, 0x00, 0x90, 0xB0, 0x68, 0x6A, 0x46, 0x03, 0x21, 0x03, 0x68,
	0x33, 0x20, 0x7F, 0xF6, 0xB2, 0xFB, 0x01, 0x28, 0x04, 0xD0, 0x00, 0x20, 0xC0, 0x43, 0x38, 0x81,
	0x00, 0x20, 0x7C, 0xE0, 0x03, 0x98, 0x04, 0x80, 0x01, 0x20, 0x38, 0x81, 0x77, 0xE0, 0x78, 0x78,
	0x3C, 0x4E, 0x02, 0x90, 0xB9, 0x78, 0x40, 0x00, 0x40, 0x1A, 0xF9, 0x78, 0x40, 0x1A, 0xB1, 0x88,
	0x49, 0x00, 0x7F, 0xF6, 0x9F, 0xFB, 0x04, 0x04, 0x24, 0x0C, 0x38, 0x8A, 0xA0, 0x42, 0x02, 0xDA,
	0x01, 0x21, 0x04, 0x1C, 0x00, 0xE0, 0x00, 0x21, 0x01, 0x91, 0x02, 0x98, 0x00, 0x26, 0x00, 0x28,
	0x0B, 0xDD, 0x30, 0x1C, 0x21, 0x1C, 0x3A, 0x1C, 0x00, 0xF0, 0x96, 0xF8, 0x40, 0x19, 0x05, 0x04,
	0x2D, 0x0C, 0x78, 0x78, 0x01, 0x36, 0xB0, 0x42, 0xF3, 0xDC, 0x2A, 0x4E, 0xB0, 0x88, 0x40, 0x1B,
	0xB0, 0x80, 0x08, 0x23, 0xF8, 0x5E, 0x01, 0x23, 0xD8, 0x42, 0x13, 0xD1, 0x01, 0x99, 0x00, 0x29,
	0x02, 0xD1, 0x01, 0x21, 0x39, 0x81, 0x0D, 0xE0, 0x71, 0x88, 0x28, 0x1C, 0x7F, 0xF6, 0xBC, 0xFA,
	0x38, 0x81, 0x71, 0x88, 0x28, 0x1C, 0x7F, 0xF6, 0xB7, 0xFA, 0x00, 0x29, 0x02, 0xD0, 0x38, 0x89,
	0x01, 0x30, 0x38, 0x81, 0x78, 0x78, 0x00, 0x25, 0x00, 0x28, 0x2F, 0xDD, 0x28, 0x1C, 0x21, 0x1C,
	0x3A, 0x1C, 0x00, 0xF0, 0x69, 0xF8, 0x01, 0x99, 0x00, 0x29, 0x07, 0xD1, 0xB1, 0x88, 0x00, 0x29,
	0x04, 0xDD, 0x01, 0x30, 0x00, 0x04, 0x00, 0x0C, 0x01, 0x39, 0xB1, 0x80, 0x31, 0x78, 0x00, 0x29,
	0x02, 0xD1, 0xF1, 0x88, 0x08, 0x18, 0x01, 0xE0, 0xF1, 0x88, 0x08, 0x1A, 0xF0, 0x80, 0xF0, 0x88,
	0x00, 0x03, 0x30, 0x30, 0x00, 0x90, 0x00, 0xF0, 0x6A, 0xF8, 0x00, 0x90, 0xB0, 0x68, 0x6A, 0x46,
	0x03, 0x21, 0x03, 0x68, 0x33, 0x20, 0x7F, 0xF6, 0x38, 0xFB, 0x01, 0x28, 0x85, 0xD1, 0xF0, 0x88,
	0x03, 0x99, 0x08, 0x80, 0x78, 0x78, 0x01, 0x35, 0xA8, 0x42, 0xCF, 0xDC, 0x01, 0x20, 0x07, 0xB0,
	0xF0, 0xBD, 0x00, 0x00, 0x18, 0x0D, 0x18, 0x00, 0xF8, 0xB5, 0x1C, 0x1C, 0x15, 0x1C, 0x06, 0x1C,
	0x0F, 0x1C, 0x38, 0x03, 0x30, 0x30, 0x00, 0x90, 0x00, 0xF0, 0x49, 0xF8, 0x00, 0x90, 0x0A, 0x48,
	0x6A, 0x46, 0x80, 0x68, 0x03, 0x21, 0x03, 0x68, 0x33, 0x20, 0x7F, 0xF6, 0x16, 0xFB, 0x01, 0x28,
	0x01, 0xD0, 0x00, 0x20, 0x06, 0xE0, 0x38, 0x1C, 0x29, 0x1C, 0x22, 0x1C, 0x37, 0x80, 0x00, 0xF0,
	0x05, 0xF8, 0x01, 0x20, 0xF8, 0xBD, 0x00, 0x00, 0x18, 0x0D, 0x18, 0x00, 0x80, 0xB5, 0x17, 0x1C,
	0x40, 0x1A, 0x00, 0xD5, 0x40, 0x42, 0xB9, 0x89, 0x48, 0x43, 0xF9, 0x89, 0x09, 0x18, 0x78, 0x69,
	0x09, 0x18, 0x7F, 0xF6, 0x49, 0xFA, 0x03, 0x4B, 0x98, 0x42, 0x00, 0xD9, 0x18, 0x1C, 0x38, 0x81,
	0x80, 0xBD, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0x80, 0xB5, 0x93, 0x78, 0x83, 0x42, 0x05, 0xDD,
	0x01, 0x30, 0x48, 0x43, 0x0A, 0x1C, 0x01, 0x1C, 0x58, 0x1C, 0x09, 0xE0, 0x53, 0x78, 0xD2, 0x78,
	0x9F, 0x1A, 0x87, 0x42, 0x09, 0xDC, 0x18, 0x1A, 0x48, 0x43, 0x0B, 0x1C, 0x01, 0x1C, 0x50, 0x1C,
	0x7F, 0xF6, 0xE0, 0xFA, 0x00, 0x04, 0x00, 0x0C, 0x80, 0xBD, 0x08, 0x1C, 0xFC, 0xE7, 0xFF, 0x21,
	0x09, 0x04, 0x01, 0x40, 0x09, 0x0C, 0xFF, 0x22, 0x12, 0x02, 0x02, 0x40, 0x11, 0x43, 0x00, 0x06,
	0x00, 0x0E, 0x00, 0x04, 0x08, 0x43, 0xF7, 0x46, 0xE5, 0x0A, 0x18, 0x00
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(init_af_drv)[] =
{
	{CAMCMP_REG_WRITE, 0xC000, 0x00000000, CAMCMP_DAT(af_drv),  sizeof(CAMCMP_DAT(af_drv))},  
	{CAMCMP_REG_WRITE, 0x485E, 0x00008D27, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x485C, 0x0000028C, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x000A, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_POLL1, 0x000A, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(init_set_5)[] =
{














	{CAMCMP_REG_WRITE, 0x0084, 0x0000014A, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0086, 0x00000298, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0088, 0x000004E2, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x008A, 0x00000A96, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x008C, 0x000007D0, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x008E, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0090, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0092, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      


	{CAMCMP_REG_WRITE, 0x01B1, 0x00000090, NULL,                CAMCMP_D_LEN_BYTE},      




	{CAMCMP_REG_WRITE, 0x01B2, 0x00000065, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x01B3, 0x00000080, NULL,                CAMCMP_D_LEN_BYTE},      


























































	{CAMCMP_REG_WRITE, 0x01D3, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
















	{CAMCMP_REG_WRITE, 0x01F8, 0x00000095, NULL,                CAMCMP_D_LEN_BYTE},      







	{CAMCMP_REG_WRITE, 0x01FB, 0x00000095, NULL,                CAMCMP_D_LEN_BYTE},      







	{CAMCMP_REG_WRITE, 0x02D7, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      













	{CAMCMP_REG_WRITE, 0x0013, 0x00000003, NULL,                CAMCMP_D_LEN_BYTE},      




















































	{CAMCMP_REG_WRITE, 0x034F, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      


	{CAMCMP_REG_WRITE, 0x0386, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      




	{CAMCMP_REG_WRITE, 0x3208, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      






























	{CAMCMP_REG_WRITE, 0x4E0C, 0x00000331, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4E0E, 0x00000B31, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4E10, 0x000000D9, NULL,                CAMCMP_D_LEN_WORD},      
};














static camcmp_ius006f_reg_val_type CAMCMP_REG(wb_auto)[] =
{
	{CAMCMP_REG_WRITE, 0x0102, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x446D, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A01, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A02, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A03, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A04, 0x0000006D, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A05, 0x00000044, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A06, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A07, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A08, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A31, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A32, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A00, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(wb_sunny)[] =
{
	{CAMCMP_REG_WRITE, 0x0102, 0x00000024, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x446D, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A01, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A02, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A03, 0x00000024, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A04, 0x0000006D, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A05, 0x00000044, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A06, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A07, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A08, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A31, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A32, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A00, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(wb_cloudy)[] =
{
	{CAMCMP_REG_WRITE, 0x0102, 0x00000026, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x446D, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A01, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A02, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A03, 0x00000026, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A04, 0x0000006D, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A05, 0x00000044, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A06, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A07, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A08, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A31, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A32, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A00, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(wb_inc)[] =
{
	{CAMCMP_REG_WRITE, 0x0102, 0x00000028, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x446D, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A01, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A02, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A03, 0x00000028, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A04, 0x0000006D, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A05, 0x00000044, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A06, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A07, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A08, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A31, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A32, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A00, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(wb_fluor)[] =
{
	{CAMCMP_REG_WRITE, 0x0102, 0x00000027, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x446D, 0x0000003E, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A01, 0x00000002, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A02, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A03, 0x00000027, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A04, 0x0000006D, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A05, 0x00000044, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A06, 0x0000003E, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A07, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A08, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A31, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A32, 0x00000000, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x6A00, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
};



























































static camcmp_ius006f_reg_val_type CAMCMP_REG(wb_led)[] =
{
	{CAMCMP_REG_WRITE, 0x0102, 0x00000025, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x443A, 0x00000C03, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x443C, 0x0000179E, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x446D, 0x000000A0, NULL,                CAMCMP_D_LEN_BYTE},      
};
















static camcmp_ius006f_reg_val_type CAMCMP_REG(night_off)[] =
{
	{CAMCMP_REG_WRITE, 0x404C, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4424, 0x0000000C, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02A4, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02A6, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4016, 0x00002C13, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4018, 0x00000331, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401A, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401C, 0x00000400, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401E, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4020, 0x00000400, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x01BD, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(night_on)[] =
{
	{CAMCMP_REG_WRITE, 0x404C, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4424, 0x0000000C, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02A4, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02A6, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4016, 0x00002C13, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4018, 0x00000331, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401A, 0x00000257, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401C, 0x00000400, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401E, 0x000005A8, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4020, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x01BD, 0x00000004, NULL,                CAMCMP_D_LEN_BYTE},      
};





static camcmp_ius006f_reg_val_type CAMCMP_REG(movie)[] =
{
	{CAMCMP_REG_WRITE, 0x404C, 0x00000020, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4424, 0x0000000C, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02A4, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02A6, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4016, 0x00002C13, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4018, 0x00000331, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401A, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401C, 0x00000400, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x401E, 0x00000000, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4020, 0x00000400, NULL,                CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x01BD, 0x00000001, NULL,                CAMCMP_D_LEN_BYTE},      
};













static camcmp_ius006f_af_val_type CAMCMP_DAT(af_val) =
{
	1244,          
	12906,         
	8500,          
	3800,          
	900,           
	500,           
	2000,          
	250,           
	500            
};












static uint16_t CAMCMP_DAT(version) = 0x0100;











static camcmp_ius006f_reg_val_type CAMCMP_REG(cap_size)[] =
{
	{CAMCMP_REG_WRITE, 0x0024, 0x00000A20, NULL,  CAMCMP_D_LEN_WORD},  
	{CAMCMP_REG_WRITE, 0x002A, 0x00000798, NULL,  CAMCMP_D_LEN_WORD}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(moni_size)[] =
{
	{CAMCMP_REG_WRITE, 0x0022, 0x00000280, NULL,  CAMCMP_D_LEN_WORD},  
	{CAMCMP_REG_WRITE, 0x0028, 0x000001E0, NULL,  CAMCMP_D_LEN_WORD}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(chg_mode)[] =
{
	{CAMCMP_REG_WRITE, 0x0011, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_POLL1, 0x00F8, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000006, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(zoom)[] =
{
	{CAMCMP_REG_WRITE, 0x0032, 0x00000100, NULL,  CAMCMP_D_LEN_WORD}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(brightness)[] =
{
	{CAMCMP_REG_WRITE, 0x0080, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(effect)[] =
{
	{CAMCMP_REG_WRITE, 0x005F, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(quality)[] =
{
	{CAMCMP_REG_WRITE, 0x0204, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(int_clr)[] =
{
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(af_cancel)[] =
{
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000010, NULL,  CAMCMP_D_LEN_BYTE},    
	{CAMCMP_REG_WRITE, 0x4885, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},   
	{CAMCMP_REG_POLL2, 0x6D76, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE}     
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(af_mode)[] =
{
	{CAMCMP_REG_WRITE, 0x002F, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(mf_pos)[] =
{
	{CAMCMP_REG_WRITE, 0x4852, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(mf_start)[] =
{
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000010, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x4850, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_POLL1, 0x00F8, 0x00000010, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000010, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(ae_normal)[] =
{
	{CAMCMP_REG_WRITE, 0x0103, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(ae_long)[] =
{
	{CAMCMP_REG_WRITE, 0x0103, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(ptnchk_off)[] =
{
	{CAMCMP_REG_WRITE, 0x2800, 0x00000000, NULL,  CAMCMP_D_LEN_LWORD}, 
	{CAMCMP_REG_WRITE, 0x3200, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x3205, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x0068, 0x0000005f, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x4F24, 0x00000032, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x4F25, 0x00000009, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x4E16, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x0105, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x01F8, 0x00000095, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x01FB, 0x00000095, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x3202, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(ptnchk_on)[] =
{
	{CAMCMP_REG_WRITE, 0x2800, 0x07000000, NULL,  CAMCMP_D_LEN_LWORD}, 
	{CAMCMP_REG_WRITE, 0x3200, 0x00000006, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x3205, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x0068, 0x00000050, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x4F24, 0x00000010, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x4F25, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x4E16, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x0105, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x01F8, 0x00000054, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x01FB, 0x00000054, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x3202, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(chk_af_lock)[] =
{
	{CAMCMP_REG_POLL3, 0x0000, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000010, NULL,  CAMCMP_D_LEN_BYTE}   
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(thumbnail)[] =
{
	{CAMCMP_REG_WRITE, 0x0222, 0x00009B9A, NULL,  CAMCMP_D_LEN_WORD},	
	{CAMCMP_REG_WRITE, 0x02D2, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE},	
	{CAMCMP_REG_WRITE, 0x02D3, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},	
	{CAMCMP_REG_WRITE, 0x02D4, 0x00009D9C, NULL,  CAMCMP_D_LEN_WORD}	
};






static camcmp_ius006f_reg_val_type CAMCMP_REG(jpeg_limit)[] =
{
	{CAMCMP_REG_WRITE, 0x020A, 0x000003A7, NULL,  CAMCMP_D_LEN_WORD},	
	{CAMCMP_REG_WRITE, 0x020C, 0x0000078F, NULL,  CAMCMP_D_LEN_WORD},	
	{CAMCMP_REG_WRITE, 0x020E, 0x00000B77, NULL,  CAMCMP_D_LEN_WORD}	
};






static camcmp_ius006f_reg_val_type CAMCMP_REG(af_restart)[] =
{
	{CAMCMP_REG_WRITE, 0x0015, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},   
};








static camcmp_ius006f_reg_val_type CAMCMP_REG(cap_half_ae_ctrl)[] =
{
	{CAMCMP_REG_WRITE, 0x027D, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(set_shut)[] =
{
	
	{CAMCMP_REG_WRITE, 0x027E, 0x00000000, NULL,  CAMCMP_D_LEN_WORD},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(set_gain)[] =
{
	{CAMCMP_REG_WRITE, 0x0280, 0x00000000, NULL,  CAMCMP_D_LEN_WORD},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(cap_gainoffset)[] =
{
	{CAMCMP_REG_WRITE, 0x0282, 0x00000000, NULL,  CAMCMP_D_LEN_WORD},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(set_capture_num)[] =
{
	{CAMCMP_REG_WRITE, 0x0014, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(set_ae_stop)[] =
{
	{CAMCMP_REG_WRITE, 0x027D, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};











static camcmp_ius006f_reg_val_type CAMCMP_REG(scene_change)[] =
{
	
	{CAMCMP_REG_WRITE, 0x01BD, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A01, 0x000000BD, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A02, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A03, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A04, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A05, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A31, 0x00000016, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A32, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A33, 0x000000CD, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A34, 0x0000002B, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A35, 0x00000018, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A36, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A37, 0x00000030, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A38, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A39, 0x0000001A, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3A, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3B, 0x00000052, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3C, 0x00000005, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3D, 0x0000001C, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3E, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3F, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A40, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A41, 0x0000001E, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A42, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A43, 0x0000005C, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A44, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A45, 0x00000020, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A46, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A47, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A48, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A49, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A4A, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A00, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(scene_angle)[] =
{
	
	{CAMCMP_REG_WRITE, 0x0104, 0x0000000B, NULL,  CAMCMP_D_LEN_BYTE},  
};






static camcmp_ius006f_reg_val_type CAMCMP_REG(camera_mode)[] =
{
	
	{CAMCMP_REG_WRITE, 0x0100, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};








static camcmp_ius006f_reg_val_type CAMCMP_REG(jpeg_intsts)[] =
{
	{CAMCMP_REG_POLL1, 0x00F8, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE}   
};







static camcmp_ius006f_reg_val_type CAMCMP_REG(flc_mode)[] =
{
	{CAMCMP_REG_WRITE, 0x4001, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}   
};






static camcmp_ius006f_reg_val_type CAMCMP_REG(afc_status)[] =
{
	
	{CAMCMP_REG_READ, 0x6D90, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(set_saf_mode)[] =
{
	
	{CAMCMP_REG_WRITE, 0x4887, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(dac_code)[] =
{
	
	{CAMCMP_REG_WRITE, 0x486A, 0x00000000, NULL,  CAMCMP_D_LEN_WORD},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(afc_result)[] =
{
	
	{CAMCMP_REG_READ, 0x6D77, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(get_saf_mode)[] =
{
	
	{CAMCMP_REG_READ, 0x4887, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(awb_hold)[] =
{
	
	{CAMCMP_REG_WRITE, 0x0102, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(ae_hold)[] =
{
	
	{CAMCMP_REG_WRITE, 0x0103, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(chk_mode_sts)[] =
{
	{CAMCMP_REG_POLL1, 0x00F8, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x00FC, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE}   
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(af_mode_moni)[] =
{
	{CAMCMP_REG_WRITE, 0x002E, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}   
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(moni_reflesh)[] =
{
	{CAMCMP_REG_WRITE, 0x0012, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},  
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(frame_pos)[] =
{
	{CAMCMP_REG_WRITE, 0x4C4C, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4C4E, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4C50, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4C52, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4C80, 0x0000000A, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C7C, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C7D, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C7E, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C7F, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C81, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C82, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C83, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C84, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
	{CAMCMP_REG_WRITE, 0x4C85, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(search_area)[] =
{
	{CAMCMP_REG_WRITE, 0x4876, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4878, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(ae_sub)[] =
{
	{CAMCMP_REG_WRITE, 0x0104, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(photometry)[] =
{
	{CAMCMP_REG_WRITE, 0x4C20, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4C24, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4C22, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
	{CAMCMP_REG_WRITE, 0x4C26, 0x00000000, NULL, CAMCMP_D_LEN_WORD}, 
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(free_weight)[] =
{
	{CAMCMP_REG_WRITE, 0x02E3, 0x00000000, NULL, CAMCMP_D_LEN_BYTE}, 
};








static camcmp_ius006f_reg_val_type CAMCMP_REG(VE295)[] =
{
	{CAMCMP_REG_WRITE, 0x0080, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}   
};








static camcmp_ius006f_reg_val_type CAMCMP_REG(iso_type)[] =
{
	{CAMCMP_REG_WRITE, 0x6A01, 0x000000BD, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A02, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A03, 0x00000005, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A04, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A05, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A31, 0x00000016, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A32, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A33, 0x000000CD, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A34, 0x00000027, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A35, 0x00000018, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A36, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A37, 0x00000030, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A38, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A39, 0x0000001A, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3A, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3B, 0x00000052, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3C, 0x00000005, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3D, 0x0000001C, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3E, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A3F, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A40, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A41, 0x0000001E, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A42, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A43, 0x000000F7, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A44, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A45, 0x00000020, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A46, 0x00000040, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A47, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A48, 0x00000008, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A49, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A4A, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},  
	{CAMCMP_REG_WRITE, 0x6A00, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE}   
};








static camcmp_ius006f_reg_val_type CAMCMP_REG(speedmovie)[] =
{
	
	{CAMCMP_REG_WRITE, 0x02FA, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FB, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FC, 0x00000043, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FD, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x02FE, 0x00000001, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0300, 0x00000002, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0302, 0x00006400, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x0304, 0x00068B00, NULL,  CAMCMP_D_LEN_LWORD},     
	{CAMCMP_REG_WRITE, 0x0009, 0x0000001F, NULL,  CAMCMP_D_LEN_BYTE},      
	
	{CAMCMP_REG_WRITE, 0x000B, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4044, 0x000021C0, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x402B, 0x00000099, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x402C, 0x0000012F, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4050, 0x0000025D, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x405C, 0x00000981, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x405E, 0x000007FE, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4060, 0x000021C0, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4C14, 0x00000440, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x403E, 0x000022E3, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x4040, 0x000021D6, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x02C7, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x444A, 0x00007B9F, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x444C, 0x00007F87, NULL,  CAMCMP_D_LEN_WORD},      
	{CAMCMP_REG_WRITE, 0x3E04, 0x00000004, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E05, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E06, 0x0000000E, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E08, 0x0000000B, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E09, 0x00000005, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E0A, 0x00000007, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E0B, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E0C, 0x00000007, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x3E0D, 0x00000005, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x4424, 0x00000060, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0380, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0382, 0x00000003, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0383, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_WRITE, 0x0385, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}       
};












static camcmp_ius006f_reg_val_type CAMCMP_REG(otp0l)[] =
{
	{CAMCMP_REG_READ, 0x0250, 0x00000000, NULL, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(otp0m)[] =
{
	{CAMCMP_REG_READ, 0x0254, 0x00000000, NULL, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(otp0h)[] =
{
	{CAMCMP_REG_READ, 0x0258, 0x00000000, NULL, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(otp1l)[] =
{
	{CAMCMP_REG_READ, 0x025C, 0x00000000, NULL, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(otp1m)[] =
{
	{CAMCMP_REG_READ, 0x0260, 0x00000000, NULL, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(otp1h)[] =
{
	{CAMCMP_REG_READ, 0x0264, 0x00000000, NULL, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(intsts)[] =
{
	{CAMCMP_REG_READ, 0x00F8, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};





static camcmp_ius006f_reg_val_type CAMCMP_REG(evaluate)[] =
{
	{CAMCMP_REG_READ, 0x6810, 0x00000000, NULL,  CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(lens_pos)[] =
{
	{CAMCMP_REG_READ, 0x6D7A, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(af_step)[] =
{
	{CAMCMP_REG_READ, 0x6D84, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(aescl)[] =
{
	{CAMCMP_REG_READ, 0x027A, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(sht_time_h)[] =
{
	{CAMCMP_REG_READ, 0x00F4, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(sht_time_l)[] =
{
	{CAMCMP_REG_READ, 0x00F2, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(agc_scl)[] =
{
	{CAMCMP_REG_READ, 0x0278, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};






static camcmp_ius006f_reg_val_type CAMCMP_REG(af_result)[] =
{
	{CAMCMP_REG_READ, 0x6D77, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(af_state)[] =
{
	{CAMCMP_REG_READ, 0x6D76, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};






static camcmp_ius006f_reg_val_type CAMCMP_REG(manual_step)[] =
{
	{CAMCMP_REG_READ, 0x486C, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(area_low_type1)[] =
{
	{CAMCMP_REG_READ, 0x4876, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(area_high_type1)[] =
{
	{CAMCMP_REG_READ, 0x4878, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};






static camcmp_ius006f_reg_val_type CAMCMP_REG(jpg_sts)[] =
{
	{CAMCMP_REG_READ, 0x0200, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(jpg_retry)[] =
{
	{CAMCMP_REG_READ, 0x0209, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};









static camcmp_ius006f_reg_val_type CAMCMP_REG(hsize_moni)[] =
{
	{CAMCMP_REG_READ, 0x0022, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};




static camcmp_ius006f_reg_val_type CAMCMP_REG(vsize_moni)[] =
{
	{CAMCMP_REG_READ, 0x0028, 0x00000000, NULL,  CAMCMP_D_LEN_WORD}    
};



static camcmp_ius006f_reg_val_type CAMCMP_REG(ae_sub_sts)[] =
{
	{CAMCMP_REG_READ, 0x0104, 0x00000000, NULL,  CAMCMP_D_LEN_BYTE}    
};















static camcmp_data_type CAMCMP_CMD(chk_dev_sts)[]=
{
	{(void*)CAMCMP_REG(chk_dev_sts), CAMCMP_SIZE_REG(CAMCMP_REG(chk_dev_sts))}
};




static camcmp_data_type CAMCMP_CMD(init_set_1)[]=
{
	{(void*)CAMCMP_REG(init_set_1), CAMCMP_SIZE_REG(CAMCMP_REG(init_set_1))}
};




static camcmp_data_type CAMCMP_CMD(init_set_2)[]=
{
	{(void*)CAMCMP_REG(init_set_2),  CAMCMP_SIZE_REG(CAMCMP_REG(init_set_2))}
};




static camcmp_data_type CAMCMP_CMD(init_set_3)[]=
{
	{(void*)CAMCMP_REG(init_set_3),  CAMCMP_SIZE_REG(CAMCMP_REG(init_set_3))}
};




static camcmp_data_type CAMCMP_CMD(rom_correct)[]=
{
	{(void*)CAMCMP_REG(rom_correct), CAMCMP_SIZE_REG(CAMCMP_REG(rom_correct))}
};




static camcmp_data_type CAMCMP_CMD(init_set_4)[]=
{
	{(void*)CAMCMP_REG(init_set_4), CAMCMP_SIZE_REG(CAMCMP_REG(init_set_4))}
};




static camcmp_data_type CAMCMP_CMD(init_set_5)[]=
{
	{(void*)CAMCMP_REG(init_af_drv), CAMCMP_SIZE_REG(CAMCMP_REG(init_af_drv))},    
	{(void*)CAMCMP_REG(init_set_5),  CAMCMP_SIZE_REG(CAMCMP_REG(init_set_5))}      
};




static camcmp_data_type CAMCMP_CMD(wb_auto)[] =
{
	{(void*)CAMCMP_REG(wb_auto), CAMCMP_SIZE_REG(CAMCMP_REG(wb_auto))}
};




static camcmp_data_type CAMCMP_CMD(wb_inc)[] =
{
	{(void*)CAMCMP_REG(wb_inc), CAMCMP_SIZE_REG(CAMCMP_REG(wb_inc))}
};




static camcmp_data_type CAMCMP_CMD(wb_sunny)[] =
{
	{(void*)CAMCMP_REG(wb_sunny), CAMCMP_SIZE_REG(CAMCMP_REG(wb_sunny))}
};




static camcmp_data_type CAMCMP_CMD(wb_fluor)[] =
{
	{(void*)CAMCMP_REG(wb_fluor), CAMCMP_SIZE_REG(CAMCMP_REG(wb_fluor))}
};




static camcmp_data_type CAMCMP_CMD(wb_cloudy)[] =
{
	{(void*)CAMCMP_REG(wb_cloudy), CAMCMP_SIZE_REG(CAMCMP_REG(wb_cloudy))}
};




static camcmp_data_type CAMCMP_CMD(wb_led)[] =
{
	{(void*)CAMCMP_REG(wb_led), CAMCMP_SIZE_REG(CAMCMP_REG(wb_led))}
};




static camcmp_data_type CAMCMP_CMD(night_off)[] =
{
	{(void*)CAMCMP_REG(night_off), CAMCMP_SIZE_REG(CAMCMP_REG(night_off))}
};




static camcmp_data_type CAMCMP_CMD(night_on)[] =
{
	{(void*)CAMCMP_REG(night_on), CAMCMP_SIZE_REG(CAMCMP_REG(night_on))}
};





static camcmp_data_type CAMCMP_CMD(movie)[] =
{
	{(void*)CAMCMP_REG(movie), CAMCMP_SIZE_REG(CAMCMP_REG(movie))}
};





static camcmp_data_type CAMCMP_CMD(cap_size)[] =
{
	{(void*)CAMCMP_REG(cap_size), CAMCMP_SIZE_REG(CAMCMP_REG(cap_size))}
};




static camcmp_data_type CAMCMP_CMD(moni_size)[] =
{
	{(void*)CAMCMP_REG(moni_size), CAMCMP_SIZE_REG(CAMCMP_REG(moni_size))}
};




static camcmp_data_type CAMCMP_CMD(chg_mode)[] =
{
	{(void*)CAMCMP_REG(chg_mode), CAMCMP_SIZE_REG(CAMCMP_REG(chg_mode))}
};







static camcmp_data_type CAMCMP_CMD(zoom_5m)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_wqhd)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_2m)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_1m)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_vga)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_hd_mv)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_vga_mv)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_qvga_mv)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};




static camcmp_data_type CAMCMP_CMD(zoom_qcif_mv)[] =
{
	{(void*)CAMCMP_REG(zoom), CAMCMP_SIZE_REG(CAMCMP_REG(zoom))}
};
























































static camcmp_data_type CAMCMP_CMD(brightness)[] =
{
	{(void*)CAMCMP_REG(brightness), CAMCMP_SIZE_REG(CAMCMP_REG(brightness))}
};




static camcmp_data_type CAMCMP_CMD(effect)[] =
{
	{(void*)CAMCMP_REG(effect), CAMCMP_SIZE_REG(CAMCMP_REG(effect))}
};




static camcmp_data_type CAMCMP_CMD(quality)[] =
{
	{(void*)CAMCMP_REG(quality), CAMCMP_SIZE_REG(CAMCMP_REG(quality))}
};




static camcmp_data_type CAMCMP_CMD(int_clr)[] =
{
	{(void*)CAMCMP_REG(int_clr), CAMCMP_SIZE_REG(CAMCMP_REG(int_clr))}
};




static camcmp_data_type CAMCMP_CMD(af_cancel)[] =
{
	{(void*)CAMCMP_REG(af_cancel), CAMCMP_SIZE_REG(CAMCMP_REG(af_cancel))}
};




static camcmp_data_type CAMCMP_CMD(af_mode)[] =
{
	{(void*)CAMCMP_REG(af_mode), CAMCMP_SIZE_REG(CAMCMP_REG(af_mode))}
};




static camcmp_data_type CAMCMP_CMD(mf_start)[] =
{
	{(void*)CAMCMP_REG(mf_pos),   CAMCMP_SIZE_REG(CAMCMP_REG(mf_pos))},      
	{(void*)CAMCMP_REG(mf_start), CAMCMP_SIZE_REG(CAMCMP_REG(mf_start))}     
};




static camcmp_data_type CAMCMP_CMD(ae_normal)[] =
{
	{(void*)CAMCMP_REG(ae_normal), CAMCMP_SIZE_REG(CAMCMP_REG(ae_normal))}
};




static camcmp_data_type CAMCMP_CMD(ae_long)[] =
{
	{(void*)CAMCMP_REG(ae_long), CAMCMP_SIZE_REG(CAMCMP_REG(ae_long))}
};




static camcmp_data_type CAMCMP_CMD(ptnchk_off)[] =
{
	{(void*)CAMCMP_REG(ptnchk_off), CAMCMP_SIZE_REG(CAMCMP_REG(ptnchk_off))}
};




static camcmp_data_type CAMCMP_CMD(ptnchk_on)[] =
{
	{(void*)CAMCMP_REG(ptnchk_on), CAMCMP_SIZE_REG(CAMCMP_REG(ptnchk_on))}
};




static camcmp_data_type CAMCMP_CMD(chk_af_lock)[] =
{
	{(void*)CAMCMP_REG(chk_af_lock), CAMCMP_SIZE_REG(CAMCMP_REG(chk_af_lock))}
};




static camcmp_data_type CAMCMP_CMD(thumbnail)[] =
{
	{(void*)CAMCMP_REG(thumbnail), CAMCMP_SIZE_REG(CAMCMP_REG(thumbnail))}
};





static camcmp_data_type CAMCMP_CMD(jpeg_limit)[] =
{
	{(void*)CAMCMP_REG(jpeg_limit), CAMCMP_SIZE_REG(CAMCMP_REG(jpeg_limit))}
};






static camcmp_data_type CAMCMP_CMD(af_restart)[] =
{
	{(void*)CAMCMP_REG(af_restart), CAMCMP_SIZE_REG(CAMCMP_REG(af_restart))}
};





static camcmp_data_type CAMCMP_CMD(otp0l)[] =
{
	{(void*)CAMCMP_REG(otp0l), CAMCMP_SIZE_REG(CAMCMP_REG(otp0l))}
};




static camcmp_data_type CAMCMP_CMD(otp0m)[] =
{
	{(void*)CAMCMP_REG(otp0m), CAMCMP_SIZE_REG(CAMCMP_REG(otp0m))}
};




static camcmp_data_type CAMCMP_CMD(otp0h)[] =
{
	{(void*)CAMCMP_REG(otp0h), CAMCMP_SIZE_REG(CAMCMP_REG(otp0h))}
};




static camcmp_data_type CAMCMP_CMD(otp1l)[] =
{
	{(void*)CAMCMP_REG(otp1l), CAMCMP_SIZE_REG(CAMCMP_REG(otp1l))}
};




static camcmp_data_type CAMCMP_CMD(otp1m)[] =
{
	{(void*)CAMCMP_REG(otp1m), CAMCMP_SIZE_REG(CAMCMP_REG(otp1m))}
};




static camcmp_data_type CAMCMP_CMD(otp1h)[] =
{
	{(void*)CAMCMP_REG(otp1h), CAMCMP_SIZE_REG(CAMCMP_REG(otp1h))}
};




static camcmp_data_type CAMCMP_CMD(otp)[] =
{
	{(void*)CAMCMP_REG(otp0l), CAMCMP_SIZE_REG(CAMCMP_REG(otp0l))},     
	{(void*)CAMCMP_REG(otp0m), CAMCMP_SIZE_REG(CAMCMP_REG(otp0m))},     
	{(void*)CAMCMP_REG(otp0h), CAMCMP_SIZE_REG(CAMCMP_REG(otp0h))},     
	{(void*)CAMCMP_REG(otp1l), CAMCMP_SIZE_REG(CAMCMP_REG(otp1l))},     
	{(void*)CAMCMP_REG(otp1m), CAMCMP_SIZE_REG(CAMCMP_REG(otp1m))},     
	{(void*)CAMCMP_REG(otp1h), CAMCMP_SIZE_REG(CAMCMP_REG(otp1h))}      
};




static camcmp_data_type CAMCMP_CMD(intsts)[] =
{
	{(void*)CAMCMP_REG(intsts), CAMCMP_SIZE_REG(CAMCMP_REG(intsts))}
};






static camcmp_data_type CAMCMP_CMD(evaluate)[] =
{
	{(void*)CAMCMP_REG(evaluate), CAMCMP_SIZE_REG(CAMCMP_REG(evaluate))}
};




static camcmp_data_type CAMCMP_CMD(lens_pos)[] =
{
	{(void*)CAMCMP_REG(lens_pos), CAMCMP_SIZE_REG(CAMCMP_REG(lens_pos))}
};




static camcmp_data_type CAMCMP_CMD(af_step)[] =
{
	{(void*)CAMCMP_REG(af_step), CAMCMP_SIZE_REG(CAMCMP_REG(af_step))}
};





static camcmp_data_type CAMCMP_CMD(aescl)[] =
{
	{(void*)CAMCMP_REG(aescl), CAMCMP_SIZE_REG(CAMCMP_REG(aescl))}
};




static camcmp_data_type CAMCMP_CMD(sht_time_h)[] =
{
	{(void*)CAMCMP_REG(sht_time_h), CAMCMP_SIZE_REG(CAMCMP_REG(sht_time_h))}
};




static camcmp_data_type CAMCMP_CMD(sht_time_l)[] =
{
	{(void*)CAMCMP_REG(sht_time_l), CAMCMP_SIZE_REG(CAMCMP_REG(sht_time_l))}
};




static camcmp_data_type CAMCMP_CMD(agc_scl)[] =
{
	{(void*)CAMCMP_REG(agc_scl), CAMCMP_SIZE_REG(CAMCMP_REG(agc_scl))}
};






static camcmp_data_type CAMCMP_CMD(af_result)[] =
{
	{(void*)CAMCMP_REG(af_result), CAMCMP_SIZE_REG(CAMCMP_REG(af_result))}
};




static camcmp_data_type CAMCMP_CMD(af_state)[] =
{
	{(void*)CAMCMP_REG(af_state), CAMCMP_SIZE_REG(CAMCMP_REG(af_state))}
};






static camcmp_data_type CAMCMP_CMD(manual_step)[] =
{
	{(void*)CAMCMP_REG(manual_step), CAMCMP_SIZE_REG(CAMCMP_REG(manual_step))}
};




static camcmp_data_type CAMCMP_CMD(area_low_type1)[] =
{
	{(void*)CAMCMP_REG(area_low_type1), CAMCMP_SIZE_REG(CAMCMP_REG(area_low_type1))}
};




static camcmp_data_type CAMCMP_CMD(area_high_type1)[] =
{
	{(void*)CAMCMP_REG(area_high_type1), CAMCMP_SIZE_REG(CAMCMP_REG(area_high_type1))}
};








static camcmp_data_type CAMCMP_CMD(cap_half_ae_ctrl)[] =
{
	{(void*)CAMCMP_REG(cap_half_ae_ctrl), CAMCMP_SIZE_REG(CAMCMP_REG(cap_half_ae_ctrl))}
};





static camcmp_data_type CAMCMP_CMD(set_shut)[] =
{
	{(void*)CAMCMP_REG(set_shut), CAMCMP_SIZE_REG(CAMCMP_REG(set_shut))}
};





static camcmp_data_type CAMCMP_CMD(set_gain)[] =
{
	{(void*)CAMCMP_REG(set_gain), CAMCMP_SIZE_REG(CAMCMP_REG(set_gain))}
};




static camcmp_data_type CAMCMP_CMD(cap_gainoffset)[] =
{
	{(void*)CAMCMP_REG(cap_gainoffset), CAMCMP_SIZE_REG(CAMCMP_REG(cap_gainoffset))}
};




static camcmp_data_type CAMCMP_CMD(set_capture_num)[] =
{
	{(void*)CAMCMP_REG(set_capture_num), CAMCMP_SIZE_REG(CAMCMP_REG(set_capture_num))}
};




static camcmp_data_type CAMCMP_CMD(set_ae_stop)[] =
{
	{(void*)CAMCMP_REG(set_ae_stop), CAMCMP_SIZE_REG(CAMCMP_REG(set_ae_stop))}
};






static camcmp_data_type CAMCMP_CMD(scene_change)[] =
{
	{(void*)CAMCMP_REG(scene_change), CAMCMP_SIZE_REG(CAMCMP_REG(scene_change))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_auto)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_portrait)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_portrait_illumi)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_landscape)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_backlight)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_night)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_pet)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_cooking)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_sports)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_off)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};




static camcmp_data_type CAMCMP_CMD(scene_angle_high_sensitivity)[] =
{
	{(void*)CAMCMP_REG(scene_angle), CAMCMP_SIZE_REG(CAMCMP_REG(scene_angle))}
};







static camcmp_data_type CAMCMP_CMD(camera_mode)[] =
{
	{(void*)CAMCMP_REG(camera_mode), CAMCMP_SIZE_REG(CAMCMP_REG(camera_mode))}
};









static camcmp_data_type CAMCMP_CMD(jpeg_intsts)[] =
{
	{(void*)CAMCMP_REG(jpeg_intsts), CAMCMP_SIZE_REG(CAMCMP_REG(jpeg_intsts))}
};



static camcmp_data_type CAMCMP_CMD(jpg_sts)[] =
{
	{(void*)CAMCMP_REG(jpg_sts), CAMCMP_SIZE_REG(CAMCMP_REG(jpg_sts))}
};




static camcmp_data_type CAMCMP_CMD(jpg_retry)[] =
{
	{(void*)CAMCMP_REG(jpg_retry), CAMCMP_SIZE_REG(CAMCMP_REG(jpg_retry))}
};







static camcmp_data_type CAMCMP_CMD(flc_mode)[] =
{
	{(void*)CAMCMP_REG(flc_mode), CAMCMP_SIZE_REG(CAMCMP_REG(flc_mode))}
};






static camcmp_data_type CAMCMP_CMD(afc_status)[] =
{
	{(void*)CAMCMP_REG(afc_status), CAMCMP_SIZE_REG(CAMCMP_REG(afc_status))}
};



static camcmp_data_type CAMCMP_CMD(set_saf_mode)[] =
{
	{(void*)CAMCMP_REG(set_saf_mode), CAMCMP_SIZE_REG(CAMCMP_REG(set_saf_mode))}
};



static camcmp_data_type CAMCMP_CMD(dac_code)[] =
{
	{(void*)CAMCMP_REG(dac_code), CAMCMP_SIZE_REG(CAMCMP_REG(dac_code))}
};



static camcmp_data_type CAMCMP_CMD(afc_result)[] =
{
	{(void*)CAMCMP_REG(afc_result), CAMCMP_SIZE_REG(CAMCMP_REG(afc_result))}
};



static camcmp_data_type CAMCMP_CMD(get_saf_mode)[] =
{
	{(void*)CAMCMP_REG(get_saf_mode), CAMCMP_SIZE_REG(CAMCMP_REG(get_saf_mode))}
};



static camcmp_data_type CAMCMP_CMD(awb_hold)[] =
{
	{(void*)CAMCMP_REG(awb_hold), CAMCMP_SIZE_REG(CAMCMP_REG(awb_hold))}
};



static camcmp_data_type CAMCMP_CMD(ae_hold)[] =
{
	{(void*)CAMCMP_REG(ae_hold), CAMCMP_SIZE_REG(CAMCMP_REG(ae_hold))}
};



static camcmp_data_type CAMCMP_CMD(chk_mode_sts)[] =
{
	{(void*)CAMCMP_REG(chk_mode_sts), CAMCMP_SIZE_REG(CAMCMP_REG(chk_mode_sts))}
};



static camcmp_data_type CAMCMP_CMD(moni_reflesh)[] =
{
	{(void*)CAMCMP_REG(moni_reflesh), CAMCMP_SIZE_REG(CAMCMP_REG(moni_reflesh))}
};



static camcmp_data_type CAMCMP_CMD(hsize_moni)[] =
{
	{(void*)CAMCMP_REG(hsize_moni), CAMCMP_SIZE_REG(CAMCMP_REG(hsize_moni))}
};




static camcmp_data_type CAMCMP_CMD(vsize_moni)[] =
{
	{(void*)CAMCMP_REG(vsize_moni), CAMCMP_SIZE_REG(CAMCMP_REG(vsize_moni))}
};




static camcmp_data_type CAMCMP_CMD(af_mode_moni)[] =
{
	{(void*)CAMCMP_REG(af_mode_moni), CAMCMP_SIZE_REG(CAMCMP_REG(af_mode_moni))}
};




static camcmp_data_type CAMCMP_CMD(frame_pos)[] =
{
	{(void*)CAMCMP_REG(frame_pos), CAMCMP_SIZE_REG(CAMCMP_REG(frame_pos))}
};



static camcmp_data_type CAMCMP_CMD(search_area)[] =
{
	{(void*)CAMCMP_REG(search_area), CAMCMP_SIZE_REG(CAMCMP_REG(search_area))}
};



static camcmp_data_type CAMCMP_CMD(ae_sub_sts)[] =
{
	{(void*)CAMCMP_REG(ae_sub_sts), CAMCMP_SIZE_REG(CAMCMP_REG(ae_sub_sts))}
};




static camcmp_data_type CAMCMP_CMD(ae_sub)[] =
{
	{(void*)CAMCMP_REG(ae_sub), CAMCMP_SIZE_REG(CAMCMP_REG(ae_sub))}
};




static camcmp_data_type CAMCMP_CMD(photometry)[] =
{
	{(void*)CAMCMP_REG(photometry), CAMCMP_SIZE_REG(CAMCMP_REG(photometry))}
};




static camcmp_data_type CAMCMP_CMD(free_weight)[] =
{
	{(void*)CAMCMP_REG(free_weight), CAMCMP_SIZE_REG(CAMCMP_REG(free_weight))}
};







static camcmp_data_type CAMCMP_CMD(VE295)[] =
{
	{(void*)CAMCMP_REG(VE295), CAMCMP_SIZE_REG(CAMCMP_REG(VE295))}
};








static camcmp_data_type CAMCMP_CMD(iso_type)[] =
{
	{(void*)CAMCMP_REG(iso_type), CAMCMP_SIZE_REG(CAMCMP_REG(iso_type))}
};








static camcmp_data_type CAMCMP_CMD(speedmovie)[] =
{
	{(void*)CAMCMP_REG(speedmovie), CAMCMP_SIZE_REG(CAMCMP_REG(speedmovie))}
};




















static camcmp_ius006f_blank_val_type CAMCMP_BLK(cap_size_5m)[] =
{
	{(void*)&(CAMCMP_REG(cap_size)[0].lwdata), 0x00000A00, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(cap_size)[1].lwdata), 0x00000780, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(cap_size_wqhd)[] =
{
	{(void*)&(CAMCMP_REG(cap_size)[0].lwdata), 0x00000A00, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(cap_size)[1].lwdata), 0x000005A0, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(cap_size_2m)[] =
{
	{(void*)&(CAMCMP_REG(cap_size)[0].lwdata), 0x00000640, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(cap_size)[1].lwdata), 0x000004B0, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(cap_size_1m)[] =
{
	{(void*)&(CAMCMP_REG(cap_size)[0].lwdata), 0x00000500, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(cap_size)[1].lwdata), 0x000003C0, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(cap_size_vga)[] =
{
	{(void*)&(CAMCMP_REG(cap_size)[0].lwdata), 0x00000280, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(cap_size)[1].lwdata), 0x000001E0, CAMCMP_D_LEN_LWORD}     
};












































static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_hd)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000500, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x000002D0, CAMCMP_D_LEN_LWORD}    
};

static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_1m)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000500, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x000003C0, CAMCMP_D_LEN_LWORD}    
};

static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_VE301)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000360, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x000001E0, CAMCMP_D_LEN_LWORD}    
};

static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_hd_half)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000300, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x000001B0, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_vga)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000280, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x000001E0, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_qvga)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000140, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x000000F0, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_qcif)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x000000B0, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x00000090, CAMCMP_D_LEN_LWORD}    
};



























static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_hd_shake)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000580, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x00000320, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_vga_shake)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000300, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x00000240, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_qvga_shake)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000180, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x00000120, CAMCMP_D_LEN_LWORD}    
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_qcif_shake)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000160, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x00000120, CAMCMP_D_LEN_LWORD}    
};






static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_size_864x480)[] =
{
	{(void*)&(CAMCMP_REG(moni_size)[0].lwdata), 0x00000360, CAMCMP_D_LEN_LWORD},   
	{(void*)&(CAMCMP_REG(moni_size)[1].lwdata), 0x000001E0, CAMCMP_D_LEN_LWORD}    
};



































static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_mode)[] =
{
	{(void*)&(CAMCMP_REG(chg_mode)[0].waddr),  0x00000011,  CAMCMP_D_LEN_WORD},    
	{(void*)&(CAMCMP_REG(chg_mode)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(moni_ref)[] =
{
	{(void*)&(CAMCMP_REG(chg_mode)[0].waddr),  0x00000012,  CAMCMP_D_LEN_WORD},    
	{(void*)&(CAMCMP_REG(chg_mode)[0].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(half_mode)[] =
{
	{(void*)&(CAMCMP_REG(chg_mode)[0].waddr),  0x00000011,  CAMCMP_D_LEN_WORD},    
	{(void*)&(CAMCMP_REG(chg_mode)[0].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(cap_mode)[] =
{
	{(void*)&(CAMCMP_REG(chg_mode)[0].waddr),  0x00000011,  CAMCMP_D_LEN_WORD},    
	{(void*)&(CAMCMP_REG(chg_mode)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD}     
};








static camcmp_ius006f_blank_val_type CAMCMP_BLK(movie_mode)[] =
{
	{(void*)&(CAMCMP_REG(chg_mode)[0].waddr),  0x00000011,  CAMCMP_D_LEN_WORD},    
	{(void*)&(CAMCMP_REG(chg_mode)[0].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD}     
};











static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_5m)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD}         
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_wqhd)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD}         
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_2m)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000105, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000010A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000110, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000011A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000124, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000131, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000013B, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000148, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000152, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000015F, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000016C, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000176, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000183, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000190, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000019C, CAMCMP_D_LEN_LWORD}         
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_1m)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD},        
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_vga)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000011F, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000140, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000164, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000018A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001B9, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001E7, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000021A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000250, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000288, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000002C3, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000002FE, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000033E, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000380, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000003C3, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000040A, CAMCMP_D_LEN_LWORD}         
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_hd_mv)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD},        
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_vga_mv)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000010A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000115, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000011F, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000131, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000140, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000152, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000164, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000176, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000018A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000019D, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001B1, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001C5, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001DA, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001EE, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000205, CAMCMP_D_LEN_LWORD}         
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_qvga_mv)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000011F, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000140, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000164, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000018A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001B9, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001E7, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000021A, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000250, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000288, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000002C3, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000002FE, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000033E, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000380, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000003C3, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000040A, CAMCMP_D_LEN_LWORD}         
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(zoom_qcif_mv)[] =
{
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000100, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000136, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000170, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001B1, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000001F6, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000240, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000290, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000002EC, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000350, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000003B8, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000429, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000049F, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000051C, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x0000059F, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x00000626, CAMCMP_D_LEN_LWORD},        
	{(void*)&(CAMCMP_REG(zoom)[0].lwdata), 0x000006B5, CAMCMP_D_LEN_LWORD}         
};





















































































static camcmp_ius006f_blank_val_type CAMCMP_BLK(brightness)[] =
{
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x000000FB, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x000000FC, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x000000FD, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x000000FE, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x000000FF, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(brightness)[0].lwdata), 0x00000005, CAMCMP_D_LEN_LWORD}   
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(effect)[] =
{
	{(void*)&(CAMCMP_REG(effect)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(effect)[0].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(effect)[0].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(effect)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD}       
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(quality)[] =
{
	{(void*)&(CAMCMP_REG(quality)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(quality)[0].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(quality)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD}      
};







static camcmp_ius006f_blank_val_type CAMCMP_BLK(flc_mode)[] =
{
	{(void*)&(CAMCMP_REG(flc_mode)[0].lwdata), 0x00000005, CAMCMP_D_LEN_BYTE},        
	{(void*)&(CAMCMP_REG(flc_mode)[0].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE},        
	{(void*)&(CAMCMP_REG(flc_mode)[0].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},        
	{(void*)&(CAMCMP_REG(flc_mode)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}         
};







static camcmp_ius006f_blank_val_type CAMCMP_BLK(int_clr)[] =
{
	{(void*)&(CAMCMP_REG(int_clr)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(int_clr)[0].lwdata), 0x00000010, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(int_clr)[0].lwdata), 0x00000012, CAMCMP_D_LEN_LWORD}      
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(af_mode)[] =
{
	{(void*)&(CAMCMP_REG(af_mode)[0].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(af_mode)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(af_mode)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD}      
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(mf_pos)[] =
{
	{(void*)&(CAMCMP_REG(mf_pos)[0].lwdata), 0x00000101, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(mf_pos)[0].lwdata), 0x00000227, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(mf_pos)[0].lwdata), 0x000000AF, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(mf_pos)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(mf_pos)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD}       
};





static camcmp_ius006f_blank_val_type CAMCMP_BLK(jpeg_limit_5m)[] =
{
	{(void*)&(CAMCMP_REG(jpeg_limit)[0].lwdata), 0x000003A7, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[1].lwdata), 0x0000078F, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[2].lwdata), 0x00000B77, CAMCMP_D_LEN_LWORD}      
};





static camcmp_ius006f_blank_val_type CAMCMP_BLK(jpeg_limit_3m)[] =
{
	{(void*)&(CAMCMP_REG(jpeg_limit)[0].lwdata), 0x00000249, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[1].lwdata), 0x000004D3, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[2].lwdata), 0x0000075D, CAMCMP_D_LEN_LWORD}      
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(jpeg_limit_2m)[] =
{
	{(void*)&(CAMCMP_REG(jpeg_limit)[0].lwdata), 0x00000163, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[1].lwdata), 0x00000307, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[2].lwdata), 0x000004AB, CAMCMP_D_LEN_LWORD}      
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(jpeg_limit_1m)[] =
{
	{(void*)&(CAMCMP_REG(jpeg_limit)[0].lwdata), 0x000000D7, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[1].lwdata), 0x000001EF, CAMCMP_D_LEN_LWORD},     
	{(void*)&(CAMCMP_REG(jpeg_limit)[2].lwdata), 0x00000307, CAMCMP_D_LEN_LWORD}      
};








static camcmp_ius006f_blank_val_type CAMCMP_BLK(set_shut)[] =
{
	
	{(void*)&(CAMCMP_REG(set_shut)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD}       
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(set_gain)[] =
{
	{(void*)&(CAMCMP_REG(set_gain)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD}       
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(set_capture_num)[] =
{
	{(void*)&(CAMCMP_REG(set_capture_num)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},       
	{(void*)&(CAMCMP_REG(set_capture_num)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD}        
};








static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_auto)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_portrait)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_portrait_illumi)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_landscape)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_backlight)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_night)[] =
{
	

	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000007, CAMCMP_D_LEN_BYTE},     



	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000007, CAMCMP_D_LEN_BYTE},     



	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000006, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_pet)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000089, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x000000EC, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_cooking)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_sports)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000089, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x000000EC, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_off)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_high_sensitivity)[] =
{
	

	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000007, CAMCMP_D_LEN_BYTE},     



	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000007, CAMCMP_D_LEN_BYTE},     



	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000006, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_auto_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_portrait_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_portrait_illumi_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_landscape_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_backlight_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_night_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000006, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_pet_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000089, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x000000EC, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_cooking_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_sports_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000089, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x000000EC, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_off_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_high_sensitivity_fixation)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_change)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[1].lwdata),  0x000000BD, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[2].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[3].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[4].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[5].lwdata),  0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[6].lwdata),  0x00000016, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[7].lwdata),  0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[8].lwdata),  0x0000003B, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[9].lwdata),  0x0000002C, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[10].lwdata), 0x00000018, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[11].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[12].lwdata), 0x00000030, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[13].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[14].lwdata), 0x0000001A, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[15].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     

	{(void*)&(CAMCMP_REG(scene_change)[16].lwdata), 0x00000076, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[17].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     




	{(void*)&(CAMCMP_REG(scene_change)[18].lwdata), 0x0000001C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[19].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[20].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[21].lwdata), 0x00000004, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[22].lwdata), 0x0000001E, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[23].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[24].lwdata), 0x0000005C, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[25].lwdata), 0x00000006, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[26].lwdata), 0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[27].lwdata), 0x00000040, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[28].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[29].lwdata), 0x00000008, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[30].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[31].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(scene_change)[32].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE}      
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_auto)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000B, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000F, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000007, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_portrait)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000B, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000F, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000007, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_portrait_illumi)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000B, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000F, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000007, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_landscape)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_backlight)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_night)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_pet)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_cooking)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000B, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000F, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000007, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_sports)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_off)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000B, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x0000000F, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000007, CAMCMP_D_LEN_BYTE}       
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(scene_angle_high_sensitivity)[] =
{
	
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},      
	{(void*)&(CAMCMP_REG(scene_angle)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}       
};







static camcmp_ius006f_blank_val_type CAMCMP_BLK(camera_mode)[] =
{
	
	{(void*)&(CAMCMP_REG(camera_mode)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},      
};






static camcmp_ius006f_blank_val_type CAMCMP_BLK(awb_hold)[] =
{
	{(void*)&(CAMCMP_REG(awb_hold)[0].lwdata),  0x00000020, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(awb_hold)[0].lwdata),  0x00000028, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(awb_hold)[0].lwdata),  0x00000027, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(awb_hold)[0].lwdata),  0x00000024, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(awb_hold)[0].lwdata),  0x00000026, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(awb_hold)[0].lwdata),  0x00000002, CAMCMP_D_LEN_BYTE},     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(ae_hold)[] =
{
	{(void*)&(CAMCMP_REG(ae_hold)[0].lwdata),  0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(ae_hold)[0].lwdata),  0x00000001, CAMCMP_D_LEN_BYTE},     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(set_saf_mode)[] =
{
	
	{(void*)&(CAMCMP_REG(set_saf_mode)[0].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(set_saf_mode)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},      
	{(void*)&(CAMCMP_REG(set_saf_mode)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD},      
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(dac_code)[] =
{
	
	{(void*)&(CAMCMP_REG(dac_code)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(af_mode_moni)[] =
{
	{(void*)&(CAMCMP_REG(af_mode_moni)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(af_mode_moni)[0].lwdata), 0x00000001, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(af_mode_moni)[0].lwdata), 0x00000002, CAMCMP_D_LEN_BYTE},     
	{(void*)&(CAMCMP_REG(af_mode_moni)[0].lwdata), 0x00000003, CAMCMP_D_LEN_BYTE}      
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(frame_pos)[] =
{
	{(void*)&(CAMCMP_REG(frame_pos)[0].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
	{(void*)&(CAMCMP_REG(frame_pos)[1].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
	{(void*)&(CAMCMP_REG(frame_pos)[2].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
	{(void*)&(CAMCMP_REG(frame_pos)[3].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(search_area)[] =
{
	{(void*)&(CAMCMP_REG(search_area)[0].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
	{(void*)&(CAMCMP_REG(search_area)[1].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
};



static camcmp_ius006f_blank_val_type CAMCMP_BLK(ae_sub)[] =
{
	{(void*)&(CAMCMP_REG(ae_sub)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE}       
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(photometry)[] =
{
	{(void*)&(CAMCMP_REG(photometry)[0].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
	{(void*)&(CAMCMP_REG(photometry)[1].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
	{(void*)&(CAMCMP_REG(photometry)[2].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
	{(void*)&(CAMCMP_REG(photometry)[3].lwdata), 0x00000000, CAMCMP_D_LEN_WORD}, 
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(free_weight)[] =
{
	{(void*)&(CAMCMP_REG(free_weight)[0].lwdata), 0x00000000, CAMCMP_D_LEN_BYTE},  
};







static camcmp_ius006f_blank_val_type CAMCMP_BLK(VE295)[] =
{
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x000000FA, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x000000FB, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x000000FC, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x000000FD, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x000000FE, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x000000FF, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x00000002, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x00000005, CAMCMP_D_LEN_LWORD},  
	{(void*)&(CAMCMP_REG(VE295)[0].lwdata), 0x00000006, CAMCMP_D_LEN_LWORD}   
};








static camcmp_ius006f_blank_val_type CAMCMP_BLK(iso_type_1600)[] =
{
	{(void*)&(CAMCMP_REG(iso_type)[0].lwdata),  0x000000BD, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[1].lwdata),  0x00000001, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[2].lwdata),  0x00000005, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[3].lwdata),  0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[4].lwdata),  0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[5].lwdata),  0x00000016, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[6].lwdata),  0x00000040, CAMCMP_D_LEN_LWORD},    

	{(void*)&(CAMCMP_REG(iso_type)[7].lwdata),  0x0000003B, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[8].lwdata),  0x00000028, CAMCMP_D_LEN_LWORD},    




	{(void*)&(CAMCMP_REG(iso_type)[9].lwdata),  0x00000018, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[10].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[11].lwdata), 0x00000030, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[12].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[13].lwdata), 0x0000001A, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[14].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    

	{(void*)&(CAMCMP_REG(iso_type)[15].lwdata), 0x00000076, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[16].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},    




	{(void*)&(CAMCMP_REG(iso_type)[17].lwdata), 0x0000001C, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[18].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[19].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[20].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[21].lwdata), 0x0000001E, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[22].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[23].lwdata), 0x000000F7, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[24].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[25].lwdata), 0x00000020, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[26].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[27].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[28].lwdata), 0x00000008, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[29].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[30].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[31].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(iso_type_3200)[] =
{
	{(void*)&(CAMCMP_REG(iso_type)[0].lwdata),  0x000000BD, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[1].lwdata),  0x00000001, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[2].lwdata),  0x00000005, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[3].lwdata),  0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[4].lwdata),  0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[5].lwdata),  0x00000016, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[6].lwdata),  0x00000040, CAMCMP_D_LEN_LWORD},    

	{(void*)&(CAMCMP_REG(iso_type)[7].lwdata),  0x0000003B, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[8].lwdata),  0x00000028, CAMCMP_D_LEN_LWORD},    




	{(void*)&(CAMCMP_REG(iso_type)[9].lwdata),  0x00000018, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[10].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[11].lwdata), 0x00000030, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[12].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[13].lwdata), 0x0000001A, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[14].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    

	{(void*)&(CAMCMP_REG(iso_type)[15].lwdata), 0x00000076, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[16].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},    




	{(void*)&(CAMCMP_REG(iso_type)[17].lwdata), 0x0000001C, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[18].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[19].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[20].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[21].lwdata), 0x0000001E, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[22].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[23].lwdata), 0x000000F7, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[24].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[25].lwdata), 0x00000020, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[26].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[27].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[28].lwdata), 0x0000000C, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[29].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[30].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[31].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD}     
};




static camcmp_ius006f_blank_val_type CAMCMP_BLK(iso_type_12800)[] =
{
	{(void*)&(CAMCMP_REG(iso_type)[0].lwdata),  0x000000BD, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[1].lwdata),  0x00000001, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[2].lwdata),  0x00000005, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[3].lwdata),  0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[4].lwdata),  0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[5].lwdata),  0x00000016, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[6].lwdata),  0x00000040, CAMCMP_D_LEN_LWORD},    

	{(void*)&(CAMCMP_REG(iso_type)[7].lwdata),  0x0000003B, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[8].lwdata),  0x00000028, CAMCMP_D_LEN_LWORD},    




	{(void*)&(CAMCMP_REG(iso_type)[9].lwdata),  0x00000018, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[10].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[11].lwdata), 0x00000030, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[12].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[13].lwdata), 0x0000001A, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[14].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    

	{(void*)&(CAMCMP_REG(iso_type)[15].lwdata), 0x00000076, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[16].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},    




	{(void*)&(CAMCMP_REG(iso_type)[17].lwdata), 0x0000001C, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[18].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[19].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[20].lwdata), 0x00000004, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[21].lwdata), 0x0000001E, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[22].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[23].lwdata), 0x000000F7, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[24].lwdata), 0x00000003, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[25].lwdata), 0x00000020, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[26].lwdata), 0x00000040, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[27].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[28].lwdata), 0x00000014, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[29].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[30].lwdata), 0x00000000, CAMCMP_D_LEN_LWORD},    
	{(void*)&(CAMCMP_REG(iso_type)[31].lwdata), 0x00000001, CAMCMP_D_LEN_LWORD}     
};












static camcmp_data_type CAMCMP_BTBL(cap_size)[] =
{


	{(void*)CAMCMP_BLK(cap_size_5m), CAMCMP_SIZE_BLK(CAMCMP_BLK(cap_size_5m))},     
	{(void*)CAMCMP_BLK(cap_size_wqhd), CAMCMP_SIZE_BLK(CAMCMP_BLK(cap_size_wqhd))}, 
	{(void*)CAMCMP_BLK(cap_size_2m), CAMCMP_SIZE_BLK(CAMCMP_BLK(cap_size_2m))},     
	{(void*)CAMCMP_BLK(cap_size_1m), CAMCMP_SIZE_BLK(CAMCMP_BLK(cap_size_1m))},     
	{(void*)CAMCMP_BLK(cap_size_vga), CAMCMP_SIZE_BLK(CAMCMP_BLK(cap_size_vga))}    







};




static camcmp_data_type CAMCMP_BTBL(moni_size)[] =
{


	{(void*)CAMCMP_BLK(moni_size_hd),   CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_hd))},    
	{(void*)CAMCMP_BLK(moni_size_1m),   CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_1m))},    
	{(void*)CAMCMP_BLK(moni_size_VE301),CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_VE301))}, 
	{(void*)CAMCMP_BLK(moni_size_hd_half),CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_hd_half))}, 
	{(void*)CAMCMP_BLK(moni_size_vga),  CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_vga))},   
	{(void*)CAMCMP_BLK(moni_size_qvga), CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_qvga))},  
    {(void*)CAMCMP_BLK(moni_size_qcif), CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_qcif))},  










                    {(void*)CAMCMP_BLK(moni_size_864x480), CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_864x480))},  

	        {(void*)CAMCMP_BLK(moni_size_hd_shake),   CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_hd_shake))  }, 
	        {(void*)CAMCMP_BLK(moni_size_vga_shake),  CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_vga_shake)) }, 
	        {(void*)CAMCMP_BLK(moni_size_qvga_shake), CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_qvga_shake))}, 
	        {(void*)CAMCMP_BLK(moni_size_qcif_shake), CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_size_qcif_shake))}  








};




static camcmp_data_type CAMCMP_BTBL(chg_mode)[] =
{
	{(void*)CAMCMP_BLK(moni_mode), CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_mode))},        
	{(void*)CAMCMP_BLK(moni_ref),  CAMCMP_SIZE_BLK(CAMCMP_BLK(moni_ref))},         
	{(void*)CAMCMP_BLK(half_mode), CAMCMP_SIZE_BLK(CAMCMP_BLK(half_mode))},        
	{(void*)CAMCMP_BLK(cap_mode),  CAMCMP_SIZE_BLK(CAMCMP_BLK(cap_mode))},          




	{(void*)CAMCMP_BLK(movie_mode),  CAMCMP_SIZE_BLK(CAMCMP_BLK(movie_mode))}      




};







static camcmp_data_type CAMCMP_BTBL(zoom_5m)[] =
{
	{(void*)&CAMCMP_BLK(zoom_5m)[0], CAMCAMP_BLK_SIZE_DEF}                         
};




static camcmp_data_type CAMCMP_BTBL(zoom_wqhd)[] =
{
	{(void*)&CAMCMP_BLK(zoom_wqhd)[0], CAMCAMP_BLK_SIZE_DEF}                       
};




static camcmp_data_type CAMCMP_BTBL(zoom_2m)[] =
{
	{(void*)&CAMCMP_BLK(zoom_2m)[0], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[1], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[2], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[3], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[4], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[5], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[6], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[7], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[8], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[9], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(zoom_2m)[10], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_2m)[11], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_2m)[12], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_2m)[13], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_2m)[14], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_2m)[15], CAMCAMP_BLK_SIZE_DEF}                        
};




static camcmp_data_type CAMCMP_BTBL(zoom_1m)[] =
{
	{(void*)&CAMCMP_BLK(zoom_1m)[0], CAMCAMP_BLK_SIZE_DEF}                         
};




static camcmp_data_type CAMCMP_BTBL(zoom_vga)[] =
{
	{(void*)&CAMCMP_BLK(zoom_vga)[0], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[1], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[2], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[3], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[4], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[5], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[6], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[7], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[8], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[9], CAMCAMP_BLK_SIZE_DEF},                       
	{(void*)&CAMCMP_BLK(zoom_vga)[10], CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(zoom_vga)[11], CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(zoom_vga)[12], CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(zoom_vga)[13], CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(zoom_vga)[14], CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(zoom_vga)[15], CAMCAMP_BLK_SIZE_DEF}                       
};




static camcmp_data_type CAMCMP_BTBL(zoom_hd_mv)[] =
{
	{(void*)&CAMCMP_BLK(zoom_hd_mv)[0], CAMCAMP_BLK_SIZE_DEF}                      
};




static camcmp_data_type CAMCMP_BTBL(zoom_vga_mv)[] =
{
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[0], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[1], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[2], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[3], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[4], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[5], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[6], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[7], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[8], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[9], CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[10], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[11], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[12], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[13], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[14], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_vga_mv)[15], CAMCAMP_BLK_SIZE_DEF}                    
};




static camcmp_data_type CAMCMP_BTBL(zoom_qvga_mv)[] =
{
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[0], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[1], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[2], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[3], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[4], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[5], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[6], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[7], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[8], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[9], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[10], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[11], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[12], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[13], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[14], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qvga_mv)[15], CAMCAMP_BLK_SIZE_DEF}                   
};




static camcmp_data_type CAMCMP_BTBL(zoom_qcif_mv)[] =
{
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[0], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[1], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[2], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[3], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[4], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[5], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[6], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[7], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[8], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[9], CAMCAMP_BLK_SIZE_DEF},                   
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[10], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[11], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[12], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[13], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[14], CAMCAMP_BLK_SIZE_DEF},                  
	{(void*)&CAMCMP_BLK(zoom_qcif_mv)[15], CAMCAMP_BLK_SIZE_DEF}                   
};







































































































static camcmp_data_type CAMCMP_BTBL(brightness)[] =
{
	{(void*)&CAMCMP_BLK(brightness)[0],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[1],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[2],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[3],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[4],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[5],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[6],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[7],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[8],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[9],  CAMCAMP_BLK_SIZE_DEF},                    
	{(void*)&CAMCMP_BLK(brightness)[10], CAMCAMP_BLK_SIZE_DEF}                     
};




static camcmp_data_type CAMCMP_BTBL(effect)[] =
{
	{(void*)&CAMCMP_BLK(effect)[0], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(effect)[1], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(effect)[2], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(effect)[3], CAMCAMP_BLK_SIZE_DEF}                          
};




static camcmp_data_type CAMCMP_BTBL(quality)[] =
{
	{(void*)&CAMCMP_BLK(quality)[0], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(quality)[1], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(quality)[2], CAMCAMP_BLK_SIZE_DEF}                         
};







static camcmp_data_type CAMCMP_BTBL(flc_mode)[] =
{
	{(void*)&CAMCMP_BLK(flc_mode)[0], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(flc_mode)[1], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(flc_mode)[2], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(flc_mode)[3], CAMCAMP_BLK_SIZE_DEF}                         
};







static camcmp_data_type CAMCMP_BTBL(int_clr)[] =
{
	{(void*)&CAMCMP_BLK(int_clr)[0], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(int_clr)[1], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(int_clr)[2], CAMCAMP_BLK_SIZE_DEF}                         
};




static camcmp_data_type CAMCMP_BTBL(af_mode)[] =
{
	{(void*)&CAMCMP_BLK(af_mode)[0], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(af_mode)[1], CAMCAMP_BLK_SIZE_DEF},                        
	{(void*)&CAMCMP_BLK(af_mode)[2], CAMCAMP_BLK_SIZE_DEF}                         
};




static camcmp_data_type CAMCMP_BTBL(mf_pos)[] =
{
	{(void*)&CAMCMP_BLK(mf_pos)[0], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(mf_pos)[1], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(mf_pos)[2], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(mf_pos)[3], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(mf_pos)[4], CAMCAMP_BLK_SIZE_DEF}                          
};




static camcmp_data_type CAMCMP_BTBL(jpeg_limit)[] =
{
	{(void*)CAMCMP_BLK(jpeg_limit_5m), CAMCMP_SIZE_BLK(CAMCMP_BLK(jpeg_limit_5m))},    
	{(void*)CAMCMP_BLK(jpeg_limit_3m), CAMCMP_SIZE_BLK(CAMCMP_BLK(jpeg_limit_3m))},    
	{(void*)CAMCMP_BLK(jpeg_limit_2m), CAMCMP_SIZE_BLK(CAMCMP_BLK(jpeg_limit_2m))},    
	{(void*)CAMCMP_BLK(jpeg_limit_1m), CAMCMP_SIZE_BLK(CAMCMP_BLK(jpeg_limit_1m))}     
};







static camcmp_data_type CAMCMP_BTBL(set_shut)[] =
{
	{(void*)&CAMCMP_BLK(set_shut)[0], CAMCAMP_BLK_SIZE_DEF},                         
};



static camcmp_data_type CAMCMP_BTBL(set_gain)[] =
{
	{(void*)&CAMCMP_BLK(set_gain)[0], CAMCAMP_BLK_SIZE_DEF},                         
};




static camcmp_data_type CAMCMP_BTBL(set_capture_num)[] =
{
	{(void*)&CAMCMP_BLK(set_capture_num)[0], CAMCAMP_BLK_SIZE_DEF},                         
	{(void*)&CAMCMP_BLK(set_capture_num)[1], CAMCAMP_BLK_SIZE_DEF},                         
};







static camcmp_data_type CAMCMP_BTBL(scene_change)[] =
{
	
	{(void*)CAMCMP_BLK(scene_auto),                      CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_auto))                      },    
	{(void*)CAMCMP_BLK(scene_portrait),                  CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_portrait))                  },    
	{(void*)CAMCMP_BLK(scene_portrait_illumi),           CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_portrait_illumi))           },    
	{(void*)CAMCMP_BLK(scene_landscape),                 CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_landscape))                 },    
	{(void*)CAMCMP_BLK(scene_backlight),                 CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_backlight))                 },    
	{(void*)CAMCMP_BLK(scene_night),                     CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_night))                     },    
	{(void*)CAMCMP_BLK(scene_pet),                       CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_pet))                       },    
	{(void*)CAMCMP_BLK(scene_cooking),                   CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_cooking))                   },    
	{(void*)CAMCMP_BLK(scene_sports),                    CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_sports))                    },    
	{(void*)CAMCMP_BLK(scene_off),                       CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_off))                       },    
	{(void*)CAMCMP_BLK(scene_high_sensitivity),          CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_high_sensitivity))          },    
	
	{(void*)CAMCMP_BLK(scene_auto_fixation),             CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_auto_fixation))             },    
	{(void*)CAMCMP_BLK(scene_portrait_fixation),         CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_portrait_fixation))         },    
	{(void*)CAMCMP_BLK(scene_portrait_illumi_fixation),  CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_portrait_illumi_fixation))  },    
	{(void*)CAMCMP_BLK(scene_landscape_fixation),        CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_landscape_fixation))        },    
	{(void*)CAMCMP_BLK(scene_backlight_fixation),        CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_backlight_fixation))        },    
	{(void*)CAMCMP_BLK(scene_night_fixation),            CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_night_fixation))            },    
	{(void*)CAMCMP_BLK(scene_pet_fixation),              CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_pet_fixation))              },    
	{(void*)CAMCMP_BLK(scene_cooking_fixation),          CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_cooking_fixation))          },    
	{(void*)CAMCMP_BLK(scene_sports_fixation),           CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_sports_fixation))           },    
	{(void*)CAMCMP_BLK(scene_off_fixation),              CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_off_fixation))              },    
	{(void*)CAMCMP_BLK(scene_high_sensitivity_fixation), CAMCMP_SIZE_BLK(CAMCMP_BLK(scene_high_sensitivity_fixation)) }     
};




static camcmp_data_type CAMCMP_BTBL(scene_angle_auto)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_auto)[0],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_auto)[1],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_auto)[2],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_auto)[3],  CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_portrait)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_portrait)[0],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_portrait)[1],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_portrait)[2],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_portrait)[3],  CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_portrait_illumi)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_portrait_illumi)[0],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_portrait_illumi)[1],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_portrait_illumi)[2],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_portrait_illumi)[3],  CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_landscape)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_landscape)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_landscape)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_landscape)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_landscape)[3], CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_backlight)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_backlight)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_backlight)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_backlight)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_backlight)[3], CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_night)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_night)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_night)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_night)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_night)[3], CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_pet)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_pet)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_pet)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_pet)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_pet)[3], CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_cooking)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_cooking)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_cooking)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_cooking)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_cooking)[3], CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_sports)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_sports)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_sports)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_sports)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_sports)[3], CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_off)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_off)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_off)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_off)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_off)[3], CAMCAMP_BLK_SIZE_DEF }     
};



static camcmp_data_type CAMCMP_BTBL(scene_angle_high_sensitivity)[] =
{
	
	{(void*)&CAMCMP_BLK(scene_angle_high_sensitivity)[0], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_high_sensitivity)[1], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_high_sensitivity)[2], CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(scene_angle_high_sensitivity)[3], CAMCAMP_BLK_SIZE_DEF }     
};






static camcmp_data_type CAMCMP_BTBL(camera_mode)[] =
{
	
	{(void*)&CAMCMP_BLK(camera_mode)[0],  CAMCAMP_BLK_SIZE_DEF },    
};






static camcmp_data_type CAMCMP_BTBL(af_mode_moni)[] =
{
	{(void*)&CAMCMP_BLK(af_mode_moni)[0], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(af_mode_moni)[1], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(af_mode_moni)[2], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(af_mode_moni)[3], CAMCAMP_BLK_SIZE_DEF}  
};



static camcmp_data_type CAMCMP_BTBL(frame_pos)[] =
{
	{(void*)&CAMCMP_BLK(frame_pos)[0], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(frame_pos)[1], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(frame_pos)[2], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(frame_pos)[3], CAMCAMP_BLK_SIZE_DEF}, 
};



static camcmp_data_type CAMCMP_BTBL(set_saf_mode)[] =
{
	{(void*)&CAMCMP_BLK(set_saf_mode)[0],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(set_saf_mode)[1],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(set_saf_mode)[2],  CAMCAMP_BLK_SIZE_DEF },    
};



static camcmp_data_type CAMCMP_BTBL(dac_code)[] =
{
	{(void*)&CAMCMP_BLK(dac_code)[0],  CAMCAMP_BLK_SIZE_DEF },    
};



static camcmp_data_type CAMCMP_BTBL(awb_hold)[] =
{
	{(void*)&CAMCMP_BLK(awb_hold)[0],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(awb_hold)[1],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(awb_hold)[2],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(awb_hold)[3],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(awb_hold)[4],  CAMCAMP_BLK_SIZE_DEF },    
	{(void*)&CAMCMP_BLK(awb_hold)[5],  CAMCAMP_BLK_SIZE_DEF },    
};



static camcmp_data_type CAMCMP_BTBL(ae_hold)[] =
{
	{(void*)&CAMCMP_BLK(ae_hold)[0], CAMCAMP_BLK_SIZE_DEF   },    
	{(void*)&CAMCMP_BLK(ae_hold)[1], CAMCAMP_BLK_SIZE_DEF   },    
};



static camcmp_data_type CAMCMP_BTBL(search_area)[] =
{
	{(void*)&CAMCMP_BLK(search_area)[0], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(search_area)[1], CAMCAMP_BLK_SIZE_DEF}, 
};



static camcmp_data_type CAMCMP_BTBL(ae_sub)[] =
{
	{(void*)&CAMCMP_BLK(ae_sub)[0], CAMCAMP_BLK_SIZE_DEF},                         
};




static camcmp_data_type CAMCMP_BTBL(photometry)[] =
{
	{(void*)&CAMCMP_BLK(photometry)[0], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(photometry)[1], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(photometry)[2], CAMCAMP_BLK_SIZE_DEF}, 
	{(void*)&CAMCMP_BLK(photometry)[3], CAMCAMP_BLK_SIZE_DEF}, 
};




static camcmp_data_type CAMCMP_BTBL(free_weight)[] =
{
	{(void*)&CAMCMP_BLK(free_weight)[0], CAMCAMP_BLK_SIZE_DEF}, 
};







static camcmp_data_type CAMCMP_BTBL(VE295)[] =
{
	{(void*)&CAMCMP_BLK(VE295)[0],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[1],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[2],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[3],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[4],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[5],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[6],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[7],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[8],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[9],  CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[10], CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[11], CAMCAMP_BLK_SIZE_DEF},                      
	{(void*)&CAMCMP_BLK(VE295)[12], CAMCAMP_BLK_SIZE_DEF}                       
};








static camcmp_data_type CAMCMP_BTBL(iso_type)[] =
{
	{(void*)CAMCMP_BLK(iso_type_1600),  CAMCMP_SIZE_BLK(CAMCMP_BLK(iso_type_1600))},   
	{(void*)CAMCMP_BLK(iso_type_3200),  CAMCMP_SIZE_BLK(CAMCMP_BLK(iso_type_3200))},   
	{(void*)CAMCMP_BLK(iso_type_12800), CAMCMP_SIZE_BLK(CAMCMP_BLK(iso_type_12800))}   
};



















camcmp_makecmd_type g_camcmp_ius006f_cmd_list[] =
{
  

	{CAMCMP_CMD(chk_dev_sts), CAMCMP_SIZE_DAT(CAMCMP_CMD(chk_dev_sts)), NULL,                    0},                                         
	{CAMCMP_CMD(init_set_1),  CAMCMP_SIZE_DAT(CAMCMP_CMD(init_set_1)),  NULL,                    0},                                         
	{CAMCMP_CMD(init_set_2),  CAMCMP_SIZE_DAT(CAMCMP_CMD(init_set_2)),  NULL,                    0},                                         
	{CAMCMP_CMD(init_set_3),  CAMCMP_SIZE_DAT(CAMCMP_CMD(init_set_3)),  NULL,                    0},                                         
	{CAMCMP_CMD(rom_correct), CAMCMP_SIZE_DAT(CAMCMP_CMD(rom_correct)), NULL,                    0},                                         
	{CAMCMP_CMD(init_set_4),  CAMCMP_SIZE_DAT(CAMCMP_CMD(init_set_4)),  NULL,                    0},                                         
	{CAMCMP_CMD(init_set_5),  CAMCMP_SIZE_DAT(CAMCMP_CMD(init_set_5)),  NULL,                    0},                                         
	{CAMCMP_CMD(wb_auto),     CAMCMP_SIZE_DAT(CAMCMP_CMD(wb_auto)),     NULL,                    0},                                         
	{CAMCMP_CMD(wb_inc),      CAMCMP_SIZE_DAT(CAMCMP_CMD(wb_inc)),      NULL,                    0},                                         
	{CAMCMP_CMD(wb_sunny),    CAMCMP_SIZE_DAT(CAMCMP_CMD(wb_sunny)),    NULL,                    0},                                         
	{CAMCMP_CMD(wb_fluor),    CAMCMP_SIZE_DAT(CAMCMP_CMD(wb_fluor)),    NULL,                    0},                                         
	{CAMCMP_CMD(wb_cloudy),   CAMCMP_SIZE_DAT(CAMCMP_CMD(wb_cloudy)),   NULL,                    0},                                         
	{CAMCMP_CMD(wb_led),      CAMCMP_SIZE_DAT(CAMCMP_CMD(wb_led)),      NULL,                    0},                                         
	{CAMCMP_CMD(night_off),   CAMCMP_SIZE_DAT(CAMCMP_CMD(night_off)),   NULL,                    0},                                         
	{CAMCMP_CMD(night_on),    CAMCMP_SIZE_DAT(CAMCMP_CMD(night_on)),    NULL,                    0},                                         
	{CAMCMP_CMD(movie),       CAMCMP_SIZE_DAT(CAMCMP_CMD(movie)),       NULL,                    0},                                         
	{CAMCMP_CMD(cap_size),    CAMCMP_SIZE_DAT(CAMCMP_CMD(cap_size)),    CAMCMP_BTBL(cap_size),   CAMCMP_SIZE_DAT(CAMCMP_BTBL(cap_size))},    
	{CAMCMP_CMD(moni_size),   CAMCMP_SIZE_DAT(CAMCMP_CMD(moni_size)),   CAMCMP_BTBL(moni_size),  CAMCMP_SIZE_DAT(CAMCMP_BTBL(moni_size))},   
	{CAMCMP_CMD(chg_mode),    CAMCMP_SIZE_DAT(CAMCMP_CMD(chg_mode)),    CAMCMP_BTBL(chg_mode),   CAMCMP_SIZE_DAT(CAMCMP_BTBL(chg_mode))},    



	{CAMCMP_CMD(zoom_5m),     CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_5m)),     CAMCMP_BTBL(zoom_5m),    CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_5m))},     
	{CAMCMP_CMD(zoom_wqhd),   CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_wqhd)),   CAMCMP_BTBL(zoom_wqhd),  CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_wqhd))},   
	{CAMCMP_CMD(zoom_2m),     CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_2m)),     CAMCMP_BTBL(zoom_2m),    CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_2m))},     
	{CAMCMP_CMD(zoom_1m),     CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_1m)),     CAMCMP_BTBL(zoom_1m),    CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_1m))},     
	{CAMCMP_CMD(zoom_vga),    CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_vga)),    CAMCMP_BTBL(zoom_vga),   CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_vga))},    
	{CAMCMP_CMD(zoom_hd_mv),  CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_hd_mv)),  CAMCMP_BTBL(zoom_hd_mv), CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_hd_mv))},  
	{CAMCMP_CMD(zoom_vga_mv), CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_vga_mv)), CAMCMP_BTBL(zoom_vga_mv),CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_vga_mv))}, 
	{CAMCMP_CMD(zoom_qvga_mv),CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_qvga_mv)),CAMCMP_BTBL(zoom_qvga_mv),CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_qvga_mv))},
	{CAMCMP_CMD(zoom_qcif_mv),CAMCMP_SIZE_DAT(CAMCMP_CMD(zoom_qcif_mv)),CAMCMP_BTBL(zoom_qcif_mv),CAMCMP_SIZE_DAT(CAMCMP_BTBL(zoom_qcif_mv))},










	{CAMCMP_CMD(brightness),  CAMCMP_SIZE_DAT(CAMCMP_CMD(brightness)),  CAMCMP_BTBL(brightness), CAMCMP_SIZE_DAT(CAMCMP_BTBL(brightness))},  
	{CAMCMP_CMD(effect),      CAMCMP_SIZE_DAT(CAMCMP_CMD(effect)),      CAMCMP_BTBL(effect),     CAMCMP_SIZE_DAT(CAMCMP_BTBL(effect))},      
	{CAMCMP_CMD(quality),     CAMCMP_SIZE_DAT(CAMCMP_CMD(quality)),     CAMCMP_BTBL(quality),    CAMCMP_SIZE_DAT(CAMCMP_BTBL(quality))},     
	{CAMCMP_CMD(int_clr),     CAMCMP_SIZE_DAT(CAMCMP_CMD(int_clr)),     CAMCMP_BTBL(int_clr),    CAMCMP_SIZE_DAT(CAMCMP_BTBL(int_clr))},     
	{CAMCMP_CMD(af_cancel),   CAMCMP_SIZE_DAT(CAMCMP_CMD(af_cancel)),   NULL,                    0},                                         
	{CAMCMP_CMD(af_mode),     CAMCMP_SIZE_DAT(CAMCMP_CMD(af_mode)),     CAMCMP_BTBL(af_mode),    CAMCMP_SIZE_DAT(CAMCMP_BTBL(af_mode))},     
	{CAMCMP_CMD(mf_start),    CAMCMP_SIZE_DAT(CAMCMP_CMD(mf_start)),    CAMCMP_BTBL(mf_pos),     CAMCMP_SIZE_DAT(CAMCMP_BTBL(mf_pos))},      
	{CAMCMP_CMD(ae_normal),   CAMCMP_SIZE_DAT(CAMCMP_CMD(ae_normal)),   NULL,                    0},                                         
	{CAMCMP_CMD(ae_long),     CAMCMP_SIZE_DAT(CAMCMP_CMD(ae_long)),     NULL,                    0},                                         
	{CAMCMP_CMD(ptnchk_off),  CAMCMP_SIZE_DAT(CAMCMP_CMD(ptnchk_off)),  NULL,                    0},                                         
	{CAMCMP_CMD(ptnchk_on),   CAMCMP_SIZE_DAT(CAMCMP_CMD(ptnchk_on)),   NULL,                    0},                                         
	{CAMCMP_CMD(chk_af_lock), CAMCMP_SIZE_DAT(CAMCMP_CMD(chk_af_lock)), NULL,                    0},                                         
	{CAMCMP_CMD(thumbnail),   CAMCMP_SIZE_DAT(CAMCMP_CMD(thumbnail)),   NULL,                    0},                                         
	{CAMCMP_CMD(jpeg_limit),  CAMCMP_SIZE_DAT(CAMCMP_CMD(jpeg_limit)),  CAMCMP_BTBL(jpeg_limit), CAMCMP_SIZE_DAT(CAMCMP_BTBL(jpeg_limit))}, 
	{CAMCMP_CMD(af_restart),  CAMCMP_SIZE_DAT(CAMCMP_CMD(af_restart)),  NULL,                    0},                                         
	{CAMCMP_CMD(jpeg_intsts), CAMCMP_SIZE_DAT(CAMCMP_CMD(jpeg_intsts)), NULL,                    0}, 



	{CAMCMP_CMD(flc_mode),    CAMCMP_SIZE_DAT(CAMCMP_CMD(flc_mode)),    CAMCMP_BTBL(flc_mode),   CAMCMP_SIZE_DAT(CAMCMP_BTBL(flc_mode))},    





	{CAMCMP_CMD(chk_mode_sts),CAMCMP_SIZE_DAT(CAMCMP_CMD(chk_mode_sts)),NULL,                    0},                                         
	{CAMCMP_CMD(moni_reflesh),CAMCMP_SIZE_DAT(CAMCMP_CMD(moni_reflesh)),NULL,                    0},                                         
	{CAMCMP_CMD(af_mode_moni),CAMCMP_SIZE_DAT(CAMCMP_CMD(af_mode_moni)),CAMCMP_BTBL(af_mode_moni),CAMCMP_SIZE_DAT(CAMCMP_BTBL(af_mode_moni))},
	{CAMCMP_CMD(frame_pos),   CAMCMP_SIZE_DAT(CAMCMP_CMD(frame_pos)),   CAMCMP_BTBL(frame_pos),  CAMCMP_SIZE_DAT(CAMCMP_BTBL(frame_pos))},   
	{CAMCMP_CMD(search_area), CAMCMP_SIZE_DAT(CAMCMP_CMD(search_area)), CAMCMP_BTBL(search_area),CAMCMP_SIZE_DAT(CAMCMP_BTBL(search_area))}, 
	{CAMCMP_CMD(ae_sub),      CAMCMP_SIZE_DAT(CAMCMP_CMD(ae_sub)),      CAMCMP_BTBL(ae_sub),     CAMCMP_SIZE_DAT(CAMCMP_BTBL(ae_sub))},      
	{CAMCMP_CMD(photometry),  CAMCMP_SIZE_DAT(CAMCMP_CMD(photometry)),  CAMCMP_BTBL(photometry), CAMCMP_SIZE_DAT(CAMCMP_BTBL(photometry))},  
	{CAMCMP_CMD(free_weight),  CAMCMP_SIZE_DAT(CAMCMP_CMD(free_weight)),  CAMCMP_BTBL(free_weight), CAMCMP_SIZE_DAT(CAMCMP_BTBL(free_weight))},



  

	{CAMCMP_CMD(otp0l),       CAMCMP_SIZE_DAT(CAMCMP_CMD(otp0l)),       NULL,                    0},                                         
	{CAMCMP_CMD(otp0m),       CAMCMP_SIZE_DAT(CAMCMP_CMD(otp0m)),       NULL,                    0},                                         
	{CAMCMP_CMD(otp0h),       CAMCMP_SIZE_DAT(CAMCMP_CMD(otp0h)),       NULL,                    0},                                         
	{CAMCMP_CMD(otp1l),       CAMCMP_SIZE_DAT(CAMCMP_CMD(otp1l)),       NULL,                    0},                                         
	{CAMCMP_CMD(otp1m),       CAMCMP_SIZE_DAT(CAMCMP_CMD(otp1m)),       NULL,                    0},                                         
	{CAMCMP_CMD(otp1h),       CAMCMP_SIZE_DAT(CAMCMP_CMD(otp1h)),       NULL,                    0},                                         
	{CAMCMP_CMD(otp),         CAMCMP_SIZE_DAT(CAMCMP_CMD(otp)),         NULL,                    0},                                         
	{CAMCMP_CMD(intsts),      CAMCMP_SIZE_DAT(CAMCMP_CMD(intsts)),      NULL,                    0},                                         

	{CAMCMP_CMD(evaluate),    CAMCMP_SIZE_DAT(CAMCMP_CMD(evaluate)),    NULL,                    0},                                         
	{CAMCMP_CMD(lens_pos),    CAMCMP_SIZE_DAT(CAMCMP_CMD(lens_pos)),    NULL,                    0},                                         
	{CAMCMP_CMD(af_step),     CAMCMP_SIZE_DAT(CAMCMP_CMD(af_step)),     NULL,                    0},                                         
	{CAMCMP_CMD(aescl),       CAMCMP_SIZE_DAT(CAMCMP_CMD(aescl)),       NULL,                    0},                                         
	{CAMCMP_CMD(sht_time_h),  CAMCMP_SIZE_DAT(CAMCMP_CMD(sht_time_h)),  NULL,                    0},                                         
	{CAMCMP_CMD(sht_time_l),  CAMCMP_SIZE_DAT(CAMCMP_CMD(sht_time_l)),  NULL,                    0},                                         
	{CAMCMP_CMD(agc_scl),     CAMCMP_SIZE_DAT(CAMCMP_CMD(agc_scl)),     NULL,                    0},                                         


	{CAMCMP_CMD(af_result),   CAMCMP_SIZE_DAT(CAMCMP_CMD(af_result)),   NULL,                    0},                                         
	{CAMCMP_CMD(af_state),    CAMCMP_SIZE_DAT(CAMCMP_CMD(af_state)),    NULL,                    0},                                         


	{CAMCMP_CMD(manual_step), CAMCMP_SIZE_DAT(CAMCMP_CMD(manual_step)), NULL,                    0},                                         
	{CAMCMP_CMD(area_low_type1),  CAMCMP_SIZE_DAT(CAMCMP_CMD(area_low_type1)),  NULL,            0},                                         
	{CAMCMP_CMD(area_high_type1), CAMCMP_SIZE_DAT(CAMCMP_CMD(area_high_type1)), NULL,            0},                                         

	{CAMCMP_CMD(jpg_sts),     CAMCMP_SIZE_DAT(CAMCMP_CMD(jpg_sts)),     NULL,                    0},                                         
	{CAMCMP_CMD(jpg_retry),   CAMCMP_SIZE_DAT(CAMCMP_CMD(jpg_retry)),   NULL,                    0},                                         




	
	{CAMCMP_CMD(cap_half_ae_ctrl),  CAMCMP_SIZE_DAT(CAMCMP_CMD(cap_half_ae_ctrl)),  NULL,                          0                                            },  
	{CAMCMP_CMD(set_shut),          CAMCMP_SIZE_DAT(CAMCMP_CMD(set_shut)),          CAMCMP_BTBL(set_shut),         CAMCMP_SIZE_DAT(CAMCMP_BTBL(set_shut))       },  
	{CAMCMP_CMD(set_gain),          CAMCMP_SIZE_DAT(CAMCMP_CMD(set_gain)),          CAMCMP_BTBL(set_gain),         CAMCMP_SIZE_DAT(CAMCMP_BTBL(set_gain))       },  
	{CAMCMP_CMD(cap_gainoffset),    CAMCMP_SIZE_DAT(CAMCMP_CMD(cap_gainoffset)),    NULL,                          0                                            },  
	{CAMCMP_CMD(set_capture_num),   CAMCMP_SIZE_DAT(CAMCMP_CMD(set_capture_num)),   CAMCMP_BTBL(set_capture_num),  CAMCMP_SIZE_DAT(CAMCMP_BTBL(set_capture_num))},  
	{CAMCMP_CMD(set_ae_stop),       CAMCMP_SIZE_DAT(CAMCMP_CMD(set_ae_stop)),       NULL,                          0                                            },  



	{CAMCMP_CMD(scene_change),                 CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_change)),                 CAMCMP_BTBL(scene_change),                 CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_change))                }, 
	{CAMCMP_CMD(scene_angle_auto),             CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_auto)),             CAMCMP_BTBL(scene_angle_auto),             CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_auto))            }, 
	{CAMCMP_CMD(scene_angle_portrait),         CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_portrait)),         CAMCMP_BTBL(scene_angle_portrait),         CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_portrait))        }, 
	{CAMCMP_CMD(scene_angle_portrait_illumi),  CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_portrait_illumi)),  CAMCMP_BTBL(scene_angle_portrait_illumi),  CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_portrait_illumi)) }, 
	{CAMCMP_CMD(scene_angle_landscape),        CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_landscape)),        CAMCMP_BTBL(scene_angle_landscape),        CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_landscape))       }, 
	{CAMCMP_CMD(scene_angle_backlight),        CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_backlight)),        CAMCMP_BTBL(scene_angle_backlight),        CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_backlight))       }, 
	{CAMCMP_CMD(scene_angle_night),            CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_night)),            CAMCMP_BTBL(scene_angle_night),            CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_night))           }, 
	{CAMCMP_CMD(scene_angle_pet),              CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_pet)),              CAMCMP_BTBL(scene_angle_pet),              CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_pet))             }, 
	{CAMCMP_CMD(scene_angle_cooking),          CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_cooking)),          CAMCMP_BTBL(scene_angle_cooking),          CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_cooking))         }, 
	{CAMCMP_CMD(scene_angle_sports),           CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_sports)),           CAMCMP_BTBL(scene_angle_sports),           CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_sports))          }, 
	{CAMCMP_CMD(scene_angle_off),              CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_off)),              CAMCMP_BTBL(scene_angle_off),              CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_off))             }, 
	{CAMCMP_CMD(scene_angle_high_sensitivity), CAMCMP_SIZE_DAT(CAMCMP_CMD(scene_angle_high_sensitivity)), CAMCMP_BTBL(scene_angle_high_sensitivity), CAMCMP_SIZE_DAT(CAMCMP_BTBL(scene_angle_high_sensitivity))}, 



	{CAMCMP_CMD(camera_mode),       CAMCMP_SIZE_DAT(CAMCMP_CMD(camera_mode)),       CAMCMP_BTBL(camera_mode),      CAMCMP_SIZE_DAT(CAMCMP_BTBL(camera_mode))   },  



	{CAMCMP_CMD(hsize_moni),   CAMCMP_SIZE_DAT(CAMCMP_CMD(hsize_moni)),   NULL,                      0                                          }, 
	{CAMCMP_CMD(vsize_moni),   CAMCMP_SIZE_DAT(CAMCMP_CMD(vsize_moni)),   NULL,                      0                                          }, 
	{CAMCMP_CMD(afc_status),   CAMCMP_SIZE_DAT(CAMCMP_CMD(afc_status)),   NULL,                      0                                          }, 
	{CAMCMP_CMD(set_saf_mode), CAMCMP_SIZE_DAT(CAMCMP_CMD(set_saf_mode)), CAMCMP_BTBL(set_saf_mode), CAMCMP_SIZE_DAT(CAMCMP_BTBL(set_saf_mode)) }, 
	{CAMCMP_CMD(dac_code),     CAMCMP_SIZE_DAT(CAMCMP_CMD(dac_code)),     CAMCMP_BTBL(dac_code),     CAMCMP_SIZE_DAT(CAMCMP_BTBL(dac_code))     }, 
	{CAMCMP_CMD(afc_result),   CAMCMP_SIZE_DAT(CAMCMP_CMD(afc_result)),   NULL,                      0                                          }, 
	{CAMCMP_CMD(get_saf_mode), CAMCMP_SIZE_DAT(CAMCMP_CMD(get_saf_mode)), NULL,                      0                                          }, 
	{CAMCMP_CMD(awb_hold),     CAMCMP_SIZE_DAT(CAMCMP_CMD(awb_hold)),     CAMCMP_BTBL(awb_hold),     CAMCMP_SIZE_DAT(CAMCMP_BTBL(awb_hold))     }, 
	{CAMCMP_CMD(ae_hold),      CAMCMP_SIZE_DAT(CAMCMP_CMD(ae_hold)),      CAMCMP_BTBL(ae_hold),      CAMCMP_SIZE_DAT(CAMCMP_BTBL(ae_hold))      }, 
	{CAMCMP_CMD(ae_sub_sts),   CAMCMP_SIZE_DAT(CAMCMP_CMD(ae_sub_sts)),   NULL,                      0                                          }, 



	{CAMCMP_CMD(VE295),  CAMCMP_SIZE_DAT(CAMCMP_CMD(VE295)),  CAMCMP_BTBL(VE295), CAMCMP_SIZE_DAT(CAMCMP_BTBL(VE295))},    





	{CAMCMP_CMD(iso_type),  CAMCMP_SIZE_DAT(CAMCMP_CMD(iso_type)),  CAMCMP_BTBL(iso_type), CAMCMP_SIZE_DAT(CAMCMP_BTBL(iso_type))},          





	{CAMCMP_CMD(speedmovie),  CAMCMP_SIZE_DAT(CAMCMP_CMD(speedmovie)),  NULL,                    0},                                         





  
	{NULL,                    0,                                        NULL,                    0}                                          
};




camcmp_ius006f_af_val_type* g_p_camcmp_ius006f_af = &CAMCMP_DAT(af_val);





uint16_t* g_p_camcmp_ius006f_ver = &CAMCMP_DAT(version);













static camcmp_ius006f_reg_val_type CAMCMP_POLL(chk_af_lock)[] =
{
	{CAMCMP_REG_POLL1, 0x00F8, 0x00000010, NULL,                CAMCMP_D_LEN_BYTE},      
	{CAMCMP_REG_POLL2, 0x6D76, 0x000000FF, NULL,                CAMCMP_D_LEN_BYTE}       
};




camcmp_data_type g_camcmp_ius006f_poll_list[] =
{
	{(void*)CAMCMP_POLL(chk_af_lock), CAMCMP_SIZE_REG(CAMCMP_POLL(chk_af_lock))}
};








































































































































































