#ifndef LLIB_SERVO_HPP
#define LLIB_SERVO_HPP

#include <stdint.h>
#include <pwm.hpp>

namespace llib {
    template<typename Pin, uint16_t MinPulse = 500, uint16_t MaxPulse = 2500, uint16_t Hz = 100>
    class servo {
    protected:
        constexpr static LLIB_FORCE_INLINE uint8_t _to_dutycyle(const uint32_t Pos) {
            // old method but division is slower
            // (Pos * (MaxPulse - MinPulse) / 180 + MinPulse) / (((1'000'000 / Hz) / 255));

            // returns an duty cycle corresponding to the position and frequency
            return static_cast<uint8_t>(
                ((17 * Hz) * (Pos * (MaxPulse - MinPulse) + 180 * MinPulse)) / 12000000
            );
        }

    public:
        using pin = Pin;

        template<uint8_t Pos = 127>
        static void init() {
            llib::target::pin_pwm<pin>::template init<Hz, _to_dutycyle(Pos)>();
        }

        template<uint8_t Pos>
        constexpr static void set() {
            llib::target::pin_pwm<pin>::template set<_to_dutycyle(Pos)>();
        }

        constexpr static void set(uint8_t Pos) {
            llib::target::pin_pwm<pin>::set(_to_dutycyle(Pos));
        }
    };
}

#endif //LLIB_QUEUE_HPP
