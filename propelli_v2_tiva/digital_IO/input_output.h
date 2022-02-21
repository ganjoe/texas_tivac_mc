/*
 * input_output.h
 *
 *  Created on: 21.02.2022
 *      Author: pymd02
 */

#ifndef DIGITAL_IO_INPUT_OUTPUT_H_
#define DIGITAL_IO_INPUT_OUTPUT_H_

#include "main.h"


typedef struct
{
    uint32_t ui32Port;
    uint8_t ui8Pins;
    //void (*GPIOPinTypeGPIOOutput)(uint32_t,uint8_t);
    //void (*GPIOPinTypeGPIOInput)(uint32_t,uint8_t);
}PINS;

void pinsetup();

void pinIsOutput(PINS thispin);
void pinIsPullup(PINS thispin, int state);
void pinIsInput(PINS thispin);

void pinset(PINS thispin, int state);
int pinget(PINS thispin);
int pintoggle(PINS thispin);

extern PINS led_green, led_red, led_blue, testpin;

#endif /* DIGITAL_IO_INPUT_OUTPUT_H_ */
