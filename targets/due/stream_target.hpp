#ifndef LLIB_DUE_STREAM_HPP
#define LLIB_DUE_STREAM_HPP

#include "stream_base.hpp"

namespace llib::due {
    namespace detail {
        void write_impl(char c);
        char read_impl();
    }

    template<base B = _default_base, bool Boolalpha = _default_boolalpha>
    struct cout : public ostream<B, Boolalpha> {
        template<llib::base IB, bool IBoolalpha>
        using instance = cout<IB, IBoolalpha>;

        void putc(char c) {
            detail::write_impl(c);
        }
    };

    struct cin : public istream {
        using instance = cin;

        char getc() {
            return detail::read_impl();
        }
    };
}

#endif //LLIB_DUE_STREAM_HPP
