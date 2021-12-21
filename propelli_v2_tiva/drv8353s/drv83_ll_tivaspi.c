/*
 * drv83_ll_tivaspi.c
 *
 *  Created on: 19.12.2021
 *      Author: danie
 */
#include "drv83_datatypes.h"

#define DRV_WRITE_FAIL_COUNT 3

void drv_writeRegister(uint8_t regNr, uint16_t bitMask)
    {

    uint16_t tword;

    //adressnummer setzen (4 bit) und an position vor das rw-bit schieben
    tword = regNr;
    tword <<= 11;
    // rw -bit setzen(15)
    utils_set_bit_in_Word(&tword, 15, 0);
    utils_set_bits_in_Word(&tword, bitMask, 1);
  //  drv_csPulse();
   // HAL_SPI_Transmit(&hspi1, (uint8_t*) &tword, 1, HAL_TIMEOUT);
    }
void drv_readRegister(uint16_t regNr, uint16_t *data)
    {
    uint16_t tword = 0;

    //adressnummer setzen (4 bit) und an position vor das rw-bit schieben
    tword = regNr;
    tword <<= 11;
    // rw -bit setzen(15)
  //  utils_set_bit_in_Word(&tword, 15, 1);
   // drv_csPulse();
   // HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) &tword, (uint8_t*) data, 1,HAL_TIMEOUT);

    }
bool drv_writeCompareReg(uint8_t regNr, uint16_t reg)
    {
    uint16_t regbuffer = 0;
    uint8_t errcounter = 0;
    drv_writeRegister(regNr, reg);

     if (errcounter == DRV_WRITE_FAIL_COUNT)
        {
        return 0;
     //   HAL_Delay(10);
      //  Error_Handler();
        }

    return 1;
    }
bool drv_readCompareReg(uint8_t regNr, uint16_t reg)
{
    uint16_t regbuffer = 0;
    uint8_t errcounter = 0;

    if (errcounter == DRV_WRITE_FAIL_COUNT)
       {
       return 0;
    //   HAL_Delay(10);
     //  Error_Handler();
       }

   return 1;
}

void drv_csPulse()
    {
    //TODO: delay.c aus propelli-head mergen und mit wait_isr ergänzen
  //  HAL_GPIO_WritePin(drv_cs_GPIO_Port, drv_cs_Pin, 0);
   // HAL_GPIO_WritePin(drv_cs_GPIO_Port, drv_cs_Pin, 1);
    int var = 0;
    for (; var < 0xF; ++var)
    {
    var += 1;
    }
    //HAL_GPIO_WritePin(drv_cs_GPIO_Port, drv_cs_Pin, 0);

    for (; var < 0xF; ++var)
    {
    var += 1;
    }
    }


