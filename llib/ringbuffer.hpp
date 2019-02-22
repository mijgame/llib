#ifndef LLIB_RINGBUFFER_HPP
#define LLIB_RINGBUFFER_HPP

#include <cstddef>

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

    public:
        /**
         * Default constructor.
         */
        constexpr ringbuffer() = default;

        /**
         * Add an item to the ringbuffer.
         *
         * @param val
         * @return
         */
        constexpr void push(const T &val) {
            if (tail >= MaxSize) {
                tail = 0;
            }

            buffer[tail++] = val;

            if (full()) {
                head = (head + 1) % MaxSize;
            } else {
                used += 1;
            }
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
    };
}

#endif //LLIB_RINGBUFFER_HPP
