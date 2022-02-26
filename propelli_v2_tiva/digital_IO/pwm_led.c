/*
 * pwm_led.c
 *
 *  Created on: 22.02.2022
 *      Author: pymd02
 */
#include <digital_IO/pwm_led.h>


PWMLED pwmled ={.flaginit = 0,
                .freq =&_pwmLedFreq,
                .red = &_pwmLedDutyRed,
                .blue = &_pwmLedDutyBlue,
                .green = &_pwmLedDutyGreen,
                };


void _pwmLedFreq(uint32_t freq, PWMLED *pwmled)
{
    if (!pwmled->flaginit)
            _pwmLedInit(pwmled);
    /*
     * This function sets the period of the specified PWM generator block,
     * where the period of the generator block is defined as the number of
     * PWM clock ticks between pulses on the generator block zero signal.
     */
    utils_truncate_number_uint32(&freq, 615, 300E3);
    MAP_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, (80000000 / freq));
    MAP_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, (80000000 / freq));
}

void _pwmLedDutyGreen(float green, PWMLED *pwmled)
    {
    if (!pwmled->flaginit)
            _pwmLedInit(pwmled);
    MAP_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,  (abs(MAP_PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2) * green)-1));
    }

void _pwmLedDutyRed(float red, PWMLED *pwmled)
    {
    if (!pwmled->flaginit)
            _pwmLedInit(pwmled);
    MAP_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,  (abs(MAP_PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * red)-1));
    }

void _pwmLedDutyBlue(float blue, PWMLED *pwmled)
    {
    if (!pwmled->flaginit)
            _pwmLedInit(pwmled);
    MAP_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,  (abs(MAP_PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * blue)-1));
    }

void _pwmLedInit(PWMLED *pwmled)
    {

    //
       // Set the clocking to run directly from the external crystal/oscillator.

       // MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |    SYSCTL_XTAL_16MHZ);

       //
       // Set the PWM clock to the system clock.
       //
       MAP_SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

        //
       // The PWM peripheral must be enabled for use.
       //
       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

       // Wait for the PWM0 module to be ready.
       //
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1))

       //
       // Enable the GPIO port that is used for the PWM output.
       //
       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

       //
       // Configure the PWM function for this pin.
       //
       MAP_GPIOPinConfigure(GPIO_PF1_M1PWM5);
       MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);

       MAP_GPIOPinConfigure(GPIO_PF2_M1PWM6);
       MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);

       MAP_GPIOPinConfigure(GPIO_PF3_M1PWM7);
       MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);

       //
       // Configure PWM1 to count up/down without synchronization.
       //
       MAP_PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN |PWM_GEN_MODE_NO_SYNC);
       MAP_PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN |PWM_GEN_MODE_NO_SYNC);

       //
       // Set the PWM period to 250Hz.  To calculate the appropriate parameter
       // use the following equation: N = (1 / f) * SysClk.  Where N is the
       // function parameter, f is the desired frequency, and SysClk is the
       // system clock frequency.
       //
       MAP_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, (ROM_SysCtlClockGet() / 250));
       MAP_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, (ROM_SysCtlClockGet() / 250));

       //
       // Set PWM0 to a duty cycle of 25%.  You set the duty cycle as a function
       // of the period.  Since the period was set above, you can use the
       // PWMGenPeriodGet() function.  For this example the PWM will be high for
       // 25% of the time or (PWM Period / 4).
       //
       MAP_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,  MAP_PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2) / 1);
       MAP_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,  MAP_PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) / 1);
       MAP_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,  MAP_PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) / 1);

       //
       // Enable PWM Out Bit 0 (PB6) output signal.
       //
       MAP_PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
       MAP_PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
       MAP_PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);

       //
       // Enable the PWM generator block.
       //
       MAP_PWMGenEnable(PWM1_BASE, PWM_GEN_2);
       MAP_PWMGenEnable(PWM1_BASE, PWM_GEN_3);


       // Switch PWM0 signal back to regular operation.
       //
       MAP_PWMOutputInvert(PWM1_BASE, PWM_OUT_5_BIT, false);
       MAP_PWMOutputInvert(PWM1_BASE, PWM_OUT_6_BIT, false);
       MAP_PWMOutputInvert(PWM1_BASE, PWM_OUT_7_BIT, false);
       //
       pwmled->flaginit = 1;

    }
