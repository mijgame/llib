#ifndef LLIB_SAM3X8E_INTERRUPT_HPP
#define LLIB_SAM3X8E_INTERRUPT_HPP

#include <util.hpp>
#include "base.hpp"
#include "pins.hpp"

namespace llib::sam3x8e {
    enum class interrupt {
        CHANGE,
        LOW,
        HIGH,
        RISING,
        FALLING
    };

    using interrupt_callback = void (*)();

    namespace {
        template<typename Handler, uint8_t priority>
        constexpr void _enable_interrupt_source() {
            // Enable clock of peripheral
            enable_clock<Handler>();

            constexpr auto irqn = static_cast<IRQn_Type>(Handler::irqn);

            NVIC_DisableIRQ(irqn);
            NVIC_ClearPendingIRQ(irqn);
            NVIC_SetPriority(irqn, priority);
            NVIC_EnableIRQ(irqn);
        }

        template<typename Handler>
        constexpr void _disable_interrupt_source() {
            constexpr auto irqn = static_cast<IRQn_Type>(Handler::irqn);

            NVIC_DisableIRQ(irqn);
            NVIC_ClearPendingIRQ(irqn);
        }

        template<typename Pin, uint8_t priority>
        void _enable_interrupt_source_for_pin() {
            // Check if an interrupt has already been set in the pio of the pin
            if (!(pins::port<typename Pin::port>->PIO_IMR)) {
                _enable_interrupt_source<typename Pin::port, priority>();
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

        template<typename>
        struct _callbacks {
            static inline interrupt_callback callbacks[32] = {};
        };

        template<typename Handler>
        constexpr void _handle_isr(uint32_t status_register, uint32_t interrupt_mask) {
            // Reverse the bit order for the count trailing zero's.
            status_register = __RBIT(status_register & interrupt_mask);

            uint8_t trailing_zeros = 0;

            while ((trailing_zeros = __CLZ(status_register)) < 32) {
                auto bit = static_cast<uint8_t>(trailing_zeros);

                if (llib::sam3x8e::_callbacks<Handler>::callbacks[bit] != nullptr) {
                    llib::sam3x8e::_callbacks<Handler>::callbacks[bit]();
                }

                status_register &= ~(1 << (31 - bit));
            }
        }

        template<typename Handler, uint32_t Mask>
        constexpr void _set_callback_func(interrupt_callback func) {
            uint32_t mask = Mask;
            uint8_t trailing_zeros = 0;


            while ((trailing_zeros = __CLZ(__RBIT(mask))) < 32) {
                auto bit = static_cast<uint8_t>(trailing_zeros);

                // Set the function on the positions of the bits in the mask
                llib::sam3x8e::_callbacks<Handler>::callbacks[bit] = func;

                mask &= ~(1 << bit);
            }
        }

        template<typename Handler, uint32_t Mask>
        constexpr void _unset_callback_func() {
            _set_callback_func<Handler, Mask>(nullptr);
        }

        /**
         * Set an interrupt on a pin with interrupt mode, priority and a
         *  function to call when the interrupt happens
         *
         * @param func Function to execute on interrupt call
         * @tparam Pin The pin for the interrupt
         * @tparam Mode For the pin to generate a interrupt
         * @tparam priority Priority for the interrupt. Sets the priority for the
         *     whole PIO doesn't update if the pio has already been set.
         */
        template<typename Pin, interrupt Mode, uint8_t priority = 7>
        void attach_interrupt(interrupt_callback func) {
            _enable_interrupt_source_for_pin<Pin, priority>();
            _set_callback_func<typename Pin::port, uint32_t(1U << Pin::number)>(func);
            _set_interrupt_mode<Pin, Mode>();
        }

        template<typename Pin>
        void detach_interrupt() {
            pins::port<typename Pin::port>->PIO_IDR = pins::mask<Pin>;

            if (!(pins::port<typename Pin::port>->PIO_IMR)) {
                // No more pins attached to interrupt on this PIO, so disable iqrn.
                _disable_interrupt_source<typename Pin::port>();
            }
        }

        template<typename Handler, uint8_t priority = 7>
        void enable_interrupt_source() {
            _enable_interrupt_source<Handler, priority>();
        }

        template<typename Handler, uint32_t mask, uint8_t priority = 7>
        void attach_interrupt(interrupt_callback func) {
            // Add function to iqrn on positions of mask and enable the iqrn interrupt.
            _set_callback_func<Handler, mask>(func);
            _enable_interrupt_source<Handler, priority>();
        }

        template<typename Handler, uint32_t mask>
        void detach_interrupt() {
            // Add function to iqrn on positions of mask and enable the iqrn interrupt.
            _unset_callback_func<Handler, mask>();

            // Check if any of the callbacks is used.

            // Todo: Change to check if the interrupt mask register is set
            for (auto i = 0; i < 32; i++) {
                if (llib::sam3x8e::_callbacks<Handler>::callbacks[i] != nullptr) {
                    return;
                }
            }

            // Disable interrupt if all callbacks are disabled.
            _disable_interrupt_source<Handler>();
        }

        template<typename Pin>
        void enable_irq() {
            NVIC_EnableIRQ(
                static_cast<IRQn_Type>(Pin::irqn)
            );
        }

        template<typename Pin>
        void disable_irq() {
            NVIC_DisableIRQ(
                static_cast<IRQn_Type>(Pin::irqn)
            );
        }

        template<typename Pin>
        void clear_pending_irq() {
            NVIC_ClearPendingIRQ(
                static_cast<IRQn_Type>(Pin::irqn)
            );
        }

        template<uint16_t IrqnId>
        void software_interrupt() {
            // Activate a interrupt within software
            // 0x03 -> activates IRQ3
            NVIC->STIR = (IrqnId & 0x1FFU);
        }
    }
}

extern "C" {
void __PIOA_Handler();

void __PIOB_Handler();

void __PIOC_Handler();

void __PIOD_Handler();
}

#endif //LLIB_SAM3X8E_INTERRUPT_HPP
