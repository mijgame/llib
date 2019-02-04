#ifndef LLIB_DUE_STREAM_HPP
#define LLIB_DUE_STREAM_HPP

#include "stream_base.hpp"

namespace llib::due {
    namespace detail {
        void write_impl(char c);
    }

    template<base B = _default_base, bool Boolalpha = _default_boolalpha>
    struct cout : public ostream<B, Boolalpha> {
        template<llib::base IB, bool IBoolalpha>
        using instance = cout<IB, IBoolalpha>;

        void write_impl(char c) {
            detail::write_impl(c);
        }
    };
}

#endif //LLIB_DUE_STREAM_HPP
