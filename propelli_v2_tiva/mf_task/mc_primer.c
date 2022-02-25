/*
 * mc_primer.c
 *
 *  Created on: 22.02.2022
 *      Author: pymd02
 */


#include "main.h"

MC_DATA mc_data ={.poti_input = 0};

void mc_task()
    {
    svm_mf.FreqMax = 1000;
    svm_mf.Freq = 0.0000005;
    svm_mf.Gain = 0.5;
    svm_mf.Offset= 0.5;
    svm_mf.calc(&svm_mf);

    pwmled.freq(100000, &pwmled);
    pwmled.blue(svm_mf.Ta, &pwmled);
    pwmled.red(svm_mf.Tb, &pwmled);
    pwmled.green(svm_mf.Tc, &pwmled);
    }


