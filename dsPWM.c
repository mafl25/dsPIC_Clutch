#include "dsPWM.h"

void initialize_PWM1(timer selection, rp_pin output,
              bool halt_on_idle, bool fault_enable)
{
    if (output != NONE)
        set_rpp_output(output, RP_OC1);
    
    bool prev_timer_state;
    if (selection == TIMER3) {
        prev_timer_state = T3CONbits.TON;
        T3CONbits.TON = 0;
    } else {
        prev_timer_state = T2CONbits.TON;
        T2CONbits.TON = 0;
    }
    
    OC1CONbits.OCM = 0;
    OC1CONbits.OCTSEL = (selection == TIMER3) ? 1 : 0;
    OC1CONbits.OCSIDL = halt_on_idle;
    OC1R = 0;
    OC1RS = 0;
    OC1CONbits.OCM = (fault_enable) ? 0b111 : 0b110;
    
    if (selection == TIMER3) 
        T3CONbits.TON = prev_timer_state;
    else
        T2CONbits.TON = prev_timer_state;
} //Still need to learn about fault

void PWM1_set_value(uint16_t value)
{
    OC1RS = value;
}

void PWM1_change_output(rp_pin prev_output, rp_pin next_output)
{
    if (prev_output != NONE)
        set_rpp_output(prev_output, RP_NULL);
    
    if (next_output != NONE)
        set_rpp_output(next_output, RP_OC1);    
}

void PWM1_set_output(rp_pin output)
{
    if (output != NONE)
        set_rpp_output(output, RP_OC1);     
}

void PWM1_shut_output(rp_pin output)
{
    if (output != NONE)
        set_rpp_output(output, RP_NULL);     
}