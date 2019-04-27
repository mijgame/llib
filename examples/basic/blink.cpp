#include <watchdog.hpp>
#include <pins.hpp>
#include <wait.hpp>

using namespace llib::due;

int main(){
    // kill the watchdog
    watchdog::disable();

    pin_out<pins::d13> d13;

    d13.init();

    bool output = false;

    while(true){
        // set output value on pin d13
        d13.set(output);

        // invert output value
        output ^= true;

        llib::wait_for(llib::ms{500});
    }
}
