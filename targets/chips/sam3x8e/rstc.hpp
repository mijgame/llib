#ifndef LLIB_SAM3X8E_RSTC_HPP
#define LLIB_SAM3X8E_RSTC_HPP

#include <cstdint>
#include "base.hpp"

namespace llib::sam3x8e {
    class rst_controller {
        private:
            constexpr static uint32_t key = RSTC_CR_KEY_PASSWD;
        public:
            static void cpu_reset(){
                // reset the processor
                RSTC->RSTC_CR = key | RSTC_CR_PROCRST;
            }

            static void peripheral_reset(){
                // reset the peripherals
                RSTC->RSTC_CR = key | RSTC_CR_PERRST;
            }

            static void external_reset(){
                // asserts the nrst pin (external reset, nc on the arduino due)
                RSTC->RSTC_CR = key | RSTC_CR_EXTRST;
            }

            template<bool enable>
            static void set_user_reset(){
                // enable/disable nrst (external reset, nc on the arduino due)
                RSTC->RSTC_MR = (RSTC->RSTC_MR & ~RSTC_MR_URSTEN) | enable | key;
            }  

            template<uint8_t erstl>
            static void set_external_reset_length(){
                // sets the external reset length (nrst). time is 2^(erstl + 1)
                // configurable between 60us and 2 sec
                RSTC->RSTC_MR = (RSTC->RSTC_MR & ~RSTC_MR_ERSTL_Msk) | (erstl & 0x0F) << 8 | key;
            }
    };
}

#endif //LLIB_SAM3X8E_RSTC_HPP