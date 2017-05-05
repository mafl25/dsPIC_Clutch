#include "dsEserial.h"

static volatile unsigned int *rts;
static unsigned int rts_mask;
static volatile unsigned int *cts;
static unsigned int cts_mask;
static volatile bool stop_receive;

#define SET_ONE(A, B)   (A | B)
#define SET_ZERO(A, B)  (A & (~B))

void eserial1_initialize(uint16_t brg, bool brgh, rp_pin tx_pin, rp_pin rx_pin,
                        volatile unsigned int *rts_latch, 
                        unsigned int rts_pin_mask, 
                        volatile unsigned int *cts_latch, 
                        unsigned int cts_pin_mask)
{
    rts = rts_latch;
    rts_mask = rts_pin_mask;
    cts = cts_latch;
    cts_mask = cts_pin_mask;
    
    *rts = SET_ONE(*rts, rts_mask);
    
    uint16_t reg_1_value = UART_EN | UART_TX_RX | UART_8BIT_NO_PAR;
    reg_1_value |= (brgh) ? UART_BRGH : 0;
    
    initialize_UART1(reg_1_value, UART_TX_INT_MODE3 | UART_RX_EN | UART_TX_EN 
                     | UART_RX_INT_MODE3, brg, tx_pin, rx_pin, NONE, NONE);
    
}

int16_t eserial1_send(struct circular_buffer *buffer)
{
    int16_t i = 0;
    int16_t value = buffer_pop(buffer);
    while (value != -1) {
        UART1_send_byte((uint8_t)value);  
        value = buffer_pop(buffer);
        i++;
    }
    
    return i;    
}
void eserial1_receive(struct circular_buffer *buffer, 
                         bool (*stop_function)(void))
{
    if (!buffer_full(buffer)) {
        
        //Reads whatever was in the buffer
        int16_t value = UART1_receive_byte();
        while (value >= 0) {
            buffer_push(buffer, value);
            value = UART1_receive_byte();
        }
        if (value < -1)
            goto Error;
        
        //Tells the PC to send new data
        stop_receive = false;
        *rts = SET_ZERO(*rts, rts_mask);
        if (stop_function != NULL) {
            bool test = false;
            while (buffer_space(buffer) && !test && !stop_receive) {
                value = UART1_receive_byte();
                if (value >= 0) 
                    buffer_push(buffer, value);
                else if (value < -1)
                    goto Error;
                test = (*stop_function)();
            }
        } else {
            while (buffer_space(buffer) && !stop_receive) {
                value = UART1_receive_byte();
                if (value >= 0) 
                    buffer_push(buffer, value);
                else if (value < -1)
                    goto Error;
            }
        }
        *rts = SET_ONE(*rts, rts_mask);
    }
    
    return;

    Error:
    UART1_reset();
    UART1_send_byte('v');
    return;
}

void eserial1_stop(void)
{
    *rts = SET_ONE(*rts, rts_mask);
    stop_receive = true;
}

#undef SET_ONE
#undef SET_ZERO