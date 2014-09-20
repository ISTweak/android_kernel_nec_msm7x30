/**********************************************************************
* File Name: include/linux/i2c/gp2ap012a00f.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/



#ifndef GP2AP012A00F_H
#define GP2AP012A00F_H

#include <linux/ioctl.h>


#define D_MODE_DIAG_OFF               (0)
#define D_MODE_DIAG_ON                (1)


#define D_ADDR_COMMAND_1            (0x00)
#define D_ADDR_COMMAND_2            (0x01)
#define D_ADDR_COMMAND_3            (0x02)
#define D_ADDR_DATA_LSB             (0x03)
#define D_ADDR_DATA_MSB             (0x04)
#define D_ADDR_INT_LT_LSB           (0x05)
#define D_ADDR_INT_LT_MSB           (0x06)
#define D_ADDR_INT_HT_LSB           (0x07)
#define D_ADDR_INT_HT_MSB           (0x08)
#define D_ADDR_MAX                  (D_ADDR_INT_HT_MSB + 1)



#define D_DATA_BIT_OP3              (1 << D_DATA_BIT_SHIFT_NUM_OP3)
#define D_DATA_BIT_OP2              (1 << D_DATA_BIT_SHIFT_NUM_OP2)
#define D_DATA_BIT_OP1              (1 << D_DATA_BIT_SHIFT_NUM_OP1)
#define D_DATA_BIT_OP0              (1 << D_DATA_BIT_SHIFT_NUM_OP0)
#define D_DATA_BIT_PROX             (1 << D_DATA_BIT_SHIFT_NUM_PROX)
#define D_DATA_BIT_FLAG             (1 << D_DATA_BIT_SHIFT_NUM_FLAG)
#define D_DATA_BIT_PRST1            (1 << D_DATA_BIT_SHIFT_NUM_PRST1)
#define D_DATA_BIT_PRST0            (1 << D_DATA_BIT_SHIFT_NUM_PRST0)



#define D_DATA_BIT_RES2             (1 << D_DATA_BIT_SHIFT_NUM_RES2)
#define D_DATA_BIT_RES1             (1 << D_DATA_BIT_SHIFT_NUM_RES1)
#define D_DATA_BIT_RES0             (1 << D_DATA_BIT_SHIFT_NUM_RES0)
#define D_DATA_BIT_RANGE3           (1 << D_DATA_BIT_SHIFT_NUM_RANGE3)
#define D_DATA_BIT_RANGE2           (1 << D_DATA_BIT_SHIFT_NUM_RANGE2)
#define D_DATA_BIT_RANGE1           (1 << D_DATA_BIT_SHIFT_NUM_RANGE1)
#define D_DATA_BIT_VE239           (1 << D_DATA_BIT_SHIFT_NUM_VE239)


#define D_DATA_BIT_INTVAL1          (1 << D_DATA_BIT_SHIFT_NUM_INTVAL1)
#define D_DATA_BIT_INTVAL0          (1 << D_DATA_BIT_SHIFT_NUM_INTVAL0)
#define D_DATA_BIT_IS1              (1 << D_DATA_BIT_SHIFT_NUM_IS1)
#define D_DATA_BIT_IS0              (1 << D_DATA_BIT_SHIFT_NUM_IS0)
#define D_DATA_BIT_PIN              (1 << D_DATA_BIT_SHIFT_NUM_PIN)

#define D_DATA_BIT_FREQ             (1 << D_DATA_BIT_SHIFT_NUM_FREQ)
#define D_DATA_BIT_RST              (1 << D_DATA_BIT_SHIFT_NUM_RST)


#define D_DATA_BIT_PRST             ( D_DATA_BIT_PRST1 | D_DATA_BIT_PRST0 )
#define D_DATA_BIT_RES              ( D_DATA_BIT_RES2 | D_DATA_BIT_RES1 | D_DATA_BIT_RES0 )
#define D_DATA_BIT_RANGE            ( D_DATA_BIT_RANGE3 | D_DATA_BIT_RANGE2 | D_DATA_BIT_RANGE1 | D_DATA_BIT_VE239 )
#define D_DATA_BIT_INTVAL           ( D_DATA_BIT_INTVAL1 | D_DATA_BIT_INTVAL0 )
#define D_DATA_BIT_IS               ( D_DATA_BIT_IS1 | D_DATA_BIT_IS0 )


#define D_DATA_BIT_SHIFT_NUM_OP3            (7)
#define D_DATA_BIT_SHIFT_NUM_OP2            (6)
#define D_DATA_BIT_SHIFT_NUM_OP1            (5)
#define D_DATA_BIT_SHIFT_NUM_OP0            (4)
#define D_DATA_BIT_SHIFT_NUM_PROX           (3)
#define D_DATA_BIT_SHIFT_NUM_FLAG           (2)
#define D_DATA_BIT_SHIFT_NUM_PRST1          (1)
#define D_DATA_BIT_SHIFT_NUM_PRST0          (0)



#define D_DATA_BIT_SHIFT_NUM_RES2           (6)
#define D_DATA_BIT_SHIFT_NUM_RES1           (5)
#define D_DATA_BIT_SHIFT_NUM_RES0           (4)
#define D_DATA_BIT_SHIFT_NUM_RANGE3         (3)
#define D_DATA_BIT_SHIFT_NUM_RANGE2         (2)
#define D_DATA_BIT_SHIFT_NUM_RANGE1         (1)
#define D_DATA_BIT_SHIFT_NUM_VE239         (0)


#define D_DATA_BIT_SHIFT_NUM_INTVAL1        (7)
#define D_DATA_BIT_SHIFT_NUM_INTVAL0        (6)
#define D_DATA_BIT_SHIFT_NUM_IS1            (5)
#define D_DATA_BIT_SHIFT_NUM_IS0            (4)
#define D_DATA_BIT_SHIFT_NUM_PIN            (3)

#define D_DATA_BIT_SHIFT_NUM_FREQ           (1)
#define D_DATA_BIT_SHIFT_NUM_RST            (0)


#define D_PROX_DETECT_STATE_NON_DETECT      (0)
#define D_PROX_DETECT_STATE_DETECT          (1)


typedef struct _t_gp2ap012a00f_ioctl_reg
{
    unsigned long address;
    unsigned long data;
}T_GP2AP012A00F_IOCTL_REG;

typedef struct _t_gp2ap012a00f_ioctl_sensor
{
    unsigned long data;
    unsigned long reg_data[D_ADDR_MAX];
    unsigned long detect_state;
}T_GP2AP012A00F_IOCTL_SENSOR;

typedef struct _t_gp2ap012a00f_ioctl_nv
{
    unsigned long nv_reg[D_ADDR_MAX];
    unsigned long nv_filter_ratio;
    unsigned long nv_meas_cycle;
}T_GP2AP012A00F_IOCTL_NV;

struct gp2ap012a00f_platform_data
{
    unsigned long data;
};

#define GP2AP012A00F_IO             'G'

#define D_IOCTL_PROX_GET_REG                _IOWR(GP2AP012A00F_IO, 0x01, T_GP2AP012A00F_IOCTL_REG)      
#define D_IOCTL_PROX_SET_REG                _IOW(GP2AP012A00F_IO, 0x02, T_GP2AP012A00F_IOCTL_REG)       
#define D_IOCTL_PROX_MEAS_START             _IO(GP2AP012A00F_IO, 0x03)                                  
#define D_IOCTL_PROX_MEAS_STOP              _IO(GP2AP012A00F_IO, 0x04)                                  
#define D_IOCTL_PROX_GET_SENSOR_DATA        _IOR(GP2AP012A00F_IO, 0x05, T_GP2AP012A00F_IOCTL_SENSOR)    
#define D_IOCTL_PROX_SET_NV                 _IOW(GP2AP012A00F_IO, 0x06, T_GP2AP012A00F_IOCTL_NV)        
#define D_IOCTL_PROX_GET_NV                 _IOR(GP2AP012A00F_IO, 0x07, T_GP2AP012A00F_IOCTL_NV)        
#define D_IOCTL_PROX_SET_DIAG_MODE          _IOW(GP2AP012A00F_IO, 0x08, unsigned long)

#define D_IOCTL_LIGHT_GET_REG               _IOWR(GP2AP012A00F_IO, 0x21, T_GP2AP012A00F_IOCTL_REG)      
#define D_IOCTL_LIGHT_SET_REG               _IOW(GP2AP012A00F_IO, 0x22, T_GP2AP012A00F_IOCTL_REG)       
#define D_IOCTL_LIGHT_MEAS_START            _IO(GP2AP012A00F_IO, 0x23)                                  
#define D_IOCTL_LIGHT_MEAS_STOP             _IO(GP2AP012A00F_IO, 0x24)                                  
#define D_IOCTL_LIGHT_GET_SENSOR_DATA       _IOR(GP2AP012A00F_IO, 0x25, T_GP2AP012A00F_IOCTL_SENSOR)    
#define D_IOCTL_LIGHT_SET_NV                _IOW(GP2AP012A00F_IO, 0x26, T_GP2AP012A00F_IOCTL_NV)        
#define D_IOCTL_LIGHT_GET_NV                _IOR(GP2AP012A00F_IO, 0x27, T_GP2AP012A00F_IOCTL_NV)        
#define D_IOCTL_LIGHT_SET_DIAG_MODE         _IOW(GP2AP012A00F_IO, 0x28, unsigned long)

typedef enum _e_range_mode
{
    E_RANGE_MODE_1 = 0,
    E_RANGE_MODE_2,
    E_RANGE_MODE_3,
    E_RANGE_MODE_MAX
}E_RANGE_MODE;

#define D_RANGE_MODE_HIGH_1_TH       (0x3E80)
#define D_RANGE_MODE_HIGH_2_TH       (0x3E80)
#define D_RANGE_MODE_LOW_2_TH        (0x05DC)
#define D_RANGE_MODE_LOW_3_TH        (0x04E2)

#endif
