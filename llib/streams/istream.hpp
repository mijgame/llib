#ifndef LLIB_ISTREAM_HPP
#define LLIB_ISTREAM_HPP

namespace llib {
    [[maybe_unused]]
    constexpr target::cin cin;

    template<typename InputStream>
    InputStream operator>>(InputStream str, char &c) {
        c = str.getc();

        return str;
    }

    template<typename InputStream>
    InputStream operator>>(InputStream str, unsigned char &c) {
        c = str.getc();

        return str;
    }

    template<typename InputStream>
    InputStream operator>>(InputStream str, int &val) {
        // Currently, a decimal base is assumed
        char buf[11] = {};

        int result = 0;

        bool negative = false;

        for (size_t i = 0; i < 10; i++) {
            char c;
            str >> c;

            if (i == 0 && c == '-') {
                negative = true;
                continue;
            }

            if (c == '\n' || c == ' ' || c == '\0') {
                buf[i] = '\0';
                break;
            }

            buf[i] = c;
        }

        char *ptr = buf + negative;
        while (*ptr != '\0') {
            result *= 10 + (*(ptr++) - '0');
        }

        if (negative) {
            result *= -1;
        }

        val = result;

        return str;
    }
}

#endif //LLIB_ISTREAM_HPP
