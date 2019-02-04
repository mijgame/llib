#ifndef LLIB_DUE_INTERRUPT_HPP
#define LLIB_DUE_INTERRUPT_HPP

#include "base.hpp"
#include "pins.hpp"

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
        template<typename Port>
        constexpr void _enable_interrupt_source() {
            // Disable irq
            NVIC->ICER[Port::irqn >> 5] = (1 << (Port::irqn & 0x1F));

            // Clean pending irq
            NVIC->ICPR[Port::irqn >> 5] = (1 << (Port::irqn & 0x1F));

            // Set priority to 0
            NVIC->IP[Port::irqn] = 0;

            // Enable irq
            NVIC->ISER[Port::irqn >> 5] = (1 << (Port::irqn & 0x1F));
        }

        template<typename Pin>
        void _enable_interrupt_source_for_pin() {
            static bool enabled = false;

            if (!enabled) {
                _enable_interrupt_source<typename Pin::port>();
                enabled = true;
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
    }

    template<typename Pin, interrupt Mode>
    void attach_interrupt(interrupt_callback func) {
        _enable_interrupt_source_for_pin<Pin>();
        _set_interrupt_mode<Pin, Mode>();
    }

    template<typename Pin>
    void detach_interrupt() {
        pins::port<typename Pin::port>->PIO_IDR = pins::mask<Pin>;
    }

}

extern "C" {
void PIOA_HANDLER() {
    uint32_t isr = PIOA->PIO_ISR;
    uint8_t leading_zeros;

    while ((leading_zeros = __CLZ(isr)) < 32) {
        auto pin = static_cast<uint8_t>(32 - leading_zeros - 1);

        if (llib::due::_callbacks<llib::target::pioa>::callbacks[pin]) {
            llib::due::_callbacks<llib::target::pioa>::callbacks[pin]();
        }

        isr = isr & (~(1 << pin));
    }
}

void PIOB_HANDLER() {
    uint32_t isr = PIOB->PIO_ISR;
    uint8_t leading_zeros;

    while ((leading_zeros = __CLZ(isr)) < 32) {
        auto pin = static_cast<uint8_t>(32 - leading_zeros - 1);

        if (llib::due::_callbacks<llib::target::piob>::callbacks[pin]) {
            llib::due::_callbacks<llib::target::piob>::callbacks[pin]();
        }

        isr = isr & (~(1 << pin));
    }
}

void PIOC_HANDLER() {
    uint32_t isr = PIOC->PIO_ISR;
    uint8_t leading_zeros;

    while ((leading_zeros = __CLZ(isr)) < 32) {
        auto pin = static_cast<uint8_t>(32 - leading_zeros - 1);

        if (llib::due::_callbacks<llib::target::pioc>::callbacks[pin]) {
            llib::due::_callbacks<llib::target::pioc>::callbacks[pin]();
        }

        isr = isr & (~(1 << pin));
    }
}

void PIOD_HANDLER() {
    uint32_t isr = PIOD->PIO_ISR;
    uint8_t leading_zeros;

    while ((leading_zeros = __CLZ(isr)) < 32) {
        auto pin = static_cast<uint8_t>(32 - leading_zeros - 1);

        if (llib::due::_callbacks<llib::target::piod>::callbacks[pin]) {
            llib::due::_callbacks<llib::target::piod>::callbacks[pin]();
        }

        isr = isr & (~(1 << pin));
    }
}
}

#endif //LLIB_DUE_INTERRUPT_HPP
