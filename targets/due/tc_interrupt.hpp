#ifndef LLIB_DUE_TC_INTERRUPT_HPP
#define LLIB_DUE_TC_INTERRUPT_HPP

#include <tc.hpp>
#include <peripheral.hpp>
#include <interrupt.hpp>

namespace llib::due {
    namespace tc {
        template<typename TC, typename T = typename TC::timer>
        class controller {
        private:
            constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
            static inline uint32_t freq = 0;

        public:
            template<uint32_t Frequency = 1000>
            static void init(void (*isr)()) {
                // create pointer to channel
                TcChannel *T_ch = &(port<T>->TC_CHANNEL[TC::channel]);

                // remove write protect from TC
                port<T>->TC_WPMR = TC_WPMR_WPKEY_PASSWD;

                attach_interrupt<TC, ~0x0U>(isr);

                // check if channel is already active
                if ((T_ch->TC_SR & TC_SR_CLKSTA) != 0) {
                    return;
                }

                // Enable clock on tc channel
                enable_clock<TC>();

                // Disable tc clock
                T_ch->TC_CCR = TC_CCR_CLKDIS;

                // Disable interrupts on channel
                T_ch->TC_IDR = ~0x0U;

                // Clear status registers
                T_ch->TC_SR;

                // Set channel mode
                T_ch->TC_CMR = TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1;

                // Enable rc compare interrupt
                enable_interrupt();

                // Clear output register
                set_frequency<Frequency>();

                // Enable channel clock
                T_ch->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
            }

            template<uint32_t Frequency>
            static void set_frequency() {
                set_frequency(Frequency);
            }

            static void set_frequency(const uint32_t frequency) {
                port<T>->TC_CHANNEL[TC::channel].TC_RC = (variant_mck / 2) / frequency;

                // set frequency for set function
                freq = (variant_mck / 2) / frequency;
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
void __TC0_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_0>(
        TC0->TC_CHANNEL[0].TC_SR,
        TC0->TC_CHANNEL[0].TC_IMR
    );
}

void __TC1_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_1>(
        TC0->TC_CHANNEL[1].TC_SR,
        TC0->TC_CHANNEL[1].TC_IMR
    );
}

void __TC2_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_2>(
        TC0->TC_CHANNEL[2].TC_SR,
        TC0->TC_CHANNEL[2].TC_IMR
    );
}

void __TC3_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_3>(
        TC1->TC_CHANNEL[0].TC_SR,
        TC1->TC_CHANNEL[0].TC_IMR
    );
}

void __TC4_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_4>(
        TC1->TC_CHANNEL[1].TC_SR,
        TC1->TC_CHANNEL[1].TC_IMR
    );
}

void __TC5_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_5>(
        TC1->TC_CHANNEL[2].TC_SR,
        TC1->TC_CHANNEL[2].TC_IMR
    );
}

void __TC6_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_6>(
        TC2->TC_CHANNEL[0].TC_SR,
        TC2->TC_CHANNEL[0].TC_IMR
    );
}

void __TC7_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_7>(
        TC2->TC_CHANNEL[1].TC_SR,
        TC2->TC_CHANNEL[1].TC_IMR
    );
}

void __TC8_Handler() {
    llib::due::_handle_isr<llib::due::tc::channel_8>(
        TC2->TC_CHANNEL[2].TC_SR,
        TC2->TC_CHANNEL[2].TC_IMR
    );
}

}

#endif
        
        
