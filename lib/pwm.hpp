#ifndef LLIB_PWM_HPP
#define LLIB_PWM_HPP

#include "peripheral.hpp"

//TODO Fix this

/*
namespace llib{

    template<typename Pin>
    class pin_pwm{
        public:
            constexpr static uint32_t instance_id = ID_PWM;

            using pin = Pin;

            template<unsigned int dutycycle, unsigned int frequency>
            static void init(){
                // enable pwm clock
                enable_clock<pin_pwm>();

                PWM->PWM_CLK = PWM_CLK_DIVA(1)          // Clock is selected by PREA
                             | PWM_CLK_DIVB(1)          // clock is selected by PREB
                             | PWM_CLK_PREA(0b0011)     // PREA = MCK/8
                             | PWM_CLK_PREB(0b0011);    // PREB = MCK/8

                // set channel as synchronous and set mode to mode 1(Method 2 in datasheet)
                PWM->PWM_SCM = pins::pwm_channel<Pin> | PWM_SCM_UPDM_MODE1;

                // set update period
                PWM->PWM_SCUP = PWM_SCUP_UPR(1);

                // enable channel
                PWM->PWM_ENA = pins::pwm_channel<Pin>;
                
                //

                // Trigger update of the period value
                PWM->PWM_SCUC = PWM_SCUC_UPDULOCK;
            }

            static void set(){

            }

    };
}
*/

#endif