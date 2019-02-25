#ifndef LLIB_SSD1306_HPP
#define LLIB_SSD1306_HPP

#include <cstdint>
#include <cstddef>
#include <cstring>

#include "strategy.hpp"

namespace llib::displays {
    namespace detail {
        struct _ssd1306;

        // Modes
        constexpr uint8_t _data_mode = 0x40;
        constexpr uint8_t _cmd_mode = 0x80;

        // Commands
        constexpr uint8_t _set_contrast = 0x81;
        constexpr uint8_t _display_all_on_resume = 0xA4;
        constexpr uint8_t _display_all_on = 0xA5;
        constexpr uint8_t _normal_display = 0xA6;
        constexpr uint8_t _invert_display = 0xA7;
        constexpr uint8_t _display_off = 0xAE;
        constexpr uint8_t _display_on = 0xAF;
        constexpr uint8_t _set_display_offset = 0xD3;
        constexpr uint8_t _set_compins = 0xDA;
        constexpr uint8_t _set_vcom_detect = 0xDB;
        constexpr uint8_t _set_display_clock_div = 0xD5;
        constexpr uint8_t _set_precharge = 0xD9;
        constexpr uint8_t _set_multiplex = 0xA8;
        constexpr uint8_t _set_lowcolumn = 0x00;
        constexpr uint8_t _set_highcolumn = 0x10;
        constexpr uint8_t _set_startline = 0x40;
        constexpr uint8_t _memory_mode = 0x20;
        constexpr uint8_t _column_addr = 0x21;
        constexpr uint8_t _page_addr = 0x22;
        constexpr uint8_t _com_scan_inc = 0xC0;
        constexpr uint8_t _com_scan_dec = 0xC8;
        constexpr uint8_t _segre_map = 0xA0;
        constexpr uint8_t _charge_pump = 0x8D;
        constexpr uint8_t _external_vcc = 0x01;
        constexpr uint8_t _switch_cap_vcc = 0x02;
        constexpr uint8_t _activate_scroll = 0x2F;
        constexpr uint8_t _deactivate_scroll = 0x2E;
        constexpr uint8_t _set_vertical_scroll_area = 0xA3;
        constexpr uint8_t _right_horizontal_scroll = 0x26;
        constexpr uint8_t _left_horizontal_scroll = 0x27;
        constexpr uint8_t _vertical_and_right_horizontal_scroll = 0x29;
        constexpr uint8_t _vertical_and_left_horizontal_scroll = 0x2A;

        constexpr static uint8_t init_sequence[] = {
            detail::_cmd_mode, detail::_display_off,
            detail::_cmd_mode, detail::_set_display_clock_div, 0x80,
            detail::_cmd_mode, detail::_set_multiplex, 0x3F,
            detail::_cmd_mode, detail::_set_display_offset, 0x00,
            detail::_cmd_mode, detail::_set_startline | 0x00,
            detail::_cmd_mode, detail::_charge_pump, 0x14,
            detail::_cmd_mode, detail::_memory_mode, 0x00,
            detail::_cmd_mode, detail::_segre_map | 0x01,
            detail::_cmd_mode, detail::_com_scan_dec,
            detail::_cmd_mode, detail::_com_scan_inc, 0x12,
            detail::_cmd_mode, detail::_set_contrast, 0xCF,
            detail::_cmd_mode, detail::_set_precharge, 0xF1,
            detail::_cmd_mode, detail::_set_vcom_detect, 0x40,
            detail::_cmd_mode, detail::_display_all_on_resume,
            detail::_cmd_mode, detail::_normal_display,
            detail::_cmd_mode, detail::_display_on
        };

        /**
         * Write a command to the display.
         *
         * @tparam Args
         * @param args
         */
        template<typename I2C, typename ...Args>
        constexpr void _command(Args &&...args) {
            const uint8_t commands[] = {
                static_cast<uint8_t>(args)...
            };

            for (const auto cmd : commands) {
                I2C::write(detail::_cmd_mode);
                I2C::write(cmd);
            }
        }

        /**
         * Initialize the display.
         */
        template<typename I2C>
        constexpr void _init(const uint8_t address) {
            I2C::start_transmission(address);
            I2C::write(init_sequence, sizeof(init_sequence));
            I2C::end_transmission();
        }
    }

    template<>
    class buffered<detail::_ssd1306> {
    protected:
        using buffer_t = uint8_t[128 * 64 / 8];

        // Buffered pixel data
        buffer_t buffer;

        // Address of the display on the bus
        uint8_t address;

        buffered(uint8_t address)
            : address(address) {}

        template<typename I2C>
        void clear() {
            memset(buffer, 0, sizeof(buffer_t));
        }

        template<typename I2C>
        void write(const size_t x, const size_t y, const bool on) {
            const size_t buffer_pos = x + (y / 8) * 128;

            if (on) {
                buffer[buffer_pos] |= (0x01 << (y % 8));
            } else {
                buffer[buffer_pos] &= ~(0x01 << (y % 8));
            }
        }

        template<typename I2C>
        void flush() {
            I2C::start_transmission(address);

            detail::_command<I2C>(detail::_column_addr, 0, 127);
            detail::_command<I2C>(detail::_page_addr, 0, 7);

            I2C::write(detail::_data_mode);
            I2C::write(buffer, sizeof(buffer));

            I2C::end_transmission();
        }
    };

    template<>
    class unbuffered<detail::_ssd1306> {
    protected:
        // Address of the display on the bus
        uint8_t address;

        uint8_t cursor_x, cursor_y;

        unbuffered(uint8_t address)
            : address(address), cursor_x(0), cursor_y(0) {}

        template<typename I2C>
        void clear() {
            I2C::start_transmission(address);

            detail::_command<I2C>(detail::_column_addr, 0, 127);
            detail::_command<I2C>(detail::_page_addr, 0, 7);

            I2C::write(0, static_cast<uint32_t>(128 * 64 / 8));

            I2C::end_transmission();
        }

        template<typename I2C>
        void write(const size_t x, const size_t y, const bool on) {
            if (x != cursor_x || y != cursor_y) {
                detail::_command<I2C>(detail::_column_addr, x, 127);
                detail::_command<I2C>(detail::_page_addr, y, 7);

                cursor_x = static_cast<uint8_t>(x);
                cursor_y = static_cast<uint8_t>(y);
            }

            I2C::start_transmission(address);
            I2C::write(detail::_data_mode);
//            I2C::write()
            I2C::end_transmission();
        }

        template<typename I2C>
        void flush() {
            // ...
        }
    };


    template<typename I2C, template<typename> typename Strategy = buffered>
    class ssd1306 : public Strategy<detail::_ssd1306> {
    protected:
        using base = Strategy<detail::_ssd1306>;

    public:
        /**
         * @param address
         */
        explicit ssd1306(const uint8_t address = 0x3C)
            : base(address) {}

        /**
         * Initialize the display.
         */
        LLIB_FORCE_INLINE void init() {
            detail::_init<I2C>(base::address);
        }

        /**
         * Clear the display buffer.
         */
        LLIB_FORCE_INLINE void clear() {
            base::template clear<I2C>();
        }

        /**
         * Write a value to the given position.
         *
         * @param x
         * @param y
         * @param on
         */
        LLIB_FORCE_INLINE void write(const size_t x, const size_t y, const bool on) {
            base::template write<I2C>(x, y, on);
        }

        /**
         * Flush the buffer to the display.
         */
        LLIB_FORCE_INLINE void flush() {
            base::template flush<I2C>();
        }
    };
}

#endif //LLIB_SSD1306_HPP
