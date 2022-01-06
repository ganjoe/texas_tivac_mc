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

 MODFLAG mf_testpin;
 MODFLAG mf_led_red_toggle;
 MODFLAG mf_led_green_toggle;
 MODFLAG mf_led_blue_toggle;

void mfinit_boardled();

void toggle_testpin(MODFLAG *thismf);
void task_toggle_green_led(MODFLAG *thismf);
void task_toggle_red_led(MODFLAG *thismf);
void task_toggle_blue_led(MODFLAG *thismf);

int toggle_blue_led();
int toggle_red_led();
int toggle_green_led();

#endif /* MF_TASK_BOARD_LED_H_ */
