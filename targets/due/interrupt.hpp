#ifndef LLIB_DUE_INTERRUPT_HPP
#define LLIB_DUE_INTERRUPT_HPP

#include "base.hpp"
#include "pins.hpp"
#include "spi.hpp"

namespace llib::due {
    enum class interrupt {
        CHANGE,
        LOW,
        HIGH,
        RISING,
        FALLING
    };

    using interrupt_callback = void (*)();

    namespace {
        template<typename Handler>
        constexpr void _enable_interrupt_source() {
            // enable clock of peripheral
            enable_clock<Handler>();

            // Disable irq
            NVIC->ICER[Handler::irqn >> 5] = (1 << (Handler::irqn & 0x1F));

            // Clean pending irq
            NVIC->ICPR[Handler::irqn >> 5] = (1 << (Handler::irqn & 0x1F));

            // Set priority to 0
            NVIC->IP[Handler::irqn] = 0;

            // Enable irq
            NVIC->ISER[Handler::irqn >> 5] = (1 << (Handler::irqn & 0x1F));
        }

        template<typename Handler>
        constexpr void _disable_interrupt_source() {
            // Disable irq
            NVIC->ICER[Handler::irqn >> 5] = (1 << (Handler::irqn & 0x1F));

            // Clean pending irq
            NVIC->ICPR[Handler::irqn >> 5] = (1 << (Handler::irqn & 0x1F));
        }        

        template<typename Pin>
        void _enable_interrupt_source_for_pin() {
            // check if an interupt has already been set in the pio of the pin
            if(!(pins::port<typename Pin::port>->PIO_IMR)){
                _enable_interrupt_source<typename Pin::port>();
            }
        }


        template<typename Pin, interrupt Mode>
        constexpr void _set_interrupt_mode() {
            const auto mask = pins::mask<Pin>;

            if constexpr (Mode == interrupt::CHANGE) {
                // Disable additional interrupt mode (detects both rising and falling edges)
                pins::port<typename Pin::port>->PIO_AIMDR = mask;
            } else {
                // Enable additional interrupt mode
                pins::port<typename Pin::port>->PIO_AIMER = mask;

                // Select mode
                if constexpr (Mode == interrupt::LOW) {
                    pins::port<typename Pin::port>->PIO_LSR = mask;
                    pins::port<typename Pin::port>->PIO_FELLSR = mask;
                } else if constexpr (Mode == interrupt::HIGH) {
                    pins::port<typename Pin::port>->PIO_LSR = mask;
                    pins::port<typename Pin::port>->PIO_REHLSR = mask;
                } else if constexpr (Mode == interrupt::FALLING) {
                    pins::port<typename Pin::port>->PIO_ESR = mask;
                    pins::port<typename Pin::port>->PIO_FELLSR = mask;
                } else if constexpr (Mode == interrupt::RISING) {
                    pins::port<typename Pin::port>->PIO_ESR = mask;
                    pins::port<typename Pin::port>->PIO_REHLSR = mask;
                }
            }

            // Enable interrupt
            pins::port<typename Pin::port>->PIO_IER = mask;
        }

        template<typename Port>
        struct _callbacks {
            static interrupt_callback callbacks[32];
        };

        template<typename Port>
        interrupt_callback _callbacks<Port>::callbacks[32] = {};


        template<typename Handler>
        constexpr void _handle_isr(uint32_t status_register, uint32_t interrupt_mask) {
            uint8_t trailing_zeros = 0;

            while ((trailing_zeros = __CLZ(__RBIT(status_register & interrupt_mask))) < 32) {
                auto bit = static_cast<uint8_t>(trailing_zeros);

                if (llib::due::_callbacks<Handler>::callbacks[bit] != nullptr) {
                    llib::due::_callbacks<Handler>::callbacks[bit]();
                }

                status_register = status_register & (~(1 << bit));
            }
        }        

        template<typename Handler, uint32_t Mask>
        constexpr void _set_callback_func(interrupt_callback func){     
            uint32_t mask = Mask;   
            uint8_t trailing_zeros = 0;

            // reverse the bit order and do a leading zero's check ( so we are counting the trailing zero's)
            while ((trailing_zeros = __CLZ(__RBIT(mask))) < 32) {
                auto bit = static_cast<uint8_t>(trailing_zeros);

                // TODO: fix the crash as this crashes the due atm   
                // set the function on the positions of the bits in the mask
                //llib::due::_callbacks<Handler>::callbacks[bit] = func;
            
                mask &= (~(1 << bit));
            }   
        }

        template<typename Handler, uint32_t Mask>
        constexpr void _unset_callback_func(){  
            uint32_t mask = Mask;   
            uint8_t trailing_zeros = 0;

            // reverse the bit order and do a leading zero's check ( so we are counting the trailing zero's)
            while ((trailing_zeros = __CLZ(__RBIT(mask))) < 32) {
                auto bit = static_cast<uint8_t>(trailing_zeros);

                // TODO: fix the crash as this crashes the due atm   
                // set the function on the positions of the bits in the mask
                //llib::due::_callbacks<Handler>::callbacks[bit] = NULL;
            
                mask &= (~(1 << bit));
            }
        }        
    }

    template<typename Pin, interrupt Mode>
    void attach_interrupt(interrupt_callback func) {        
        _enable_interrupt_source_for_pin<Pin>();
        _set_callback_func<typename Pin::port, Pin::number>(func);        
        _set_interrupt_mode<Pin, Mode>();
    }

    template<typename Pin>
    void detach_interrupt() {
        pins::port<typename Pin::port>->PIO_IDR = pins::mask<Pin>;

        if(!(pins::port<typename Pin::port>->PIO_IMR)){
            // no more pins attached to interrupt on this pio so disable iqrn
            _disable_interrupt_source<typename Pin::port>();
        }
    }

    template<typename Handler, uint32_t mask>
    void attach_interrupt(interrupt_callback func) {
        // add function to iqrn on positions of mask and enable the iqrn interupt
        _set_callback_func<Handler, mask>(func);
        _enable_interrupt_source<Handler>();
    }

    template<typename Handler, uint32_t mask>
    void detach_interrupt() {
        // add function to iqrn on positions of mask and enable the iqrn interupt
        _unset_callback_func<Handler, mask>();

        // check if any of the callbacks is used 
        // Todo: Change to check if the interupt mask register is set
        for(auto i = 0; i < 32; i++){
            if(llib::due::_callbacks<Handler>::callbacks[i] != NULL){
                return;
            }
        }

        // disable interrupt if all callbacks are disabled
        _disable_interrupt_source<Handler>();
    }    
}

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

void __SPI0_Handler() {
    llib::due::_handle_isr<llib::due::spi::spi0>(
        llib::due::spi::port<llib::due::spi::spi0>->SPI_SR,
        llib::due::spi::port<llib::due::spi::spi0>->SPI_IMR
    );
}
}

#endif //LLIB_DUE_INTERRUPT_HPP
