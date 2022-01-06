/*
 * board_led.c
 *
 *  Created on: 04.01.2022
 *      Author: pymd02
 */

#include "board_led.h"
#include "modflagtimer/modflagtimer.h"



void mfinit_boardled()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GRN_LED);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, BLU_LED);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, TESTPIN);

    modflag_init(&mf_led_green_toggle, mf_systick,  0.25);
    modflag_init(&mf_led_red_toggle, mf_systick,  1);
    modflag_init(&mf_led_blue_toggle, mf_systick,  0.5);
    /*GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, GRN_LED, GRN_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, BLU_LED, BLU_LED);*/
}

void toggle_testpin(MODFLAG *thismf)
    {
        if (thismf->rampcounter)
            {
            GPIOPinWrite(GPIO_PORTF_BASE, TESTPIN, TESTPIN);
            thismf->rampcounter = 0;
            }
        else
            {
            GPIOPinWrite(GPIO_PORTF_BASE, TESTPIN, 0);
            thismf->rampcounter = 1;
            }
    }

void task_toggle_green_led(MODFLAG *thismf)
    {
    if (thismf->flag)
        {
        thismf->repeat = modflag_tickdiff(thismf);
        if (thismf->rampcounter)
            {
            GPIOPinWrite(GPIO_PORTF_BASE, GRN_LED, GRN_LED);
            thismf->rampcounter = 0;
            }
        else
            {
            GPIOPinWrite(GPIO_PORTF_BASE, GRN_LED, 0);
            thismf->rampcounter = 1;
            }
        thismf->duration = modflag_tickdiff(thismf);
        thismf->flag = false;
        }
    }

void task_toggle_red_led(MODFLAG *thismf)
    {
    if (thismf->flag)
        {
        thismf->repeat = modflag_tickdiff(thismf);
        if (thismf->rampcounter)
            {
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
            thismf->rampcounter = 0;
            }
        else
            {
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0);
            thismf->rampcounter = 1;
            }
        thismf->duration = modflag_tickdiff(thismf);
        thismf->flag = false;
        }
    }

void task_toggle_blue_led(MODFLAG *thismf)
    {
    if (thismf->flag)
        {
        thismf->repeat = modflag_tickdiff(thismf);
        if (thismf->rampcounter)
            {
            GPIOPinWrite(GPIO_PORTF_BASE, BLU_LED, BLU_LED);
            thismf->rampcounter = 0;
            }
        else
            {
            GPIOPinWrite(GPIO_PORTF_BASE, BLU_LED, 0);
            thismf->rampcounter = 1;
            }
        thismf->duration = modflag_tickdiff(thismf);
        thismf->flag = false;
        }
    }

void toggle_blue_led()
    {
    if (GPIOPinRead(GPIO_PORTF_BASE, BLU_LED))
        {
        GPIOPinWrite(GPIO_PORTF_BASE, BLU_LED, 0);
        }
    else
        {
        GPIOPinWrite(GPIO_PORTF_BASE, BLU_LED, BLU_LED);
        }
    }
