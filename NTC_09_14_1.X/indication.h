/* 
 * File:   indication.h
 * Author: stas
 *
 * Created on 19 ?????? 2018 ?., 9:49
 */

#ifndef INDICATION_H
#define	INDICATION_H

#include "system.h"

#define BLINK_TICK_PERIOD_MS 100
#define INDICATOR_COUNT 23

#define SUPPLY_LED_0 3
#define PUMP_LED 2
#define SYPPLY_LED_1 1
#define SUPPLY_VALVE_LED 0
#define SUPPLY_LED_2 4
#define L_INNER_LED_8 5
#define L_INNER_LED_7 6
#define L_INNER_LED_6 7
#define L_INNER_LED_5 8
#define L_INNER_LED_4 9 
#define L_INNER_LED_3 10
#define L_INNER_LED_2 11
#define L_INNER_LED_1 15
#define L_INNER_LED_0 14
#define RELEASE_LED_0 13
#define RELEASE_VALVE_LED 12
#define RELEASE_LED_1 16
#define READINNES_LED 17
#define ACCIDENT_LED 18
#define L_OUTER_LED_3 19
#define L_OUTER_LED_2 22
#define L_OUTER_LED_1 21
#define L_OUTER_LED_0 20

typedef struct
{
    uint32_t period_ticks;
	uint32_t tick_counter;
	bool blink_once;
	bool state;
} Blink;

extern Blink blinks[INDICATOR_COUNT]; 

void indication_init();
void indication_update();

void blink();
void blink_tick();
void blink_set_value(unsigned int id, float ratio);
void blink_set_initial_state(unsigned int id, bool state);

#endif	/* INDICATION_H */

