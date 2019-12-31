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

            // data lines
            using d0 = pins::p59;
            using d1 = pins::p60;
            using d2 = pins::p116;
            using d3 = pins::p63;
            using d4 = pins::p64;
            using d5 = pins::p65;
            using d6 = pins::p66;
            using d7 = pins::p67;

            // other signal lines
            using lbs = pins::p132;
            using ubs = pins::p32;
            using oe = pins::p112;
            using we = pins::p100;

            // Give a compile time error when the pin is
            // not a Chip select pin
            static_assert(static_cast<uint32_t>(Cs::ebi::type) <= 
                static_cast<uint32_t>(detail::ebi::mode::NCS3));

            // chip select lines
            // using ncs0 = sam3x8e::pins::p82;
            // using ncs1 = sam3x8e::pins::p26;
            // using ncs2 = sam3x8e::pins::p143;
            // using ncs3 = sam3x8e::pins::p68;

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

                set_peripheral<d0, d0::data_bus::periph>();
                set_peripheral<d1, d1::data_bus::periph>();
                set_peripheral<d2, d2::data_bus::periph>();
                set_peripheral<d3, d3::data_bus::periph>();
                set_peripheral<d4, d4::data_bus::periph>();
                set_peripheral<d5, d5::data_bus::periph>();
                set_peripheral<d6, d6::data_bus::periph>();
                set_peripheral<d7, d7::data_bus::periph>();

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