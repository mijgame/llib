#include "uotghs.hpp"

namespace llib::due::usb {
}

extern "C" {
void __UOTGHS_Handler() {
    // call the usb otg handler
    if (llib::due::usb::detail::_isr_callback) {
        // call it if it is set
        llib::due::usb::detail::_isr_callback();
    }
}    
}