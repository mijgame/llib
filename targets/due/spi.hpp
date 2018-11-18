#ifndef LLIB_DUE_SPI_HPP
#define LLIB_DUE_SPI_HPP

#include "base.hpp"
#include "pins.hpp"
#include "peripheral.hpp"
#include "error.hpp"
#include <type_traits>

namespace llib::due {
    namespace spi {
        struct spi0 {
            constexpr static uint32_t instance_id = ID_SPI0;
        };

        enum class mode {
            MASTER,
            SLAVE
        };

        template<typename SPI>
        Spi *const port = nullptr;

        template<>
        Spi *const port<spi0> = SPI0;

        enum class spi_mode : uint8_t {
            MODE_0 = 0x02,
            MODE_1 = 0x00,
            MODE_2 = 0x03,
            MODE_3 = 0x01
        };

        enum class bits : uint8_t {
            BIT_8 = 0,
            BIT_9 = 1,
            BIT_10 = 3,
            BIT_11 = 2,
            BIT_12 = 4,
            BIT_13 = 5,
            BIT_14 = 6,
            BIT_15 = 7,
            BIT_16 = 8
        };

        template<typename SPI, typename Pin = pins::d10_multi>
        class bus {
        private:
            template<typename PPin>
            static void configure_pin() {
                // special cases sinds d10 and d4 have multiple pio's
                if(std::is_same_v<PPin, pins::d10>){
                    return configure_pin<pins::d10_multi>();
                }                
                if(std::is_same_v<PPin, pins::d4>){
                    return configure_pin<pins::d4_multi>();
                }         
                                   
                pins::port<typename PPin::port>->PIO_IDR = pins::mask<PPin>;

                // change pio multiplexer
                if constexpr (std::is_same_v<typename PPin::port, pioa>) {
                    uint32_t t = pins::port<typename PPin::port>->PIO_ABSR;
                    pins::port<typename PPin::port>->PIO_ABSR &= (~pins::mask<PPin> & t);
                } else if constexpr (std::is_same_v<typename PPin::port, piob>) {
                    uint32_t t = pins::port<typename PPin::port>->PIO_ABSR;
                    pins::port<typename PPin::port>->PIO_ABSR = (pins::mask<PPin> | t);
                }          
                else{
                    // do nothing sinds we cant use different pio's
                    LLIB_ERROR("Wrong Pin detected cant use pin's that are not in pioa/piob")
                    for(;;);
                }
                pins::port<typename PPin::port>->PIO_PDR = pins::mask<PPin>;

                /* Disable interrupts on the pin(s) */
                pins::port<typename PPin::port>->PIO_IDR = pins::mask<PPin>;
                // disable pull ups
                pins::port<typename PPin::port>->PIO_PUDR = pins::mask<PPin>;
            }

            template<typename PPin>
            constexpr static uint8_t pin_to_spi() {
                return PPin::spi_number;
            }         

            constexpr static uint32_t SPI_PCS(uint32_t npcs) {
                return ((~(1 << (npcs)) & 0xF) << 16);
            }

        public:
            template<mode M, spi_mode Spm, uint32_t Divider, bits B>
            void static init() {
                // disable write protection spi
                REG_SPI0_WPMR = 0x53504900;

                // enable spi clock
                enable_clock<SPI>();

                // disable spi
                spi::port<SPI>->SPI_CR = SPI_CR_SPIDIS;

                // configure cs pin
                configure_pin<Pin>();

                // configure sck, miso and mosi
                configure_pin<pins::sck>();
                configure_pin<pins::miso>();
                configure_pin<pins::mosi>();

                // do a software reset twice
                spi::port<SPI>->SPI_CR = SPI_CR_SWRST;
                spi::port<SPI>->SPI_CR = SPI_CR_SWRST;

                if constexpr (M == mode::MASTER) {
                    // Set SPI configuration parameters.
                    spi::port<SPI>->SPI_MR = SPI_MR_MSTR | SPI_MR_PS | SPI_MR_MODFDIS | SPI_MR_DLYBCS(1);
                    spi::port<SPI>->SPI_CSR[pin_to_spi<Pin>()] = (static_cast<uint32_t>(Spm) & 0x03)
                                                                 | SPI_CSR_SCBR(Divider) | SPI_CSR_DLYBCT(1)
                                                                 | SPI_CSR_DLYBS(1) | SPI_CSR_CSAAT
                                                                 | ((static_cast<uint32_t>(B) << SPI_CSR_BITS_Pos) &
                                                                    SPI_CSR_BITS_Msk);
                } else {
                    // Set SPI configuration parameters.
                    spi::port<SPI>->SPI_MR = SPI_MR_PS | SPI_MR_MODFDIS;
                    spi::port<SPI>->SPI_CSR[pin_to_spi<Pin>()] = (static_cast<uint32_t>(Spm) & 0x03)
                                                                 | SPI_CSR_SCBR(Divider) | SPI_CSR_DLYBCT(1);
                }

                // enable spi
                spi::port<SPI>->SPI_CR = SPI_CR_SPIEN;
            }

            static uint16_t read() {
                while ((spi::port<SPI>->SPI_SR & SPI_SR_RDRF) == 0);
                return spi::port<SPI>->SPI_RDR & 0xFFFF;
            }

            static void write(uint16_t Data) {
                while ((spi::port<SPI>->SPI_SR & SPI_SR_TXEMPTY) == 0);
                spi::port<SPI>->SPI_TDR = Data | SPI_PCS(static_cast<uint32_t>(pin_to_spi<Pin>()));
                while ((spi::port<SPI>->SPI_SR & SPI_SR_TDRE) == 0);
            }
        };
    }

    //struct spi_uart {
    //    constexpr static uint32_t instance_id = ID_SPI1;
    //};

    //template<>
    //Pio *const spi::port<spi_uart> = SPI0;



    //template<>
    //class bus<spi_uart> {
    //public:
    //    constexpr void init() {
    //
    //    }
    //};
}

#endif //LLIB_DUE_SPI_HPP
