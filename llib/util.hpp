#ifndef LLIB_UTIL_HPP
#define LLIB_UTIL_HPP

#include <base.hpp>

namespace llib::util {
    /**
     * Execute a lambda function for each set bit
     * in the mask. This function currently relies on
     * intrinsics to efficiently deduce which bits are set.
     *
     * TODO: create a fallback implementation for other targets?
     *
     * @tparam F
     * @param mask
     * @param f
     * @return
     */
    template<typename F>
    constexpr void for_bit_in_mask(uint32_t mask, F f) {
        uint8_t trailing_zeros = 0;

        while ((trailing_zeros = __CLZ(__RBIT(mask))) < 32) {
            const auto bit = static_cast<uint8_t>(trailing_zeros);

            f(bit);

            mask &= (~(1U << bit));
        }
    }

    /**
     * Templated mask for for_bit_in_mask support.
     *
     * @see for_bit_in_mask
     *
     * @tparam F
     * @param mask
     * @param f
     * @return
     */
    template<uint32_t Mask, typename F>
    constexpr void for_bit_in_mask(F f) {
        for_bit_in_mask(Mask, f);
    }
}

#endif //LLIB_UTIL_HPP
