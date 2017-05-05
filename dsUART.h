/* 
 * File:   dsUART.h
 * Author: Manuel
 *
 * Created on October 2, 2015, 3:34 PM
 */

#ifndef DSUART_H
#define	DSUART_H

#include <xc.h>
#include <stdint.h>
#include <libpic30.h>
#include "remappable.h"

#define UART_EN             0x8000
#define UART_STOP_IDLE      0x2000
#define UART_IRDA_EN        0x1000
#define UART_RTS_SIMPLEX    0x0800
#define UART_ALTERNATE      0x0400
#define UART_TX_RX_BCLK     0x0300
#define UART_TX_RX_CTS_RTS  0x0200
#define UART_TX_RX_RTS      0x0100
#define UART_TX_RX          0x0000
#define UART_WAKE_SLEEP     0x0080
#define UART_LOOPBACK_MODE  0x0040
#define UART_AUTO_BAUDRATE  0x0020
#define UART_RX_POL         0x0010
#define UART_BRGH           0x0008
#define UART_9BIT_NO_PAR    0x0006
#define UART_8BIT_ODD_PAR   0x0004
#define UART_8BIT_EVEN_PAR  0x0002
#define UART_8BIT_NO_PAR    0x0000
#define UART_2STOP_BITS     0x0001

#define UART_TX_INT_MODE1   0x8000
#define UART_TX_INT_MODE2   0x2000
#define UART_TX_INT_MODE3   0x0000
#define UART_TX_POL         0x4000
#define UART_RX_EN          0x1000
#define UART_TX_BREAK       0x0800
#define UART_TX_EN          0x0400
#define UART_RX_INT_MODE1   0x00C0
#define UART_RX_INT_MODE2   0x0080
#define UART_RX_INT_MODE3   0x0000
#define UART_ADDRESS_MODE   0x0020

void initialize_UART1(uint16_t register_1, uint16_t register_2, uint16_t brg,
                      rp_pin tx_pin, rp_pin rx_pin, rp_pin cts, rp_pin rts);
void UART1_reset(void);
void UART1_send_byte(uint8_t byte);
int16_t UART1_receive_byte(void);


void initialize_UART2(uint16_t register_1, uint16_t register_2, uint16_t brg,
                      rp_pin tx_pin, rp_pin rx_pin, rp_pin cts, rp_pin rts);
void UART2_reset(void);
void UART2_send_byte(uint8_t byte);
int16_t UART2_receive_byte(void);

#endif	/* DSUART_H */

