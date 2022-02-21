/*
 * input_output.c
 *
 *  Created on: 21.02.2022
 *      Author: pymd02
 */
#include "input_output.h"
#include "driverlib/gpio.h"

PINS led_red = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_1,

                };

PINS led_blue = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_2,

                };

PINS led_green = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_3,

                };

PINS testpin = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_4,
                };
/*It takes five clock cycles after the write to enable a peripheral before the the peripheral is actually enabled*/
void WaitFiveCycles()
    {
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    }

void PeripheralEnable(PINS *thispin)
{
     if(!thispin->PeripheralEnable)
        {
         SysCtlPeripheralEnable(thispin->sysctr);
         thispin->PeripheralEnable = 1;
         WaitFiveCycles();
        }
}

void pinsetup()
    {
    pinIsOutput(&led_blue);
    pinIsOutput(&led_green);
    pinIsOutput(&led_red);
    }

void pinset(PINS *thispin, int state)
    {
    if (state)
        GPIOPinWrite(thispin->ui32Port, thispin->ui8Pins, thispin->ui8Pins);
    else
        GPIOPinWrite(thispin->ui32Port, thispin->ui8Pins, 0);

    }
int pinget(PINS *thispin)
    {
    return GPIOPinRead(thispin->ui32Port, thispin->ui8Pins);
    }

int pintoggle(PINS *thispin)
{
    if (GPIOPinRead(thispin->ui32Port, thispin->ui8Pins))
        {
        GPIOPinWrite(thispin->ui32Port, thispin->ui8Pins, 0);
        return 0;
        }
    else
        {
        GPIOPinWrite(thispin->ui32Port, thispin->ui8Pins, thispin->ui8Pins);
        return 1;
        }
}

void pinIsOutput(PINS *thispin)
    {
    PeripheralEnable(thispin);
    GPIOPinTypeGPIOOutput(thispin->ui32Port, thispin->ui8Pins);
    }

void pinIsInput(PINS *thispin)
    {
    PeripheralEnable(thispin);
    GPIOPinTypeGPIOInput(thispin->ui32Port, thispin->ui8Pins);
    }
