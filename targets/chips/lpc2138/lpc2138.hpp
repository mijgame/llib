#ifndef LLIB_LPC2138_HPP
#define LLIB_LPC2138_HPP

#include <stdint.h>

#define     __I     volatile             /*!< Defines 'read only' permissions                 */
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

namespace llib::lpc2138 {
    struct Pio {
        __IO uint32_t IOPIN;
        __IO uint32_t IOSET;
        __IO uint32_t IODIR;
        __O  uint32_t IOCLR;
    };

    // legacy ports
    #define PIO0       ((Pio   *)0xE0028000)
    #define PIO1       ((Pio   *)0xE0028010)
}

#endif  // LLIB_LPC2138_HPP
