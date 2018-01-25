/* 
 * File:   switchers.h
 * Author: stas
 *
 * Created on 19 ?????? 2018 ?., 9:42
 */

#ifndef SWITCHERS_H
#define	SWITCHERS_H
#include <stdbool.h>

#define MODE_ID 0
#define M1_HAND_ID 1
#define Y1_HAND_ID 2
#define Y2_HAND_ID 3
#define RES_ID 4
#define ACCIDENT_ID 5
#define READINESS_ID 6

#define SWITCHERS_COUNT 7

void switchers_init();

bool switchers_is_on(unsigned int switcherId);


#endif	/* SWITCHERS_H */

