#ifndef LLIB_BITSET_HPP
#define LLIB_BITSET_HPP

#include <limits>
#include <cstddef>

#include "stream.hpp"

namespace llib {
    namespace detail {
        /**
         * The different variants that are
         * possible for an implementation.
         *
         * @internal
         */
        enum _variations {
            max_8,
            max_16,
            max_32,
            max_other,
        };

        /**
         * Base type for bitset internal type
         * selection.
         *
         * @internal
         * @tparam Variation
         */
        template<int Variation>
        struct _bitset_type;

        /**
         * Bitset internal type for bitsets <= 8 bits.
         *
         * @internal
         */
        template<>
        struct _bitset_type<max_8> {
            using type = uint8_t;
            constexpr static uint8_t bits = 8;
            constexpr static int variation = max_8;
        };

        /**
         * Bitset internal type for bitsets <= 16 bits.
         *
         * @internal
         */
        template<>
        struct _bitset_type<max_16> {
            using type = uint16_t;
            constexpr static uint8_t bits = 16;
            constexpr static int variation = max_16;
        };

        /**
         * Bitset internal type for bitsets <= 8 bits.
         *
         * @internal
         */
        template<>
        struct _bitset_type<max_32> {
            using type = uint32_t;
            constexpr static uint8_t bits = 32;
            constexpr static int variation = max_32;
        };

        /**
         * Cleaner bitset type selection.
         */
        template<int Variation>
        using _bitset_type_t = typename _bitset_type<Variation>::type;

        /**
         * Helper function that decides the implementation
         * of bitset to use.
         *
         * @internal
         * @tparam Bits
         * @return
         */
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

        /**
         * Base class for _bitset implementation
         * selection. Both boolean values are specialized.
         *
         * @internal
         * @tparam Bits
         * @tparam Large
         */
        template<int Bits, bool Large>
        class _bitset;

        /**
         * Basic implementation that uses a single
         * variable for all bits.
         *
         * @tparam Bits
         * @tparam InternalType
         */
        template<int Bits>
        class _bitset<Bits, false> {
        protected:
            using InternalType = typename detail::_bitset_type_t<
                detail::_bitset_variation<Bits>()
            >;

            InternalType bits = {};

        public:
            /**
             * Get the value of the bit at the given index.
             * Indices above the bitset size produce undefined behaviour.
             *
             * @param index
             * @return
             */
            constexpr bool operator[](const int index) const {
                return test(index);
            }

            /**
             * Count the number of set bits.
             *
             * @return
             */
            constexpr int count() const {
                int result = 0;

                for (int i = 0; i < Bits; i++) {
                    result += test(i);
                }

                return result;
            }

            /**
             * Get the amount of bits in the bitset.
             *
             * @return
             */
            constexpr int size() const {
                return Bits;
            }

            /**
             * Test whether the bit at the given position
             * is set.
             *
             * @param index
             * @return
             */
            constexpr bool test(const int index) const {
                return (bits & (1 << index)) != 0;
            }

            /**
             * Check if any bits are set.
             *
             * @return
             */
            constexpr bool any() const {
                return bits > 0;
            }

            /**
             * Check if no bits are set.
             *
             * @return
             */
            constexpr bool none() const {
                return bits == 0;
            }

            /**
             * Check if all bits are set.
             *
             * @return
             */
            constexpr bool all() const {
                return bits == std::numeric_limits<InternalType>::max();
            }

            /**
             * Set all bits to 1.
             *
             * @return
             */
            constexpr void set() {
                bits = std::numeric_limits<InternalType>::max();
            }

            /**
             * Set a specific bit to the given value.
             *
             * @param index
             * @param value
             * @return
             */
            constexpr void set(const int index, const bool value = true) {
                bits ^= (-value ^ bits) & (1UL << index);
            }

            /**
             * Clear all bits.
             *
             * @return
             */
            constexpr void reset() {
                bits = 0;
            }

            /**
             * Clear a bit at the given index.
             *
             * @param index
             * @return
             */
            constexpr void reset(const int index) {
                bits &= ~(1UL << index);
            }

            /**
             * Flip all bits in the bitset.
             *
             * @return
             */
            constexpr void flip() {
                bits = ~bits;
            }

            /**
             * Flip the bit at the given index.
             *
             * @param index
             * @return
             */
            constexpr void flip(const int index) {
                bits ^= 1UL << index;
            }
        };

        /**
         * Implementation for bitsets larger that the maximum integer
         * size, uses an array internally and is slightly slower.
         *
         * @tparam Bits
         */
        template<int Bits>
        class _bitset<Bits, true> {
        protected:
            using bitset_type = _bitset_type<max_32>;

            constexpr static int ArraySize = Bits / bitset_type::bits + 1;

            bitset_type::type bits[ArraySize] = {};

        public:
            /**
             * Get the value of the bit at the given index.
             * Indices above the bitset size produce undefined behaviour.
             *
             * @param index
             * @return
             */
            constexpr bool operator[](const int index) const {
                return test(index);
            }

            /**
             * Count the number of set bits.
             *
             * @return
             */
            constexpr int count() const {
                int result = 0;

                for (int i = 0; i < Bits; i++) {
                    result += test(i);
                }

                return result;
            }

            /**
             * Get the amount of bits in the bitset.
             *
             * @return
             */
            constexpr int size() const {
                return Bits;
            }

            /**
             * Test whether the bit at the given position
             * is set.
             *
             * @param index
             * @return
             */
            constexpr bool test(const int index) const {
                return (bits[index / bitset_type::bits] & (1 << (index % bitset_type::bits))) != 0;
            }

            /**
             * Check if any bits are set.
             *
             * @return
             */
            constexpr bool any() const {
                for (int i = 0; i < ArraySize; i++) {
                    if (bits[i] > 0) {
                        return true;
                    }
                }

                return false;
            }

            /**
             * Check if no bits are set.
             *
             * @return
             */
            constexpr bool none() const {
                for (int i = 0; i < ArraySize; i++) {
                    if (bits[i] != 0) {
                        return false;
                    }
                }

                return true;
            }

            /**
             * Check if all bits are set.
             *
             * @return
             */
            constexpr bool all() const {
                for (int i = 0; i < ArraySize; i++) {
                    if (bits[i] != std::numeric_limits<bitset_type::type>::max()) {
                        return false;
                    }
                }

                return true;
            }

            /**
             * Set all bits to 1.
             *
             * @return
             */
            constexpr void set() {
                for (int i = 0; i < ArraySize; i++) {
                    bits[i] = std::numeric_limits<bitset_type::type>::max();
                }
            }

            /**
             * Set a specific bit to the given value.
             *
             * @param index
             * @param value
             * @return
             */
            constexpr void set(const int index, const bool value = true) {
                const int array_index = index / bitset_type::bits;

                bits[array_index] ^= (-value ^ bits[array_index]) & (1UL << (index % bitset_type::bits));
            }

            /**
             * Clear all bits.
             *
             * @return
             */
            constexpr void reset() {
                for (int i = 0; i < ArraySize; i++) {
                    bits[i] = 0;
                }
            }

            /**
             * Clear a bit at the given index.
             *
             * @param index
             * @return
             */
            constexpr void reset(const int index) {
                bits[index / bitset_type::bits] &= ~(1UL << (index % bitset_type::bits));
            }

            /**
             * Flip all bits in the bitset.
             *
             * @return
             */
            constexpr void flip() {
                for (int i = 0; i < ArraySize; i++) {
                    bits[i] = ~bits[i];
                }
            }

            /**
             * Flip the bit at the given index.
             *
             * @param index
             * @return
             */
            constexpr void flip(const int index) {
                bits[index / bitset_type::bits] ^= 1UL << (index % bitset_type::bits);
            }
        };
    }

    template<int Bits>
    using bitset = detail::_bitset<Bits, (Bits > 32)>;

    /**
     * Output the given bitset to the stream.
     *
     * @tparam OutputStream
     * @tparam Bits
     * @param str
     * @param bitset
     * @return
     */
    template<typename OutputStream, int Bits>
    OutputStream operator<<(OutputStream str, bitset<Bits> &bitset) {
        for (int i = 0; i < Bits; i++) {
            str << bitset.test(i);
        }

        return str;
    }

    /**
     * Output the given constant bitset to the stream.
     *
     * @tparam OutputStream
     * @tparam Bits
     * @param str
     * @param bitset
     * @return
     */
    template<typename OutputStream, int Bits>
    OutputStream operator<<(OutputStream str, const bitset <Bits> &bitset) {
        for (int i = 0; i < Bits; i++) {
            str << bitset.test(i);
        }

        return str;
    }
}

#endif //LLIB_BITSET_HPP
