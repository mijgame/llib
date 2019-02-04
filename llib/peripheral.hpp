#ifndef LLIB_PERIPHERAL_HPP
#define LLIB_PERIPHERAL_HPP

#include "base.hpp"
#include <pins.hpp>

namespace llib {

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

//    template<typename Pin>
//    class pin_in_out {
//    public:
//        using pin = Pin;
//
//        constexpr static bool get() {
//            pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
//            return pin_in<Pin>::get();
//        }
//
//        constexpr static void pullup_enable() {
//            pin_in<Pin>::pullup_enable();
//        }
//
//        constexpr static void pullup_disable() {
//            pin_in<Pin>::pullup_disable();
//        }
//
//        template<bool val>
//        constexpr static void set() {
//            pins::port<Pin>->PIO_OER = pins::mask<Pin>;
//            pin_out<Pin>::template set<val>();
//        }
//
//        constexpr static void set(const bool val) {
//            pins::port<Pin>->PIO_OER = pins::mask<Pin>;
//            pin_out<Pin>::set(val);
//        }
//    };

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