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

    modflag_init(&mf_led_green_toggle, 10000.0,  0.5);
    modflag_init(&mf_led_red_toggle, 10000.0,  1);
    modflag_init(&mf_led_blue_toggle, 10000.0,  2);
    /*GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, GRN_LED, GRN_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, BLU_LED, BLU_LED);*/
}

void task_toggle_green_led(MODFLAGTIMER *thismf)
    {
    if (thismf->flag && thismf->init_done)
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

void task_toggle_red_led(MODFLAGTIMER *thismf)
    {
    if (thismf->flag && thismf->init_done)
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

void task_toggle_blue_led(MODFLAGTIMER *thismf)
    {
    if (thismf->flag && thismf->init_done)
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

