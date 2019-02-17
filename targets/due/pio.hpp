#ifndef LLIB_DUE_PIO_HPP
#define LLIB_DUE_PIO_HPP

#include "base.hpp"

namespace llib::due {
    struct pioa {
        constexpr static uint32_t instance_id = ID_PIOA;
        constexpr static uint32_t irqn = static_cast<uint32_t>(PIOA_IRQn);
    };

    struct piob {
        constexpr static uint32_t instance_id = ID_PIOB;
        constexpr static uint32_t irqn = static_cast<uint32_t>(PIOB_IRQn);
    };

    struct pioc {
        constexpr static uint32_t instance_id = ID_PIOC;
        constexpr static uint32_t irqn = static_cast<uint32_t>(PIOC_IRQn);
    };

    struct piod {
        constexpr static uint32_t instance_id = ID_PIOD;
        constexpr static uint32_t irqn = static_cast<uint32_t>(PIOD_IRQn);
    };

    struct pio_periph_a {};

    struct pio_periph_b {};

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

    /**
    * Returns the status of the clock on the peripheral.
    *
    * @tparam P
    */
    template<typename P>
    bool clock_status(){
        if constexpr (P::instance_id < 32){
            return (PMC->PMC_PCSR0 & (1U << P::instance_id));
        } else {
            return PMC->PMC_PCSR1 & (1U << (P::instance_id - 32));
        }
    }
}

#endif //LLIB_DUE_PIO_HPP
