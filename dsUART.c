#include "dsUART.h"

void initialize_UART1(uint16_t register_1, uint16_t register_2, uint16_t brg,
                      rp_pin tx_pin, rp_pin rx_pin, rp_pin cts, rp_pin rts)
{
    set_rpp_output(tx_pin, U1TX);
    set_rpp_output(rts, U1RTS);
    set_rpp_input(rx_pin, U1RX);
    set_rpp_input(cts, U1CTS);
    
    U1MODE = register_1;
    U1STA = register_2;
    U1BRG = brg;
}

void UART1_reset(void)
{
    uint16_t mode = U1MODE;
    uint16_t sta = U1STA;
    
    U1MODEbits.UARTEN = 0;
    U1MODEbits.UARTEN = 1;
    
    U1MODE = mode;
    U1STA = sta;
}

void UART1_send_byte(uint8_t byte)
{
    while(U1STAbits.UTXBF);
    U1TXREG = byte;
}

int16_t UART1_receive_byte(void) 
{
    if (U1STAbits.OERR || U1STAbits.FERR || U1STAbits.PERR) {
        int16_t return_value = (U1STAbits.OERR << 3) | (U1STAbits.FERR << 2)
                                | (U1STAbits.PERR << 1);
        return_value *= -1;
        return return_value;
    } else if (U1STAbits.URXDA) {
        return U1RXREG; 
    } else {
        return -1;
    }
}