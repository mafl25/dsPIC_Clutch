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

int16_t read_adc_ch0(void);
void ADC_init(void);
void set_value_motor(int16_t value);



static volatile bool send_status;

bool stop_func(void)
{
    return send_status;
}

int main(void) {
    
    initialize_oscillator(0, 0, 0, DOZE_1, FRC_1, OUT_2, 2, 39, ACLK_256, 0x18);
    
    TRISBbits.TRISB10 = 0;
    AD1PCFGLbits.PCFG11 = 1;
    TRISBbits.TRISB13 = 0;
    eserial1_initialize(32, true, RP11, RP12, &LATB, _LATB_LATB10_MASK, &LATB, 
                        _LATB_LATB13_MASK);
    
    
    initialize_timer3(TMR3_ON | TMR3_SCALE_64, 1249);  //Check how often
    enable_interrupts(false, 0);
    init_timer_interrupt(TIMER3, 1);

    
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    LATBbits.LATB6 = 0;
    LATBbits.LATB7 = 0;

    /*Comm buffers*/
    uint16_t received_value = 0;
    struct circular_buffer _receive = {0, 0, {0}};
    struct circular_buffer *receive = &_receive;
    
    struct circular_buffer _send = {0, 0, {0}};
    struct circular_buffer *send = &_send;
    
    
    ADC_init();
    initialize_timer2(TMR2_ON | TMR2_SCALE_1, 1019);
    initialize_PWM1(TIMER2, NONE, false, false); 
    
    double output;
    double Kp = 0;
    double Ki = 0;
    double Kd = 0;
    double der;
    double integral = 0;
    double err = 0;
    double perr = 0;
    double set = 0.0;
    double actual;
    double dt = 0.002;
    
    int count = 0;
    bool run_pid = false;
    bool which = false;
    bool der_filter_on = false;
    
    //FILTER
    double R = 100;
    double C = 100e-6;
    double beta = 1/(1+2*R*C/dt);
    double alpha = (1-2*R*C/dt);
    double unfiltered_output[2] = {0};
    double filtered_output[2] = {0};
    
    while(1) {
        
        eserial1_receive(receive, stop_func);
        
        while (buffer_count(receive) >= 5) {
            received_value = buffer_pop(receive);
            uint8_t byte_1;
            uint8_t byte_2;  // I assume I will always receive at least three bytes*/
            
            /**Instruction processing*/
            switch (received_value) {
                case 0xAA:
                    buffer_pop(receive);
                    buffer_pop(receive);
                    buffer_pop(receive);
                    buffer_pop(receive);
                    set = (double)read_adc_ch0();
                    run_pid = true;
                    break;
                case 0xAB:
                    buffer_pop(receive);
                    buffer_pop(receive);
                    buffer_pop(receive);
                    buffer_pop(receive);
                    set_value_motor(0);
                    run_pid = false;
                    break;
                case 0xAC:
                    buffer_pop(receive);
                    buffer_pop(receive);
                    byte_1 = buffer_pop(receive);
                    byte_2 = buffer_pop(receive);
                    set = ((double)(byte_1 << 2 | byte_2) - 1023.0*0.5);
                    break;
                case 0xAD:             
                    ((unsigned char *)(&Kp))[0] = buffer_pop(receive);
                    ((unsigned char *)(&Kp))[1] = buffer_pop(receive);
                    ((unsigned char *)(&Kp))[2] = buffer_pop(receive);
                    ((unsigned char *)(&Kp))[3] = buffer_pop(receive);
                    break;
                case 0xAE:             
                    ((unsigned char *)(&Kd))[0] = buffer_pop(receive);
                    ((unsigned char *)(&Kd))[1] = buffer_pop(receive);
                    ((unsigned char *)(&Kd))[2] = buffer_pop(receive);
                    ((unsigned char *)(&Kd))[3] = buffer_pop(receive);
                    break;
                case 0xAF:             
                    ((unsigned char *)(&Ki))[0] = buffer_pop(receive);
                    ((unsigned char *)(&Ki))[1] = buffer_pop(receive);
                    ((unsigned char *)(&Ki))[2] = buffer_pop(receive);
                    ((unsigned char *)(&Ki))[3] = buffer_pop(receive);
                    break;
                case 0xB0:             
                    buffer_pop(receive);
                    buffer_pop(receive);
                    buffer_pop(receive);
                    der_filter_on = buffer_pop(receive);
                    break;
            }    
        }
        
        if (send_status) { 
            
            if (run_pid) {
                actual = (double)read_adc_ch0();
                err = set - actual;
                integral += err;
                der = err - perr;
                
                if (der_filter_on){
                    unfiltered_output[1] = der;
                    filtered_output[1] = beta*(unfiltered_output[1] + unfiltered_output[0] - alpha*filtered_output[0]);
                    unfiltered_output[0] = unfiltered_output[1];
                    filtered_output[0] = filtered_output[1];
                    der = filtered_output[1];
                }
              
                output = Kp * err + (Ki * integral *  dt) + (Kd * der / dt);
                if (integral >  2000.0) {
                    integral = 2000.0;   
                }else if (integral < -2000.0) {
                    integral = -2000.0;
                }
                perr = err;

                int pwm_value = (int)(output);
                if (pwm_value >  1023) {
                    pwm_value = 1023;   
                }else if (pwm_value < -1023) {
                    pwm_value = -1023;
                }
                set_value_motor(pwm_value);                     
            }
          
            buffer_push(send, 0x55);
            buffer_push(send, 0xDD);
            buffer_push(send, 0x00);  //No bytes being sent adjust according to data that must be sent
            
            /*buffer_push(send, 0x05);
            buffer_push(send, 0xEA);
            buffer_push(send, ((unsigned char *)(&output))[0]);
            buffer_push(send, ((unsigned char *)(&output))[1]);
            buffer_push(send, ((unsigned char *)(&output))[2]);
            buffer_push(send, ((unsigned char *)(&output))[3]);
            /*buffer_push(send, byte_1);
            buffer_push(send, byte_0);*/
           
            send_status = false;
            count++;
        }
        
        eserial1_send(send);
        /*if (count > 200) {
            count = 0;
            if (!which){
                set = 200;
                which = true;
            }else{
                set = -200;
                which = false;
            }
        }*/
    }
    
    return (0);
}



void __attribute__((__interrupt__, __no_auto_psv__)) _T3Interrupt(void)
{
    clear_timer_interrupt(TIMER3);
    eserial1_stop();
    
    //LATBbits.LATB6 = ~LATBbits.LATB6;
    
    send_status = true;
    
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
    AD1CON1bits.FORM = 0b01; //  Integer (DOUT = 0000 dddd dddd dddd)
    AD1CON1bits.SSRC = 0b111; // Clearing sample bit ends sampling and starts conversion
    AD1CON1bits.SIMSAM = 0; // Samples multiple channels individually in sequence.
    AD1CON1bits.ASAM = 0; // Sampling begins when SAMP bit is set
    AD1CON1bits.ADON = 1;
}

int16_t read_adc_ch0(void) {
    AD1CON1bits.SAMP = 1;
    while(!AD1CON1bits.DONE);
    AD1CON1bits.DONE = 0;
    return ADC1BUF0;
}

void set_value_motor(int16_t value) {
    if (value >= 0) {
        PWM1_shut_output(RP7);
        PWM1_set_value(value);
        PWM1_set_output(RP6);
    } else {
        value *= -1;
        PWM1_shut_output(RP6);
        PWM1_set_value(value);
        PWM1_set_output(RP7);       
    }
}
