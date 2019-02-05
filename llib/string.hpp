#ifndef LLIB_STRING_HPP
#define LLIB_STRING_HPP

#include <cstddef>
#include <type_traits>
#include <cstring>

namespace llib {
    /**
     * Dynamic string for embedded applications.
     * This string is not 0-terminated; to get a 0-terminated representation
     * use the c_str() function.
     *
     * @tparam BufferSize
     */
    template<int BufferSize>
    class string {
    protected:
        char buffer[BufferSize];
        size_t buffer_length;

        /**
         * Get the length of the given 0-terminated
         * C string, excluding the terminator.
         *
         * @internal
         * @param str
         * @return
         */
        size_t str_len(const char *str) const {
            size_t length = 0;

            while (*(str++)) {
                length++;
            }

            return length;
        }

        /**
         * Copy the source C string into the target
         * buffer.
         *
         * @param dest
         * @param source
         */
        void str_copy(char *dest, const char *source) {
            int i = 0;
            while (source[i] != '\0') {
                dest[i] = source[i];
                i += 1;
            }
        }

    public:
        /**
         * Initialize the string.
         */
        string()
            : buffer('\0'), buffer_length(0) {}

        /**
         * Initialize the string with the given value.
         *
         * @param value
         */
        explicit string(const char *value) {
            buffer_length = str_len(value);
            str_copy(buffer, value);
        }

        /**
         * Initialize the string with the value of
         * the other string.
         *
         * @tparam OtherBufferSize
         * @param other
         */
        template<
            int OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        explicit string(const string<OtherBufferSize> &other) {
            buffer_length = other.len();
            str_copy(buffer, other.buffer);
        }

        /**
         * Get the length of the string.
         *
         * @return
         */
        size_t len() const {
            return buffer_length;
        }

        /**
         * Get a 0-terminated char pointer representation
         * of the string.
         *
         * @return
         */
        const char *c_str() const {
            return buffer;
        }

        /**
         * Append the given string to this string buffer.
         *
         * @tparam OtherBufferSize
         * @param other
         */
        template<
            int OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        void append(const string<OtherBufferSize> &other) {
            str_copy((buffer + buffer_length), other.buffer);
        }

        /**
         * Append the given 0-terminated C string to this string buffer.
         *
         * @param other
         */
        void append(const char *other) {
            str_copy((buffer + buffer_length), other);
        }

        /**
        * Append the given character to this string buffer.
        *
        * @param other
        */
        void append(char other) {
            const auto start = buffer_length; // Overwrite '\0'

            buffer[start] = other;
            buffer[start + 1] = '\0';
        }

        /**
         * Combine this buffer and the given buffer to a new
         * buffer.
         *
         * @tparam OtherBufferSize
         * @tparam NewBufferSize
         * @param other
         * @return
         */
        template<
            int OtherBufferSize,
            int NewBufferSize = BufferSize + OtherBufferSize
        >
        string<NewBufferSize> operator+(const string<OtherBufferSize> &other) {
            string<NewBufferSize> buffer(c_str());
            buffer.append(other);

            return buffer;
        }

        /**
         * Combine this buffer and the given 0-terminated C string to a
         * new buffer. Please note that the length of the current buffer is used
         * as the length of the new buffer. To make sure that the new string fits in the buffer,
         * the current buffer should be resized appropriately.
         *
         * @param other
         * @return
         */
        string<BufferSize> operator+(const char *other) {
            string<BufferSize> buffer(c_str());
            buffer.append(other);

            return buffer;
        }

        /**
         * Combine this buffer and the given character to a
         * new buffer.
         *
         * @param other
         * @return
         */
        string<BufferSize + 1> operator+(char other) {
            string<BufferSize + 1> buffer(c_str());
            buffer.append(other);

            return buffer;
        }

        /**
         * Append the given string to this string.
         *
         * @tparam OtherBufferSize
         * @param other
         * @return
         */
        template<
            int OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        string<BufferSize> &operator+=(const string<OtherBufferSize> &other) {
            append(other);
            return *this;
        }

        /**
         * Append the given 0-terminated C string to this string.
         *
         * @param other
         * @return
         */
        string<BufferSize> &operator+=(const char *other) {
            append(other);
            return *this;
        }
    };

    /**
     * Output stream overload for string.
     *
     * @tparam OutputStream
     * @tparam BufferSize
     * @param str
     * @param data
     * @return
     */
    template<typename OutputStream, int BufferSize>
    OutputStream operator<<(OutputStream str, const string<BufferSize> &data) {
        str << data.c_str();
        return str;
    }
}

#endif //LLIB_STRING_HPP
