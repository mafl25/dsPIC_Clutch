#include "dsOscillator.h"

void initialize_oscillator(uint16_t register_1, uint16_t register_2, 
                           uint16_t register_3, doze_sel doze, 
                           frc_div_sel FRC_div, pll_post_sel PLL_post, 
                           uint8_t PLL_pre, uint16_t PLL_mul,
                           aclk_sel ACLK_div, uint8_t tuning)
{
    OSCCON = register_1;
    
    if (PLL_pre > 33 || PLL_pre < 2)
        PLL_pre = 0;
    else 
        PLL_pre -= 2;
    
    CLKDIV = register_2;
    CLKDIVbits.DOZE = doze;
    CLKDIVbits.PLLPOST = PLL_post;
    CLKDIVbits.PLLPRE = PLL_pre;
    
    if (PLL_mul > 513 || PLL_mul < 2)
        PLL_mul = 0;
    else
        PLL_mul -= 2;
    
    PLLFBD = PLL_mul;
    
    if (tuning > 63)
        tuning = 0;
    
    OSCTUN = tuning;
    
    ACLKCON = register_3;
    ACLKCONbits.ASRCSEL = ACLK_div;      
}

bool clock_fail(bool clear)
{
    bool value = OSCCONbits.CF;
    if (clear)
        OSCCONbits.CF = 0;
    return value;
}

void enable_secondary_osc(bool enable)
{
    OSCCONbits.LPOSCEN = enable;
}

void switch_oscillator(bool wait)
{
    OSCCONbits.OSWEN = 1;
    if (wait)
        while (OSCCONbits.OSWEN);
}
