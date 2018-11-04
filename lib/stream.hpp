#ifndef LLIB_STREAM_HPP
#define LLIB_STREAM_HPP

#include <cmath>
#include <stdio.h>
#include <limits>

#include "math.hpp"
#include "uart.hpp"

namespace llib {
    struct ostream {
    };
    struct istream {
    };

    constexpr ostream cout;
    constexpr istream cin;

    constexpr char endl = '\n';

    ostream operator<<(ostream str, char c) {
        uart::put_char(c);
        return str;
    }

    ostream operator<<(ostream str, bool v) {
        uart::put_char(v ? '1' : '0');
        return str;
    }

    ostream operator<<(ostream str, char *s) {
        for (char *p = s; *p != '\0'; p++) {
            str << *p;
        }

        return str;
    }

    ostream operator<<(ostream str, const char *s) {
        for (const char *p = s; *p != '\0'; p++) {
            str << *p;
        }

        return str;
    }

    template<
            typename T,
            typename = std::enable_if_t<std::is_integral_v<T>>
    >
    ostream operator<<(ostream str, T v) {
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
}

#endif //LLIB_STREAM_HPP
