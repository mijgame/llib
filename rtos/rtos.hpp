#ifndef LLIB_RTOS_HPP
#define LLIB_RTOS_HPP

#include <bitset.hpp>
#include <dynamic_array.hpp>
#include <cstddef>
#include <tuple>
#include <brigand.hpp>
#include <wait.hpp>

extern "C" {
// Pre-declaration for friend
void __pendsv_handler();

void switch_task(
    uint32_t *old_sp,
    uint32_t new_sp
);
}


namespace llib::rtos {
    namespace {
        void task_trampoline();
    }

    // Pre-declaration for friend
    template<typename ...Tasks>
    class scheduler;

    class task_base {
    protected:
        // Stack pointer
        uint32_t sp;

        friend void ::__pendsv_handler();

    public:
        virtual void run() = 0;

        virtual void suspend() = 0;

        virtual void resume() = 0;

        virtual bool ready_to_run() const = 0;

        virtual uint8_t get_priority() const = 0;
    };

    template<uint8_t Priority, uint32_t StackSize = 2048>
    class task : public task_base {
    private:
        constexpr static uint32_t stack_words = (StackSize + 3) / 4;
        constexpr static uint32_t marker = 0xDEADBEEF;

        bool ready = true;

        // Stack memory for this task
        uint32_t stack[stack_words] = {};

    public:
        /*
         * The priority of this task.
         * 0 = the highest priority
         * 255 = the lowest priority
         */
        constexpr static uint8_t priority = Priority;

        task() {
            // Fill up all stack locations with a marker
            for (size_t i = 0; i < stack_words; ++i) {
                stack[i] = marker;
            }

            // software stacking (r4 - r11) + 
            // hardware stacking (r0 - r3 + r12 + lr + pc + stack) = 16
            sp = reinterpret_cast<uint32_t>(&stack[stack_words - 16]);  

            auto *stack_ptr = reinterpret_cast<uint32_t*>(sp);
            auto task_tram = reinterpret_cast<uint32_t>(task_trampoline);

            // set reg 12
            stack_ptr[12] = 0x00;                                                
            // lr register
            stack_ptr[13] = task_tram;
            // pc register
            stack_ptr[14] = task_tram;
            // stack register
            stack_ptr[15] = sp;
        }

        /**
         * Suspend the task.
         */
        void suspend() override {
            ready = false;
        }

        /**
         * Allow this task to be scheduled
         * again.
         */
        void resume() override {
            ready = true;
        }

        /**
         * Is this task ready to run?
         *
         * @return
         */
        bool ready_to_run() const override {
            return ready;
        }

        /**
         * Get the priority of this task.
         *
         * @return
         */
        uint8_t get_priority() const override {
            return Priority;
        }
    };

    class scheduler_base {
    protected:
        task_base *current = nullptr;
        task_base *next = nullptr;

        friend void ::__pendsv_handler();

    public:
        static scheduler_base *instance;

        virtual void tick() = 0;

        virtual task_base *get_current_task() = 0;
    };

    namespace {
        /**
         * The idle task is a task that is run when
         * there is no other work to do. It is responsible
         * for the "idle action", like sleeping the processor.
         */
        class idle_task : public task<255> {
        public:
            idle_task() : task<255>() {}

            void run() override {
                for (;;) {
                    llib::cout << "idle\n";
                    //__WFE();
                }
            }

            /**
             * The idle task is always ready
             * to run.
             *
             * @return
             */
            bool ready_to_run() const override {
                return true;
            }
        };

        /**
         * Helper function that calls run
         * on the current task.
         */
        void task_trampoline() {
            llib::cout << "trampoline\n";
            auto *task = scheduler_base::instance->get_current_task();
            task->run();
        }
    }

    /**
     * Compare helper to sort tasks based on
     * their priority.
     */
    template<typename Left, typename Right>
    using compare_task_priority = brigand::bool_<
        (Left::priority < Right::priority)
    >;

    template<typename ...Tasks>
    class scheduler : public scheduler_base {
    protected:
        constexpr static size_t stack_size = 32;
        /**
         * Stack for last function calls in the run function as 
         * we switch to a different stack.
         * 
         * We need at least 8 bytes for a interrupt. The rest is
         * uncalculated and may not be enough.
         * 
         */
        const uint32_t stack[stack_size] = {};

        /**
         * Tasks are sorted by their priority, from
         * smallest number (highest priority) to the
         * largest number (lowest priority).
         */
        using SortedTasks = brigand::sort<
            brigand::push_back<
                brigand::list<
                    std::decay_t<Tasks>...
                >,

                // The idle task is inserted
                idle_task
            >,
            brigand::bind<
                compare_task_priority,
                brigand::_1,
                brigand::_2
            >
        >;

        // Tuple helps with getting indices
        using TasksTuple = brigand::as_tuple<SortedTasks>;

        dynamic_array<
            task_base *,
            std::tuple_size_v<TasksTuple>
        > tasks;

        // Storage for the idle task.
        idle_task idle;

        void schedule_cycle() const {
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

    public:
        /**
         * Instantiate the scheduler with all tasks.
         * The tasks will be taken in by ref.
         *
         * Currently, there is a limitation where the
         * tasks have to be passed in order of priority.
         *
         * @param t
         */
        explicit scheduler(Tasks &...t) {
            /*
             * Currently, a static assert is used
             * to check if the user passed the tasks in
             * the correct order.
             *
             * Maybe it is possible in the future to sort
             * the variadic argument pack with values such that
             * the user could pass the tasks in any order desired?
             */
            static_assert(
                std::is_same_v<
                    std::tuple<Tasks..., idle_task>,
                    TasksTuple
                >,
                "The tasks should be passed in order of their priority."
            );

            static_assert(
                (std::is_base_of_v<task_base, Tasks> && ...),
                "All tasks should inherit from task_base"
            );

            (tasks.push_back(&t), ...);
            tasks.push_back(&idle);
        }

        /**
         * Called by the PendSV handler, will
         * check if any task with a higher priority is
         * ready to run.
         */
        void tick() override {
            llib::cout << "tick\n";

            /*
             * Tasks are sorted by priority, find the
             * next task to run. If no user tasks are ready to
             * run, the idle task is used.
             *
             * This is because the idle task is the last
             * element in the list and always ready to run.
             */

            for (task_base *task : tasks) {
                if (!task->ready_to_run()) {
                    continue;
                }

                /*
                 * Are we currently running the
                 * task that has the highest priority?
                 */
                if (task == current) {
                    return; // Nothing to do
                }

                llib::cout << "Switching task\n";

                // Schedule the task to be run
                next = task;
                schedule_cycle();

                break;
            }
        }

        /**
         * Get a pointer to the current
         * task.
         *
         * @return
         */
        task_base *get_current_task() override {
            return current;
        }

        /**
         * Run the scheduler.
         *
         * This should not return, as it is possible
         * that the scheduler will go out of scope.
         */
        void run(const size_t tps = 1000) {
            // Set this scheduler as the current scheduler.
            instance = this;

            // Give the current thread an initial
            // value of the idle thread.
            current = tasks[tasks.size() - 1];

            llib::wait_for(llib::us{10});

            /// Important: instance and current have to be set before interrupts run!  ///

            // set the process stack pointer to a memory location.
            // this is done so we dont use any stack we don't know.
            __set_PSP(reinterpret_cast<uint32_t>(&stack[stack_size - 1]));

            // Set up SysTick to trigger "tps" times per second
            SysTick_Config(CHIP_FREQ_CPU_MAX / tps);

            // Set the PendSV interrupt to the lowest priority
            NVIC_SetPriority(PendSV_IRQn, 0xFFU);

            // enable the process stack
            __set_CONTROL(__get_CONTROL() | 0x1 << 1);

            // ISB instruction must be emitted immediately after
            // MSR to ensure the new stack pointer is used
            __ISB();

            // Infinite loop, that should never
            // be actually run except for a short moment
            // at startup.
            for (;;) {}
        }
    };
}
#endif //LLIB_RTOS_HPP
