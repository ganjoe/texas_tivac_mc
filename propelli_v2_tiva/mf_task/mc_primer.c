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
    svm_mf.Freq = 0.5;
    svm_mf.Gain = 0.5;
    svm_mf.Offset= 0.5;
    svm_mf.calc(&svm_mf);
    }


