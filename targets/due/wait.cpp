#include <wait.hpp>
#include <base.hpp>
#include <tc_interrupt.hpp>
#include <units.hpp>

namespace llib {
    using tc_controller = target::tc::controller<
        target::tc::channel_0
    >;

    // For now, we only need one bool in total.
    static volatile bool done = false;

    void wfe_until_done() {
        tc_controller::enable_interrupt();

        while (!done) {
            // Sleep to save power...
            __WFE();
        }

        done = false;

        tc_controller::disable_interrupt();
    }

    void wait_for(const llib::us us) {
        tc_controller::init([] {
            done = true;
        });

        uint32_t _sec = us.value / 1'000'000;

        if (_sec) {
            tc_controller::set_frequency(
                centihertz::from_s(_sec)
            );

            wfe_until_done();
        }

        if (us.value) {
            tc_controller::set_frequency(
                hertz::from(us)
            );

            wfe_until_done();
        }
    }

    void wait_for(const llib::ms ms) {
        tc_controller::init([] {
            done = true;
        });

        tc_controller::set_frequency(
            hertz::from(ms)
        );

        wfe_until_done();
    }

    void wait_for(const llib::s s) {
        tc_controller::init([] {
            done = true;
        });

        tc_controller::set_frequency(
            hertz::from(s)
        );

        wfe_until_done();
    }
}