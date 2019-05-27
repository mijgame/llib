#ifndef LLIB_DUE_TC_INTERRUPT_HPP
#define LLIB_DUE_TC_INTERRUPT_HPP

#include <tc.hpp>
#include <peripheral.hpp>
#include <interrupt.hpp>

namespace llib::due{
    namespace tc {
        namespace detail {
            template<typename T>
            struct _isr_store {
                static inline void (*isr)() = nullptr;
            };
        }      

        struct centihertz {
            uint32_t value;

            constexpr static centihertz from_s(uint32_t s) {
                return centihertz{s * 100};
            }
        };

        struct hertz {
            uint32_t value; 

            constexpr hertz(uint32_t hz) : value(hz) {}

            constexpr hertz(centihertz chz) : value (chz.value / 100) {}

            constexpr hertz() : value(0) {}

            constexpr static hertz from_us(uint32_t us) {
                return hertz{1'000'000 / us};
            }

            operator centihertz() const {
                return centihertz{value * 100};
            }
        };



        template<typename TC, typename T = typename TC::timer>
        class controller {
            private:
                constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;

                constexpr static void _set_freq(uint32_t frequency) {
                    port<T>->TC_CHANNEL[TC::channel].TC_RC = frequency;
                }

            public:
                static void init(void (*isr)()) {
                    // create pointer to channel
                    TcChannel * T_ch = &(port<T>->TC_CHANNEL[TC::channel]);

                    // remove write protect from TC
                    port<T>->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

                    detail::_isr_store<TC>::isr = isr;
                    enable_interrupt_source<TC, 7>();

                    // check if channel is already active
                    if(!(T_ch->TC_SR & TC_SR_CLKSTA)){
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
                }

                static void set_frequency(hertz frequency) {
                    _set_freq((variant_mck / 2) / frequency.value);
                }

                static void set_frequency(centihertz frequency) {
                    _set_freq((variant_mck / 2 / 100) * frequency.value);
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
        
        
