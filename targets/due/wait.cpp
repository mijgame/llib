#include <wait.hpp>

#include "base.hpp"

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

    void wait_for(llib::ns ns) {
        constexpr uint_fast32_t ticks_per_rollover = 16777216;

        const uint_fast32_t total_ticks = ns.value / 12;
        const uint_fast32_t rollovers = total_ticks / ticks_per_rollover;
        const uint_fast32_t ticks = total_ticks - ticks_per_rollover * rollovers;

        _wait_for(rollovers, ticks);
    }

    void wait_for(llib::us us) {
        constexpr uint_fast32_t us_per_rollover = 1410;

        const uint_fast32_t divider = us.value / us_per_rollover;
        const uint_fast32_t rollovers = us.value / us_per_rollover;
        const uint_fast32_t ticks = (us.value - us_per_rollover * divider) * 84;

        _wait_for(rollovers, ticks);
    }

    void wait_for(llib::ms ms) {
        constexpr uint_fast32_t us_per_rollover = 1410;

        const uint_fast32_t total_us = ms.value * 1000;
        const uint_fast32_t divider = total_us / us_per_rollover;
        const uint_fast32_t rollovers = total_us / us_per_rollover;
        const uint_fast32_t ticks = (total_us - us_per_rollover * divider) * 84;

        _wait_for(rollovers, ticks);
    }

    void wait_for(llib::s s) {
        constexpr uint_fast32_t us_per_rollover = 1410;

        const uint_fast32_t total_us = s.value * 1000 * 1000;
        const uint_fast32_t divider = total_us / us_per_rollover;
        const uint_fast32_t rollovers = total_us / us_per_rollover;
        const uint_fast32_t ticks = (total_us - us_per_rollover * divider) * 84;

        _wait_for(rollovers, ticks);
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