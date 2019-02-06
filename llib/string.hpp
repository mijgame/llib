#ifndef LLIB_STRING_HPP
#define LLIB_STRING_HPP

#include <cstddef>
#include <type_traits>
#include <cstring>
#include <initializer_list>

namespace llib {
    /**
     * Dynamic string for embedded applications.
     * This string is not 0-terminated; to get a 0-terminated representation
     * use the c_str() function.
     *
     * @tparam BufferSize
     */
    template<size_t BufferSize = 64>
    class string {
    protected:
        char buffer[BufferSize] = {};
        size_t buffer_length = 0;

        /**
         * Get the length of the given 0-terminated
         * C string, excluding the terminator.
         *
         * @internal
         * @param str
         * @return
         */
        constexpr size_t str_len(const char *str) const {
            size_t length = 0;

            while (*(str++)) {
                length++;
            }

            return length;
        }

        /**
         * Copy the source C string into the target
         * buffer. Return the length of the copied segment.
         *
         * @param dest
         * @param source
         * @return
         */
        constexpr size_t str_copy(char *dest, const char *source) const {
            size_t i = 0;
            while (source[i] != '\0') {
                dest[i] = source[i];
                i += 1;
            }

            dest[i] = '\0';

            return i - 1;
        }

    public:
        /**
         * Empty constructor.
         */
        constexpr string() {
            buffer[0] = '\0';
        };

        /**
         * Initialize the string with the given value.
         *
         * @param value
         */
        constexpr explicit string(char value) {
            *this = value;
        }

        /**
         * Fill the string with the given value
         * n times.
         *
         * @param value
         * @param n
         */
        constexpr string(char value, const size_t n) {
           buffer_length = n;

           for (size_t i = 0; i < n; i++) {
               buffer[i] = value;
           }

           buffer[buffer_length + 1] = '\0';
        }

        /**
         * Initialize the string with the given value.
         *
         * @param value
         */
        constexpr explicit string(const char *value) {
            *this = value;
        }

        /**
         * Initialize the string with the first n characters from
         * the given string.
         *
         * @param value
         * @param n
         */
        constexpr string(const char *value, const size_t n) {
            buffer_length = n;

            for (size_t i = 0; i < n; i++) {
                buffer[i] = value[i];
            }

            buffer[n + 1] = '\0';
        }

        /**
         * Initialize the string with the value of
         * the other string.
         *
         * @tparam OtherBufferSize
         * @param other
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        constexpr explicit string(const string<OtherBufferSize> &other) {
            *this = other;
        }

        /**
         * Initialize the string with the value of
         * the other string until n characters.
         *
         * @tparam OtherBufferSize
         * @param other
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        constexpr string(const string<OtherBufferSize> &other, const size_t n) {
            buffer_length = n;
            const char *value = other.c_str();

            for (size_t i = 0; i < n; i++) {
                buffer[i] = value[i];
            }

            buffer[n + 1] = '\0';
        }

        /**
         * Initialize the string with the values from
         * the given iterator.
         *
         * @tparam InputIterator
         * @param first
         * @param last
         */
        template<typename InputIterator>
        constexpr string(InputIterator first, InputIterator last) {
            buffer_length = 0;

            for (auto it = first; it != last; ++it) {
                buffer[buffer_length++] = *it;
            }

            buffer[buffer_length + 1] = '\0';
        }

        /**
         * Construct the string with the given initializer
         * list.
         *
         * @param il
         */
        constexpr string(std::initializer_list<char> il) {
            *this = il;
        }

        /**
         * Assign the string with the given character.
         *
         * @param value
         * @return
         */
        constexpr string<BufferSize> &operator=(char value) {
            buffer_length = 1;

            buffer[0] = value;
            buffer[1] = '\0';

            return *this;
        }

        /**
         * Assign the string with the given C string.
         *
         * @param value
         * @return
         */
        constexpr string<BufferSize> &operator=(const char *value) {
            buffer_length = str_len(value);
            str_copy(buffer, value);

            return *this;
        }

        /**
         * Assign the string with the value of the given initializer list.
         *
         * @param il
         * @return
         */
        constexpr string<BufferSize> &operator=(std::initializer_list<char> il) {
            buffer_length = 0;

            for (const char c : il) {
                buffer[buffer_length++] = c;
            }

            buffer[buffer_length + 1] = '\0';

            return *this;
        }

        /**
         * Assign the string with the value of another string.
         *
         * @tparam OtherBufferSize
         * @param other
         * @return
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        constexpr string<BufferSize> &operator=(const string<OtherBufferSize> &other) {
            buffer_length = other.len();
            str_copy(buffer, other.buffer);

            return *this;
        }

        /**
         * Get the length of the string.
         *
         * @return
         */
        constexpr size_t len() const {
            return buffer_length;
        }

        /**
         * Get a 0-terminated char pointer representation
         * of the string.
         *
         * @return
         */
        constexpr const char *c_str() const {
            return buffer;
        }

        /**
         * Append the given string to this string buffer.
         *
         * @tparam OtherBufferSize
         * @param other
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        constexpr void append(const string<OtherBufferSize> &other) {
            buffer_length += str_copy((buffer + buffer_length), other.c_str());
        }

        /**
         * Append the given 0-terminated C string to this string buffer.
         *
         * @param other
         */
        constexpr void append(const char *other) {
            buffer_length += str_copy((buffer + buffer_length), other);
        }

        /**
        * Append the given character to this string buffer.
        *
        * @param other
        */
        constexpr void append(char other) {
            buffer[buffer_length] = other;
            buffer[++buffer_length] = '\0';
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
            size_t OtherBufferSize,
            size_t NewBufferSize = BufferSize + OtherBufferSize
        >
        constexpr string<NewBufferSize> operator+(const string<OtherBufferSize> &other) const {
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
        constexpr string<BufferSize> operator+(const char *other) const {
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
        constexpr string<BufferSize + 1> operator+(char other) const {
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
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        constexpr string<BufferSize> &operator+=(const string<OtherBufferSize> &other) {
            append(other);
            return *this;
        }

        /**
         * Append the given 0-terminated C string to this string.
         *
         * @param other
         * @return
         */
        constexpr string<BufferSize> &operator+=(const char *other) {
            append(other);
            return *this;
        }

        /**
         * Check whether the string starts with the given string.
         *
         * @tparam OtherBufferSize
         * @param str
         * @return
         */
        template<size_t OtherBufferSize>
        constexpr bool ends_with(const string<OtherBufferSize> &str) const {
            const auto offset = buffer_length - str.len();

            for (size_t i = 0; i < str.len(); i++) {
                if (buffer[offset + i] != str[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Check whether the string starts with the given string.
         *
         * @param str
         * @return
         */
        constexpr bool ends_with(const char *str) const {
            const auto len = str_len(str);
            const auto offset = buffer_length - len;

            for (size_t i = 0; i < len; i++) {
                if (buffer[offset + i] != str[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Check whether the string starts with the given string.
         *
         * @tparam OtherBufferSize
         * @param str
         * @return
         */
        template<size_t OtherBufferSize>
        constexpr bool starts_with(const string<OtherBufferSize> &str) const {
            for (size_t i = 0; i < str.len(); i++) {
                if (buffer[i] != str[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Check whether the string starts with the given string.
         *
         * @param str
         * @return
         */
        constexpr bool starts_with(const char *str) const {
            for (size_t i = 0; i < str_len(str); i++) {
                if (buffer[i] != str[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Get a reference to the character at the given index.
         *
         * @param index
         * @return
         */
        constexpr char &operator[](const size_t index) {
            return buffer[index];
        }

        /**
         * Get the character at the given index.
         * @param index
         * @return
         */
        constexpr char operator[](const size_t index) const {
            return buffer[index];
        }

        /**
         * Clear the string.
         * The underlying array is not actually zeroed.
         *
         * @return
         */
        constexpr void clear() {
            buffer_length = 0;
        }

        /**
         * Whether this string is empty.
         *
         * @return
         */
        constexpr bool empty() const {
            return buffer_length == 0;
        }

        /**
         * Copy the current buffer into a new string container,
         * allowing for a smaller size. This function exists to allow
         * the user of the container to make it explicit that the string
         * fits into a smaller container.
         *
         * @tparam NewBufferSize
         * @return
         */
        template<size_t NewBufferSize>
        constexpr string<NewBufferSize> to_smaller_buffer() const {
            return string<NewBufferSize>(buffer);
        }

        /**
         * Access the first character in the string.
         * Not defined on an empty string.
         *
         * @return
         */
        constexpr char front() const {
            return buffer[0];
        }

        /**
         * Access the last character in the string.
         * Not defined on an empty string.
         *
         * @return
         */
        constexpr char back() const {
            return buffer[buffer_length];
        }

        /**
         * Replace the contents a pos for a length of len with the
         * contents of the given string.
         *
         * @tparam OtherBufferSize
         * @param pos
         * @param len
         * @param str
         * @return
         */
//        template<size_t OtherBufferSize>
//        constexpr string<BufferSize> &replace(const size_t pos, const size_t len, const string<OtherBufferSize> &str) {
//            // If str.len() is equal to the len, simply replace
//            if (len == str.len()) {
//                for (size_t i = pos; i < pos + len; i++) {
//                    buffer[i] = str[i - pos];
//                }
//
//                return *this;
//            }
//
//            // We need to make space
//            if (len < str.len()) {
//                const auto make_space_for = len - str.len();
//            }
//
//            // We need to reclaim space
//
//            // Make space in the buffer for the required length
//
//        }

        /**
         * Get an iterator to the character buffer.
         *
         * @return
         */
        constexpr char *begin() {
            return buffer;
        }

        /**
         * Get an iterator to the character buffer.
         *
         * @return
         */
        constexpr const char *begin() const {
            return buffer;
        }

        /**
         * Get an iterator to the character buffer.
         *
         * @return
         */
        constexpr char *end() {
            return buffer + buffer_length + 1;
        }

        /**
         * Get an iterator to the character buffer.
         *
         * @return
         */
        constexpr const char *end() const {
            return buffer + buffer_length + 1;
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
    template<typename OutputStream, size_t BufferSize>
    constexpr OutputStream operator<<(OutputStream str, const string<BufferSize> &data) {
        str << data.c_str();
        return str;
    }
}

#endif //LLIB_STRING_HPP
