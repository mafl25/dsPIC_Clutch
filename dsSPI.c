#include "dsSPI.h"
#include "dsTimers.h"
#include "dsEInt.h"

void initialize_SPI1(uint16_t SPI1STAT_reg, uint16_t SPI1CON1_reg,
                     uint16_t SPI1CON2_reg, rp_pin SDO_pin, rp_pin SDI_pin, 
                     rp_pin SCK_pin, rp_pin SS_pin)
{
    if ((SPI1CON2_reg & SPI1_FRAMED) == SPI1_FRAMED)  // Maybe use unions
       SPI1CON1_reg = SPI1CON1_reg & 0xFE7F;
    
    if (((SPI1CON1_reg & SPI1_SPRE_1) == SPI1_SPRE_1)
        && ((SPI1CON1_reg & SPI1_PPRE_1) == SPI1_PPRE_1))
        SPI1CON1_reg = SPI1CON1_reg & 0xFFFE;
    
    if (((SPI1CON1_reg & SPI1_MASTER) != SPI1_MASTER)
        && ((SPI1CON1_reg & SPI1_DATA_SAMPLE) == SPI1_DATA_SAMPLE))
        SPI1CON1_reg = SPI1CON1_reg & 0xFDFF;
    
    SPI1CON1 = SPI1CON1_reg; //The SMP bit must be set only after setting the MSTEN bit. The SMP bit remains clear if MSTEN = 0. <- Check later
    SPI1CON2 = SPI1CON2_reg;
    SPI1STAT = SPI1STAT_reg;
    
    if (SPI1CON1bits.MSTEN) {
        if (!SPI1CON1bits.DISSCK && SCK_pin != NONE) {
            set_rpp_input(SCK_pin, I_SCK1);
            set_rpp_output(SCK_pin, O_SCK1);
        }
        
        if (!SPI1CON1bits.DISSDO && SDO_pin != NONE)
            set_rpp_output(SDO_pin, SDO1); 
        
        if(SS_pin != NONE)
            set_rpp_output(SS_pin, RP_NULL);
    } else {
        if (SPI1CON1bits.SSEN && SS_pin != NONE)
            set_rpp_input(SS_pin, I_SS1);
        
        set_rpp_input(SCK_pin, I_SCK1);
        
        if(SDO_pin != NONE)
            set_rpp_output(SDO_pin, SDO1); 
    }
   
    set_rpp_input(SDI_pin, SDI1);
}

uint16_t spi1_send_get_data(uint16_t data)
{
    while(SPI1STATbits.SPITBF);
    IFS0bits.SPI1IF = 0;
    SPI1STATbits.SPIROV = 0;
    SPI1BUF = data;
    while(!SPI1STATbits.SPIRBF);
    return SPI1BUF;
}


static void wait_pulse(uint8_t value, uint16_t timeout, timer timer_sel)
{
    set_timer(timer_sel, timeout);
    while (!external_interrupt_ocurred(INT_1, true)) {//Change this into interrupt function
        if (timer_up(timer_sel)) { 
            spi1_send_get_data(value);
            set_timer(timer_sel, timeout);
        }
    }
}

static void send_delay(uint16_t time, timer timer_sel)
{
    set_timer(timer_sel, time);
    while(!timer_up(timer_sel));
}

void espi1_master_receive(struct circular_buffer *buffer, timer timer_sel,
                          uint16_t timeout, uint16_t delay)
{
    if (!buffer_full(buffer)) {
        spi1_send_get_data(RX_CHAR);
        
        wait_pulse(RX_CHAR, timeout, timer_sel);

        uint8_t received_1;
        uint8_t received_2;
        uint8_t value;
        while (buffer_space(buffer)) {
            received_1 = spi1_send_get_data(0xE0);
            send_delay(delay, timer_sel);
            if (received_1 == END_CHAR)
                return;
            
            received_2 = spi1_send_get_data(0xE0); 
            send_delay(delay, timer_sel);
            if (received_2 == END_CHAR)
                return;
            
            if (decode_data(&value, received_1, received_2) == 0)
                buffer_push(buffer, value);
        }

        spi1_send_get_data(END_CHAR);
        send_delay(delay, timer_sel);
    }
}

void espi1_master_send(struct circular_buffer *buffer, timer timer_sel,
                       uint16_t timeout, uint16_t delay)
{
    if (buffer_count(buffer)) {
        spi1_send_get_data(TX_CHAR);
        
        wait_pulse(TX_CHAR, timeout, timer_sel);
        
        uint16_t byte_to_send;
        uint8_t byte_1;
        uint8_t byte_2;
        uint8_t received_1;
        uint8_t received_2;
        
        while (1) {
            byte_to_send = buffer_peek(buffer);
            if (byte_to_send == -1)
                break;
            encode_data(byte_to_send, &byte_1, &byte_2);  //Remember that timers act different
            
            received_1 = spi1_send_get_data(byte_1);  //Use the oscilloscope
            send_delay(delay, timer_sel);
            if (received_1 == END_CHAR)
                return;
            
            received_2 = spi1_send_get_data(byte_2); //This data will be lost if the buffer in the receiver is full.
            send_delay(delay, timer_sel);
            if (received_2 == END_CHAR)
                return;
            
            buffer_pop(buffer);
        }   
        
        spi1_send_get_data(END_CHAR);  //Remember, if buffer gets filled, the last byte sent gets lost
        send_delay(delay, timer_sel);
    }
}