/*
 * utils.h
 *
 *  Created on: 20.12.2021
 *      Author: daniel
 */

#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_

#include <stdint.h>
#include <stdbool.h>

void utils_set_bits_in_Word(uint16_t *word, uint16_t bitmask, int state);
void utils_set_bit_in_Word(uint16_t *word, uint8_t pos, bool state);
int utils_truncate_number_int(int *number, int min, int max);



#endif /* COMMON_UTILS_H_ */
