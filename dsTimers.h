/* 
 * File:   timers.h
 * Author: Manuel
 *
 * Created on August 21, 2015, 10:58 AM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {TIMER1, TIMER2, TIMER3, TIMER4} timer;

#define TMR1_ON         0x8000
#define TMR1_HALT       0x2000
#define TMR1_TGATE      0x0040
#define TMR1_SCALE_256  0x0030
#define TMR1_SCALE_64   0x0020
#define TMR1_SCALE_8    0x0010
#define TMR1_SCALE_1    0x0000
#define TMR1_EXT_SYNC   0x0004
#define TMR1_EXT_CLK    0x0002

void initialize_timer1(uint16_t T1CON_reg, uint16_t PR_value);

#define TMR2_ON         0x8000
#define TMR2_HALT       0x2000
#define TMR2_TGATE      0x0040
#define TMR2_SCALE_256  0x0030
#define TMR2_SCALE_64   0x0020
#define TMR2_SCALE_8    0x0010
#define TMR2_SCALE_1    0x0000
#define TMR2_32         0x0008
#define TMR2_EXT_CLK    0x0002

void initialize_timer2(uint16_t T2CON_reg, uint16_t PR_value);

#define TMR3_ON         0x8000
#define TMR3_HALT       0x2000
#define TMR3_TGATE      0x0040
#define TMR3_SCALE_256  0x0030
#define TMR3_SCALE_64   0x0020
#define TMR3_SCALE_8    0x0010
#define TMR3_SCALE_1    0x0000
#define TMR3_EXT_CLK    0x0002

void initialize_timer3(uint16_t T3CON_reg, uint16_t PR_value);

void set_timer(timer timer_sel, uint16_t value);
bool timer_up(timer timer_sel);
void init_timer_interrupt(timer timer_sel, uint8_t priority_level);
void clear_timer_interrupt(timer timer_sel);

#endif	/* TIMERS_H */

