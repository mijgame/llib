#ifndef LLIB_SAM3X8E_UOTGHS_HPP
#define LLIB_SAM3X8E_UOTGHS_HPP

#include "pins.hpp"
#include "peripheral.hpp"

namespace llib::sam3x8e{
    // arduino due Usb On-The-Go Interface (UOTGHS)
    // UOTGHS pin: PB11 UOTGID pullups needed when enabled
    // UOTGHS pin: PB10 UOTGVBOF
    // enable clock in pmc
    // before disabling the clock disable uotghs
    // 
    // normal mode (spdconf = 1) avaialable modes: (high, full and low speed)
    // low power mode (spdconf = 0) available modes: (full and low speed)
    //
    // normal mode:
    //      enable upll 480mhz
    //      wait for the upll 480mhz to be considered as locked by pmc
    //      enable the uotghs peripheral clock(PMC_PCER)
    //      the uotghs will use USB_480M clock
    //
    // low power mode:
    //      USB_48M must be set to 48Mhz, select either the PLLA or the UPLL
    //      (previously set to ON), and program the PMC_USB register (source selection and divider)
    //      enable the uotgck bit (PMC_SCER)
    //      enable the uotghs peripheral clock(PMC_PCER)
    //      put the uotghs in low poer mode (spdconf)
    //
    // uotgid has access to each Pipe/endpoint FIFO through its reserved 32KB address space
    // the application can access a 64KB buffer linearly or fixedly as the dpram address increment is
    // fully handled by hardware
    // byte, half-word and word access is supported
    // data should be accessed in a big-endian way
    // disabling the uotghs(by writing a zero to the uotghs_ctrl.usbe bit) does not reset the dpram
    // has automatic host/device detection by the id pin
    // 
    class uotghs{
        private:        

        public:
            constexpr static uint32_t instance_id = ID_UOTGHS;     

    };
}

#endif
