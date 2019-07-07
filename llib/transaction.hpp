#ifndef LLIB_TRANSACTION_HPP
#define LLIB_TRANSACTION_HPP

#include <cstddef>
#include <utility>

namespace llib {
    template<typename Impl>
    class transaction {
    public:
        void wait() {
            Impl::_wait();
        }

        bool done() {
            return Impl::_done();
        }

        size_t remaining() {
            return Impl::_remaining();
        }
    };

    template<typename T>
    class scoped_transaction {
    protected:
        transaction<T> trans;

    public:
        scoped_transaction(transaction<T> trans)
            : trans(trans) { }

        ~scoped_transaction() {
            if (! trans.done()) {
                trans.wait();
            }
        }
    };
}

#endif //LLIB_TRANSACTION_HPP
