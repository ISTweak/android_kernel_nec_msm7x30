/**********************************************************************
* File Name: include/net/irda/irdrv.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/












#ifndef IRDRV_H
#define IRDRV_H

#define IRDRVPARAMSET       0
#define IRDRVDISCOVERYSTART 1101
#define IRDRVDISCOVERYSTOP  1102

#define IR_COMMSTAT_POWERON     0                                               
#define IR_COMMSTAT_STARTNEGO   1                                               
#define IR_COMMSTAT_DISCLAP     2                                               
#define IR_COMMSTAT_POWEROFF    3                                               




struct irda_paramdata{
    unsigned char   dev_nickname[32];
    unsigned int    name_len;
    unsigned char   discovery_timeout;
};




extern struct irda_paramdata irda_param;                                        
extern unsigned char irdrv_icon_flag;                                           
extern unsigned char irdrv_irlap_event_flag;                                    
extern unsigned char irdrv_disc_wait_flag;                                      
extern wait_queue_head_t irdrv_irlap_event_wait;                                
extern wait_queue_head_t irdrv_disc_event_wait;									
#endif 
