#ifndef LLIB_DUE_PWM_HPP
#define LLIB_DUE_PWM_HPP

#include "peripheral.hpp"

//TODO Fix this


namespace llib::due {
    template<typename Pin, uint32_t PWM_channel = Pin::pwm_channel>
    class pin_pwm{
        private:
            template <typename PPin>
            struct pin_status{
                static inline  bool initialized = false;
            };

            template<typename PPin>
            static void set_pio_b_peripheral(){
                pins::port<typename Pin::port>->PIO_IDR = pins::mask<Pin>;
                uint32_t t = pins::port<typename Pin::port>->PIO_ABSR;

                // Change pio multiplexer to pio b
                pins::port<typename Pin::port>->PIO_ABSR = (pins::mask<Pin> | t);

                // Disable interrupts on the pin(s)
                pins::port<typename Pin::port>->PIO_IDR = pins::mask<Pin>;

                // disable pull ups
                pins::port<typename Pin::port>->PIO_PUDR = pins::mask<Pin>;

                // remove pin from pio controller
                pins::port<typename Pin::port>->PIO_PDR = pins::mask<Pin>;
            }

        public:
            constexpr static uint32_t instance_id = ID_PWM;
            constexpr static uint32_t irqn = static_cast<uint32_t>(PWM_IRQn);

            template<unsigned int dutycycle = 127, unsigned int frequency = 10000>
            static void init(){
                // enable pwm clock
                enable_clock<pin_pwm>();

                // disable write protect for all groups of registers
                PWM->PWM_WPCR = PWM_WPCR_WPKEY(0x50574D) | 0xFC;

                PWM->PWM_CLK = PWM_CLK_DIVA(1)          // Clock is selected by PREA
                            | PWM_CLK_DIVB(1)          // clock is selected by PREB
                            | PWM_CLK_PREA(0b0011)     // PREA = MCK/8
                            | PWM_CLK_PREB(0b0011);    // PREB = MCK/8

                if(!pin_status<Pin>::initialized){
                    // change pio multiplexer
                    set_pio_b_peripheral<Pin>();

                    // set clock to pwm clock a
                    PWM->PWM_CH_NUM[PWM_channel].PWM_CMR = PWM_CMR_CPRE_CLKA;

                    // write to cprd register sinds channel is still off
                    PWM->PWM_CH_NUM[PWM_channel].PWM_CPRD = 0xFF;

                    // write duty cycle to cdty register
                    PWM->PWM_CH_NUM[PWM_channel].PWM_CDTY = dutycycle;

                    // enable channel
                    PWM->PWM_ENA = (1 << PWM_channel);

                    // init pin complete
                    pin_status<Pin>::initialized = true;
                }

                // set dutycycle in update register
                PWM->PWM_CH_NUM[PWM_channel].PWM_CDTYUPD = dutycycle;
            }

            template<uint8_t dutycycle>
            constexpr static void set() {
                PWM->PWM_CH_NUM[PWM_channel].PWM_CDTYUPD = dutycycle;
            }

            constexpr static void set(const uint8_t dutycycle) {
                PWM->PWM_CH_NUM[PWM_channel].PWM_CDTYUPD = dutycycle;
            }  
    };
}


#endif //LLIB_DUE_PWM_HPP