#include "interrupt.hpp"

extern "C" {
void __PIOA_Handler() {
    llib::sam3x8e::_handle_isr<llib::sam3x8e::pioa>(
        llib::sam3x8e::pins::port<llib::sam3x8e::pioa>->PIO_ISR,
        llib::sam3x8e::pins::port<llib::sam3x8e::pioa>->PIO_IMR
    );
}

void __PIOB_Handler() {
    llib::sam3x8e::_handle_isr<llib::sam3x8e::piob>(
        llib::sam3x8e::pins::port<llib::sam3x8e::piob>->PIO_ISR,
        llib::sam3x8e::pins::port<llib::sam3x8e::piob>->PIO_IMR
    );
}

void __PIOC_Handler() {
    llib::sam3x8e::_handle_isr<llib::sam3x8e::pioc>(
        llib::sam3x8e::pins::port<llib::sam3x8e::pioc>->PIO_ISR,
        llib::sam3x8e::pins::port<llib::sam3x8e::pioc>->PIO_IMR
    );
}

void __PIOD_Handler() {
    llib::sam3x8e::_handle_isr<llib::sam3x8e::piod>(
        llib::sam3x8e::pins::port<llib::sam3x8e::piod>->PIO_ISR,
        llib::sam3x8e::pins::port<llib::sam3x8e::piod>->PIO_IMR
    );
}
}
