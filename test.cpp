#include <watchdog.hpp>
#include <wait.hpp>
#include <stream.hpp>
#include <uart.hpp>
#include <ports.hpp>
#include <tc_interrupt.hpp>
//#include <sensors/hcsr04.hpp>

int main() {
    // Disable the watchdog timer.
    llib::target::watchdog::disable();
    llib::target::uart::init();

    wait_for(llib::ms{100});

    llib::cout << "Init...\n";

    for (;;) {
        llib::wait_for_new(llib::us{1000 * 1000 * 1000});
        llib::cout << "1 second passed\n";
    }
//
//    using test_pin = llib::pin_out<llib::pins::d7>;
//
//    test_pin::init();
//    test_pin::set<false>();
//
//    for (;;) {
//        llib::wait_for_new(llib::us{10});
//        test_pin::set<false>();
//        llib::wait_for_new(llib::us{10});
//        test_pin::set<true>();
//    }

//    using output_pin = llib::pin_out<llib::pins::d7>;
//
//    output_pin::init();
//
//    for(;;) {
//        output_pin::set<true>();
//        llib::wait_for_new(llib::us{10});
//        output_pin::set<false>();
//        llib::wait_for_new(llib::us{10});
//    }




//    wait_for(llib::ms{1000});
//
//    using namespace llib::due;
//
//    using trigger_pin = llib::pin_out<llib::pins::d7>;
//    using echo_pin = llib::pin_in<llib::pins::d6>;
//
//    trigger_pin::init();
//    echo_pin::init();
//
//    using sensor = llib::sensors::hcsr04<trigger_pin, echo_pin>;
//
//    for (;;) {
//        llib::cout << sensor::read() << llib::endl;
//    }
}
