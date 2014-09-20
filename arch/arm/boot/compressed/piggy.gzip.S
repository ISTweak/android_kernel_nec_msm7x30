/**********************************************************************
* File Name: arch/arm/boot/compressed/piggy.gzip.S
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/
	.section .piggydata,#alloc
	.globl	input_data_uncompress
input_data_uncompress:
	.incbin	"arch/arm/boot/Image.aa"
	.globl	input_data_uncompress_end
input_data_uncompress_end:
	.globl	input_data




input_data:

	.incbin	"arch/arm/boot/compressed/piggy.gzip"





	.globl	input_data_end
input_data_end:
