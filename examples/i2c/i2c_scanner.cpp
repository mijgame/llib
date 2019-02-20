#include <stream.hpp>
#include <uart.hpp>
#include <watchdog.hpp>
#include <wait.hpp>
#include <twi.hpp>

using namespace llib::due;

int main() {
    // Kill the watchdog
    watchdog::disable();

    // Init the uart for cout
    uart::init();

    // Wait for terminal to start up
    llib::wait_for(llib::ms{1000});

    llib::cout << "Starting I2C scanner\n";

    twi::bus<twi::twi0, twi::mode::MASTER> twi;

    twi.init<100'000>();

    llib::cout << "Scanning...\n\n";

    // Scan for all 127 devices
    for (uint8_t i = 0; i < 0x7F; i++) {
        // Start a transmission on address i
        twi.start_transmission(i);
        auto t = twi.write(0xFF);

        // Check if value is not a timeout or a nack
        if (t != twi::twi_message::TIMEOUT && t != twi::twi_message::NACK) {
            llib::cout << "I2C device found at: " << llib::hex << i << '\n';
        }

        // Close the transmission
        twi.end_transmission();
    }

    llib::cout << "\nDone scanning\n";
}