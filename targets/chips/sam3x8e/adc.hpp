#ifndef LLIB_SAM3X8E_ADC_HPP
#define LLIB_SAM3X8E_ADC_HPP

#include "peripheral.hpp"

namespace llib::sam3x8e {

    template<typename Pin, bool Freerunning = true>
    class pin_adc {
    public:
        constexpr static uint32_t instance_id = ID_ADC;
        constexpr static uint32_t irqn = static_cast<uint32_t>(ADC_IRQn);

        using pin = Pin;

        // true set adc to 12 bit, false to 10 bit
        template<bool LowHighRes = false>
        static void init() {
            // enable adc clock
            enable_clock<pin_adc>();

            // set the multiplexer to the correct setting
            set_peripheral<Pin, Pin::adc::periph>();

            // Remove pin from pio
            ADC->ADC_CHER = (1U << Pin::adc::id);

            // select resolution (10 - 12 bits)
            ADC->ADC_MR = static_cast<uint32_t>(!LowHighRes << 4);

            if constexpr (Freerunning) {
                // Enable freerun mode
                ADC->ADC_MR |= ADC_MR_FREERUN_ON;
            }

            // Disable interupts
            ADC->ADC_IDR = 0xFFFFFFFF;

            // Set gain to 1 (since ADC->COR diffx = 0)
            ADC->ADC_CGR = 0;

            // Set offset to 0
            ADC->ADC_COR = 0;

            if constexpr (!Freerunning) {
                // Enable data ready interrupt
                ADC->ADC_IER = ADC_IER_DRDY;
            }
        }

        static bool value_available() {
            // return if the conversion is ready
            // this register is cleared after a read
            return (ADC->ADC_ISR & ADC_ISR_DRDY);
        }

        static uint16_t get() {
            if constexpr(!Freerunning) {
                // Start analog to digital conversion
                ADC->ADC_CR = ADC_CR_START;

                // Wait until conversion is ready
                while (!value_available()) {}
            }

            // Return last 16 bits
            return ADC->ADC_CDR[Pin::adc_channel] & 0xFFFF;
        }

    };
}

#endif //LLIB_SAM3X8E_ADC_HPP