/*
 * datatypes_tasks.c
 *
 *  Created on: 10.09.2020
 *      Author: daniel
 */

#include "main.h"

MODFLAG mf_systick;

void mf_timerinit(uint32_t hz, MODFLAG *thismf)
{

    uint32_t timerclock = 80000000; //in Hz
    uint32_t timertop;
    timertop= timerclock / hz /2;
    thismf->freq = (float)hz;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, timertop);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void modflag_init(MODFLAG *thismf, MODFLAG systick, float setpoint_hz)
    {
    utils_truncate_number(&setpoint_hz, 0, systick.freq);

    thismf->freq = systick.freq;
    thismf->divisor = thismf->freq / setpoint_hz;
    if (setpoint_hz==0)
        {
        thismf->init_done = false;
        }
    else
        {
        thismf->init_done = true;
        }
    }

void modflag_upd_regular(MODFLAG *thismf)
    {
    if (thismf->init_done)
        {
        thismf->counter++;
        if (!(thismf->counter % thismf->divisor))
            {
            thismf->flag++;
            }
        }
    else
        {
        thismf->flag = 0;
        }
    }

void Timer0IntHandler(void)
{
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    ++mf_systick.ovf;

    pintoggle(&testpin);
    modflag_upd_regular(&mf_led_green_toggle);
    modflag_upd_regular(&mf_led_red_toggle);
    modflag_upd_regular(&mf_led_blue_toggle);

    mc_task();

  //  task_toggle_blue_led(&mf_led_blue_toggle);
   // task_toggle_red_led(&mf_led_red_toggle);
   // task_toggle_green_led(&mf_led_green_toggle);

    MAP_IntMasterEnable();
}



uint64_t modflag_tickdiff(MODFLAG *cnt)
    {
    uint32_t counter = MAP_TimerValueGet(TIMER0_BASE, TIMER_A);
    cnt->ovf = mf_systick.ovf;

    cnt->systick = counter + (cnt->ovf * 0xFFFF);
    cnt->newtick = cnt->systick;
    cnt->tickdiff = cnt->newtick - cnt->oldtick;
    cnt->oldtick = cnt->newtick;
    return cnt->tickdiff;
    }
void modflag_enable(MODFLAG *thismf)
    {
    thismf->init_done = true;
    }

void modflag_disable(MODFLAG *thismf)
{
thismf->init_done = false;
}
