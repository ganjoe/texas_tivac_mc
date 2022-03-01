/*
 * mc_config.c
 *
 *  Created on: 01.03.2022
 *      Author: pymd02
 */

#include "mc_config.h"
#include "digital_IO/pwm_led.h"


int confgen_setdefaults(TD_MC_PARAMS *mc)
{

    _pwmLedFreq(100000, &pwmled);
    svm_mf.FreqMax = 1;
    svm_mf.Freq = 0.0005;
    svm_mf.Gain = 0.5;
    svm_mf.Offset= 0.5;

    return 1;
}

TD_MC_PARAMS mcdata;
