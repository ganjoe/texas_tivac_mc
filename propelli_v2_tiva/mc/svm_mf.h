/*
 * svm_mf.h
 *
 *  Created on: 21.02.2022
 *      Author: daniel
 */

#ifndef MC_SVM_MF_H_
#define MC_SVM_MF_H_

/* =================================================================================
File name:       SVGEN_MF.H  (IQ version)

Originator: Digital Control Systems Group
            Texas Instruments

Description:
Header file containing constants, data type definitions, and
function prototypes for the SVGEN_MF.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005 Version 3.20
------------------------------------------------------------------------------*/
#include "main.h"

typedef struct
    {
    float  Gain;                // Input: reference gain voltage (pu)
    float  Offset;              // Input: reference offset voltage (pu)
    float  Freq;                // Input: reference frequency (pu)
    float  FreqMax;             // Parameter: Maximum step angle = 6*base_freq*T (pu)
    float  Alpha;               // History: Sector angle (pu)
    float  NewEntry;            // History: Sine (angular) look-up pointer (pu)
    uint32_t  SectorPointer;    // History: Sector number (Q0) - independently with global Q
    float  Ta;                  // Output: reference phase-a switching function (pu)
    float  Tb;                  // Output: reference phase-b switching function (pu)
    float  Tc;                  // Output: reference phase-c switching function (pu)
    void   (*calc)();         // Pointer to calculation function
    } SVM_MF;

extern SVM_MF svm_mf;

//typedef SVGENMF *SVGENMF_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SVGENMF object.
-----------------------------------------------------------------------------*/
//#define SVGENMF_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,(void (*)(Uint32))svgenmf_calc }

#define PI_THIRD 1.04719755119660    // This is 60 degree
/*------------------------------------------------------------------------------
Prototypes for the functions in SVGEN_MF.C
------------------------------------------------------------------------------*/
void svgenmf_calc(SVM_MF *v);

#endif /* MC_SVM_MF_H_ */
