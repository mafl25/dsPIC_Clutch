/* 
 * File:   main.c
 * Author: Manuel
 *
 * Created on August 13, 2015, 6:13 PM
 */
#include <xc.h>

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Mode (Internal Fast RC (FRC) w/ PLL)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

#define FOSC 79900000UL
#define FCY ((FOSC)/2)
#include <libpic30.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <dsp.h>
#include "dsTimers.h"
#include "remappable.h"
#include "dsPWM.h"
#include "dsSPI.h"
#include "dsEInt.h"


/*
 * #define FCY 40000000
 * #define BAUDRATE 9600
 * #define BRGVAL ((FCY/BAUDRATE)/16) - 1
 * 
 */

void enable_interrupts(bool nested, uint8_t interrupt_level);
void disable_interrpts(void);

uint16_t read_adc_ch0(void) {
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE);
    AD1CON1bits.DONE = 0;
    return ADC1BUF0;
}

float proportional(float setpoint, float value, float constant)
{
    return (setpoint - value) * constant;
}



void set_value_motor(int16_t value) {
    if (value >= 0) {
        PWM1_shut_output(RP7);
        PWM1_set_output(RP6);
    } else {
        value *= -1;
        PWM1_shut_output(RP6);
        PWM1_set_output(RP7);       
    }
    
    PWM1_set_value(value);
}


volatile uint16_t set_point;

#define TIMEOUT         312
#define SEND_DELAY      14

int main(void) {

    OSCTUN = 0x1E;   // Center frequency +11.25% (8.20 MHz)
    CLKDIVbits.FRCDIV = 0;  // FRC divide by 1 (default)
    CLKDIVbits.PLLPRE = 0;  // Input/2 (default)
    PLLFBD = 39;  // Input  * 39
    CLKDIVbits.PLLPOST = 0;  // Output/2 
    
    AD1PCFGLbits.PCFG9 = 0;
    
    AD1CHS0bits.CH0NA = 0;
    AD1CHS0bits.CH0SA = 9;
    
    AD1CON2bits.VCFG = 0; // AVDD, AVSS
    AD1CON2bits.CSCNA = 0; // Do not scan inputs
    AD1CON2bits.CHPS = 0; // Converts CH0
    AD1CON2bits.SMPI = 0; // Increments the DMA address after completion of every sample/conversion operation
    AD1CON2bits.BUFM = 0; // Always starts filling buffer at address 0x0
    AD1CON2bits.ALTS = 0; // Always uses channel input selects for Sample A
    
    AD1CON3bits.ADRC = 0; // Clock derived from system clock
    AD1CON3bits.ADCS = 3; // 4 · TCY = TAD
    
    AD1CON1bits.ADSIDL = 0; // Continue module operation in Idle mode
    AD1CON1bits.ADDMABM = 1; // DMA buffers are written in the order of conversion. Won't actually use it.
    AD1CON1bits.AD12B = 0; // 10-bit, 4-channel ADC operation
    AD1CON1bits.FORM = 0; // Signed fractional (DOUT = sddd dddd dd00 0000, where s =.NOT.d<9>)
    AD1CON1bits.SSRC = 0; // Clearing sample bit ends sampling and starts conversion
    AD1CON1bits.SIMSAM = 0; // Samples multiple channels individually in sequence.
    AD1CON1bits.ASAM = 1; // Sampling begins immediately after last conversion. SAMP bit is auto-set
    AD1CON1bits.ADON = 1;

    
    initialize_timer1(TMR1_ON | TMR1_SCALE_64, 6246);
    initialize_SPI1(SPI1_ENABLE, SPI1_MASTER | SPI1_SPRE_8 | SPI1_PPRE_64 | SPI1_CLK_POL,
                    0 ,RP10, RP11, RP12, NONE);
    initialize_external_interrupt(INT_1, POS_EDGE, RP13);
    
    initialize_timer2(TMR2_ON | TMR2_SCALE_1, 1019);
    initialize_PWM1(TIMER2, NONE, false, false); 
    PWM1_set_value(0);
    
    initialize_timer3(TMR3_ON | TMR3_SCALE_64, 6246);
    enable_interrupts(false, 0);
    init_timer_interrupt(TIMER3, 1);
    
    uint16_t value = 0;
    
    set_point = 512;

    struct circular_buffer _receive = {0, 0, {0}};
    struct circular_buffer *receive = &_receive;
    while(1) {
        
        espi1_master_receive(receive, TIMER1, TIMEOUT, SEND_DELAY);
        
        while (buffer_count(receive) >= 3) {
            value = buffer_pop(receive);
            uint8_t byte_1;
            uint8_t byte_2;  // I assume I will always receive at least three bytes
            
            switch (value) {
                case 0xAC:
                    byte_1 = buffer_pop(receive);
                    byte_2 = buffer_pop(receive);
                    set_point = (byte_1 << 2 | byte_2);
//                    value = read_adc_ch0();
//                    if (value > 100 && value < 923)
//                        PWM1_set_value(byte_1 << 2 | byte_2);
//                    else
//                        PWM1_set_value(0);
                    break;
                case 0xAA:
                    byte_1 = buffer_pop(receive);
                    byte_2 = buffer_pop(receive);
//                    if (byte_1 == 1) {
//                        if (byte_2)
//                            PWM1_set_output(RP6);
//                        else
//                            PWM1_shut_output(RP6);
//                    } else if (byte_1 == 2) {
//                        if (byte_2)
//                            PWM1_set_output(RP7);
//                        else
//                            PWM1_shut_output(RP7);
//                    }
                    break;
//                case 0xBA:
//                    right = buffer_pop(&receive);
//                    count = buffer_pop(&receive);
//                    continuous = false;
//                    break;
//                case 0xBB:
//                    right = buffer_pop(&receive);
//                    buffer_pop(&receive);
//                    count = 0;
//                    continuous = true;
//                    break;
            }    
        }
            
//        espi1_master_send(receive, TIMER1, TIMEOUT, SEND_DELAY);
    }
    
    return (0);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _T3Interrupt(void)
{
    float set = set_point / 1023.0;
    float adc_value = read_adc_ch0() / 1023.0;
    float result = proportional(set,  adc_value, 5.0);
    if (result > 1.0)
        result = 1.0;
    else if (result < -1.0)
        result = -1.0;
    
    result *= 1023;
    set_value_motor((int16_t)result);
    clear_timer_interrupt(TIMER3);
}

void enable_interrupts(bool nested, uint8_t interrupt_level)
{
    INTCON1bits.NSTDIS = nested;
    if (interrupt_level > 15)
        interrupt_level = 15;
    CORCONbits.IPL3 = interrupt_level >> 3;
    SRbits.IPL = interrupt_level;
}

void disable_interrupts(void)
{
    SRbits.IPL = 7;
}
