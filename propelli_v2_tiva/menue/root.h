/*
 * root.h
 *
 *  Created on: 02.03.2022
 *      Author: danie
 */

#ifndef MENUE_ROOT_H_
#define MENUE_ROOT_H_

struct MENUE_SCREENS;

typedef struct MENUE_SCREENS
{
    const char *maintext;   //bdc, bldc, pmsm, acim
    const char *mode;    //*mode*, *return*, maxramp, minramp, limit-up, limit-down
    const char *submode; // *return*
    int *data;


}MENUE_SCREEN;

extern MENUE_SCREEN menue;

void show_menue(MENUE_SCREEN *thismenue);

#endif /* MENUE_ROOT_H_ */
