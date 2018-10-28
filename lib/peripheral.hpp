#define register

#include <type_traits>
#include "sam.h"

struct pioa {
    constexpr static uint32_t instance_id = 11;
};

struct piob {
    constexpr static uint32_t instance_id = 12;
};

struct pioc {
    constexpr static uint32_t instance_id = 13;
};

struct piod {
    constexpr static uint32_t instance_id = 14;
};

template<typename Pio>
const Pio *const get_port() {
    if constexpr(std::is_same_v<Pio, pioa>) {
        return PIOA;
    } else if constexpr (std::is_same_v<Pio, piob>) {
        return PIOB;
    } else if constexpr (std::is_same_v<Pio, pioc>) {
        return PIOC;
    } else {
        return PIOD;
    }
}

namespace pins {
    struct d0 {
        using port = pioa;
        constexpr static uint32_t number = 8;
    };

    struct d1 {
        using port = pioa;
        constexpr static uint32_t number = 9;
    };

    struct d2 {
        using port = piob;
        constexpr static uint32_t number = 25;
    };

    struct d3 {
        using port = piob;
        constexpr static uint32_t number = 28;
    };

    struct d4 {
        using port = piob;
        constexpr static uint32_t number = 26;
    };

    template<typename Pin>
    inline constexpr uint32_t mask = 1U << Pin::number;

    template<typename Pin>
    inline const Pio *port = nullptr;

    template<>
    inline Pio *const port<pioa> = PIOA;

    template<>
    inline Pio *const port<piob> = PIOB;

    template<>
    inline Pio *const port<pioc> = PIOC;

    template<>
    inline Pio *const port<piod> = PIOD;
}

template<typename Pin>
class pin_in {
public:
    using pin = Pin;

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

template<typename Pin>
class pin_in_out {
public:
    using pin = Pin;

    constexpr static bool get() {
        return pin_in<Pin>::get();
    }

    constexpr static void pullup_enable() {
        pin_in<Pin>::pullup_enable();
    }

    constexpr static void pullup_disable() {
        pin_in<Pin>::pullup_disable();
    }

    template<bool val>
    constexpr static void set() {
        pin_out<Pin>::template set<val>();
    }

    constexpr static void set(const bool val) {
        pin_out<Pin>::set(val);
    }
};

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
        return ! pin_in<typename PinIn::pin>::get();
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
        PMC->PMC_PCER1 = 1U << P::instance_id;
    }
}




