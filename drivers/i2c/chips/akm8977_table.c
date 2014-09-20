/**********************************************************************
* File Name: drivers/i2c/chips/akm8977_table.c
* 
* (C) NEC CASIO Mobile Communications, Ltd. 2011
**********************************************************************/







#include <linux/akm8977_table.h>
#include <linux/akm8977.h>

extern int et_pedometerOFF(void);           
extern int et_pedometerON(void);            
extern int et_VE306(void);       
extern int et_VE307(void);        
extern int et_startMeasureCONT(void);       
extern int et_powerDown(void);              
extern int et_ignore(void);                 

extern int AKM_get_state(int state);        


const REGISTER_STATE_ST event_table[STATE_MAX][EVENT_MAX] =
{
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_VE307,           ms : et_startMeasureCONT, nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_pedometerON,  slct2 : et_VE307,           ms : et_startMeasureCONT, nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_VE306,           ms : et_powerDown,        nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,  ms : et_ignore,           nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,  ms : et_ignore,           nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_pedometerON,  slct2 : et_ignore,           ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_pedometerOFF, slct2 : et_ignore,           ms : et_powerDown,        nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_pedometerOFF, slct2 : et_ignore,           ms : et_powerDown,        nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_pedometerOFF, slct2 : et_ignore,           ms : et_powerDown,        nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_pedometerOFF, slct2 : et_ignore,  ms : et_ignore,           nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_pedometerOFF, slct2 : et_VE307,  ms : et_ignore,           nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_pedometerOFF, slct2 : et_ignore,           ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_VE307,  ms : et_startMeasureCONT, nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_powerDown,        nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore, ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore, ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_VE307,  ms : et_startMeasureCONT, nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_pedometerON,  slct2 : et_ignore,           ms : et_startMeasureCONT, nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_pedometerON,  slct2 : et_ignore,           ms : et_startMeasureCONT, nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_powerDown,        nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_pedometerON,  slct2 : et_ignore, ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_pedometerON,  slct2 : et_ignore, ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_VE307,  ms : et_startMeasureCONT, nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_powerDown,        nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_VE307,  ms : et_startMeasureCONT, nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_pedometerON,  slct2 : et_ignore,           ms : et_startMeasureCONT, nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_pedometerON,  slct2 : et_ignore,           ms : et_startMeasureCONT, nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_powerDown,        nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_pedometerON,  slct2 : et_VE306, ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_pedometerON,  slct2 : et_VE306, ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_VE307,  ms : et_startMeasureCONT, nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE8__POWEROFF_PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE4__POWEROFF_PEDOOFF_VE284__VE252, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE0__POWEROFF_PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_powerDown,        nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE9__VE123____PEDOOFF_VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE5__VE123____PEDOOFF_VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_ignore,           nextState : STATE1__VE122___PEDOOFF_VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_VE307,  ms : et_startMeasureCONT, nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE10_POWEROFF_PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE6__POWEROFF_PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE12_POWEROFF_PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_pedometerON,  slct2 : et_ignore,           ms : et_startMeasureCONT, nextState : STATE2__POWEROFF_PEDOON__VE283_VE252, },
    },
                
    {
  { slct1 : et_ignore,       slct2 : et_VE306, ms : et_powerDown,        nextState : STATE14_POWEROFF_PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE11_VE123____PEDOON__VE283_SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE7__VE123____PEDOON__VE284__SPKOFF, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE13_VE123____PEDOOFF_VE284__SPKON_, },
  { slct1 : et_ignore,       slct2 : et_ignore,           ms : et_ignore,           nextState : STATE15_VE123____PEDOON__VE284__SPKON_, },
  { slct1 : et_pedometerON,  slct2 : et_VE306, ms : et_ignore,           nextState : STATE3__VE122___PEDOON__VE283_VE252, },
    },
};

const REGISTER_ST state_table[STATE_MAX] =
{
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_OFF },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_ON , slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_ON , slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_OFF },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_ON , ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_OFF },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_ON , ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_OFF },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_ON , ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_OFF },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_ON , ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_OFF },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_ON , ms_mode : MS_MODE_ON  },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_OFF, ms_mode : MS_MODE_OFF },
   { slct1_peen : SLCT1_PEEN_OFF, slct2_VE304 : SLCT2_LFEN_ON , ms_mode : MS_MODE_ON  },
};
