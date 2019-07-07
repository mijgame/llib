#ifndef LLIB_PROMISE_HPP
#define LLIB_PROMISE_HPP

#include <algorithm>
#include "thread.hpp"
#include "rtos.hpp"

#if 0
namespace llib::rtos {
    template<typename T>
    class promise_base {
    protected:
        volatile thread *th;
        bool resolved = false;

        promise_base() {
            th = current_thread();
        }

        void resolve() {
            resolved = true;
            th->resume();
        }

    public:
        void wait() {
            while (!resolved) {
                th->suspend();
            }
        }
    };

    template<typename T>
    class promise : public promise_base<T> {
    protected:
        T value;

    public:
        promise() : promise_base<T>() {}

        void set_value(const T &v) {
            value = v;
            this->resolve();
        }

        void set_value(T &&v) {
            value = std::move(v);
            this->resolve();
        }

        T get() {
            this->wait();
            return value;
        }
    };

    template<typename T>
    class promise<T &> : public promise_base<T &> {
    protected:
        /**
         * This is a pointer, but the actual templated
         * type is a reference type. The pointer is only used
         * for storage and is guaranteed to be set upon
         * releasing data to the client.
         */
        T *value;

    public:
        promise() : promise_base<T &>() {}

        void set_value(T &val) {
            value = &val;
            this->resolve();
        }

        T &get() {
            this->wait();
            return *value;
        }
    };

    template<>
    class promise<void> : public promise_base<void> {
    public:
        promise() : promise_base<void>() {}

        void set_value() {
            this->resolve();
        }

        void get() {
            this->wait();
        }
    };
}
#endif

#endif //LLIB_PROMISE_HPP
