#include "dsEInt.h"

void initialize_external_interrupt(ext_interrupts sel_interrupt,
                                    edge_select edge, rp_pin  pin)
{
    switch (sel_interrupt) {
        case INT_0:
            INTCON2bits.INT0EP = (edge == NEG_EDGE) ? 1 : 0;
            IFS0bits.INT0IF = 0;
            break;
        case INT_1:
            set_rpp_input(pin, INT1);
            INTCON2bits.INT1EP = (edge == NEG_EDGE) ? 1 : 0;
            IFS1bits.INT1IF = 0;
            break;
        case INT_2:
            set_rpp_input(pin, INT2);
            INTCON2bits.INT2EP = (edge == NEG_EDGE) ? 1 : 0;
            IFS1bits.INT2IF = 0;
            break;
    }
}

bool external_interrupt_ocurred(ext_interrupts sel_interrupt, bool clear)
{
    switch (sel_interrupt) {
        case INT_0:
            if (IFS0bits.INT0IF) {
                if (clear)
                    IFS0bits.INT0IF = 0;
                return true;
            } else {
                return false;
            }
        case INT_1:
            if (IFS1bits.INT1IF) {
                if (clear)
                    IFS1bits.INT1IF = 0;
                return true;
            } else {
                return false;
            }
        case INT_2:
            if (IFS1bits.INT2IF) {
                if (clear)
                    IFS1bits.INT2IF = 0;
                return true;
            } else {
                return false;
            }
        default:
            return false;
    }
}
