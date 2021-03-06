/*
 * drv83_ll_tivaspi.c
 *
 *  Created on: 19.12.2021
 *      Author: danie
 */
#include "drv83_datatypes.h"
#include "drv83_ll_tivaspi.h"

#define DRV_WRITE_FAIL_COUNT 3
#define DRV_READ_REPEAT_COUNT 3

void _drv_spi_blocking_init(TD_DRV83 *select)
{
    // Enable the SSI0 peripheral
        SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        //      PA5 - SSI0Tx (TM4C123x) / SSI0XDAT1 (TM4C129x)
        //      PA4 - SSI0Rx (TM4C123x) / SSI0XDAT0 (TM4C129x)
        //      PA3 - SSI0Fss
        //      PA2 - SSI0CLK
        GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);

        //
        // Wait for the SSI0 module to be ready.
        //
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))   {    }
        // Configure the SSI.
        SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_TI, SSI_MODE_MASTER, 200000, 16);

        SSIEnable(SSI0_BASE);
        select->flag_init = true;
}

void drv_writeRegister(uint8_t regNr, uint16_t bitMask)
    {

    uint16_t tword;
    uint32_t temp;

    tword = regNr;                                                  //adressnummer setzen (4 bit) und an position vor das rw-bit schieben
    tword <<= 11;                                                   // und an position vor das rw-bit schieben

    utils_set_bit_in_Word(&tword, 15, 0);                           // rw -bit setzen(15)
    utils_set_bits_in_Word(&tword, bitMask, 1);

   // modflag_Timeout(&mf_spi_timeout, 10);
        while(SSIDataGetNonBlocking(SSI0_BASE, &temp)) {}     // buffer leeren, nonblocking h�ngt nicht falls schon leer
        SSIDataPut(SSI0_BASE, tword);
        while(SSIBusy(SSI0_BASE))
           {
           // if (modflag_Timeout(&mf_spi_timeout, 10))
          //      {break;}
           }
    }

void drv_readRegister(uint16_t regNr, uint16_t *data)
    {
    uint16_t tword = 0;

    tword = regNr;                                                  //adressnummer setzen (4 bit)
    tword <<= 11;                                                   // und an position vor das rw-bit schieben

    utils_set_bit_in_Word(&tword, 15, 1);                           // rw -bit setzen(15)
    //modflag_Timeout(&mf_spi_timeout, 10);
   while(SSIDataGetNonBlocking(SSI0_BASE, (uint32_t*)data)) {}     // buffer leeren, nonblocking h�ngt nicht falls schon leer
    SSIDataPut(SSI0_BASE, (uint32_t)tword);                         //adresse mit dummyword f�r clockgenerierung senden
    while(SSIBusy(SSI0_BASE))
       {
       // if (modflag_Timeout(&mf_spi_timeout, 10))
        //    {break;}
       }


    SSIDataGet(SSI0_BASE, (uint32_t*)data);

    }
int drv_writeCompareReg(uint8_t regNr, uint16_t data)
    {


    uint16_t comparebuffer = 0;
    int errcounter = DRV_WRITE_FAIL_COUNT;
    
    
    while(errcounter >= 0)
            {
            drv_writeRegister(regNr, data);
            drv_readRegister(regNr, &comparebuffer);

            if (data!=comparebuffer)
                {
                errcounter--;
                }
            else
                {
                return 1;
                }

            }
    return 0;

    }
int drv_readCompareReg(uint8_t regNr, uint16_t *data)
    {
    uint16_t comparebuff = 0;
    int errcounter = DRV_READ_REPEAT_COUNT;

    while(errcounter>=0)
        {
         drv_readRegister (regNr,data);
         drv_readRegister (regNr,&comparebuff);
         if (*data!=comparebuff)
             {
             errcounter--;
             }
         else
             {
             return 1;
             }

        }

    return 0;
    }


