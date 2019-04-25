#ifndef LLIB_DUE_PINS_HPP
#define LLIB_DUE_PINS_HPP

#include "pio.hpp"
#include "tc.hpp"
#include <type_traits>

namespace llib::due {
    namespace pins {
        struct d0 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 8;
            constexpr static uint32_t pwm_channel = 0;
        };

        struct d1 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 9;
            constexpr static uint32_t pwm_channel = 3;
        };

        struct d2 {
            using port = piob;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_0; 
            using timer_pin = tc::tioa; // TC0, TIOA0
            constexpr static uint32_t number = 25;            
        };

        struct d3 {
            using port = pioc;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_7;
            using timer_pin = tc::tioa; // TC2, TIOA7
            constexpr static uint32_t number = 28;
        };

        struct d4 {
            using port = pioc;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_6;
            using timer_pin = tc::tiob; // TC2, TIOB6
            constexpr static uint32_t number = 26;
        };

        struct d5 {
            using port = pioc;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_6;
            using timer_pin = tc::tioa; // TC2, TIOA6
            constexpr static uint32_t number = 25;
        };

        struct d6 {
            using port = pioc;
            constexpr static uint32_t number = 24;
            constexpr static uint32_t pwm_channel = 7;
        };

        struct d7 {
            using port = pioc;
            constexpr static uint32_t number = 23;
            constexpr static uint32_t pwm_channel = 6;
        };

        struct d8 {
            using port = pioc;
            constexpr static uint32_t number = 22;
            constexpr static uint32_t pwm_channel = 5;
        };

        struct d9 {
            using port = pioc;
            constexpr static uint32_t number = 21;
            constexpr static uint32_t pwm_channel = 4;
        };

        struct d10 {
            using port = pioc;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_7;
            using timer_pin = tc::tiob; // TC2, TIOB7      
            constexpr static uint32_t number = 29;
        };

        struct d11 {
            using port = piod;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_8;
            using timer_pin = tc::tioa; // TC2, TIOA8        
            constexpr static uint32_t number = 7;
        };

        struct d12 {
            using port = piod;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_8;
            using timer_pin = tc::tiob; // TC2, TIOB8
            constexpr static uint32_t number = 8;
        };

        struct d13 {
            using port = piob;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_0;
            using timer_pin = tc::tiob; // TC0, TIOB0
            constexpr static uint32_t number = 27;
        };

        struct d14 {
            using port = piod;
            using periph = pio_periph_b;
            constexpr static uint32_t number = 4;
        };

        struct d15 {
            using port = piod;
            using periph = pio_periph_b;
            constexpr static uint32_t number = 5;
        };

        struct d16 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 13;
            constexpr static uint32_t pwm_channel = 2;
        };

        struct d17 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 12;
            constexpr static uint32_t pwm_channel = 1;
        };

        struct d18 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 11;
        };

        struct d19 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 10;
        };

        struct d20 {
            using port = piob;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 12;
            constexpr static uint32_t pwm_channel = 0;
        };

        struct d21 {
            using port = piob;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 13;
            constexpr static uint32_t pwm_channel = 1;
        };

        struct d22 {
            using port = piob;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_0;
            using timer_pin = tc::tclk; // TC0, TCLK0
            constexpr static uint32_t number = 26;
        };

        struct d23 {
            using port = pioa;
            constexpr static uint32_t number = 14;
        };

        struct d24 {
            using port = pioa;
            constexpr static uint32_t number = 15;
        };

        struct d25 {
            using port = piod;
            constexpr static uint32_t number = 0;
        };

        struct d26 {
            using port = piod;
            constexpr static uint32_t number = 1;
        };

        struct d27 {
            using port = piod;
            constexpr static uint32_t number = 2;
            constexpr static uint32_t pwm_channel = 0;
        };

        struct d28 {
            using port = piod;
            constexpr static uint32_t number = 3;
            constexpr static uint32_t pwm_channel = 0;
        };

        struct d29 {
            using port = piod;
            constexpr static uint32_t number = 6;
            constexpr static uint32_t pwm_channel = 2;
        };

        struct d30 {
            using port = piod;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_8;
            using timer_pin = tc::tclk; // TC2, TCLK8
            constexpr static uint32_t number = 9;
        };

        struct d31 {
            using port = pioa;
            using periph = pio_periph_a;
            using timer_channel = tc::channel_2;
            using timer_pin = tc::tclk; // TC0, TCLK2
            constexpr static uint32_t number = 7;
        };

        struct d32 {
            using port = piod;
            constexpr static uint32_t number = 10;
        };

        struct d33 {
            using port = pioc;
            constexpr static uint32_t number = 1;
        };

        struct d34 {
            using port = pioc;
            constexpr static uint32_t number = 2;
            constexpr static uint32_t pwm_channel = 0;
        };

        struct d35 {
            using port = pioc;
            constexpr static uint32_t number = 3;
            constexpr static uint32_t pwm_channel = 0;
        };

        struct d36 {
            using port = pioc;
            constexpr static uint32_t number = 4;
            constexpr static uint32_t pwm_channel = 1;
        };

        struct d37 {
            using port = pioc;
            constexpr static uint32_t number = 5;
            constexpr static uint32_t pwm_channel = 1;
        };

        struct d38 {
            using port = pioc;
            constexpr static uint32_t number = 6;
            constexpr static uint32_t pwm_channel = 2;
        };

        struct d39 {
            using port = pioc;
            constexpr static uint32_t number = 7;
            constexpr static uint32_t pwm_channel = 2;
        };

        struct d40 {
            using port = pioc;
            constexpr static uint32_t number = 8;
            constexpr static uint32_t pwm_channel = 3;
        };

        struct d41 {
            using port = pioc;
            constexpr static uint32_t number = 9;
            constexpr static uint32_t pwm_channel = 3;
        };

        struct d42 {
            using port = pioa;
            constexpr static uint32_t number = 19;
            constexpr static uint32_t pwm_channel = 1;
        };

        struct d43 {
            using port = pioa;
            constexpr static uint32_t number = 20;
            constexpr static uint32_t pwm_channel = 2;
        };

        struct d44 {
            using port = pioc;
            constexpr static uint32_t number = 19;
            constexpr static uint32_t pwm_channel = 5;
        };

        struct d45 {
            using port = pioc;
            constexpr static uint32_t number = 18;
            constexpr static uint32_t pwm_channel = 6;
        };

        struct d46 {
            using port = pioc;
            constexpr static uint32_t number = 17;
        };

        struct d47 {
            using port = pioc;
            constexpr static uint32_t number = 16;
        };

        struct d48 {
            using port = pioc;
            constexpr static uint32_t number = 15;
        };

        struct d49 {
            using port = pioc;
            constexpr static uint32_t number = 14;
        };

        struct d50 {
            using port = pioc;
            constexpr static uint32_t number = 13;
        };

        struct d51 {
            using port = pioc;
            constexpr static uint32_t number = 12;
        };

        struct d52 {
            using port = piob;
            using periph = pio_periph_b;
            constexpr static uint32_t number = 21;
            constexpr static uint32_t spi_number = 2;
        };

        struct d53 {
            using port = piob;
            constexpr static uint32_t number = 14;
            constexpr static uint32_t pwm_channel = 2;
        };

        struct a0 {
            using port = pioa;
            constexpr static uint32_t number = 16;
            constexpr static uint32_t adc_channel = 7;
        };

        struct a1 {
            using port = pioa;
            constexpr static uint32_t number = 24;
            constexpr static uint32_t adc_channel = 6;
        };

        struct a2 {
            using port = pioa;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_4;
            using timer_pin = tc::tclk; // TC1, TCLK4
            constexpr static uint32_t number = 23;
            constexpr static uint32_t adc_channel = 5;
        };

        struct a3 {
            using port = pioa;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_3;
            using timer_pin = tc::tclk; // TC1, TCLK3
            constexpr static uint32_t number = 22;
            constexpr static uint32_t adc_channel = 4;
        };

        struct a4 {
            using port = pioa;
            using periph = pio_periph_a;
            using timer_channel = tc::channel_2;
            using timer_pin = tc::tiob; // TC0, TIOB2
            constexpr static uint32_t number = 6;
            constexpr static uint32_t adc_channel = 3;
        };

        struct a5 {
            using port = pioa;
            using periph = pio_periph_a;
            using timer_channel = tc::channel_1; 
            using timer_pin = tc::tclk; // TC0, TCLK1
            constexpr static uint32_t number = 4;
            constexpr static uint32_t adc_channel = 2;
        };

        struct a6 {
            using port = pioa;
            using periph = pio_periph_a;
            using timer_channel = tc::channel_1;
            using timer_pin = tc::tiob; // TC0, TIOB1
            constexpr static uint32_t number = 3;
            constexpr static uint32_t adc_channel = 1;
            constexpr static uint32_t pwm_channel = 1;
        };

        struct a7 {
            using port = pioa;
            using periph = pio_periph_a;
            using timer_channel = tc::channel_1; 
            using timer_pin = tc::tioa; // TC0, TIOA1
            constexpr static uint32_t number = 2;
            constexpr static uint32_t adc_channel = 0;
        };

        struct a8 {
            using port = piob;
            constexpr static uint32_t number = 17;
            constexpr static uint32_t adc_channel = 10;
            constexpr static uint32_t pwm_channel = 1;
        };

        struct a9 {
            using port = piob;
            constexpr static uint32_t number = 18;
            constexpr static uint32_t adc_channel = 11;
            constexpr static uint32_t pwm_channel = 2;
        };

        struct a10 {
            using port = piob;
            constexpr static uint32_t number = 19;
            constexpr static uint32_t adc_channel = 12;
            constexpr static uint32_t pwm_channel = 3;
        };

        struct a11 {
            using port = piob;
            using periph = pio_periph_b;
            constexpr static uint32_t number = 20;
            constexpr static uint32_t adc_channel = 13;
            constexpr static uint32_t spi_number = 1;
        };

        struct dac0 {
            using port = piob;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 15;
            constexpr static uint32_t pwm_channel = 3;
            constexpr static uint32_t dacc_channel = 0;
        };

        struct dac1 {
            using port = piob;
            using periph = pio_periph_a;
            using timer_channel = tc::channel_5;
            using timer_pin = tc::tclk; // TC1, TCLK5
            constexpr static uint32_t number = 16;
            constexpr static uint32_t pwm_channel = 0;
            constexpr static uint32_t dacc_channel = 1;
        };

        struct canrx {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 1;
        };

        struct cantx {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 0;
        };

        struct scl {
            using port = piob;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 13;
        };

        struct sda {
            using port = piob;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 12;
        };

        struct scl1 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 18;
        };

        struct sda1 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 17;
        };

        struct tx {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 9;
        };

        struct rx {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 8;
        };

        struct led {
            using port = piob;
            using periph = pio_periph_b;
            using timer_channel = tc::channel_0; 
            using timer_pin = tc::tiob; // TC0, TIOB0
            constexpr static uint32_t number = 27;
        };

        struct sck {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 27;
        };

        struct miso {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 25;
        };

        struct mosi {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 26;
        };

        struct cs0 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 28;
            constexpr static uint32_t spi_number = 0;
        };

        struct cs1 {
            using port = pioa;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 29;
            constexpr static uint32_t spi_number = 1;
        };    
        
        struct cs2 {
            using port = piob;
            using periph = pio_periph_b;
            constexpr static uint32_t number = 20;
            constexpr static uint32_t adc_channel = 13;
            constexpr static uint32_t spi_number = 1;            
        };

        struct cs3 {
            using port = piob;
            using periph = pio_periph_b;
            constexpr static uint32_t number = 21;
            constexpr static uint32_t spi_number = 2;
        };

        struct uotg_vbof{
            using port = piob;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 10;
        };             

        struct uotg_id{
            using port = piob;
            using periph = pio_periph_a;
            constexpr static uint32_t number = 11;
        };

        template<typename Pin>
        constexpr uint32_t mask = 1U << Pin::number;

        template<typename Pin>
        constexpr uint32_t adc_channel = 1U << Pin::adc_channel;

        template<typename Pin>
        constexpr uint32_t pwm_channel = 1U << Pin::pwm_channel;

        template<typename Pin>
        const Pio *port = nullptr;

        template<>
        Pio *const port<pioa> = PIOA;

        template<>
        Pio *const port<piob> = PIOB;

        template<>
        Pio *const port<pioc> = PIOC;

        template<>
        Pio *const port<piod> = PIOD;
    }

    template<typename Pin>
    class pin_in {
    public:
        using pin = Pin;

        constexpr static void init() {
            enable_clock<typename Pin::port>();
            pins::port<typename Pin::port>->PIO_ODR = pins::mask<Pin>;
        }

        constexpr static bool get() {
            return (pins::port<typename Pin::port>->PIO_PDSR & pins::mask<Pin>) != 0;
        }

        constexpr static void pullup_enable() {
            pins::port<typename Pin::port>->PIO_PUER = pins::mask<Pin>;
        }

        constexpr static void pullup_disable() {
            pins::port<typename Pin::port>->PIO_PUDR = pins::mask<Pin>;
        }
    };

    template<typename Pin>
    class pin_out {
    public:
        using pin = Pin;

        constexpr static void init() {
            enable_clock<typename Pin::port>();
            pins::port<typename Pin::port>->PIO_OER = pins::mask<Pin>;
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<typename Pin::port>->PIO_SODR = pins::mask<Pin>;
            } else {
                pins::port<typename Pin::port>->PIO_CODR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            (val
             ? pins::port<typename Pin::port>->PIO_SODR
             : pins::port<typename Pin::port>->PIO_CODR
            ) = pins::mask<Pin>;
        }
    };

    template<typename Pin>
    class pin_in_out {
    public:
        using pin = Pin;

        constexpr static bool get() {
            pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            return pin_in<Pin>::get();
        }

        constexpr static void pullup_enable() {
            pin_in<Pin>::pullup_enable();
        }

        constexpr static void pullup_disable() {
            pin_in<Pin>::pullup_disable();
        }

        template<bool val>
        constexpr static void set() {
            pins::port<Pin>->PIO_OER = pins::mask<Pin>;
            pin_out<Pin>::template set<val>();
        }

        constexpr static void set(const bool val) {
            pins::port<Pin>->PIO_OER = pins::mask<Pin>;
            pin_out<Pin>::set(val);
        }
    };

    template<typename Pin>
    class pin_oc {
    public:
        using pin = Pin;

        constexpr static void init() {
            enable_clock<typename Pin::port>();
        }

        constexpr static bool get() {
            return pin_in<Pin>::get();
        }

        template<bool val>
        constexpr static void set() {
            if constexpr (val) {
                pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            } else {
                pins::port<Pin>->PIO_OER = pins::mask<Pin>;
                pins::port<Pin>->PIO_CODR = pins::mask<Pin>;
            }
        }

        constexpr static void set(const bool val) {
            if (val) {
                pins::port<Pin>->PIO_ODR = pins::mask<Pin>;
            } else {
                pins::port<Pin>->PIO_OER = pins::mask<Pin>;
                pins::port<Pin>->PIO_CODR = pins::mask<Pin>;
            }
        }
    };

    template<typename Pin>
    void set_peripheral() {
        // Disable interrupts on the pin
        pins::port<typename Pin::port>->PIO_IDR = pins::mask<Pin>;
        uint32_t t = pins::port<typename Pin::port>->PIO_ABSR;

        // Change pio multiplexer
        if constexpr (std::is_same_v<typename Pin::periph, pio_periph_a>) {
            pins::port<typename Pin::port>->PIO_ABSR &= (~pins::mask<Pin> & t);
        } else if constexpr (std::is_same_v<typename Pin::periph, pio_periph_b>) {
            pins::port<typename Pin::port>->PIO_ABSR = (pins::mask<Pin> | t);
        }

        // disable pull ups
        pins::port<typename Pin::port>->PIO_PUDR = pins::mask<Pin>;

        // remove pin from pio controller
        pins::port<typename Pin::port>->PIO_PDR = pins::mask<Pin>;
    }
}

#endif //LLIB_DUE_PINS_HPP
