#ifndef LLIB_UART_HPP
#define LLIB_UART_HPP

#include "peripheral.hpp"
#include "pio.hpp"

namespace llib {
    namespace uart {
        struct uart {
            constexpr static uint32_t instance_id = ID_UART;
        };

        template<unsigned int baud = 115200>
        void init() {
            static bool initialised = false;

            if (initialised) {
                return;
            }

            // Enable clock on port A
            enable_clock<pioa>();

            // Disable PIo control on PA9
            PIOA->PIO_PDR = PIO_PA8;
            PIOA->PIO_ABSR &= ~PIO_PA8;
            PIOA->PIO_PDR = PIO_PA9;
            PIOA->PIO_ABSR &= ~PIO_PA9;

            // Enable UART clock
            enable_clock<uart>();

            // Reset and disable receiver and transmitter
            UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;

            // Baudrate to 115200
            UART->UART_BRGR = 5241600 / baud;

            // No parity, normal channel
            UART->UART_MR = UART_MR_PAR_NO;

            // Disable interrupts
            UART->UART_IDR = 0xFFFFFFFF;

            // Enable the receiver and the transmitter
            UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;

            initialised = true;
        }

        bool char_available() {
            return (UART->UART_SR & 1) != 0;
        }

        char get_char() {
            while (!char_available());

            return UART->UART_RHR;
        }

        void put_char(const char c) {
            while ((UART->UART_SR & 2) == 0);
            UART->UART_THR = c;
        }
    }
}

#endif //LLIB_UART_HPP
