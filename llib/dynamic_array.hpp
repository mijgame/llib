#ifndef LLIB_DYNAMIC_ARRAY_HPP
#define LLIB_DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <utility>
#include <iterator>

namespace llib {
    template<typename T, size_t Size>
    class dynamic_array {
    protected:
        T store[Size] = {};
        size_t index = 0;

        void free_position(const size_t pos) {
            for (size_t i = this->index; i != pos; --i) {
                store[i + 1] = store[i];
            }
        }

    public:
        dynamic_array() = default;

        dynamic_array(std::initializer_list<T> list) {
            for (const auto &item : list) {
                push_back(item);
            }
        }

        template<typename InputIterator>
        dynamic_array(InputIterator first, InputIterator last) {
            for (auto it = first; it != last; ++it) {
                push_back(*it);
            }
        }

        dynamic_array(const dynamic_array &x) {
            for (size_t i = 0; i < x.size(); i++) {
                push_back(x[i]);
            }
        }

        dynamic_array(dynamic_array &&x) {
            store = std::move(x.store);
            index = std::move(x.index);

            x.index = 0;
        }

        dynamic_array &operator=(const dynamic_array &x) {
            for (size_t i = 0; i < Size; i++) {
                store[i] = x.store[i];
            }

            index = x.index;

            return *this;
        }

        dynamic_array &operator=(dynamic_array &&x) {
            store = std::move(x.store);
            index = std::move(x.index);

            x.index = 0;

            return *this;
        }

        dynamic_array &operator=(std::initializer_list<T> list) {
            index = 0;

            for (const auto &item : list) {
                push_back(item);
            }

            return *this;
        }

        /**
         * A bidirectional iterator for the dynamic array;
         * used for for-ranges or standard algorithms.
         */
        class bidirectional_iterator {
        protected:
            dynamic_array<T, Size> &subject;
            size_t at;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = value_type *;
            using reference = value_type &;
            using iterator_category = std::bidirectional_iterator_tag;

            bidirectional_iterator(dynamic_array<T, Size> &subject)
                    : subject(subject), at(0) {}

            bidirectional_iterator(dynamic_array<T, Size> &subject, size_t start)
                    : subject(subject), at(start) {}

            bidirectional_iterator(const bidirectional_iterator &rhs)
                    : subject(rhs.subject), at(rhs.at) {}

            bidirectional_iterator(bidirectional_iterator &&rhs) {
                subject = rhs.subject;
                at = rhs.at;
            }

            bidirectional_iterator &operator=(const bidirectional_iterator &rhs) {
                subject = rhs.subject;
                at = rhs.at;
            }

            bidirectional_iterator &operator=(bidirectional_iterator &&rhs) {
                subject = rhs.subject;
                at = rhs.at;
            }

            bool operator==(const bidirectional_iterator &rhs) {
                return at == rhs.at
                       && std::addressof(subject) == std::addressof(rhs.subject);
            }

            bool operator!=(const bidirectional_iterator &rhs) {
                return !(*this == rhs);
            }

            reference operator*() {
                return subject.store[at];
            }

            pointer operator->() {
                return &subject.store[at];
            }

            /**
             * Pre-increment.
             *
             * @return
             */
            bidirectional_iterator &operator++() {
                at++;
                return *this;
            }

            /**
             * Post increment.
             *
             * @return
             */
            bidirectional_iterator operator++(int) {
                bidirectional_iterator temp(*this);
                operator++();
                return temp;
            }

            bidirectional_iterator &operator--() {
                at--;
            }

            bidirectional_iterator operator--(int) {
                bidirectional_iterator temp(*this);
                operator--();
                return temp;
            }
        };

        T &front() {
            return store[0];
        }

        T &back() {
            return store[index];
        }

        T *data() {
            return data;
        }

        bool empty() const {
            return size() == 0;
        }

        size_t size() const {
            return index;
        }

        size_t max_size() const {
            return Size;
        }

        void clear() {
            index = 0;
        }

        void insert(const size_t pos, const T &value) {
            free_position(pos);
            store[pos] = value;
            index++;
        }

        template<typename ...Args>
        void emplace(const size_t pos, Args &&... args) {
            free_position(pos);
            store[pos] = T(std::forward<Args>(args)...);
            index++;
        }

        void erase(const size_t pos) {
            if (pos == this->index) {
                this->index--;
                return;
            }

            // We don't set the data to zero; all items from the given
            // index on will be shifted one left in the array, overwriting the index to
            // remove. This makes removals expensive in the front of the array but prevents
            // fragmentation.
            for (size_t i = pos; i < this->index - 1; ++i) {
                store[i] = store[i + 1];
            }

            this->index--;
        }

        void erase(const size_t start, const size_t end) {
            for (size_t pos = end; pos != start; --pos) {
                erase(pos);
            }
        }

        void assign(size_t n, const T &val) {
            for (size_t i = 0; i < n; i++) {
                store[i] = val;
            }
        }

        void assign(std::initializer_list<T> list) {
            index = 0;

            for (const auto &item : list) {
                push_back(item);
            }
        }

        void push_back(const T &entry) {
            store[index++] = entry;
        }

        void push_back(T &&entry) {
            store[index++] = entry;
        }

        template<typename ...Args>
        void emplace_back(Args &&... args) {
            store[index++] = T(std::forward<Args>(args)...);
        }

        template<typename ...Args>
        void emplace_back(size_t pos, Args &&... args) {
            free_position(pos);
            store[pos] = T(std::forward<Args>(args)...);
        }

        void pop_back() {
            index--;
        }

        void swap(dynamic_array<T, Size> &other) {
            std::swap(store, other.store);
            std::swap(index, other.index);
        }

        T &operator[](const size_t index) {
            return store[index];
        }

        T operator[](const size_t index) const {
            return store[index];
        }

        /**
         * Begin function is provided for
         * std::begin(...).
         *
         * @return
         */
        bidirectional_iterator begin() {
            return bidirectional_iterator(*this);
        }

        const bidirectional_iterator begin() const {
            return bidirectional_iterator(*this);
        }

        /**
         * End function is provided for
         * std::end(...).
         *
         * @return
         */
        bidirectional_iterator end() {
            return bidirectional_iterator(*this, index);
        }

        const bidirectional_iterator end() const {
            return bidirectional_iterator(*this, index);
        }
    };

    template<typename T, size_t Size>
    bool operator==(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        for (int i = 0; i < Size; i++) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename T, size_t Size>
    bool operator!=(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !operator==(lhs, rhs);
    }

    template<typename T, size_t Size>
    bool operator<(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        for (int i = 0; i < Size; i++) {
            if (!(lhs[i] < rhs[i])) {
                return false;
            }
        }

        return true;
    }

    template<typename T, size_t Size>
    bool operator<=(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !(lhs < rhs);
    }

    template<typename T, size_t Size>
    bool operator>(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !(lhs < rhs);
    }

    template<typename T, size_t Size>
    bool operator>=(const dynamic_array<T, Size> &lhs, const dynamic_array<T, Size> &rhs) {
        return !(lhs < rhs);
    }
}

#endif //LLIB_DYNAMIC_ARRAY_HPP
