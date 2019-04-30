#ifndef LLIB_PCF8591_HPP
#define LLIB_PCF8591_HPP

#include <cstdint>

namespace llib::analog {
    enum class pcf8591_pin : uint8_t {
        A0 = 0,
        A1 = 1,
        A2 = 2,
        A3 = 3
    };

    /**
     * FOUR_SINGLE_ENDED will configure all inputs to be single
     * inputs.
     *
     * THREE_DIFFERENTIAL will configure all inputs to be differential
     * to AIN3.
     *
     * MIXED will configure AIN0 and AIN1 as single ended inputs and
     * AIN2 and AIN3 to be differential.
     *
     * TWO_DIFFERENTIAL will configure AIN0 and AIN1 as differential and
     * AIND2 and AIN3 to be differential.
     */
    enum class pcf8591_pin_mode : uint8_t {
        FOUR_SINGLE_ENDED = 0,
        THREE_DIFFERENTIAL = 1,
        MIXED = 2,
        TWO_DIFFERENTIAL = 2
    };

    /**
     * YL-40 is mentioned on the board itself.
     * TODO: support differential inputs (datasheet page 6 fig.4)
     * https://www.nxp.com/docs/en/data-sheet/PCF8591.pdf
     *
     * @tparam I2C
     */
    template<typename I2C>
    class pcf8591 {
    protected:
        uint8_t address;
        pcf8591_pin_mode pin_mode;

        constexpr uint8_t _get_control_byte(const uint8_t pin, bool auto_increment, const uint8_t pin_mode, bool output_enable) {
            return (auto_increment << 7U)
                   | ((pin_mode & 0x3U) << 5U)
                   | (auto_increment << 3U)
                   | (pin & 0x3U);
        }

    public:
        explicit pcf8591(
            uint8_t address = 0x48,
            pcf8591_pin_mode pin_mode = pcf8591_pin_mode::FOUR_SINGLE_ENDED
        ) : address(address), pin_mode(pin_mode) {}

        uint32_t read(const pcf8591_pin pin) {
            uint8_t value;
            const uint8_t control_byte = _get_control_byte(
                static_cast<uint8_t>(pin),
                false,
                static_cast<uint8_t>(pin_mode),
                false
            );

            I2C::start_transmission(address);

            // Second byte to the device is the control byte
            I2C::write(control_byte);

            // Third byte is stored in the DAC data register
//            I2C::write(0);

            I2C::end_transmission();

            // A I2C read triggers the read cycle, so we need to
            // read twice in succession in order to get the result.
//            I2C::read(address);
            I2C::read(address, &value, 1);

            return static_cast<uint32_t>(value);
        }
    };
}

#endif //LLIB_PCF8591_HPP
