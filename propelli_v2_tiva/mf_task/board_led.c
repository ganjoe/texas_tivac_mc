/*
 * board_led.c
 *
 *  Created on: 04.01.2022
 *      Author: pymd02
 */

#include "board_led.h"
#include "digital_IO/input_output.h"
#include "modflagtimer/modflagtimer.h"



void mfinit_boardled()
{

    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_GREEN);
   // GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED);
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_BLUE);
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, TESTPIN);

    modflag_init(&mf_led_green_toggle, mf_systick,  0.25);
    modflag_init(&mf_led_red_toggle, mf_systick,  1);
    modflag_init(&mf_led_blue_toggle, mf_systick,  0.5);
    /*GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, GRN_LED, GRN_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, BLU_LED, BLU_LED);*/
}


void toggle_testpin(MODFLAG *thismf)
    {
    if (thismf->flag)
        {
        thismf->repeat = modflag_tickdiff(thismf);
        pintoggle(&testpin);
        thismf->duration = modflag_tickdiff(thismf);
        thismf->flag = false;
        }
    }

void task_toggle_green_led(MODFLAG *thismf)
    {
    if (thismf->flag)
        {
        thismf->repeat = modflag_tickdiff(thismf);
        pintoggle(&led_green);
        thismf->duration = modflag_tickdiff(thismf);
        thismf->flag = false;
        }
    }

void task_toggle_red_led(MODFLAG *thismf)
    {
    if (thismf->flag)
        {
        thismf->repeat = modflag_tickdiff(thismf);
        pintoggle(&led_red);
        thismf->duration = modflag_tickdiff(thismf);
        thismf->flag = false;
        }
    }

void task_toggle_blue_led(MODFLAG *thismf)
    {
    if (thismf->flag)
        {
        thismf->repeat = modflag_tickdiff(thismf);
        pintoggle(&led_blue);
        thismf->duration = modflag_tickdiff(thismf);
        thismf->flag = false;
        }
    }

