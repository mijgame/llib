#ifndef LLIB_IMAGE_HPP
#define LLIB_IMAGE_HPP

#include <cstddef>
#include <cstdint>

#include <graphics/color.hpp>
#include <vector2.hpp>

namespace llib::graphics {
    /**
     * Simple image class that stores pixels
     * as bits.
     *
     * @tparam W
     * @tparam H
     */
    template<size_t W, size_t H>
    struct image {
        uint8_t data[W * H / 8] = {};

        /**
         * Default constructor, everything
         * is zero.
         */
        constexpr image() = default;

        /**
         * Constructor that initializes the data with
         * as many arguments as are in the argument pack.
         *
         * @tparam Bytes
         * @param bytes
         */
        template<typename ...Bytes>
        constexpr image(Bytes... bytes)
            : data{static_cast<uint8_t>(bytes)...} {}

        /**
         * Operator to get the pixel value at
         * the given position.
         *
         * @param pos
         * @return
         */
        constexpr color operator()(const uint_fast32_t x, const uint_fast32_t y) const {
            return (data[y] & (0x01U << x)) == 0
                   ? white
                   : black;
        }

        /**
         * Operator to get the pixel value at
         * the given position.
         *
         * @param pos
         * @return
         */
        constexpr color operator[](const vector2u &pos) const {
            return *this(pos.x, pos.y);
        }
    };

    /**
     * Outputstream overload for an image.
     *
     * @tparam OutputStream
     * @tparam W
     * @tparam H
     * @param str
     * @param im
     * @return
     */
    template<typename OutputStream, size_t W, size_t H>
    OutputStream &operator<<(OutputStream &str, const image<W, H> &im) {
        for (size_t y = 0; y < W; y++) {
            for (size_t x = 0; x < H; x++) {
                str << (im(x, y) == white ? '1' : '0');
            }

            str << llib::endl;
        }

        return str;
    }
}

#endif //LLIB_IMAGE_HPP
