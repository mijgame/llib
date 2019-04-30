#ifndef LLIB_DUE_TWI_HPP
#define LLIB_DUE_TWI_HPP

#include "pins.hpp"
#include "peripheral.hpp"
#include "wait.hpp"
#include "error.hpp"
#include "interrupt.hpp"
#include "queue.hpp"

namespace llib::due::twi {
    struct twi0 {
        // twi numbers are switched on the arduino due
        constexpr static uint32_t instance_id = ID_TWI1;
        constexpr static uint32_t irqn = static_cast<uint32_t>(TWI1_IRQn);

        using sda = pins::sda;
        using scl = pins::scl;
    };

    struct twi1 {
        // twi numbers are switched on the arduino due
        constexpr static uint32_t instance_id = ID_TWI0;
        constexpr static uint32_t irqn = static_cast<uint32_t>(TWI0_IRQn);

        using sda = pins::sda1;
        using scl = pins::scl1;
    };

    enum class mode {
        MASTER,
        SLAVE
    };

    template<typename TWI>
    Twi *const port = nullptr;

    template<>
    Twi *const port<twi0> = TWI1;

    template<>
    Twi *const port<twi1> = TWI0;

    // all the twi messages in the status register
    enum class twi_message {
        OK = 0x0, // is nothing in the status register
        TXCOMP = 0x1,
        RXRDY = 0x2,
        TXRDY = 0x4,
        SVREAD = 0x8,
        SVACC = 0x10,
        GACC = 0x20,
        OVRE = 0x40,
        TIMEOUT = 0x80, // this one is not in the status register
        NACK = 0x100,
        ARBLST = 0x200,
        SCLWS = 0x400,
        EOSACC = 0x800,
        ENDRX = 0x1000,
        ENDTX = 0x2000,
        RXBUFF = 0x4000,
        TXBUFE = 0x8000
    };

    template<typename TWI, mode TwiMode, size_t RxBuffer = 64, size_t TxBuffer = 64>
    class bus {};

    template<typename TWI>
    class bus<TWI, mode::MASTER> {
    private:
        constexpr static uint32_t variant_mck = CHIP_FREQ_CPU_MAX;
        constexpr static uint32_t xmit_timeout = 100'000;

        static void _set_clock(uint32_t Frequency) {
            uint32_t divider = 0;

            // Calculate clock divider and clock low/high divider
            for (uint8_t clk_div = 0; clk_div < 7; clk_div++) {
                divider = ((variant_mck / (2 * Frequency)) - 4) / pow(2, clk_div);

                if (divider <= 0xFF) {
                    divider = ((clk_div & 0x7) << 16) | ((divider & 0xFF) << 8) | (divider & 0xFF);
                    break;
                }
            }

            port<TWI>->TWI_CWGR = 0;
            port<TWI>->TWI_CWGR = divider;
        }

        static twi_message _wait_for_status(const twi_message flag) {
            uint32_t status = port<TWI>->TWI_SR;
            uint32_t timeout = xmit_timeout;

            while (!(status & uint32_t(flag))) {
                status = port<TWI>->TWI_SR;

                if (status & TWI_SR_NACK) {
                    // Not ack received, stop
                    return twi_message::NACK;
                }

                if (--timeout == 0) {
                    // Tried for to long, stop
                    return twi_message::TIMEOUT;
                }
            }

            return flag;
        }

        template<bool Read>
        static void _start(const uint8_t addr, const uint32_t in_addr = 0, const uint8_t in_addr_size = 0) {
            // Setup addresses
            port<TWI>->TWI_MMR = (uint32_t(addr & 0x7F) << 16) | ((in_addr_size & 0x3) << 8);

            if constexpr (Read) {
                // Enable Read mode
                port<TWI>->TWI_MMR |= TWI_MMR_MREAD;
            }

            // Set the internal address / data after addr and before repeated start
            port<TWI>->TWI_IADR = in_addr & 0xFFFFFF;
        }

        static twi_message _read(uint8_t *data, const size_t size) {
            // Write a start
            port<TWI>->TWI_CR = TWI_CR_START;

            for (size_t i = 0; i < size; i++) {
                if (i + 1 >= size) {
                    // Write stop on last byte we want to read
                    port<TWI>->TWI_CR = TWI_CR_STOP;
                }

                auto res = _wait_for_status(twi_message::RXRDY);
                if (res == twi_message::RXRDY) {
                    // Read data into array
                    data[i] = static_cast<uint8_t>(port<TWI>->TWI_RHR & 0xFF);
                } else {
                    // Return error
                    return res;
                }
            }

            // Wait until read is done
            return _wait_for_status(twi_message::TXCOMP);
        }

    public:
        template<uint32_t Frequency = 100000>
        static void init() {
            // Enable clock
            enable_clock<TWI>();

            // Change the multiplexer
            set_peripheral<typename TWI::sda>();
            set_peripheral<typename TWI::scl>();

            // Enable the pullups of the pins
            pin_in<typename TWI::sda>::pullup_enable();
            pin_in<typename TWI::scl>::pullup_enable();

            // Disable PDC channel
            port<TWI>->TWI_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

            // TWI Slave Mode Enabled
            port<TWI>->TWI_CR = TWI_CR_SVEN;

            // TWI disable
            port<TWI>->TWI_CR = TWI_CR_SWRST;
            port<TWI>->TWI_RHR;

            // Wait for at least 10ms
            wait_for(llib::ms{15});

            // TWI Slave mode disabled, Twi master mode disabled
            port<TWI>->TWI_CR = TWI_CR_SVDIS | TWI_CR_MSDIS;

            // Enable master mode
            port<TWI>->TWI_CR = TWI_CR_MSEN;

            _set_clock(Frequency);
        }

        /**
         * Sets the twi frequency
         *
         * @param frequency
         */
        static void set_frequency(const uint32_t frequency){
            _set_clock(frequency);
        }

        /**
         * Starts a write transmission.
         *
         * @param address
         */
        static void start_transmission(const uint8_t address) {
            // Start a write
            _start<false>(address);
        }

        /**
         * Ends a transmission and checks for errors.
         */
        static twi_message end_transmission() {
            // Stop write
            port<TWI>->TWI_CR = TWI_CR_STOP;

            return _wait_for_status(twi_message::TXCOMP);
        }

        /**
         * Writes an array of bytes to the twi interface.
         *
         * @param data
         * @param size
         */
        static twi_message write(const uint8_t *data, const size_t size) {
            // Write the amount of data to the twi interface and check if nothing wrong happens
            for (size_t i = 0; i < size; i++) {
                // Write data in twi register
                port<TWI>->TWI_THR = data[i];

                auto res = _wait_for_status(twi_message::TXRDY);
                if (res != twi_message::TXRDY) {
                    // Error
                    return res;
                }
            }

            return twi_message::OK;
        }

        /**
         * Writes an single byte to the twi interface.
         *
         * @param data
         */
        static twi_message write(const uint8_t data) {
            // Write data in twi register
            port<TWI>->TWI_THR = data;

            auto res = _wait_for_status(twi_message::TXRDY);
            if (res != twi_message::TXRDY) {
                // Error
                return res;
            }

            return twi_message::OK;
        }

        /**
         * Writes the given byte for count amount
         * to the twi interface.
         *
         * @param data
         * @param count
         * @return
         */
        static twi_message write(const uint8_t data, const uint32_t count) {
            // Write the amount of data to the twi interface and check if nothing wrong happens
            for (size_t i = 0; i < count; i++) {
                // Write data in twi register
                port<TWI>->TWI_THR = data;

                auto res = _wait_for_status(twi_message::TXRDY);
                if (res != twi_message::TXRDY) {
                    // Error
                    return res;
                }
            }

            return twi_message::OK;
        }

        /**
         * Tries to read size amount of bytes from the twi interface.
         *
         * @param addres
         * @param data
         * @param size
         */
        static twi_message read(const uint8_t address, uint8_t *data, const size_t size) {
            // Start a read
            _start<true>(address);

            // Read the data
            return _read(data, size);
        }

        /**
         * Tries to read a byte from the twi interface, but it doesn't save the result.
         * @param address
         * @param data
         * @param size
         * @return
         */
        static twi_message read(const uint8_t address) {
            // Start a read
            _start<true>(address);

            // Read the data
            uint8_t v;
            return _read(&v, 1);
        }

        /**
         * Tries to read size amount of bytes from the twi interface.
         * This writes one or two bytes before the read to the twi interface.
         *
         * @param address
         * @param data
         * @param size
         */
        template<
            typename T,
            uint8_t InSize = sizeof(T),
            typename = std::enable_if_t<sizeof(T) <= 2>
        >
        static twi_message read(const uint8_t address, const T in_addr, uint8_t *data, const size_t size) {
            // Start a read with two or less InSize
            _start<true>(address, uint32_t(in_addr & 0xFFFFFF), InSize);

            // Read the data
            return _read(data, size);
        }

        /**
         * Tries to read a size amount of bytes from the twi interface.
         * This writes 3 bytes before the read to the twi interface.
         *
         * @param address
         * @param data
         * @param size
         */
        template<
            typename T,
            typename = std::enable_if_t<(sizeof(T) > 2)>
        >
        static twi_message read(const uint8_t address, const T in_addr, uint8_t *data, const size_t size) {
            // Start a read with more than two In_size
            _start<true>(address, uint32_t(in_addr & 0xFFFFFF), 3);

            // Read the data
            return _read(data, size);
        }

        static bool is_valid(twi_message message){
            return (message != twi_message::TIMEOUT && message != twi_message::NACK);
        }
    };

    template<typename TWI, size_t RxBuffer, size_t TxBuffer>
    class bus<TWI, mode::SLAVE, RxBuffer, TxBuffer>{
    private:
        static inline llib::queue<uint8_t, RxBuffer, true> rx_buffer;
        static inline llib::queue<uint8_t, TxBuffer, false> tx_buffer;

        using interrupt_callback = void (*)();

        static inline interrupt_callback recive_isr = nullptr;
        static inline interrupt_callback request_isr = nullptr;

        static void _isr_handler_twi(){
            // read status register once since some of the
            // bits get lost if you read the register
            uint32_t status_reg = port<TWI>->TWI_SR;
            uint32_t interrupt_msk = port<TWI>->TWI_IMR;

            // calculate interrupts to activate based on the isr mask
            uint32_t interrupts = status_reg & interrupt_msk;

            if(interrupts & TWI_SR_SVACC){
                // enable access to the device
                return _isr_svacc_slave();
            }

            if(interrupts & TWI_SR_EOSACC){
                // clear device access
                return _isr_eosacc_slave();
            }

            if(status_reg & TWI_SR_SVREAD){
                // write mode
                return _isr_write(status_reg);
            }
            else {
                // read mode
                return _isr_read(status_reg);
            }
        }

        static void _isr_read(uint32_t status_reg){
            if (!(status_reg & TWI_SR_RXRDY)){
                // data not ready yet
                return;
            }
            if(rx_buffer.size() >= rx_buffer.max_size() - 1){
                // buffer is full so stop
                return;
            }
            rx_buffer.push(port<TWI>->TWI_RHR);
        }

        static void _isr_write(uint32_t status_reg){
            if(!(status_reg & TWI_SR_TXRDY) || status_reg & TWI_SR_NACK){
                // not ready to accept new data
                return;
            }
            // update the holding register
            if(tx_buffer.size() == 0){
                // nothing to update since registers are empty so
                // write some data to keep the i2c bus going
                port<TWI>->TWI_THR = 0x00;
                return;
            }
            port<TWI>->TWI_THR = tx_buffer.copy_and_pop();
        }

        static void _isr_eosacc_slave(){
            if(recive_isr){
                recive_isr();
            }

            // disable read interrupts
            port<TWI>->TWI_IER = TWI_IER_SVACC;
            port<TWI>->TWI_IDR = TWI_IDR_RXRDY | TWI_IDR_GACC | TWI_IDR_NACK
                               | TWI_IDR_EOSACC | TWI_IDR_SCL_WS | TWI_IER_TXCOMP;
        }

        static void _isr_svacc_slave(){
            // enable read interrupts
            port<TWI>->TWI_IDR = TWI_IDR_SVACC;
            port<TWI>->TWI_IER = TWI_IER_RXRDY | TWI_IER_GACC | TWI_IER_NACK
                               | TWI_IER_EOSACC | TWI_IER_SCL_WS | TWI_IER_TXCOMP;

            if(!(port<TWI>->TWI_SR & TWI_SR_SVREAD) && request_isr){
                request_isr();
            }
        }

    public:
        /**
         * @brief init the twi slave
         *
         * @param addr
         */
        static void init(const uint8_t addr) {
            // Enable clock
            enable_clock<TWI>();

            // clear buffers
            rx_buffer.clear();
            tx_buffer.clear();

            // Change the multiplexer
            set_peripheral<typename TWI::sda>();
            set_peripheral<typename TWI::scl>();

            // Enable the pullups of the pins
            pin_in<typename TWI::sda>::pullup_enable();
            pin_in<typename TWI::scl>::pullup_enable();

            // Disable PDC channel
            port<TWI>->TWI_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

            // disable interrupts
            port<TWI>->TWI_IDR = 0xFFFF;

            // dummy read isr
            port<TWI>->TWI_SR;

            // attach all interrupts to _isr_handler_twi sinds any interrupt will trigger 0x1
            attach_interrupt<TWI, 0x1>(_isr_handler_twi);

            // TWI disable
            port<TWI>->TWI_CR = TWI_CR_SWRST;
            port<TWI>->TWI_RHR;

            // Wait for at least 10ms
            wait_for(llib::ms{15});

            // TWI Slave mode disabled, Twi master mode disabled
            port<TWI>->TWI_CR = TWI_CR_SVDIS | TWI_CR_MSDIS;

            // Configure slave address
            port<TWI>->TWI_SMR = TWI_SMR_SADR(addr);

            port<TWI>->TWI_CR = TWI_CR_MSDIS | TWI_CR_SVDIS;

            // TWI Slave Mode Enabled
            port<TWI>->TWI_CR = TWI_CR_SVEN;

            // enable interrupts
            port<TWI>->TWI_IER = TWI_IER_SVACC;

            // Wait for at least 10ms
            wait_for(llib::ms{15});

            if(port<TWI>->TWI_CR & TWI_CR_SVDIS){
                // Retry since twi is not in slave mode
                LLIB_WARNING("Failed setting twi in slave mode. Trying again");
                init(addr);
            }
        }

        /**
         * @brief returns the amount of bytes in the rx_buffer
         *
         * @return size_t
         */
        static size_t rx_available(){
            return rx_buffer.size();
        }

        /**
         * @brief returns the amount of bytes the tx_buffer has left
         *
         * @return size_t
         */
        static size_t tx_available(){
            return tx_buffer.max_size() - tx_buffer.size();
        }

        /**
         * @brief read a single byte from the rx_buffer
         * @warning if the buffer is empty it will return random data
         *
         * @return uint8_t
         */
        static uint8_t read(){
            if(rx_buffer.empty()){
                return 0x00;
            }
            return rx_buffer.copy_and_pop();
        }

        /**
         * @brief writes a single byte to the tx_buffer
         * @warning if the buffer is full it will discard the data
         * @warning the master should do a dummy read before reading
         * the actual data
         *
         * @param data
         */
        static void write(uint8_t data){
            if(!tx_available()){
                // tx_buffer is full
                return;
            }
            tx_buffer.push(data);
        }

        /**
         * @brief set the callback when a transmission is complete
         * this can be a read or a write
         *
         * @param isr
         */
        static void on_receive(interrupt_callback isr){
            recive_isr = isr;
        }

        /**
         * @brief set the callback for when a read is requested
         *
         * @param isr
         */
        static void on_request(interrupt_callback isr){
            request_isr = isr;
        }
    };
}

extern "C" {
void __TWI0_Handler(){
    // handle twi 0 with twi 1 sinds the twi ports are reversed on the arduino due   
    // force all interrupts to execute handler function at 0x1
    llib::due::_handle_isr<llib::due::twi::twi1>(0x1, 0x1);
}

void __TWI1_Handler(){
    // handle twi 1 with twi 0 sinds the twi ports are reversed on the arduino due
    // force all interrupts to execute handler function at 0x1
    llib::due::_handle_isr<llib::due::twi::twi0>(0x1, 0x1);
}
}

#endif