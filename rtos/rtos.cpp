#include "rtos.hpp"

#include <base.hpp>

using namespace llib::rtos;

scheduler_base *scheduler_base::instance = nullptr;

volatile llib::rtos::_switch_helper _switch;

extern "C" {
void __systick_handler() {
    // __disable_irq();
    scheduler_base::instance->tick();
    // __enable_irq();
}

void __hardfault_handler() {
    llib::cout << "HARDFAULT";

    for (;;) {}
}

void print_stack(uint32_t *sp, const size_t length) {
    for ( size_t i = 0; i < (length + 3) / 4; i++) {
        llib::cout << reinterpret_cast<size_t>(sp + i * 4) << ": ";
        
        for ( size_t h = 0; h < 4; h++) {
            llib::cout << sp[i * 4 + h] << '\t';
        }
        llib::cout << '\n';
    }
    llib::cout << '\n';
}
}