#ifndef LLIB_DYNAMIC_ARRAY_HPP
#define LLIB_DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <utility>
#include <iterator>

namespace llib {
    template<typename T, size_t Size>
    class dynamic_array {
    protected:
        T data[Size] = {};
        size_t index = 0;

    public:
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

            bidirectional_iterator(const bidirectional_iterator &rhs) {
                subject = rhs.subject;
                at = rhs.at;
            }

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

            void swap(bidirectional_iterator &iter) {
                std::swap(at, iter.at);
                std::swap(subject, iter.subject);
            }

            bool operator==(const bidirectional_iterator &rhs) {
                return at == rhs.at
                       && std::addressof(subject) == std::addressof(rhs.subject);
            }

            bool operator!=(const bidirectional_iterator &rhs) {
                return !(*this == rhs);
            }

            reference operator*() {
                return subject.data[at];
            }

            pointer operator->() {
                return &subject.data[at];
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

        void add(const T &entry) {
            data[index++] = entry;
        }

        template<typename ...Args>
        void emplace(Args &&... args) {
            data[index++] = T(std::forward<Args>(args)...);
        }

        void set(const T &entry, const size_t index) {
            data[index] = entry;
        }

        bool contains(const T &entry) const {
            for (size_t i = 0; i < index; i++) {
                if (data[i] == entry) {
                    return true;
                }
            }

            return false;
        }

        void remove(const size_t index) {
            if (index == this->index) {
                this->index--;
                return;
            }

            // We don't set the data to zero; all items from the given
            // index on will be shifted one left in the array, overwriting the index to
            // remove. This makes removals expensive in the front of the array but prevents
            // fragmentation.
            for (size_t i = index; i < this->index - 1; i++) {
                data[i] = data[i + 1];
            }

            this->index--;
        }

        size_t size() const {
            return index;
        }

        constexpr size_t capacity() const {
            return Size;
        }

        T &operator[](const size_t index) {
            return data[index];
        }

        T operator[](const size_t index) const {
            return data[index];
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
}

#endif //LLIB_DYNAMIC_ARRAY_HPP
