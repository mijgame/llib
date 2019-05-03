#ifndef LLIB_DISPLAY_HPP
#define LLIB_DISPLAY_HPP

#include <vector2.hpp>
#include <graphics/image.hpp>
#include <graphics/color.hpp>

namespace llib::displays {
    template<typename Impl>
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
        void write(const size_t x, const size_t y, const graphics::color color) {
            Impl::write(x, y, color);
        }

        /**
         * Write a value to the given position.
         *
         * @param x
         * @param y
         * @param color
         */
        void write(const vector2u &pos, const graphics::color color) {
            write(pos.x, pos.y, color);
        }

        /**
         * Write an image to the screen at the given
         * position.
         *
         * @tparam W
         * @tparam H
         * @param x
         * @param y
         * @param image
         */
        template<size_t W, size_t H>
        void write(const size_t x, const size_t y, const graphics::image<W, H> &image) {
            for (uint_fast8_t im_x = 0; im_x < W; im_x++) {
                for (uint_fast8_t im_y = 0; im_y < H; im_y++) {
                    write(
                        x + im_x,
                        y + im_y,
                        image(im_x, im_y)
                    );
                }
            }
        }

        /**
         * Write an image to the screen at the given
         * position.
         *
         * @tparam W
         * @tparam H
         * @param x
         * @param y
         * @param image
         */
        template<size_t W, size_t H>
        void write(const vector2u &pos, const graphics::image<W, H> &image) {
            write(pos.x, pos.y, image);
        }

        /**
         * Flush the buffer to the display,
         * if any.
         */
        void flush();
    };
}

#endif //LLIB_DISPLAY_HPP
