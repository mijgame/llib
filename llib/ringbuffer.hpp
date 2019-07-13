#ifndef LLIB_RINGBUFFER_HPP
#define LLIB_RINGBUFFER_HPP

#include <cstddef>
#include <utility>

namespace llib {
    /**
     * Simple ringbuffer implementation.
     *
     * @tparam T
     * @tparam MaxSize
     */
    template<typename T, size_t MaxSize>
    class ringbuffer {
    protected:
        T buffer[MaxSize] = {};

        size_t head = 0;
        size_t tail = 0;
        size_t used = 0;

        /**
         * Get the index at which a
         * item can be stored.
         *
         * @return size_t
         */
        constexpr size_t get_next_location() {
            if (tail >= MaxSize) {
                tail = 0;
            }

            size_t prev_tail = tail++;

            if (full()) {
                tail = head;
                head = (head + 1) % MaxSize;
            } else {
                used += 1;
            }

            return prev_tail;
        }

    public:
        /**
         * Default constructor.
         */
        constexpr ringbuffer() = default;

        /**
         * Copy constructor.
         *
         * @param other
         */
        constexpr ringbuffer(const ringbuffer &other) {
            // Maybe a bit lazy; just copy all the elements
            for (size_t i = 0; i < MaxSize; i++) {
                buffer[i] = other.buffer[i];
            }

            head = other.head;
            tail = other.tail;
            used = other.used;
        }

        /**
         * Move constructor.
         *
         * @param other
         */
        constexpr ringbuffer(ringbuffer &&other) noexcept {
            buffer = std::move(other.buffer);

            head = std::move(other.head);
            tail = std::move(other.tail);
            used = std::move(other.used);
        }

        /**
         * Add an item to the ringbuffer.
         *
         * @param val
         * @return
         */
        constexpr T &push(const T &val) {
            const auto index = get_next_location();

            buffer[index] = val;

            return buffer[index];
        }

        /**
         * Emplace an item into the ringbuffer.
         *
         * @tparam Args
         * @param args
         * @return constexpr T&
         */
        template<typename ...Args>
        constexpr T &emplace(Args &&...args) {
            const auto index = get_next_location();
            buffer[index] = T(std::forward<Args>(args)...);

            return buffer[index];
        }

        /**
         * Pop a value from the buffer.
         *
         * @return
         */
        constexpr void pop() {
            if (!used) {
                // At last item
                return;
            }

            // Remove last item
            used--;

            // Move tail back 1 or back to maxsize - 1
            if (!(tail)) {
                tail = MaxSize - 1;
            } else {
                tail--;
            }
        }

        /**
         * Copy the last item from the buffer
         * and pop.
         *
         * @return
         */
        constexpr T copy_and_pop() {
            size_t pos = 0;

            // Get previous position
            if (tail) {
                pos = tail - 1;
            } else {
                // Tail is at 0, shift to end
                pos = MaxSize - 1;
            }

            T item = buffer[pos];

            pop();

            return item;
        }

        /**
         * Get a reference to the item
         * at the front of the buffer.
         *
         * @return
         */
        constexpr T &front() {
            return buffer[head];
        }

        /**
         * Get a reference to the item
         * at the back of the buffer.
         *
         * @return
         */
        constexpr T &back() {
            return buffer[tail];
        }

        /**
         * Copy the first item from the buffer and pop.
         *
         * @return constexpr T
         */
        constexpr T copy_and_pop_front() {
            // Get the data on head
            T item = buffer[head];

            // move the head to its new location
            if (head < (MaxSize - 1)) {
                head++;
            } else {
                head = 0;
            }

            used--;

            return item;
        }

        /**
         * Reset (empty) the ringbuffer.
         *
         * @return
         */
        constexpr void reset() {
            head = 0;
            tail = 0;
            used = 0;
        }

        /**
         * Get the value at the given index.
         *
         * @param index
         * @return
         */
        constexpr T &operator[](const size_t index) {
            return buffer[(head + index) % MaxSize];
        }

        /**
         * Get the value at the given index.
         *
         * @param index
         * @return
         */
        constexpr T const &operator[](const size_t index) const {
            return buffer[(head + index) % MaxSize];
        }

        /**
         * Return whether the ringbuffer is empty.
         *
         * @return
         */
        constexpr bool empty() const {
            return used == 0;
        }

        /**
         * Return whether the ringbuffer is full.
         *
         * @return
         */
        constexpr bool full() const {
            return used == MaxSize;
        }

        /**
         * Get the current size of the ringbuffer.
         *
         * @return
         */
        constexpr size_t size() const {
            return used;
        }

        /**
         * Get the maximum size of the ringbuffer.
         *
         * @return
         */
        constexpr size_t max_size() const {
            return MaxSize;
        }

        /**
         * Swap two ringbuffers.
         *
         * @param other
         * @return
         */
        constexpr void swap(ringbuffer &other) noexcept {
            std::swap(buffer, other.buffer);
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(used, other.used);
        }
    };
}

#endif //LLIB_RINGBUFFER_HPP
