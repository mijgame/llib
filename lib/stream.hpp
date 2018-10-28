#ifndef LLIB_STREAM_HPP
#define LLIB_STREAM_HPP

#include <stdio.h>

#include "uart.hpp"

namespace llib {
    struct ostream {
    };
    struct istream {
    };

    constexpr ostream cout;
    constexpr istream cin;

    ostream operator<<(ostream str, char c) {
        uart::put_char(c);
        return str;
    }

    ostream operator<<(ostream str, bool v) {
        uart::put_char(v ? '1' : '0');
        return str;
    }

    ostream operator<<(ostream str, const char *s) {
        for (const char *p = s; *p != '\0'; p++) {
            str << *p;
        }

        return str;
    }

    ostream operator<<(ostream str, int v) {
        char buf[22];
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
        do { //Move back, inserting digits as u go
            *--p = char(v % 10) + '0';
            v /= 10;
        } while (v);

        return str;
    }
}

#endif //LLIB_STREAM_HPP
