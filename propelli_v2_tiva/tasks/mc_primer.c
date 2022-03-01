/*
 * mc_primer.c
 *
 *  Created on: 22.02.2022
 *      Author: pymd02
 */


#include "main.h"



void mc_task()
    {


  //  _pwmLedFreq(100000, &pwmled);
  //  svm_mf.FreqMax = 1;
 //   svm_mf.Freq = 0.0005;
 ///   svm_mf.Gain = 0.5;
  //  svm_mf.Offset= 0.5;

    pwmled.blue(svm_mf.Ta, &pwmled);
    pwmled.red(svm_mf.Tb, &pwmled);
    pwmled.green(svm_mf.Tc, &pwmled);

    svm_mf.calc(&svm_mf);

    }


