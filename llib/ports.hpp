#ifndef LLIB_PORTS_HPP
#define LLIB_PORTS_HPP

#include <bitset.hpp>

namespace llib {
    /**
     * Port that combines multiple llib::pin_in pins
     * into a single type.
     *
     * @tparam Pins
     */
    template<typename ... Pins>
    class port_in {
    public:
        constexpr static void init() {
            (Pins::init(), ...);
        }

        constexpr static bitset<sizeof...(Pins)> get() {
            bitset<sizeof...(Pins)> result;

            size_t i = 0;
            (result.set(i++, Pins::get()), ...);

            return result;
        }

        constexpr static void pullup_enable() {
            (Pins::pullup_enable(), ...);
        }

        constexpr static void pullup_disable() {
            (Pins::pullup_disable(), ...);
        }
    };

    /**
     * Port that combines multiple llib::pin_out pins
     * into a single type.
     *
     * @tparam Pins
     */
    template<typename ... Pins>
    class port_out {
    public:
        constexpr static void init() {
            (Pins::init(), ...);
        }

        template <bool Val>
        constexpr static void set() {
            (Pins::template set<Val>(), ...);
        }

        constexpr static void set(const bool val) {
            (Pins::set(val), ...);
        }

        constexpr static void set(const bitset<sizeof...(Pins)> &bits) {
            size_t i = sizeof...(Pins) - 1;
            (Pins::set(bits[i--]), ...);
        }
    };
}

#endif //LLIB_PORTS_HPP
