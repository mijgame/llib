#include "uotghs.hpp"

namespace llib::due::usb {
    void uotghs::__isr_handler() {
        // check for a start of a frame
        if (UOTGHS->UOTGHS_DEVISR & UOTGHS_DEVISR_SOF) {
            // ack start of frame
            UOTGHS->UOTGHS_DEVICR = UOTGHS_DEVICR_SOFC;

            // call user callback for start of frame
            return;            
        }

        // check for micro start of frame
        if (UOTGHS->UOTGHS_DEVISR & UOTGHS_DEVISR_MSOF) {
            // ack micro start of frame
            UOTGHS->UOTGHS_DEVICR = UOTGHS_DEVIMR_MSOFE;

            // call user callback
            return;
        }

        // usb reset interrupt
        if (UOTGHS->UOTGHS_DEVISR & UOTGHS_DEVISR_EORST) {
            // ack the reset
            UOTGHS->UOTGHS_DEVICR = UOTGHS_DEVICR_EORSTC;

            return;
        }

        // check for a wakeup interrupt
        if ((UOTGHS->UOTGHS_DEVISR & UOTGHS->UOTGHS_DEVIMR) & (1 << 4)) {
            // unfreeze the clock
            UOTGHS->UOTGHS_CTRL &= ~UOTGHS_CTRL_FRZCLK;

            // wait until usb clock is locked
            while (!(UOTGHS->UOTGHS_SR & UOTGHS_SR_CLKUSABLE)) {
                // break if USB state changed to high speed
                if (UOTGHS->UOTGHS_DEVISR & UOTGHS_DEVISR_SUSP) {
                    break;
                }
            }

            // disable wakeup interrupt
            UOTGHS->UOTGHS_DEVIDR = UOTGHS_DEVIDR_WAKEUPEC;

            // enable suspend interrupt
            UOTGHS->UOTGHS_DEVIER = UOTGHS_DEVIER_SUSPES;

            return;
        }

        // check for a suspend interrupt
        if ((UOTGHS->UOTGHS_DEVISR & UOTGHS->UOTGHS_DEVIMR) & 0x1) {
            // unfreeze the clock
            UOTGHS->UOTGHS_CTRL &= ~UOTGHS_CTRL_FRZCLK;

            // disable suspend interrupt
            UOTGHS->UOTGHS_DEVIDR = UOTGHS_DEVIDR_SUSPEC;

            // enable wakup interrupt
            UOTGHS->UOTGHS_DEVIER = UOTGHS_DEVIER_WAKEUPES;

            // freeze the usb clock
            UOTGHS->UOTGHS_CTRL |= UOTGHS_CTRL_FRZCLK;

            return;    
        } 

    } 

    void uotghs::init_usb() {
        // enable the usb otg clock
        enable_clock<uotghs>();

        // set the interrupt properties
        NVIC_SetPriority(static_cast<IRQn_Type>(irqn), 5);

        // enable the interrupt
        NVIC_EnableIRQ(static_cast<IRQn_Type>(irqn));

    }
}

extern "C" {
void __UOTGHS_Handler() {
    // call the usb otg handler
    llib::due::usb::uotghs::__isr_handler();
}    
}