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

        // check for interrupts on the control endpoint
        if (UOTGHS->UOTGHS_DEVISR & UOTGHS_DEVISR_PEP_0) {
            // disable overflow and underflow interrupt
            UOTGHS->UOTGHS_DEVEPTIDR[0] = UOTGHS_DEVEPTIDR_NAKINEC | 
                                          UOTGHS_DEVEPTIDR_NAKOUTEC;

            // check what event happend on the control endpoint
            const uint32_t status = UOTGHS->UOTGHS_DEVEPTISR[0];

            if (status & UOTGHS_DEVEPTISR_RXSTPI) {
                // setup packet received

                // check if the received amount is correct for an control packet
                if (get_byte_count(status) != 8) {
                    // stall all in and out packets on Endpoint
                    UOTGHS->UOTGHS_DEVEPTIER[0] = UOTGHS_DEVEPTIER_STALLRQS;

                    // ack the setup request to clear the interrupt
                    UOTGHS->UOTGHS_DEVEPTICR[0] = UOTGHS_DEVEPTICR_RXSTPIC;

                    return;                    
                }

                // get the fifo address of the control endpoint
                uint8_t *fifo = get_fifo<0>();

                // copy the fifo to a setup packet
                auto setup_packet = (*reinterpret_cast<
                    llib::usb::setup::setup_packet*
                >(fifo));

                if (!decode_setup(setup_packet)) {
                    // setup request unknown stall
                    UOTGHS->UOTGHS_DEVEPTIER[0] = UOTGHS_DEVEPTIER_STALLRQS;

                    // ack the setup request
                    UOTGHS->UOTGHS_DEVEPTICR[0] = UOTGHS_DEVEPTICR_RXSTPIC;

                    return;
                }

                // ack the setup request
                UOTGHS->UOTGHS_DEVEPTICR[0] = UOTGHS_DEVEPTICR_RXSTPIC;

            } else if ((status & 0x1) && (UOTGHS->UOTGHS_DEVEPTIMR[0] & 0x1)) {
                // in packet received

            } else if (status & UOTGHS_DEVEPTISR_RXOUTI) {
                // out packet received

            } else if (status & UOTGHS_DEVEPTISR_NAKOUTI) {
                // overflow on out packet
                UOTGHS->UOTGHS_DEVEPTICR[0] = UOTGHS_DEVEPTICR_NAKOUTIC;

            } else if (status & UOTGHS_DEVEPTISR_NAKINI) {
                // underflow on in packet
                UOTGHS->UOTGHS_DEVEPTICR[0] = UOTGHS_DEVEPTICR_NAKINIC;

                // ignore underflow if out data is received
                if (!(UOTGHS->UOTGHS_DEVEPTISR[0] & UOTGHS_DEVEPTISR_RXOUTI)) {
                    return;
                }
            }

            // stop the interupt as we handled the control interrupt
            return;
        }

        // check for interrupts on the other endpoints 
        // if () {
        // 
        // }        

        // usb reset interrupt
        if (UOTGHS->UOTGHS_DEVISR & UOTGHS_DEVISR_EORST) {
            // ack the reset
            UOTGHS->UOTGHS_DEVICR = UOTGHS_DEVICR_EORSTC;

            // reset usb address to 0 and enable usb device address
            UOTGHS->UOTGHS_DEVCTRL &= ~UOTGHS_DEVCTRL_UADD_Msk;
            UOTGHS->UOTGHS_DEVCTRL |= UOTGHS_DEVCTRL_UADD(0) | UOTGHS_DEVCTRL_ADDEN;

            // clear the control endpoint settings
            UOTGHS->UOTGHS_DEVEPTCFG[0] &= ~(UOTGHS_DEVEPTCFG_EPTYPE_Msk | 
                                             UOTGHS_DEVEPTCFG_EPDIR | 
                                             UOTGHS_DEVEPTCFG_EPSIZE_Msk | 
                                             UOTGHS_DEVEPTCFG_EPBK_Msk);

            // Configure control endpoint
            UOTGHS->UOTGHS_DEVEPTCFG[0] |= UOTGHS_DEVEPTCFG_EPSIZE_8_BYTE | 
                                           UOTGHS_DEVEPTCFG_EPBK_1_BANK;

            // allocate configured enpoint in dpram
            UOTGHS->UOTGHS_DEVEPTCFG[0] = UOTGHS_DEVEPTCFG_ALLOC;

            // enable control endpoint
            UOTGHS->UOTGHS_DEVEPT |= UOTGHS_DEVEPT_EPEN0;

            // disable interrupts
            __disable_irq();

            // enable setup and out interrupts
            UOTGHS->UOTGHS_DEVEPTIER[0] = UOTGHS_DEVEPTIER_RXOUTES | UOTGHS_DEVEPTIER_RXSTPES;

            // enable endpoint 0 interrupt
            UOTGHS->UOTGHS_DEVIER = UOTGHS_DEVIER_PEP_0;

            // disable in interrupt
            UOTGHS->UOTGHS_DEVEPTIDR[0] = UOTGHS_DEVEPTIDR_TXINEC;

            // restore the interrupt status
            __enable_irq();

            // In case of OUT ZLP event is no processed before Setup event occurs
            UOTGHS->UOTGHS_DEVEPTICR[0] = UOTGHS_DEVEPTICR_RXOUTIC;

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

        // vbus transition interrupt
        if (UOTGHS->UOTGHS_SR & UOTGHS_SR_VBUSTI) {
            // unfreeze the clock
            UOTGHS->UOTGHS_CTRL &= ~UOTGHS_CTRL_FRZCLK;

            // ack vbus transition
            UOTGHS->UOTGHS_SCR = UOTGHS_SCR_VBUSTIC;

            // check if vbus is high to know if we 
            // attached or detached from usb
            if (!(UOTGHS->UOTGHS_SR & UOTGHS_SR_VBUS)) {
                // detach the device from the bus
                UOTGHS->UOTGHS_DEVCTRL |= UOTGHS_DEVCTRL_DETACH;

                // freeze the usb clock
                UOTGHS->UOTGHS_CTRL |= UOTGHS_CTRL_FRZCLK;

                return;
            }

            // disable global interrupts
            __disable_irq();

            // wait until usb clock is locked
            while (!(UOTGHS->UOTGHS_SR & UOTGHS_SR_CLKUSABLE)) {}

            // authorize attach if vbus is present
            UOTGHS->UOTGHS_DEVCTRL &= ~UOTGHS_DEVCTRL_DETACH;

            // enable interupt flags
            UOTGHS->UOTGHS_DEVIER = UOTGHS_DEVIER_EORSTES | UOTGHS_DEVIER_SUSPES | 
                                    UOTGHS_DEVIER_WAKEUPES | UOTGHS_DEVIER_SOFES;

            // ack interrupt flags
            UOTGHS->UOTGHS_DEVICR = UOTGHS_DEVIMR_MSOFE | UOTGHS_DEVICR_SOFC | 
                                    UOTGHS_DEVICR_EORSTC;

            // The first suspend interrupt must be forced
            UOTGHS->UOTGHS_DEVIFR = UOTGHS_DEVIFR_SUSPS;

            // ack the wakeup
            UOTGHS->UOTGHS_DEVICR = UOTGHS_DEVICR_WAKEUPC;

            // disable global interrupts
            __enable_irq();

            // freeze the usb clock
            UOTGHS->UOTGHS_CTRL |= UOTGHS_CTRL_FRZCLK;

            return;
        }

    } 

    void uotghs::init_usb() {
        // enable global interrupts
        __disable_irq();   

        // enable the usb otg clock
        enable_clock<uotghs>();

        // enable UPLL clock
        PMC->CKGR_UCKR = CKGR_UCKR_UPLLCOUNT(3) | CKGR_UCKR_UPLLEN;

        // wait for clock to lock status
        while (!(PMC->PMC_SR & PMC_SR_LOCKU)) {}

        // set the clock input (PLLB) and the clock divider
        PMC->PMC_USB = PMC_USB_USBS | PMC_USB_USBDIV(0);

        // enable the udp usb clock
        PMC->PMC_SCER = PMC_SCER_UOTGCLK;

        // set the interrupt properties
        NVIC_SetPriority(static_cast<IRQn_Type>(irqn), 5);

        // enable the interrupt
        NVIC_EnableIRQ(static_cast<IRQn_Type>(irqn));

        // always authorize asynchrone USB interrupts to exit of sleep mode
        // for SAM USB wake up device except BACKUP mode
        PMC->PMC_FSMR |= PMC_FSMR_USBAL;

        // disable USB ID pin so it is ignored by the usb
        UOTGHS->UOTGHS_CTRL &= ~UOTGHS_CTRL_UIDE;

        // set the device mode (should have no effect as UIDE is disabled)
        UOTGHS->UOTGHS_CTRL |= UOTGHS_CTRL_UIMOD;

        // enable the otg pad and enable otg usb
        UOTGHS->UOTGHS_CTRL |= UOTGHS_CTRL_OTGPADE | UOTGHS_CTRL_USBE;

        // disable low speed mode
        UOTGHS->UOTGHS_DEVCTRL &= ~UOTGHS_DEVCTRL_LS;

        // force device to stay in full speed mode
        UOTGHS->UOTGHS_DEVCTRL |= UOTGHS_DEVCTRL_SPDCONF_FORCED_FS;

        // unfreeze the clock
        UOTGHS->UOTGHS_CTRL &= ~UOTGHS_CTRL_FRZCLK;

        // wait until the clock is usable
        while (!(UOTGHS->UOTGHS_SR & UOTGHS_SR_CLKUSABLE)) {}

        // ack the vbus transition
        UOTGHS->UOTGHS_SCR = UOTGHS_SCR_VBUSTIC;

        // force Vbus interrupt in case of Vbus always with a high level
        // this is possible with a short timing between a Host mode stop/start.
        if (UOTGHS->UOTGHS_SR & UOTGHS_SR_VBUS) {
            // raise a vbus transition
            UOTGHS->UOTGHS_SFR = UOTGHS_SFR_VBUSTIS;
        }        

        // enable the vbus transition interrupt
        UOTGHS->UOTGHS_CTRL |= UOTGHS_CTRL_VBUSTE;

        // freeze the usb clock
        UOTGHS->UOTGHS_CTRL |= UOTGHS_CTRL_FRZCLK;

        // enable global interrupts
        __enable_irq();        
    }

    bool uotghs::decode_setup(const llib::usb::setup::setup_packet &p) {
        using namespace llib::usb::setup;

        // check on correct length for device_to_host messages first
        if (get_direction(p.bmRequestType) == direction::device_to_host) {
            if (p.wLength == 0) {
                // error from usb host
                return false;
            }
        }

        // check if the tyep is a standard request
        if (get_request_type(p.bmRequestType) == request_type::standard) {
            switch (get_recipient_code(p.bmRequestType)) {
                case recipient_code::device:
                    // handle standard device request
                    return true;
                    break;
                case recipient_code::interface:
                    // handle standard interface requests
                    return true;
                    break;
                case recipient_code::endpoint:
                    // handle standard endpoint requests
                    return true;
                    break;
                default:
                    break;
            }

            return false;
        }

        if (get_recipient_code(p.bmRequestType) == recipient_code::interface) {
            return true;
        }

        if (get_recipient_code(p.bmRequestType) == recipient_code::endpoint) {
            return true;
        }        

        return false;
    }
}

extern "C" {
void __UOTGHS_Handler() {
    // call the usb otg handler
    llib::due::usb::uotghs::__isr_handler();
}    
}