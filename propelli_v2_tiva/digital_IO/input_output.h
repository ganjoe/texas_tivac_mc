/*
 * input_output.h
 *
 *  Created on: 21.02.2022
 *      Author: pymd02
 */

#ifndef DIGITAL_IO_INPUT_OUTPUT_H_
#define DIGITAL_IO_INPUT_OUTPUT_H_

#include "main.h"

struct sPINS;

typedef struct sPINS
    {
    int flaginit, state;
    uint32_t sysctr;    //Peripheral zum enablen
    uint32_t ui32Port;
    uint8_t ui8Pins;
    int (*get)(struct sPINS *pin);
    void (*set)(struct sPINS *pin, int state);
    void (*strobe)(struct sPINS *pin);
    int (*toggle)(struct sPINS *pin);
    void (*setInput)(struct sPINS *pin);
    void (*setOutput)(struct sPINS *pin);
    }tPINS;

void pinsetup();

void _PeripheralEnable(tPINS *thispin);

void _pinSetOutput(struct sPINS *pin);
//void _pinSetPullup(struct sPINS *pin, int state);
void _pinSetInput(struct sPINS *pin);
void _pinSet(struct sPINS *pin, int state);
int _pinGet(struct sPINS *pin);
int _pinToggle(struct sPINS *pin);


extern tPINS led_green, led_red, led_blue, testpin;

#endif /* DIGITAL_IO_INPUT_OUTPUT_H_ */
