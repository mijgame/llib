#include <wait.hpp>

#include "base.hpp"

namespace llib {
    uint_fast64_t _ticks() {
        static bool initialized = false;

        if (!initialized) {
            EFC0->EEFC_FMR = EEFC_FMR_FWS(4);
            EFC1->EEFC_FMR = EEFC_FMR_FWS(4);

            SysTick->CTRL = 0;          // Stop timer
            SysTick->LOAD = 0xFFFFFF;   // 24-bit timer
            SysTick->VAL = 0;           // Clear timer
            SysTick->CTRL = 5;          // Start timer

            initialized = true;
        }

        static uint32_t last_low = 0;
        static uint64_t high = 0;

        uint32_t low = 0xFFFFFF - (SysTick->VAL & 0xFFFFFF);

        if (low < last_low) {
            // Rollover, increment
            high += 0x1ULL << 24;
        }

        last_low = low;

        return (low | high);
    }

    uint64_t _us() {
        return _ticks() / 84;
    }

    void wait_for(uint64_t ns) {
        // Due works on 84mhz, so a single tick is 11.9ns
        // for now only a us resolution is used.
        // TODO: support ns resolution

        auto end = _us() + (ns / 1000);

        while (_us() < end);
    }

    void sleep_for(uint64_t ns) {
        // TODO: use timer

        wait_for(ns);
    }
}