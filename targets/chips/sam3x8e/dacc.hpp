#ifndef LLIB_SAM3X8E_DACC_HPP
#define LLIB_SAM3X8E_DACC_HPP

#include "pins.hpp"
#include "peripheral.hpp"

namespace llib::sam3x8e {

    template<typename Pin, uint8_t Dacc_channel = Pin::dacc_channel>
    class pin_dacc {
    public:
        constexpr static uint32_t instance_id = ID_DACC;
        constexpr static uint32_t irqn = static_cast<uint32_t>(DACC_IRQn);

        static void init() {
            // enable the clock for the peripheral
            enable_clock<pin_dacc, typename Pin::port>();

            // set pin to peripheral a if someone has used the pin as a pwm pin before
            set_peripheral<Pin, Pin::dac::periph>();

            // setup dacc
            DACC->DACC_MR = DACC_MR_TRGEN_DIS       |
                            DACC_MR_REFRESH (0x02)  |
                            DACC_MR_STARTUP_512     |
                            // DACC_MR_MAXS            | // this enables max speed mode 
                            ((Dacc_channel & 0x01) << DACC_MR_USER_SEL_Pos);

            // enable channel of dacc
            DACC->DACC_CHER = (1 << (Dacc_channel & 0x01));

            // set output parameters and limit max output current
            DACC->DACC_ACR = DACC_ACR_IBCTLCH0(0x03) |
                             DACC_ACR_IBCTLCH1(0x03) |
                             DACC_ACR_IBCTLDACCORE(0x03);

            // clear output
            DACC->DACC_CDR = 0;
        }

        static void set(uint16_t data) {
            // wait until dac is ready to receive a conversion request
            while(!(DACC->DACC_ISR & DACC_ISR_TXRDY));

            // select channel
            DACC->DACC_MR = (DACC->DACC_MR & ~DACC_MR_USER_SEL_Msk) | ((Dacc_channel & 0x01) << DACC_MR_USER_SEL_Pos);

            // set data in conversion register
            DACC->DACC_CDR = data & 0xFFF;
        }

    };
}

#endif //LLIB_SAM3X8E_DACC_HPP