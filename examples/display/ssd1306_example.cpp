#include <watchdog.hpp>
#include "twi.hpp"
#include "displays/ssd1306.hpp"

int main() {
    // Disable the watchdog timer.
    llib::target::watchdog::disable();

    using namespace llib::due;

    // The i2c bus with the given configuration is a
    // type, not an instance.
    using i2c = twi::bus<twi::twi1, twi::mode::MASTER>;

    // Initialize the i2c bus with the given clock.
    // Can go faster, but would be out of spec.
    i2c::init<100'000>();

    // The display uses an instance. Default address is
    // 0x3C.
    llib::displays::ssd1306<i2c> display;

    // Initialize the display; sets up some default
    // parameters.
    display.init();

    // Draw a dot that travels across the middle
    // of the screen.
    for (;;) {
        for (int i = 0; i < 128; i++) {
            display.clear();
            display.write(i, 32, llib::graphics::white);
            display.flush();
        }
    }
}
