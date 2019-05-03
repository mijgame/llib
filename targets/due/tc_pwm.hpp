#ifndef LLIB_DUE_TCPWM_HPP
#define LLIB_DUE_TCPWM_HPP

#include <cstdint>
#include <tc.hpp>
#include <peripheral.hpp>
#include <type_traits>

namespace llib::due {
    template<typename Pin>
    class pin_tc {
    protected:
        constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
        static inline uint32_t freq = 0;

        static TcChannel &get_timer_channel() {
            return tc::port<typename Pin::timer_channel::timer>->TC_CHANNEL[Pin::timer_channel::channel];
        }

    public:
        template<uint32_t Frequency = 10000>
        static void init() {
            static_assert(Frequency <= CHIP_FREQ_CPU_MAX / 2, "The timer frequency cannot exceed MCK/2.");

            // Create pointer to channel
            auto &timer_channel = get_timer_channel();

            // Remove write protection from TC
            tc::port<typename Pin::timer_channel::timer>->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

            // TODO: implement TCLK of tc
            if constexpr (std::is_same_v<typename Pin::timer_pin, tc::tclk>) {
                return;
            }

            if (!(timer_channel.TC_SR & TC_SR_CLKSTA)) {
                // Enable peripheral clock
                enable_clock<typename Pin::timer_channel>();

                // Disable tc clock
                timer_channel.TC_CCR = TC_CCR_CLKDIS;

                // Disable interrupts on channel
                timer_channel.TC_IDR = ~0x0U;

                // Clear status registers
                timer_channel.TC_SR;
                timer_channel.TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVE
                                       | TC_CMR_WAVSEL_UP_RC | TC_CMR_EEVT_XC0 | TC_CMR_ACPA_CLEAR
                                       | TC_CMR_ACPC_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR;

                // Set frequency
                set_frequency<Frequency>();
            }

            // clear output
            set<0x0>();

            // setup peripheral
            set_peripheral<Pin>();

            // enable channel clock
            timer_channel.TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
        }

        template<uint32_t Frequency>
        static void set_frequency() {
            static_assert(Frequency <= CHIP_FREQ_CPU_MAX / 2, "The timer frequency cannot exceed MCK/2.");

            set_frequency(Frequency);
        }

        static void set_frequency(const uint32_t frequency) {
            get_timer_channel().TC_RC = (variant_mck / 2) / frequency;

            // Set frequency for set function
            freq = (variant_mck / 2) / frequency;
        }

        template<uint8_t Value>
        static void set() {
            if constexpr(std::is_same_v<typename Pin::timer_pin, tc::tclk>) {
                // Can't set a tclk pin since it is only an input
                return;
            }

            // Create pointer to channel
            auto &timer_channel = get_timer_channel();

            if constexpr(std::is_same_v<typename Pin::timer_pin, tc::tioa>) {
                if constexpr (Value) {
                    timer_channel.TC_RA = (Value * freq) / 0xFF;
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_SET;
                } else {
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_CLEAR;
                }
            } else if (std::is_same_v<typename Pin::timer_pin, tc::tiob>) {
                if constexpr (Value) {
                    timer_channel.TC_RB = (Value * freq) / 0xFF;
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_SET;
                } else {
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_CLEAR;
                }
            }
        }

        static void set(const uint8_t value) {
            if constexpr(std::is_same_v<Pin::timer_pin, tc::tclk>) {
                // Can't set a tclk pin since it is only an input
                return;
            }

            // create pointer to channel
            auto &timer_channel = get_timer_channel();

            if constexpr(std::is_same_v<typename Pin::timer_pin, tc::tioa>) {
                if (value) {
                    timer_channel.TC_RA = (value * freq) / 0xFF;
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_SET;
                } else {
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_ACPA_Msk | TC_CMR_ACPC_Msk))
                        | TC_CMR_ACPA_CLEAR
                        | TC_CMR_ACPC_CLEAR;
                }
            } else if (std::is_same_v<typename Pin::timer_pin, tc::tiob>) {
                if (value) {
                    timer_channel.TC_RB = (value * freq) / 0xFF;
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_SET;
                } else {
                    timer_channel.TC_CMR =
                        (timer_channel.TC_CMR & ~(TC_CMR_BCPB_Msk | TC_CMR_BCPC_Msk))
                        | TC_CMR_BCPB_CLEAR
                        | TC_CMR_BCPC_CLEAR;
                }
            }
        }
    };
}

#endif
