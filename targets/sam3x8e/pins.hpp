#ifndef LLIB_SAM3X8E_PINS_HPP
#define LLIB_SAM3X8E_PINS_HPP

#include <type_traits>

#include "pio.hpp"

namespace llib::sam3x8e::detail {
    namespace pwm {
        enum class mode {
            HIGH,
            LOW,
            FAULT
        };

        template <uint32_t Pwm, mode Mode, typename Periph>
        struct pwm {
            constexpr static uint32_t id = Pwm;
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace can {
        enum class mode {
            TX,
            RX
        };

        template <uint32_t Can, mode Mode, typename Periph>
        struct can {
            constexpr static uint32_t id = Can;
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace uart {
        enum class mode {
            TXD,
            RXD
        };

        template <mode Mode, typename Periph>
        struct uart {
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace usart {
        enum class mode {
            TXD,
            RXD,
            SCK,
            RTS,
            CTS
        };

        template <uint32_t Usart, mode Mode, typename Periph>
        struct usart {
            constexpr static uint32_t id = Usart;
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace twi {
        enum class mode {
            SDA,
            SCL
        };

        template <uint32_t Twi, mode Mode, typename Periph>
        struct twi {
            constexpr static uint32_t id = Twi;
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace spi {
        enum class mode {
            MISO,
            MOSI,
            SCK,
            CS0,
            CS1,
            CS2,
            CS3
        };

        template <mode Mode, typename Periph>
        struct spi {
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace hsmci {
        enum class mode {
            MCCDA,
            MCCK,
            MCDA0,
            MCDA1,
            MCDA2, 
            MCDA3,
            MCDA4,
            MCDA5,
            MCDA6,
            MCDA7
        };

        template <mode Mode, typename Periph>
        struct hsmci {
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace wkup {
        template <uint32_t Wkup, typename Periph>
        struct wkup {
            constexpr static uint32_t id = Wkup;

            using periph = Periph;
        };
    }

    namespace dac {
        template <uint32_t Dac, typename Periph>
        struct dac {
            constexpr static uint32_t id = Dac;

            using periph = Periph;
        };
    }

    namespace adc {
        template <uint32_t Adc, typename Periph>
        struct adc {
            constexpr static uint32_t id = Adc;

            using periph = Periph;
        };
    }

    namespace ebi {
        template <uint32_t AddressBus, typename Periph>
        struct address_bus {
            constexpr static uint32_t id = AddressBus;

            using periph = Periph;
        };

        template <uint32_t DataBus, typename Periph>
        struct data_bus {
            constexpr static uint32_t id = DataBus;

            using periph = Periph;
        };

        enum class mode {
            NCS0,
            NCS1,
            NCS2,
            NCS3,
            NRD,
            NWR0_NWE,
            NBS0,
            NWR1_NBS1,
            NANDRDY,
            NANDOE,
            NANDWE,
            NANDALE,
            NANDCLE,
            NWAIT
        };

        template <mode Mode, typename Periph>
        struct ebi {
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace ssc {
        enum class mode {
            TF,
            TK,
            TD,
            RD,
            RK,
            RF
        };

        template <mode Mode, typename Periph>
        struct ssc {
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace eth {
        enum class mode {
            ETXCK_EREFCK,
            ECRS,
            ECOL,
            ERXDV,
            ERX0,
            ERX1,
            ERX2,
            ERX3,
            ERXER,
            ERXCK,
            ETXEN,
            ETX0,
            ETX1,
            ETX2,
            ETX3,
            ETXER,
            EREFCK,
            ECRSDV
        };

        template <mode Mode, typename Periph>
        struct eth {
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }

    namespace otg {
        enum class mode {
            UOTGVBOF,
            UOTGID
        };

        template <mode Mode, typename Periph>
        struct otg {
            constexpr static mode type = Mode;

            using periph = Periph;
        };        
    }

    namespace tc {
        enum class mode {
            TCLK,
            TIOA,
            TIOB
        };

        template <uint32_t Tc, mode Mode, typename Periph>
        struct tc {
            constexpr static uint32_t id = Tc;
            constexpr static mode type = Mode;

            using periph = Periph;
        };
    }
}

namespace llib::sam3x8e::pins {
    struct p1 {
        // PB26
        using port = piob;
        constexpr static uint32_t number = 26;

        // multiplexed io
        using usart = detail::usart::usart<0, detail::usart::mode::CTS, pio_periph_a>;
        using tc = detail::tc::tc<0, detail::tc::mode::TCLK, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<15, pio_periph_none>;
    };

    struct p2 {
        // PA9
        using port = pioa;
        constexpr static uint32_t number = 9;

        // multiplexed io
        using uart = detail::uart::uart<detail::uart::mode::TXD, pio_periph_a>;
        using pwm = detail::pwm::pwm<3, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p3 {
        // PA10
        using port = pioa;
        constexpr static uint32_t number = 10;

        // multiplexed io
        using usart = detail::usart::usart<0, detail::usart::mode::RXD, pio_periph_a>;
        // datrg periph_b

        // extra functions
        using wkup = detail::wkup::wkup<5, pio_periph_none>;
    };

    struct p4 {
        // PA11
        using port = pioa;
        constexpr static uint32_t number = 11;

        // multiplexed io
        using usart = detail::usart::usart<0, detail::usart::mode::TXD, pio_periph_a>;
        // is a trigger for the analog to digital converter
        // not sure how to handle this yet (adtrg, pio_periph_b)

        // extra functions
        using wkup = detail::wkup::wkup<6, pio_periph_none>;
    };

    struct p5 {
        // PA12
        using port = pioa;
        constexpr static uint32_t number = 12;

        // multiplexed io
        using usart = detail::usart::usart<1, detail::usart::mode::RXD, pio_periph_a>;
        using pwm = detail::pwm::pwm<1, detail::pwm::mode::LOW, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<7, pio_periph_none>;
    };

    struct p6 {
        // PA13
        using port = pioa;
        constexpr static uint32_t number = 13;

        // multiplexed io
        using usart = detail::usart::usart<1, detail::usart::mode::TXD, pio_periph_a>;
        using pwm = detail::pwm::pwm<2, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p7 {
        // PA14
        using port = pioa;
        constexpr static uint32_t number = 14;

        // multiplexed io
        using usart = detail::usart::usart<1, detail::usart::mode::RTS, pio_periph_a>;
        using ssc = detail::ssc::ssc<detail::ssc::mode::TK, pio_periph_b>;
    };

    struct p8 {
        // PA15
        using port = pioa;
        constexpr static uint32_t number = 15;

        // multiplexed io
        using usart = detail::usart::usart<1, detail::usart::mode::CTS, pio_periph_a>;
        using ssc = detail::ssc::ssc<detail::ssc::mode::TF, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<8, pio_periph_none>;
    };

    struct p9 {
        // PA17
        using port = pioa;
        constexpr static uint32_t number = 17;

        // multiplexed io
        using twi = detail::twi::twi<0, detail::twi::mode::SDA, pio_periph_a>;
        using usart = detail::usart::usart<1, detail::usart::mode::SCK, pio_periph_b>;
    };

    struct p10 {
        // VDDCORE
    };

    struct p11 {
        // VDDIO
    };

    struct p12 {
        // GND
    };

    struct p13 {
        // PD0
        using port = piod;
        constexpr static uint32_t number = 0;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<10, pio_periph_a>;
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA4, pio_periph_b>;
    };

    struct p14 {
        // PD1
        using port = piod;
        constexpr static uint32_t number = 1;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<11, pio_periph_a>;
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA5, pio_periph_b>;
    };

    struct p15 {
        // PD2
        using port = piod;
        constexpr static uint32_t number = 2;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<12, pio_periph_a>;
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA6, pio_periph_b>;
    };

    struct p16 {
        // PD3
        using port = piod;
        constexpr static uint32_t number = 3;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<13, pio_periph_a>;
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA7, pio_periph_b>;
    };

    struct p17 {
        // PD4
        using port = piod;
        constexpr static uint32_t number = 4;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<14, pio_periph_a>;
        using usart = detail::usart::usart<3, detail::usart::mode::TXD, pio_periph_b>;
    };

    struct p18 {
        // PD5
        using port = piod;
        constexpr static uint32_t number = 5;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<15, pio_periph_a>;
        using usart = detail::usart::usart<3, detail::usart::mode::RXD, pio_periph_b>;
    };

    struct p19 {
        // PD6
        using port = piod;
        constexpr static uint32_t number = 6;

        // multiplexed io
        // a16/ba0 periph_a
        using address_bus = detail::ebi::address_bus<16, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::FAULT, pio_periph_b>;
    };

    struct p20 {
        // PD7
        using port = piod;
        constexpr static uint32_t number = 7;

        // multiplexed io
        // a17/ba1 periph_a
        using address_bus = detail::ebi::address_bus<17, pio_periph_a>;
        using tc = detail::tc::tc<8, detail::tc::mode::TIOA, pio_periph_b>;
    };

    struct p21 {
        // PD8
        using port = piod;
        constexpr static uint32_t number = 8;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<21, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NANDALE, pio_periph_a>;
        using tc = detail::tc::tc<8, detail::tc::mode::TIOB, pio_periph_b>;
    };

    struct p22 {
        // PD9
        using port = piod;
        constexpr static uint32_t number = 9;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<22, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NANDCLE, pio_periph_a>;
        using tc = detail::tc::tc<8, detail::tc::mode::TCLK, pio_periph_b>;
    };

    struct p23 {
        // PA0
        using port = pioa;
        constexpr static uint32_t number = 0;

        // multiplexed io
        using can = detail::can::can<0, detail::can::mode::TX, pio_periph_a>;
        using pwm = detail::pwm::pwm<3, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p24 {
        // PA1
        using port = pioa;
        constexpr static uint32_t number = 1;

        // multiplexed io
        using can = detail::can::can<0, detail::can::mode::RX, pio_periph_a>;
        // pck0 periph_b

        // extra functions
        using wkup = detail::wkup::wkup<0, pio_periph_none>;
    };

    struct p25 {
        // PA5
        using port = pioa;
        constexpr static uint32_t number = 5;

        // multiplexed io
        using tc = detail::tc::tc<2, detail::tc::mode::TIOA, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::FAULT, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<2, pio_periph_none>;
    };

    struct p26 {
        // PA7
        using port = pioa;
        constexpr static uint32_t number = 7;

        // multiplexed io
        using tc = detail::tc::tc<2, detail::tc::mode::TCLK, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NCS0, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<3, pio_periph_none>;
    };

    struct p27 {
        // PA8
        using port = pioa;
        constexpr static uint32_t number = 8;

        // multiplexed io
        using uart = detail::uart::uart<detail::uart::mode::RXD, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::HIGH, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<4, pio_periph_none>;
    };

    struct p28 {
        // PB28
        using port = piob;
        constexpr static uint32_t number = 28;

        // multiplexed io (TCK after reset)
        // tck/swclk periph_a
    };

    struct p29 {
        // PB29
        using port = piob;
        constexpr static uint32_t number = 29;

        // multiplexed io (tdi after reset)
        // tdi periph_a
    };

    struct p30 {
        // PB30
        using port = piob;
        constexpr static uint32_t number = 30;

        // multiplexed io (tdo after reset)
        // tdo/traceswo periph_a
    };

    struct p31 {
        // PB31
        using port = piob;
        constexpr static uint32_t number = 31;

        // multiplexed io (tms after reset)
        // tms/swdio
    };

    struct p32 {
        // PD10
        using port = piod;
        constexpr static uint32_t number = 10;

        // multiplexed io
        // nwr1/nbs1 periph_a
        using ebi = detail::ebi::ebi<detail::ebi::mode::NWR1_NBS1, pio_periph_a>;
    };

    struct p33 {
        // GNDPLL
    };

    struct p34 {
        // VDDPLL
    };

    struct p35 {
        // XOUT
    };

    struct p36 {
        // XIN
    };

    struct p37 {
        // DHSDP
    };

    struct p38 {
        // DHSDM
    };

    struct p39 {
        // VBUS
    };

    struct p40 {
        // VBG
    };

    struct p41 {
        // VDDUTMI
    };

    struct p42 {
        // DFSDP
    };

    struct p43 {
        // DFSDM
    };

    struct p44 {
        // GNDUTMI
    };

    struct p45 {
        // VDDCORE
    };

    struct p46 {
        // JTAGSEL
    };

    struct p47 {
        // NRSTB
    };

    struct p48 {
        // XIN32
    };

    struct p49 {
        // XOUT32
    };

    struct p50 {
        // SHDN
    };

    struct p51 {
        // TST
    };

    struct p52 {
        // VDDBU
    };

    struct p53 {
        // FWUP
    };

    struct p54 {
        // GNDBU
    };

    struct p55 {
        // PC1
        using port = pioc;
        constexpr static uint32_t number = 1;
    };

    struct p56 {
        // VDDOUT
    };

    struct p57 {
        // VDDIN
    };

    struct p58 {
        // GND
    };

    struct p59 {
        // PC2
        using port = pioc;
        constexpr static uint32_t number = 2;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<0, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p60 {
        // PC3
        using port = pioc;
        constexpr static uint32_t number = 3;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<1, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p61 {
        // VDDCORE
    };

    struct p62 {
        // VDDIO
    };

    struct p63 {
        // PC5
        using port = pioc;
        constexpr static uint32_t number = 5;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<3, pio_periph_a>;
        using pwm = detail::pwm::pwm<1, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p64 {
        // PC6
        using port = pioc;
        constexpr static uint32_t number = 6;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<4, pio_periph_a>;
        using pwm = detail::pwm::pwm<2, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p65 {
        // PC7
        using port = pioc;
        constexpr static uint32_t number = 7;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<5, pio_periph_a>;
        using pwm = detail::pwm::pwm<2, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p66 {
        // PC8
        using port = pioc;
        constexpr static uint32_t number = 8;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<6, pio_periph_a>;
        using pwm = detail::pwm::pwm<3, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p67 {
        // PC9
        using port = pioc;
        constexpr static uint32_t number = 9;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<7, pio_periph_a>;
        using pwm = detail::pwm::pwm<3, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p68 {
        // PB27
        using port = piob;
        constexpr static uint32_t number = 27;

        // multiplexed io
        using ebi = detail::ebi::ebi<detail::ebi::mode::NCS3, pio_periph_a>;
        using tc = detail::tc::tc<0, detail::tc::mode::TIOB, pio_periph_b>;
    };

    struct p69 {
        // NRST
    };

    struct p70 {
        // PA18
        using port = pioa;
        constexpr static uint32_t number = 18;

        // multiplexed io
        using twi = detail::twi::twi<0, detail::twi::mode::SCL, pio_periph_a>;
        using address_bus = detail::ebi::address_bus<20, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<9, pio_periph_none>;
    };

    struct p71 {
        // PA19
        using port = pioa;
        constexpr static uint32_t number = 19;

        // multiplexed io
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCCK, pio_periph_a>;
        using pwm = detail::pwm::pwm<1, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p72 {
        // PA20
        using port = pioa;
        constexpr static uint32_t number = 20;

        // multiplexed io
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCCDA, pio_periph_a>;
        using pwm = detail::pwm::pwm<2, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p73 {
        // VDDANA
    };

    struct p74 {
        // GNDANA
    };

    struct p75 {
        // ADVREF
    };

    struct p76 {
        // PB15
        using port = piob;
        constexpr static uint32_t number = 15;

        // multiplexed io
        using can = detail::can::can<1, detail::can::mode::RX, pio_periph_a>;
        using pwm = detail::pwm::pwm<3, detail::pwm::mode::HIGH, pio_periph_b>;

        // extra functions
        using dac = detail::dac::dac<0, pio_periph_none>;
        using wkup = detail::wkup::wkup<12, pio_periph_none>;
    };

    struct p77 {
        // PB16
        using port = piob;
        constexpr static uint32_t number = 16;

        // multiplexed io
        using tc = detail::tc::tc<5, detail::tc::mode::TCLK, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::LOW, pio_periph_b>;

        // extra functions
        using dac = detail::dac::dac<1, pio_periph_none>;
    };

    struct p78 {
        // PA16
        using port = pioa;
        constexpr static uint32_t number = 16;

        // multiplexed io
        using usart = detail::usart::usart<1, detail::usart::mode::SCK, pio_periph_a>;
        using ssc = detail::ssc::ssc<detail::ssc::mode::TD, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<7, pio_periph_none>;
    };

    struct p79 {
        // PA24
        using port = pioa;
        constexpr static uint32_t number = 24;

        // multiplexed io
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA3, pio_periph_a>;
        // pck1 periph_b

        using adc = detail::adc::adc<6, pio_periph_none>;
    };

    struct p80 {
        // PA23
        using port = pioa;
        constexpr static uint32_t number = 23;

        // multiplexed io
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA2, pio_periph_a>;
        using tc = detail::tc::tc<4, detail::tc::mode::TCLK, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<5, pio_periph_none>;
    };

    struct p81 {
        // PA22
        using port = pioa;
        constexpr static uint32_t number = 22;

        // multiplexed io
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA1, pio_periph_a>;
        // tclk3

        // extra functions
        using adc = detail::adc::adc<4, pio_periph_none>;
    };

    struct p82 {
        // PA6
        using port = pioa;
        constexpr static uint32_t number = 6;

        // multiplexed io
        using tc = detail::tc::tc<2, detail::tc::mode::TIOB, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NCS0, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<3, pio_periph_none>;
    };

    struct p83 {
        // PA4
        using port = pioa;
        constexpr static uint32_t number = 4;

        // multiplexed io
        using tc = detail::tc::tc<1, detail::tc::mode::TCLK, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NWAIT, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<2, pio_periph_none>;
    };

    struct p84 {
        // PA3
        using port = pioa;
        constexpr static uint32_t number = 3;

        // multiplexed io
        using tc = detail::tc::tc<1, detail::tc::mode::TIOB, pio_periph_a>;
        using pwm = detail::pwm::pwm<1, detail::pwm::mode::FAULT, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<1, pio_periph_none>;
        using wkup = detail::wkup::wkup<1, pio_periph_none>;
    };

    struct p85 {
        // PA2
        using port = pioa;
        constexpr static uint32_t number = 2;

        // multiplexed io
        using tc = detail::tc::tc<1, detail::tc::mode::TIOA, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NANDRDY, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<0, pio_periph_none>;
    };

    struct p86 {
        // PB12
        using port = piob;
        constexpr static uint32_t number = 12;

        // multiplexed io
        using twi = detail::twi::twi<1, detail::twi::mode::SDA, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::HIGH, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<8, pio_periph_none>;
    };

    struct p87 {
        // PB13
        using port = piob;
        constexpr static uint32_t number = 13;

        // multiplexed io
        using twi = detail::twi::twi<1, detail::twi::mode::SCL, pio_periph_a>;
        using pwm = detail::pwm::pwm<1, detail::pwm::mode::HIGH, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<9, pio_periph_none>;
    };

    struct p88 {
        // PB17
        using port = piob;
        constexpr static uint32_t number = 17;

        // multiplexed io
        using ssc = detail::ssc::ssc<detail::ssc::mode::RF, pio_periph_a>;
        using pwm = detail::pwm::pwm<1, detail::pwm::mode::LOW, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<10, pio_periph_none>;
    };

    struct p89 {
        // PB18
        using port = piob;
        constexpr static uint32_t number = 18;

        // multiplexed io
        using ssc = detail::ssc::ssc<detail::ssc::mode::RD, pio_periph_a>;
        using pwm = detail::pwm::pwm<2, detail::pwm::mode::LOW, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<11, pio_periph_none>;
    };

    struct p90 {
        // PB19
        using port = piob;
        constexpr static uint32_t number = 19;

        // multiplexed io
        using ssc = detail::ssc::ssc<detail::ssc::mode::RK, pio_periph_a>;
        using pwm = detail::pwm::pwm<3, detail::pwm::mode::LOW, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<12, pio_periph_none>;
    };

    struct p91 {
        // PB20
        using port = piob;
        constexpr static uint32_t number = 20;

        // multiplexed io
        using usart = detail::usart::usart<2, detail::usart::mode::TXD, pio_periph_a>;
        using spi = detail::spi::spi<detail::spi::mode::CS1, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<13, pio_periph_none>;
    };

    struct p92 {
        // PB21
        using port = piob;
        constexpr static uint32_t number = 21;

        // multiplexed io
        using usart = detail::usart::usart<2, detail::usart::mode::RXD, pio_periph_a>;
        using spi = detail::spi::spi<detail::spi::mode::CS2, pio_periph_b>;

        // extra functions
        using adc = detail::adc::adc<14, pio_periph_none>;
        using wkup = detail::wkup::wkup<13, pio_periph_none>;
    };

    struct p93 {
        // PC11
        using port = pioc;
        constexpr static uint32_t number = 11;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<9, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ERX2, pio_periph_b>;
    };

    struct p94 {
        // PC12
        using port = pioc;
        constexpr static uint32_t number = 12;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<10, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ERX3, pio_periph_b>;
    };

    struct p95 {
        // PC13
        using port = pioc;
        constexpr static uint32_t number = 13;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<11, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ECOL, pio_periph_b>;
    };

    struct p96 {
        // PC14
        using port = pioc;
        constexpr static uint32_t number = 14;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<12, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ERXCK, pio_periph_b>;
    };

    struct p97 {
        // PC15
        using port = pioc;
        constexpr static uint32_t number = 15;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<13, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ETX2, pio_periph_b>;
    };

    struct p98 {
        // PC16
        using port = pioc;
        constexpr static uint32_t number = 16;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<14, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ETX3, pio_periph_b>;
    };

    struct p99 {
        // PC17
        using port = pioc;
        constexpr static uint32_t number = 17;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<15, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ETXER, pio_periph_b>;
    };

    struct p100 {
        // PC18
        using port = pioc;
        constexpr static uint32_t number = 18;

        // multiplexed io
        using ebi = detail::ebi::ebi<detail::ebi::mode::NWR0_NWE, pio_periph_a>;
        using pwm = detail::pwm::pwm<5, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p101 {
        // PC19
        using port = pioc;
        constexpr static uint32_t number = 19;

        // multiplexed io
        using ebi = detail::ebi::ebi<detail::ebi::mode::NANDOE, pio_periph_a>;
        using pwm = detail::pwm::pwm<5, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p102 {
        // PC29
        using port = pioc;
        constexpr static uint32_t number = 29;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<8, pio_periph_a>;
        using tc = detail::tc::tc<7, detail::tc::mode::TIOB, pio_periph_b>;
    };

    struct p103 {
        // PC30
        using port = pioc;
        constexpr static uint32_t number = 30;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<9, pio_periph_a>;
        using tc = detail::tc::tc<7, detail::tc::mode::TCLK, pio_periph_b>;
    };

    struct p104 {
        // VDDCORE
    };

    struct p105 {
        // VDDIO
    };

    struct p106 {
        // GND
    };

    struct p107 {
        // PA21
        using port = pioa;
        constexpr static uint32_t number = 21;

        // multiplexed io
        using hsmci = detail::hsmci::hsmci<detail::hsmci::mode::MCDA0, pio_periph_a>;
        using pwm = detail::pwm::pwm<0, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p108 {
        // PA25
        using port = pioa;
        constexpr static uint32_t number = 25;

        // multiplexed io
        using spi = detail::spi::spi<detail::spi::mode::MISO, pio_periph_a>;
        using address_bus = detail::ebi::address_bus<18, pio_periph_b>;
    };

    struct p109 {
        // PA26
        using port = pioa;
        constexpr static uint32_t number = 26;

        // multiplexed io
        using spi = detail::spi::spi<detail::spi::mode::MOSI, pio_periph_a>;
        using address_bus = detail::ebi::address_bus<19, pio_periph_b>;
    };

    struct p110 {
        // PA27
        using port = pioa;
        constexpr static uint32_t number = 27;

        // multiplexed io
        using spi = detail::spi::spi<detail::spi::mode::SCK, pio_periph_a>;
        using address_bus = detail::ebi::address_bus<20, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<10, pio_periph_none>;
    };

    struct p111 {
        // PA28
        using port = pioa;
        constexpr static uint32_t number = 28;

        // multiplexed io
        using spi = detail::spi::spi<detail::spi::mode::CS0, pio_periph_a>;
        // pck2 periph_b

        // extra functions
        using wkup = detail::wkup::wkup<11, pio_periph_none>;
    };

    struct p112 {
        // PA29
        using port = pioa;
        constexpr static uint32_t number = 29;

        // multiplexed io
        using spi = detail::spi::spi<detail::spi::mode::CS1, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NRD, pio_periph_b>;
    };

    struct p113 {
        // PB0
        using port = piob;
        constexpr static uint32_t number = 0;

        // multiplexed io
        using eth = detail::eth::eth<detail::eth::mode::ETXCK_EREFCK, pio_periph_a>;
    };

    struct p114 {
        // PB1
        using port = piob;
        constexpr static uint32_t number = 1;

        // multiplexed io
        using eth = detail::eth::eth<detail::eth::mode::ETXEN, pio_periph_a>;
    };

    struct p115 {
        // PB2
        using port = piob;
        constexpr static uint32_t number = 2;

        // multiplexed io
        using eth = detail::eth::eth<detail::eth::mode::ETX0, pio_periph_a>;
    };

    struct p116 {
        // PC4
        using port = pioc;
        constexpr static uint32_t number = 4;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<2, pio_periph_a>;
        using pwm = detail::pwm::pwm<1, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p117 {
        // PC10
        using port = pioc;
        constexpr static uint32_t number = 10;

        // multiplexed io
        using data_bus = detail::ebi::data_bus<8, pio_periph_a>;
        using eth = detail::eth::eth<detail::eth::mode::ECRS, pio_periph_b>;
    };

    struct p118 {
        // PB3
        using port = piob;
        constexpr static uint32_t number = 3;

        // multiplexed io
        using eth = detail::eth::eth<detail::eth::mode::ETX1, pio_periph_a>;
    };

    struct p119 {
        // PB4
        using port = piob;
        constexpr static uint32_t number = 4;

        // multiplexed io
        // ecrsdv/erxdv periph_a
        using eth = detail::eth::eth<detail::eth::mode::ERXDV, pio_periph_a>;
    };

    struct p120 {
        // PB5
        using port = piob;
        constexpr static uint32_t number = 5;

        // multiplexed io
        using eth = detail::eth::eth<detail::eth::mode::ERX0, pio_periph_a>;
    };

    struct p121 {
        // PB6
        using port = piob;
        constexpr static uint32_t number = 6;

        // multiplexed io
        using eth = detail::eth::eth<detail::eth::mode::ERX1, pio_periph_a>;
    };

    struct p122 {
        // PB7
        using port = piob;
        constexpr static uint32_t number = 7;

        // multiplexed io
        using eth = detail::eth::eth<detail::eth::mode::ERXER, pio_periph_a>;
    };

    struct p123 {
        // PB8
        using port = piob;
        constexpr static uint32_t number = 8;

        // multiplexed io
        // emdc periph_a
    };

    struct p124 {
        // VDDCORE
    };

    struct p125 {
        // VDDIO
    };

    struct p126 {
        // GND
    };

    struct p127 {
        // PB9
        using port = piob;
        constexpr static uint32_t number = 9;

        // multiplexed io
        // emdio periph_a
    };

    struct p128 {
        // PB10
        using port = piob;
        constexpr static uint32_t number = 10;

        // multiplexed io
        using otg = detail::otg::otg<detail::otg::mode::UOTGVBOF, pio_periph_a>;
        using address_bus = detail::ebi::address_bus<18, pio_periph_b>;
    };

    struct p129 {
        // PB11
        using port = piob;
        constexpr static uint32_t number = 11;

        // multiplexed io
        using otg = detail::otg::otg<detail::otg::mode::UOTGID, pio_periph_a>;
        using address_bus = detail::ebi::address_bus<19, pio_periph_b>;
    };

    struct p130 {
        // PC0
        using port = pioc;
        constexpr static uint32_t number = 0;
    };

    struct p131 {
        // PC20
        using port = pioc;
        constexpr static uint32_t number = 20;

        // multiplexed io
        using ebi = detail::ebi::ebi<detail::ebi::mode::NANDWE, pio_periph_a>;
        using pwm = detail::pwm::pwm<4, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p132 {
        // PC21
        using port = pioc;
        constexpr static uint32_t number = 21;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<0, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NBS0, pio_periph_a>;
        using pwm = detail::pwm::pwm<4, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p133 {
        // PC22
        using port = pioc;
        constexpr static uint32_t number = 22;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<1, pio_periph_a>;
        using pwm = detail::pwm::pwm<5, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p134 {
        // PC23
        using port = pioc;
        constexpr static uint32_t number = 23;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<2, pio_periph_a>;
        using pwm = detail::pwm::pwm<6, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p135 {
        // PC24
        using port = pioc;
        constexpr static uint32_t number = 24;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<3, pio_periph_a>;
        using pwm = detail::pwm::pwm<7, detail::pwm::mode::LOW, pio_periph_b>;
    };

    struct p136 {
        // PC25
        using port = pioc;
        constexpr static uint32_t number = 25;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<4, pio_periph_a>;
        using tc = detail::tc::tc<6, detail::tc::mode::TIOA, pio_periph_b>;
    };

    struct p137 {
        // PC26
        using port = pioc;
        constexpr static uint32_t number = 26;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<5, pio_periph_a>;
        using tc = detail::tc::tc<6, detail::tc::mode::TIOB, pio_periph_b>;
    };

    struct p138 {
        // PC27
        using port = pioc;
        constexpr static uint32_t number = 27;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<6, pio_periph_a>;
        using tc = detail::tc::tc<6, detail::tc::mode::TCLK, pio_periph_b>;
    };

    struct p139 {
        // PC28
        using port = pioc;
        constexpr static uint32_t number = 28;

        // multiplexed io
        using address_bus = detail::ebi::address_bus<7, pio_periph_a>;
        using tc = detail::tc::tc<7, detail::tc::mode::TIOA, pio_periph_b>;
    };

    struct p140 {
        // PB14
        using port = piob;
        constexpr static uint32_t number = 14;

        // multiplexed io
        using can = detail::can::can<1, detail::can::mode::TX, pio_periph_a>;
        using pwm = detail::pwm::pwm<2, detail::pwm::mode::HIGH, pio_periph_b>;
    };

    struct p141 {
        // PB22
        using port = piob;
        constexpr static uint32_t number = 22;

        // multiplexed io
        using usart = detail::usart::usart<2, detail::usart::mode::RTS, pio_periph_a>;
        // pck0 periph_b
    };

    struct p142 {
        // PB23
        using port = piob;
        constexpr static uint32_t number = 23;

        // multiplexed io
        using usart = detail::usart::usart<2, detail::usart::mode::CTS, pio_periph_a>;
        using spi = detail::spi::spi<detail::spi::mode::CS3, pio_periph_b>;

        // extra functions
        using wkup = detail::wkup::wkup<14, pio_periph_none>;
    };

    struct p143 {
        // PB24
        using port = piob;
        constexpr static uint32_t number = 24;

        // multiplexed io
        using usart = detail::usart::usart<2, detail::usart::mode::SCK, pio_periph_a>;
        using ebi = detail::ebi::ebi<detail::ebi::mode::NCS2, pio_periph_b>;
    };

    struct p144 {
        // PB25
        using port = piob;
        constexpr static uint32_t number = 25;

        // multiplexed io
        using usart = detail::usart::usart<0, detail::usart::mode::RTS, pio_periph_a>;
        using tc = detail::tc::tc<0, detail::tc::mode::TIOA, pio_periph_b>;
    };

    template<typename Pin>
    constexpr uint32_t mask = 1U << Pin::number;

    template<typename Pin>
    const Pio *port = nullptr;

    template<>
    Pio *const port<pioa> = PIOA;

    template<>
    Pio *const port<piob> = PIOB;

    template<>
    Pio *const port<pioc> = PIOC;

    template<>
    Pio *const port<piod> = PIOD;    
}

namespace llib::sam3x8e {
    template<typename Pin>
    class pin_in {
    public:
        using pin = Pin;

        constexpr static void init() {
            enable_clock<typename Pin::port>();
            pins::port<typename Pin::port>->PIO_ODR = pins::mask<Pin>;
        }

        constexpr static bool get() {
            return (pins::port<typename Pin::port>->PIO_PDSR & pins::mask<Pin>) != 0;
        }

        constexpr static void pullup_enable() {
            pins::port<typename Pin::port>->PIO_PUER = pins::mask<Pin>;
        }

        constexpr static void pullup_disable() {
            pins::port<typename Pin::port>->PIO_PUDR = pins::mask<Pin>;
        }
    };

    template<typename Pin>
    class pin_out {
    public:
        using pin = Pin;

        constexpr static void init() {
            enable_clock<typename Pin::port>();
            pins::port<typename Pin::port>->PIO_OER = pins::mask<Pin>;
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<typename Pin::port>->PIO_SODR = pins::mask<Pin>;
            } else {
                pins::port<typename Pin::port>->PIO_CODR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            (val
             ? pins::port<typename Pin::port>->PIO_SODR
             : pins::port<typename Pin::port>->PIO_CODR
            ) = pins::mask<Pin>;
        }
    };

    template<typename Pin>
    class pin_in_out {
    public:
        using pin = Pin;

        constexpr static bool get() {
            pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            return pin_in<Pin>::get();
        }

        constexpr static void pullup_enable() {
            pin_in<Pin>::pullup_enable();
        }

        constexpr static void pullup_disable() {
            pin_in<Pin>::pullup_disable();
        }

        template<bool val>
        constexpr static void set() {
            pins::port<Pin>->PIO_OER = pins::mask<Pin>;
            pin_out<Pin>::template set<val>();
        }

        constexpr static void set(const bool val) {
            pins::port<Pin>->PIO_OER = pins::mask<Pin>;
            pin_out<Pin>::set(val);
        }
    };

    template<typename Pin>
    class pin_oc {
    public:
        using pin = Pin;

        constexpr static void init() {
            enable_clock<typename Pin::port>();
        }

        constexpr static bool get() {
            return pin_in<Pin>::get();
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            } else {
                pins::port<Pin>->PIO_OER = pins::mask<Pin>;
                pins::port<Pin>->PIO_CODR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            if (val) {
                pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            } else {
                pins::port<Pin>->PIO_OER = pins::mask<Pin>;
                pins::port<Pin>->PIO_CODR = pins::mask<Pin>;
            }
        }
    };

    /**
     * @brief Set the peripheral of a pin
     * 
     * @tparam Pin 
     * @tparam Periph 
     */
    template<typename Pin, typename Periph>
    void set_peripheral() {
        if constexpr (std::is_same_v<Periph, pio_periph_none>) {
            // add pin back to the pio controller
            pins::port<typename Pin::port>->PIO_PER = pins::mask<Pin>;
            return;
        }

        // Disable interrupts on the pin
        pins::port<typename Pin::port>->PIO_IDR = pins::mask<Pin>;
        uint32_t t = pins::port<typename Pin::port>->PIO_ABSR;

        // Change pio multiplexer
        if constexpr (std::is_same_v<Periph, pio_periph_a>) {
            pins::port<typename Pin::port>->PIO_ABSR &= (~pins::mask<Pin> & t);
        } else if constexpr (std::is_same_v<Periph, pio_periph_b>) {
            pins::port<typename Pin::port>->PIO_ABSR = (pins::mask<Pin> | t);
        }

        // disable pull ups
        pins::port<typename Pin::port>->PIO_PUDR = pins::mask<Pin>;

        // remove pin from pio controller
        pins::port<typename Pin::port>->PIO_PDR = pins::mask<Pin>;
    }     
}

#endif