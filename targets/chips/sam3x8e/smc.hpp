#ifndef LLIB_SAM3X8E_SMC_HPP
#define LLIB_SAM3X8E_SMC_HPP

#include <cstdint>
#include "base.hpp"

namespace llib::sam3x8e {
    /**
     * @brief Class that inits the Static memory controller.
     * 
     * @tparam Cs the chip select pin connected to the static memory.
     */
    template <typename Cs>
    class smc {
        private:
            // A0 is used as the Lower byte select
            // that's why the A1 is a0.
            // 
            // for more information about these pins
            // check the datasheet:
            // https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-11057-32-bit-Cortex-M3-Microcontroller-SAM3X-SAM3A_Datasheet.pdf#page=385&zoom=100,37,484
            using a0 = pins::p133;
            using a1 = pins::p134;
            using a2 = pins::p135;
            using a3 = pins::p136;
            using a4 = pins::p137;
            using a5 = pins::p138;
            using a6 = pins::p139;
            using a7 = pins::p102;
            using a8 = pins::p103;
            using a9 = pins::p13;
            using a10 = pins::p14;
            using a11 = pins::p15;
            using a12 = pins::p16;
            using a13 = pins::p17;
            using a14 = pins::p18;
            using a15 = pins::p19;
            using a16 = pins::p20;
            using a17 = pins::p108;
            using a18 = pins::p109;
            using a19 = pins::p110;
            using a20 = pins::p21;
            using a21 = pins::p22;

            // data lines
            using d0 = pins::p59;
            using d1 = pins::p60;
            using d2 = pins::p116;
            using d3 = pins::p63;
            using d4 = pins::p64;
            using d5 = pins::p65;
            using d6 = pins::p66;
            using d7 = pins::p67;
            
            using d8 = pins::p117;
            using d9 = pins::p93;
            using d10 = pins::p94;
            using d11 = pins::p95;
            using d12 = pins::p96;
            using d13 = pins::p97;
            using d14 = pins::p98;
            using d15 = pins::p99;

            // other signal lines
            using lbs = pins::p132;
            using ubs = pins::p32;
            using oe = pins::p112;
            using we = pins::p100;

            // check if the pin is a chip select pin.
            // the sam3x8e only supports 4 chip selects.
            static_assert(
                detail::ebi::mode::NCS0 >= Cs::ebi::type && 
                Cs::ebi::type <= detail::ebi::mode::NCS3
            );

            // remove NCS0 from our type to get the chip select number.
            constexpr static uint32_t cs_number = static_cast<uint32_t>(Cs::ebi::type) - 
                static_cast<uint32_t>(detail::ebi::mode::NCS0);

        public:
            constexpr static uint32_t instance_id = ID_SMC;
            constexpr static uint32_t irqn = static_cast<uint32_t>(SMC_IRQn);

            static void init() {
                // enable the smc clock
                enable_clock<smc>();

                // set the periperhal of all io lines
                set_peripheral<a0, a0::address_bus::periph>();
                set_peripheral<a1, a1::address_bus::periph>();
                set_peripheral<a2, a2::address_bus::periph>();
                set_peripheral<a3, a3::address_bus::periph>();
                set_peripheral<a4, a4::address_bus::periph>();
                set_peripheral<a5, a5::address_bus::periph>();
                set_peripheral<a6, a6::address_bus::periph>();
                set_peripheral<a7, a7::address_bus::periph>();
                set_peripheral<a8, a8::address_bus::periph>();
                set_peripheral<a9, a9::address_bus::periph>();
                set_peripheral<a10, a10::address_bus::periph>();
                set_peripheral<a11, a11::address_bus::periph>();
                set_peripheral<a12, a12::address_bus::periph>();
                set_peripheral<a13, a13::address_bus::periph>();
                set_peripheral<a14, a14::address_bus::periph>();
                set_peripheral<a15, a15::address_bus::periph>();
                set_peripheral<a16, a16::address_bus::periph>();
                set_peripheral<a17, a17::address_bus::periph>();
                set_peripheral<a18, a18::address_bus::periph>();
                set_peripheral<a19, a19::address_bus::periph>();
                set_peripheral<a20, a20::address_bus::periph>();
                set_peripheral<a21, a21::address_bus::periph>();

                set_peripheral<d0, d0::data_bus::periph>();
                set_peripheral<d1, d1::data_bus::periph>();
                set_peripheral<d2, d2::data_bus::periph>();
                set_peripheral<d3, d3::data_bus::periph>();
                set_peripheral<d4, d4::data_bus::periph>();
                set_peripheral<d5, d5::data_bus::periph>();
                set_peripheral<d6, d6::data_bus::periph>();
                set_peripheral<d7, d7::data_bus::periph>();
                set_peripheral<d8, d8::data_bus::periph>();
                set_peripheral<d9, d9::data_bus::periph>();
                set_peripheral<d10, d10::data_bus::periph>();
                set_peripheral<d11, d11::data_bus::periph>();
                set_peripheral<d12, d12::data_bus::periph>();
                set_peripheral<d13, d13::data_bus::periph>();
                set_peripheral<d14, d14::data_bus::periph>();
                set_peripheral<d15, d15::data_bus::periph>();

                set_peripheral<lbs, lbs::ebi::periph>();
                set_peripheral<ubs, ubs::ebi::periph>();
                set_peripheral<oe, oe::ebi::periph>();
                set_peripheral<we, we::ebi::periph>();

                // set the chip select to the correct periph
                set_peripheral<Cs, typename Cs::ebi::periph>();

                SMC->SMC_CS_NUMBER[cs_number].SMC_SETUP = 
                    SMC_SETUP_NWE_SETUP(1) | 
                    SMC_SETUP_NCS_WR_SETUP(1) |
                    SMC_SETUP_NRD_SETUP(1) |
                    SMC_SETUP_NCS_RD_SETUP(0);

                SMC->SMC_CS_NUMBER[cs_number].SMC_PULSE = 
                    SMC_PULSE_NWE_PULSE(3) | 
                    SMC_PULSE_NCS_WR_PULSE(3) |
                    SMC_PULSE_NRD_PULSE(3) |
                    SMC_PULSE_NCS_RD_PULSE(4);

                SMC->SMC_CS_NUMBER[cs_number].SMC_CYCLE = 
                    SMC_CYCLE_NWE_CYCLE(5) |
                    SMC_CYCLE_NRD_CYCLE(5);

                // Timings for Nand flash controller (not used)
                // Memory scrambling can be enabled using this
                // register
                SMC->SMC_CS_NUMBER[cs_number].SMC_TIMINGS = 
                    0x00; // | SMC_TIMINGS_OCMS;

                SMC->SMC_CS_NUMBER[cs_number].SMC_MODE = 
                    SMC_MODE_READ_MODE_NCS_CTRL |
                    SMC_MODE_WRITE_MODE_NCS_CTRL |
                    SMC_MODE_EXNW_MODE_DISABLED |
                    SMC_MODE_DBW_BIT_16 |
                    SMC_MODE_TDF_CYCLES(0); // |
                    // SMC_MODE_TDF_MODE;             
            }

            static uint8_t * get_memory_start() {
                // return the base address of the memory location
                return (uint8_t *)(EBI_CS0_ADDR + (0x1000000 * cs_number));
            }
    };
}

#endif //LLIB_SAM3X8E_SMC_HPP