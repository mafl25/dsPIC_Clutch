/* 
 * File:   remappable.h
 * Author: Manuel
 *
 * Created on August 21, 2015, 4:19 PM
 */

#ifndef REMAPPABLE_H
#define	REMAPPABLE_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {RP_NULL, C1OUT, C2OUT, U1TX, U1RTS, U2TX, U2RTS, SDO1, O_SCK1,
              O_SS1, SDO2, O_SCK2, O_SS2, CSDO, O_CSCK, O_COFS, C1TX,
              RP_OC1 = 0b10010, RP_OC2, RP_OC3, RP_OC4, RP_INPUT} rp_output; 
typedef enum {INT1, INT2, T2CK, T3CK, T4CK, T5CK, RP_IC1, RP_IC2, RP_IC7,
              RP_IC8, OCFA, U1RX, U1CTS, U2RX, U2CTS, SDI1, I_SCK1, I_SS1, SDI2,
              I_SCK2, I_SS2, CSDI, I_CSCK, I_COFS, CIRX} rp_input;
typedef enum {RP0, RP1, RP2, RP3, RP4, RP5, RP6, RP7, RP8, RP9, RP10, RP11,
              RP12, RP13, RP14, RP15, VSS = 0b11111, NONE} rp_pin;
              
void set_rpp_output(rp_pin pin, rp_output output);
void set_rpp_input(rp_pin pin, rp_input output);

#endif	/* REMAPPABLE_H */
