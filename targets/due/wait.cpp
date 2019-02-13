#include <wait.hpp>

#include "base.hpp"

namespace llib {
//    uint64_t _ticks() {
//        // save data since we can only read the flag once
//        uint32_t SysTick_CTRL = SysTick->CTRL;
//
//        if (!(SysTick_CTRL & SysTick_CTRL_ENABLE_Msk)) {
//            SysTick->CTRL = 0;          // Stop timer
//            SysTick->LOAD = 0xFFFFFF;   // 24-bit timer
//            SysTick->VAL = 0;           // Clear timer
//            SysTick->CTRL = 5;          // Start timer
//        }
//
//        static uint64_t high_counter = 0;
//
//        if (SysTick_CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
//            // Rollover, increment
//            high_counter += 1ULL << 24;
//        }
//
//        uint32_t low_counter = 0xFFFFFF - (SysTick->VAL & 0xFFFFFF);
//
//        return (high_counter + low_counter);
//    }
//
//    uint64_t _ns() {
//        auto ticks = _ticks();
//        return ticks * 11 + (ticks / 10 * 9);
//    }
//
//    uint64_t _us() {
//        return _ticks() / 84;
//    }

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

    void wait_for(uint64_t ns) {
        constexpr uint_fast32_t ticks_per_rollover = 16777216;

        _timer timer;

        const uint64_t total_ticks = ns / 12;
        const uint_fast32_t rollovers = total_ticks / ticks_per_rollover;
        const uint_fast32_t ticks = total_ticks - ticks_per_rollover * rollovers;

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

//    void wait_for(uint64_t ns) {
//        // Due works on 84mhz, so a single tick is 11.9ns
//        // for now only a us resolution is used.
//        // TODO: support ns resolution
//
//        auto end = _ns() + ns;
//
//        while (_ns() < end);
//    }

    void sleep_for(uint64_t ns) {
        // TODO: use timer

        wait_for(ns);
    }
}

extern "C" {
void __systick_handler() {
    // do nothing
}
}