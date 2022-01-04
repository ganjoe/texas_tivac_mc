/*
 * datatypes_tasks.c
 *
 *  Created on: 10.09.2020
 *      Author: daniel
 */

#include "main.h"

MODFLAGTIMER mf_global_systick;

void mf_timerinit(int hz)
{

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, 6600);
    MAP_IntEnable(INT_TIMER0A);
    MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerEnable(TIMER0_BASE, TIMER_A);
}

void modflag_init(MODFLAGTIMER *thismf, float systick, float setpoint_hz)
    {
    utils_truncate_number(&setpoint_hz, 0, systick); // max 1h minimum: systick
    thismf->freq = systick;
    thismf->divisor = systick / setpoint_hz;
    if (setpoint_hz==0)
        {
        thismf->init_done = false;
        }
    else
        {
        thismf->init_done = true;
        }
    }

void modflag_upd_regular(MODFLAGTIMER *thismf)
    {
    if (thismf->init_done)
    {
    thismf->counter++;
    if (!(thismf->counter % thismf->divisor))
        {
        thismf->flag = true;
       // thismf->counter = false;
        }
    }
    }

void Timer0IntHandler(void)
{
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    ++mf_global_systick.ovf;

    modflag_upd_regular(&mf_led_green_toggle);
    modflag_upd_regular(&mf_led_red_toggle);
    modflag_upd_regular(&mf_led_blue_toggle);

    MAP_IntMasterEnable();
}



uint64_t modflag_tickdiff(MODFLAGTIMER *cnt)
    {
    uint32_t counter = MAP_TimerValueGet(TIMER0_BASE, TIMER_A);
    cnt->ovf = mf_global_systick.ovf;

    cnt->systick = counter + (cnt->ovf * 0xFFFF);
    cnt->newtick = cnt->systick;
    cnt->tickdiff = cnt->newtick - cnt->oldtick;
    cnt->oldtick = cnt->newtick;
    return cnt->tickdiff;
    }
void modflag_enable(MODFLAGTIMER *thismf)
    {
    thismf->init_done = true;
    }

void modflag_disable(MODFLAGTIMER *thismf)
{
thismf->init_done = false;
}
