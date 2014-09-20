/**********************************************************************
* File Name: drivers/i2c/chips/akm8977_queue.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/






#include <linux/slab.h>
#include <linux/akm8977_queue.h>













BOOL IsInit = 0;


static struct mutex queue_mutex;


T_QUEUE* head_queue_addr[E_QUEUE_KIND_MAX];

T_QUEUE* tail_queue_addr[E_QUEUE_KIND_MAX];





void ErrorQueueHandler( E_QUEUE_KIND kind )
{
    ClearQueue( kind );
}





void InitializeQueue()
{
    int count = 0;



    if( IsInit != 0 )
    {
        return;
    }

    IsInit = 1;

    mutex_init(&queue_mutex);

    for( count = 0; count < E_QUEUE_KIND_MAX; count++ )
    {
        head_queue_addr[count] = NULL;
        tail_queue_addr[count] = NULL;
    }

}





void TerminateQueue()
{
    int count;



    if( IsInit == 0 )
    {
        return;
    }

    for( count = 0; count < E_QUEUE_KIND_MAX; count++ )
    {
        ClearQueue( count );
    }

    IsInit = 0;
}





void ClearQueue( int kind )
{
    int ret;
    T_MSG_DATA dummy;



    if( IsInit == 0 )
    {
        return;
    }

    for(;;)
    {
        ret = Dequeue( kind, &dummy );

        if( ret == QUE_EMPTY )
        {
            break;
        }
    }
}







int Enqueue( int kind, T_MSG_DATA info )
{





    T_QUEUE *new_queue = NULL;

    if( IsInit == 0 )
    {
        return QUE_ERROR;
    }

    new_queue = (T_QUEUE *)kmalloc( sizeof(T_QUEUE) , GFP_KERNEL);

    if( new_queue == NULL )
    {
        return QUE_ERROR;
    }

    memset( new_queue, 0x0, sizeof(T_QUEUE) );

    memcpy( &(new_queue->info), &info, sizeof(T_MSG_DATA) );

    mutex_lock( &queue_mutex );

    if( head_queue_addr[kind] == NULL )
    {
        head_queue_addr[kind]       = new_queue;
        tail_queue_addr[kind]       = head_queue_addr[kind];
        tail_queue_addr[kind]->next = NULL;
    }
    else
    {
        tail_queue_addr[kind]->next = new_queue;
        tail_queue_addr[kind]       = new_queue;
        tail_queue_addr[kind]->next = NULL;
    }



















    mutex_unlock( &queue_mutex );

    return QUE_OK;
}








int Dequeue( int kind, T_MSG_DATA* info )
{





    T_QUEUE* tmp;

    if( IsInit == 0 )
    {
        return QUE_ERROR;
    }

    if( info == NULL )
    {
        return QUE_ERROR;
    }

    mutex_lock( &queue_mutex );

    if( head_queue_addr[kind] == NULL )
    {
        mutex_unlock( &queue_mutex );



        return QUE_EMPTY;
    }

    memcpy( info, &(head_queue_addr[kind]->info), sizeof(T_MSG_DATA) );

    tmp = head_queue_addr[kind];

    if( head_queue_addr[kind]->next != NULL )
    {
        head_queue_addr[kind] = (T_QUEUE*)head_queue_addr[kind]->next;
    }
    else
    {
        head_queue_addr[kind] = NULL;
        tail_queue_addr[kind] = NULL;
    }

    kfree(tmp);



















    mutex_unlock( &queue_mutex );

    return QUE_OK;
}

