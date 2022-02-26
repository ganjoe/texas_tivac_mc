/*
 * mc_primer.h
 *
 *  Created on: 22.02.2022
 *      Author: pymd02
 */

#ifndef MF_TASK_MC_PRIMER_H_
#define MF_TASK_MC_PRIMER_H_

typedef struct
    {
    float poti_input;   //pu. kontextabhängige vorgabe

    }MC_DATA;

extern MC_DATA mc_data;

void mc_task();



#endif /* MF_TASK_MC_PRIMER_H_ */
