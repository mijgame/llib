#ifndef LLIB_THREAD_HPP
#define LLIB_THREAD_HPP

#include <cstddef>
#include <cstdint>

#include "rtos.hpp"

#if 0
namespace llib::rtos {
    template<size_t StackSize>
    class thread {
    public:
        // Stack size in bytes, must be divisible by four
        constexpr static uint32_t stack_size = StackSize;
        constexpr static uint32_t stack_words = stack_size / 4;

    protected:
        // Stack TEMP
        uint32_t stack[stack_words];

        // Stack pointer
        uint32_t *sp;

        // Timeout down counter
        uint32_t timeout;

        // Handler
        task *t;

        // The id the scheduler has assigned to this thread
        uint8_t id;

        // Allow the pendsv handler to access the
        // stack pointer
        friend void ::__pendsv_handler();

    public:
        explicit thread(task *t)
            : t(t) { }

        void start() {
            stack[stack_words - 1] = reinterpret_cast<uint32_t>(&task::work);
            sp = reinterpret_cast<uint32_t*>(&stack[stack_words - 10]);
            id = scheduler::register_thread(this);
        }

        void suspend() volatile {
            scheduler::ready_to_run.reset(id);
        }

        bool is_suspended() const volatile {
            return scheduler::ready_to_run.test(id);
        }

        void resume() volatile {
            scheduler::ready_to_run.set(id);
        }
    };
}
#endif
#endif //LLIB_THREAD_HPP
