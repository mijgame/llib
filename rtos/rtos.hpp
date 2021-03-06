#ifndef LLIB_RTOS_HPP
#define LLIB_RTOS_HPP

#include <bitset.hpp>
#include <dynamic_array.hpp>
#include <cstddef>
#include <tuple>
#include <brigand.hpp>
#include <wait.hpp>

namespace llib::rtos {
    class task_base;

    struct _switch_helper {
        uint32_t *old_sp;
        uint32_t new_sp;
        task_base **current;
        task_base **next;
    };
}

extern volatile llib::rtos::_switch_helper _switch;

namespace llib::rtos {
    namespace {
        void task_trampoline();

        template <class T, class Tuple>
        struct tuple_index;

        template <class T, class... Types>
        struct tuple_index<T, std::tuple<T, Types...>> {
            static const std::size_t value = 0;
        };

        template <class T, class U, class... Types>
        struct tuple_index<T, std::tuple<U, Types...>> {
            static const std::size_t value = 1 + tuple_index<T, std::tuple<Types...>>::value;
        };

        template <class T, class Tuple>
        constexpr size_t tuple_index_v = tuple_index<T, Tuple>::value;
    }

    // Pre-declaration for friend
    template<typename ...Tasks>
    class scheduler;

    class task_base {
    protected:
        // Stack pointer
        uint32_t sp = 0;

        template<typename ...Tasks>
        friend
        class scheduler;

    public:
        virtual void run() = 0;

        virtual void suspend() = 0;

        virtual void yield() = 0;

        virtual void unyield() = 0;

        virtual void resume() = 0;

        virtual bool ready_to_run() const = 0;

        virtual bool yielded() const = 0;

        virtual uint8_t get_priority() const = 0;
    };

    template<uint8_t Priority, uint32_t StackSize = 2048>
    class task : public task_base {
    private:
        constexpr static uint32_t stack_words = (StackSize + 3) / 4;

        bool ready = true;
        bool currently_yielded = false;

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
            // software stacking (r4 - r11) + 
            // hardware stacking (r0 - r3 + r12 + lr + pc + stack) = 16
            sp = reinterpret_cast<uint32_t>(&stack[stack_words - 16]);

            auto *stack_ptr = reinterpret_cast<uint32_t *>(sp);
            auto task_tram = reinterpret_cast<uint32_t>(task_trampoline);

            // reg 0
            stack_ptr[8] = 0x00000000;
            // reg 1
            stack_ptr[9] = 0x11111111;
            // reg 2
            stack_ptr[10] = 0x22222222;
            // reg 3
            stack_ptr[11] = 0x33333333;

            // set reg 12
            stack_ptr[12] = 0x00;
            // lr register
            stack_ptr[13] = task_tram;
            // pc register
            stack_ptr[14] = task_tram;
            // xpsr register
            stack_ptr[15] = 0x1000000;
        }

        /**
         * Suspend the task.
         */
        void suspend() override {
            ready = false;
        }

        /**
         * Yield the current task.
         * When is task is yielded, for one cycle
         * it won't be considered ready to run, allowing
         * other tasks to execute work.
         *
         * This is handy when the task needs to periodically
         * check for progress, while not suspending (which would rely
         * on an external factor to unsuspend the task).
         *
         * If a task is yielded but not ready to run,
         * it is only unyielded when it is ready to run again.
         */
        void yield() override;

        /**
         * Unyield the current task.
         */
        void unyield() override {
            currently_yielded = false;
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
         * Is this task currently yielded?
         *
         * @return
         */
        bool yielded() const override {
            return currently_yielded;
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

    public:
        static scheduler_base *instance;

        virtual void tick() = 0;

        virtual task_base *get_current_task() = 0;

        virtual void request_cycle() = 0;
    };

    /**
     * @tparam Priority
     * @tparam StackSize
     */
    template<uint8_t Priority, uint32_t StackSize>
    void task<Priority, StackSize>::yield() {
        currently_yielded = true;
        scheduler_base::instance->request_cycle();
    }

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
                    __WFE();
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
        /**
         * 16 for all registers + 1 for SP
         */
        constexpr static size_t stack_size = 17;

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

        constexpr static size_t task_count = std::tuple_size_v<TasksTuple>;

        dynamic_array<task_base *, task_count> tasks;

        // Storage for the idle task.
        idle_task idle;

        void schedule_cycle() const {
            _switch.old_sp = &current->sp;
            _switch.new_sp = next->sp;

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
            static_assert(
                (std::is_base_of_v<task_base, Tasks> && ...),
                "All tasks should inherit from task_base"
            );

            // Pre-size the array to the task count
            tasks.resize(task_count);

            // Because the index of the task is known at compile time,
            // the user can pass the tasks in any way they like and this
            // will put them in the right place in the tasks array.
            (
                tasks.set(tuple_index_v<typeof(t), TasksTuple>, &t),
                ...
            );

            tasks.set(task_count - 1, &idle);
        }

        /**
         * Called by the PendSV handler, will
         * check if any task with a higher priority is
         * ready to run.
         */
        void tick() override {
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
                    break; // Nothing to do
                }

                // Schedule the task to be run
                next = task;
                schedule_cycle();

                break;
            }

            for (task_base *task : tasks) {
                if (task->yielded()) {
                    task->unyield();
                }
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
         * Request a scheduling cycle.
         */
        void request_cycle() override {
            tick();
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
            next = current;

            _switch.current = &current;
            _switch.next = &next;

            llib::wait_for(llib::us{10});

            /// Important: instance and current have to be set before interrupts run!  ///

            // set the process stack pointer to a memory location.
            // this is done so we dont use any stack we don't know.
            __set_PSP(reinterpret_cast<uint32_t>(&stack[stack_size - 1]));

            // Set up SysTick to trigger "tps" times per second
            SysTick_Config(CHIP_FREQ_CPU_MAX / tps);

            // Set the PendSV interrupt to the lowest priority
            NVIC_SetPriority(PendSV_IRQn, 0x0F);
            NVIC_SetPriority(SysTick_IRQn, 0x01);

            // enable the process stack
            __set_CONTROL(__get_CONTROL() | (0x1U << 1U));

            // ISB instruction must be emitted immediately after
            // MSR to ensure the new stack pointer is used
            __ISB();
            __DSB();

            // Infinite loop, that should never
            // be actually run except for a short moment
            // at startup.
            for (;;) {}
        }
    };
}
#endif //LLIB_RTOS_HPP
