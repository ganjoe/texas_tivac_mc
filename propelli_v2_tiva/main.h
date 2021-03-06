/*
 * main.h
 *
 *  Created on: 21.12.2021
 *      Author: pymd02
 */

#ifndef MAIN_H_
#define MAIN_H_

// von texas
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "string.h"
#include "inc/hw_ints.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "stdarg.h"
#include "stdlib.h"
#include "stdio.h"
#include "common/uartstdio.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"
//  user
#include "common/utils.h"
#include "scheudler/modflagtimer.h"
#include "tasks/board_led.h"
#include "motor_control/svm_mf.h"
#include "tasks/mc_primer.h"
#include "digital_IO/input_output.h"
#include "digital_IO/pwm_led.h"


#endif /* MAIN_H_ */
