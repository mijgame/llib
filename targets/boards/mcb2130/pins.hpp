#ifndef LLIB_MCB2130_PINS_HPP
#define LLIB_MCB2130_PINS_HPP

#include <lpc2138/ppins.hpp>

namespace llib::lpc2138::mcb2130::pins {
    // using the lpc2138 pins
    using p0_d0 = lpc2138::pins::p19;
    using p0_d1 = lpc2138::pins::p21;
    using p0_d2 = lpc2138::pins::p22;
    using p0_d3 = lpc2138::pins::p26;
    using p0_d4 = lpc2138::pins::p27;
    using p0_d5 = lpc2138::pins::p29;
    using p0_d6 = lpc2138::pins::p30;
    using p0_d7 = lpc2138::pins::p31;

    using p0_d8 = lpc2138::pins::p33;
    using p0_d9 = lpc2138::pins::p34;
    using p0_d10 = lpc2138::pins::p35;
    using p0_d11 = lpc2138::pins::p37;
    using p0_d12 = lpc2138::pins::p38;
    using p0_d13 = lpc2138::pins::p39;
    using p0_d14 = lpc2138::pins::p41;
    using p0_d15 = lpc2138::pins::p45;

    using p0_d16 = lpc2138::pins::p46;
    using p0_d17 = lpc2138::pins::p47;
    using p0_d18 = lpc2138::pins::p53;
    using p0_d19 = lpc2138::pins::p54;
    using p0_d20 = lpc2138::pins::p55;
    using p0_d21 = lpc2138::pins::p1;
    using p0_d22 = lpc2138::pins::p2;
    using p0_d23 = lpc2138::pins::p58;

    using p0_d24 = lpc2138::pins::p9;
    using p0_d25 = lpc2138::pins::p10;
    using p0_d26 = lpc2138::pins::p11;
    using p0_d27 = lpc2138::pins::p12;
    using p0_d28 = lpc2138::pins::p13;
    using p0_d29 = lpc2138::pins::p14;
    using p0_d30 = lpc2138::pins::p15;
    using p0_d31 = lpc2138::pins::p17;

    using p1_d16 = lpc2138::pins::p16;
    using p1_d17 = lpc2138::pins::p12;
    using p1_d18 = lpc2138::pins::p8;
    using p1_d19 = lpc2138::pins::p4;
    using p1_d20 = lpc2138::pins::p48;
    using p1_d21 = lpc2138::pins::p44;
    using p1_d22 = lpc2138::pins::p40;
    using p1_d23 = lpc2138::pins::p36;

    using p1_d24 = lpc2138::pins::p32;
    using p1_d25 = lpc2138::pins::p28;
    using p1_d26 = lpc2138::pins::p24;
    using p1_d27 = lpc2138::pins::p64;
    using p1_d28 = lpc2138::pins::p60;
    using p1_d29 = lpc2138::pins::p56;
    using p1_d30 = lpc2138::pins::p52;
    using p1_d31 = lpc2138::pins::p20;
    
    using led = lpc2138::pins::p36;

    // using the led as led_0    
    using led_0 = led;
    using led_1 = lpc2138::pins::p40;
    using led_2 = lpc2138::pins::p44;
    using led_3 = lpc2138::pins::p48;

    using led_4 = lpc2138::pins::p4;
    using led_5 = lpc2138::pins::p8;
    using led_6 = lpc2138::pins::p12;
    using led_7 = lpc2138::pins::p16;

    using speaker = lpc2138::pins::p9;

} // namespace llib::due

#endif //LLIB_MCB2130_PINS_HPP