
//*****************************************************************************
// DRV83.h
//
//  Created on: Feb 12, 2021
//
//      Author: pymd02
//
//*****************************************************************************

//*****************************************************************************
//
//! Globaler Datentyp für DRV83
//
//*****************************************************************************

#ifndef DRV8353S_DRV83_DATATYPES_H_
#define DRV8353S_DRV83_DATATYPES_H_

#include "main.h"


//*****************************************************************************
//
// Pwm-Ansteuerungsmodus
// Der Treiber nimmt 1, 3 oder 6 Pwm-Signale entgegen
// bei 1x Sind die Hall Signale an den anderen Pwm-Eingï¿½ngen verbunden
// Siehe /doc/drv8385s_datasheet.pdf
//*****************************************************************************


typedef enum
{
    drv_pwm_6x, drv_pwm_3x, drv_pwm_1x,
} EN_DRV_MODE_PWM;

//*****************************************************************************
// Faktoren fï¿½r Shuntverstï¿½rker (CSA)
//*****************************************************************************

typedef enum
{
    /* Shunt amplifier gain */
    drv_sgain_5, drv_sgain_10, drv_sgain_20, drv_sgain_40,

} EN_DRV_MODE_SHNT;

//*****************************************************************************
// Schwellen fï¿½r Kurzschlusserkennung
// Spannungsfall direkt ï¿½ber den Mosfets
//*****************************************************************************

typedef enum
{
    drv_ocp_250mV, drv_ocp_500mV, drv_ocp_750mV, drv_ocp_1000mV,
} EN_DRV_MODE_OLP;

//*****************************************************************************
// Bezugsspannung fï¿½r Shuntspannung
// unidirektional heiï¿½t bezug auf gnd (kein vorzeichen)
// bidirektional ist Bezug auf vcc/2 (vorzeichen)
// bidirektinale Messung ist fï¿½r Shuntverstï¿½rker in den Motorphasen sinnvoll
//*****************************************************************************

typedef enum
{
    drv_shunt_unidirectional, drv_shunt_bidirectinal

} EN_DRV_MODE_OFFSET;

//*****************************************************************************
// Registeroffsetadressen
//*****************************************************************************

typedef enum
{
    faultstatus = 0,
    vgsStatus,
    driverControl,
    gateDriveHS,
    gateDriveLS,
    OCPcontrol,
    CSAcontrol,
} EN_DRV_ADDR;

//*****************************************************************************
//
//*****************************************************************************


struct TD_DRV83S;

typedef struct TD_DRV83S
{
    EN_DRV_ADDR regAdress;
    EN_DRV_MODE_OFFSET opref;
    EN_DRV_MODE_SHNT csa_gain;
    EN_DRV_MODE_PWM modeSelect;
    EN_DRV_MODE_OLP OLshuntvolts;

    int flag_init;
    int (*check)(struct TD_DRV83S *drv);
    void (*SpiInit)(struct TD_DRV83S *drv);

    int (*setPwmMode)(struct TD_DRV83S *drv);
    int (*setShuntGain)(struct TD_DRV83S *drv);
    int (*setOvrLoadProt)(struct TD_DRV83S *drv);

    int (*readCompare)(uint8_t regNr, uint16_t *data);
    int (*writeCompare)(uint8_t regNr, uint16_t data);

    void (*drv_writeRegister) (uint8_t regNr, uint16_t data);
    void (*drv_readRegister) (uint16_t regNr, uint16_t *data);

} TD_DRV83;

extern TD_DRV83 drv;

#endif /* DRV8353S_DRV83_DATATYPES_H_ */
