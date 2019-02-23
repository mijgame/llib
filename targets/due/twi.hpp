#ifndef LLIB_DUE_TWI_HPP
#define LLIB_DUE_TWI_HPP

#include "pins.hpp"
#include "peripheral.hpp"
#include "wait.hpp"
#include "error.hpp"

namespace llib::due {
    namespace twi {
        struct twi0 {
            // twi numbers are switched on the arduino due
            constexpr static uint32_t instance_id = ID_TWI1;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TWI1_IRQn);

            using sda = pins::sda1;
            using scl = pins::scl1;
        };

        struct twi1 {
            // twi numbers are switched on the arduino due
            constexpr static uint32_t instance_id = ID_TWI0;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TWI0_IRQn);

            using sda = pins::sda;
            using scl = pins::scl;
        };

        enum class mode {
            MASTER,
            SLAVE
        };

        template<typename TWI>
        Twi *const port = nullptr;

        template<>
        Twi *const port<twi0> = TWI1;

        template<>
        Twi *const port<twi1> = TWI0;

        // all the twi messages in the status register
        enum class twi_message {
            OK = 0x0, // is nothing in the status register
            TXCOMP = 0x1,
            RXRDY = 0x2,
            TXRDY = 0x4,
            SVREAD = 0x8,
            SVACC = 0x10,
            GACC = 0x20,
            OVRE = 0x40,
            TIMEOUT = 0x80, // this one is not in the status register
            NACK = 0x100,
            ARBLST = 0x200,
            SCLWS = 0x400,
            EOSACC = 0x800,
            ENDRX = 0x1000,
            ENDTX = 0x2000,
            RXBUFF = 0x4000,
            TXBUFE = 0x8000
        };

        template<typename TWI, mode Twm>
        class bus {
        private:
            constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
            constexpr static uint32_t xmit_timeout = 100'000;

            template<uint32_t frequency>
            static void _set_clock() {
                uint32_t divider = 0;

                // calculate clock divider and clock low/high divider
                for (uint8_t clk_div = 0; clk_div < 7; clk_div++) {
                    divider = ((variant_mck / (2 * frequency)) - 4) / pow(2, clk_div);

                    if (divider <= 0xFF) {
                        divider = ((clk_div & 0x7) << 16) | ((divider & 0xFF) << 8) | (divider & 0xFF);
                        break;
                    }
                }

                port<TWI>->TWI_CWGR = 0;
                port<TWI>->TWI_CWGR = divider;
            }

            template<twi_message flag>
            static twi_message _wait_for_status() {
                uint32_t status = port<TWI>->TWI_SR;
                uint32_t timeout = xmit_timeout;

                while (!(status & uint32_t(flag))) {
                    status = port<TWI>->TWI_SR;

                    if (status & TWI_SR_NACK) {
                        // not ack received stop
                        return twi_message::NACK;
                    }

                    if (--timeout == 0) {
                        // tried for to long so stop
                        return twi_message::TIMEOUT;
                    }
                }
                return flag;
            }

            template<bool read>
            static void _start(uint8_t addr, uint32_t in_addr = 0, uint8_t in_addr_size = 0) {
                // Setup addresses
                port<TWI>->TWI_MMR = (uint32_t(addr & 0x7F) << 16) | ((in_addr_size & 0x3) << 8);

                if constexpr (read) {
                    // enable read mode
                    port<TWI>->TWI_MMR |= TWI_MMR_MREAD;
                }

                // set the internal address / data after addr and before repeated start
                port<TWI>->TWI_IADR = in_addr & 0xFFFFFF;
            }

            static twi_message _read(uint8_t *data, size_t size) {
                // write a start
                port<TWI>->TWI_CR = TWI_CR_START;

                for (size_t i = 0; i < size; i++) {
                    if (i + 1 >= size) {
                        // write stop on last byte we want to read
                        port<TWI>->TWI_CR = TWI_CR_STOP;
                    }

                    auto res = _wait_for_status<twi_message::RXRDY>();
                    if (res == twi_message::RXRDY) {
                        // read data into array
                        data[i] = (port<TWI>->TWI_RHR & 0xFF);
                    } else {
                        // return error
                        return res;
                    }
                }
                // wait until read is done
                return _wait_for_status<twi_message::TXCOMP>();
            }

        public:
            template<uint32_t frequency = 100000>
            static void init() {
                // enable clock
                enable_clock<TWI>();

                // change the multiplexer
                set_peripheral<typename TWI::sda>();
                set_peripheral<typename TWI::scl>();

                // enable the pullups of the pins
                pin_in<typename TWI::sda>::pullup_enable();
                pin_in<typename TWI::scl>::pullup_enable();

                // Disable PDC channel
                port<TWI>->TWI_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

                if constexpr(Twm == mode::MASTER) {
                    // TWI Slave Mode Enabled
                    port<TWI>->TWI_CR = TWI_CR_SVEN;
                }

                // TWI disable
                port<TWI>->TWI_CR = TWI_CR_SWRST;
                port<TWI>->TWI_RHR;

                // wait for at least 10ms
                wait_for(llib::ms{15});

                // TWI Slave mode disabled, Twi master mode disabled
                port<TWI>->TWI_CR = TWI_CR_SVDIS | TWI_CR_MSDIS;

                if constexpr(Twm == mode::MASTER) {
                    // enable master mode
                    port<TWI>->TWI_CR = TWI_CR_MSEN;

                    _set_clock<frequency>();
                }
            }

            template<uint32_t frequency = 100000>
            static void init(uint8_t addr) {
                // do a normal init
                init<frequency>();

                if constexpr(Twm == mode::SLAVE) {
                    // configure slave address
                    port<TWI>->TWI_SMR = 0;
                    port<TWI>->TWI_SMR = TWI_SMR_SADR(addr);

                    // TWI Slave Mode Enabled
                    port<TWI>->TWI_CR = TWI_CR_SVEN;

                    // wait for at least 10ms
                    wait_for(llib::ms{15});

                    if ((port<TWI>->TWI_CR & TWI_CR_SVDIS) != TWI_CR_SVDIS) {
                        // retry since twi is not in slave mode
                        LLIB_WARNING("Failed setting twi in slave mode. Trying again");
                        init<addr, frequency>();
                    }

                    _set_clock<frequency>();
                }
            }

            /**
             * starts an write transmission
             *
             * @param address
             */
            static void start_transmission(uint8_t address) {
                // start a write
                _start<false>(address);
            }

            /**
             * ends an transmission and checks for faults
             *
             */
            static twi_message end_transmission() {
                // Stop write
                port<TWI>->TWI_CR = TWI_CR_STOP;

                return _wait_for_status<twi_message::TXCOMP>();
            }

            /**
             * Writes an array of bytes to the twi interface
             *
             * @param data
             * @param size
             */
            static twi_message write(const uint8_t *data, size_t size) {
                // write the amount of data to the twi interface and check if nothing wrong happens
                for (size_t i = 0; i < size; i++) {
                    // write data in twi register
                    port<TWI>->TWI_THR = data[i];

                    auto res = _wait_for_status<twi_message::TXRDY>();
                    if (res != twi_message::TXRDY) {
                        // Error
                        return res;
                    }
                }
                return twi_message::OK;
            }

            /**
             * Writes an single byte to the twi interface
             *
             * @param data
             */
            static twi_message write(uint8_t data) {
                return write(&data, 1);
            }

            /**
             * Tries to read a size amount of bytes from the twi interface
             *
             * @param addres
             * @param data
             * @param size
             */
            static twi_message read(uint8_t address, uint8_t *data, size_t size) {
                // start a read
                _start<true>(address);

                // read the data
                return _read(data, size);
            }

            /**
             * Tries to read a size amount of bytes from the twi interface
             * This writes one or two bytes before the read to the twi interface
             *
             * @param addres
             * @param data
             * @param size
             */
            template<typename T, uint8_t In_size = sizeof(T), typename std::enable_if<(sizeof(T) <=
                                                                                       2)>::type * = nullptr>
            static twi_message read(uint8_t address, T in_addr, uint8_t *data, size_t size) {
                // start a read with two or less In_size
                _start<true>(address, uint32_t(in_addr & 0xFFFFFF), In_size);

                // read the data
                return _read(data, size);
            }

            /**
             * Tries to read a size amount of bytes from the twi interface
             * This writes 3 bytes before the read to the twi interface
             *
             * @param addres
             * @param data
             * @param size
             */
            template<typename T, typename std::enable_if<(sizeof(T) > 2)>::type * = nullptr>
            static twi_message read(uint8_t address, T in_addr, uint8_t *data, size_t size) {
                // start a read with more than two In_size
                _start<true>(address, uint32_t(in_addr & 0xFFFFFF), 3);

                // read the data
                return _read(data, size);
            }

        };
    }
}

#endif