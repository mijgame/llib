#ifndef LLIB_TRNG_HPP
#define LLIB_TRNG_HPP

#include "peripheral.hpp"

namespace llib {
    namespace trng{
        struct trng{
            constexpr static uint32_t instance_id = ID_TRNG;
            constexpr static uint32_t trng_key = 0x524e47;
        };

        void init(){
            // enable clock
            enable_clock<trng>();

            // enable trng
            TRNG->TRNG_CR = TRNG_CR_KEY(trng::trng_key) | (uint32_t(0x01) & TRNG_CR_ENABLE);
        }

        template <bool interupt>
        void set_interupt(){
            if constexpr (interupt){
                // enable interupt
                TRNG->TRNG_IER = TRNG_IER_DATRDY;
            }
            else{
                // disable interupt
                TRNG->TRNG_IDR = TRNG_IDR_DATRDY;
            }
        }

        bool get_interupt(){
            // return if new data is in the TRNG_IMR register
            // this register is cleared after a read
            return TRNG->TRNG_ISR & TRNG_ISR_DATRDY;
        }

        uint32_t get(){
            // return the 32bit random number
            return TRNG->TRNG_IMR & TRNG_IMR_DATRDY;
        }
    }
}

#endif // LLIB_TRNG_HPP