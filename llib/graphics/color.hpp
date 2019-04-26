#ifndef LLIB_COLOR_HPP
#define LLIB_COLOR_HPP

#include <stdint-gcc.h>

namespace llib::graphics {
    struct color {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        /**
         * Default constructor, black.
         */
        constexpr color() : r(0), g(0), b(0) {}

        /**
         * Initialize the color with the given values.
         *
         * @param r
         * @param g
         * @param b
         */
        constexpr color(uint8_t r, uint8_t g, uint8_t b)
            : r(r), g(g), b(b) {}

        /**
         * Construct the color from the given 32 bit value.
         *
         * @param value
         */
        constexpr explicit color(uint32_t value)
            : r((value & 0xFF0000U) >> 16U),
              g((value & 0x00FF00U) >> 8U),
              b(value & 0x0000FFU) {}

        /**
         * Return the negative of the color.
         *
         * @return
         */
        constexpr color operator-() const {
            return color(
                0xFF - r,
                0xFF - g,
                0xFF - b
            );
        }

        /**
         * Check if two colors are equal.
         *
         * @param other
         * @return
         */
        constexpr bool operator==(const color other) const {
            return r == other.r
                   && b == other.b
                   && g == other.g;
        }

        /**
         * Check if to colors are not equal.
         *
         * @param other
         * @return
         */
        constexpr bool operator!=(const color other) const {
            return !operator==(other);
        }

        /**
         * Get the RGB representation as a single
         * 32-bit value.
         *
         * @return
         */
        constexpr uint32_t to_rgb() const {
            return (static_cast< uint_fast32_t >(r) << 16U)
                   | (static_cast< uint_fast32_t >(g) << 8U)
                   | static_cast< uint_fast32_t >( b );
        }

        /**
         * Get the 5-6-5 bit color representation of
         * this color. 5 bits red, 6 bits green, 5 bits blue.
         *
         * @return
         */
        constexpr uint16_t to_565() const {
            return (static_cast<uint16_t>(r) * 0x1FU / 0xFFU) << 11U
                   | (static_cast<uint16_t>(g) * 0x3FU / 0xFFU) << 5U
                   | (static_cast<uint16_t>(b) * 0x1FU / 0xFFU);
        }
    };

    constexpr color black = color(0, 0, 0);
    constexpr color white = color(0xFF, 0xFF, 0xFF);
    constexpr color red = color(0xFF, 0, 0);
    constexpr color green = color(0, 0xFF, 0);
    constexpr color blue = color(0, 0, 0xFF);
    constexpr color gray = color(0x80, 0x80, 0x80);
    constexpr color yellow = color(0xFF, 0xFF, 0);
    constexpr color cyan = color(0, 0xFF, 0xFF);
    constexpr color magenta = color(0xFF, 0, 0xFF);
    constexpr color violet = color(0xEE82EE);
    constexpr color sienna = color(0xA0522D);
    constexpr color purple = color(0x800080);
    constexpr color pink = color(0xFFC8CB);
    constexpr color silver = color(0xC0C0C0);
    constexpr color brown = color(0xA52A2A);
    constexpr color salmon = color(0xFA8072);
}

#endif //LLIB_COLOR_HPP
