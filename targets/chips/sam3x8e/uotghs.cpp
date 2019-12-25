#include "uotghs.hpp"

namespace llib::sam3x8e::usb {
}

extern "C" {
void __UOTGHS_Handler() {
    // call the usb otg handler
    if (llib::sam3x8e::usb::detail::_isr_callback) {
        // call it if it is set
        llib::sam3x8e::usb::detail::_isr_callback();
    }
}    
}