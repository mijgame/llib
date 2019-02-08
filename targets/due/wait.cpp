#include <wait.hpp>

#include "base.hpp"

namespace llib {
    uint64_t _ticks() {
        // save data sinds we can only read the flag once
        uint32_t SysTick_CTRL = SysTick->CTRL;

        if (!(SysTick_CTRL & SysTick_CTRL_ENABLE_Msk)) {
            SysTick->CTRL = 0;          // Stop timer
            SysTick->LOAD = 0xFFFFFF;   // 24-bit timer
            SysTick->VAL = 0;           // Clear timer
            SysTick->CTRL = 5;          // Start timer
        }

        static uint64_t high_counter = 0;

        if (SysTick_CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            // Rollover, increment
            high_counter += ((SysTick->LOAD & 0xFFFFFF) + 1);
        }

        uint32_t low_counter = (SysTick->LOAD & 0xFFFFFF) - (SysTick->VAL & 0xFFFFFF);

        return (high_counter + low_counter);
    }

    uint64_t _ns() {
        return _ticks() * 12;
    }

    uint64_t _us() {
        return _ticks() / 84;
    }

    void wait_for(uint64_t ns) {
        // Due works on 84mhz, so a single tick is 11.9ns
        // for now only a us resolution is used.
        // TODO: support ns resolution
                
        auto end = _ns() + ns;

        while (_ns() < end);
    } 

    void sleep_for(uint64_t ns) {
        // TODO: use timer

        wait_for(ns);
    }
}

extern "C"{
    void __systick_handler(){
        // do nothing
    }
}