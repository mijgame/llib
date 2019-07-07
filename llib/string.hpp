#ifndef LLIB_STRING_HPP
#define LLIB_STRING_HPP

#include <cstddef>
#include <type_traits>
#include <cstring>
#include <initializer_list>

#include <util.hpp>

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

            return i;
        }

        constexpr bool is_lowercase(char c) const {
            return c >= 'a' && c <= 'z';
        }

        constexpr bool is_uppercase(char c) const {
            return c >= 'A' && c <= 'Z';
        }

        constexpr bool is_number(char c) const {
            return c >= '0' && c <= '9';
        }

        constexpr bool is_whitespace(char c) const {
            return c == ' ' || c == '\n' || c == '\t' || c== '\r';
        }

    public:
        /**
         * npos is a constant that refers to the end of the string
         * when used for lengths and/or positions.
         */
        constexpr static size_t npos = std::numeric_limits<size_t>::max();

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
        constexpr string(const char value, const size_t n) {
            assign(value, n);
        }

        /**
         * Initialize the string with the given value.
         * Notice: this constructor should not be explicit!
         *
         * @param value
         */
        constexpr string(const char *value) {
            assign(value);
        }

        /**
         * Initialize the string with the first n characters from
         * the given string.
         *
         * @param value
         * @param n
         */
        constexpr string(const char *value, const size_t n) {
            assign(value, n);
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
            assign(other);
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
            assign(other.c_str(), n);
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
            assign(first, last);
        }

        /**
         * Construct the string with the given initializer
         * list.
         *
         * @param il
         */
        constexpr string(std::initializer_list<char> il) {
            assign(il);
        }

        /**
         * Acquires the contents of str.
         * str is left in an unspecified but valid state.
         *
         * @tparam OtherBufferSize
         * @param str
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize == OtherBufferSize>
        >
        constexpr string(string<OtherBufferSize> &&str) {
            assign(std::move(str));
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
            return assign(value);
        }

        /**
         * Assign the string with the value of the given initializer list.
         *
         * @param il
         * @return
         */
        constexpr string<BufferSize> &operator=(std::initializer_list<char> il) {
            return assign(il);
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
            return assign(other);
        }

        /**
         * Copy the given string into this string.
         *
         * @tparam OtherBufferSize
         * @param str
         * @return
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<OtherBufferSize <= BufferSize>
        >
        constexpr string<BufferSize> &assign(const string<OtherBufferSize> &str) {
            buffer_length = str.buffer_length;
            str_copy(buffer, str.buffer);

            return *this;
        }

        /**
         * Copies the portion of str that begins at the character position subpos and
         * spans sublen characters (or until the end of str, if either str is too short or
         * if sublen is string::npos).
         *
         * @tparam OtherBufferSize
         * @param str
         * @param subpos
         * @param sublen
         * @return
         */
        template<size_t OtherBufferSize>
        constexpr string &assign(const string<OtherBufferSize> &str, const size_t subpos, const size_t sublen) {
            constexpr auto length = sublen == npos
                                    ? str.len() - subpos
                                    : llib::min(str.len() - subpos, sublen);

            memcpy(
                (void *) buffer,
                (void *) (str.c_str() + subpos),
                length
            );

            // Add a null terminator and change length if required
            if (subpos + length > buffer_length) {
                buffer_length = subpos + length;
                buffer[buffer_length + 1] = '\0';
            }

            return *this;
        }

        /**
         * Copies the null-terminated character sequence (C-string) pointed by value.
         *
         * @param value
         * @return
         */
        constexpr string &assign(const char *value) {
            const auto len = str_len(value);

            memcpy(
                (void *) buffer,
                (const void *) value,
                len
            );

            buffer_length = len;
            buffer[len + 1] = '\0';

            return *this;
        }

        /**
         * Copies the first n characters from the array of characters pointed by value.
         *
         * @param value
         * @param n
         * @return
         */
        constexpr string &assign(const char *value, const size_t n) {
            memcpy(
                (void *) buffer,
                (const void *) value,
                n
            );

            buffer_length = n;
            buffer[n + 1] = '\0';

            return *this;
        }

        /**
         * Replaces the current value by n consecutive copies of character value.
         *
         * @param value
         * @param n
         * @return
         */
        constexpr string &assign(const char value, const size_t n) {
            buffer_length = n;

            for (size_t i = 0; i < n; i++) {
                buffer[i] = value;
            }

            buffer[buffer_length + 1] = '\0';

            return *this;
        }

        /**
         * Copies the sequence of characters in the range [first,last), in the same order.
         *
         * @tparam InputIterator
         * @param first
         * @param last
         * @return
         */
        template<typename InputIterator>
        constexpr string &assign(InputIterator first, InputIterator last) {
            buffer_length = 0;

            for (auto it = first; it != last; ++it) {
                buffer[buffer_length++] = *it;
            }

            buffer[buffer_length + 1] = '\0';

            return *this;
        }

        /**
         * Copies each of the characters in il, in the same order.
         *
         * @param il
         * @return
         */
        constexpr string &assign(std::initializer_list<char> il) {
            buffer_length = 0;

            for (const char c : il) {
                buffer[buffer_length++] = c;
            }

            buffer[buffer_length + 1] = '\0';

            return *this;
        }

        /**
         * Acquires the contents of str.
         * str is left in an unspecified but valid state.
         *
         * @tparam OtherBufferSize
         * @param str
         * @return
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize == OtherBufferSize>
        >
        constexpr string<BufferSize> &assign(string<OtherBufferSize> &&str) noexcept {
            buffer = std::move(str.buffer);
            buffer_length = std::move(str.buffer_length);

            return *this;
        }

        /**
         * Insert additional characters before the character
         * indicated by pos.
         *
         * @tparam OtherBufferSize
         * @param pos
         * @param str
         * @return
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        constexpr string<BufferSize> &insert(const size_t pos, const string<OtherBufferSize> &str) {
            memmove(
                (void *) (buffer + pos + str.len()),
                (void *) (buffer + pos),
                buffer_length - pos
            );

            memcpy(
                (void *) (buffer + pos),
                (void *) str.c_str(),
                str.len()
            );

            buffer_length += str.len();
            buffer[buffer_length] = '\0';

            return *this;
        };

        /**
         * Inserts a copy of a substring of str.
         * The substring is the portion of str that begins at the character position subpos
         * and spans sublen characters (or until the end of str, if either str is
         * too short or if sublen is npos).
         *
         * @tparam OtherBufferSize
         * @param pos
         * @param str
         * @return
         */
        template<
            size_t OtherBufferSize,
            typename = std::enable_if_t<BufferSize >= OtherBufferSize>
        >
        constexpr string<BufferSize> &
        insert(const size_t pos, const string<OtherBufferSize> &str, const size_t subpos, const size_t sublen = npos) {
            constexpr auto length = sublen == npos
                                    ? str.len() - subpos
                                    : llib::min(str.len() - subpos, sublen);

            memmove(
                (void *) (buffer + pos + length),
                (void *) (buffer + pos),
                buffer_length - pos
            );

            memcpy(
                (void *) (buffer + pos),
                (void *) (str.c_str() + subpos),
                length
            );

            buffer_length += length;
            buffer[buffer_length] = '\0';

            return *this;
        };

        /**
         * Search the string for the given substring.
         * If found, the position of the first character in the match
         * is returned. If nothing is found, -1 is returned.
         *
         * This function uses a naive search algorithm, which works
         * well for small strings on embedded systems as there are no setup costs
         * or additional memory requirements.
         *
         * @tparam OtherBufferSize
         * @param subject
         * @return
         */
        template<size_t OtherBufferSize>
        constexpr int find(const string<OtherBufferSize> &subject) const {
            int pos = 0;
            int length = static_cast<int>(len() - subject.len());

            while (pos < length) {
                if (buffer[pos] != subject[0]) {
                    pos += 1;
                    continue;
                }

                size_t match = 1;
                while (buffer[pos + match] == subject[match]) {
                    match += 1;

                    if (match == subject.len()) {
                        return static_cast<int>(pos);
                    }
                }

                pos += match;
            }

            return -1;
        }

        /**
         * Capitalize the first letter of the string.
         *
         * @return
         */
        constexpr void capitalize() {
            if (buffer_length > 0 && is_lowercase(buffer[0])) {
                buffer[0] -= 32;
            }
        }

        /**
         * Convert the string to lowercase.
         *
         * @return
         */
        constexpr void to_lower() {
            for (size_t i = 0; i < buffer_length; i++) {
                if (is_uppercase(buffer[i])) {
                    buffer[i] += 32;
                }
            }
        }

        /**
         * Convert the string to uppercase.
         *
         * @return
         */
        constexpr void to_upper() {
            for (size_t i = 0; i < buffer_length; i++) {
                if (is_lowercase(buffer[i])) {
                    buffer[i] -= 32;
                }
            }
        }

        /**
         * Check if the entire string is lowercase.
         * This function will ignore whitespace.
         *
         * @return
         */
        constexpr bool is_lower() const {
            for (size_t i = 0; i < buffer_length; i++) {
                if (is_whitespace(buffer[i])) {
                    continue;
                }

                if (! is_lowercase(buffer[i])) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Check if the entire string is uppercase.
         * This function will ignore whitespace.
         *
         * @return
         */
        constexpr bool is_upper() const {
            for (size_t i = 0; i < buffer_length; i++) {
                if (is_whitespace(buffer[i])) {
                    continue;
                }

                if (! is_uppercase(buffer[i])) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Check if the entire string is alphanumeric.
         * This function will ignore whitespace.
         *
         * @return
         */
        constexpr bool is_alnum() const {
            for (size_t i = 0; i < buffer_length; i++) {
                if (is_whitespace(buffer[i])) {
                    continue;
                }

                if (!(is_lowercase(buffer[i])
                      || is_number(buffer[i])
                      || is_uppercase(buffer[i]))
                    ) {
                    return false;
                }
            }

            return true;
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
        constexpr void push_back(const char c) {
            buffer[buffer_length++] = c;
            buffer[buffer_length + 1] = '\0';
        }

        /**
         * Erase the last character of this string buffer.
         * @return
         */
        constexpr void pop_back() {
            buffer[buffer_length--] = '\0';
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
            buffer.push_back(other);

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
         * Create a new string that contains the old string
         * n times.
         *
         * Notice: the current string buffer should be large enough to
         * store the whole new string!
         *
         * @param n
         * @return
         */
        constexpr string<BufferSize> operator*(int n) {
            llib::string<BufferSize> copy = *this;

            // n - 1 because 'aa' * 3 should be 'aaaaaa'.
            for (int i = 0; i < n - 1; i++) {
                copy.append(*this);
            }

            return copy;
        }

        /**
         * Copy the string value into the current buffer
         * n times.
         *
         * Notice: the current string buffer should be large enough to
         * store the whole new string!
         *
         * @param n
         * @return
         */
        constexpr string<BufferSize> &operator*=(size_t n) {
            size_t length = buffer_length;

            for (size_t i = 0; i < n - 1; i++) {
                for (size_t j = 0; j < length; j++) {
                    buffer[buffer_length++] = buffer[j];
                }
            }

            buffer[buffer_length + 1] = '\0';

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
         * Whether this string is full.
         * Full means that the length is equal
         * to the size of the buffer.
         *
         * @return
         */
        constexpr bool full() const {
            // -1 for the null terminator
            return buffer_length == BufferSize - 1;
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
        *
        * @tparam OtherBufferSize
        * @param other
        */
        template<size_t OtherBufferSize>
        constexpr void swap(string<OtherBufferSize> &other) {
            // Swap pointers
            std::swap(buffer, other.buffer);
            std::swap(buffer_length, other.buffer_length);
        }

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

        /**
         * Check if the contents of the two strings
         * are equal.
         *
         * @param other
         * @return
         */
        constexpr bool operator==(const char c) const {
            if (len() != 1) {
                return false;
            }

            return buffer[0] == c;
        }

        /**
         * Check if the contents of the two strings
         * are not equal.
         *
         * @param other
         * @return
         */
        constexpr bool operator!=(const char c) const {
            return !operator==(c);
        }

        /**
         * Check if the contents of the two strings
         * are equal.
         *
         * @param other
         * @return
         */
        constexpr bool operator==(const char *other) const {
            if (len() != strlen(other)) {
                return false;
            }

            for (size_t i = 0; i < buffer_length; ++i) {
                if (buffer[i] != other[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Check if the contents of the two strings are not
         * equal.
         *
         * @param other
         * @return
         */
        constexpr bool operator!=(const char *other) const {
            return !operator==(other);
        }

        /**
         * Check if the contents of the two strings are
         * equal.
         *
         * @tparam OtherBufferSize
         * @param other
         * @return
         */
        template<size_t OtherBufferSize>
        constexpr bool operator==(const string<OtherBufferSize> &other) const {
            if (len() != other.len()) {
                return false;
            }

            for (size_t i = 0; i < buffer_length; ++i) {
                if (buffer[i] != other[i]) {
                    return false;
                }
            }

            return true;
        }

        /**
         * Check if the contents of the two strings are not
         * equal.
         *
         * @tparam OtherBufferSize
         * @param other
         * @return
         */
        template<size_t OtherBufferSize>
        constexpr bool operator!=(const string<OtherBufferSize> &other) const {
            return !operator==(other);
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
    constexpr OutputStream &operator<<(OutputStream &str, const string<BufferSize> &data) {
        str << data.c_str();
        return str;
    }

    /**
     * Input stream overload for string.
     * Will read until one of the following things are true:
     *  - The string buffer is full
     *  - A space is found
     *  - A tab is found
     *  - A newline is found
     *
     * @tparam InputStream
     * @tparam BufferSize
     * @param str
     * @param data
     * @return
     */
    template<typename InputStream, size_t BufferSize>
    InputStream &operator>>(InputStream &str, string<BufferSize> &data) {
        char c = 0;

        for (;;) {
            if (data.full()) {
                break;
            }

            if (!(str >> c)) {
                break;
            }

            data.push_back(c);
        }

        return str;
    }
}

#endif //LLIB_STRING_HPP
