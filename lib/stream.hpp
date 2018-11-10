#ifndef LLIB_STREAM_HPP
#define LLIB_STREAM_HPP

#include <cmath>
#include <stdio.h>
#include <limits>

#include "math.hpp"
#include "uart.hpp"

namespace llib {
    enum class base {
        HEX,
        DEC,
        OCT,
        BIN
    };

    template<base B = base::DEC, bool Boolalpha = false>
    struct ostream {
        constexpr static llib::base base = B;
        constexpr static bool boolalpha = Boolalpha;
    };

    struct istream {
    };

    constexpr ostream cout;

    struct _boolalpha {};
    constexpr _boolalpha boolalpha;

    struct hex {};
    struct dec {};
    struct oct {};
    struct bin {};

    constexpr istream cin;

    constexpr char endl = '\n';

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, char c) {
        uart::put_char(c);
        return str;
    }

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, bool v) {
        if constexpr (OutputStream::boolalpha) {
            str << (v ? "true" : "false");
        } else {
            uart::put_char('0' + v);
        }

        return str;
    }

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, char *s) {
        for (char *p = s; *p != '\0'; p++) {
            uart::put_char(*p);
        }

        return str;
    }

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, const char *s) {
        for (const char *p = s; *p != '\0'; p++) {
            uart::put_char(*p);
        }

        return str;
    }

    template<
            typename T,
            typename OutputStream,
            typename = std::enable_if_t<std::is_integral_v<T>>
    >
    OutputStream operator<<(OutputStream str, T v) {
        /*
         * The buffer wil be the maximum amount of digits in the type
         * + a optional leading '-' or '+' + a \0.
         */
        char buf[std::numeric_limits<T>::max_digits10 + 2];
        char *p = buf;

        if (v < 0) {
            *p++ = '-';
            v *= -1;
        }

        int shifter = v;

        // Move to where representation ends
        do {
            ++p;
            shifter /= 10;
        } while (shifter);

        *p = '\0';
        do { // Move back, inserting digits
            *--p = char(v % 10) + '0';
            v /= 10;
        } while (v);

        str << buf;

        return str;
    }

    template<typename OutputStream>
    auto operator<<(OutputStream, _boolalpha) {
        return ostream<OutputStream::base, true>();
    }
}

#endif //LLIB_STREAM_HPP
