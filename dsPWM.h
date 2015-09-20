/* 
 * File:   dsPWM.h
 * Author: Manuel
 *
 * Created on August 24, 2015, 1:27 PM
 */

#ifndef DSPWM_H
#define	DSPWM_H

#include <xc.h>
#include "dsTimers.h"
#include "remappable.h"

void initialize_PWM1(timer selection, rp_pin output,
              bool halt_on_idle, bool fault_enable);
void PWM1_set_value(uint16_t value);
void PWM1_change_output(rp_pin prev_output, rp_pin next_output);
void PWM1_set_output(rp_pin output);
void PWM1_shut_output(rp_pin output);

#endif	/* DSPWM_H */

