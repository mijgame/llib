#ifndef LLIB_DUE_GPBR_HPP
#define LLIB_DUE_GPBR_HPP

#include "base.hpp"

namespace llib::due {
    /**
     * General Purpose backup registers
     * 
     * This needs a backup battery to keep the content. When the
     * due is reset the content will be cleared as well.
     * 
     * There is 256 bit (8x 32bit) of data available
     * 
     */
    class gpbr {
        public:
            constexpr static uint32_t size = 8;

            static inline uint32_t *const backup_reg = ((uint32_t *) 0x400E1A90U);
    };
}

#endif