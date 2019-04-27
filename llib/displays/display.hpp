#ifndef LLIB_DISPLAY_HPP
#define LLIB_DISPLAY_HPP

#include <graphics/color.hpp>

namespace llib::displays {
    class display {
    public:
        /**
         * Initialize the display.
         */
        void init();

        /**
         * Clear the display or display buffer.
         */
        void clear();

        /**
         * Write a value to the given position.
         *
         * @param x
         * @param y
         * @param color
         */
        void write(const size_t x, const size_t y, const graphics::color color);

        /**
         * Flush the buffer to the display,
         * if any.
         */
        void flush();
    };
}

#endif //LLIB_DISPLAY_HPP
