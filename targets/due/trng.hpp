#ifndef LLIB_DUE_TRNG_HPP
#define LLIB_DUE_TRNG_HPP

#include "peripheral.hpp"

namespace llib::due {

    class trng {
    protected:
        constexpr static uint32_t trng_key = 0x524e47;

    public:
        constexpr static uint32_t instance_id = ID_TRNG;

        template<bool Interrupt = true>
        constexpr void static init() {
            // Enable clock
            enable_clock<trng>();

            // Enable trng
            TRNG->TRNG_CR = TRNG_CR_KEY(trng::trng_key) | (uint32_t(0x01) & TRNG_CR_ENABLE);

            if constexpr (Interrupt) {
                // Enable Interrupt
                TRNG->TRNG_IER = TRNG_IER_DATRDY;
            }
        }

        static void disable_interrupt() {
            TRNG->TRNG_IDR = TRNG_IDR_DATRDY;
        }

        static bool value_available() {
            // return if new data is in the TRNG_IMR register
            // this register is cleared after a read
            return TRNG->TRNG_ISR & TRNG_ISR_DATRDY;
        }

        static uint32_t get() {
            // return the 32bit random number
            return TRNG->TRNG_ODATA;
        }
    };
}

#endif // LLIB_DUE_TRNG_HPP