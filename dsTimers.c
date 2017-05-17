#include "dsTimers.h"

void initialize_timer1(uint16_t T1CON_reg, uint16_t PR_value)
{     
    T1CONbits.TON = 0;
    if (T1CON_reg & TMR1_TGATE)
        T1CON = T1CON_reg & 0xFFFD;
    else
        T1CON = T1CON_reg;
    
    PR1 = PR_value;
    TMR1 = 0x00;
    IFS0bits.T1IF = 0;
}


void initialize_timer2(uint16_t T2CON_reg, uint16_t PR_value)
{
    T2CONbits.TON = 0;
    if (T2CON_reg & TMR2_TGATE)
        T2CON = T2CON_reg & 0xFFFD;
    else
        T2CON = T2CON_reg;
    
    PR2 = PR_value;
    TMR2 = 0x00;   
}

void initialize_timer3(uint16_t T3CON_reg, uint16_t PR_value)
{
    T3CONbits.TON = 0;
    if (T3CON_reg & TMR3_TGATE)
        T3CON = T3CON_reg & 0xFFFD;
    else
        T3CON = T3CON_reg;
    
    PR3 = PR_value;
    TMR3 = 0x00;   
}

void set_timer(timer timer_sel, uint16_t value)
{
    switch (timer_sel) {
        case TIMER1:
            PR1 = value;
            TMR1 = 0;
            IFS0bits.T1IF = 0;
            break;
        case TIMER2:
            PR2 = value;
            TMR2 = 0;
            IFS0bits.T2IF = 0;
            break;
        case TIMER3:
            PR3 = value;
            TMR3 = 0;
            IFS0bits.T3IF = 0;
            break;
        case TIMER4:
            PR4 = value;
            TMR4 = 0;
            IFS1bits.T4IF = 0;
            break;
    }
}

bool timer_up(timer timer_sel)
{
    switch (timer_sel) {
        case TIMER1:
            return IFS0bits.T1IF;
        case TIMER2:
            return IFS0bits.T2IF;
        case TIMER3:
            return IFS0bits.T3IF;
        case TIMER4:
            return IFS1bits.T4IF;
        default:
            return false;
    }    
}

void init_timer_interrupt(timer timer_sel, uint8_t priority_level)
{
    if (priority_level > 7)
        priority_level = 7;
   
    switch (timer_sel) {
        case TIMER1:
            IPC0bits.T1IP = priority_level;
            IEC0bits.T1IE = 1;
            IFS0bits.T1IF = 0;
            break;
        case TIMER2:
            IPC1bits.T2IP = priority_level;
            IEC0bits.T2IE = 1;
            IFS0bits.T2IF = 0;
            break;
        case TIMER3:
            IPC2bits.T3IP = priority_level;
            IEC0bits.T3IE = 1;
            IFS0bits.T3IF = 0;
            break;
        case TIMER4:
            IPC6bits.T4IP = priority_level;
            IEC1bits.T4IE = 1;
            IFS1bits.T4IF = 0;
            break;
    }   
}

void clear_timer_interrupt(timer timer_sel)
{
    switch (timer_sel) {
        case TIMER1:
            IFS0bits.T1IF = 0;
            break;
        case TIMER2:
            IFS0bits.T2IF = 0;
            break;
        case TIMER3:
            IFS0bits.T3IF = 0;
            break;
        case TIMER4:
            IFS1bits.T4IF = 0;
            break;
    }   
}