/*
 * utils.c
 *
 *  Created on: 20.12.2021
 *      Author: danie
 */

#include "utils.h"

void utils_set_bits_in_Word(uint16_t* word, uint16_t bitmask, int state)
{
    switch (state)
    {
    case true:
    *word |= bitmask;
    break;
    case false:
    *word &= ~(bitmask);
    break;
    }

}

void utils_set_bit_in_Word(uint16_t *word, uint8_t pos, bool state)
    {
    switch (state)
        {
        case 1:
        *word |= 1UL << pos;
        break;
        case 0:
        *word &= ~(1UL << pos);
        break;
        }

    }
