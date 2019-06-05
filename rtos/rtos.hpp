#ifndef LLIB_RTOS_HPP
#define LLIB_RTOS_HPP

#include <bitset.hpp>
#include <dynamic_array.hpp>
#include <cstddef>

// Pre-declaration in global scope
// to allow for friend declaration
void __pendsv_handler();

extern "C" void switch_task(
    uint32_t *old_sp,
    uint32_t new_sp
);

namespace llib::rtos {
    class thread {
    public:
        // Stack size in bytes, must be divisible by four
        constexpr static uint32_t stack_size = 512;
        constexpr static uint32_t stack_words = stack_size / 4;

        using thread_handler = void (*)();

    protected:
        // Stack TEMP
        uint32_t stack[stack_words];

        // Stack pointer
        uint32_t *sp;

        // Timeout down counter
        uint32_t timeout;

        // Handler
        thread_handler handler;

        // The id the scheduler has assigned to this thread
        uint8_t id;

        // Allow the pendsv handler to access the
        // stack pointer
        friend void ::__pendsv_handler();

    public:
        explicit thread(thread_handler handler);

        void start();
    };

    class scheduler {
    protected:
        // 32 user threads + idle thread
        static inline dynamic_array<thread*, 32 + 1> threads;

        static inline bitset<32> ready_to_run;
        static inline uint8_t current_thread_id;

        // Volatile because they are accessed by an
        // interrupt in assembly
        static volatile inline thread *current_thread;
        static volatile inline thread *next_thread;

        // Only allow a thread to register
        // itself
        friend thread;

        // Allow the pendv handler to access
        // the current and next thread pointers.
        friend void ::__pendsv_handler();

        static void on_idle();

        static uint8_t register_thread(thread *th);

        static void schedule_cycle();

    public:
        static void startup(size_t tps = 1000);

        static void tick();
    };
}

#endif //LLIB_RTOS_HPP
