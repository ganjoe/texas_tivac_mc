

#include "main.h"
#include "drv8353s/drv83_interface.h"
#include "terminal/uart_tivac.h"
#include "terminal/newCmdOrder.h"
#include "modflagtimer/modflagtimer.h"
#include "digital_IO/input_output.h"

size_t ramcounter;

int main(void)
{

    // init für system
    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();
    MAP_IntMasterEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_3|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    WaitFiveCycles();

    // init für gpio
    pinsetup();

    // init für pwmled

    pwmLedSetDuty(&pwmled);
    pwmLedSetFreq(&pwmled);

    // init für systick
    mf_timerinit(10000, &mf_systick);

    // init für modflags
    mfinit_boardled();

    // init für uart-terminal
    UARTInit();

    // init für terminal-callback-funktionen
    cmd_init_callbacks(&newcmd);

     // init für spi
    drv_spi_blocking_init();



    // pseudoinfos
    UARTprintf("System Clock@ %d Mhz\r",SysCtlClockGet()/1000000);//SysCtlClockGet ist bei 80Mhz buggy
    UARTprintf("Flash Size@ %d kbyte\r",SysCtlFlashSizeGet()/1000);
    UARTprintf("SRAM Size@ %d kbyte\r",SysCtlSRAMSizeGet()/1000);
    UARTprintf("Systick @ %d Hz\r",(int)mf_systick.freq);
    UARTprintf("type help\r");



    //testconfig
    drvconfig.modeSelect = drv_pwm_6x;


    while(1)
    {
        /**/


        //drv_setOvrLoadProt(&drvconfig);

        //drv_setPwmMode(&drvconfig);

        //drv_setPwmMode(&drvconfig);

    }
}
