#ifndef LLIB_TEENSY_STREAM_HPP
#define LLIB_TEENSY_STREAM_HPP

#include "stream_base.hpp"

namespace llib::due {
    namespace detail {
        // todo: implement write and read
        void write_impl(char c);
        char read_impl();
    }

    template<base B = _default_base, bool Boolalpha = _default_boolalpha>
    struct cout : public ostream<B, Boolalpha> {
        template<llib::base IB, bool IBoolalpha>
        using instance = cout<IB, IBoolalpha>;

        void putc(char c) const {
            detail::write_impl(c);
        }
    };

    class cin : public istream {
    protected:
        bool good_bit = true;

    public:
        using instance = cin;

        operator bool() const {
            return good_bit;
        }

        char getc() {
            char c = detail::read_impl();
            good_bit = !(c == '\n' || c == '\0' || c == ' ');
            return c;
        }
    };
}

#endif //LLIB_TEENSY_STREAM_HPP
