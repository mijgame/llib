#ifndef LLIB_STREAM_HPP
#define LLIB_STREAM_HPP

#include <type_traits>
#include <stdio.h>

#include "base.hpp"
#include "stream_base.hpp"

#include <stream_target.hpp>

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

    namespace {
        /**
         * Reverse a char buffer.
         *
         * @internal
         * @param str
         * @param length
         * @return
         */
        constexpr void _reverse(char *str, const int length) {
            int start = 0;
            int end = length - 1;

            while (start < end) {
                char temp = *(str + start);
                *(str + start++) = *(str + end);
                *(str + end--) = temp;
            }
        }

        /**
         * Add the prefix to the output stream.
         *
         * @internal
         * @param str
         * @param base
         * @return
         */
        constexpr int _add_prefix(char *str, int base) {
            char *p = str;

            if (base == 8) {
                *p++ = 'b';
                *p = '0';

                return 2;
            }

            if (base == 16) {
                *p++ = 'x';
                *p = '0';

                return 2;
            }

            return 0;
        }

        /**
         * Internal itoa for stream output.
         *
         * @internal
         * @param num
         * @param str
         * @param base
         * @return
         */
        constexpr char *_itoa(int num, char *str, int base) {
            // Handle 0 explicitly, otherwise empty string is printed for 0
            if (num == 0) {
                str[0] = '0';
                int added = _add_prefix(&str[1], base);

                str[added + 1] = '\0';

                return str;
            }

            int i = 0;
            bool negative = false;

            // In standard itoa(), negative numbers are handled only with
            // base 10. Otherwise numbers are considered unsigned.
            if (num < 0 && base == 10) {
                negative = true;
                num = -num;
            }

            // Process individual digits
            while (num != 0) {
                int rem = num % base;

                if (rem > 9) {
                    str[i++] = '0' + (rem - 10);
                } else {
                    str[i++] = '0' + rem;
                }

                num /= base;
            }

            // If number is negative, append '-'
            if (negative) {
                str[i++] = '-';
            }

            // For hex, append 0x
            int added = _add_prefix(&str[i], base);
            str[i += added] = '\0'; // Append string terminator

            // Reverse the string
            _reverse(str, i);

            return str;
        }

        /**
         * Helper function that counts the amount of characters in the
         * positive representation of the given number.
         *
         * @internal
         * @tparam T
         * @param v
         * @return
         */
        template<typename T>
        constexpr int _count_chars(T v, const int base) {
            if (v < 0) {
                v *= -1;
            }

            int chars = 0;
            while (v) {
                chars += 1;
                v /= base;
            }

            return chars;
        }

        /**
         * Convert a integral numeric value to a binary
         * representation with leading zero's.
         *
         * @internal
         * @tparam T
         * @param v
         * @param buffer
         */
        template<typename T>
        void _integral_to_bin_buffer(T v, char *buffer) {
            char *p = buffer;

            // TODO: showbase
            *p++ = '0';
            *p++ = 'b';

            for (int i = sizeof(T) * 8; i != 0; i--) {
                *p++ = ((v >> i) & 0x1) ? '1' : '0';
            }

            *p = '\0';
        }
    }

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
        if constexpr(OutputStream::base == base::HEX) {
            /*
             * A single hex char describes a nibble, so
             * sizeof(T) * 2 will hold the hex representation and
             * the +3 is for the leading 0x and trailing \0.
             */
            char buf[sizeof(T) * 2 + 3];
            _itoa(v, buf, 16);
            str << buf;
        } else if constexpr (OutputStream::base == base::DEC) {
            /*
             * The buffer wil be the maximum amount of digits in the type
             * + a optional leading '-' or '+' + a \0.
             */
            char buf[_count_chars(v, 10) + 2] = {};
            _itoa(v, buf, 10);
            str << buf;
        } else if constexpr (OutputStream::base == base::OCT) {
            /*
             * A char is needed for each 3 bits + 3 for the leading
             * 0o and the trailing \0.
             */
            char buf[sizeof(T) * 3 + 3];
            _itoa(v, buf, 8);
            str << buf;
        } else {
            // binary
            /*
             * A char is needed for each bit + 3 for the leading
             * 0b and trailing \0.
             */
            char buf[sizeof(T) * 8 + 3];
            _integral_to_bin_buffer(v, buf);
            str << buf;
        }

        return str;
    }

    /**
     * Output numbers as hexadecimal for this
     * stream.
     *
     * @tparam OutputStream
     * @return
     */
    template<typename OutputStream>
    auto operator<<(OutputStream, _hex) {
        return typename OutputStream::template instance<base::HEX, OutputStream::boolalpha>();
    }

    /**
     * Output numbers as decimal for this
     * stream.
     *
     * @tparam OutputStream
     * @return
     */
    template<typename OutputStream>
    auto operator<<(OutputStream, _dec) {
        return typename OutputStream::template instance<base::DEC, OutputStream::boolalpha>();
    }

    /**
     * Output numbers as octal for
     * this stream.
     *
     * @tparam OutputStream
     * @return
     */
    template<typename OutputStream>
    auto operator<<(OutputStream, _oct) {
        return typename OutputStream::template instance<base::OCT, OutputStream::boolalpha>();
    }

    /**
     * Output numbers as binary for
     * this stream.
     *
     * @tparam OutputStream
     * @return
     */
    template<typename OutputStream>
    auto operator<<(OutputStream, _bin) {
        return typename OutputStream::template instance<base::BIN, OutputStream::boolalpha>();
    }

    /**
     * Output booleans as 'true' and 'false'
     * for this stream.
     *
     * @tparam OutputStream
     * @return
     */
    template<typename OutputStream>
    auto operator<<(OutputStream, _boolalpha) {
        return typename OutputStream::template instance<OutputStream::base, true>();
    }
}

#endif //LLIB_STREAM_HPP
