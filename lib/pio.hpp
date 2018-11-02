#ifndef LLIB_PIO_HPP
#define LLIB_PIO_HPP

#include "base.hpp"

namespace llib {
    struct pioa {
        constexpr static uint32_t instance_id = ID_PIOA;
    };

    struct piob {
        constexpr static uint32_t instance_id = ID_PIOB;
    };

    struct pioc {
        constexpr static uint32_t instance_id = ID_PIOC;
    };

    struct piod {
        constexpr static uint32_t instance_id = ID_PIOD;
    };
}

#endif //LLIB_PIO_HPP
