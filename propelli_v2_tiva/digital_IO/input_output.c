/*
 * input_output.c
 *
 *  Created on: 21.02.2022
 *      Author: pymd02
 */
#include "input_output.h"
#include "driverlib/gpio.h"

tPINS led_red = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_1,
                .setInput = &_pinSetInput,
                .setOutput =&_pinSetOutput,
                .toggle = &_pinToggle,
                //.strobe = &_pinStrobe,
                .set = &_pinSet,
                .get = &_pinGet,
                };

tPINS led_blue = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_2,
                .setInput = &_pinSetInput,
                .setOutput =&_pinSetOutput,
                //.toggle = &_pinSetPullup,
                //.strobe = &_pinStrobe,
                .set = &_pinSet,
                .get = &_pinGet,
                };

tPINS led_green = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_3,
                .setInput = &_pinSetInput,
                .setOutput =&_pinSetOutput,
                //.toggle = &_pinSetPullup,
                //.strobe = &_pinStrobe,
                .set = &_pinSet,
                .get = &_pinGet,
                };

tPINS testpin = {
                .sysctr = SYSCTL_PERIPH_GPIOF,
                .ui32Port = GPIO_PORTF_BASE,
                .ui8Pins = GPIO_PIN_4,
                .setInput = &_pinSetInput,
                .setOutput =&_pinSetOutput,
                //.toggle = &_pinSetPullup,
                //.strobe = &_pinStrobe,
                .set = &_pinSet,
                .get = &_pinGet,
                };


void _PeripheralEnable(tPINS *thispin)
    {
     if(!thispin->flaginit)
        {
         SysCtlPeripheralEnable(thispin->sysctr);
         thispin->flaginit = 1;
         WaitFiveCycles();
        }
    }

void pinsetup()
    {
    led_green.setOutput(&led_green);
    led_red.setOutput(&led_red);
    led_blue.setOutput(&led_blue);
    }

void _pinSet(struct sPINS *pin, int state)
    {
    if (state)
        GPIOPinWrite(pin->ui32Port, pin->ui8Pins, pin->ui8Pins);
    else
        GPIOPinWrite(pin->ui32Port, pin->ui8Pins, 0);

    }

int _pinGet(struct sPINS *pin)
    {
    return GPIOPinRead(pin->ui32Port, pin->ui8Pins);
    }

int _pinToggle(struct sPINS *pin)
{
    if (GPIOPinRead(pin->ui32Port, pin->ui8Pins))
        {
        GPIOPinWrite(pin->ui32Port, pin->ui8Pins, 0);
        return 0;
        }
    else
        {
        GPIOPinWrite(pin->ui32Port, pin->ui8Pins, pin->ui8Pins);
        return 1;
        }
}

void _pinSetOutput(struct sPINS *pin)
    {
    _PeripheralEnable(pin);
    GPIOPinTypeGPIOOutput(pin->ui32Port, pin->ui8Pins);
    }

void _pinSetInput(struct sPINS *pin)
    {
    _PeripheralEnable(pin);
    GPIOPinTypeGPIOInput(pin->ui32Port, pin->ui8Pins);
    }
