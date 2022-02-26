

#include "main.h"
#include "drv8353s/drv83_interface.h"
#include "terminal/uart_tivac.h"
#include "terminal/newCmdOrder.h"
#include "scheudler/modflagtimer.h"
#include "digital_IO/input_output.h"

size_t ramcounter;

int main(void)
{

    // init f�r system
    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();
    MAP_IntMasterEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    WaitFiveCycles();

    // init f�r gpio
    pinsetup();

    // init f�r pwmled
    _pwmLedInit(&pwmled);
    //pwmLedSetDuty(&pwmled);
    //pwmLedSetFreq(&pwmled);
//
    // init f�r systick
    mf_timerinit(1000, &mf_systick);

    // init f�r modflags
    mfinit_boardled();

    // init f�r uart-terminal
    UARTInit();

    // init f�r terminal-callback-funktionen
    cmd_init_callbacks(&newcmd);

     // init f�r spi
    drv_spi_blocking_init();



    // pseudoinfos
    UARTprintf("System Clock@ %d Mhz\r",ROM_SysCtlClockGet()/1000000);//SysCtlClockGet ist bei einigen Frequenzen (z.b. 80Mhz)  buggy, daher _ROM
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
