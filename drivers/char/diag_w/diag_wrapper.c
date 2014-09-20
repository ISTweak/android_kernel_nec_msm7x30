/*
 * diag_wrapper.c
 *
 * Copyright (C) 2010 NEC NEC Corporation
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/
 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/uaccess.h>
#include <linux/timer.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/rwsem.h>
#include <linux/leds.h>
#include <linux/leds-bd6082gul.h>
#include <linux/ioctl.h>

#include <linux/keypad_cmd.h>
#include <linux/leds_cmd.h>
#include <linux/touch_panel_cmd.h>
#include <linux/diag_wrapper.h>
#include <mach/rpc_server_handset.h>

#include <linux/slab.h>




#define DEVICEWRPPER_NAME       "diag_wrapper"
#define KEY_TIMEOUT     (HZ * 30)






static wait_queue_head_t key_rand_wait;
static wait_queue_head_t touch_cmd_wait;
static int g_rsp_key_data;
touch_diag_result g_rsp_touch_data;
static char g_touch_flg;

static long g_touch_timeout = (HZ * 30);


static int diag_wrapper_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "diag_wrapper_open\n");
    return 0;
}

void diag_keypad_cmd_rand_ctl(void *key_in)
{
    wait_queue_head_t   *wq = &key_rand_wait;
    keypad_cmd_callback_param_keycode *key_type;

    key_type = (keypad_cmd_callback_param_keycode *)key_in;

    g_rsp_key_data = key_type->key_code;

    wake_up(wq);
    return;
}

void diag_touch_panel_cmd_pd_mdcmd(void *par)
{
    wait_queue_head_t   *wq = &touch_cmd_wait;
    touch_diag_result *coord;

    coord = (touch_diag_result *)par;

    memcpy (&g_rsp_touch_data, coord, sizeof (touch_diag_result));
    g_touch_flg = 1;

    wake_up(wq);
    return;
}

static int diag_leds_cmd_ctl(unsigned char red_f,
                             unsigned char grn_f,
                             unsigned char ble_f)
{
    int ret = LEDS_CMD_RET_OK;
    unsigned char ret_val;

    ret_val = leds_cmd(LEDS_CMD_TYPE_RGB_RED, red_f);
    if (ret_val != LEDS_CMD_RET_OK)
    {
        ret = LEDS_CMD_RET_NG;
    }
    ret_val = leds_cmd(LEDS_CMD_TYPE_RGB_GREEN, grn_f);
    if (ret_val != LEDS_CMD_RET_OK)
    {
        ret = LEDS_CMD_RET_NG;
    }
    ret_val = leds_cmd(LEDS_CMD_TYPE_RGB_BLUE, ble_f);
    if (ret_val != LEDS_CMD_RET_OK)
    {
        ret = LEDS_CMD_RET_NG;
    }
    
    return ret;
}

static int diag_wrapper_ioctl(struct inode *inode, struct file *file,
    unsigned int iocmd, unsigned long data)
{
    int ret = DIAG_WRAPPER_IOCTL_OK;
    int led_ret = LEDS_CMD_RET_OK;
    unsigned char ret_val;

    unsigned char touch_finger;
    touch_diag_result *touch_result = NULL;






    int err;
    long    timeout;
    unsigned char *pkt_params = NULL;
    
    int *key_val = NULL;
    int key_mask;
    size_t res_size = sizeof(char);
    size_t req_size = sizeof(char);
    
    
    init_waitqueue_head(&key_rand_wait);
    init_waitqueue_head(&touch_cmd_wait);

    printk(KERN_DEBUG "[diag_wrapper]%s: ioctl Enter (iocmd:0x%02X)\n", __func__,iocmd);
    g_touch_flg = 0;

    switch(iocmd){
    case DIAG_WRAPPER_IOCTL_A01:
        ret_val = keypad_cmd_callback(KEYPAD_CMD_TYPE_GET_KEYCODE, 0, diag_keypad_cmd_rand_ctl);
        if (ret_val != 1)
        {
            ret = 0;
        }
        else
        {
            g_rsp_key_data = 0xff;
            timeout = wait_event_timeout(key_rand_wait, g_rsp_key_data != 0xff, KEY_TIMEOUT);
            if(timeout == 0)
            {
                g_rsp_key_data = 0x00;
                key_mask = 0;
                keypad_cmd(KEYPAD_CMD_TYPE_MASK, &key_mask);
            }
            ret = g_rsp_key_data;
        }
        break;

    case DIAG_WRAPPER_IOCTL_A02:
        key_mask = 1;
        ret = keypad_cmd(KEYPAD_CMD_TYPE_MASK, &key_mask);
        break;

    case DIAG_WRAPPER_IOCTL_A03:
        key_mask = 0;
        ret = keypad_cmd(KEYPAD_CMD_TYPE_MASK, &key_mask);
        break;

    case DIAG_WRAPPER_IOCTL_A04:
        req_size = ( sizeof(int) * 4 );
        key_val = (int*)kmalloc(req_size, GFP_KERNEL);
        if(!key_val)
            return -ENOMEM;

        err = copy_from_user( key_val, (int *)data, req_size );
        if (err) {
            kfree(key_val);
            return DIAG_WRAPPER_IOCTL_NG;
        }
        
        if( key_val[3] == KEY_DIAG_EMULATION_KEY )
            ret = keypad_cmd(KEYPAD_CMD_TYPE_KEY_EMULATION, key_val);
        else if( key_val[3] == KEY_DIAG_EMULATION_HANDSET )
            ret = hs_key_cmd(key_val);
        
        kfree(key_val);
        
        break;

    case DIAG_WRAPPER_IOCTL_B01:
        led_ret = diag_leds_cmd_ctl(1, 0, 0);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B02:
        led_ret = diag_leds_cmd_ctl(0, 1, 0);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B03:
        led_ret = diag_leds_cmd_ctl(0, 0, 1);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B04:
        led_ret = diag_leds_cmd_ctl(1, 1, 0);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B05:
        led_ret = diag_leds_cmd_ctl(1, 0, 1);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B06:
        led_ret = diag_leds_cmd_ctl(0, 1, 1);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B07:
        led_ret = diag_leds_cmd_ctl(1, 1, 1);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B08:
        led_ret = diag_leds_cmd_ctl(0, 0, 0);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_B09:
        led_ret= leds_cmd(LEDS_CMD_TYPE_KEY, 1);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;

    case DIAG_WRAPPER_IOCTL_B10:
        led_ret = leds_cmd(LEDS_CMD_TYPE_KEY, 0);
        if( led_ret != LEDS_CMD_RET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;

    case DIAG_WRAPPER_IOCTL_B11:
        req_size = ( sizeof(char) * 2 );
        pkt_params = (char *)kmalloc(req_size, GFP_KERNEL);
        if( !pkt_params )
            return -ENOMEM;
            
        err = copy_from_user( pkt_params, (unsigned char *)data, req_size );
        if (err) {
            kfree(pkt_params);
            return DIAG_WRAPPER_IOCTL_NG;
        }
        ret = bd6082gul_reg_write(pkt_params[0], pkt_params[1]);
        break;

    case DIAG_WRAPPER_IOCTL_B12:
        ret = bd6082gul_main_lcd_don( BD6082GUL_LED_ON );
        if( ret != BD6082GUL_LED_SET_OK )
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;







    case DIAG_WRAPPER_IOCTL_C01:
        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_RESET, NULL);
        if (ret != 0)
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_C02:
        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_ENTR_SLEEP, NULL);
        if (ret != 0)
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_C03:
        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_EXIT_SLEEP, NULL);
        if (ret != 0)
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_C04:



        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_ENTR_DEEP, NULL);

        if (ret != 0)
            ret = DIAG_WRAPPER_IOCTL_NG;
        break;
        
    case DIAG_WRAPPER_IOCTL_C05:














        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_EXIT_DEEP, NULL);
        if (ret != 0)
            ret = DIAG_WRAPPER_IOCTL_NG;

        break;
        
    case DIAG_WRAPPER_IOCTL_C06:
        res_size = ( sizeof(char) * 3 );
        pkt_params = (char *)kmalloc(res_size, GFP_KERNEL);
        if( !pkt_params )
            return -ENOMEM;
            
        err = copy_from_user( pkt_params, (unsigned char *)data, res_size );
        if (err) {
            kfree(pkt_params);
            return -EINVAL;
        }

        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_GET_REVISION, NULL);
        
        pkt_params[1] = 0x00;
        pkt_params[2] = ret;
        ret = DIAG_WRAPPER_IOCTL_OK;
        
        break;
        

    case DIAG_WRAPPER_IOCTL_C07:
        res_size = ( sizeof(char) * 5 );





        
        pkt_params = (char *)kmalloc(res_size, GFP_KERNEL);
        
        if( !pkt_params )
            return -ENOMEM;
        
        touch_result = (touch_diag_result *)kmalloc(sizeof(touch_diag_result), GFP_KERNEL);
        
        if( !touch_result ){
            kfree(pkt_params);
            return -ENOMEM;
        }
        
        err = copy_from_user( pkt_params, (unsigned char *)data, res_size );
        if (err) {
            kfree(pkt_params);
            kfree(touch_result);
            return -EINVAL;
        }

        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_GET_COORD, touch_result);
        
        touch_finger = pkt_params[1];
        
        pkt_params[1] = touch_result->finger[touch_finger].finger_data_x[0];
        pkt_params[2] = touch_result->finger[touch_finger].finger_data_x[1];
        pkt_params[3] = touch_result->finger[touch_finger].finger_data_y[0];
        pkt_params[4] = touch_result->finger[touch_finger].finger_data_y[1];
























































        kfree(touch_result);
        break;







    case DIAG_WRAPPER_IOCTL_C10:
        res_size = ( sizeof(char) * 2 );
        pkt_params = (char *)kmalloc(res_size, GFP_KERNEL);
        if( !pkt_params )
            return -ENOMEM;
            
        err = copy_from_user( pkt_params, (unsigned char *)data, res_size );
        if (err) {
            kfree(pkt_params);
            return -EINVAL;
        }
        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_FW_UPDATE, NULL);
        pkt_params[1] = ret;
        ret = DIAG_WRAPPER_IOCTL_OK;
        break;
    case DIAG_WRAPPER_IOCTL_C11:
        res_size = ( sizeof(char) * 3 );
        pkt_params = (char *)kmalloc(res_size, GFP_KERNEL);
        if( !pkt_params )
            return -ENOMEM;
            
        err = copy_from_user( pkt_params, (unsigned char *)data, res_size );
        if (err) {
            kfree(pkt_params);
            return -EINVAL;
        }
        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_GET_CHECKSUM, pkt_params);
        pkt_params[1] = (unsigned char)((ret >> 8) & 0xFF);
        pkt_params[2] = (unsigned char)(ret & 0xFF);
        break;


    case DIAG_WRAPPER_IOCTL_C12:
        res_size = ( sizeof(char) * 21 );
        
        pkt_params = (char *)kmalloc(res_size, GFP_KERNEL);
        if( !pkt_params )
            return -ENOMEM;
        
        ret_val = (int)touch_panel_cmd_callback(TOUCH_PANEL_CMD_TYPE_LINE_TEST, 0, diag_touch_panel_cmd_pd_mdcmd);
        if (ret_val != 0)
        {
            ret = -1;
        }
        else
        {
            g_touch_flg = 0;
            timeout = wait_event_timeout(touch_cmd_wait, g_touch_flg != 0, (g_touch_timeout * HZ));
            if(timeout == 0)
            {
                memset(pkt_params, 0xFF, res_size );
                ret = DIAG_WRAPPER_IOCTL_NG;
            } else {
                pkt_params[0]  = g_rsp_touch_data.ret;
                pkt_params[1]  = g_rsp_touch_data.finger[0].finger_data_x[0];
                pkt_params[2]  = g_rsp_touch_data.finger[0].finger_data_x[1];
                pkt_params[3]  = g_rsp_touch_data.finger[0].finger_data_y[0];
                pkt_params[4]  = g_rsp_touch_data.finger[0].finger_data_y[1];
                pkt_params[5]  = g_rsp_touch_data.finger[1].finger_data_x[0];
                pkt_params[6]  = g_rsp_touch_data.finger[1].finger_data_x[1];
                pkt_params[7]  = g_rsp_touch_data.finger[1].finger_data_y[0];
                pkt_params[8]  = g_rsp_touch_data.finger[1].finger_data_y[1];
                pkt_params[9]  = g_rsp_touch_data.finger[2].finger_data_x[0];
                pkt_params[10] = g_rsp_touch_data.finger[2].finger_data_x[1];
                pkt_params[11] = g_rsp_touch_data.finger[2].finger_data_y[0];
                pkt_params[12] = g_rsp_touch_data.finger[2].finger_data_y[1];
                pkt_params[13] = g_rsp_touch_data.finger[3].finger_data_x[0];
                pkt_params[14] = g_rsp_touch_data.finger[3].finger_data_x[1];
                pkt_params[15] = g_rsp_touch_data.finger[3].finger_data_y[0];
                pkt_params[16] = g_rsp_touch_data.finger[3].finger_data_y[1];
                pkt_params[17] = g_rsp_touch_data.finger[4].finger_data_x[0];
                pkt_params[18] = g_rsp_touch_data.finger[4].finger_data_x[1];
                pkt_params[19] = g_rsp_touch_data.finger[4].finger_data_y[0];
                pkt_params[20] = g_rsp_touch_data.finger[4].finger_data_y[1];
























                ret = DIAG_WRAPPER_IOCTL_OK;
            }
        }
        
        break;
    case DIAG_WRAPPER_IOCTL_C13:
        err = copy_from_user( &g_touch_timeout, (unsigned char *)data, sizeof(long) );
        if (err) {
            kfree(pkt_params);
            return -EINVAL;
        }
        break;













    case DIAG_WRAPPER_IOCTL_C16:
        res_size = ( sizeof(char) * 3 );
        pkt_params = (char *)kmalloc(res_size, GFP_KERNEL);
        if( !pkt_params )
            return -ENOMEM;
            
        err = copy_from_user( pkt_params, (unsigned char *)data, res_size );
        if (err) {
            kfree(pkt_params);
            return -EINVAL;
        }

        ret = (int)touch_panel_cmd(TOUCH_PANEL_CMD_TYPE_GET_FW_REVISION, NULL);
        
        if( ret == 0xFF )
            pkt_params[1] = 0x01;
        else
            pkt_params[1] = 0x00;
        
        pkt_params[2] = ret;
        ret = DIAG_WRAPPER_IOCTL_OK;
        break;

    default:
        ret = DIAG_WRAPPER_IOCTL_NG;
        break;
    }
    
    if(pkt_params){
        err = copy_to_user((unsigned char *)data, pkt_params, res_size);
        if (err) {
            ret = -1;
        }
        kfree(pkt_params);
    }
    printk(KERN_DEBUG "[diag_wrapper]%s: ioctl Exit\n", __func__);
    return ret;
}


static const struct file_operations diag_wrapper_fops = {
    .owner      = THIS_MODULE,
    .open       = diag_wrapper_open,
    .ioctl      = diag_wrapper_ioctl,
};

static struct miscdevice diag_wrapper = {
    .fops       = &diag_wrapper_fops,
    .name       = DEVICEWRPPER_NAME,
    .minor      = MISC_DYNAMIC_MINOR,
};

static int __init input_device_wrapper_init(void)
{
	printk(KERN_DEBUG "[diag_wrapper]%s: init Enter\n", __func__);
    return misc_register(&diag_wrapper);
}

static void __exit input_device_wrapper_exit(void)
{
    misc_deregister(&diag_wrapper);
}

module_init(input_device_wrapper_init);
module_exit(input_device_wrapper_exit);


