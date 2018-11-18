#ifndef LLIB_BITSET_HPP
#define LLIB_BITSET_HPP

#include <cstdint>
#include <type_traits>
#include <limits>
#include <iterator>
#include <cstddef>

#include "stream.hpp"

namespace llib {
    namespace {
        enum _variations {
            max_8,
            max_16,
            max_32,
            max_other,
        };

        template<int Bits>
        constexpr auto _bitset_variation() {
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

        template<int Variation>
        struct _bitset_type {
            using type = uint32_t;
            constexpr static int variation = Variation;
        };

        template<>
        struct _bitset_type<max_8> {
            using type = uint8_t;
            constexpr static int variation = max_8;
        };

        template<>
        struct _bitset_type<max_16> {
            using type = uint16_t;
            constexpr static int variation = max_16;
        };

        template<int Bits, typename InternalType>
        class _bitset {
        protected:
            InternalType bits = {};

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
                return (bits >> index & 0x1) != 0;
            }

            constexpr bool any() const {
                return bits > 0;
            }

            constexpr bool none() const {
                return bits == 0;
            }

            constexpr bool all() const {
                return bits == std::numeric_limits<InternalType>::max();
            }

            constexpr void set() {
                bits = std::numeric_limits<InternalType>::max();
            }

            constexpr void set(const int index, const bool value = true) {
                bits ^= (-value ^ bits) & (1UL << index);
            }

            constexpr void reset() {
                bits = 0;
            }

            constexpr void reset(const int index) {
                bits &= ~(1UL << index);
            }

            constexpr void flip() {
                bits = ~bits;
            }

            constexpr void flip(const int index) {
                bits ^= 1UL << index;
            }
        };

        template<int Bits>
        class _bitset<Bits, _bitset_type<max_other>> {
        protected:
            constexpr static int ArraySize = Bits / 32 + 1;

            _bitset_type<max_other>::type bits[ArraySize] = {};

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
                for (int i = 0; i < ArraySize; i++) {
                    if (bits[i] > 0) {
                        return true;
                    }
                }

                return false;
            }

            constexpr bool none() const {
                for (int i = 0; i < ArraySize; i++) {
                    if (bits[i] != 0) {
                        return false;
                    }
                }

                return true;
            }

            constexpr bool all() const {
                for (int i = 0; i < ArraySize; i++) {
                    if (bits[i] != std::numeric_limits<_bitset_type<max_other>::type>::max()) {
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
    }

    template<int Bits>
    using bitset = _bitset<
            Bits,
            typename _bitset_type<_bitset_variation<Bits>()>::type
    >;

    template<typename OutputStream, int Bits>
    OutputStream operator<<(OutputStream str, bitset<Bits> &bitset) {
        for (int i = 0; i < Bits; i++) {
            str << bitset.test(i);
        }

        return str;
    }

    template<typename OutputStream, int Bits>
    OutputStream operator<<(OutputStream str, const bitset <Bits> &bitset) {
        for (int i = 0; i < Bits; i++) {
            str << bitset.test(i);
        }

        return str;
    }
}

#endif //LLIB_BITSET_HPP
