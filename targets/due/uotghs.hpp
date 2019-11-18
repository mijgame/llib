#ifndef LLIB_DUE_UOTGHS_HPP
#define LLIB_DUE_UOTGHS_HPP

#include <cstddef>

#include <usb/usb_protocol.hpp>

#include "pins.hpp"
#include "peripheral.hpp"

namespace llib::due::usb {
    class uotghs {
        private:
            using interrupt_callback = void (*)(const uint8_t* data, size_t size);

            // otg ram location
            static inline uint8_t *const _otg_ram = (reinterpret_cast<uint8_t *>(UOTGHS_RAM_ADDR));

            // the size of the ram
            constexpr static uint32_t _otg_ram_size = 0x8000;

            // maximum amount of endpoints available
            constexpr static uint8_t max_endpoints = 10;

            // isr handler
            static inline interrupt_callback isr = nullptr;

            // init the usb hardware
            static void init_usb();

            // decode the setup packet
            static bool decode_setup(const llib::usb::setup::setup_packet &p);

            constexpr static uint32_t get_byte_count(const uint32_t s) {
                return (s & UOTGHS_DEVEPTISR_BYCT_Msk) >> UOTGHS_DEVEPTISR_BYCT_Pos;
            }

            template<uint32_t Endpoint>
            constexpr static uint8_t* get_fifo() {
                // check if the endpoint is below the max amount
                static_assert(Endpoint < max_endpoints);

                return _otg_ram + (_otg_ram_size * Endpoint);
            }            

        public:
            constexpr static uint32_t instance_id = ID_UOTGHS;
            constexpr static uint32_t irqn = static_cast<uint32_t>(UOTGHS_IRQn);

            static void init() {
                if (!isr) {
                    // callback not registered return
                    return;
                }

                init_usb();
            }

            static void register_callback(interrupt_callback interrupt) {
                isr = interrupt;
            }

            static void __isr_handler();

    };
}

extern "C" {
void __UOTGHS_Handler();
}

#endif
