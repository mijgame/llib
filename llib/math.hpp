#ifndef LLIB_MATH_HPP
#define LLIB_MATH_HPP

#include <limits>
#include <type_traits>
#include <cstdint>

#include "base.hpp"
#include "defines.hpp"

namespace llib {
    template<
            typename T,
            typename = std::enable_if_t<std::is_integral_v<T>>
    >
    constexpr T pow(T base, T exp) {
        // https://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
        T result = 1;

        for (;;) {
            if (exp & 1) {
                result *= base;
            }

            exp >>= 1;

            if (!exp) {
                break;
            }

            base *= base;
        }

        return result;
    }

    template<
            typename T,
            typename = std::enable_if_t<std::is_integral_v<T>>
    >
    constexpr T sqrt(T input) {
        // https://stackoverflow.com/questions/1100090/looking-for-an-efficient-integer-square-root-algorithm-for-arm-thumb2
        T op = input;
        T res = 0;
        T one = 1uL << (sizeof(T) * 8 - 2); // Amount of bits - 2


        // "one" starts at the highest power of four <= than the argument.
        while (one > op) {
            one >>= 2;
        }

        while (one != 0) {
            if (op >= res + one) {
                op = op - (res + one);
                res = res + 2 * one;
            }

            res >>= 1;
            one >>= 2;
        }

        return res;
    }

    template<typename T>
    constexpr T min(const T a, const T b) {
        if constexpr(std::is_integral_v<T> && std::is_unsigned_v<T>) {
            return b + ((a - b) & (a - b) >> (sizeof(T) * 8 - 1));
        } else {
            return (a > b) ? b : a;
        }
    }

    template<typename T>
    constexpr T max(const T a, const T b) {
        if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>) {
            return a - ((a - b) & (a - b) >> (sizeof(T) * 8 - 1));
        } else {
            return (a > b) ? a : b;
        }
    }

    template<typename T>
    constexpr LLIB_FORCE_INLINE T abs(const T x) {
        if constexpr (std::is_unsigned_v<T>) {
            return x < 0 ? -x : x;
        } else {
            return x;
        }
    }

    int LLIB_FORCE_INLINE log2(const uint32_t n) {
        return 31 - __CLZ(n);
    }
}

#endif //LLIB_MATH_HPP
