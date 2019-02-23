#ifndef LLIB_PORTS_HPP
#define LLIB_PORTS_HPP

#include <bitset.hpp>
#include <tuple>

namespace llib {
    /**
     * Port that combines multiple llib::pin_in pins
     * into a single type.
     *
     * @tparam Pins
     */
    template<typename ... Pins>
    class port_in {
    protected:
        using pins = std::tuple<Pins...>;

        template<size_t Index>
        using pin = std::tuple_element_t<Index, pins>;

    public:
        constexpr static size_t pin_count = sizeof...(Pins);

        constexpr static void init() {
            (Pins::init(), ...);
        }

        template<size_t Index>
        constexpr static void init() {
            pin<Index>::init();
        }

        constexpr static bitset<sizeof...(Pins)> get() {
            bitset<sizeof...(Pins)> result;

            size_t i = 0;
            (result.set(i++, Pins::get()), ...);

            return result;
        }

        template<size_t Index>
        constexpr static bool get() {
            return pin<Index>::get();
        }

        constexpr static void pullup_enable() {
            (Pins::pullup_enable(), ...);
        }

        template<size_t Index>
        constexpr static void pullup_enable() {
            pin<Index>::pullup_enable();
        }

        constexpr static void pullup_disable() {
            (Pins::pullup_disable(), ...);
        }

        template<size_t Index>
        constexpr static void pullup_disable() {
            pin<Index>::pullup_disable();
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
    protected:
        using pins = std::tuple<Pins...>;

        template<size_t Index>
        using pin = std::tuple_element_t<Index, pins>;

    public:
        constexpr static size_t pin_count = sizeof...(Pins);

        constexpr static void init() {
            (Pins::init(), ...);
        }

        template<size_t Index>
        constexpr static void init() {
            pin<Index>::init();
        }

        template <bool Val>
        constexpr static void set() {
            (Pins::template set<Val>(), ...);
        }

        template<size_t Index, bool Val>
        constexpr static void set() {
            pin<Index>::template set<Val>();
        }

        constexpr static void set(const bool val) {
            (Pins::set(val), ...);
        }

        template<size_t Index>
        constexpr static void set(const bool val) {
            pin<Index>::set(val);
        }

        constexpr static void set(const bitset<sizeof...(Pins)> &bits) {
            size_t i = sizeof...(Pins) - 1;
            (Pins::set(bits[i--]), ...);
        }
    };
}

#endif //LLIB_PORTS_HPP
