/* 
 * File:   analog_inputs.h
 * Author: stas
 *
 * Created on 19 ?????? 2018 ?., 15:11
 */

#ifndef ANALOG_INPUTS_H
#define	ANALOG_INPUTS_H

#include "system.h"

#define CONVERT_COEF 0.000244140625

void analog_inputs_init();
uint16_t get_pressure();
uint16_t get_supply();
uint16_t get_outflow();

#endif	/* ANALOG_INPUTS_H */

