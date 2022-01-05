/*
 * board_led.h
 *
 *  Created on: 04.01.2022
 *      Author: pymd02
 */


#ifndef MF_TASK_BOARD_LED_H_
#define MF_TASK_BOARD_LED_H_

#include "main.h"


#define RED_LED   GPIO_PIN_1
#define BLU_LED   GPIO_PIN_2
#define GRN_LED   GPIO_PIN_3
#define TESTPIN   GPIO_PIN_4

 MODFLAGTIMER mf_testpin;
 MODFLAGTIMER mf_led_red_toggle;
 MODFLAGTIMER mf_led_green_toggle;
 MODFLAGTIMER mf_led_blue_toggle;

void mfinit_boardled();

void toggle_testpin(MODFLAGTIMER *thismf);
void task_toggle_green_led(MODFLAGTIMER *thismf);
void task_toggle_red_led(MODFLAGTIMER *thismf);
void task_toggle_blue_led(MODFLAGTIMER *thismf);

#endif /* MF_TASK_BOARD_LED_H_ */
