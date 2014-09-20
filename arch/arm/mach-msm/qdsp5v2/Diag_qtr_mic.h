/**********************************************************************
* File Name: arch/arm/mach-msm/qdsp5v2/Diag_qtr_mic.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/

#ifndef DIAG_QTR_MIC_H_
#define DIAG_QTR_MIC_H_




typedef struct
{
	
	char tx_dev;
	
	
	char rx_dev;
	
	





	char type;
}Diag_Audio_qtr_action_type;




char Diag_Audio_qtr_action(Diag_Audio_qtr_action_type *data);




typedef struct
{
	








	char path;

}Diag_Audio_qtr_loopback_type;

char Diag_Audio_qtr_loopback( Diag_Audio_qtr_loopback_type *data );




typedef struct
{
	




	char bias;

	
}Diag_Audio_hsedbias_ctl_type;


char Diag_Audio_hsedbias_ctl( Diag_Audio_hsedbias_ctl_type *data );


signed char Diag_Audio_rx_gain_adjust(signed char data);
signed char Diag_Audio_tx_gain_adjust(signed char data);


#endif	

