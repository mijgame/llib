#ifndef LLIB_STREAM_HPP
#define LLIB_STREAM_HPP

#include <cmath>
#include <stdio.h>
#include <limits>

#include "math.hpp"
#include "stream_base.hpp"

#include <stream.hpp>

namespace llib {
    [[maybe_unused]]
    constexpr target::cout cout;

    struct _boolalpha {};

    [[maybe_unused]]
    constexpr _boolalpha boolalpha;

    struct _hex {};

    [[maybe_unused]]
    constexpr _hex hex;

    struct _dec {};

    [[maybe_unused]]
    constexpr _dec dec;

    struct _oct {};

    [[maybe_unused]]
    constexpr _oct oct;

    struct _bin {};

    [[maybe_unused]]
    constexpr _bin bin;

    [[maybe_unused]]
    constexpr istream cin;

    [[maybe_unused]]
    constexpr char endl = '\n';

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, char c) {
        str.write_impl(c);

        return str;
    }

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, bool v) {
        if constexpr (OutputStream::boolalpha) {
            str << (v ? "true" : "false");
        } else {
            str << char('0' + v);
        }

        return str;
    }

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, char *s) {
        for (char *p = s; *p != '\0'; p++) {
            str << *p;
        }

        return str;
    }

    template<typename OutputStream>
    OutputStream operator<<(OutputStream str, const char *s) {
        for (const char *p = s; *p != '\0'; p++) {
            str << *p;
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
        return typename OutputStream::template instance<OutputStream::base, true>();
    }
}

#endif //LLIB_STREAM_HPP
