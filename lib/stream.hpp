#ifndef LLIB_STREAM_HPP
#define LLIB_STREAM_HPP

#include <cmath>
#include <stdio.h>
#include <limits>

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

        return str;
    }

    ostream operator<<(ostream str, double v) {
        constexpr double precision = 0.00000000000001;
        constexpr int max_string_size = 32;

        char buf[max_string_size];

        if (std::isnan(v)) {
            str << "NaN";
        } else if (std::isinf(v)) {
            str << "inf";
        } else if (v == 0.0) {
            str << 0;
        } else {
            int digit, m, m1;
            char *c = buf;

            bool neg = v < 0;
            if (neg) {
                v = -v;
            }

            // Calculate magnitude
            m = std::log10(v);
            bool useExp = (m >= 14 || (neg && m >= 9) || m <= -9);

            if (neg) {
                *(c++) = '-';
            }

            // Scientific notation
            if (useExp) {
                if (m < 0) {
                    m -= 1.0;
                }

                v /= std::pow(10.0, m);
                m1 = m;
                m = 0;
            }

            if (m < 1.0) {
                m = 0;
            }

            // Convert the number
            while (v > precision || m >= 0) {
                double weight = pow(10.0, m);
                if (weight > 0 && !std::isinf(weight)) {
                    digit = std::floor(v / weight);
                    v -= (digit * weight);
                    *(c++) = '0' + digit;
                }

                if (m == 0 && v > 0) {
                    *(c++) = '.';
                }

                m--;
            }

            if (useExp) {
                *(c++) = 'e';

                if (m1 > 0) {
                    *(c++) = '+';
                } else {
                    *(c++) = '-';
                    m1 = -m1;
                }

                m = 0;
                while (m1 > 0) {
                    *(c++) = '0' + (m1 % 10);
                    m1 /= 10;
                    m++;
                }

                c -= m;
                for (int i = 0, j = m - 1; i < j; i++, j--) {
                    c[i] ^= c[j];
                    c[j] ^= c[i];
                    c[i] ^= c[j];
                }

                c += m;
            }

            *(c) = '\0';
        }

        return str;
    }

    ostream operator<<(ostream str, float v) {
        str << static_cast<double>(v);
        return str;
    }
}

#endif //LLIB_STREAM_HPP
