/*
 * pwm_led.h
 *
 *  Created on: 22.02.2022
 *      Author: pymd02
 */

#ifndef MC_PWM_LED_H_
#define MC_PWM_LED_H_

#include "main.h"

typedef struct
{
    float red, blue, green;
    uint32_t freq;
    int flaginit;
}PWMLED;

extern PWMLED pwmled;

void pwmLedInit(PWMLED *freq);
void pwmLedSetFreq(PWMLED *freq);
void pwmLedSetDuty(PWMLED *duty);



#endif /* MC_PWM_LED_H_ */
