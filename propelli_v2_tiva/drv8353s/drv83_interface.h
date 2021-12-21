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

int drv_setPwmMode     (TD_DRV83 *select);
int drv_setShuntGain   (TD_DRV83 *select);
int drv_setOvrLoadProt (TD_DRV83 *select);

//*****************************************************************************
// Hardwarespezifische Inits
//*****************************************************************************
void drv_spi_blocking_init();

#endif /* DRV8353S_DRV83_INTERFACE_H_ */
