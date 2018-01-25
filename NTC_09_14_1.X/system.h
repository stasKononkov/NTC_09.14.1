#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "interrupt_priorities.h"

#define INT_CRYSTAL_FREQ        7370000L
extern uint32_t sysFreq;
#define SYS_FREQ        (sysFreq)
#define FCY             (SYS_FREQ/2)

#include <libpic30.h>
#define system_delay_us(d ) \
  { __delay32( (unsigned long) (((float) d)*(FCY)/1e6f)); }

void system_init();
void system_reset() __attribute__((noreturn));
void interrupts_disable();
void interrupts_enable();

uint32_t get_system_frequency();



#endif	/* SYSTEM_H */

