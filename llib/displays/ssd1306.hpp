#ifndef LLIB_SSD1306_HPP
#define LLIB_SSD1306_HPP

#include <cstdint>
#include <cstddef>
#include <cstring>

namespace llib::displays {
    template<typename I2C>
    class ssd1306 {
    protected:
        // Modes
        constexpr static uint8_t DATA_MODE = 0x40;
        constexpr static uint8_t CMD_MODE = 0x80;

        // Commands
        constexpr static uint8_t SETCONTRAST = 0x81;
        constexpr static uint8_t DISPLAYALLON_RESUME = 0xA4;
        constexpr static uint8_t DISPLAYALLON = 0xA5;
        constexpr static uint8_t NORMALDISPLAY = 0xA6;
        constexpr static uint8_t INVERTDISPLAY = 0xA7;
        constexpr static uint8_t DISPLAYOFF = 0xAE;
        constexpr static uint8_t DISPLAYON = 0xAF;
        constexpr static uint8_t SETDISPLAYOFFSET = 0xD3;
        constexpr static uint8_t SETCOMPINS = 0xDA;
        constexpr static uint8_t SETVCOMDETECT = 0xDB;
        constexpr static uint8_t SETDISPLAYCLOCKDIV = 0xD5;
        constexpr static uint8_t SETPRECHARGE = 0xD9;
        constexpr static uint8_t SETMULTIPLEX = 0xA8;
        constexpr static uint8_t SETLOWCOLUMN = 0x00;
        constexpr static uint8_t SETHIGHCOLUMN = 0x10;
        constexpr static uint8_t SETSTARTLINE = 0x40;
        constexpr static uint8_t MEMORYMODE = 0x20;
        constexpr static uint8_t COLUMNADDR = 0x21;
        constexpr static uint8_t PAGEADDR = 0x22;
        constexpr static uint8_t COMSCANINC = 0xC0;
        constexpr static uint8_t COMSCANDEC = 0xC8;
        constexpr static uint8_t SEGREMAP = 0xA0;
        constexpr static uint8_t CHARGEPUMP = 0x8D;
        constexpr static uint8_t EXTERNALVCC = 0x01;
        constexpr static uint8_t SWITCHCAPVCC = 0x02;
        constexpr static uint8_t ACTIVATE_SCROLL = 0x2F;
        constexpr static uint8_t DEACTIVATE_SCROLL = 0x2E;
        constexpr static uint8_t SET_VERTICAL_SCROLL_AREA = 0xA3;
        constexpr static uint8_t RIGHT_HORIZONTAL_SCROLL = 0x26;
        constexpr static uint8_t LEFT_HORIZONTAL_SCROLL = 0x27;
        constexpr static uint8_t VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL = 0x29;
        constexpr static uint8_t VERTICAL_AND_LEFT_HORIZONTAL_SCROLL = 0x2A;

        constexpr static uint8_t init_sequence[] = {
            CMD_MODE, DISPLAYOFF,
            CMD_MODE, SETDISPLAYCLOCKDIV, 0x80,
            CMD_MODE, SETMULTIPLEX, 0x3F,
            CMD_MODE, SETDISPLAYOFFSET, 0x00,
            CMD_MODE, SETSTARTLINE | 0x00,
            CMD_MODE, CHARGEPUMP, 0x14,
            CMD_MODE, MEMORYMODE, 0x00,
            CMD_MODE, SEGREMAP | 0x01,
            CMD_MODE, COMSCANDEC,
            CMD_MODE, SETCOMPINS, 0x12,
            CMD_MODE, SETCONTRAST, 0xCF,
            CMD_MODE, SETPRECHARGE, 0xF1,
            CMD_MODE, SETVCOMDETECT, 0x40,
            CMD_MODE, DISPLAYALLON_RESUME,
            CMD_MODE, NORMALDISPLAY,
            CMD_MODE, DISPLAYON
        };

        // Address of the display on the bus
        uint8_t address;

        // Buffered pixel data
        uint8_t buffer[128 * 64 / 8];

        /**
         * Write a command to the display.
         *
         * @tparam Args
         * @param args
         */
        template<typename ...Args>
        void command(Args &&...args) {
            const uint8_t commands[] = {
                static_cast<uint8_t>(args)...
            };

            for (const auto cmd : commands) {
                I2C::write(CMD_MODE);
                I2C::write(cmd);
            }
        }

    public:
        /**
         * @param address
         */
        explicit ssd1306(const uint8_t address = 0x3C)
            : address(address) {}

        /**
         * Initialize the display.
         */
        void init() {
            I2C::start_transmission(address);
            I2C::write(init_sequence, sizeof(init_sequence));
            I2C::end_transmission();
        }

        /**
         * Clear the display buffer.
         */
        void clear() {
            memset(buffer, 0, sizeof(buffer));
        }

        /**
         * Write a value to the given position.
         *
         * @param x
         * @param y
         * @param on
         */
        void write(const size_t x, const size_t y, const bool on) {
            const size_t buffer_pos = x + (y / 8) * 128;

            if (on) {
                buffer[buffer_pos] |= (0x01 << (y % 8));
            } else {
                buffer[buffer_pos] &= ~(0x01 << (y % 8));
            }
        }

        /**
         * Flush the buffer to the display.
         */
        void flush() {
            I2C::start_transmission(address);

            command(COLUMNADDR, 0, 127);
            command(PAGEADDR, 0, 7);

            I2C::write(DATA_MODE);
            I2C::write(buffer, sizeof(buffer));

            I2C::end_transmission();
        }
    };
}

#endif //LLIB_SSD1306_HPP
