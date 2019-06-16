#include "rtos.hpp"

#include <base.hpp>

using namespace llib::rtos;

scheduler_base *scheduler_base::instance = nullptr;

extern "C" {
void __systick_handler() {
    __disable_irq();
    scheduler_base::instance->tick();
    __enable_irq();
}

void __pendsv_handler() {
    llib::cout << "pendsv\n";

    auto *instance = scheduler_base::instance;

    task_base *old = instance->current;
    instance->current = instance->next;

//    switch_task(
//        &old->sp,
//        instance->next->sp
//    );

    asm volatile(
        // save current context on the stack
        "push { r4 - r7, lr }\n"
        "mov r2, r8\n"
        "mov r3, r9\n"
        "mov r4, r10\n"
        "mov r5, r11\n"
        "mov r6, r12\n"
        "push { r2 - r6 }\n"

        // *store_old_sp = SP
        // "mov r2, sp\n"

        // get process stack pointer
        "MRS r2, psp\n"
        "str r2, [ %0 ]\n"
        

        // SP = next_sp
        // "mov sp, %1\n"

        // write new stack location to the process stack ptr
        "MSR psp, %1\n"

        // restore the new context from the stack
        "pop { r2 - r6 }\n"
        "mov r12, r6\n"
        "mov r11, r5\n"
        "mov r10, r4\n"
        "mov r9, r3\n"
        "mov r8, r2\n"
        "pop { r4 - r7, pc }"

        : /* No output operands */

        // %0 = pointer to old SP
        // %1 = new value of SP
        : "r"(&old->sp), "r"(instance->next->sp)
    );
}
}