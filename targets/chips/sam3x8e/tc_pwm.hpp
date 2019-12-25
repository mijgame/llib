#ifndef LLIB_SAM3X8E_TCPWM_HPP
#define LLIB_SAM3X8E_TCPWM_HPP

#include <cstdint>
#include <tc.hpp>
#include <peripheral.hpp>
#include <type_traits>

namespace llib::sam3x8e {
    template<typename Pin>
    class pin_tc {
    protected:
        using channel = typename tc::detail::channel<Pin::tc::id>::c;

        constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
        static inline uint32_t freq = 0;

        constexpr static TcChannel* timer_channel() {
            return &tc::port<typename channel::timer>->TC_CHANNEL[channel::channel];
        }

    public:
        template<uint32_t Frequency = 10000>
        static void init() {
            static_assert(Frequency <= CHIP_FREQ_CPU_MAX / 2, "The timer frequency cannot exceed MCK/2.");

            // TODO: implement TCLK of tc
            static_assert(Pin::tc::type != detail::tc::mode::TCLK, "Cannot have TCLK pin atm");

            if constexpr (Pin::tc::type == detail::tc::mode::TCLK) {
                return;
            }

            // Remove write protection from TC
            tc::port<typename channel::timer>->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

            auto* tc = timer_channel();
            
            if (!(tc->TC_SR & TC_SR_CLKSTA)) {
                // Enable peripheral clock
                enable_clock<channel>();

                // Disable tc clock
                tc->TC_CCR = TC_CCR_CLKDIS;

                // Disable interrupts on channel
                tc->TC_IDR = ~0x0U;

                // Clear status registers
                tc->TC_SR;
                tc->TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVE
                        | TC_CMR_WAVSEL_UP_RC | TC_CMR_EEVT_XC0 | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR;

                // Set frequency
                set_frequency<Frequency>();
            }
            
            // clear output
            set<0x0>();

            // setup peripheral
            set_peripheral<Pin, typename Pin::tc::periph>();

            // enable channel clock
            tc->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
        }

        template<uint32_t Frequency>
        static void set_frequency() {
            static_assert(Frequency <= CHIP_FREQ_CPU_MAX / 2, "The timer frequency cannot exceed MCK/2.");

            set_frequency(Frequency);
        }

        static void set_frequency(const uint32_t frequency) {
            timer_channel()->TC_RC = (variant_mck / 2) / frequency;

            // Set frequency for set function
            freq = (variant_mck / 2) / frequency;
        }

        template<uint8_t Value>
        static void set() {     
            if constexpr (Pin::tc::type == detail::tc::mode::TCLK) {
                // Can't set a tclk pin since it is only an input
                return;
            }

            // get the channel of the pin
            auto* tc = timer_channel();

            if constexpr(Pin::tc::type == detail::tc::mode::TIOA) {
                if constexpr (Value) {
                    tc->TC_RA = (Value * freq) / 0xFF;
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_SET;
                } else {
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_CLEAR;
                }
            } else if (Pin::tc::type == detail::tc::mode::TIOB) {
                if constexpr (Value) {
                    tc->TC_RB = (Value * freq) / 0xFF;
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_SET;
                } else {
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_CLEAR;
                }
            }
        }

        static void set(const uint8_t value) {
            if constexpr (Pin::tc::type == detail::tc::mode::TCLK) {
                // Can't set a tclk pin since it is only an input
                return;
            }

            // get the channel of the pin
            auto* tc = timer_channel();

            if constexpr(Pin::tc::type == detail::tc::mode::TIOA) {
                if (value) {
                    tc->TC_RA = (value * freq) / 0xFF;
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_SET;
                } else {
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_CLEAR;
                }
            } else if (Pin::tc::type == detail::tc::mode::TIOB) {
                if (value) {
                    tc->TC_RB = (value * freq) / 0xFF;
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_SET;
                } else {
                    tc->TC_CMR =
                        (tc->TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_CLEAR;
                }
            }
        }
    };
}

#endif
