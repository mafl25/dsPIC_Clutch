/* 
 * File:   dsSPI.h
 * Author: Manuel
 *
 * Created on August 25, 2015, 2:55 PM
 */

#ifndef DSSPI_H
#define	DSSPI_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "remappable.h"
#include "circular_buffer.h"
#include "encoding.h"
#include "dsTimers.h"

//Reg 1
#define SPI1_ENABLE         0x8000
#define SPI1_HALT           0x2000
//Reg 2
#define SPI1_DISABLE_SCK    0x1000
#define SPI1_DISABLE_SDO    0x0800
#define SPI1_MODE_16        0x0400
#define SPI1_DATA_SAMPLE    0x0200
#define SPI1_CLK_EDGE       0x0100
#define SPI1_SS             0x0080
#define SPI1_CLK_POL        0x0040
#define SPI1_MASTER         0x0020
#define SPI1_SPRE_1         0x001C
#define SPI1_SPRE_2         0x0018
#define SPI1_SPRE_3         0x0014
#define SPI1_SPRE_4         0x0010
#define SPI1_SPRE_5         0x000C
#define SPI1_SPRE_6         0x0008
#define SPI1_SPRE_7         0x0004
#define SPI1_SPRE_8         0x0000
#define SPI1_PPRE_1         0x0003
#define SPI1_PPRE_4         0x0002
#define SPI1_PPRE_16        0x0001
#define SPI1_PPRE_64        0x0000
//Reg 3
#define SPI1_FRAMED         0x8000
#define SPI1_SPULSE_DIR     0x4000
#define SPI1_FRAME_POL      0x2000
#define SPI1_PULSE_EDGE     0x0002

void initialize_SPI1(uint16_t SPI1STAT_reg, uint16_t SPI1CON1_reg,
                     uint16_t SPI1CON2_reg, rp_pin SDO, rp_pin SDI, 
                     rp_pin SCK, rp_pin SS);

uint16_t spi1_send_get_data(uint16_t data);



#define TX_CHAR     0x10
#define RX_CHAR     0x20
#define END_CHAR    0x30
#define ERROR_CHAR  0x70

void initialized_espi1(void);

void espi1_master_receive(struct circular_buffer *buffer, timer timer_sel,
                          uint16_t timeout, uint16_t send_delay);
void espi1_master_send(struct circular_buffer *buffer, timer timer_sel,
                       uint16_t timeout, uint16_t send_delay);

#endif	/* DSSPI_H */

