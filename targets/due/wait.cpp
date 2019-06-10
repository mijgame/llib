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

        auto _sec = llib::s{us.value / 1'000'000};
        auto _us = llib::us{us.value % 1'000'000};

        if (_sec.value) {
            tc_controller::set_frequency(_sec);

            wfe_until_done();
        }

        if (_us.value) {
            tc_controller::set_frequency(_us);

            wfe_until_done();
        }
    }

    void wait_for(const llib::ms ms) {
        tc_controller::init([] {
            done = true;
        });

        tc_controller::set_frequency(ms);

        wfe_until_done();
    }

    void wait_for(const llib::s s) {
        tc_controller::init([] {
            done = true;
        });

        tc_controller::set_frequency(s);

        wfe_until_done();
    }
}