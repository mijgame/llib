#include "rtos.hpp"

#include <base.hpp>

namespace llib::rtos {
    thread::thread(llib::rtos::thread::thread_handler handler)
        : handler(handler) {}

    void thread::start() {
        // Round down stack top to 8 byte boundary
        // Cortex-M stack grows from high -> low memory
        const uint32_t address = (reinterpret_cast<uint32_t>(stack + stack_size)) / 8 * 8;
        auto *initial_sp = reinterpret_cast<uint32_t *>(address);

        *(--initial_sp) = (1U << 24U);  /* xPSR */
        *(--initial_sp) = (uint32_t) handler; /* PC */
        *(--initial_sp) = 0x0000000EU; /* LR  */
        *(--initial_sp) = 0x0000000CU; /* R12 */
        *(--initial_sp) = 0x00000003U; /* R3  */
        *(--initial_sp) = 0x00000002U; /* R2  */
        *(--initial_sp) = 0x00000001U; /* R1  */
        *(--initial_sp) = 0x00000000U; /* R0  */
        /* additionally, fake registers R4-R11 */
        *(--initial_sp) = 0x0000000BU; /* R11 */
        *(--initial_sp) = 0x0000000AU; /* R10 */
        *(--initial_sp) = 0x00000009U; /* R9 */
        *(--initial_sp) = 0x00000008U; /* R8 */
        *(--initial_sp) = 0x00000007U; /* R7 */
        *(--initial_sp) = 0x00000006U; /* R6 */
        *(--initial_sp) = 0x00000005U; /* R5 */
        *(--initial_sp) = 0x00000004U; /* R4 */

        // Save top of the stack
        sp = initial_sp;

        auto *stack_limit = reinterpret_cast<uint32_t *>(
            ((reinterpret_cast<uint32_t>(stack - 1U) / 8) + 1U) * 8
        );

        // Pre-fill unused part of the stack with deadbeef
        for (uint32_t *ptr = initial_sp; ptr >= stack_limit; --ptr) {
            *ptr = 0xDEADBEEF;
        }

        id = scheduler::register_thread(this);
    }

    /// Scheduler

    // Initialize the idle thread.
    thread scheduler::idle_thread = thread(scheduler::on_idle);

    void scheduler::on_idle() {
        __WFE();
    }

    uint8_t scheduler::register_thread(thread *th) {
        uint8_t id = threads.size();

        threads.push_back(th);
        ready_to_run.set(id);

        return id;
    }

    void scheduler::schedule_cycle() {
        /*
         * This will set the PendSV bit in
         * the Interrupt Control and State Register, which
         * will set the PendSV exception to "pending".
         *
         * This will actually run once no other exceptions
         * are running.
         */
        SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
    }

    void scheduler::startup(size_t tps) {
        // Set up systick
        SysTick_Config(CHIP_FREQ_CPU_MAX / tps);

        // Set the PendSV interrupt to the lowest priority
        NVIC_SetPriority(PendSV_IRQn, 0xFFU);

        idle_thread.start();
    }

    void scheduler::tick() {
        // Are there any tasks ready to run?
        if (ready_to_run.none()) {
            // Go to the idle thread
            current_thread_id = 0;
            return;
        }

        do {
            current_thread_id += 1;

            if (current_thread_id == threads.size()) {
                current_thread_id = 1;
            }
        } while(! ready_to_run.test(current_thread_id - 1));

        next_thread = threads[current_thread_id];

        // If the next thread is not the current thread, schedule a cycle
        schedule_cycle();
    }
}

void __systick_handler() {
    __disable_irq();
    llib::rtos::scheduler::tick();
    __enable_irq();
}

void __pendsv_handler() {
    using namespace llib::rtos;

    switch_task(
        scheduler::current_thread->sp,
        *scheduler::next_thread->sp
    );
}