#ifndef LLIB_USB_DEVICE_HID_KEYBOARD_HPP
#define LLIB_USB_DEVICE_HID_KEYBOARD_HPP

#include <cstdint>

#include <usb/usb_device.hpp>

namespace llib::usb::device {
    class hid_keyboard {
        public:
            // usb atmel vid
            constexpr static uint16_t vendor_id = 0x03EB;

            // product id
            constexpr static uint16_t product_id = 0x2401;

            // device version
            constexpr static uint8_t major_version = 0x01;
            constexpr static uint8_t minor_version = 0x00;

            // device power configuration (100 mA)
            constexpr static uint8_t power = 50;

            // device attributes (eg bus power, remote wakeup)
            // (1 << 7) must be set as the specification
            constexpr static uint8_t device_attributes = (1 << 7);

            // string definitions
            constexpr static uint8_t manufacture_name[] = "ATMEL ASF";
            constexpr static uint8_t product_name[] = "HID Keyboard";
            constexpr static uint8_t serial_name[] = "12EF";

            // prefered speed
            constexpr static usb_speed speed = usb_speed::full_speed;
    };
} // namespace llib::usb::device

#endif