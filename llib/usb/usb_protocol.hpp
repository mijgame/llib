#ifndef LLIB_USB_PROTOCOL_HPP
#define LLIB_USB_PROTOCOL_HPP

#include <cstdint>

// Push the current pack to the stack and set the pack to 1
// as all these structs have specific sizes
#pragma pack(push, 1)

/**
 * Definitions are taken from:
 * https://www.beyondlogic.org/usbnutshell/
 * 
 */
namespace llib::usb::setup {
    /**
     * More information can be found here:
     * https://www.beyondlogic.org/usbnutshell/usb6.shtml
     * 
     */

    /**
     * USB request data transfer direction
     * (bmRequestType)
     * 
     */
    enum class direction {
        host_to_device = 0,
        device_to_host = 1
    };

    /**
     * Usb request types
     * (bmRequestType)
     * 
     */
    enum class request_type {
        standard = 0,
        uclass = 1,
        vendor = 2,
        reserved = 3
    };

    /**
     * USB recipient codes
     * (bmRequestType)
     * 
     */
    enum class recipient_code {
        device = 0,
        interface = 1,
        endpoint = 2,
        other = 3,
        reserved
    };

    /**
     * Standard USB requests
     * (bRequest)
     * 
     */
    enum class device_request {
        // wValue = zero
        // wIndex = zero
        // wLength = 2
        // data = device status
        get_status = 0x00,

        // wValue = feature selector
        // wIndex = zero
        // wLength = zero
        // data = none
        clear_feature = 0x01,

        // wValue = feature selector
        // wIndex = zero
        // wLength = zero
        // data = none
        set_feature = 0x03,

        // wValue = device address
        // wIndex = zero
        // wLength = zero
        // data = none
        set_address = 0x05,

        // wValue = descriptor type & index
        // wIndex = zero or language id
        // wLength = descriptor length
        // data = descriptor
        get_descriptor = 0x06,

        // wValue = descriptor type & index
        // wIndex = zero or language id
        // wLength = descriptor length
        // data = descriptor
        set_descriptor = 0x07,

        // wValue = zero
        // wIndex = zero
        // wLength = 1
        // data = configuration value
        get_configuration = 0x08,

        // wValue = configuration value
        // wIndex = zero
        // wLength = zero
        // data = none
        set_configuration = 0x09
    };

    /**
     * interface USB requests
     * (bRequest)
     * 
     * wIndex is normally used to specify the referring interface for 
     * requests directed at the interface. Its format is shown below.
     * 
     * wIndex:
     * b[0..7] = interface number
     * b[8..15] = reserved
     * 
     */
    enum class interface_request {
        // wValue = zero
        // wIndex = interface
        // wLength = 2
        // data = interface status
        get_status = 0x00,

        // wValue = feature selector
        // wIndex = interface
        // wLength = zero
        // data = none
        clear_feature = 0x01,

        // wValue = feature selector
        // wIndex = interface
        // wLength = zero
        // data = none
        set_feature = 0x03,

        // wValue = zero
        // wIndex = interface
        // wLength = 1
        // data = alternate interface
        get_interface = 0x0A,

        // wValue = alternative setting
        // wIndex = interface
        // wLength = zero
        // data = none
        set_interface = 0x11
    };

    /**
     * endpoint USB requests
     * (bRequest)
     * 
     * The wIndex field is normally used to specify the referring endpoint 
     * and direction for requests directed to an endpoint. Its format is 
     * shown below.
     * 
     * windex:
     * b[0..3] = endpoint number
     * b[4..6] = reserved
     * b[7] = dir
     * b[8..15] = reserved
     * 
     */
    enum class endpoint_request {
        // wValue = zero
        // wIndex = endpoint
        // wLength = 2
        // data = endpoint status
        get_status = 0x00,

        // wValue = feature selector
        // wIndex = endpoint
        // wLength = zero
        // data = none
        clear_feature = 0x01,

        // wValue = feature selector
        // wIndex = endpoint
        // wLength = zero
        // data = none
        set_feature = 0x03,

        // wValue = zero
        // wIndex = endpoint
        // wLength = 2
        // data = framenumber
        synch_frame = 0x12
    };

    /**
     * 8 byte long USB setup packet
     * 
     */
    struct setup_packet {
        // b[0..4] = Recipient
        // 0x0 = device
        // 0x1 = interface
        // 0x2 = endpoint
        // 0x3 = Other
        // 0x4..31 = reserved
        // b[5..6] = Type
        // 0x0 = standard
        // 0x1 = interface
        // 0x2 = vendor
        // 0x3 = reserved
        // b[7] = data phase transfer
        // 0x0 = host to device
        // 0x1 = device to host
        uint8_t bmRequestType;

        // b[0..7] request
        uint8_t bRequest;

        // b[0..16] value
        uint16_t wValue;

        // b[0..16] index or offset
        uint16_t wIndex;

        // b[0..16] Count
        uint16_t wLength;
    };

    constexpr recipient_code get_recipient_code(const uint8_t bmRequestType) {
        return static_cast<recipient_code>(bmRequestType & 0xF);
    }

    constexpr request_type get_request_type(const uint8_t bmRequestType) {
        return static_cast<request_type>((bmRequestType >> 5) & 0x3);
    }

    constexpr direction get_direction(const uint8_t bmRequestType) {
        return static_cast<direction>(bmRequestType >> 7);
    }        
}

namespace llib::usb::descriptor {
    /**
     * More information can be found here:
     * https://www.beyondlogic.org/usbnutshell/usb5.shtml
     * 
     */

    /**
     * Header of all descriptors
     * 
     */
    struct _header {
        // size of descriptor in bytes
        uint8_t bLenght;

        // descriptorType
        uint8_t bDescriptionType;
    };

    /**
     * Transfer types
     * (bmAttributes)
     * 
     */
    enum class transfer_type {
        control = 0,
        isochronous = 1,
        bulk = 2,
        interrupt = 3
    };

    /**
     * Synchronisation types
     * (bmAttributes)
     * 
     */
    enum class synchronisation_type {
        no_synchronisation = 0,
        asynchronous = 1,
        adaptive = 2,
        synchronous = 3
    };

    /**
     * Usage types
     * (bmAttributes)
     * 
     */
    enum class usage_type {
        data_endpoint = 0,
        feedback_endpoint = 1,
        explicit_feedback_data_endpoint = 2,
        reserved = 3
    };

    /**
     * The device descriptor of a USB device represents the entire device.
     * As a result a USB device can only have one device descriptor. It 
     * specifies some basic, yet important information about the device 
     * such as the supported USB version, maximum packet size, vendor and
     * product ids and the number of possible configurations the device can
     * have.
     * 
     */
    struct device_descriptor {
        // header of descriptor
        const _header header{sizeof(device_descriptor), 0x01};

        // usb specification number wich device compies to
        uint16_t bcdUSB;

        // class code
        uint8_t bDeviceClass;

        // subclass code
        uint8_t bDeviceSubClass;

        // protocol code
        uint8_t bDeviceProtocol;

        // maximum packet size for zero endpoint(control).
        // valid sizes are (8, 16, 32, 64)
        uint8_t bMaxPacketSize;

        // vendor id
        uint16_t idVendor;

        // product id
        uint16_t idProduct;

        // device release number
        uint16_t bcdDevice;

        // index of manufacturer string descriptor
        uint8_t iManufacturer;

        // index of product string descriptor
        uint8_t iProduct;

        // index of serial number string descriptor
        uint8_t iSerialNumber;

        // number of possible configurations
        uint8_t bNumConfigurations;
    };

    /**
     * Descriptor for a configuration.
     * 
     */
    struct configuration_descriptor {
        // header of descriptor
        const _header header{sizeof(configuration_descriptor), 0x02};

        // total length in bytes of data returned
        uint16_t wTotalLength;

        // number of interfaces
        uint8_t bNumInterfaces;

        // value to use as an argument to select this configuration
        uint8_t bConfigurationValue;

        // index of string descriptor describing this configuration
        uint8_t iConfiguration;

        // b[0..4] = reserved, set to 0
        // b[5] = remote wakeup
        // b[6] = self powered
        // b[7] = reserved, set to 1 (USB 1.0 Bus powered)
        uint8_t bmAttributes;

        // maximum power consumption in 2mA units
        uint8_t bMaxPower;
    };

    /**
     * Descriptor for a string. This provides human readable information 
     * and is optional. If they are not used, any string index fields of
     * descriptors must be set to zero indicating there is no string 
     * descriptor available.
     * 
     * All strings are encoded in the unicode format and products can be 
     * made to support multiple languages.
     * 
     * @tparam Size the size of the string
     * 
     */
    template<uint32_t Size>
    struct string_descriptor {
        // header of descriptor
        const _header header{sizeof(string_descriptor), 0x03};

        // unicode encoded string
        uint16_t bString[Size];
    };

    /**
     * Descriptor what languages are supported by the device. List with 
     * id's can be found here:
     * http://www.usb.org/developers/data/USB_LANGIDs.pdf
     * 
     * This descriptor has the same bDescriptionType as the string 
     * descriptor.
     * 
     */
    struct language_descriptor {
        // header of descriptor
        const _header header{sizeof(language_descriptor), 0x03};

        // supported language codes (eg 0x0409 English - United States)
        uint16_t wLANGID[1] = {0x0409};
    };

    /**
     * A interface descriptor can be seen as a header or grouping of the 
     * endpoints into a functional group performing a single feature of the
     * device. 
     * 
     */
    struct interface_descriptor {
        // header of descriptor
        const _header header{sizeof(interface_descriptor), 0x04};

        // number of interface
        uint8_t bInterfaceNumber;

        // value used to select alternative setting
        uint8_t bAlternateSetting;

        // number of endpoints used for this interface
        uint8_t bNumEndpoints;

        // class code
        uint8_t bInterfaceClass;

        // subclass code
        uint8_t bInterfaceSubClass;

        // protocol code
        uint8_t bInterfaceProtocol;

        // index of string descirptor describing this interface
        uint8_t iInterface;
    };

    /**
     * Descriptor for an endpoint. Endpoint zero is always assumed to be a 
     * control endpoint and is configured before any descriptors are even 
     * requested. The host will use the information returned from these 
     * descriptors to determine the bandwidth requirements of the bus.
     * 
     */
    struct endpoint_descriptor {
        // header of descriptor
        const _header header{sizeof(endpoint_descriptor), 0x05};

        // endpoint address
        // b[0..3] = endpoint number
        // b[4..6] = reserved, set to 0
        // b[7] = direction (ignored for control endpoints)
        // 0x0 = out
        // 0x1 = in 
        uint8_t bEndpointAddress;

        // b[0..1] = Transfer type
        // 0x0 = Control
        // 0x1 = Isochronous
        // 0x2 = Bulk
        // 0x3 = Interrupt
        // b[2..3] = Synchronisation type 
        // 0x0 = no synchronisation
        // 0x1 = asynchronous
        // 0x2 = adaptive
        // 0x3 = synchronous
        // b[4..5] = Usage type
        // 0x0 = data endpoint
        // 0x1 = feedback endpoint
        // 0x2 = explicit feedback data type
        // 0x3 = reserved
        // b[2..7] = reserved if Isochronous endpoint
        uint8_t bmAttributes;

        // maximum packet size this endpoint is capable of sending or 
        // receiving
        uint16_t wMaxPacketSize;

        // interval for polling endpoint data transfers. Value in frame 
        // counts. Ignored for bulk and control endpoints. Isochronous
        // must equal 1 and field may range from 1 to 255 for interrupt
        // endpoints
        uint8_t bInterval;
    };
}

// release the old pack so the rest of the structs are not 
// affected by the pack(1)
#pragma pack(pop)

#endif