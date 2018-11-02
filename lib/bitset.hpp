#ifndef LLIB_BITSET_HPP
#define LLIB_BITSET_HPP

#include <cstdint>
#include <type_traits>

namespace llib {
    namespace {
        enum variations {
            max_8 = 0,
            max_16 = 1,
            max_32 = 2,
            max_other = 3
        };

        template<int Bits>
        constexpr auto bitset_variation() {
            if constexpr(Bits >= 0 && Bits <= 8) {
                return max_8;
            }

            if constexpr(Bits >= 9 && Bits <= 16) {
                return max_16;
            }

            if constexpr(Bits >= 17 && Bits <= 32) {
                return max_32;
            }

            return max_other;
        }
    }

    template<int Bits, int>
    class _bitset {
    protected:
        uint32_t bits[Bits / 32 + 1] = {};


    public:
        constexpr bool operator[](const int index) const {
            return bits[index / 32] >> index != 0;
        }
    };

    template<int Bits>
    class _bitset<Bits, max_8> {
    protected:
        uint8_t bits;
    };

    template<int Bits>
    class _bitset<Bits, max_16> {
        uint16_t bits;
    };

    template<int Bits>
    class _bitset<Bits, max_32> {
        uint32_t bits;
    };

    template<int Bits>
    using bitset = _bitset<Bits, bitset_variation<Bits>()>;
}

#endif //LLIB_BITSET_HPP
