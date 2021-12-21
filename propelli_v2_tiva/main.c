
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"

#include "drv8353s/drv83_interface.h"


#define RED_LED   GPIO_PIN_1


int main(void)
{
    //
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))   { }

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED);

    // Enable the SSI0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //      PA5 - SSI0Tx (TM4C123x) / SSI0XDAT1 (TM4C129x)
    //      PA4 - SSI0Rx (TM4C123x) / SSI0XDAT0 (TM4C129x)
    //      PA3 - SSI0Fss
    //      PA2 - SSI0CLK
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);

    //
    // Wait for the SSI0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))   {    }
    // Configure the SSI.
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 2000000, 8);

    SSIEnable(SSI0_BASE);
   //      drvconfig.modeSelect = drv_pwm_3x;
     //   drv_setPwmMode(&drvconfig);


    char *pcChars = "SSI Master send data.";
    int32_t i32Idx =21;
    // Loop Forever

    while(1)
    {
    while(i32Idx)
    {
        SSIDataPut(SSI0_BASE, pcChars[i32Idx]);
        i32Idx--;
    }
    i32Idx =21;
    }
}
