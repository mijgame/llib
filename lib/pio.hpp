#ifndef LLIB_PIO_HPP
#define LLIB_PIO_HPP

#include <cstdint>

namespace llib {
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
}

#endif //LLIB_PIO_HPP
