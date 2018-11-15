#ifndef LLIB_RTT_HPP
#define LLIB_RTT_HPP

#include "peripheral.hpp"

namespace llib {
    class rtt {
    public:
        constexpr static uint32_t instance_id = ID_RTT;

        template<uint16_t Prescaler = 0x00008000, bool AlarmInterrupt = true, bool IncrementInterrupt = true>
        void static init() {
            RTT->RTT_MR = static_cast<uint32_t>(0)
                          | (IncrementInterrupt << 17)
                          | (AlarmInterrupt << 16)
                          | Prescaler;
        }

        template<uint16_t Prescaler = 0x00008000, bool AlarmInterrupt = true, bool IncrementInterrupt = true>
        static void reset() {
            RTT->RTT_MR = static_cast<uint32_t>(0)
                          | (1 << 18) // Real-time Timer Restart (RTTRST)
                          | (IncrementInterrupt << 17)
                          | (AlarmInterrupt << 16)
                          | Prescaler;
        }

        static void set_alarm(uint32_t value) {
            RTT->RTT_AR = value;
        }

        static bool alarm_occurred() {
            return (RTT->RTT_SR & 0x1) != 0;
        }

        static bool timer_advanced() {
            if (((RTT->RTT_SR >> 1) & 0x1) == 0) {
                return false;
            }

            /*
             * We need to disable interrupts, wait for the SR
             * to clear to 0 and enable interrupts again so
             * the ISR is not called twice.
             */

            // Disable interrupt
            RTT->RTT_MR &= ~(1 << 17);

            while (RTT->RTT_SR != 0);

            // Enable interrupt again
            RTT->RTT_MR |= 1 << 17;

            return true;
        }

        static uint32_t get() {
            // Per the datasheet; read the same value twice for best accuracy
            (void) RTT->RTT_VR;
            return RTT->RTT_VR;
        }
    };
}

#endif //LLIB_RTT_HPP
