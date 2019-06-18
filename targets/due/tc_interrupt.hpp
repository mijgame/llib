#ifndef LLIB_DUE_TC_INTERRUPT_HPP
#define LLIB_DUE_TC_INTERRUPT_HPP

#include <tc.hpp>
#include <peripheral.hpp>
#include <interrupt.hpp>

namespace llib::due::tc {
    template<typename TC>
    class controller {
    private:
        constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
        static inline uint32_t freq = 0;

    public:
        template<uint32_t Frequency = 1000>
        static void init(void (*isr)()) {
            static_assert(Frequency <= CHIP_FREQ_CPU_MAX / 2, "The timer frequency cannot exceed MCK/2.");

            // Create pointer to channel
            TcChannel *timer_channel = &(port<typename TC::timer>->TC_CHANNEL[TC::channel]);

            // Remove write protect from TC
            port<typename TC::timer>->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

            attach_interrupt<TC, ~0x0U>(isr);

            // Check if channel is already active
            if ((timer_channel->TC_SR & TC_SR_CLKSTA) != 0) {
                return;
            }

            // Enable clock on tc channel
            enable_clock<TC>();

            // Disable tc clock
            timer_channel->TC_CCR = TC_CCR_CLKDIS;

            // Disable interrupts on channel
            timer_channel->TC_IDR = ~0x0U;

            // Clear status registers
            timer_channel->TC_SR;

            // Set channel mode
            timer_channel->TC_CMR = TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1;

            // Enable rc compare interrupt
            enable_interrupt();

            // Clear output register
            set_frequency<Frequency>();
        }

        static void start() {
            clear_pending_irq<TC>();
            enable_irq<TC>();

            // Timer start signal
            port<typename TC::timer>->TC_CHANNEL[TC::channel].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
        }

        static void stop() {
            disable_irq<TC>();

            // Timer stop signal
            port<typename TC::timer>->TC_CHANNEL[TC::channel].TC_CCR = TC_CCR_CLKDIS;
        }

        template<uint32_t Frequency>
        static void set_frequency() {
            static_assert(Frequency <= CHIP_FREQ_CPU_MAX / 2, "The timer frequency cannot exceed MCK/2.");

            set_frequency(Frequency);
        }

        static void set_frequency(const uint32_t frequency) {
            port<typename TC::timer>->TC_CHANNEL[TC::channel].TC_RC = (variant_mck / 2) / frequency;

            // set frequency for set function
            freq = (variant_mck / 2) / frequency;
        }

        static void enable_interrupt() {
            port<typename TC::timer>->TC_CHANNEL[TC::channel].TC_IER = TC_IER_CPCS;
        }

        static void disable_interrupt() {
            port<typename TC::timer>->TC_CHANNEL[TC::channel].TC_IDR = TC_IDR_CPCS;
        }
    };
}

#endif
        
        
