#ifndef LLIB_PERIPHERAL_HPP
#define LLIB_PERIPHERAL_HPP

#include "base.hpp"
#include <pins.hpp>

namespace llib {
    template<typename T>
    concept bool HasInitFunction = requires () {
        { T::init() } -> void;
    };

    template<typename T>
    concept bool HasGetFunction = requires () {
        { T::get() } -> bool;
    };

    template<typename T>
    concept bool HasSetFunction = requires (bool val) {
        { T::set(val) } -> void;
    };

    template<typename T>
    concept bool PinIn = HasInitFunction<T> && HasGetFunction<T>;

    template<typename T>
    concept bool PinOut = HasInitFunction<T> && HasSetFunction<T>;


    template<typename Pin>
    class pin_in {
    public:
        using pin = Pin;

        constexpr static void init() {
            target::pin_in<Pin>::init();
        }

        constexpr static bool get() {
            return target::pin_in<Pin>::get();
        }

        constexpr static void pullup_enable() {
            target::pin_in<Pin>::pullup_enable();
        }

        constexpr static void pullup_disable() {
            target::pin_in<Pin>::pullup_disable();
        }
    };

    template<typename Pin>
    class pin_out {
    public:
        using pin = Pin;

        constexpr static void init() {
            target::pin_out<Pin>::init();
        }

        template<bool val>
        constexpr static void set() {
            target::pin_out<Pin>::template set<val>();
        }

        constexpr static void set(const bool val) {
            target::pin_out<Pin>::set(val);
        }
    };

    template<typename Pin>
    class pin_in_out {
    public:
        using pin = Pin;

        // Exists for duck typing
        constexpr static void init() {

        }

        constexpr static bool get() {
            return target::pin_in_out<Pin>::get();
        }

        constexpr static void pullup_enable() {
            target::pin_in_out<Pin>::pullup_enable();
        }

        constexpr static void pullup_disable() {
            target::pin_in_out<Pin>::pullup_disable();
        }

        template<bool Val>
        constexpr static void set() {
            target::pin_in_out<Pin>::template set<Val>();
        }

        constexpr static void set(const bool val) {
            target::pin_in_out<Pin>::set(val);
        }
    };

    template<typename Pin>
    class pin_oc {
    public:
        using pin = Pin;

        constexpr static bool get() {
            return target::pin_oc<Pin>::get();
        }

        template<bool val>
        constexpr static void set() {
            target::pin_oc<Pin>::template set<val>();
        }

        constexpr static void set(const bool val) {
            target::pin_oc<Pin>::set(val);
        }
    };

    template<typename PinIn>
    class pin_in_invert : public pin_in<typename PinIn::pin> {
    public:
        constexpr static bool get() {
            return !pin_in<typename PinIn::pin>::get();
        }
    };
}

#endif //LLIB_PERIPHERAL_HPP