/*
 * input_output.c
 *
 *  Created on: 21.02.2022
 *      Author: pymd02
 */
#include "input_output.h"
#include "driverlib/gpio.h"
PINS led_red = {
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_1,

                };

PINS led_blue = {
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_2,

                };

PINS led_green = {
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_3,

                };

PINS testpin = {
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_4,
                };

void pinsetup()
    {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
   //  pinIsOutput(&led_blue);
   //  pinIsOutput(&led_green);
    // pinIsOutput(&led_red);
    }

void pinset(PINS *thispin, int state)
    {
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
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
        GPIOPinWrite(thispin->ui32Port, thispin->ui8Pins, 1);
        return 1;
        }
}

void pinIsOutput(PINS *thispin)
    {
    GPIOPinTypeGPIOOutput(thispin->ui32Port, thispin->ui8Pins);
    }

void pinIsInput(PINS *thispin)
    {
    GPIOPinTypeGPIOInput(thispin->ui32Port, thispin->ui8Pins);
    }
