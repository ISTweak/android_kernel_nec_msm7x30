/**********************************************************************
* File Name: include/linux/akm8977_queue.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/
#ifndef __AKM8977_QUEUE_H
#define __AKM8977_QUEUE_H






#include <linux/akm8977.h>
#include <linux/akm8977_table.h>





#define QUE_OK				0				
#define QUE_EMPTY			1				
#define QUE_ERROR			2				

typedef int BOOL;
typedef struct _tag_msg_data
{
    EVENT_NUM eventid;
}T_MSG_DATA;



typedef enum _enum_queue_kind
{
	E_QUE_REQ				= 0,
	E_QUEUE_KIND_MAX,
	
	E_QUE_NONE						= 0xFFFF,
}E_QUEUE_KIND;				


typedef struct _tag_queue
{
	
	T_MSG_DATA info;

	
	void* next;

}T_QUEUE;			



extern void ErrorQueueHandler( E_QUEUE_KIND kind );

extern void InitializeQueue(void);

extern void TerminateQueue(void);

extern void ClearQueue( int kind );

extern int Enqueue( int kind, T_MSG_DATA info );

extern int Dequeue( int kind, T_MSG_DATA* info );

#endif 
