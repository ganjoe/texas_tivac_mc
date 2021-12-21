//*****************************************************************************
//
// project0.c - Example to demonstrate minimal TivaWare setup
//
// Copyright (c) 2012-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LI6ABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "drv8353s/drv83_interface.h"


#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************

//*****************************************************************************
//
// Main 'C' Language entry point.  Toggle an LED using TivaWare.
//
//*****************************************************************************
int main(void)
{
    //
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //
    // Enable and wait for the port to be ready for access
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    
    //
    // Configure the GPIO port for the LED operation.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);

    //
    // Loop Forever
    //
    while(1)
    {
        //
        // Turn on the LED
        //

        drvconfig.modeSelect = drv_pwm_3x;
        drv_setPwmMode(&drvconfig);

        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, RED_LED);

        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);

        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, BLUE_LED);

        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);
    }
}
