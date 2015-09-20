#include "remappable.h"

void set_rpp_output(rp_pin pin, rp_output output)
{
    switch (pin) {
        case RP0:
            AD1PCFGLbits.PCFG2 = 1;
            RPOR0bits.RP0R = output;  
            TRISBbits.TRISB0 = 0;
            break;
        case RP1:
            AD1PCFGLbits.PCFG3 = 1;
            RPOR0bits.RP1R = output;
            TRISBbits.TRISB1 = 0;       
            break;
        case RP2:
            AD1PCFGLbits.PCFG4 = 1;
            RPOR1bits.RP2R = output;
            TRISBbits.TRISB2 = 0;            
            break;
        case RP3:
            AD1PCFGLbits.PCFG5 = 1;
            RPOR1bits.RP3R = output;
            TRISBbits.TRISB3 = 0;
            break;
        case RP4:
            RPOR2bits.RP4R = output;
            TRISBbits.TRISB4 = 0;
            break;
        case RP5:
            RPOR2bits.RP5R = output;
            TRISBbits.TRISB5 = 0;
            break;
        case RP6:
            RPOR3bits.RP6R = output;
            TRISBbits.TRISB6 = 0;
            break;
        case RP7:
            RPOR3bits.RP7R = output;
            TRISBbits.TRISB7 = 0;
            break;
        case RP8:
            RPOR4bits.RP8R = output;
            TRISBbits.TRISB8 = 0;
            break;
        case RP9:
            RPOR4bits.RP9R = output;
            TRISBbits.TRISB9 = 0;
            break;
        case RP10:
            RPOR5bits.RP10R = output;
            TRISBbits.TRISB10 = 0;
            break;
        case RP11:
            RPOR5bits.RP11R = output;
            TRISBbits.TRISB11 = 0;
            break;
        case RP12:
            AD1PCFGLbits.PCFG12 = 1;
            RPOR6bits.RP12R = output;
            TRISBbits.TRISB12 = 0;
            break;
        case RP13:
            AD1PCFGLbits.PCFG11 = 1;
            RPOR6bits.RP13R = output;
            TRISBbits.TRISB13 = 0;
            break;
        case RP14:
            AD1PCFGLbits.PCFG10 = 1;
            RPOR7bits.RP14R = output;
            TRISBbits.TRISB14 = 0;
            break;
        case RP15:
            AD1PCFGLbits.PCFG9 = 1;
            RPOR7bits.RP15R = output;
            TRISBbits.TRISB15 = 0;
            break;
        default:
            break;
    }
}

static void select_input_pin(rp_pin pin, rp_input input)
{
    switch (input) {
        case INT1:
            RPINR0bits.INT1R = pin;
            break;
        case INT2:
            RPINR1bits.INT2R = pin;
            break;
        case T2CK:
            RPINR3bits.T2CKR = pin;
            break;
        case T3CK:
            RPINR3bits.T3CKR = pin;
            break;
        case T4CK:
            RPINR4bits.T4CKR = pin;
            break;
        case T5CK:
            RPINR4bits.T5CKR = pin;
            break;
        case RP_IC1:
            RPINR7bits.IC1R = pin;
            break;
        case RP_IC2:
            RPINR7bits.IC2R = pin;
            break;
        case RP_IC7:
            RPINR10bits.IC7R = pin;
            break;
        case RP_IC8:
            RPINR10bits.IC8R = pin;
            break;
        case OCFA:
            RPINR11bits.OCFAR = pin;
            break;
        case U1RX:
            RPINR18bits.U1RXR = pin;
            break;
        case U1CTS:
            RPINR18bits.U1CTSR = pin;
            break;
        case U2RX:
            RPINR19bits.U2RXR = pin;
            break;
        case U2CTS:
            RPINR19bits.U2CTSR = pin;
            break;
        case SDI1:
            RPINR20bits.SDI1R = pin;
            break;
        case I_SCK1:
            RPINR20bits.SCK1R = pin;
            break;
        case I_SS1:
            RPINR21bits.SS1R = pin;
            break;
        case SDI2:
            RPINR22bits.SDI2R = pin;
            break;
        case I_SCK2:
            RPINR22bits.SCK2R = pin;
            break;
        case I_SS2:
            RPINR23bits.SS2R = pin;
            break;
        case CSDI:
            RPINR24bits.CSDIR = pin;
            break;
        case I_CSCK:
            RPINR24bits.CSCKR = pin;
            break;
        case I_COFS:
            RPINR25bits.COFSR = pin;
            break;
        case CIRX:
            RPINR26bits.C1RXR = pin;
            break;
    }    
}

void set_rpp_input(rp_pin pin, rp_input input)
{
    switch (pin) {
        case RP0:
            AD1PCFGLbits.PCFG2 = 1;
            TRISBbits.TRISB0 = 1;            
            break;
        case RP1:
            AD1PCFGLbits.PCFG3 = 1;
            TRISBbits.TRISB1 = 1;
            break;
        case RP2:
            AD1PCFGLbits.PCFG4 = 1;
            TRISBbits.TRISB2 = 1;
            break;
        case RP3:
            AD1PCFGLbits.PCFG5 = 1;
            TRISBbits.TRISB3 = 1;
            break;
        case RP4:
            TRISBbits.TRISB4 = 1;
            break;
        case RP5:
            TRISBbits.TRISB5 = 1;
            break;
        case RP6:
            TRISBbits.TRISB6 = 1;
            break;
        case RP7:
            TRISBbits.TRISB7 = 1;
            break;
        case RP8:
            TRISBbits.TRISB8 = 1;
            break;
        case RP9:
            TRISBbits.TRISB9 = 1;
            break;
        case RP10:
            TRISBbits.TRISB10 = 1;
            break;
        case RP11:
            TRISBbits.TRISB11 = 1;
            break;
        case RP12:
            AD1PCFGLbits.PCFG12 = 1;
            TRISBbits.TRISB12 = 1;
            break;
        case RP13:
            AD1PCFGLbits.PCFG11 = 1;
            TRISBbits.TRISB13 = 1;
            break;
        case RP14:
            AD1PCFGLbits.PCFG10 = 1;
            TRISBbits.TRISB14 = 1;
            break;
        case RP15:
            AD1PCFGLbits.PCFG9 = 1;
            TRISBbits.TRISB15 = 1;
            break;
        default:
            break;
    }
    
    select_input_pin(pin, input);
}