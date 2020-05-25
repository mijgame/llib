#ifndef LLIB_DUE_CORE_PINS_HPP
#define LLIB_DUE_CORE_PINS_HPP

#include <sam3x8e/ppins.hpp>

namespace llib::sam3x8e::due_core::pins {
    // using the sam3x8e pinsd
    // d1 = Reset (Pull low to reset)
    using d2 = sam3x8e::pins::p27;
    // d3 = VBUS_5V
    using d4 = sam3x8e::pins::p2;
    // d5 = master_rst
    // d6 = ext_erase
    // d7 = ext_fwup
    // d8 = shdn
    using d9 = sam3x8e::pins::p111;
    using d10 = sam3x8e::pins::p112;
    using d11 = sam3x8e::pins::p109;
    using d12 = sam3x8e::pins::p110;
    // d13 = AGND
    using d14 = sam3x8e::pins::p108;
    using d15 = sam3x8e::pins::p79;
    // d16 = AREF
    using d17 = sam3x8e::pins::p81;
    using d18 = sam3x8e::pins::p80;
    using d19 = sam3x8e::pins::p72;
    using d20 = sam3x8e::pins::p107;
    using d21 = sam3x8e::pins::p70;
    using d22 = sam3x8e::pins::p71;
    using d23 = sam3x8e::pins::p78;
    using d24 = sam3x8e::pins::p9;
    using d25 = sam3x8e::pins::p7;
    using d26 = sam3x8e::pins::p8;
    using d27 = sam3x8e::pins::p5;
    using d28 = sam3x8e::pins::p6;
    using d29 = sam3x8e::pins::p3;
    using d30 = sam3x8e::pins::p4;
    using d31 = sam3x8e::pins::p27;
    using d32 = sam3x8e::pins::p2;
    using d33 = sam3x8e::pins::p82;
    using d34 = sam3x8e::pins::p26;
    using d35 = sam3x8e::pins::p83;
    using d36 = sam3x8e::pins::p25;
    using d37 = sam3x8e::pins::p85;
    using d38 = sam3x8e::pins::p84;
    using d39 = sam3x8e::pins::p23;
    using d40 = sam3x8e::pins::p24;
    using d41 = sam3x8e::pins::p102;
    using d42 = sam3x8e::pins::p103;
    using d43 = sam3x8e::pins::p138;
    using d44 = sam3x8e::pins::p139;

    // d45 = VCC_5V_IN
    // d46 = GND
    // the JTAG pins are multiplext to JTAG after reset
    // if the user wants to use these pins they need to
    // be removed from the multiplexer.
    using d47 = sam3x8e::pins::p31;
    using d48 = sam3x8e::pins::p30;
    using d49 = sam3x8e::pins::p28;
    using d50 = sam3x8e::pins::p29;
    using d51 = sam3x8e::pins::p1;
    using d52 = sam3x8e::pins::p68;
    using d53 = sam3x8e::pins::p143;
    using d54 = sam3x8e::pins::p144;
    using d55 = sam3x8e::pins::p141;
    using d56 = sam3x8e::pins::p142;
    using d57 = sam3x8e::pins::p91;
    using d58 = sam3x8e::pins::p92;
    using d59 = sam3x8e::pins::p89;
    using d60 = sam3x8e::pins::p90;
    using d61 = sam3x8e::pins::p77;
    using d62 = sam3x8e::pins::p88;
    using d63 = sam3x8e::pins::p140;
    using d64 = sam3x8e::pins::p76;
    using d65 = sam3x8e::pins::p86;
    using d66 = sam3x8e::pins::p87;
    using d67 = sam3x8e::pins::p128;
    using d68 = sam3x8e::pins::p129;
    using d69 = sam3x8e::pins::p123;
    using d70 = sam3x8e::pins::p127;
    using d71 = sam3x8e::pins::p121;
    using d72 = sam3x8e::pins::p122;
    using d73 = sam3x8e::pins::p119;
    using d74 = sam3x8e::pins::p120;
    using d75 = sam3x8e::pins::p115;
    using d76 = sam3x8e::pins::p118;
    using d77 = sam3x8e::pins::p113;
    using d78 = sam3x8e::pins::p114;
    using d79 = sam3x8e::pins::p32;
    using d80 = sam3x8e::pins::p22;
    using d81 = sam3x8e::pins::p21;
    using d82 = sam3x8e::pins::p20;
    using d83 = sam3x8e::pins::p19;
    using d84 = sam3x8e::pins::p18;
    using d85 = sam3x8e::pins::p17;
    using d86 = sam3x8e::pins::p16;
    using d87 = sam3x8e::pins::p15;
    using d88 = sam3x8e::pins::p14;

    using d89 = sam3x8e::pins::p130;
    using d90 = sam3x8e::pins::p13;
    using d91 = sam3x8e::pins::p59;
    using d92 = sam3x8e::pins::p55;
    using d93 = sam3x8e::pins::p116;
    using d94 = sam3x8e::pins::p60;
    using d95 = sam3x8e::pins::p64;
    using d96 = sam3x8e::pins::p63;
    using d97 = sam3x8e::pins::p66;
    using d98 = sam3x8e::pins::p65;
    using d99 = sam3x8e::pins::p117;
    using d100 = sam3x8e::pins::p67;
    using d101 = sam3x8e::pins::p94;
    using d102 = sam3x8e::pins::p93;
    using d103 = sam3x8e::pins::p96;
    using d104 = sam3x8e::pins::p95;
    using d105 = sam3x8e::pins::p98;
    using d106 = sam3x8e::pins::p97;
    using d107 = sam3x8e::pins::p100;
    using d108 = sam3x8e::pins::p99;
    using d109 = sam3x8e::pins::p131;
    using d110 = sam3x8e::pins::p101;
    using d111 = sam3x8e::pins::p133;
    using d112 = sam3x8e::pins::p132;
    using d113 = sam3x8e::pins::p135;
    using d114 = sam3x8e::pins::p134;
    using d115 = sam3x8e::pins::p137;
    using d116 = sam3x8e::pins::p136;

    // extra for additional functionality
    using a0 = sam3x8e::pins::p78;
    using a1 = sam3x8e::pins::p79;
    using a2 = sam3x8e::pins::p80;
    using a3 = sam3x8e::pins::p81;
    using a4 = sam3x8e::pins::p82;
    using a5 = sam3x8e::pins::p83;
    using a6 = sam3x8e::pins::p84;
    using a7 = sam3x8e::pins::p85;
    using a8 = sam3x8e::pins::p86;
    using a9 = sam3x8e::pins::p87;
    using a10 = sam3x8e::pins::p88;
    using a11 = sam3x8e::pins::p89;
    using a12 = sam3x8e::pins::p90;
    using a13 = sam3x8e::pins::p91;

    using dac0 = sam3x8e::pins::p76;
    using dac1 = sam3x8e::pins::p77;
    using canrx0 = sam3x8e::pins::p24;
    using cantx0 = sam3x8e::pins::p23;
    using canrx1 = sam3x8e::pins::p76;
    using cantx1 = sam3x8e::pins::p140;
    using scl = sam3x8e::pins::p87;
    using sda = sam3x8e::pins::p86;
    using scl1 = sam3x8e::pins::p70;
    using sda1 = sam3x8e::pins::p9;
    using tx = sam3x8e::pins::p2;
    using rx = sam3x8e::pins::p27;
    using led = sam3x8e::pins::p68;
    using sck = sam3x8e::pins::p110;
    using miso = sam3x8e::pins::p108;
    using mosi = sam3x8e::pins::p109;
    using cs0 = sam3x8e::pins::p111;
    using cs1 = sam3x8e::pins::p112;
    using cs2 = sam3x8e::pins::p91;
    using cs3 = sam3x8e::pins::p92;
    using otg_vbof = sam3x8e::pins::p128;
    using otg_id = sam3x8e::pins::p129;

} // namespace llib::sam3x8e::due_core

#endif //LLIB_DUE_CORE_PINS_HPP