

#include "main.h"
#include "drv8353s/drv83_interface.h"
#include "terminal/uart_tivac.h"
#include "terminal/newCmdOrder.h"
#include "modflagtimer/modflagtimer.h"



size_t ramcounter;

int main(void)
{

    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();
    MAP_IntMasterEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_3|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    mf_timerinit(10000, &mf_global_systick);
    mfinit_boardled();
    UARTInit();
    cmd_init_callbacks(&newcmd);

    UARTprintf("System Clock@ %d Mhz\r",SysCtlClockGet()/1000000);//SysCtlClockGet ist bei 80Mhz buggy
    UARTprintf("Flash Size@ %d kbyte\r",SysCtlFlashSizeGet()/1000);
    UARTprintf("SRAM Size@ %d kbyte\r",SysCtlSRAMSizeGet()/1000);
    UARTprintf("type help\r");

    drv_spi_blocking_init();

    drvconfig.modeSelect = drv_pwm_6x;


    while(1)
    {
        task_toggle_blue_led(&mf_led_blue_toggle);
        task_toggle_red_led(&mf_led_red_toggle);
        task_toggle_green_led(&mf_led_green_toggle);
        //drv_setOvrLoadProt(&drvconfig);

        //drv_setPwmMode(&drvconfig);

        //drv_setPwmMode(&drvconfig);

    }
}
