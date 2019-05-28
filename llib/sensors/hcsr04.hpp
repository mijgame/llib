#ifndef LLIB_HCSR04_HPP
#define LLIB_HCSR04_HPP

#include <wait.hpp>
#include <peripheral.hpp>

namespace llib::sensors {
    template<PinOut TriggerPin, PinIn EchoPin>
    class hcsr04 {
    public:
        static uint32_t read() {
            // Clear
            TriggerPin::template set<false>();
            llib::wait_for(llib::us{2});

            // Trigger the sensor
            TriggerPin::template set<true>();
            llib::wait_for(llib::us{10});
            TriggerPin::template set<false>();

            const llib::us us{10};
            uint32_t duration = 0;

            // Wait to go high..
            while (!EchoPin::get());

            while (EchoPin::get()) {
                wait_for(us);
                duration += 1;
            }

            uint32_t distance = (duration / 2) / 29; // Should be 29.1 ...

            return distance;
        }
    };
}

#endif //LLIB_HCSR04_HPP
