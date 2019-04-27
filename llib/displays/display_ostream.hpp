#ifndef LLIB_DISPLAY_OSTREAM_HPP
#define LLIB_DISPLAY_OSTREAM_HPP

#include <stream_base.hpp>
#include <graphics/font.hpp>
#include <graphics/color.hpp>

namespace llib::displays {
    template<typename Display, typename Ostream = llib::ostream<>>
    class display_ostream : public Ostream {
    protected:
        constexpr static int8_t char_width = 9;
        constexpr static int8_t line_height = 10;
        constexpr static int8_t chars_on_term = 13;
        constexpr static int8_t tab_width = 2;
        constexpr static int8_t line_width = char_width * chars_on_term;

        // TODO: make this adjustable at runtime
        constexpr static llib::graphics::color foreground = llib::graphics::white;
        constexpr static llib::graphics::color background = llib::graphics::black;

        Display &display;

        llib::graphics::font font;

        size_t x = 1;
        size_t y = 1;

        void newline() {
            x = 1;
            y += line_height;
        }

    public:
        explicit display_ostream(Display &display)
            : display(display) {}

        void putc(char c) {
            if (c == '\n') {
                newline();
                return;
            }

            if (c == '\t') {
                x += tab_width * char_width;
                return;
            }

            if (x + char_width > line_width + 1) {
                newline();
            }

            const auto &image = font[c];

            for (uint_fast8_t im_x = 0; im_x < 8; im_x++) {
                for (uint_fast8_t im_y = 0; im_y < 8; im_y++) {
                    display.write(
                        x + im_x,
                        y + im_y,
                        image(x, y)
                    );
                }
            }

            x += char_width;
        }

        void flush() {
            x = 1;
            y = 1;

            display.flush();
        }
    };
}

#endif //LLIB_DISPLAY_OSTREAM_HPP
