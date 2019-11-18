#ifndef LLIB_DUE_UOTGHS_HPP
#define LLIB_DUE_UOTGHS_HPP

#include <cstddef>

#include "pins.hpp"
#include "peripheral.hpp"

namespace llib::due::usb {
    class uotghs {
        private:
            using interrupt_callback = void (*)(const uint8_t* data, size_t size);

            // isr handler
            static inline interrupt_callback isr = nullptr;

            // init the usb hardware
            static void init_usb();

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
