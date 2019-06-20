#include "rtos.hpp"

#include <base.hpp>

using namespace llib::rtos;

scheduler_base *scheduler_base::instance = nullptr;

extern "C" {
auto *instance = scheduler_base::instance;

void __systick_handler() {
    __disable_irq();
    scheduler_base::instance->tick();
    __enable_irq();
}

void __hardfault_handler() {
    llib::cout << "HARDFAULT ERROR\n";

    for (;;) {}
}

// void __attribute__((optimize("O0"))) __pendsv_handler() {
//     task_base *old = instance->current;
//     instance->current = instance->next;

//     switch_task(&old->sp, instance->current->sp);

// //     // this uses the idea that the following registers are already stored in
// //     // the old stack:
// //     // r0, r1, r2, r3, r12, lr, pc, stack
//     asm volatile (
//         // get process stack pointer
//         "mrs r2, PSP\n"
//         "isb\n"

//         // reserve space for registers (8 * 4 = 32 bytes)
//         "sub r2, #0x20\n"

//         // store the new location for later use
//         "str r2, [ %0 ]\n"

//         // save current context on the old stack
//         "stm r2,{r4, r5, r6, r7}\n"
// //        "str r4, [r2, #0x00]\n"
// //        "str r5, [r2, #0x04]\n"
// //        "str r6, [r2, #0x08]\n"
// //        "str r7, [r2, #0x0C]\n"

//         // copy the higher registers to the old stack
//         "mov r3, r8\n"
//         "str r3, [r2, #0x10]\n"
//         "mov r3, r9\n"
//         "str r3, [r2, #0x14]\n"
//         "mov r3, r10\n"
//         "str r3, [r2, #0x18]\n"
//         "mov r3, r11\n"
//         "str r3, [r2, #0x1C]\n"

//         "mov r0, %1\n"

//         // restore the new context from the stack
//         "ldm r0, {r4, r5, r6, r7}\n"
// //        "ldr r4, [r0, #0x00]\n"
// //        "ldr r5, [r0, #0x04]\n"
// //        "ldr r6, [r0, #0x08]\n"
// //        "ldr r7, [r0, #0x0C]\n"

//         // copy the higher registers to from the new stack
//         "ldr r3, [r0, #0x10]\n"
//         "mov r8, r3\n"
//         "ldr r3, [r0, #0x14]\n"
//         "mov r9, r3\n"
//         "ldr r3, [r0, #0x18]\n"
//         "mov r10, r3\n"
//         "ldr r3, [r0, #0x1C]\n"
//         "mov r11, r3\n"

//         // update the new stack pointer
//         "add r3, r0, #0x20\n"
//         "msr PSP, r3\n"
//         "isb\n"

//         : /* No output operands */

//         // %0 = pointer to old SP
//         // %1 = new value of SP
//         : "r"(&old->sp), "r"(instance->next->sp)
//     );

// //     instance->current = instance->next;

// //     llib::cout << llib::array_values(&instance->current->sp, 16) << '\n';
// }
}