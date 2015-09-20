/* 
 * File:   dsEInt.h
 * Author: Manuel
 *
 * Created on August 25, 2015, 3:17 PM
 */

#ifndef DSEINT_H
#define	DSEINT_H

#include <xc.h>
#include <stdbool.h>
#include "remappable.h"

typedef enum {POS_EDGE, NEG_EDGE} edge_select;
typedef enum {INT_0, INT_1, INT_2} ext_interrupts;

void initialize_external_interrupt(ext_interrupts sel_interrupt,
                                   edge_select edge, rp_pin  pin);
bool external_interrupt_ocurred(ext_interrupts sel_interrupt, bool clear);

#endif	/* DSEINT_H */

