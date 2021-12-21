
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
//! Diese Datei3 beinhaltet Enums die Spi-Register des Treigber-IC
//
//*****************************************************************************

#ifndef DRV8353S_DRV83_DATATYPES_H_
#define DRV8353S_DRV83_DATATYPES_H_

#include <stdint.h>     // f�r texas instruments
#include <stdbool.h>
#include "common/utils.h"

//*****************************************************************************
//
// Pwm-Ansteuerungsmodus
// Der Treiber nimmt 1, 3 oder 6 Pwm-Signale entgegen
// bei 1x Sind die Hall Signale an den anderen Pwm-Eing�ngen verbunden
// Siehe /doc/drv8385s_datasheet.pdf
//*****************************************************************************

typedef enum
{
    drv_pwm_6x, drv_pwm_3x, drv_pwm_1x,
} EN_DRV_MODE_PWM;

//*****************************************************************************
// Faktoren f�r Shuntverst�rker (CSA)
//*****************************************************************************

typedef enum
{
    /* Shunt amplifier gain */
    drv_sgain_5, drv_sgain_10, drv_sgain_20, drv_sgain_40,

} EN_DRV_MODE_SHNT;

//*****************************************************************************
// Schwellen f�r Kurzschlusserkennung
// Spannungsfall direkt �ber den Mosfets
//*****************************************************************************

typedef enum
{
    drv_ocp_250mV, drv_ocp_500mV, drv_ocp_750mV, drv_ocp_1000mV,
} EN_DRV_MODE_OLP;

//*****************************************************************************
// Bezugsspannung f�r Shuntspannung
// unidirektional hei�t bezug auf gnd (kein vorzeichen)
// bidirektional ist Bezug auf vcc/2 (vorzeichen)
// bidirektinale Messung ist f�r Shuntverst�rker in den Motorphasen sinnvoll
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



typedef struct
{
    uint16_t shadowRegister[8];
    EN_DRV_MODE_SHNT csa_gain;
    EN_DRV_ADDR regAdress;
    EN_DRV_MODE_PWM modeSelect;
    EN_DRV_MODE_OFFSET opref;
    EN_DRV_MODE_OLP OLshuntvolts;

} TD_DRV83;

#endif /* DRV8353S_DRV83_DATATYPES_H_ */
