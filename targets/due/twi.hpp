#ifndef LLIB_DUE_TWI_HPP
#define LLIB_DUE_TWI_HPP

#include "pins.hpp"
#include "peripheral.hpp"
#include "wait.hpp"
#include "error.hpp"

namespace llib::due {
    namespace twi{
        struct twi0{
            // twi numbers are switched on the arduino due
            constexpr static uint32_t instance_id = ID_TWI1;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TWI1_IRQn);
            
            using sda = pins::sda1;
            using scl = pins::scl1;
        };

        struct twi1{
            // twi numbers are switched on the arduino due
            constexpr static uint32_t instance_id = ID_TWI0;
            constexpr static uint32_t irqn = static_cast<uint32_t>(TWI0_IRQn);

            using sda = pins::sda;
            using scl = pins::scl;            
        };

        enum class mode{
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
        enum class twi_message{
            TXCOMP  = 0x1,
            RXRDY   = 0x2,
            TXRDY   = 0x4,
            SVREAD  = 0x8,
            SVACC   = 0x10,
            GACC    = 0x20,
            OVRE    = 0x40,
            TIMEOUT = 0x80, // this one is not in the status register
            NACK    = 0x100,
            ARBLST  = 0x200,
            SCLWS   = 0x400,
            EOSACC  = 0x800,
            ENDRX   = 0x1000,
            ENDTX   = 0x2000,
            RXBUFF  = 0x4000,
            TXBUFE  = 0x8000
        };

        template<typename TWI, mode Twm, uint32_t Clock>
        class bus{
            private:
                constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
                constexpr static uint32_t xmit_timeout = 100'000;

                template<uint32_t ClK>
                void set_clock(){
                    // dwTwCk is twi_clock
                    // dwMCk is variant_mck
                    uint32_t dwCkDiv = 0;
                    uint32_t dwClDiv = 0;
                    uint32_t dwOk = 0;

                    while (!dwOk) {
                        dwClDiv = ((variant_mck / (2 * ClK)) - 4) / (1 << dwCkDiv);
                        if (dwClDiv <= 255) {
                            dwOk = 1;
                        } else {
                            dwCkDiv += 1;
                        }
                    }

                    port<TWI>->TWI_CWGR = 0;
                    port<TWI>->TWI_CWGR = (dwCkDiv << 16) | (dwClDiv << 8) | dwClDiv;                    
                }

                template<twi_message flag>
                twi_message wait_for_status() const {
                    uint32_t status = 0;
                    uint32_t timeout = xmit_timeout;

                    while ((status & uint32_t(flag)) != uint32_t(flag)) {
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


            public:
                template<uint8_t addr = 0x10>
                void init(){
                    // enable clock
                    enable_clock<TWI>();

                    // change the multiplexer
                    set_peripheral<TWI::sda>();
                    set_peripheral<TWI::scl>();

                    // enable the pullups of the pins
                    pin_in<typename TWI::sda>::pullup_enable();
                    pin_in<typename TWI::scl>::pullup_enable();

                    // Disable PDC channel
                    port<TWI>->TWI_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

                    if constexpr(Twm == mode::MASTER){
                        // TWI Slave Mode Enabled
                        port<TWI>->TWI_CR = TWI_CR_SVEN;
                    }

                    // TWI disable
                    port<TWI>->TWI_CR = TWI_CR_SWRST;
                    port<TWI>->TWI_RHR;

                    // wait for at least 10ms
                    wait_for(15_ms);

                    // TWI Slave mode disabled, Twi master mode disabled
                    port<TWI>->TWI_CR = TWI_CR_SVDIS | TWI_CR_MSDIS;

                    if constexpr(Twm == mode::MASTER){
                        // enable master mode
                        port<TWI>->TWI_CR = TWI_CR_MSEN;
                    }
                    else{
                        // configure slave address
                        port<TWI>->TWI_SMR = 0;
                        port<TWI>->TWI_SMR = TWI_SMR_SADR(addr);

                        // TWI Slave Mode Enabled
                        port<TWI>->TWI_CR = TWI_CR_SVEN;

                        // wait for at least 10ms
                        wait_for(15_ms);              

                        if((port<TWI>->TWI_CR & TWI_CR_SVDIS)!= TWI_CR_SVDIS){
                            // retry since twi is not in slave mode
                            LLIB_ERROR("Failed setting twi in slave mode. Trying again");
                            init<addr>();
                        }
                    }

                    set_clock<Clock>();
                }

                template<uint8_t address>
                twi_message write(uint8_t * data, size_t size){
                    // Start write
                    port<TWI>->TWI_MMR = 0;
                    port<TWI>->TWI_MMR = uint32_t(address & 0x7F) << 16;;
                    port<TWI>->TWI_IADR = 0;

                    // write a start
                    port<TWI>->TWI_CR = TWI_CR_START;

                    for (size_t i = 0; i < size; i++) {
                        // write data in twi register
                        port<TWI>->TWI_THR = data[i];

                        auto res = wait_for_status<twi_message::TXRDY>();
                        if (res != twi_message::TXRDY) {
                            // Error
                            return res;
                        }
                    }

                    // Stop write
                    port<TWI>->TWI_CR = TWI_CR_STOP;

                    return wait_for_status(TWI_SR_TXCOMP);                                     
                }

                // template<uint8_t address, uint8_t data>
                // twi_message read_extended(uint8_t * data, size_t size){
                //     // Start write
                //     port<TWI>->TWI_MMR = 0;
                //     port<TWI>->TWI_MMR = uint32_t(address & 0x7F) << 16;;
                //     port<TWI>->TWI_IADR = 0;

                //     // write a start
                //     port<TWI>->TWI_CR = TWI_CR_START;

                //     for (size_t i = 0; i < size; i++) {
                //         // write data in twi register
                //         port<TWI>->TWI_THR = data[i];

                //         auto res = wait_for_status<twi_message::TXRDY>();
                //         if (res != twi_message::TXRDY) {
                //             // Error
                //             return res;
                //         }
                //     }

                //     // Stop write
                //     port<TWI>->TWI_CR = TWI_CR_STOP;

                //     return wait_for_status(TWI_SR_TXCOMP);                                     
                // }                

                uint16_t read(){                 
                    return 0;
                }
        };
    }
}

#endif