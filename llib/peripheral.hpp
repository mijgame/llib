#ifndef LLIB_PERIPHERAL_HPP
#define LLIB_PERIPHERAL_HPP

#include <type_traits>

#include "pins.hpp"
#include "pio.hpp"

namespace llib {

    template<typename Pin>
    class pin_in {
    public:
        using pin = Pin;

        constexpr static void init() {
            pins::port<typename Pin::port>->PIO_ODR = pins::mask<Pin>;
        }

        constexpr static bool get() {
            return (pins::port<typename Pin::port>->PIO_PDSR & pins::mask<Pin>) != 0;
        }

        constexpr static void pullup_enable() {
            pins::port<typename Pin::port>->PIO_PUDR = pins::mask<Pin>;
        }

        constexpr static void pullup_disable() {
            pins::port<typename Pin::port>->PIO_PUER = pins::mask<Pin>;
        }
    };

    template<typename Pin>
    class pin_out {
    public:
        using pin = Pin;

        constexpr static void init() {
            pins::port<typename Pin::port>->PIO_OER = pins::mask<Pin>;
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<typename Pin::port>->PIO_SODR = pins::mask<Pin>;
            } else {
                pins::port<typename Pin::port>->PIO_CODR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            (val
             ? pins::port<typename Pin::port>->PIO_SODR
             : pins::port<typename Pin::port>->PIO_CODR
            ) = pins::mask<Pin>;
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
            return pin_in<Pin>::get();
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            } else {
                pins::port<Pin>->PIO_OER = pins::mask<Pin>;
                pins::port<Pin>->PIO_CODR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            if (val) {
                pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            } else {
                pins::port<Pin>->PIO_OER = pins::mask<Pin>;
                pins::port<Pin>->PIO_CODR = pins::mask<Pin>;
            }
        }
    };

    template<typename PinIn>
    class pin_in_invert : public pin_in<typename PinIn::pin> {
    public:
        constexpr static bool get() {
            return !pin_in<typename PinIn::pin>::get();
        }
    };

    /**
    * Enable the clock on the peripheral.
    *
    * @tparam P
    */
    template<typename P>
    void enable_clock() {
        if constexpr (P::instance_id < 32) {
            // PCER0
            PMC->PMC_PCER0 = 1U << P::instance_id;
        } else {
            // PCER1
            PMC->PMC_PCER1 = 1U << (P::instance_id - 32);
        }
    }

    /**
     * Enable the clock on multiple peripherals.
     *
     * @tparam P
     * @tparam Args
     */
    template<typename P, typename P2, typename ...Args>
    void enable_clock() {
        enable_clock<P>();
        enable_clock<P2, Args...>();
    }
}

#endif //LLIB_PERIPHERAL_HPP