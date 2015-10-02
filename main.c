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
#include "dsOscillator.h"
#include "dsEserial.h"


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

void ADC_init(void);


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

static volatile bool continuos_steps; 
static volatile bool stepper_direction;
static volatile uint16_t step_count;
static volatile uint16_t stepper_interval;
static volatile uint8_t current_stepper_state;
static volatile uint8_t output_stepper_value[8] = {0x01, 0x03, 0x02, 0x06,
                                                   0x04, 0x0C, 0x08, 0x09};

void stepper_setup(void);
void step_forward(void);
void step_backward(void);


static volatile bool send_status;
#define MAX_STEPS       1000
static volatile int16_t stepper_position;


volatile uint16_t set_point;



#define TIMEOUT         312
#define SEND_DELAY      14

bool stop_func(void)
{
//    static int count = 0;
//    count++;
//    
//    if (count > 32) {
//        count = 0;
//        return true;
//    } else {
//        return false;
//    }
    
    return send_status;
}

int main(void) {
    
    initialize_oscillator(0, 0, 0, DOZE_1, FRC_1, OUT_2, 2, 39, ACLK_256, 0x1E);
    
    ADC_init();
    
//    initialize_timer1(TMR1_ON | TMR1_SCALE_64, 6246);
//    initialize_SPI1(SPI1_ENABLE, SPI1_MASTER | SPI1_SPRE_8 | SPI1_PPRE_64 | SPI1_CLK_POL,
//                    0 ,RP10, RP11, RP12, NONE);
//    initialize_external_interrupt(INT_1, POS_EDGE, RP13);
    
    eserial1_initialize(86, true, RP11, RP12, &LATB, _LATB_LATB10_MASK, &LATB, 
                        _LATB_LATB13_MASK);
    TRISBbits.TRISB10 = 0;
    AD1PCFGLbits.PCFG11 = 1;
    TRISBbits.TRISB13 = 0;
    
    initialize_timer2(TMR2_ON | TMR2_SCALE_1, 1019);
    initialize_PWM1(TIMER2, NONE, false, false); 
    PWM1_set_value(0);
    
    initialize_timer3(TMR3_ON | TMR3_SCALE_64, 1873);
    enable_interrupts(false, 0);
    init_timer_interrupt(TIMER3, 1);
    
    stepper_setup();
    stepper_interval = 50;
    TRISBbits.TRISB8 = 1;
    
    while(!PORTBbits.RB8) {
        step_backward();
        stepper_position = 0;
        __delay_ms(5);
    }
        
    
    uint16_t received_value = 0;
    
    set_point = 512;

    struct circular_buffer _receive = {0, 0, {0}};
    struct circular_buffer *receive = &_receive;
    
    struct circular_buffer _send = {0, 0, {0}};
    struct circular_buffer *send = &_send;
    
    while(1) {
        
//        espi1_master_receive(receive, TIMER1, TIMEOUT, SEND_DELAY);
        eserial1_receive(receive, stop_func);
        
        while (buffer_count(receive) >= 3) {
            received_value = buffer_pop(receive);
            uint8_t byte_1;
            uint8_t byte_2;  // I assume I will always receive at least three bytes
            
            switch (received_value) {
                case 0xAC:
                    byte_1 = buffer_pop(receive);
                    byte_2 = buffer_pop(receive);
                    set_point = (byte_1 << 2 | byte_2);
                    break;
                case 0xAA:
                    byte_1 = buffer_pop(receive);
                    byte_2 = buffer_pop(receive);
                    break;
                case 0xBA:
                    stepper_direction = buffer_pop(receive);
                    step_count = buffer_pop(receive);
                    continuos_steps = false;
                    break;
                case 0xBB:
                    stepper_direction = buffer_pop(receive);
                    buffer_pop(receive);
                    step_count = 0;
                    continuos_steps = true;
                    break;
                case 0xBC:
                    byte_1 = buffer_pop(receive);
                    byte_2 = buffer_pop(receive);
                    stepper_interval = (byte_1 << 8 | byte_2);
            }    
        }
            
        if (send_status) {
            buffer_push(send, 0x55);
            buffer_push(send, 0xDD);
            buffer_push(send, 0x00);
            send_status = false;
        }
        

//        espi1_master_send(send, TIMER1, TIMEOUT, SEND_DELAY);
        eserial1_send(send);
    }
    
    return (0);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _T3Interrupt(void)
{
    clear_timer_interrupt(TIMER3);
    float set = set_point / 1023.0;
    float adc_value = read_adc_ch0() / 1023.0;
    float result = proportional(set,  adc_value, 5.0);
    if (result > 1.0)
        result = 1.0;
    else if (result < -1.0)
        result = -1.0;
    
    result *= 1023;
    set_value_motor((int16_t)result);
    static uint16_t stepper_interval_count = 1;
    if (stepper_interval_count >= stepper_interval) {
        if (step_count || continuos_steps) {
            if (stepper_direction) {
                if (stepper_position <= MAX_STEPS) {
                    step_forward();
                    if (!PORTBbits.RB8)
                        stepper_position++;
                } else {
                    continuos_steps = false;
                    step_count = 0;
                }
            } else if (!PORTBbits.RB8) {
                step_backward();
                stepper_position--;
            } else  {
                continuos_steps = false;
                step_count = 0;
                stepper_position = 0;
            }
            
            if (step_count)
                step_count--;
        }
        stepper_interval_count = 0;
    }
    stepper_interval_count++;
    
    static uint16_t status_count = 1; 
    if (status_count == 40) {
        send_status = true;
        status_count = 0;
    }
    status_count++;
    
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

void ADC_init(void)
{
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
}

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