/*=====================================================================================
 File name:        SVGEN_MF.C  (IQ version)

 Originator:    Digital Control Systems Group
            Texas Instruments

 Description:   Space-vector PWM generation based on magnitude and frequency components

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005 Version 3.20
-------------------------------------------------------------------------------------*/
/*
 * svm_mf.c
 *
 *  Created on: 21.02.2022
 *      Author: daniel
 */
#include "svm_mf.h"
#include "math.h"

void svgenmf_calc(SVGENMF *v)
{
    float StepAngle, EntryOld, dx, dy;
    float T = 1.0;

    // Normalise the freq input to appropriate step angle
    // Here, 1 pu. = 60 degree
    StepAngle = v->Freq * v->FreqMax;

    // Calculate new angle alpha
    EntryOld = v->NewEntry;
    v->Alpha = v->Alpha + StepAngle;
    if (v->Alpha >= 1.0)
        {
        v->Alpha = v->Alpha-1.0;
        }

    v->NewEntry = v->Alpha;

    dy = sinf((v->NewEntry * PI_THIRD));             // dy = sin(NewEntry)
    dx = sinf(PI_THIRD-(v->NewEntry *  PI_THIRD));     // dx = sin(60-NewEntry)

    // Determine which sector
    if (v->NewEntry-EntryOld<0)
    {
      if (v->SectorPointer==5)
         v->SectorPointer = 0;
      else
         v->SectorPointer = v->SectorPointer + 1;
    }

    if (v->SectorPointer==0)  // Sector 1 calculations - a,b,c --> a,b,c
    {
        v->Ta = ((0.5) * (T-dx-dy));
        v->Tb = v->Ta + dx;
        v->Tc = T - v->Ta;
    }
    else if (v->SectorPointer==1)  // Sector 2 calculations - a,b,c --> b,a,c  &  dx <--> dy
    {
        v->Tb = ((0.5) * (T-dx-dy));
        v->Ta = v->Tb + dy;
        v->Tc = T - v->Tb;
    }
    else if (v->SectorPointer==2)  // Sector 3 calculations - a,b,c --> b,c,a
    {
        v->Tb = ((0.5) * (T-dx-dy));
        v->Tc = v->Tb + dx;
        v->Ta = T - v->Tb;
    }
    else if (v->SectorPointer==3)  // Sector 4 calculations - a,b,c --> c,b,a  &  dx <--> dy
    {
        v->Tc = ((0.5) * (T-dx-dy));
        v->Tb = v->Tc + dy;
        v->Ta = T - v->Tc;
    }
    else if (v->SectorPointer==4)  // Sector 5 calculations - a,b,c --> c,a,b
    {
        v->Tc = ((0.5) * (T-dx-dy));
        v->Ta = v->Tc + dx;
        v->Tb = T - v->Tc;
    }
    else if (v->SectorPointer==5)  // Sector 6 calculations - a,b,c --> a,c,b  &  dx <--> dy
    {
        v->Ta = ((0.5) * (T-dx-dy));
        v->Tc = v->Ta + dy;
        v->Tb = T - v->Ta;
    }

// Convert the unsigned GLOBAL_Q format (ranged (0,1)) -> signed GLOBAL_Q format (ranged (-1,1))
// Then, multiply with a gain and add an offset.
    v->Ta = ((2.0) * (v->Ta-(0.5)));
    v->Ta = (v->Gain * v->Ta) + v->Offset;

    v->Tb = ((2.0) * (v->Tb-(0.5)));
    v->Tb = (v->Gain * v->Tb) + v->Offset;

    v->Tc = ((2.0) * (v->Tc-(0.5)));
    v->Tc = (v->Gain * v->Tc) + v->Offset;

}







