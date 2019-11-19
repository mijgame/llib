#ifndef LLIB_USB_DEVICE_HID_KEYBOARD_HPP
#define LLIB_USB_DEVICE_HID_KEYBOARD_HPP

#include <cstdint>

#include <usb/usb_device.hpp>

namespace llib::usb::device {
    class hid_keyboard {
        protected:
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

            // endpoint settings
            constexpr static uint8_t ep_ctrl_size = 8;
            constexpr static uint8_t interfaces = 1;

            constexpr static uint8_t hid_keyboard_endpoint_size = 8;

            // change pragma settings
            #pragma pack(push, 1)

            // custom struct with the configuration and the hid keyboard
            // configuration settings
            struct keyboard_descriptor {
                // default configuration
                descriptor::configuration_descriptor conf = {
                    .wTotalLength = sizeof(keyboard_descriptor),
                    .bNumInterfaces = interfaces,
                    .bConfigurationValue = 1,
                    .iConfiguration = 0,
                    .bmAttributes = device_attributes,
                    .bMaxPower = power                    
                };

                // interface configuration
                descriptor::interface_descriptor interface = {
                    .bAlternateSettings = 0,
                    .bNumEndpoints = interfaces,
                    .bInterfaceClass = 0x03,
                    .bInterfaceSubClass = 0x00,
                    .bInterfaceProtocol = 0x01,
                    .iInterface = 0x00
                };

                // hid specific configuration
                descriptor::hid::hid_descriptor hid = {
                    .bcdHID = 0x0111,
                    .bCountryCode = 0x00,
                    .bNumDescriptors = interfaces,
                    .bRDescriptorType = 0x22,
                    .wDescriptorLength = sizeof(descriptor::hid::report_descriptor)
                };

                // endpoint descriptor configuration
                descriptor::endpoint_descriptor endpoint = {
                    .bEndpointAddress = 0x01 | 0x80,
                    .bmAttributes = static_cast<uint8_t>(descriptor::transfer_type::interrupt),
                    .wMaxPacketSize = hid_keyboard_endpoint_size,
                    .bInterval = 2
                };
            };

            // restore pragma
            #pragma pack(pop)

        public:
            // device descriptor
            static inline descriptor::device_descriptor device = {
                .bcdUSB = static_cast<uint16_t>(usb_version::usb_v2_0),
                .bDeviceClass = 0,
                .bDeviceSubClass = 0,
                .bDeviceProtocol = 0,
                .bMaxPacketSize = ep_ctrl_size,
                .idVendor = vendor_id,
                .idProduct = product_id,
                .bcdDevice = ((major_version << 8) | minor_version),
                .iManufacturer = 1,
                .iProduct = 2,
                .iSerialNumber = 3,
                .bNumConfigurations = 1
            };

            // the all the other descriptors for the hid keyboard
            static inline keyboard_descriptor descriptor = {};

            // report descriptor
            static inline descriptor::hid::report_descriptor report = {};
    };
} // namespace llib::usb::device

#endif