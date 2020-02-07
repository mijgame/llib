#ifndef LLIB_LPC2138_PINS_HPP
#define LLIB_LPC2138_PINS_HPP

#include <type_traits>

#include "pio.hpp"

namespace llib::lpc2138::detail {

}

namespace llib::lpc2138::pins {
    struct p1 {
        using port = pio0;
        constexpr static uint32_t number = 21;

        // PWM5/AD1.6/CAP1.3
    };

    struct p2 {
        using port = pio0;
        constexpr static uint32_t number = 22;

        // AD1.7/CAP0.0/MAT0.0
    };

    struct p3 {
        // RTCX1
    };

    struct p4 {
        using port = pio1;
        constexpr static uint32_t number = 19;

        // TRACEPKT3
    };

    struct p5 {
        // RTCX2
    };

    struct p6 {
        // VSS
    };

    struct p7 {
        // VDDA
    };

    struct p8 {
        using port = pio1;
        constexpr static uint32_t number = 18;

        // TRACEPKT2
    };

    struct p9 {
        using port = pio0;
        constexpr static uint32_t number = 25;

        // AD0.4/AOUT
    };

    struct p10 {
        using port = pio0;
        constexpr static uint32_t number = 26;

        // AD0.5
    };

    struct p11 {
        using port = pio0;
        constexpr static uint32_t number = 27;

        // AD0.5
    };

    struct p12 {
        using port = pio1;
        constexpr static uint32_t number = 17;

        // AD0.0/CAP0.1/MAT0.1
    };

    struct p13 {
        using port = pio0;
        constexpr static uint32_t number = 28;

        // AD0.1/CAP0.2/MAT0.2
    };

    struct p14 {
        using port = pio0;
        constexpr static uint32_t number = 29;

        // AD0.2/CAP0.3/MAT0.3AD0.2/CAP0.3/MAT0.3
    };

    struct p15 {
        using port = pio0;
        constexpr static uint32_t number = 30;

        // AD0.3/EINT3/CAP0.0
    };

    struct p16 {
        using port = pio1;
        constexpr static uint32_t number = 16;

        // TRACEPKT0
    };

    struct p17 {
        using port = pio0;
        constexpr static uint32_t number = 31;
    };

    struct p18 {
        // VSS
    };

    struct p19 {
        using port = pio0;
        constexpr static uint32_t number = 0;

        // TXD0/PWM1
    };

    struct p20 {
        using port = pio1;
        constexpr static uint32_t number = 31;

        // /TRST
    };

    struct p21 {
        using port = pio0;
        constexpr static uint32_t number = 1;

        // RXD0/PWM3/EINT0
    };

    struct p22 {
        using port = pio0;
        constexpr static uint32_t number = 2;

        // SCL0/CAP0.0
    };

    struct p23 {
        // VDD
    };

    struct p24 {
        using port = pio0;
        constexpr static uint32_t number = 26;

        // RTCK
    };

    struct p25 {
        // VSS
    };
    
    struct p26 {
        using port = pio0;
        constexpr static uint32_t number = 3;

        // SDA0/MAT0.0/EINT1
    };

    struct p27 {
        using port = pio0;
        constexpr static uint32_t number = 4;

        // SCK0/CAP0.1/AD0.6
    };

    struct p28 {
        using port = pio1;
        constexpr static uint32_t number = 25;
        
        // EXTIN0
    };

    struct p29 {
        using port = pio0;
        constexpr static uint32_t number = 5;

        // MISO0/MAT0.1/AD0.7
    };

    struct p30 {
        using port = pio0;
        constexpr static uint32_t number = 6;

        // MOSI0/CAP0.2/AD1.0
    };

    struct p31 {
        using port = pio0;
        constexpr static uint32_t number = 7;

        // SSEL0/PWM2/EINT2
    };

    struct p32 {
        using port = pio1;
        constexpr static uint32_t number = 24;

        // TRACECLK
    };

    struct p33 {
        using port = pio0;
        constexpr static uint32_t number = 8;

        // TXD1/PWM4/AD1.1
    };

    struct p34 {
        using port = pio0;
        constexpr static uint32_t number = 9;

        // RXD1/PWM6/EINT3
    };

    struct p35 {
        using port = pio0;
        constexpr static uint32_t number = 10;

        // RTS1/CAP1.0/AD1.2
    };

    struct p36 {
        using port = pio1;
        constexpr static uint32_t number = 23;

        // PIPESTAT2
    };

    struct p37 {
        using port = pio0;
        constexpr static uint32_t number = 11;

        // CTS1/CAP1.1/SCL1
    };

    struct p38 {
        using port = pio0;
        constexpr static uint32_t number = 12;

        // DSR1/MAT1.0/AD1.3
    };

    struct p39 {
        using port = pio0;
        constexpr static uint32_t number = 13;

        // DTR1/MAT1.1/AD1.4
    };

    struct p40 {
        using port = pio1;
        constexpr static uint32_t number = 22;

        // PIPESTAT1
    };

    struct p41 {
        using port = pio0;
        constexpr static uint32_t number = 14;

        // DCD1/EINT1/SDA1
    };

    struct p42 {
        // VSS
    };

    struct p43 {
        // VDD
    };

    struct p44 {
        using port = pio1;
        constexpr static uint32_t number = 21;

        // PIPESTAT0
    };

    struct p45 {
        using port = pio0;
        constexpr static uint32_t number = 15;

        // RI1/EINT2/AD1.5
    };

    struct p46 {
        using port = pio0;
        constexpr static uint32_t number = 16;

        // EINT0/MAT0.2/CAP0.2
    };

    struct p47 {
        using port = pio0;
        constexpr static uint32_t number = 17;

        // CAP1.2/SCK1/MAT1.2
    };

    struct p48 {
        using port = pio1;
        constexpr static uint32_t number = 20;

        // TRACESYNC
    };

    struct p49 {
        // VBAT
    };

    struct p50 {
        // VSS
    };

    struct p51 {
        // VDD
    };

    struct p52 {
        using port = pio1;
        constexpr static uint32_t number = 30;

        // TMS
    };

    struct p53 {
        using port = pio0;
        constexpr static uint32_t number = 18;

        // CAP1.3/MISO1/MAT1.3
    };

    struct p54 {
        using port = pio0;
        constexpr static uint32_t number = 19;
    
        // MAT1.2/MOSI1/CAP1.2
    };
    
    struct p55 {
        using port = pio0;
        constexpr static uint32_t number = 20;

        // MAT1.3/SSEL1/EINT3
    };

    struct p56 {
        using port = pio1;
        constexpr static uint32_t number = 29;
        
        // TCK
    };

    struct p57 {
        // /RESET
    };

    struct p58 {
        using port = pio0;
        constexpr static uint32_t number = 23;
    };

    struct p59 {
        // VSSA
    };

    struct p60 {
        using port = pio1;
        constexpr static uint32_t number = 28;
        
        // TDI
    };

    struct p61 {
        // XTAL2
    };

    struct p62 {
        // XTAL1
    };

    struct p63 {
        // VREFVREF
    };

    struct p64 {
        using port = pio1;
        constexpr static uint32_t number = 27;

        // TDO
    };

    template<typename Pin>
    constexpr uint32_t mask = 1U << Pin::number;

    template<typename Pin>
    const Pio *port = nullptr;

    template<>
    Pio *const port<pio0> = PIO0;

    template<>
    Pio *const port<pio1> = PIO1;
}

namespace llib::lpc2138 {
    template<typename Pin>
    class pin_in {
    public:
        using pin = Pin;

        constexpr static void init() {
            pins::port<typename Pin::port>->IODIR &= ~pins::mask<Pin>;
        }

        constexpr static bool get() {
            return (pins::port<typename Pin::port>->IOPIN & pins::mask<Pin>);
        }
    };

    template<typename Pin>
    class pin_out {
    public:
        using pin = Pin;

        constexpr static void init() {
            pins::port<typename Pin::port>->IODIR |= pins::mask<Pin>;
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<typename Pin::port>->IOSET = pins::mask<Pin>;
            } else {
                pins::port<typename Pin::port>->IOCLR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            (val
             ? pins::port<typename Pin::port>->IOSET
             : pins::port<typename Pin::port>->IOCLR
            ) = pins::mask<Pin>;
        }
    };   
}

#endif