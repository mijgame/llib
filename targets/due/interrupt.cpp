#include "interrupt.hpp"

extern "C" {
void __PIOA_Handler() {
    llib::due::_handle_isr<llib::due::pioa>(
        llib::due::pins::port<llib::due::pioa>->PIO_ISR,
        llib::due::pins::port<llib::due::pioa>->PIO_IMR
    );
}

void __PIOB_Handler() {
    llib::due::_handle_isr<llib::due::piob>(
        llib::due::pins::port<llib::due::piob>->PIO_ISR,
        llib::due::pins::port<llib::due::piob>->PIO_IMR
    );
}

void __PIOC_Handler() {
    llib::due::_handle_isr<llib::due::pioc>(
        llib::due::pins::port<llib::due::pioc>->PIO_ISR,
        llib::due::pins::port<llib::due::pioc>->PIO_IMR
    );
}

void __PIOD_Handler() {
    llib::due::_handle_isr<llib::due::piod>(
        llib::due::pins::port<llib::due::piod>->PIO_ISR,
        llib::due::pins::port<llib::due::piod>->PIO_IMR
    );
}
}
