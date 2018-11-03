#ifndef LLIB_RTT_HPP
#define LLIB_RTT_HPP

#include "peripheral.hpp"

namespace llib {
    class rtt {
    public:
        constexpr static uint32_t instance_id = ID_RTT;

        template<uint16_t Prescaler = 0, bool AlarmInterrupt = true, bool IncrementInterrupt = true>
        void static init() {
            RTT->RTT_MR = static_cast<uint32_t>(0)
                          | (IncrementInterrupt << 17)
                          | (AlarmInterrupt << 16)
                          | Prescaler;
        }

        template<uint16_t Prescaler = 0, bool AlarmInterrupt = true, bool IncrementInterrupt = true>
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
            return ((RTT->RTT_SR >> 1) & 0x1) != 0;
        }

        static uint32_t get() {
            // Per the datasheet; read the same value twice for best accuracy
            uint32_t first = RTT->RTT_VR;
            uint32_t second = RTT->RTT_VR;

            while (first != second) {
                first = second;
                second = RTT->RTT_VR;
            }

            return first;
        }
    };
}

#endif //LLIB_RTT_HPP
