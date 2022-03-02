/*
 * root.c
 *
 *  Created on: 02.03.2022
 *      Author: danie
 */


#include "main.h"
#include "root.h"

MENUE_SCREEN menue;

void show_menue(MENUE_SCREEN *thismenue)
{
 UARTprintf(thismenue->maintext);
}
