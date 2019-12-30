#ifndef LLIB_LPC2138_PINS_HPP
#define LLIB_LPC2138_PINS_HPP

#include <type_traits>

#include "pio.hpp"

namespace llib::lpc2138::detail {

}

namespace llib::lpc2138::pins {
    struct p0 {
        using port = pio1;
        constexpr static uint32_t number = 16;
    };                    

    template<typename Pin>
    constexpr uint32_t mask = 1U << Pin::number;

    template<typename Pin>
    const Pio *port = nullptr;

    template<>
    Pio *const port<pio0> = PIO0;

    template<>
    Pio *const port<pio1> = PIO1;
}

namespace llib::lpc2138 {
    template<typename Pin>
    class pin_in {
    public:
        using pin = Pin;

        constexpr static void init() {
            pins::port<typename Pin::port>->IODIR &= ~pins::mask<Pin>;
        }

        constexpr static bool get() {
            return (pins::port<typename Pin::port>->IOPIN & pins::mask<Pin>);
        }
    };

    template<typename Pin>
    class pin_out {
    public:
        using pin = Pin;

        constexpr static void init() {
            pins::port<typename Pin::port>->IODIR |= pins::mask<Pin>;
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<typename Pin::port>->IOSET = pins::mask<Pin>;
            } else {
                pins::port<typename Pin::port>->IOCLR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            (val
             ? pins::port<typename Pin::port>->IOSET
             : pins::port<typename Pin::port>->IOCLR
            ) = pins::mask<Pin>;
        }
    };   
}

#endif