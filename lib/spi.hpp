#ifndef LLIB_SPI_HPP
#define LLIB_SPI_HPP

#include "base.hpp"

namespace llib {
    class spi {
        enum class mode {
            MASTER,
            SLAVE
        };

        struct spi0 {
            constexpr static uint32_t instance_id = ID_SPI0;
        };

        struct spi1 {
//            constexpr static uint32_t instance_id = ID_SPI1;
        };

        template<mode M>
        constexpr static void init() {
//            SPI0->SPI_WPMR
        }
    };
}

#endif //LLIB_SPI_HPP
