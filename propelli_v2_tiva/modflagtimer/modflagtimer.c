/*
 * modflagtimer.c
 *
 *  Created on: 04.01.2022
 *      Author: pymd02
 */

#include "main.h"
#include "modflagtimer.h"

void mf_timerinit()
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, MAP_SysCtlClockGet());
    MAP_IntEnable(INT_TIMER0A);
    MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerEnable(TIMER0_BASE, TIMER_A);
}

void Timer0IntHandler(void)
{
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    UARTprintf("t");

    MAP_IntMasterEnable();
}
