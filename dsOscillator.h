/* 
 * File:   dsOscillator.h
 * Author: Manuel
 *
 * Created on September 25, 2015, 2:28 PM
 */

#ifndef DSOSCILLATOR_H
#define	DSOSCILLATOR_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#define NEW_FRC_DIV_N   0x0700
#define NEW_FRC_DIV_16  0x0600
#define NEW_LPRC        0x0500
#define NEW_SEC_OSC     0x0400
#define NEW_PRI_OSC_PLL 0x0300
#define NEW_PRI_OSC     0x0200
#define NEW_FRC_PLL     0x0100
#define NEW_FRC         0x0000
#define CLK_LOCK        0x0080
#define EN_SEC_OSC      0x0002
#define OSC_SWITCH      0x0001

#define INT_DIS_DOZE    0x8000
#define EN_DOZE         0x0800

#define SEL_ACLK        0x0200
#define ACLK_MODE_EC    0x1800    
#define ACLK_MODE_XT    0x1000
#define ACLK_MODE_HS    0x0800 
#define ACLK_DISABLED   0x0000  
#define SEL_CLK_SOURCE  0x0080

typedef enum {DOZE_1 = 0, DOZE_2, DOZE_4, DOZE_8, DOZE_16, DOZE_32, DOZE_64,
              DOZE_128} doze_sel;
typedef enum {FRC_1 = 0, FRC_2, FRC_4, FRC_8, FRC_16, FRC_32, FRC_64, FRC_256} 
              frc_div_sel;
typedef enum {OUT_2, OUT_4, OUT_8 = 3} pll_post_sel;
typedef enum {ACLK_256, ACLK_64, ACLK_32, ACLK_16, ACLK_8, ACLK_4, ACLK_2,
              ACLK_1} aclk_sel;

void initialize_oscillator(uint16_t register_1, uint16_t register_2, 
                           uint16_t register_3, doze_sel doze, 
                           frc_div_sel FRC_div, pll_post_sel PLL_post, 
                           uint8_t PLL_pre, uint16_t PLL_mul,
                           aclk_sel ACLK_div, uint8_t tuning);
bool clock_fail(bool clear);
void enable_secondary_osc(bool enable);
void switch_oscillator(bool wait);

#endif	/* DSOSCILLATOR_H */

