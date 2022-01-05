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
            cmd_parse_string(&newcmd, &uartReceivedString);
            uartReceivedCounter = 0;
            }
        else
            {
            uartReceivedCounter++;
            }


        //
        // Read the next character from the UART and write it back to the UART.
        //MAP_UARTCharPutNonBlocking(UART1_BASE,MAP_UARTCharGetNonBlocking(UART1_BASE));

        }
}




void
UARTInit()
{

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    MAP_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART1_BASE, UART_CLOCK_SYSTEM);

    // nicht modifiziert. aus "hello" example
    UARTStdioConfig(1, 115200, SysCtlClockGet());

    // notwendig für non-blocking receive
    MAP_IntEnable(INT_UART1);
    MAP_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
}

char uartTranceiveString[128];

/*void term_qPrintf   (char *fmt, ...)
    {
    va_list argp;

    va_start(argp, fmt);

    vsnprintf(uartTranceiveString, uartPrintBufferSize, fmt, argp);

    va_end(argp);

    term_sendBuffer(uartTranceiveString, bytesWrote);
    }*/
