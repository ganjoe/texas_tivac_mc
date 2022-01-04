

#include "main.h"
#include "drv8353s/drv83_interface.h"
#include "terminal/uart_tivac.h"
#include "terminal/newCmdOrder.h"




#define RED_LED   GPIO_PIN_1

size_t ramcounter;
int main(void)
{

    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();
    MAP_IntMasterEnable();
    //
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))   { }

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED);

    UARTInit();

    UARTprintf("System Clock@ %d Mhz\r",SysCtlClockGet()/1000000);
    UARTprintf("Flash Size@ %d kbyte\r",SysCtlFlashSizeGet()/1000);
    UARTprintf("SRAM Size@ %d kbyte\r",SysCtlSRAMSizeGet()/1000);

    ramcounter = __TI_heap_total_available();



    cmd_init_callbacks(&newcmd);

    drv_spi_blocking_init();

    drvconfig.modeSelect = drv_pwm_3x;


    while(1)
    {
        //drv_setOvrLoadProt(&drvconfig);
        //drv_setPwmMode(&drvconfig);
    }
}
