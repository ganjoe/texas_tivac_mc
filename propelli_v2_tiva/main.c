

#include "main.h"
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


    drv_spi_blocking_init();

    drvconfig.modeSelect = drv_pwm_3x;


    while(1)
    {
        drv_setOvrLoadProt(&drvconfig);
        //drv_setPwmMode(&drvconfig);
    }
}
