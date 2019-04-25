#ifndef LLIB_ISTREAM_HPP
#define LLIB_ISTREAM_HPP

namespace llib {
    [[maybe_unused]]
    constexpr target::cin cin;

    template<typename InputStream>
    InputStream operator>>(InputStream str, char &c) {
        c = str.read_impl();

        return str;
    }

    template<typename InputStream>
    InputStream operator>>(InputStream str, int &val) {
        // Currently, a decimal base is assumed
        char buf[11] = {};
        int result = 0;

        for (size_t i = 0; i < 10; i++) {
            char c;
            str >> c;

            if (c == '\n' || c == ' ' || c == '\0') {
                buf[i] = '\0';
                break;
            }

            buf[i] = c;
        }

        char *ptr = buf;
        while (*ptr != '\0') {
            result *= 10 + (*(ptr++) - '0');
        }

        val = result;

        return str;
    }
}

#endif //LLIB_ISTREAM_HPP
