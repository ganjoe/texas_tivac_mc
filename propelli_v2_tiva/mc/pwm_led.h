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
    uint32_t thisfreq;
    int flaginit;
    void (*freq)(uint32_t);
    void (*redd)(uint32_t, PWMLED);
    void (*greend)(uint32_t, PWMLED);
    void (*blued)(uint32_t, PWMLED);
}PWMLED;

extern PWMLED pwmled;

void pwmLedInit(PWMLED *pwmled);

void pwmLedSetDuty(PWMLED *duty);

void _pwmLedFreq(uint32_t freq);
void _pwmLedDutyGreen(uint32_t duty, PWMLED *pwmled);
void _pwmLedDutyRed(uint32_t duty, PWMLED *pwmled);
void _pwmLedDutyBlue(uint32_t duty, PWMLED *pwmled);



#endif /* MC_PWM_LED_H_ */
