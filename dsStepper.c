#include "dsStepper.h"

static volatile uint8_t current_stepper_state;
static volatile uint8_t output_stepper_value[8] = {0x01, 0x03, 0x02, 0x06,
                                                   0x04, 0x0C, 0x08, 0x09};

void stepper_setup(void)
{
    AN_STEPPER_OUT_A(1);
    AN_STEPPER_OUT_B(1);
    AN_STEPPER_OUT_C(1);
    AN_STEPPER_OUT_D(1);
    
    STEPPER_OUT_A(0);
    STEPPER_OUT_B(0);
    STEPPER_OUT_C(0);
    STEPPER_OUT_D(0);
    
    TRIS_STEPPER_OUT_A(0);
    TRIS_STEPPER_OUT_B(0);
    TRIS_STEPPER_OUT_C(0);
    TRIS_STEPPER_OUT_D(0);
}

void step_forward(void)
{
    current_stepper_state++;
    current_stepper_state &= 0x07;
    
    STEPPER_REG_UPDATE(output_stepper_value[current_stepper_state]);
}

void step_backward(void)
{
    current_stepper_state--;
    current_stepper_state &= 0x07;
    
    STEPPER_REG_UPDATE(output_stepper_value[current_stepper_state]); 
}

void stepper_shut_down(void)
{
    STEPPER_REG_UPDATE(0);
}