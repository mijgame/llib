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

    namespace {
        template<typename T>
        struct _unsigned_type {
            using type = T;
        };

        template<>
        struct _unsigned_type<char> {
            using type = uint8_t;
        };

        template<>
        struct _unsigned_type<signed short> {
            using type = uint16_t;
        };

        template<>
        struct _unsigned_type<signed int> {
            using type = uint32_t ;
        };

        template<>
        struct _unsigned_type<signed long> {
            using type = uint64_t;
        };

        template<typename T>
        using _unsigned_type_t = typename _unsigned_type<T>::type;

        template<typename T>
        void _integral_to_hex_buffer(T v, char *buffer) {
            auto val = static_cast<_unsigned_type_t<T>>(v);

            char *p = buffer;

            // TODO: showbase
            *p++ = '0';
            *p++ = 'x';

            // Convert nibbles
            for (int i = sizeof(val) * 2; i != 0; i--) {
                auto nibble = static_cast<uint8_t>(val >> (i * 4 - 4));

                if (nibble > 9) {
                    *p++ = char('A' + (nibble - 10));
                } else {
                    *p++ = char('0' + nibble);
                }
            }

            *p = '\0';
        }

        template<typename T>
        void _integral_to_dec_buffer(T v, char *p) {
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

            // Move back, inserting digits
            do {
                // Reuse division in modulo
                const auto div = v / 10;

                *(--p) = '0' + (v - 10 * div);
                v /= 10;
            } while (v);
        }

        template<typename T>
        void _integral_to_oct_buffer(T v, char *buffer) {
            auto val = static_cast<_unsigned_type_t<T>>(v);

            char *p = buffer;

            // Move to where representation ends
            int shifter = val; // TODO: int?

            do {
                ++p;
                shifter /= 8;
            } while (shifter);

            p += 2; // Allow for base
            *p = '\0';

            if (val == 0) {
                *p++ = '0';
            } else {
                char remainder;
                while (val > 0) {
                    remainder = (val % 8) + '0';
                    *p-- = remainder;
                    val /= 8;
                }
            }

            // TODO: showbase
            *p-- = 'o';
            *p = '0';
        }

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
             * sizeof(T) * 4 will hold the hex representation and
             * the +3 is for the leading 0x and trailing \0.
             */
            char buf[sizeof(T) * 2 + 3];
            _integral_to_hex_buffer(v, buf);
            str << buf;
        } else if constexpr (OutputStream::base == base::DEC) {
            /*
             * The buffer wil be the maximum amount of digits in the type
             * + a optional leading '-' or '+' + a \0.
             */
            char buf[std::numeric_limits<T>::max_digits10 + 2];
            _integral_to_dec_buffer(v, buf);
            str << buf;
        } else if constexpr (OutputStream::base == base::OCT) {
            /*
             * A char is needed for each 3 bits + 3 for the leading
             * 0o and the trailing \0.
             */
            char buf[sizeof(T) * 3 + 3];
            _integral_to_oct_buffer(v, buf);
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
