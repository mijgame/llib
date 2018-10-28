#ifndef LLIB_UART_HPP
#define LLIB_UART_HPP

#include "sam.h"

namespace llib {
    namespace uart {
        void init() {
            static bool initialised = false;

            if (initialised) {
                return;
            }

            // Enable clock on port A
            PMC->PMC_PCER0 = 1 << ID_PIOA;

            // Disable PIo control on PA9
            PIOA->PIO_PDR = PIO_PA8;
            PIOA->PIO_ABSR &= ~PIO_PA8;
            PIOA->PIO_PDR = PIO_PA9;
            PIOA->PIO_ABSR &= ~PIO_PA9;

            // Enable UART clock
            PMC->PMC_PCER0 = (0x01 << ID_UART);

            // Reset and disable receiver and transmitter
            UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;

            // Baudrate to 115200
            UART->UART_MR = 5241600 / 115200;

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
