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
#include "dsStepper.h"

void enable_interrupts(bool nested, uint8_t interrupt_level);
void disable_interrpts(void);

uint16_t read_adc_ch0(void) {
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE);
    AD1CON1bits.DONE = 0;
    return ADC1BUF0;
}

void ADC_init(void);

#define MAX_STEPS       1000
#define STEPPER_BYTE    0xEE
static volatile int16_t stepper_position;
static volatile bool continuos_steps; 
static volatile bool stepper_direction;
static volatile uint16_t step_count;
static volatile uint16_t stepper_interval;

#define SPEED_BYTE 0xEA
bool volatile stop_go;
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

static volatile bool send_status;

bool stop_func(void)
{
    return send_status;
}

int main(void) {
    
    initialize_oscillator(0, 0, 0, DOZE_1, FRC_1, OUT_2, 2, 39, ACLK_256, 0x1E);
    

    initialize_UART2(UART_EN | UART_TX_RX | UART_8BIT_NO_PAR | UART_BRGH, 
                     UART_TX_INT_MODE3 | UART_RX_EN | UART_TX_EN 
                     | UART_RX_INT_MODE3, 9, RP9, RP15, NONE, NONE);
    
    eserial1_initialize(32, true, RP11, RP12, &LATB, _LATB_LATB10_MASK, &LATB, 
                        _LATB_LATB13_MASK);
    TRISBbits.TRISB10 = 0;
    AD1PCFGLbits.PCFG11 = 1;
    TRISBbits.TRISB13 = 0;
    
    initialize_timer2(TMR2_ON | TMR2_SCALE_1, 1019);
    initialize_PWM1(TIMER2, NONE, false, false); 
    PWM1_set_value(1023);
    PWM1_set_output(RP6);
    
    initialize_timer3(TMR3_ON | TMR3_SCALE_64, 3123);
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
    stepper_shut_down();
        
    uint16_t received_value = 0;
    struct circular_buffer _receive = {0, 0, {0}};
    struct circular_buffer *receive = &_receive;
    
    struct circular_buffer _send = {0, 0, {0}};
    struct circular_buffer *send = &_send;
    
    while(1) {
        
        eserial1_receive(receive, stop_func);
        
        while (buffer_count(receive) >= 3) {
            received_value = buffer_pop(receive);
            uint8_t byte_1;
            uint8_t byte_2;  // I assume I will always receive at least three bytes
            
            switch (received_value) {
                case 0xAC:
                    byte_1 = buffer_pop(receive);
                    byte_2 = buffer_pop(receive);
                    PWM1_set_value(1023 - (byte_1 << 2 | byte_2));
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
                    break;
                case 0xCA:
                    buffer_pop(receive);
                    buffer_pop(receive);
                    stop_go = true;
                    break;
                case 0xCB:
                    buffer_pop(receive);
                    buffer_pop(receive);
                    stop_go = false;
                    break;
            }    
        }
            
        if (send_status) {
            UART2_send_byte(0xAA);
            
            int16_t byte_2;
            int16_t byte_1;
            int16_t byte_0;

            do {
                byte_2 = UART2_receive_byte();
            } while (byte_2 < 0);
            do {
                byte_1 = UART2_receive_byte();
            } while (byte_1 < 0);
            do {
                byte_0 = UART2_receive_byte();
            } while (byte_0 < 0);
            
            
            buffer_push(send, 0x55);
            buffer_push(send, 0xDD);
            buffer_push(send, 0x07);
            buffer_push(send, STEPPER_BYTE);
            buffer_push(send, (stepper_position >> 8) & 0xFF);
            buffer_push(send, stepper_position & 0xFF);
            buffer_push(send, SPEED_BYTE);
            buffer_push(send, byte_2);
            buffer_push(send, byte_1);
            buffer_push(send, byte_0);
            send_status = false;
        }
        
        eserial1_send(send);
    }
    
    return (0);
}



void __attribute__((__interrupt__, __no_auto_psv__)) _T3Interrupt(void)
{
    clear_timer_interrupt(TIMER3);
    eserial1_stop();
    
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
        } else {
            stepper_shut_down();
        }
        stepper_interval_count = 0;
    }
    stepper_interval_count++;
    
    static uint16_t status_count = 1; 
    if (status_count == 1) {
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

