#ifndef LLIB_USB_HPP
#define LLIB_USB_HPP

#include <cstddef>
#include <stream.hpp>

#include "usb_protocol.hpp"

namespace llib::usb {
    template <typename Usb, typename Device>
    class usb {
        public:
            static void init() {
                // register the callback
                Usb::register_callback(_isr_handler);
                
                // init the usb device
                Usb::init();
            }

            /**
             * @brief Isr that handles the setup packets for all usb devices
             * 
             * @param data 
             * @param size 
             */
            static void _isr_handler(const uint8_t *data, size_t size) {
                llib::cout << "Handler called\n";
            }
    };
}

#endif