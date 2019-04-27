#ifndef LLIB_QUEUE_HPP
#define LLIB_QUEUE_HPP

#include "dynamic_array.hpp"

namespace llib {
    /**
     * Simple queue build on a dynamic array.
     * This is a convenience implementation.
     *
     * The tparam WriteOptimized controls whether insertions
     * or deletions are fast. Because of the underlying array structure,
     * on either insertion or deletion the array contents need to be shuffled
     * around in memory. Setting write optimized to false would instruct
     * the queue to shuffle around memory on insertion and simply reduce
     * the memory size on pop.
     *
     * @tparam T
     * @tparam MaxSize
     * @tparam WriteOptimized
     */
    template<typename T, size_t MaxSize, bool WriteOptimized = true>
    class queue {
    protected:
        dynamic_array<T, MaxSize> store;

    public:
        /**
         * Default constructor.
         */
        constexpr queue() = default;

        /**
         * Copy constructor.
         *
         * @param other
         */
        constexpr queue(const queue &other) {
            store = other.store;
        }

        /**
         * Move constructor.
         *
         * @param other
         */
        constexpr queue(queue &&other) {
            store = std::move(other.store);
        }

        /**
         * Push a value onto the queue.
         *
         * @param val
         * @return
         */
        constexpr void push(const T &val) {
            if constexpr (WriteOptimized) {
                store.push_back(val);
            } else {
                store.insert(store.begin(), val);
            }
        }

        /**
         * Push a value onto the queue.
         *
         * @param val
         * @return
         */
        constexpr void push(T &&val) {
            if constexpr (WriteOptimized) {
                store.push_back(val);
            } else {
                store.insert(store.begin(), val);
            }
        }

        /**
         * Emplace a value onto the queue.
         *
         * @tparam Args
         * @param args
         * @return
         */
        template<typename ... Args>
        constexpr void emplace(Args &&... args) {
            if constexpr (WriteOptimized) {
                store.emplace_back(
                    std::forward<Args>(args)...
                );
            } else {
                store.emplace(
                    0, std::forward<Args>(args)...
                );
            }
        }

        /**
         * Copy the value at the front of the queue,
         * pop and return that value.
         *
         * @return
         */
        constexpr T copy_and_pop() {
            T val = front();
            pop();

            return val;
        }

        /**
         * Pop the front of the queue.
         *
         * @return
         */
        constexpr void pop() {
            if constexpr (WriteOptimized) {
                store.pop_front();
            } else {
                store.pop_back();
            }
        }

        /**
         * Whether the queue is empty.
         *
         * @return
         */
        constexpr bool empty() const {
            return store.empty();
        }

        /**
         * The current queue size.
         *
         * @return
         */
        constexpr size_t size() const {
            return store.size();
        }

        /**
         * The maximum size of the queue.
         *
         * @return
         */
        constexpr size_t max_size() const {
            return store.max_size();
        }

        /**
         * Get a reference to the first item in the
         * queue.
         *
         * @return
         */
        constexpr T &front() {
            if constexpr (WriteOptimized) {
                return store.front();
            } else {
                return store.back();
            }
        }

        /**
         * Get a const reference to the first item in the
         * queue.
         *
         * @return
         */
        constexpr T const &front() const {
            if constexpr (WriteOptimized) {
                return store.front();
            } else {
                return store.back();
            }
        }

        /**
         * Get a reference to the last item in the
         * queue.
         *
         * @return
         */
        constexpr T &back() {
            if constexpr (WriteOptimized) {
                return store.back();
            } else {
                return store.front();
            }

        }

        /**
         * Get a const reference to the last item in the
         * queue.
         *
         * @return
         */
        constexpr T const &back() const {
            if constexpr (WriteOptimized) {
                return store.back();
            } else {
                return store.front();
            }
        }

        /**
         * Swap two queues with each other.
         *
         * @param other
         * @return
         */
        constexpr void swap(queue &other) noexcept {
            std::swap(store, other.store);
        }

        /**
         * Clears the queue
         * 
         */
        constexpr void clear() {
            store.clear();
        }
    };
}

#endif //LLIB_QUEUE_HPP
