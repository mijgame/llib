#include <wait.hpp>
#include <base.hpp>
#include <tc_interrupt.hpp>

namespace llib {
    struct _timer {
        uint_fast32_t counter;
        uint_fast32_t rollovers;

        _timer()
            : counter(0), rollovers(0) {}
    };

    void _stop_systick() {
        SysTick->CTRL = 0;
    }

    void _reset_systick() {
        if (!(SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)) {
            SysTick->CTRL = 0;          // Stop timer
            SysTick->LOAD = 0xFFFFFF;   // 24-bit timer
            SysTick->CTRL = 5;          // Start timer
        }

        SysTick->VAL = 0;           // Clear timer
    }

    void _advance_timer(_timer &timer) {
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            timer.rollovers += 1;
        }

        timer.counter = 0xFFFFFF - (SysTick->VAL & 0xFFFFFF);
    }

    void _wait_for(const uint_fast32_t rollovers, const uint_fast32_t ticks) {
        _timer timer;

        _reset_systick();

        while (timer.rollovers < rollovers) {
            _advance_timer(timer);
        }

        // TODO: can a rollover occur without us knowing here?
        while (timer.counter < ticks) {
            _advance_timer(timer);
        }

        _stop_systick();
    }

    void wait_for(const llib::ns ns) {
        constexpr uint_fast32_t ticks_per_rollover = 16777216;

        const uint_fast32_t total_ticks = ns.value / 12;
        const uint_fast32_t rollovers = total_ticks / ticks_per_rollover;
        const uint_fast32_t ticks = total_ticks - ticks_per_rollover * rollovers;

        _wait_for(rollovers, ticks);
    }

    void wait_for(const llib::us us) {
        // Approx: rounded down from 199648,8704
        constexpr uint_fast32_t us_per_rollover = 199648;
        constexpr uint_fast32_t ns_short_per_rollover = 129;

        const uint_fast32_t rollovers = us.value / us_per_rollover;
        const uint_fast32_t ticks = (us.value - us_per_rollover * rollovers) * 84;

        _wait_for(rollovers, ticks);
        wait_for(ns{rollovers * ns_short_per_rollover});
    }

    void wait_for(const llib::ms ms) {
        constexpr uint_fast32_t ms_per_rollover = 199;

        const uint_fast32_t rollovers = ms.value / ms_per_rollover;
        const uint_fast32_t excess_us = (ms.value % ms_per_rollover) * 1000;

        _wait_for(rollovers, 0);
        wait_for(us{excess_us});
    }

    void wait_for(const llib::s s) {
       wait_for(ms{s.value * 1000});
    }

    void wait_for_new(const llib::us us) {
        static volatile bool done = false;

        using tc_controller = target::tc::controller<
            target::tc::channel_0
        >;

        tc_controller::init([] {
            done = true;
        });

        uint32_t _us = us.value;
        uint32_t _sec = us.value / 1'000'000;

        llib::cout << "S: " << _sec << " uS: " << _us << '\n'; 

        if (_sec) {
            tc_controller::set_frequency(
                target::tc::centihertz::from_s(_sec)
            );
            tc_controller::enable_interrupt();

            while (!done) {
                __WFE();
            }

            done = false;
        }
 
        if (_us) {
            tc_controller::set_frequency(
                target::tc::hertz::from_us(_us)
            );
            tc_controller::enable_interrupt();

            while (!done) {
                __WFE();
            }

            done = false;
        }

        tc_controller::disable_interrupt();
    }

//    void sleep_for(uint64_t ns) {
//        // TODO: use timer
//
//        wait_for(ns);
//    }
}

extern "C" {
void __systick_handler() {
    // do nothing
}
}