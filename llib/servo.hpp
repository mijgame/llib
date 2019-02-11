#ifndef LLIB_SERVO_HPP
#define LLIB_SERVO_HPP

#include <stdint.h>
#include <pwm.hpp>

namespace llib {
    namespace detail {
        template<uint16_t Pos, uint16_t Hz, uint16_t MinPulse, uint16_t MaxPulse>
        constexpr uint16_t _dutycycle = (((17 * Hz) * (Pos * (MaxPulse - MinPulse) + 180 * MinPulse)) / 12000000);
    }

    template<typename Pin, uint16_t Min_pulse = 500, uint16_t Max_pulse = 2500, uint16_t Hz = 100>
    class servo {
        private:        
            static uint8_t _to_dutycyle(uint32_t Pos){
                // old method but division is slower
                // (Pos * (Max_pulse - Min_pulse) / 180 + Min_pulse) / (((1'000'000 / Hz) / 255));

                // returns an duty cycle corresponding to the position and frequency
                return ((17 * Hz) * (Pos * (Max_pulse - Min_pulse) + 180 * Min_pulse)) / 12000000;
            }

        public:
            using pin = Pin;

            template<uint8_t Pos = 127>
            static void init(){
                llib::target::pin_pwm<pin>::template init<Hz, detail::_dutycycle<Pos, Hz, Min_pulse, Max_pulse>>();
            }

            template<uint8_t Pos>
            constexpr static void set() {
                llib::target::pin_pwm<pin>::template set<detail::_dutycycle<Pos, Hz, Min_pulse, Max_pulse>>();
            }            
            
            constexpr static void set(uint8_t Pos) {
                llib::target::pin_pwm<pin>::set(_to_dutycyle(Pos));
            }        
    };
}

#endif //LLIB_QUEUE_HPP
