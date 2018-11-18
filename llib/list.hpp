#ifndef LLIB_LIST_HPP
#define LLIB_LIST_HPP

#include <cstddef>

#include "bitset.hpp"
#if 0
namespace llib {
    template<typename T, size_t MaxSize>
    class list {
    private:
        struct list_entry {
            T item;
            size_t loc;
            list_entry *previous = nullptr;
            list_entry *next = nullptr;

            list_entry(T item, size_t loc)
                    : item(item), loc(loc) {}

            list_entry(T &&item, size_t loc)
                    : item(std::move(item)) {}
        };


        // TODO: move memory management to separate class
        list_entry store[MaxSize];
        bitset<MaxSize> used;

        list_entry *start = nullptr;
        list_entry *end = nullptr;

        size_t allocate_loc() {
            size_t loc = MaxSize + 1; // explicitly out of range
            for (size_t i = 0; i < MaxSize; i++) {
                if (used.test(i)) {
                    continue;
                }

                loc = i;
                break;
            }

            used.set(loc, true);

            return loc;
        }

        void clear_entry(list_entry &entry) {
            entry.item.~T();
            used.reset(entry.loc);
        }

        list_entry &get_entry(const T &item) {
            auto loc = allocate_loc();
            store[loc] = list_entry(item);
            return store[loc];
        }

        list_entry &get_entry(T &&item) {
            auto loc = allocate_loc();
            store[loc] = list_entry(std::move(item));
            return store[loc];
        }

        void set_start(list_entry &entry) {
            if (!start) {
                start = entry;
                end = entry;
            } else {
                list_entry *tmp = start;
                start = entry;
                tmp->previous = start;
                start->next = tmp;
            }
        }

        void set_end(list_entry &entry) {
            if (!start) {
                start = entry;
                end = entry;
            } else {
                list_entry *tmp = end;
                end = entry;
                tmp->next = end;
                end->previous = tmp;
            }
        }

    public:
        list() = default;

        /**
         * A bidirectional iterator for the dynamic array;
         * used for for-ranges or standard algorithms.
         */
        class bidirectional_iterator {
        protected:
            list<T, MaxSize> &subject;
            list_entry *at;

            friend list;

        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = value_type *;
            using reference = value_type &;
            using iterator_category = std::bidirectional_iterator_tag;

            bidirectional_iterator(list<T, MaxSize> &subject)
                    : subject(subject), at(0) {}

            bidirectional_iterator(list<T, MaxSize> &subject, list_entry *start)
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
                return at->item;
            }

            pointer operator->() {
                return &at->item;
            }

            /**
             * Pre-increment.
             *
             * @return
             */
            bidirectional_iterator &operator++() {
                at = at->next;
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
                at = at->previous;
            }

            bidirectional_iterator operator--(int) {
                bidirectional_iterator temp(*this);
                operator--();
                return temp;
            }
        };

        bool empty() const {
            return used.none();
        }

        size_t size() const {
            return static_cast<size_t>(used.count());
        }

        size_t max_size() const {
            return MaxSize;
        }

        T &first() {
            return *start;
        }

        T first() const {
            return *start;
        }

        T &back() {
            list_entry *it = start;

            while (it->next != nullptr) {
                it = it->next;
            }

            return it->item;
        }

        T back() const {
            list_entry *it = start;

            while (it->next != nullptr) {
                it = it->next;
            }

            return it->item;
        }

        template<typename ...Args>
        void emplace_front(Args&&... args) {
            T t(std::forward<Args>(args)...);

            auto &entry = get_entry(std::move(t));
            set_start(entry);
        }

        void push_front(const T &val) {
            auto &entry = get_entry(val);
            set_start(entry);
        }

        void push_front(T &&val) {
            auto &entry = get_entry(std::move(val));
            set_start(entry);
        }

        void pop_front() {
            list_entry *next = start->next;
            clear_entry(start);
            start = next;
        }

        template<typename ...Args>
        void emplace_back(Args&&... args) {
            T t(std::forward<Args>(args)...);

            auto &entry = get_entry(std::move(t));

            set_end(entry);
        }

        void push_back(const T &val) {
            auto &entry(get_entry(val));
            set_end(entry);
        }

        void push_back(T &&val) {
            auto &entry = get_entry(std::move(val));
            set_end(entry);
        }

        void pop_back() {
            list_entry *prev = end->previous;
            clear_entry(end);
            end = prev;
        }

        template<typename ...Args>
        void emplace(const bidirectional_iterator &it, Args&&... args) {
            T t(std::forward<Args>(args)...);
        }

        void insert(const bidirectional_iterator &it, const T &value) {
            auto &entry = get_entry(value);
            // TODO: what if any value is null?
            auto* next = it.at->next;

            it.at->next = entry;
            next->previous = entry;
            entry->next = next;
            entry.previous = it.at;
        }

        void insert(const bidirectional_iterator &it, T &&value) {
            auto &entry = get_entry(std::move(value));
            // TODO: what if any value is null?
            auto* next = it.at->next;

            it.at->next = entry;
            next->previous = entry;
            entry->next = next;
            entry.previous = it.at;
        }

        void swap(list &x) {
            std::swap(store, x.store);
            std::swap(used, x.used);
            std::swap(start, x.start);
            std::swap(end, x.end);
        }

        void clear() {
            for (int i = 0; i < MaxSize; i++) {
                if (used.test(i)) {
                    clear_entry(store[i]);
                }
            }

            start = nullptr;
            end = nullptr;
        }

        void remove(const T& value) {
            // TODO: finish
            list_entry *it = start;

            while(it != nullptr) {
                if (it->item == value) {

                }

                it = it->next;
            }
        }
    };
}
#endif
#endif //LLIB_LIST_HPP
