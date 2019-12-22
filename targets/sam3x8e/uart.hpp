#ifndef LLIB_SAM3X8E_UART_HPP
#define LLIB_SAM3X8E_UART_HPP

#include "peripheral.hpp"
#include "pins.hpp"
#include "pio.hpp"

namespace llib::sam3x8e {
    namespace uart {
        struct uart {
            constexpr static uint32_t instance_id = ID_UART;
            constexpr static uint32_t irqn = static_cast<uint32_t>(UART_IRQn);
        };

        template<unsigned int Baud = 115200>
        void init() {
            // Enable clock on port A
            enable_clock<pioa>();

            using tx = pins::p2;
            using rx = pins::p27;

            // Disable PIO control on PA9
            set_peripheral<tx, tx::uart::periph>();
            set_peripheral<rx, rx::uart::periph>();

            // Enable UART clock
            enable_clock<uart>();

            // Reset and disable receiver and transmitter
            UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX;
            UART->UART_CR = UART_CR_RXDIS | UART_CR_TXDIS;

            // Baudrate to 115200
            UART->UART_BRGR = 5241600 / Baud;

            // No parity, normal channel
            UART->UART_MR = UART_MR_PAR_NO;

            // Disable interrupts
            UART->UART_IDR = 0xFFFFFFFF;

            // Enable the receiver and the transmitter
            UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
        }

        inline bool char_available() {
            return (UART->UART_SR & 1) != 0;
        }

        inline char get_char() {
            while (!char_available());

            return UART->UART_RHR;
        }

        inline void put_char(const char c) {
            while ((UART->UART_SR & 2) == 0);
            UART->UART_THR = c;
        }
    }
}

#endif //LLIB_SAM3X8E_UART_HPP
