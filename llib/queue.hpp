#ifndef LLIB_QUEUE_HPP
#define LLIB_QUEUE_HPP

#include <ringbuffer.hpp>
#include <utility>

namespace llib {
    /**
     * A queue implementation.
     * This queue is based on a ringbuffer, as that offers
     * better performance. This does mean that the underlying memory
     * doesn't act like a queue; if you require this behaviour, please use
     * consistent_queue.
     *
     * @tparam T
     * @tparam MaxSize
     */
    template<typename T, size_t MaxSize>
    class queue {
    protected:
        ringbuffer<T, MaxSize> store;

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
        constexpr queue(queue &&other) noexcept {
            store = std::move(other.store);
        }

        /**
         * Push a value onto the queue.
         *
         * @param val
         * @return
         */
        constexpr void push(const T &val) {
            store.push(val);
        }

        /**
         * Move value onto the queue.
         *
         * @param val
         * @return
         */
        constexpr void push(T &&val) {
            store.push(
                std::move(val)
            );
        }

        /**
         * Emplace a value onto the queue.
         *
         * @tparam Args
         * @param args
         * @return
         */
        template<typename ...Args>
        constexpr void emplace(Args &&... args) {
            store.emplace(
                std::forward<Args>(args)...
            );
        }

        /**
         * Pop an item from the queue.
         * @return
         */
        constexpr void pop() {
            store.pop();
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
         * Get a reference to the item
         * at the front of the queue.
         *
         * @return
         */
        constexpr T &front() {
            return store.front();
        }

        /**
         * Get a constant reference to the item
         * at the front of the queue.
         *
         * @return
         */
        constexpr T const& front() const {
            return store.front();
        }

        /**
         * Get a reference to the item
         * at the back fo the queue.
         *
         * @return
         */
        constexpr T &back() {
            return store.back();
        }

        /**
         * Get a constant reference to the item
         * at the back fo the queue.
         *
         * @return
         */
        constexpr T const& back() const {
            return store.back();
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
         * Clear the queue.
         *
         * @return
         */
        constexpr void clear() {
            store.clear();
        }
    };
}

#endif //LLIB_QUEUE_HPP
