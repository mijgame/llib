#ifndef LLIB_DYNAMIC_ARRAY_HPP
#define LLIB_DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <utility>
#include <iterator>

#include "math.hpp"

namespace llib {
    template<typename T, size_t Size>
    class dynamic_array {
    protected:
        T store[Size] = {};
        size_t index = 0;

        /**
         * Helper function that frees a spot at
         * the given position by shifting all elements
         * to the right by one.
         *
         * Does not update the index.
         *
         * @param pos
         */
        void free_position(const size_t pos) {
            for (size_t i = this->index; i != pos; --i) {
                store[i + 1] = store[i];
            }
        }

    public:
        /**
         * Default constructor.
         */
        dynamic_array() = default;

        /**
         * Construct from a initializer list.
         *
         * @param list
         */
        dynamic_array(std::initializer_list<T> list)
                : dynamic_array(list.begin(), list.end()) {}

        /**
         * Construct from a given InputIterator.
         *
         * @tparam InputIterator
         * @param first
         * @param last
         */
        template<typename InputIterator>
        dynamic_array(InputIterator first, InputIterator last) {
            for (auto it = first; it != last; ++it) {
                push_back(*it);
            }
        }

        /**
         * Copy constructor.
         *
         * @param x
         */
        dynamic_array(const dynamic_array &x) {
            for (size_t i = 0; i < x.size(); i++) {
                push_back(x[i]);
            }
        }

        /**
         * Move constructor.
         *
         * @param other
         */
        dynamic_array(dynamic_array &&other) : dynamic_array() {
            swap(*this, other);
        }

        /**
         * Assignment operator for two arrays.
         *
         * @param other
         * @return
         */
        dynamic_array &operator=(dynamic_array other) {
            swap(*this, other);

            return *this;
        }

        /**
         * Assignment operator for an array and an
         * initializer_list.
         *
         * @param list
         * @return
         */
        dynamic_array &operator=(std::initializer_list<T> list) {
            index = 0;

            for (const auto &item : list) {
                push_back(item);
            }

            return *this;
        }

        /**
         * A random access iterator for the dynamic array;
         * used for for-ranges or standard algorithms.
         */
        class random_access_iterator {
        protected:
            dynamic_array<T, Size> &subject;
            size_t at;

            // Allow access to the 'at' member
            friend dynamic_array;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = value_type *;
            using const_pointer = value_type const *;
            using reference = value_type &;
            using iterator_category = std::bidirectional_iterator_tag;

            random_access_iterator(dynamic_array<T, Size> &subject)
                    : subject(subject), at(0) {}

            random_access_iterator(dynamic_array<T, Size> &subject, size_t start)
                    : subject(subject), at(start) {}

            random_access_iterator(const random_access_iterator &rhs)
                    : subject(rhs.subject), at(rhs.at) {}

            random_access_iterator(random_access_iterator &&rhs) {
                subject = rhs.subject;
                at = rhs.at;
            }

            random_access_iterator &operator=(const random_access_iterator &rhs) {
                subject = rhs.subject;
                at = rhs.at;
            }

            random_access_iterator &operator=(random_access_iterator &&rhs) {
                subject = rhs.subject;
                at = rhs.at;
            }

            /**
             * a == b
             *
             * @param rhs
             * @return
             */
            bool operator==(const random_access_iterator &rhs) {
                return at == rhs.at
                       && std::addressof(subject) == std::addressof(rhs.subject);
            }

            /**
             * a != b
             *
             * @param rhs
             * @return
             */
            bool operator!=(const random_access_iterator &rhs) {
                return !operator==(rhs);
            }

            reference operator*() {
                return subject[at];
            }

            value_type operator*() const {
                return subject[at];
            }

            pointer operator->() {
                return &subject[at];
            }

            const_pointer operator->() const {
                return &subject[at];
            }

            /**
             * Pre-increment.
             *
             * @return
             */
            random_access_iterator &operator++() {
                at++;
                return *this;
            }

            /**
             * Post increment.
             *
             * @return
             */
            const random_access_iterator operator++(int) {
                random_access_iterator temp(*this);
                operator++();
                return temp;
            }

            random_access_iterator &operator--() {
                at--;
            }

            const random_access_iterator operator--(int) {
                random_access_iterator temp(*this);
                operator--();
                return temp;
            }

            /**
             * a + n
             *
             * @param n
             * @return
             */
            random_access_iterator operator+(const size_t n) const {
                return random_access_iterator(subject, at + n);
            }

            /**
             * n + a
             *
             * @param n
             * @param it
             * @return
             */
            friend random_access_iterator operator+(const size_t n, const random_access_iterator &it) {
                return it + n;
            }

            /**
             * a - n
             *
             * @param n
             * @return
             */
            random_access_iterator operator-(const size_t n) const {
                return random_access_iterator(subject, at - n);
            }

            /**
             * a - b
             *
             * @param other
             * @return
             */
            random_access_iterator operator-(const random_access_iterator &other) const {
                return random_access_iterator(subject, at - other.at);
            }

            /**
             * a < b
             *
             * @param other
             * @return
             */
            random_access_iterator operator<(const random_access_iterator &other) const {
                return at < other.at;
            }

            /**
             * a > b
             *
             * @param other
             * @return
             */
            random_access_iterator operator>(const random_access_iterator &other) const {
                return at > other.at;
            }

            /**
             * a <= b
             *
             * @param other
             * @return
             */
            random_access_iterator operator<=(const random_access_iterator &other) const {
                return operator<(other) || operator==(other);
            }

            /**
             * a >= b
             *
             * @param other
             * @return
             */
            random_access_iterator operator>=(const random_access_iterator &other) const {
                return operator>(other) || operator==(other);
            }

            /**
             * a += n
             *
             * @param n
             * @return
             */
            random_access_iterator operator+=(const size_t n) {
                at += n;
            }

            /**
             * a -= n
             *
             * @param n
             * @return
             */
            random_access_iterator operator-=(const size_t n) {
                at -= n;
            }

            /**
             * a[n]
             *
             * @param n
             * @return
             */
            reference operator[](const size_t n) {
                return subject[n];
            }
        };

        /**
         * Get a reference to the first element
         * in the array. Calling this function on
         * an empty container causes undefined behaviour.
         *
         * @return
         */
        T &front() {
            return store[0];
        }

        /**
         * Get a constant reference to the first element
         * in the array. Calling this function on
         * an empty container causes undefined behaviour.
         *
         * @return
         */
        const T &front() const {
            return store[0];
        }

        /**
         * Get a reference to the last element
         * in the array. Calling this function on
         * an empty container causes undefined behaviour.
         *
         * @return
         */
        T &back() {
            return store[index - 1];
        }

        /**
         * Get constant a reference to the last element
         * in the array. Calling this function on
         * an empty container causes undefined behaviour.
         *
         * @return
         */
        const T &back() const {
            return store[index - 1];
        }

        /**
         * Get a pointer to the
         * underlying data store.
         *
         * @return
         */
        T *data() {
            return store;
        }

        /**
         * Get a constant pointer to the
         * underlying data store.
         *
         * @return
         */
        const T *data() const {
            return store;
        }

        /**
         * Check whether the array is
         * empty.
         *
         * @return
         */
        bool empty() const {
            return size() == 0;
        }

        /**
         * Get the amount of elements
         * in the array.
         *
         * @return
         */
        size_t size() const {
            return index;
        }

        /**
         * Get the maximum size of
         * the array.
         *
         * @return
         */
        constexpr size_t max_size() const {
            return Size;
        }

        /**
         * Remove all elements from the array.
         * These elements are destroyed.
         */
        void clear() {
            // Destruct elements.
            for (size_t i = 0; i < index; i++) {
                store[i].~T();
            }

            index = 0;
        }

        // Reduce visual noise with these aliases
        using iterator = random_access_iterator;
        using const_iterator = const random_access_iterator;

        /**
         * Insert a single element.
         *
         * @param it
         * @param value
         * @return
         */
        iterator insert(const_iterator &it, const T &value) {
            free_position(it.at);
            store[it.at] = value;
            index++;

            return iterator(it);
        }

        /**
         * Insert the given value n types, starting
         * at iterator it.
         *
         * @param it
         * @param n
         * @param value
         * @return
         */
        iterator insert(const_iterator &it, size_t n, const T &value) {
            for (size_t i = 0; i < n; i++) {
                insert(it + i, value);
            }

            return it;
        }

        /**
         * Insert a range of values from the input iterator,
         * starting at the given iterator.
         *
         * @tparam InputIterator
         * @param it
         * @param first
         * @param last
         * @return
         */
        template<typename InputIterator>
        iterator insert(const_iterator &it, InputIterator first, InputIterator last) {
            size_t i = 0;

            for (auto iit = first; iit != last; ++i, ++iit) {
                insert(it + i, iit);
            }

            return it;
        }

        /**
         * Insert a single element by move at
         * the given position.
         *
         * @param it
         * @param value
         * @return
         */
        iterator insert(const_iterator &it, T &&value) {
            insert(it, std::move(value));

            return it;
        }

        /**
         * Insert a range of values from an initializer list,
         * starting at the given position.
         *
         * @param it
         * @param list
         * @return
         */
        iterator insert(const_iterator &it, std::initializer_list<T> list) {
            insert(it, list.begin(), list.end());
        }

        /**
         * Emplace an element at the given position.
         *
         * @tparam Args
         * @param pos
         * @param args
         */
        template<typename ...Args>
        void emplace(const size_t pos, Args &&... args) {
            free_position(pos);
            store[pos] = T(std::forward<Args>(args)...);
            index++;
        }

        /**
         * Emplace an element at the given position.
         *
         * @tparam Args
         * @param pos
         * @param args
         */
        template<typename ...Args>
        void emplace(const_iterator &it, Args &&... args) {
            emplace(it.at, std::forward<Args>(args)...);
        }

        /**
         * Erase an element at the given position.
         *
         * @param pos
         */
        void erase(const_iterator &it) {
            if (it.at == this->index - 1) {
                this->index--;
                return;
            }

            // We don't set the data to zero; all items from the given
            // index on will be shifted one left in the array, overwriting the index to
            // remove. This makes removals expensive in the front of the array but prevents
            // fragmentation.
            for (size_t i = it.at; i < this->index - 1; ++i) {
                store[i] = store[i + 1];
            }

            this->index--;
        }

        /**
         * Erase a range of elements.
         *
         * @param start
         * @param end
         */
        void erase(const_iterator &start, const_iterator &end) {
            for (auto it = start; it != end; ++it) {
                erase(it);
            }
        }

        /**
         * Replace the contents of the array with
         * the values from the iterator.
         * Old values are destroyed.
         *
         * @tparam InputIterator
         * @param first
         * @param last
         */
        template<typename InputIterator>
        void assign(InputIterator first, InputIterator last) {
            clear();

            for (auto it = first; it != last; ++it) {
                push_back(it);
            }
        }

        /**
         * Replace the contents of the array with
         * the given value.
         * Old values are destroyed.
         *
         * @param n
         * @param val
         */
        void assign(size_t n, const T &val) {
            clear();

            for (size_t i = 0; i < n; i++) {
                push_back(val);
            }
        }

        /**
         * Replace the contents of the array with
         * the values from the initializer list.
         * Old values are destroyed.
         *
         * @param list
         */
        void assign(std::initializer_list<T> list) {
            assign(list.begin(), list.end());
        }

        /**
         * Add the given value to the end
         * of the array.
         *
         * @param entry
         */
        void push_back(const T &entry) {
            store[index++] = entry;
        }

        /**
         * Add the given value to the end
         * of the array.
         *
         * @param entry
         */
        void push_back(T &&entry) {
            store[index++] = entry;
        }

        /**
         * Emplace an element at
         * the back of the array.
         *
         * @tparam Args
         * @param args
         */
        template<typename ...Args>
        void emplace_back(Args &&... args) {
            store[index++] = T(std::forward<Args>(args)...);
        }

        /**
         * Remove the last element of the array,
         * reducing the array size by one.
         * This destroys the removed element.
         */
        void pop_back() {
            store[index--].~T();
        }

        /**
         * Swap the arrays.
         *
         * @param first
         * @param second
         */
        friend void swap(dynamic_array &first, dynamic_array &second) {
            using std::swap;

            swap(first.store, second.store);
            swap(first.index, second.index);
        }

        /**
         * Get a reference to the element
         * at the given index.
         *
         * @param index
         * @return
         */
        T &operator[](const size_t index) {
            return store[index];
        }

        /**
         * Get a copy of the element
         * at the given index.
         *
         * @param index
         * @return
         */
        T operator[](const size_t index) const {
            return store[index];
        }

        /**
         * Get an iterator to the start
         * of the array.
         *
         * @return
         */
        iterator begin() {
            return iterator(*this);
        }

        /**
         * Get a constant iterator to the start
         * of the array.
         *
         * @return
         */
        const_iterator begin() const {
            return iterator(*this);
        }

        /**
         * Get an iterator to the end
         * of the array.
         *
         * @return
         */
        iterator end() {
            return iterator(*this, index);
        }

        /**
         * Get a constant iterator to the end
         * of the array.
         *
         * @return
         */
        const_iterator end() const {
            return const_iterator(*this, index);
        }
    };

    /**
     * Check if the array contents are equal.
     * The smallest array size decides how many elements
     * are checked.
     *
     * @tparam T
     * @tparam Size
     * @param lhs
     * @param rhs
     * @return
     */
    template<typename T, size_t Size>
    bool operator==(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        int size = min(lhs.size(), rhs.size());

        for (int i = 0; i < size; i++) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }

        return true;
    }

    /**
     * Check if the array contents are not equal.
     * The smallest array size decides how many elements
     * are checked.
     *
     * @tparam T
     * @tparam Size
     * @param lhs
     * @param rhs
     * @return
     */
    template<typename T, size_t Size>
    bool operator!=(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !operator==(lhs, rhs);
    }

    /**
     * Check if each element is less then
     * the element in the other array.
     * The smallest array size decides how many elements
     * are checked.
     *
     * @tparam T
     * @tparam Size
     * @param lhs
     * @param rhs
     * @return
     */
    template<typename T, size_t Size>
    bool operator<(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        int size = min(lhs.size(), rhs.size());

        for (int i = 0; i < size; i++) {
            if (!(lhs[i] < rhs[i])) {
                return false;
            }
        }

        return true;
    }

    /**
     * Check if each element is less then or equal to
     * the element in the other array.
     * The smallest array size decides how many elements
     * are checked.
     *
     * @tparam T
     * @tparam Size
     * @param lhs
     * @param rhs
     * @return
     */
    template<typename T, size_t Size>
    bool operator<=(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !(lhs < rhs);
    }

    /**
     * Check if each element is greater than
     * the element in the other array.
     * The smallest array size decides how many elements
     * are checked.
     *
     * @tparam T
     * @tparam Size
     * @param lhs
     * @param rhs
     * @return
     */
    template<typename T, size_t Size>
    bool operator>(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !(lhs < rhs);
    }

    /**
     * Check if each element is greater than or equal to
     * the element in the other array.
     * The smallest array size decides how many elements
     * are checked.
     *
     * @tparam T
     * @tparam Size
     * @param lhs
     * @param rhs
     * @return
     */
    template<typename T, size_t Size>
    bool operator>=(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !(lhs < rhs);
    }
}

#endif //LLIB_DYNAMIC_ARRAY_HPP
