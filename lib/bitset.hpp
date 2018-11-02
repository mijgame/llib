#ifndef LLIB_BITSET_HPP
#define LLIB_BITSET_HPP

#include <cstdint>
#include <type_traits>
#include <limits>

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
        constexpr static int ArraySize = Bits / 32 + 1;

        uint32_t bits[ArraySize] = {};


    public:
        constexpr bool operator[](const int index) const {
            return test(index);
        }

        constexpr int count() const {
            int result = 0;

            for (int i = 0; i < Bits; i++) {
                result += test(i);
            }

            return result;
        }

        constexpr int size() const {
            return Bits;
        }

        constexpr bool test(const int index) const {
            return (bits[index / 32] >> (index % 32)) != 0;
        }

        constexpr bool any() const {
            for (int i = 0; i < Bits; i++) {
                if (test(i)) {
                    return true;
                }
            }

            return false;
        }

        constexpr bool none() const {
            for (int i = 0; i < Bits; i++) {
                if (test(i)) {
                    return false;
                }
            }

            return true;
        }

        constexpr bool all() const {
            for (int i = 0; i < Bits; i++) {
                if (!test(i)) {
                    return false;
                }
            }

            return true;
        }

        constexpr void set() {
            for (int i = 0; i < ArraySize; i++) {
                bits[i] = std::numeric_limits<uint32_t>::max();
            }
        }

        constexpr void set(const int index, const bool value = true) {
            bits[index / 32] ^= (-value ^ bits[index / 32]) & (1UL << (index % 32));
        }

        constexpr void reset() {
            for (int i = 0; i < ArraySize; i++) {
                bits[i] = 0;
            }
        }

        constexpr void reset(const int index) {
            bits[index / 32] &= ~(1UL << (index % 32));
        }

        constexpr void flip() {
            for (int i = 0; i < ArraySize; i++) {
                bits[i] = ~bits[i];
            }
        }

        constexpr void flip(const int index) {
            bits[index / 32] ^= 1UL << (index % 32);
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
