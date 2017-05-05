/* 
 * File:   dsEserial.h
 * Author: Manuel
 *
 * Created on October 2, 2015, 3:50 PM
 */

#ifndef DSESERIAL_H
#define	DSESERIAL_H

#include "dsUART.h"
#include "circular_buffer.h"

void eserial1_initialize(uint16_t brg, bool brgh, rp_pin tx_pin, rp_pin rx_pin,
                        volatile unsigned int *rts_latch, 
                        unsigned int rts_pin_mask, 
                        volatile unsigned int *cts_latch, 
                        unsigned int cts_pin_mask);
int16_t eserial1_send(struct circular_buffer *buffer);
void eserial1_receive(struct circular_buffer *buffer, 
                         bool (*stop_function)(void));
void eserial1_stop(void); // Need to implement this

#endif	/* DSESERIAL_H */

