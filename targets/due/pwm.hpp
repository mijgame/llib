#ifndef LLIB_DUE_PWM_HPP
#define LLIB_DUE_PWM_HPP

#include <math.hpp>

#include "peripheral.hpp"

namespace llib::due {
    namespace detail{
        // master clock of the sam3x8e
        constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;

        // the amount of extra pwm dividers
        constexpr static uint8_t clock_amount = 2;

        // the clocks used and what they are used for
        static inline uint16_t available_clocks[clock_amount] = {};
    }

    template<typename Pin, uint32_t PWM_channel = Pin::pwm_channel>
    class pin_pwm {
    private:
        template<typename PPin>
        static void _set_pio_b_peripheral() {
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

        static uint8_t _check_clocks(uint16_t div) {
            uint8_t unused_clocks = 0;
            // check if we have the same value in the current clocks
            for (auto i = 0; i < detail::clock_amount; i++) {
                if (detail::available_clocks[i] == 0) {
                    unused_clocks++;
                    continue;
                }
                if (detail::available_clocks[i] == div) {
                    // we have a clock that is the same
                    return i + 1;
                }
            }
            // returns a clock we can use
            return unused_clocks;
        }

        static bool _is_divider(uint32_t div) {
            for (uint8_t i = 0; i < 11; i++) {
                if (uint32_t(pow(2, i)) == div) {
                    return true;
                }
            }
            return false;
        }

        static void _setup_clock(uint8_t id, uint32_t div) {
            if (id > detail::clock_amount) {
                return;
            }
            // check if clock is already set
            if (!detail::available_clocks[id]) {
                // set clock in array
                detail::available_clocks[id] = div;
                // clear data in empty clock
                PWM->PWM_CLK &= (0xFFF << (16 * id));
                // write new clock values in the clock
                PWM->PWM_CLK |= ((div & 0xFFF) << (16 * id));
            }
        }

        template<uint32_t frequency>
        static void _set_frequency() {
            // get the nearest master clock frequency
            if (frequency > detail::variant_mck) {
                // set master clock as clock
                PWM->PWM_CH_NUM[PWM_channel].PWM_CMR = PWM_CMR_CPRE_MCK;
            }

            uint32_t divider;

            // caluculate prescaler and clock divider
            for (uint8_t clk_div = 0; clk_div < 11; ++clk_div) {
                divider = ((detail::variant_mck / frequency) / pow(2, clk_div));

                if (divider <= 0xFF) {
                    divider |= (clk_div << 8);
                    break;
                }
            }

            if (_is_divider(divider & 0xFF)) {
                // no extra clock needed so dont use one
                PWM->PWM_CH_NUM[PWM_channel].PWM_CMR = log2(divider & 0xFF);
                return;
            }

            const uint8_t c_id = _check_clocks(divider);

            if (c_id) {
                _setup_clock(c_id - 1, divider);
                // change clock of channel to new clock
                PWM->PWM_CH_NUM[PWM_channel].PWM_CMR = PWM_CMR_CPRE_CLKA + (c_id - 1);
                return;
            } else {
                // no unused clocks left so change to a mck divider only
                for (uint8_t i = 0; i < 11; i++) {
                    // try to get a divider that is below the requested frequency
                    if (uint32_t(pow(2, i)) < frequency) {
                        PWM->PWM_CH_NUM[PWM_channel].PWM_CMR = i;
                        return;
                    }
                }
                // set the lowest frequency possible
                PWM->PWM_CH_NUM[PWM_channel].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024;
            }
        }

    public:
        constexpr static uint32_t instance_id = ID_PWM;
        constexpr static uint32_t irqn = static_cast<uint32_t>(PWM_IRQn);

        template<uint32_t frequency = 82031, uint8_t dutycycle = 127>
        static void init() {
            // enable pwm clock
            enable_clock<pin_pwm>();

            // disable write protect for all groups of registers
            PWM->PWM_WPCR = PWM_WPCR_WPKEY(0x50574D) | 0xFC;

            // change pio multiplexer
            _set_pio_b_peripheral<Pin>();

            // only setup the channel when channel is not initilized yet
            if (!(PWM->PWM_ENA & (1 << PWM_channel))) {
                // set clock to pwm
                _set_frequency<frequency * 0xFF>();

                // write to cprd register since channel is still off
                PWM->PWM_CH_NUM[PWM_channel].PWM_CPRD = 0xFF;

                // write duty cycle to cdty register
                PWM->PWM_CH_NUM[PWM_channel].PWM_CDTY = dutycycle;

                // enable channel
                PWM->PWM_ENA = (1 << PWM_channel);
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