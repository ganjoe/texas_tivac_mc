/*
 * pwm_led.h
 *
 *  Created on: 22.02.2022
 *      Author: pymd02
 */

#ifndef DIGITAL_IO_PWM_LED_H_
#define DIGITAL_IO_PWM_LED_H_

#include "main.h"

struct PWMLEDS;

typedef struct PWMLEDS
{
    int flaginit;
    void (*freq)(uint32_t,struct PWMLEDS *pwmled);// set freq 700..300.000
    void (*red)(float,struct PWMLEDS *pwmled);   // set dutycycle -1..1
    void (*green)(float,struct PWMLEDS *pwmled); // set dutycycle -1..1
    void (*blue)(float,struct PWMLEDS *pwmled); // set dutycycle -1..1
}PWMLED;

extern PWMLED pwmled;

void _pwmLedInit(PWMLED *pwmled);
void _pwmLedFreq(uint32_t freq, PWMLED *pwmled);
void _pwmLedDutyGreen(float duty, PWMLED *pwmled);
void _pwmLedDutyRed(float duty, PWMLED *pwmled);
void _pwmLedDutyBlue(float duty, PWMLED *pwmled);



#endif /* DIGITAL_IO_PWM_LED_H_ */
