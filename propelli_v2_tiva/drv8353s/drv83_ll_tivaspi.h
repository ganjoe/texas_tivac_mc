/*
 * drv83_ll_tivaspi.h
 *
 *  Created on: 22.12.2021
 *      Author: danie
 */

#ifndef DRV8353S_DRV83_LL_TIVASPI_H_
#define DRV8353S_DRV83_LL_TIVASPI_H_
#include "main.h"

void drv_writeRegister(uint8_t regNr, uint16_t bitMask);
void drv_readRegister(uint16_t regNr, uint16_t *data);
int drv_writeCompareReg(uint8_t regNr, uint16_t data);
int drv_readCompareReg(uint8_t regNr, uint16_t *data);



#endif /* DRV8353S_DRV83_LL_TIVASPI_H_ */
