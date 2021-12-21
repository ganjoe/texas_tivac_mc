/*
 * drv83_interface.h
 *
 *  Created on: 20.12.2021
 *      Author: danie
 */

#ifndef DRV8353S_DRV83_INTERFACE_H_
#define DRV8353S_DRV83_INTERFACE_H_


#include "drv83_datatypes.h"

TD_DRV83 drvconfig;

int drv_setPwmMode     (TD_DRV83 *select);
int drv_setShuntGain   (TD_DRV83 *select);
int drv_setOvrLoadProt (TD_DRV83 *select);


#endif /* DRV8353S_DRV83_INTERFACE_H_ */
