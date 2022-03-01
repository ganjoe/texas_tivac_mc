/*
 * mc_config.h
 *
 *  Created on: 01.03.2022
 *      Author: pymd02
 */

#ifndef CONFGEN_MC_CONFIG_H_
#define CONFGEN_MC_CONFIG_H_

#include "main.h"

typedef struct
        {
    float poti;
        }TD_MC_PARAMS;

int confgen_setdefaults(TD_MC_PARAMS *mc);

extern TD_MC_PARAMS mcdata;

#endif /* CONFGEN_MC_CONFIG_H_ */
