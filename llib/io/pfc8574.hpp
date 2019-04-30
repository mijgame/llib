#ifndef LLIB_PFC8574_HPP
#define LLIB_PFC8574_HPP

#include <stdint-gcc.h>

namespace llib::io {
    template<typename I2C>
    class pfc8574 {
    protected:
        uint8_t address;
        uint8_t mask;

    public:
        explicit pfc8574(uint8_t mask, uint8_t address = 0x41)
            : mask(mask), address(address) {
            I2C::start_transmission(address);
            I2C::write(mask);
            I2C::end_transmission();
        }

        void write(uint8_t value) {
            I2C::start_transmission(address);
            I2C::write(value);
            I2C::end_transmission();
        }

        uint8_t read() {
            I2C::start_transmission(address);
            uint8_t value = I2C::read();
            I2C::end_transmission();

            return value;
        }
    };
}

#endif //LLIB_PFC8574_HPP
