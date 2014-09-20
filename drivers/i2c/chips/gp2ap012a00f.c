/**********************************************************************
* File Name: drivers/i2c/chips/gp2ap012a00f.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/








#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/spinlock.h>
#include <linux/i2c/gp2ap012a00f.h>
#include <mach/msm_battery.h>
#include <asm/uaccess.h>

















#define GP2AP012A00F_DRV_NAME    "gp2ap012a00f"
#define DRIVER_VERSION           "2.0.0"


#define D_MODE_ALS             (0)
#define D_MODE_PROX            (1)
#define D_MODE_KIND_NUM        (2)


#define D_MEAS_NOT_COMP       (-1)


#define D_FALSE                (0)
#define D_TRUE                 (1)


#define D_DEACTIVE             (0)
#define D_ACTIVE               (1)

#define D_PROX_ACTIVE_KIND_NUM (2)
#define D_ALS_ACTIVE_KIND_NUM  (2)

#define D_RES_TABLE_NUM        (8)

#define D_MEAS_NUM             (5)
#define D_MEAS_AVE_NUM         (D_MEAS_NUM - 2)

#define D_DATA_SIZE_2BYTE      (2)


typedef enum _e_state
{
    E_STATE_STOP  = 0,
    E_STATE_PROX,
    E_STATE_ALS,
    E_STATE_ALT,
    E_STATE_MAX
}E_STATE_TYPE;


typedef enum _e_event
{
    E_EVENT_PROX_START = 0,
    E_EVENT_PROX_STOP,
    E_EVENT_ALS_START,
    E_EVENT_ALS_STOP,
    E_EVENT_PROX_COMP,
    E_EVENT_ALS_COMP,
    E_EVENT_WAKEUP,
    E_EVENT_MAX
}E_EVENT_TYPE;


struct gp2ap012a00f_data
{
    struct input_dev *p_input_dev;
    struct work_struct work;
};






static unsigned char g_prox_reg_data[D_ADDR_MAX];
static unsigned char g_ALS_reg_data[D_ADDR_MAX];


static unsigned char  g_nv_prox_data[D_ADDR_MAX];
static unsigned char  g_nv_prox_filter_ratio = 0;
static unsigned short g_nv_prox_meas_cycle = 0;


static unsigned char  g_nv_ALS_data[D_ADDR_MAX];
static unsigned char  g_nv_ALS_filter_ratio = 0;
static unsigned short g_nv_ALS_meas_cycle = 0;


static long g_prox_count_value = D_MEAS_NOT_COMP;
static long g_ALS_count_value  = D_MEAS_NOT_COMP;


static unsigned long g_prox_detect_state = D_PROX_DETECT_STATE_NON_DETECT;


static int g_is_prox_nv_set = D_FALSE;
static int g_is_ALS_nv_set  = D_FALSE;


static int g_prox_active = D_DEACTIVE;
static int g_ALS_active  = D_DEACTIVE;


static int g_diag_mode = D_MODE_DIAG_OFF;


static int g_is_diag_set = D_FALSE;


static int g_prox_start_req_count = 0;
static int g_ALS_start_req_count  = 0;


static int g_RANGE_mode = E_RANGE_MODE_1;

static int g_meas_comp_RANGE_mode = E_RANGE_MODE_1;


static E_STATE_TYPE g_state = E_STATE_STOP;

static wait_queue_head_t g_meas_start_queue;
static wait_queue_head_t g_diag_set_queue;

static spinlock_t sense_data_spin_lock;

static struct i2c_client *this_client;





static int prox_start( E_EVENT_TYPE* );
static int ALS_start ( E_EVENT_TYPE* );
static int prox_stop ( E_EVENT_TYPE* );
static int ALS_stop  ( E_EVENT_TYPE* );
static int prox_meas ( E_EVENT_TYPE* );
static int ALS_meas  ( E_EVENT_TYPE* );
static int meas_stop ( E_EVENT_TYPE* );





const int state_check_table[D_PROX_ACTIVE_KIND_NUM][D_ALS_ACTIVE_KIND_NUM] = {
                    
{   E_STATE_STOP, E_STATE_ALS },
{   E_STATE_PROX, E_STATE_ALT },
};

typedef int (*state_transition_func )(E_EVENT_TYPE*);


state_transition_func state_proc[E_EVENT_MAX][E_STATE_MAX] = {
{   prox_start,   prox_start,   prox_start,   prox_start},
{   NULL,         prox_stop,    NULL,         prox_stop },
{   ALS_start,    ALS_start,    ALS_start,    ALS_start },
{   NULL,         NULL,         ALS_stop,     ALS_stop  },
{   meas_stop,    prox_meas,    ALS_meas,     ALS_meas  },
{   meas_stop,    prox_meas,    ALS_meas,     prox_meas },
{   meas_stop,    prox_meas,    ALS_meas,     prox_meas }
};


const int res_sleep_table[D_RES_TABLE_NUM][D_MODE_KIND_NUM] = {
            
{    100, 200},
{     25,  50},
{      7,  13},
{      2,   4},
{      0,   0},
{      0,   0},
{      0,   0},
{      0,   0},
};









static int i2c_rx_data(char *p_rxData, int length)
{
    int            ret    = 0;
    struct i2c_msg msgs[] =
    {
        {
            .addr = this_client->addr,
            .flags = 0,
            .len = 1,
            .buf = p_rxData,
        },
        {
            .addr = this_client->addr,
            .flags = I2C_M_RD,
            .len = length,
            .buf = p_rxData,
        },
    };
    

    
    if (i2c_transfer(this_client->adapter, msgs, 2) < 0)
    {
        printk(KERN_ERR "GP2AP012A00F i2c_rx_data: transfer error.\n");
        ret = -EIO;
    }
    

    
    return ret;
}






static int i2c_tx_data(char *p_txData, int length)
{
    int            ret   = 0;
    struct i2c_msg msg[] =
    {
        {
            .addr = this_client->addr,
            .flags = 0,
            .len = length,
            .buf = p_txData,
        },
    };
    
    if (i2c_transfer(this_client->adapter, msg, 1) < 0)
    {
        printk(KERN_ERR "GP2AP012A00F i2c_tx_data: transfer error.\n");
        ret = -EIO;
    }
    
    return ret;
}






static void soft_reset(void)
{
    int           ret = 0;
    unsigned char data[D_DATA_SIZE_2BYTE];
    
    memset( data, 0x0, D_DATA_SIZE_2BYTE );
    
    
    data[0] = D_ADDR_COMMAND_3;
    
    
    data[1] = D_DATA_BIT_RST;
    
    ret = i2c_tx_data( data, D_DATA_SIZE_2BYTE );
    
    mdelay( 1 );
    
    return;
}






static int prox_register_setting( void )
{
    int ret  = 0;
    int addr = 0;
    unsigned char data[D_DATA_SIZE_2BYTE];
    
    memset( data, 0x0, D_DATA_SIZE_2BYTE );
    
    
    memset( g_prox_reg_data, 0x0, D_ADDR_MAX );
    
    spin_lock( &sense_data_spin_lock );
    
    for( addr = 0; addr < D_ADDR_MAX; addr++ )
    {
        if( addr != D_ADDR_DATA_LSB && addr != D_ADDR_DATA_MSB )
        {
            g_prox_reg_data[addr] = g_nv_prox_data[addr];
        }
        else
        {
            g_prox_reg_data[addr] = 0;
        }
    }
    spin_unlock( &sense_data_spin_lock );
    
    
    for( addr = D_ADDR_MAX - 1; addr >= 0; addr-- )
    {
        if( addr != D_ADDR_DATA_LSB && addr != D_ADDR_DATA_MSB )
        {
            data[0] = addr;
            data[1] = g_prox_reg_data[addr];
            
            ret = i2c_tx_data( data, D_DATA_SIZE_2BYTE );
            
            if( ret != 0 )
            {
                printk( KERN_ERR "GP2AP012A00F i2c err!! prox_register_setting :prox addr(0x%02X).\n", addr );
                break;
            }
        }
    }
    return ret;
}






static int ALS_register_setting( void )
{
    int ret  = 0;
    int addr = 0;
    unsigned char data[D_DATA_SIZE_2BYTE];
    
    memset( data, 0x0, D_DATA_SIZE_2BYTE );
    
    
    memset( g_ALS_reg_data, 0x0, D_ADDR_MAX );
    
    spin_lock( &sense_data_spin_lock );
    
    for( addr = 0; addr < D_ADDR_MAX; addr++ )
    {
        if( addr != D_ADDR_DATA_LSB && addr != D_ADDR_DATA_MSB )
        {
            g_ALS_reg_data[addr] = g_nv_ALS_data[addr];
        }
        else
        {
            g_ALS_reg_data[addr] = 0;
        }
    }
    
    
    g_ALS_reg_data[D_ADDR_COMMAND_2] = 0;
    
    
    g_ALS_reg_data[D_ADDR_COMMAND_2] |= D_DATA_BIT_RES0;
    
    
    if( g_RANGE_mode == E_RANGE_MODE_2 )
    {
        
        g_ALS_reg_data[D_ADDR_COMMAND_2] |= ( D_DATA_BIT_RANGE3 );
    }
    else if( g_RANGE_mode == E_RANGE_MODE_3 )
    {
        
        g_ALS_reg_data[D_ADDR_COMMAND_2] |= ( D_DATA_BIT_RANGE );
    }
    else        
    {
        
        g_ALS_reg_data[D_ADDR_COMMAND_2] |= ( D_DATA_BIT_VE239 );
    }
    
    spin_unlock( &sense_data_spin_lock );
    
    
    for( addr = D_ADDR_MAX - 1; addr >= 0; addr-- )
    {
        if( addr != D_ADDR_DATA_LSB && addr != D_ADDR_DATA_MSB )
        {
            data[0] = addr;
            data[1] = g_ALS_reg_data[addr];
            
            ret = i2c_tx_data( data, D_DATA_SIZE_2BYTE );
            
            if( ret != 0 )
            {
                printk( KERN_ERR "GP2AP012A00F i2c err!! ALS_register_setting :ALS addr(0x%02X).\n", addr );
                break;
            }
        }
    }
    return ret;
}






static int exec_state_proc ( E_EVENT_TYPE *event, E_STATE_TYPE *state )
{
    int ret = 0;
    state_transition_func func;
    
    func = state_proc[*event][*state];
    if( func != NULL )
    {
        ret = (*func)(event);
    }
    
    return ret;
}






static int get_register( unsigned char addr, unsigned char* pval, int len )
{
    int ret = 0;
    

    
    
    pval[0] = addr;
    
    ret = i2c_rx_data( pval, len );
    

    
    return ret;
}






static int set_register( unsigned char addr, unsigned char val )
{
    int ret = 0;
    unsigned char data[D_DATA_SIZE_2BYTE];
    
    memset( data, 0x0, D_DATA_SIZE_2BYTE );
    
    
    data[0] = addr;
    
    
    data[1] = val;
    
    ret = i2c_tx_data( data, D_DATA_SIZE_2BYTE );
    
    return ret;
}






static int register_ctrl( int mode, int cmd, unsigned long arg )
{
    int ret = 0;
    void __user *argp = (void __user *)arg;
    T_GP2AP012A00F_IOCTL_REG ioctl_data;
    unsigned char data[D_DATA_SIZE_2BYTE];
    
    memset( &ioctl_data, 0x0, sizeof(T_GP2AP012A00F_IOCTL_REG) );
    memset( data, 0x0, D_DATA_SIZE_2BYTE );
    
    if( copy_from_user( &ioctl_data, argp, sizeof(T_GP2AP012A00F_IOCTL_REG)) )
    {
        printk( KERN_ERR "GP2AP012A00F register_ctrl: copy_from_user() Err!!\n" );
        return -EFAULT;
    }
    
    
    if( ( cmd == D_IOCTL_PROX_SET_REG ) || ( cmd == D_IOCTL_LIGHT_SET_REG ) )
    {
        if( g_diag_mode != D_MODE_DIAG_ON )
        {
            printk(KERN_ERR "GP2AP012A00F register_ctrl: Diag mode not ON.\n");
            return -EPERM;
        }
        
        ret = set_register( ioctl_data.address, (unsigned char)ioctl_data.data );
        if( ret != 0 )
        {
            printk(KERN_ERR "GP2AP012A00F register_ctrl: Can't set register data.\n");
        }
        else
        {
            if( (ioctl_data.address != D_ADDR_DATA_LSB) && (ioctl_data.address != D_ADDR_DATA_MSB) )
            {
                
                if( mode == D_MODE_PROX )
                {
                    g_prox_reg_data[ioctl_data.address] = (unsigned char)ioctl_data.data;
                }
                else
                {
                    g_ALS_reg_data[ioctl_data.address] = (unsigned char)ioctl_data.data;
                }
            }
            

        }
    }
    else 
    {
        ret = get_register( ioctl_data.address, (unsigned char*)data, D_DATA_SIZE_2BYTE );
        if( ret != 0 )
        {
            printk(KERN_ERR "GP2AP012A00F register_ctrl: Can't get register data.\n");
        }
        else
        {
            ioctl_data.data = (((unsigned long)data[0]) & 0x000000FF);
            if( copy_to_user(argp, &ioctl_data, sizeof(T_GP2AP012A00F_IOCTL_REG)) )
            {
                printk( KERN_ERR "GP2AP012A00F register_ctrl copy_to_user() Err!!\n" );
                ret = -EFAULT;
            }
            


            
            if( (ioctl_data.address != D_ADDR_DATA_LSB) && (ioctl_data.address != D_ADDR_DATA_MSB) )
            {
                
                if( mode == D_MODE_PROX )
                {
                    g_prox_reg_data[ioctl_data.address] = (unsigned char)ioctl_data.data;
                }
                else
                {
                    g_ALS_reg_data[ioctl_data.address] = (unsigned char)ioctl_data.data;
                }
            }
        }
    }
    
    return ret;
}






static int prox_start( E_EVENT_TYPE *p_event )
{
    int ret = 0;
    
    spin_lock( &sense_data_spin_lock );
    
    
    g_prox_start_req_count++;
    
    
    g_prox_active = D_ACTIVE;
    
    
    g_state = state_check_table[g_prox_active][g_ALS_active];
    
    spin_unlock( &sense_data_spin_lock );
    
    wake_up( &g_meas_start_queue );
    
    return ret;
}






static int ALS_start( E_EVENT_TYPE *p_event )
{
    int ret = 0;
    
    spin_lock( &sense_data_spin_lock );
    
    
    g_ALS_start_req_count++;
    
    
    g_ALS_active = D_ACTIVE;
    
    
    g_state = state_check_table[g_prox_active][g_ALS_active];
    
    spin_unlock( &sense_data_spin_lock );
    
    wake_up( &g_meas_start_queue );
    
    return ret;
}






static int prox_stop( E_EVENT_TYPE *p_event )
{
    int ret = 0;
    
    spin_lock( &sense_data_spin_lock );
    
    
    g_prox_start_req_count--;
    
    if( g_prox_start_req_count <= 0 )
    {
        g_prox_start_req_count = 0;
        
        
        g_prox_active = D_DEACTIVE;
        
        
        g_prox_count_value = D_MEAS_NOT_COMP;
        g_prox_detect_state = D_PROX_DETECT_STATE_NON_DETECT;
        
        
        g_state = state_check_table[g_prox_active][g_ALS_active];
    }
    
    spin_unlock( &sense_data_spin_lock );
    
    return ret;
}






static int ALS_stop( E_EVENT_TYPE *p_event )
{
    int ret = 0;
    
    spin_lock( &sense_data_spin_lock );
    
    
    g_ALS_start_req_count--;
    
    if( g_ALS_start_req_count <= 0 )
    {
        g_ALS_start_req_count = 0;
        
        
        g_ALS_active = D_DEACTIVE;
        
        
        g_ALS_count_value = D_MEAS_NOT_COMP;
        
        
        g_state = state_check_table[g_prox_active][g_ALS_active];
    }
    
    spin_unlock( &sense_data_spin_lock );
    
    return ret;
}






static int get_sensor_data( int mode, unsigned long arg )
{
    int ret = 0;
    int cnt = 0;
    void __user *argp = (void __user *)arg;
    T_GP2AP012A00F_IOCTL_SENSOR sensor_data;
    
    memset( &sensor_data, 0x0, sizeof(T_GP2AP012A00F_IOCTL_SENSOR) );
    
    spin_lock( &sense_data_spin_lock );
        
    if( g_is_prox_nv_set == D_FALSE || g_is_ALS_nv_set == D_FALSE )
    {
        spin_unlock( &sense_data_spin_lock );
        
        
        printk(KERN_ERR "GP2AP012A00F get_sensor_data: Not set prox NV.\n");
        return -EAGAIN;
    }
    
    if( mode == D_MODE_PROX )
    {
        if( g_prox_count_value == D_MEAS_NOT_COMP )
        {
            
            spin_unlock( &sense_data_spin_lock );
            return -EBUSY;
        }
        else
        {
            
            sensor_data.data = g_prox_count_value;
        }
        
        
        for( cnt = 0; cnt < D_ADDR_MAX; cnt++ )
        {
            sensor_data.reg_data[cnt] = g_prox_reg_data[cnt];
        }
        
        
        sensor_data.detect_state = g_prox_detect_state;
    }
    else
    {
        if( g_ALS_count_value == D_MEAS_NOT_COMP )
        {
            
            spin_unlock( &sense_data_spin_lock );
            return -EBUSY;
        }
        else
        {
            
            sensor_data.data = g_ALS_count_value;
        }
        
        
        for( cnt = 0; cnt < D_ADDR_MAX; cnt++ )
        {
            sensor_data.reg_data[cnt] = g_ALS_reg_data[cnt];
        }
               
        
        sensor_data.reg_data[D_ADDR_COMMAND_2] &= ~( D_DATA_BIT_RANGE );
        
        
        if( g_meas_comp_RANGE_mode == E_RANGE_MODE_1 )
        {
            
            sensor_data.reg_data[D_ADDR_COMMAND_2] |= ( D_DATA_BIT_VE239 );
        }
        else if( g_meas_comp_RANGE_mode == E_RANGE_MODE_2 )
        {
            
            sensor_data.reg_data[D_ADDR_COMMAND_2] |= ( D_DATA_BIT_RANGE3 );
        }
        else        
        {
            
            sensor_data.reg_data[D_ADDR_COMMAND_2] |= ( D_DATA_BIT_RANGE );
        }
    }
    
    spin_unlock( &sense_data_spin_lock );
    
    if( copy_to_user(argp, &sensor_data, sizeof(T_GP2AP012A00F_IOCTL_SENSOR)) )
    {
        printk( KERN_ERR "GP2AP012A00F get_sensor_data copy_to_user() Err!!\n" );
        ret = -EFAULT;
    }
    
    return ret;
}






static int set_nv_data( int mode, unsigned long arg )
{
    int ret  = 0;
    int addr = 0;
    void __user *argp = (void __user *)arg;
    T_GP2AP012A00F_IOCTL_NV nv_data;
    

    
    memset( &nv_data, 0x0, sizeof(T_GP2AP012A00F_IOCTL_NV) );
    
    if( copy_from_user( &nv_data, argp, sizeof(T_GP2AP012A00F_IOCTL_NV) ) )
    {
        printk( KERN_ERR "GP2AP012A00F set_nv_data: copy_from_user() Err!!\n" );
        return -EFAULT;
    }
    
    spin_lock( &sense_data_spin_lock );
    
    if( mode == D_MODE_PROX )
    {
        
        for( addr = 0; addr < D_ADDR_MAX; addr++ )
        {
            if( addr != D_ADDR_DATA_LSB && addr != D_ADDR_DATA_MSB )
            {
                g_nv_prox_data[addr] = (unsigned char)(nv_data.nv_reg[addr]);
            }
        }
        
        g_nv_prox_filter_ratio = (unsigned char)(nv_data.nv_filter_ratio);
        
        g_nv_prox_meas_cycle = (unsigned short)(nv_data.nv_meas_cycle);
        
        if( g_is_prox_nv_set == D_FALSE )
        {
            g_is_prox_nv_set = D_TRUE;
            spin_unlock( &sense_data_spin_lock );
            wake_up( &g_meas_start_queue );
        }
        else
        {
            spin_unlock( &sense_data_spin_lock );
        }
    }
    else
    {
        
        for( addr = 0; addr < D_ADDR_MAX; addr++ )
        {
            if( addr != D_ADDR_DATA_LSB && addr != D_ADDR_DATA_MSB )
            {
                g_nv_ALS_data[addr] = (unsigned char)(nv_data.nv_reg[addr]);
            }
        }
        
        g_nv_ALS_filter_ratio = (unsigned char)(nv_data.nv_filter_ratio);
        
        g_nv_ALS_meas_cycle = (unsigned short)(nv_data.nv_meas_cycle);

        if( g_is_ALS_nv_set == D_FALSE )
        {
            g_is_ALS_nv_set = D_TRUE;
            spin_unlock( &sense_data_spin_lock );
            wake_up( &g_meas_start_queue );
        }
        else
        {
            spin_unlock( &sense_data_spin_lock );
        }
    }


























    

    
    return ret;
}






static int get_nv_data( int mode, unsigned long arg )
{
    int ret  = 0;
    int addr = 0;
    void __user *argp = (void __user *)arg;
    T_GP2AP012A00F_IOCTL_NV nv_data;
    

    
    spin_lock( &sense_data_spin_lock );
    
    if( g_is_prox_nv_set == D_FALSE || g_is_ALS_nv_set == D_FALSE )
    {
        spin_unlock( &sense_data_spin_lock );
        
        
        printk(KERN_ERR "GP2AP012A00F get_sensor_data: Not set prox NV.\n");
        return -EAGAIN;
    }
    
    if( mode == D_MODE_PROX )
    {
        
        for( addr = 0; addr < D_ADDR_MAX; addr++ )
        {
            nv_data.nv_reg[addr] = ((unsigned long)g_nv_prox_data[addr]) & 0x000000FF;
        }
        
        nv_data.nv_filter_ratio = ((unsigned long)g_nv_prox_filter_ratio) & 0x000000FF;
        
        nv_data.nv_meas_cycle = ((unsigned long)g_nv_prox_meas_cycle) & 0x0000FFFF;
    }
    else 
    {
        
        for( addr = 0; addr < D_ADDR_MAX; addr++ )
        {
            nv_data.nv_reg[addr]  = ((unsigned long)g_nv_ALS_data[addr])  & 0x000000FF;
        }
        
        nv_data.nv_filter_ratio  = ((unsigned long)g_nv_ALS_filter_ratio)  & 0x000000FF;
        
        nv_data.nv_meas_cycle = ((unsigned long)g_nv_ALS_meas_cycle) & 0x0000FFFF;
    }
    spin_unlock( &sense_data_spin_lock );
    
    if( copy_to_user(argp, &nv_data, sizeof(T_GP2AP012A00F_IOCTL_NV)) )
    {
        printk( KERN_ERR "GP2AP012A00F get_nv_data copy_to_user() Err!!\n" );
        ret = -EFAULT;
    }
    

























    

    
    return ret;
}






static int set_diag_mode( int mode, unsigned long arg )
{
    int  ret      = 0;
    long wait_ret = 0;
    void __user *argp = (void __user *)arg;
    unsigned long  req_diag_mode = 0;
    
    if( copy_from_user( &req_diag_mode, argp, sizeof(unsigned long) ) )
    {
        printk( KERN_ERR "GP2AP012A00F set_diag_mode: copy_from_user() Err!!\n" );
        return -EFAULT;
    }
    
    if( req_diag_mode == D_MODE_DIAG_ON ) 
    {
        spin_lock( &sense_data_spin_lock );
        if( g_diag_mode == D_MODE_DIAG_ON )
        {
            
            spin_unlock( &sense_data_spin_lock );
            printk(KERN_ERR "GP2AP012A00F set_diag_mode: Already diag mode ON.\n");
            return -EPERM;
        }
        
        
        g_diag_mode = D_MODE_DIAG_ON;
        g_is_diag_set = D_TRUE;
        
        spin_unlock( &sense_data_spin_lock );
        
        wake_up( &g_meas_start_queue );
        
        
        wait_ret = wait_event_timeout( g_diag_set_queue, g_is_diag_set != D_TRUE, HZ * 2 );
        if( wait_ret == 0 )
        {
            
            spin_lock( &sense_data_spin_lock );
            
            g_diag_mode = D_MODE_DIAG_OFF;
            spin_unlock( &sense_data_spin_lock );
            
            return -ETIME;
        }
        
        
        soft_reset();
        
        
        if( mode == D_MODE_PROX )
        {
            ret = prox_register_setting();
            if( ret < 0 )
            {
                
                spin_lock( &sense_data_spin_lock );
                
                g_diag_mode = D_MODE_DIAG_OFF;
                spin_unlock( &sense_data_spin_lock );
                
                printk(KERN_ERR "GP2AP012A00F set_diag_mode: prox_register_setting err.\n");
                return -EIO;
            }
        }
        else
        {
            ret = ALS_register_setting();
            if( ret < 0 )
            {
                
                spin_lock( &sense_data_spin_lock );
                
                g_diag_mode = D_MODE_DIAG_OFF;
                spin_unlock( &sense_data_spin_lock );
                
                printk(KERN_ERR "GP2AP012A00F set_diag_mode: ALS_register_setting err.\n");
                return -EIO;
            }
        }
    }
    else 
    {
        spin_lock( &sense_data_spin_lock );
        
        
        g_diag_mode = D_MODE_DIAG_OFF;
        
        
        g_prox_count_value = D_MEAS_NOT_COMP;
        g_ALS_count_value  = D_MEAS_NOT_COMP;
        g_prox_detect_state = D_PROX_DETECT_STATE_NON_DETECT;
        
        spin_unlock( &sense_data_spin_lock );
        wake_up( &g_meas_start_queue );
    }
    return ret;
}






static int gp2ap012a00f_prox_open(struct inode *inode, struct file *file)
{
    
    return 0;
}






static int gp2ap012a00f_prox_release(struct inode *inode, struct file *file)
{
    
    return 0;
}






static int
gp2ap012a00f_prox_ioctl(struct inode *inode, struct file *file, unsigned int cmd,
       unsigned long arg)
{
    int ret = -EINVAL;
    int mode           = D_MODE_PROX;
    E_EVENT_TYPE event = E_EVENT_WAKEUP;
    E_STATE_TYPE state = E_STATE_STOP;

    switch( cmd )
    {
        case D_IOCTL_PROX_GET_REG:
            
        case D_IOCTL_PROX_SET_REG:
            ret = register_ctrl( mode, cmd, arg );
            break;
            
        case D_IOCTL_PROX_MEAS_START:
            event = E_EVENT_PROX_START;
            spin_lock( &sense_data_spin_lock );
            state = g_state;
            spin_unlock( &sense_data_spin_lock );
            ret = exec_state_proc( &event, &state );
            break;

        case D_IOCTL_PROX_MEAS_STOP:
            event = E_EVENT_PROX_STOP;
            spin_lock( &sense_data_spin_lock );
            state = g_state;
            spin_unlock( &sense_data_spin_lock );
            ret = exec_state_proc( &event, &state );
            break;

        case D_IOCTL_PROX_GET_SENSOR_DATA:
            ret = get_sensor_data( mode, arg );
            break;

        case D_IOCTL_PROX_SET_NV:
            ret = set_nv_data( mode, arg );
            break;

        case D_IOCTL_PROX_GET_NV:
            ret = get_nv_data( mode, arg );
            break;

        case D_IOCTL_PROX_SET_DIAG_MODE:
            ret = set_diag_mode( mode, arg );
            break;

        default:
            
            break;
    }

    return ret;
}






static int gp2ap012a00f_light_open(struct inode *inode, struct file *file)
{
    
    return 0;
}






static int gp2ap012a00f_light_release(struct inode *inode, struct file *file)
{
    
    return 0;
}






static int
gp2ap012a00f_light_ioctl(struct inode *inode, struct file *file, unsigned int cmd,
       unsigned long arg)
{
    int ret            = -EINVAL;
    int mode           = D_MODE_ALS;
    E_EVENT_TYPE event = E_EVENT_WAKEUP;
    E_STATE_TYPE state = E_STATE_STOP;

    switch( cmd )
    {
        case D_IOCTL_LIGHT_GET_REG:
            
        case D_IOCTL_LIGHT_SET_REG:
            ret = register_ctrl( mode, cmd, arg );
            break;

        case D_IOCTL_LIGHT_MEAS_START:
            event = E_EVENT_ALS_START;
            spin_lock( &sense_data_spin_lock );
            state = g_state;
            spin_unlock( &sense_data_spin_lock );
            ret = exec_state_proc( &event, &state );
            break;

        case D_IOCTL_LIGHT_MEAS_STOP:
            event = E_EVENT_ALS_STOP;
            spin_lock( &sense_data_spin_lock );
            state = g_state;
            spin_unlock( &sense_data_spin_lock );
            ret = exec_state_proc( &event, &state );
            break;

        case D_IOCTL_LIGHT_GET_SENSOR_DATA:
            ret = get_sensor_data( mode, arg );
            break;

        case D_IOCTL_LIGHT_SET_NV:
            ret = set_nv_data( mode, arg );
            break;

        case D_IOCTL_LIGHT_GET_NV:
            ret = get_nv_data( mode, arg );
            break;

        case D_IOCTL_LIGHT_SET_DIAG_MODE:
            ret = set_diag_mode( mode, arg );
            break;

        default:
            
            break;
        }

    return ret;
}






static unsigned long calc_meas_val( unsigned long *meas_data )
{
    int cnt                    = 0;
    int first                  = 0;
    unsigned long lowest_data  = 0;
    unsigned long highest_data = 0;
    unsigned long lowest_no    = 0;
    unsigned long highest_no   = 0;
    unsigned long count_value  = 0;

    
    for( cnt = 0; cnt < D_MEAS_NUM; cnt++ )
    {
        if( cnt == 0 )
        {
            lowest_data = meas_data[cnt];
            lowest_no = cnt;
        }
        else
        {
            if( lowest_data > meas_data[cnt] )
            {
                lowest_data = meas_data[cnt];
                lowest_no = cnt;
            }
        }
    }

    
    for( cnt = 0; cnt < D_MEAS_NUM; cnt++ )
    {
        if( cnt == lowest_no )
        {
            continue;
        }

        if( first == 0 )
        {
            highest_data = meas_data[cnt];
            highest_no = cnt;
            first = 1;
        }
        else
        {
            if( highest_data < meas_data[cnt] )
            {
                highest_data = meas_data[cnt];
                highest_no = cnt;
            }
        }
    }
    
    
    for( cnt = 0; cnt < D_MEAS_NUM; cnt++ )
    {
        if( cnt != highest_no && cnt != lowest_no )
        {
            count_value += meas_data[cnt];
        }
    }
    
    count_value /= D_MEAS_AVE_NUM;
    
    return count_value;
}






static void res_sleep( int mode, unsigned char res )
{
    unsigned int wait_time = 0;
    
    wait_time = res_sleep_table[res][mode];
    
    if( wait_time != 0 )
    {
        msleep( wait_time );
    }
    
    return;
}






static void meas_cycle_sleep( int mode, struct timeval start_time, struct timeval end_time )
{
    unsigned int   diff_sec_time  = 0;
    unsigned int   diff_usec_time = 0;
    unsigned int   pass_time      = 0;
    int            sleep_time     = 0;
    
    
    start_time.tv_sec &= 0xFFFF;
    end_time.tv_sec &= 0xFFFF;
    
    if( end_time.tv_sec < start_time.tv_sec )
    {
        diff_sec_time = end_time.tv_sec + (0xFFFF - start_time.tv_sec + 1);
    }
    else
    {
        diff_sec_time = end_time.tv_sec - start_time.tv_sec;
    }
    
    if( end_time.tv_usec < start_time.tv_usec )
    {
        diff_usec_time = end_time.tv_usec + (1000000 - start_time.tv_usec);
        diff_sec_time--;
    }
    else
    {
        diff_usec_time = end_time.tv_usec - start_time.tv_usec;
    }
    
    pass_time = diff_sec_time * 1000 + diff_usec_time / 1000;
    
    if( mode == D_MODE_PROX )
    {
        sleep_time = (int)(g_nv_prox_meas_cycle - pass_time);
    }
    else
    {
        sleep_time = (int)(g_nv_ALS_meas_cycle - pass_time);
    }
    
    if( sleep_time > 0 )
    {
        msleep( (unsigned int)sleep_time );
    }
    
    return;
}





static int prox_meas( E_EVENT_TYPE *p_event )
{
    int ret                       = 0;
    int meas_cnt                  = 0;
    unsigned long  get_data       = 0;
    unsigned char  res            = 0;
    unsigned short high_threshold = 0;
    unsigned short low_threshold  = 0;
    struct timeval start_time;
    struct timeval end_time;
    unsigned char  data[D_DATA_SIZE_2BYTE];
    unsigned long  meas_data[D_MEAS_NUM];
    
    memset( &start_time, 0x0, sizeof(struct timeval) );
    memset( &end_time, 0x0, sizeof(struct timeval) );
    memset( data, 0x0, D_DATA_SIZE_2BYTE );
    memset( meas_data, 0x0, sizeof(unsigned long) * D_MEAS_NUM );
    
    
    do_gettimeofday( &start_time );
    
    
    if( p_event == NULL )
    {
        printk( KERN_ERR "GP2AP012A00F prox_meas : input err.\n" );
        return -1;
    }
    
    if( *p_event != E_EVENT_PROX_COMP )
    {
        
        pm_obs_a_sensor(PM_OBS_SENSOR_KINSETSU_ON);
    }
    
    
    soft_reset();
    
    
    ret = prox_register_setting();
    if( ret != 0 )
    {
        printk( KERN_ERR "GP2AP012A00F prox_meas : prox_register_setting err.\n" );
    }
    
    for( meas_cnt = 0 ; meas_cnt < D_MEAS_NUM ; meas_cnt++ )
    {
        if( g_diag_mode == D_MODE_DIAG_ON )
        {
            
            return 0;
        }
        
        
        g_prox_reg_data[D_ADDR_COMMAND_1] |= ( D_DATA_BIT_OP3 );
        
        data[0] = D_ADDR_COMMAND_1;
        data[1] = g_prox_reg_data[D_ADDR_COMMAND_1];
        
        ret = i2c_tx_data( data, D_DATA_SIZE_2BYTE );
        if( ret != 0 )
        {
            printk( KERN_ERR "GP2AP012A00F prox_meas : i2c_tx_data err.\n" );
        }
        
        
        res = (g_prox_reg_data[D_ADDR_COMMAND_2] & D_DATA_BIT_RES) >> D_DATA_BIT_SHIFT_NUM_RES0;
        res_sleep( D_MODE_PROX, res );
        
        
        while( 1 )
        {
            ret = get_register( D_ADDR_COMMAND_1, data, D_DATA_SIZE_2BYTE );
            
            if( ret != 0 )
            {
                printk( KERN_ERR "GP2AP012A00F prox_meas : get OP3 register err.\n" );
                return ret;
            }
            
            if( ( data[0] & D_DATA_BIT_OP3 ) == 0 )
            {
                g_prox_reg_data[D_ADDR_COMMAND_1] = data[0];
                break;
            }
        }
        
        memset( data, 0x0, D_DATA_SIZE_2BYTE );
        
        
        ret = get_register( D_ADDR_DATA_LSB, data, D_DATA_SIZE_2BYTE );
        if( ret != 0 )
        {
            printk( KERN_ERR "GP2AP012A00F prox_meas : get LSB data err.\n" );
            return ret;
        }
        
        get_data = ( ((unsigned long)data[0]) & 0x000000FF );
        get_data |= ( ( ((unsigned long)data[1]) << 8 ) & 0x0000FF00 );
        
        meas_data[meas_cnt] = get_data;
    }
    
    spin_lock( &sense_data_spin_lock );
    
    g_prox_count_value = calc_meas_val( meas_data );
    
    low_threshold  = (unsigned short)( g_prox_reg_data[D_ADDR_INT_LT_LSB] | ( g_prox_reg_data[D_ADDR_INT_LT_MSB] << 8 ) );
    high_threshold = (unsigned short)( g_prox_reg_data[D_ADDR_INT_HT_LSB] | ( g_prox_reg_data[D_ADDR_INT_HT_MSB] << 8 ) );
    
    
    if( (unsigned short)g_prox_count_value < low_threshold ) 
    {
        g_prox_detect_state = D_PROX_DETECT_STATE_NON_DETECT;
    }
    else if( (unsigned short)g_prox_count_value > high_threshold ) 
    {
        g_prox_detect_state = D_PROX_DETECT_STATE_DETECT;
    }
    else 
    {
        
    }
    spin_unlock( &sense_data_spin_lock );
    
    
    do_gettimeofday(&end_time);
    
    
    meas_cycle_sleep( D_MODE_PROX, start_time, end_time );
    
    
    *p_event = E_EVENT_PROX_COMP;
    
    return 0;
}






static int ALS_meas( E_EVENT_TYPE *p_event )
{
    
    int            ret        = 0;
    int            meas_cnt   = 0;
    unsigned long  get_data   = 0;
    unsigned char  res        = 0;
    struct timeval start_time;
    struct timeval end_time;
    unsigned char  data[D_DATA_SIZE_2BYTE];
    unsigned long  meas_data[D_MEAS_NUM];
    
    memset( &start_time, 0x0, sizeof(struct timeval) );
    memset( &end_time, 0x0, sizeof(struct timeval) );
    memset( data, 0x0, D_DATA_SIZE_2BYTE );
    memset( meas_data, 0x0, sizeof(unsigned long)* D_MEAS_NUM );
    
    
    do_gettimeofday( &start_time );
    
    
    if( p_event == NULL )
    {
        printk( KERN_ERR "GP2AP012A00F ALS_meas : input err.\n" );
        return -1;
    }
    
    if( *p_event != E_EVENT_ALS_COMP )
    {
        
        pm_obs_a_sensor(PM_OBS_SENSOR_SYOUDO_ON);
    }
    
    soft_reset();
    
    
    ret = ALS_register_setting();
    if( ret != 0 )
    {
        printk( KERN_ERR "GP2AP012A00F ALS_meas : ALS_register_setting err.\n" );
    }
    
    for( meas_cnt = 0 ; meas_cnt < D_MEAS_NUM ; meas_cnt++ )
    {
        if( g_diag_mode == D_MODE_DIAG_ON )
        {
            
            return 0;
        }
        
        
        g_ALS_reg_data[D_ADDR_COMMAND_1] |= ( D_DATA_BIT_OP3 );
        
        data[0] = D_ADDR_COMMAND_1;
        data[1] = g_ALS_reg_data[D_ADDR_COMMAND_1];
        
        ret = i2c_tx_data( data, D_DATA_SIZE_2BYTE );
        
        if( ret != 0 )
        {
            printk( KERN_ERR "GP2AP012A00F ALS_meas : i2c_tx_data.\n" );
        }
        
        
        res = (g_ALS_reg_data[D_ADDR_COMMAND_2] & D_DATA_BIT_RES) >> D_DATA_BIT_SHIFT_NUM_RES0;
        res_sleep( D_MODE_ALS, res );
        
        
        while( 1 )
        {
            ret = get_register( D_ADDR_COMMAND_1, data, D_DATA_SIZE_2BYTE );
            
            if( ret != 0 )
            {
                printk( KERN_ERR "GP2AP012A00F ALS_meas : get OP3 register.\n" );
                return ret;
            }
            
            if( ( data[0] & D_DATA_BIT_OP3 ) == 0 )
            {
                g_ALS_reg_data[D_ADDR_COMMAND_1] = data[0];
                break;
            }
        }
        
        memset( data, 0x0, D_DATA_SIZE_2BYTE );
        
        ret = get_register( D_ADDR_DATA_LSB, data, D_DATA_SIZE_2BYTE );
        if( ret != 0 )
        {
            printk( KERN_ERR "GP2AP012A00F ALS_meas : get LSB data err.\n" );
            return ret;
        }
        
        get_data = ( ((unsigned long)data[0]) & 0x000000FF );
        get_data |= ( ( ((unsigned long)data[1]) << 8 ) & 0x0000FF00 );
        
        meas_data[meas_cnt] = get_data;
    }
    
    spin_lock( &sense_data_spin_lock );
    
    g_ALS_count_value = calc_meas_val( meas_data );
    
    
    g_meas_comp_RANGE_mode = g_RANGE_mode;
    
    spin_unlock( &sense_data_spin_lock );
    
    
    if( ( g_RANGE_mode == E_RANGE_MODE_1 && g_ALS_count_value >= D_RANGE_MODE_HIGH_1_TH ) ||
        ( g_RANGE_mode == E_RANGE_MODE_2 && g_ALS_count_value >= D_RANGE_MODE_HIGH_2_TH ) )
    {
        g_RANGE_mode++;
    }
    else if( ( g_RANGE_mode == E_RANGE_MODE_2 && g_ALS_count_value <= D_RANGE_MODE_LOW_2_TH ) || 
             ( g_RANGE_mode == E_RANGE_MODE_3 && g_ALS_count_value <= D_RANGE_MODE_LOW_3_TH ) )
    {
        g_RANGE_mode--;
    }
    else
    {
        
    }
    
    
    do_gettimeofday(&end_time);
    
    
    meas_cycle_sleep( D_MODE_ALS, start_time, end_time );
    
    
    *p_event = E_EVENT_ALS_COMP;
    
    return 0;
}






static int meas_stop( E_EVENT_TYPE *p_event )
{
    
    return 0;
}






static int gp2ap012a00f_poll_thread( void* param )
{
    int ret              = 0;
    E_EVENT_TYPE event   = E_EVENT_WAKEUP;
    E_STATE_TYPE state   = E_STATE_STOP;
    int dummy_wait       = 0;
    wait_queue_head_t dummy_queue;
    

    
    init_waitqueue_head( &dummy_queue );
    
    
    wait_event( g_meas_start_queue, ( g_is_prox_nv_set != FALSE )&&( g_is_ALS_nv_set != FALSE ));
    
    while( 1 )
    {
        
        spin_lock( &sense_data_spin_lock );
        state = g_state;
        spin_unlock( &sense_data_spin_lock );
        
        if( ( state == E_STATE_STOP )&&( g_diag_mode == D_MODE_DIAG_OFF ) )
        {
            
            pm_obs_a_sensor(PM_OBS_SENSOR_OFF);
            
            spin_lock( &sense_data_spin_lock );
            
            g_prox_count_value = D_MEAS_NOT_COMP;
            g_prox_detect_state = D_PROX_DETECT_STATE_NON_DETECT;
            g_ALS_count_value = D_MEAS_NOT_COMP;
            spin_unlock( &sense_data_spin_lock );
            
            
            wait_event( g_meas_start_queue, ( ( g_state != E_STATE_STOP )||( g_diag_mode != D_MODE_DIAG_OFF ) ) );
            
            spin_lock( &sense_data_spin_lock );
            state = g_state;
            spin_unlock( &sense_data_spin_lock );
            
            event = E_EVENT_WAKEUP;
        }
        
        if( g_diag_mode == D_MODE_DIAG_ON )
        {
            
            pm_obs_a_sensor(PM_OBS_SENSOR_OFF);
            g_is_diag_set = D_FALSE;
            wake_up( &g_diag_set_queue);
            
            wait_event( g_meas_start_queue, g_diag_mode != D_MODE_DIAG_ON );
            spin_lock( &sense_data_spin_lock );
            state = g_state;
            spin_unlock( &sense_data_spin_lock );
            event = E_EVENT_WAKEUP;
        }
        
        ret = exec_state_proc( &event, &state );
        if( ret != 0 )
        {
            
            wait_event_timeout( dummy_queue, dummy_wait != 0, HZ );
        }
    }
    return 0;
}






static void gp2ap012a00f_work_func(struct work_struct *work)
{
    
    return;
}






static int gp2ap012a00f_init_client(struct i2c_client *client)
{
    struct gp2ap012a00f_data *data;
    
    data = i2c_get_clientdata(client);
    
    spin_lock_init( &sense_data_spin_lock );
    
    return 0;
}






static struct file_operations gp2ap012a00f_prox_fops = {
    .owner   = THIS_MODULE,
    .open    = gp2ap012a00f_prox_open,
    .release = gp2ap012a00f_prox_release,
    .ioctl   = gp2ap012a00f_prox_ioctl,
};


static struct miscdevice gp2ap012a00f_prox_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name  = "prox_sensor",
    .fops  = &gp2ap012a00f_prox_fops,
};



static struct file_operations gp2ap012a00f_light_fops = {
    .owner   = THIS_MODULE,
    .open    = gp2ap012a00f_light_open,
    .release = gp2ap012a00f_light_release,
    .ioctl   = gp2ap012a00f_light_ioctl,
};


static struct miscdevice gp2ap012a00f_light_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name  = "light_sensor",
    .fops  = &gp2ap012a00f_light_fops,
};






static int __devinit gp2ap012a00f_probe(struct i2c_client *client,
                   const struct i2c_device_id *id)
{
    int err;
    struct gp2ap012a00f_data *data;
    struct task_struct *th;
    
    data = kzalloc(sizeof(struct gp2ap012a00f_data), GFP_KERNEL);
    if (!data) {
        err = -ENOMEM;
        goto exit;
    }
    
    INIT_WORK(&data->work, gp2ap012a00f_work_func);
    i2c_set_clientdata(client, data);
    
    
    err = gp2ap012a00f_init_client(client);
    if (err)
    {
        goto exit_kfree;
    }
    this_client = client;
    
    
    pm_obs_a_sensor(PM_OBS_SENSOR_OFF);
    
    
    err = misc_register(&gp2ap012a00f_prox_device);
    if (err)
    {
        printk(KERN_ERR
               "gp2ap012a00f_probe: gp2ap012a00f prox register failed.\n");
        goto exit_kfree;
    }
    
    
    err = misc_register(&gp2ap012a00f_light_device);
    if (err)
    {
        misc_deregister(&gp2ap012a00f_prox_device);
        printk(KERN_ERR
               "gp2ap012a00f_probe: gp2ap012a00f light register failed.\n");
        goto exit_kfree;
    }
    
    
    th = kthread_create(gp2ap012a00f_poll_thread, NULL, "sensor_poll");
    if(IS_ERR(th) )
    {
        misc_deregister(&gp2ap012a00f_prox_device);
        misc_deregister(&gp2ap012a00f_light_device);
        
        printk(KERN_ERR
               "gp2ap012a00f_probe: Can't create thread.\n");
        goto exit_kfree;
    }
    else
    {
        wake_up_process(th);
    }
    
    return 0;
    
exit_kfree:
    kfree(data);
exit:
    return err;
}






static int __devexit gp2ap012a00f_remove(struct i2c_client *client)
{
    misc_deregister(&gp2ap012a00f_prox_device);
    misc_deregister(&gp2ap012a00f_light_device);
    i2c_release_client(client);
    
    kfree(i2c_get_clientdata(client));
    
    return 0;
}






static int gp2ap012a00f_suspend(struct i2c_client *client, pm_message_t mesg)
{
    
    return 0;
}






static int gp2ap012a00f_resume(struct i2c_client *client)
{
    
    return 0;
}





static const struct i2c_device_id gp2ap012a00f_id[] = {
    { "gp2ap012a00f", 0 },
    { }
};


static struct i2c_driver gp2ap012a00f_driver = {
    .probe   = gp2ap012a00f_probe,
    .remove  = gp2ap012a00f_remove,
    .suspend = gp2ap012a00f_suspend,
    .resume  = gp2ap012a00f_resume,
    .id_table = gp2ap012a00f_id,
    .driver = {
           .name = "gp2ap012a00f",
           },
};






static int __init gp2ap012a00f_init(void)
{
    int ret = 0;
    
    
    init_waitqueue_head( &g_meas_start_queue );
    init_waitqueue_head( &g_diag_set_queue );
    memset( &g_prox_reg_data, 0, sizeof(unsigned char) * D_ADDR_MAX );
    memset( &g_ALS_reg_data, 0, sizeof(unsigned char) * D_ADDR_MAX );
    memset( &g_nv_prox_data, 0, sizeof(unsigned char) * D_ADDR_MAX );
    memset( &g_nv_ALS_data, 0, sizeof(unsigned char) * D_ADDR_MAX );
    
    printk(KERN_INFO "gp2ap012a00f_init: " GP2AP012A00F_DRV_NAME " driver ver." DRIVER_VERSION "\n" );
    
    
    ret = i2c_add_driver(&gp2ap012a00f_driver);
    
    return ret;
}






static void __exit gp2ap012a00f_exit(void)
{
    i2c_del_driver(&gp2ap012a00f_driver);
}


MODULE_AUTHOR("NEC Communication Systems Co.,Ltd");
MODULE_DESCRIPTION("GP2AP012A00F driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

module_init(gp2ap012a00f_init);
module_exit(gp2ap012a00f_exit);

