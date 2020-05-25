#ifndef LLIB_SAM3X8E_TC_INTERRUPT_HPP
#define LLIB_SAM3X8E_TC_INTERRUPT_HPP

#include <tc.hpp>
#include <peripheral.hpp>
#include <interrupt.hpp>
#include <units.hpp>

namespace llib::sam3x8e {
    namespace tc {
        namespace detail {
            template<typename T>
            struct _isr_store {
                static inline void (*isr)() = nullptr;
            };
        }

        template<typename TC>
        class controller {
        private:
            using T = typename TC::timer;
            
            constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;

            constexpr static void _set_freq(uint32_t frequency) {
                // Set the frequency
                port<T>->TC_CHANNEL[TC::channel].TC_RC = frequency;

                // Reset the counter value
                port<T>->TC_CHANNEL[TC::channel].TC_CCR = TC_CCR_SWTRG;
            }

        public:
            static void init(void (*isr)()) {
                // create pointer to channel
                TcChannel *T_ch = &(port<T>->TC_CHANNEL[TC::channel]);

                // remove write protect from TC
                port<T>->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

                detail::_isr_store<TC>::isr = isr;
                enable_interrupt_source<TC, 7>();

                // check if channel is already active
                if ((T_ch->TC_SR & TC_SR_CLKSTA) != 0) {
                    return;
                }

                // enable clock on tc channel
                enable_clock<TC>();

                // disable tc clock
                T_ch->TC_CCR = TC_CCR_CLKDIS;

                // disable interrupts on channel
                T_ch->TC_IDR = ~0x0;

                // clear status registers
                T_ch->TC_SR;

                // set channel mode
                T_ch->TC_CMR = TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1;

                // enable channel clock
                T_ch->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
            }

            static void set_frequency(us _us) {
                _set_freq(42 * _us.value);
            }

            static void set_frequency(ms _ms) {
                _set_freq(42'000 * _ms.value);
            }

            static void set_frequency(s _s) {
                _set_freq((variant_mck / 2) * _s.value);
            }

            static void enable_interrupt() {
                port<T>->TC_CHANNEL[TC::channel].TC_IER = TC_IER_CPCS;
            }

            static void disable_interrupt() {
                port<T>->TC_CHANNEL[TC::channel].TC_IDR = TC_IDR_CPCS;
            }
        };
    }
}

extern "C" {
void __TC0_Handler();

void __TC1_Handler();

void __TC2_Handler();

void __TC3_Handler();

void __TC4_Handler();

void __TC5_Handler();

void __TC6_Handler();

void __TC7_Handler();

void __TC8_Handler();
}

#endif
        