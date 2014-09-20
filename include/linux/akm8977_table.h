/**********************************************************************
* File Name: include/linux/akm8977_table.h
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/







#ifndef AKM8977_TABLE_H_
#define AKM8977_TABLE_H_

#define TABLE_REG   3

#define SLCT1_PEEN_OFF          0x00
#define SLCT1_PEEN_ON           0x04
#define SLCT2_LFEN_OFF          0x00
#define SLCT2_LFEN_ON           0x08
#define MS_MODE_OFF             0x00
#define MS_MODE_ON              0x02


typedef enum _EVENT_NUM
{
    EVENT_POWER_OFF = 0,
    EVENT_POWER_ON,
    EVENT_VIB_OFF,
    EVENT_VIB_ON,
    EVENT_SPK_OFF,
    EVENT_SPK_ON,
    EVENT_PEDO_OFF,
    EVENT_PEDO_ON,
    EVENT_TIMEOUT,
    EVENT_MAX,
    EVENT_NONE = (-1),
}EVENT_NUM;

typedef enum _STATE_NUM
{
    STATE0__POWEROFF_PEDOOFF_VE283_VE252 = 0,
    STATE1__VE122___PEDOOFF_VE283_VE252,
    STATE2__POWEROFF_PEDOON__VE283_VE252,
    STATE3__VE122___PEDOON__VE283_VE252,
    STATE4__POWEROFF_PEDOOFF_VE284__VE252,
    STATE5__VE123____PEDOOFF_VE284__SPKOFF,
    STATE6__POWEROFF_PEDOON__VE284__SPKOFF,
    STATE7__VE123____PEDOON__VE284__SPKOFF,
    STATE8__POWEROFF_PEDOOFF_VE283_SPKON_,
    STATE9__VE123____PEDOOFF_VE283_SPKON_,
    STATE10_POWEROFF_PEDOON__VE283_SPKON_,
    STATE11_VE123____PEDOON__VE283_SPKON_,
    STATE12_POWEROFF_PEDOOFF_VE284__SPKON_,
    STATE13_VE123____PEDOOFF_VE284__SPKON_,
    STATE14_POWEROFF_PEDOON__VE284__SPKON_,
    STATE15_VE123____PEDOON__VE284__SPKON_,
    STATE_MAX,
    STATE_NONE = (-1),
}STATE_NUM;

typedef struct register_state_tag
{
    int (*slct1)(void);
    int (*slct2)(void);
    int (*ms)(void);
    int nextState;
} REGISTER_STATE_ST;

typedef struct register_tag
{
    int slct1_peen;
    int slct2_VE304;
    int ms_mode;
} REGISTER_ST;

extern const REGISTER_STATE_ST event_table[STATE_MAX][EVENT_MAX];
extern const REGISTER_ST state_table[STATE_MAX];

#endif 
