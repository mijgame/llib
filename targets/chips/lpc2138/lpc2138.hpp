#ifndef LLIB_LPC2138_HPP
#define LLIB_LPC2138_HPP

#include <stdint.h>

#define     __I     const volatile       /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

namespace llib::lpc2138 {
    // Watchdog timer interface
    struct Wdt {
        __IO uint32_t WDMOD;
        __IO uint32_t WDTC;
        __O  uint32_t WDFEED;
        __I  uint32_t WDTV;
    };

    Wdt *const WDT = ((Wdt *)0xE0000000);

    // Timer interface
    struct Tc {

    };

    Tc *const TC0 = ((Tc *)0xE0004000);
    Tc *const TC1 = ((Tc *)0xE0004000);

    // Uart interfaces
    struct Uart {

    };

    Uart *const UART0 = ((Uart *)0xE000C000);
    Uart *const UART1 = ((Uart *)0xE0010000);
    
    // PWM interface
    struct Pwm {

    };

    Pwm *const PWM = ((Pwm *)0xE0014000);

    // TWI(I2C) interfaces
    struct Twi {

    };

    Twi *const TWI0 = ((Twi *)0xE001C000);
    Twi *const TWI1 = ((Twi *)0xE005C000);

    // SPI interface
    struct Spi {

    };

    Spi *const SPI = ((Spi *)0xE0020000);

    // Real time clock
    struct Rtc {
        __IO uint32_t ILR;
        __I  uint32_t CTC;
        __IO uint32_t CCR;
        __IO uint32_t CIIR;
        __IO uint32_t AMR;
        __O  uint32_t CTIME0;
        __O  uint32_t CTIME1;
        __O  uint32_t CTIME2;
        __IO uint32_t SEC;
        __IO uint32_t MIN;
        __IO uint32_t HOUR;
        __IO uint32_t DOM;
        __IO uint32_t DOW;
        __IO uint32_t DOY;
        __IO uint32_t MONTH;
        __IO uint32_t YEAR;
        __I  uint32_t reserved[9];
        __IO uint32_t ALSEC;
        __IO uint32_t ALMIN;
        __IO uint32_t ALHOUR;
        __IO uint32_t ALDOM;
        __IO uint32_t ALDOW;
        __IO uint32_t ALDOY;
        __IO uint32_t ALMON;
        __IO uint32_t ALYEAR;
        __IO uint32_t PREINT;
        __IO uint32_t PREFRAC;
    };

    Rtc *const RTC = ((Rtc *)0xE0024000);

    // legacy GPIO ports
    struct Pio {
        __IO uint32_t IOPIN;
        __IO uint32_t IOSET;
        __IO uint32_t IODIR;
        __O  uint32_t IOCLR;
    };

    Pio *const PIO0 = ((Pio *)0xE0028000);
    Pio *const PIO1 = ((Pio *)0xE0028010);

    // fast GPIO ports
    struct Fpio {
        __IO uint32_t FIODIR;
        __O  uint32_t reserved[2];
        __IO uint32_t FIOMASK;
        __IO uint32_t FIOPIN;
        __IO uint32_t FIOSET;
        __IO uint32_t FIOCLR;        
    };

    Fpio *const FPIO0 = ((Fpio *)0x3FFFC000);
    Fpio *const FPIO1 = ((Fpio *)0x3FFFC020);

    // Pin connect block
    struct Pcb {

    };

    Pcb *const PCB = ((Pcb *)0xE002C000);

    // ADC interfaces
    struct Adc {

    };

    Adc *const ADC0 = ((Adc *)0xE0034000);
    Adc *const ADC1 = ((Adc *)0xE0060000);

    // SSP interface
    struct Ssp {

    };

    Ssp *const SSP = ((Ssp *)0xE0068000);

    // DAC interface
    struct Dac {
        __IO uint32_t DACR;
    };

    Dac *const DAC = ((Dac *)0xE006C000);

    // System control block
    struct Scb {

    };

    Scb *const SCB = ((Scb *)0xE01FC000);
}

#endif  // LLIB_LPC2138_HPP
