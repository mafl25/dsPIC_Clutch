/* 
 * File:   dsStepper.h
 * Author: Manuel
 *
 * Created on October 26, 2015, 2:09 PM
 */

#ifndef DSSTEPPER_H
#define	DSSTEPPER_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#define TRIS_STEPPER_OUT_A(A)   TRISBbits.TRISB2 = (A)
#define TRIS_STEPPER_OUT_B(A)   TRISBbits.TRISB3 = (A)
#define TRIS_STEPPER_OUT_C(A)   TRISBbits.TRISB4 = (A)
#define TRIS_STEPPER_OUT_D(A)   TRISBbits.TRISB5 = (A)

#define STEPPER_OUT_A(A)        LATBbits.LATB2 = (A)
#define STEPPER_OUT_B(A)        LATBbits.LATB3 = (A)
#define STEPPER_OUT_C(A)        LATBbits.LATB4 = (A)
#define STEPPER_OUT_D(A)        LATBbits.LATB5 = (A)

#define AN_STEPPER_OUT_A(A)     AD1PCFGLbits.PCFG4 = (A)
#define AN_STEPPER_OUT_B(A)     AD1PCFGLbits.PCFG5 = (A)
#define AN_STEPPER_OUT_C(A)
#define AN_STEPPER_OUT_D(A)

#define STEPPER_REG_UPDATE(A)   LATB = (LATB & 0xFFC3) | ((A) << 2)

void stepper_setup(void);
void step_forward(void);
void step_backward(void);
void stepper_shut_down(void);

#endif	/* DSSTEPPER_H */

