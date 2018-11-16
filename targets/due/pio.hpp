#ifndef LLIB_PIO_HPP
#define LLIB_PIO_HPP

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
}

#endif //LLIB_PIO_HPP
