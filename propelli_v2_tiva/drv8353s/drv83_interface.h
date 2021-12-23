/*
 * drv83_interface.h
 *
 *  Created on: 20.12.2021
 *      Author: danie
 */

#ifndef DRV8353S_DRV83_INTERFACE_H_
#define DRV8353S_DRV83_INTERFACE_H_


#include "drv83_datatypes.h"

//*****************************************************************************
// Einzige Instanz für TD_DRV83
// wird durch mc_config.c initialisiert
//*****************************************************************************
TD_DRV83 drvconfig;

//*****************************************************************************
//Api für die MC-Loop
//*****************************************************************************
void drv_spi_blocking_init();

int drv_setPwmMode     (TD_DRV83 *select);
int drv_setShuntGain   (TD_DRV83 *select);
int drv_setOvrLoadProt (TD_DRV83 *select);


//TODO:
void drv_enable();
void drv_reset();
int drv_getFaults       (TD_DRV83 *select);

int drv_setDeadtime     (TD_DRV83 *select);
int drv_setOvrCurrProt  (TD_DRV83 *select);
int drv_setGateCurrRise (TD_DRV83 *select);
int drv_setGateCurrFall (TD_DRV83 *select);





#endif /* DRV8353S_DRV83_INTERFACE_H_ */
