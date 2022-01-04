/*
 * drv83_interface.c
 *
 *  Created on: 19.12.2021
 *      Author: daniel
 */


#include "drv83_interface.h"
#include "drv83_ll_tivaspi.h"

//implementiert in drv83_ll_


int drv_setPwmMode(TD_DRV83 *select)
    {
    uint16_t regbuffer = 0;

    if( drv_readCompareReg(driverControl, &regbuffer))
    {
    switch (select->modeSelect)
        {
        case drv_pwm_1x:
        utils_set_bit_in_Word(&regbuffer, 5, 0);
        utils_set_bit_in_Word(&regbuffer, 6, 1);
        break;

        case drv_pwm_3x:
        utils_set_bit_in_Word(&regbuffer, 5, 1);
        utils_set_bit_in_Word(&regbuffer, 6, 0);
        break;

        case drv_pwm_6x:
        utils_set_bit_in_Word(&regbuffer, 5, 0);
        utils_set_bit_in_Word(&regbuffer, 6, 0);
        break;

        }
     if (drv_writeCompareReg(CSAcontrol, regbuffer))
         return 1;
    }
   return 0;
    }
int drv_setShuntGain(TD_DRV83 *select)
    {

    uint16_t regbuffer = 0;

    if(drv_readCompareReg(CSAcontrol, &regbuffer))
    {
        switch (select->csa_gain)
        {
        case drv_sgain_5:
        utils_set_bit_in_Word(&regbuffer, 6, 0);
        utils_set_bit_in_Word(&regbuffer, 7, 0);


        break;
        case drv_sgain_10:
        utils_set_bit_in_Word(&regbuffer, 6, 1);
        utils_set_bit_in_Word(&regbuffer, 7, 0);


        break;
        case drv_sgain_20:
        utils_set_bit_in_Word(&regbuffer, 6, 0);
        utils_set_bit_in_Word(&regbuffer, 7, 1);


        break;
        case drv_sgain_40:
        utils_set_bit_in_Word(&regbuffer, 6, 1);
        utils_set_bit_in_Word(&regbuffer, 7, 1);


        break;
        }
        if (drv_writeCompareReg(CSAcontrol, regbuffer))
            return 1;
    }
    return 0;
    }
int drv_setOvrLoadProt(TD_DRV83 *select)
    {
    uint16_t regbuffer = 0;

    if(drv_readCompareReg(CSAcontrol, &regbuffer))
    {

        switch (select->OLshuntvolts)
        {
        case drv_ocp_250mV:
        utils_set_bit_in_Word(&regbuffer, 0, 0);
        utils_set_bit_in_Word(&regbuffer, 1, 0);
        //term_qPrintf(&myTxQueueHandle, "drv_ocp_250mV");
        break;
        case drv_ocp_500mV:
        utils_set_bit_in_Word(&regbuffer, 0, 1);
        utils_set_bit_in_Word(&regbuffer, 1, 0);
        //term_qPrintf(&myTxQueueHandle, "drv_ocp_500mV");
        case drv_ocp_750mV:
        utils_set_bit_in_Word(&regbuffer, 0, 0);
        utils_set_bit_in_Word(&regbuffer, 1, 1);
        //term_qPrintf(&myTxQueueHandle, "drv_ocp_750mV");
        case drv_ocp_1000mV:
        utils_set_bit_in_Word(&regbuffer, 0, 1);
        utils_set_bit_in_Word(&regbuffer, 1, 1);
        //term_qPrintf(&myTxQueueHandle, "drv_ocp_1000mV");
        break;
        }
        utils_set_bit_in_Word(&regbuffer, 5, 1);
        if (drv_writeCompareReg(CSAcontrol, regbuffer))
            return 1;
    }
    return 0;
    }

