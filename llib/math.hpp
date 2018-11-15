#ifndef LLIB_MATH_HPP
#define LLIB_MATH_HPP

#include <cstdint>

#include "base.hpp"
#include "defines.hpp"

namespace llib {
    int LLIB_FORCE_INLINE log2(uint32_t n) {
        return 31 - __CLZ(n);
    }
}

#endif //LLIB_MATH_HPP
