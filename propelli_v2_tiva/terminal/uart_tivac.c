/*
 * uart_tivac.c
 *
 *  Created on: 02.01.2022
 *      Author: danie
 */


#include "uart_tivac.h"
#include "newCmdOrder.h"


char uartReceivedString[128];
char uartCR =13;
uint8_t uartReceivedCounter = 0;


void UARTIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = MAP_UARTIntStatus(UART1_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    MAP_UARTIntClear(UART1_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(MAP_UARTCharsAvail(UART1_BASE))
        {
        uartReceivedString[uartReceivedCounter] = MAP_UARTCharGetNonBlocking(UART1_BASE);
        if (uartReceivedString[uartReceivedCounter] == uartCR)
            {
            uartReceivedCounter = 0;
            cmd_parse_string(&newcmd, &uartReceivedString);
            MAP_UARTCharPut(UART1_BASE, uartCR);
            }
        uartReceivedCounter++;

        //
        // Read the next character from the UART and write it back to the UART.
        //MAP_UARTCharPutNonBlocking(UART1_BASE,MAP_UARTCharGetNonBlocking(UART1_BASE));

        }
}

void UARTInit()
{

    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    //
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable the GPIO pins for the LED (PF2).
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    MAP_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    MAP_UARTConfigSetExpClk(UART1_BASE, MAP_SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    MAP_IntEnable(INT_UART1);
    MAP_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
}
