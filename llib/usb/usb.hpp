#ifndef LLIB_USB_HPP
#define LLIB_USB_HPP

#include <cstddef>
#include <stream.hpp>

#include "usb_protocol.hpp"

namespace llib::usb {
    template <typename Usb, typename Device>
    class usb {
        protected:
            // device descriptor
            static inline llib::usb::descriptor::device_descriptor device = {
                .bcdUSB = 0x0200,
                .bDeviceClass = 0,
                .bDeviceSubClass = 0,
                .bDeviceProtocol = 0,
                .bMaxPacketSize = Device::ep_ctrl_size,
                .idVendor = Device::vendor_id,
                .idProduct = Device::product_id,
                .bcdDevice = ((Device::major_version << 8) | Device::minor_version),
                .iManufacturer = 1,
                .iProduct = 2,
                .iSerialNumber = 3,
                .bNumConfigurations = 1
            };

            // the class specific struct should be bound with this (todo)
            static inline llib::usb::descriptor::configuration_descriptor config = {
                // .conf.wTotalLength         = sizeof(configuration_descriptor + ?),
                .bNumInterfaces       = Device::interfaces,
                .bConfigurationValue  = 1,
                .iConfiguration       = 0,
                .bmAttributes         = Device::device_attributes,
                .bMaxPower            = Device::power,                
            };

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