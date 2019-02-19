#include <stream.hpp>
#include <uart.hpp>
#include <watchdog.hpp>
#include <wait.hpp>
#include <twi.hpp>

using namespace llib::due;

int main(){
    // kill the watchdog
    watchdog::disable();

    uart::init();

    // wait for terminal to start up
    llib::wait_for(llib::ms{1000});

    llib::cout << "Starting I2C scanner\n";

    twi::bus<twi::twi0, twi::mode::MASTER> twi;

    twi.init<100'000>();

    llib::cout << "Scanning...\n\n";

    // scan for all 127 devices
    for(uint8_t i = 0; i < 0x7F; i++){
        // start a transmission on address i
        twi.start_transmission(i);
        auto t = twi.write(0xFF);

        // check if value is not a timeout or a nack
        if(t != twi::twi_message::TIMEOUT && t != twi::twi_message::NACK){
            llib::cout << "I2C device found at: " << llib::hex << i << '\n';
        }

        // close the transmission
        twi.end_transmission();
    }

    llib::cout << "\nDone scanning\n";
    
    // endless loop
    while(true);
}