#ifndef LLIB_UTIL_HPP
#define LLIB_UTIL_HPP

namespace llib {
    // TODO: there are more algorithms to add here!
    // - block sort (fast stable sorting)
    // - nth element

    /**
     * Check if the predicate returns true for all members
     * in the container.
     *
     * @tparam Container
     * @tparam Predicate
     * @param container
     * @param p
     * @return
     */
    template<typename Container, typename Predicate>
    bool all_of(const Container &container, Predicate p) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for (; first != last; ++first) {
            if (!p(*first)) {
                return false;
            }
        }

        return true;
    }

    /**
     * Check if the predicate returns true for any members
     * in the container.
     *
     * @tparam Container
     * @tparam Predicate
     * @param container
     * @param p
     * @return
     */
    template<typename Container, typename Predicate>
    bool any_of(const Container &container, Predicate p) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for (; first != last; ++first) {
            if (p(*first)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Check if the predicate returns true for no members
     * in the container.
     *
     * @tparam Container
     * @tparam Predicate
     * @param container
     * @param p
     * @return
     */
    template<typename Container, typename Predicate>
    bool none_of(const Container &container, Predicate p) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for (; first != last; ++first) {
            if (p(*first)) {
                return false;
            }
        }

        return true;
    }

    /**
     * Call a function on each element in the container.
     *
     * @tparam Container
     * @tparam Function
     * @param container
     * @param f
     * @return
     */
    template<typename Container, typename Function>
    constexpr Function for_each(const Container &container, Function f) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for (; first != last; ++first) {
            f(*first);
        }

        return f;
    }

    /**
     * Call a function on the first n elements in the container.
     *
     * @tparam Container
     * @tparam Function
     * @param container
     * @param f
     * @return
     */
    template<typename Container, typename Function>
    constexpr auto for_each_n(const Container &container, size_t n, Function f) -> decltype(std::cbegin(container)) {
        auto first = std::cbegin(container);

        for (size_t i = 0; i < n; ++first, ++i) {
            f(*first);
        }

        return first;
    }

    /**
     * Count how many elements are equal to
     * the given value.
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename T>
    constexpr size_t count(const Container &container, const T& value) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        size_t result = 0;

        for (; first != last; ++first) {
            if (*first == value) {
                result += 1;
            }
        }

        return result;
    }

    /**
     * Count how many elements match the
     * given predicate.
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename Predicate>
    constexpr size_t count_if(const Container &container, Predicate p) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        size_t result = 0;

        for (; first != last; ++first) {
            if (p(*first)) {
                result += 1;
            }
        }

        return result;
    }

    /**
     * Find the first of the given value in the container.
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename T>
    constexpr auto find(const Container &container, const T &value) -> decltype(std::cbegin(container)) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for(; first != last; ++first) {
            if (*first == value) {
                return first;
            }
        }

        return last;
    }

    /**
     * Find the first value in the container that matches the
     * given predicate.
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename Predicate>
    constexpr auto find_if(const Container &container, Predicate p) -> decltype(std::cbegin(container)) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for(; first != last; ++first) {
            if (p(*first)) {
                return first;
            }
        }

        return last;
    }

    /**
     * Searches the container for two consecutive identical elements.
     *
     * @tparam Container
     * @param container
     * @return
     */
    template<typename Container>
    constexpr auto adjacent_find(const Container &container) -> decltype(std::cbegin(container)) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        if (first == last) {
            return last;
        }

        auto next = first;
        ++next;

        for (; next != last; ++next, ++first) {
            if (*first == *next) {
                return first;
            }
        }

        return last;
    }

    /**
     * Searches the container for two consecutive identical elements.
     * The comparator is used for comparison.
     *
     * @tparam Container
     * @param container
     * @return
     */
    template<typename Container, typename Comparator>
    constexpr auto adjacent_find(const Container &container, Comparator c) -> decltype(std::cbegin(container)) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        if (first == last) {
            return last;
        }

        auto next = first;
        ++next;

        for (; next != last; ++next, ++first) {
            if (c(*first, *next)) {
                return first;
            }
        }

        return last;
    }

    /**
     * Find the first value in the container that does not
     * match the given predicate.
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename Predicate>
    constexpr auto find_if_not(const Container &container, Predicate p) -> decltype(std::cbegin(container)) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for(; first != last; ++first) {
            if (!p(*first)) {
                return first;
            }
        }

        return last;
    }

    /**
     * Fill the given container with the given value.
     *
     * Notice: this function fills the container using an iterator using std::begin and
     * std::end. This means only previously set elements will be overwritten and empty
     * containers will see no change. To fill the container until a given index see fill_n
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename T>
    constexpr void fill(Container &container, const T &value) {
        auto first = std::begin(container);
        auto last = std::end(container);

        for (; first != last; ++first) {
            *first = value;
        }
    }

    /**
    * Fill the given container with the given value until the nth position.
    *
    * @tparam Container
    * @tparam T
    * @param container
    * @param value
    * @return
    */
    template<typename Container, typename T>
    constexpr void fill_n(Container &container, size_t n, const T &value) {
        auto first = std::begin(container);

        for (size_t i = 0; i < n; i++, ++first) {
            *first = value;
        }
    }

    /**
     * Fill the given container with the value generated by the given function.
     *
     * Notice: this function fills the container using an iterator using std::begin and
     * std::end. This means only previously set elements will be overwritten and empty
     * containers will see no change. To fill the container until a given index see generate_n
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename Generator>
    constexpr void generate(Container &container, Generator g) {
        auto first = std::begin(container);
        auto last = std::end(container);

        for (; first != last; ++first) {
            *first = g();
        }
    }

    /**
    * Fill the given container with the value generated by
    * the given function until the nth position.
    *
    * @tparam Container
    * @tparam T
    * @param container
    * @param value
    * @return
    */
    template<typename Container, typename Generator>
    constexpr void generate_n(Container &container, size_t n, Generator g) {
        auto first = std::begin(container);

        for (size_t i = 0; i < n; i++, ++first) {
            *first = g();
        }
    }

    /**
     * Call a function for every element in the given container.
     * The result of this function is stored instead of the original value.
     *
     * @tparam Container
     * @tparam Operation
     * @param container
     * @param op
     * @return
     */
    template<typename Container, typename Operation>
    constexpr void transform(Container &container, Operation op) {
        auto first = std::begin(container);
        auto last = std::end(container);

        for (; first != last; ++first) {
            *first = op(*first);
        }
    }

    /**
     * Reverse the contents of the container.
     * This requires the container to have at least a
     * bidirectional iterator.
     *
     * @tparam Container
     * @param container
     * @return
     */
    template<typename Container>
    constexpr void reverse(Container &container) {
        auto first = std::begin(container);
        auto last = std::end(container);

        while ((first != last) && (first != --last)) {
            std::swap(*first, *last);
            first++;
        }
    }

    /**
     * Sort the given container using
     * insertion sort. This function uses operator[] and
     * is meant to be compact.
     *
     * @tparam Container
     * @param container
     * @return
     */
    template<typename Container>
    constexpr void insertion_sort(Container &container) {
        size_t i = 0;
        while (i != container.size()) {
            if (i > 0 && container[i] < container[i - 1]) {
                std::swap(container[i], container[i - 1]);
                i -= 1;
            } else {
                i += 1;
            }
        }
    }

    /**
     * Execute binary search to find the given value.
     * This function requires operator[] to be defined on the container
     * and will return the index the item is found at, or -1 if the item
     * isn't found. This function is meant to be compact.
     *
     * This function requires the container to be sorted.
     * Otherwise the behaviour is undefined.
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param value
     * @return
     */
    template<typename Container, typename T>
    constexpr int binary_search(const Container &container, const T &value) {
        size_t lower = 0;
        size_t upper = container.size();

        while (lower < upper) {
            size_t x = lower + (upper - lower) / 2;
            const T &val = container[x];

            if (value == val) {
                return x;
            } else if (value > val) {
                if (lower == x) {
                    break;
                }

                lower = x;
            } else if (value < val) {
                upper = x;
            }
        }

        return -1;
    }

    /**
     * Find the largest element in the given container.
     *
     * @tparam Container
     * @param container
     * @return
     */
    template<typename Container>
    constexpr auto max_element(const Container &container) -> decltype(std::begin(container)) {
        auto first = std::begin(container);
        auto last = std::end(container);

        if (first == last) {
            return last;
        }

        auto largest = first;
        ++first;

        for (; first != last; ++first) {
            if (*largest < *first) {
                largest = first;
            }
        }

        return largest;
    }

    /**
     * Find the largest element in the given container, using the given
     * comparator function.
     *
     * @tparam Container
     * @tparam Comparator
     * @param container
     * @param comp
     * @return
     */
    template<typename Container, typename Comparator>
    constexpr auto max_element(const Container &container, Comparator comp) -> decltype(std::begin(container)) {
        auto first = std::begin(container);
        auto last = std::end(container);

        if (first == last) {
            return last;
        }

        auto largest = first;
        ++first;

        for (; first != last; ++first) {
            if (comp(*largest, *first)) {
                largest = first;
            }
        }

        return largest;
    }

    /**
     * Find the smallest element in the given container.
     *
     * @tparam Container
     * @param container
     * @return
     */
    template<typename Container>
    constexpr auto min_element(const Container &container) -> decltype(std::begin(container)) {
        auto first = std::begin(container);
        auto last = std::end(container);

        if (first == last) {
            return last;
        }

        auto smallest = first;
        ++first;

        for (; first != last; ++first) {
            if (*first < *smallest) {
                smallest = first;
            }
        }

        return smallest;
    }

    /**
     * Find the smallest element in the given container, using the given
     * comparator function.
     *
     * @tparam Container
     * @tparam Comparator
     * @param container
     * @param comp
     * @return
     */
    template<typename Container, typename Comparator>
    constexpr auto min_element(const Container &container, Comparator comp) -> decltype(std::begin(container)) {
        auto first = std::begin(container);
        auto last = std::end(container);

        if (first == last) {
            return last;
        }

        auto smallest = first;
        ++first;

        for (; first != last; ++first) {
            if (comp(*first, *smallest)) {
                smallest = first;
            }
        }

        return smallest;
    }

    /**
     * Sum all the values in the container to the initial value.
     *
     * @tparam Container
     * @tparam T
     * @param container
     * @param init
     * @return
     */
    template<typename Container, typename T>
    constexpr T accumulate(const Container &container, T init) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for (; first != last; ++first) {
            init = std::move(init) + *first;
        }

        return init;
    }

    /**
     * Sum all the values in the container over the given operator
     * to the initial value.
     *
     * @tparam Container
     * @tparam T
     * @tparam Operator
     * @param container
     * @param init
     * @param op
     * @return
     */
    template<typename Container, typename T, typename Operator>
    constexpr T accumulate(const Container &container, T init, Operator op) {
        auto first = std::cbegin(container);
        auto last = std::cend(container);

        for (; first != last; ++first) {
            init = op(std::move(init), *first);
        }

        return init;
    }

    template<typename Container>
    constexpr void shift_left(Container &container, size_t n) {
        auto first = std::begin(container);
        auto last = std::end(container);

        if (n == 0 || first == last) {
            return;
        }

        auto prev = first;
        ++first;

        for (size_t i = 0; i < n; i++, ++prev, ++first) {
            *prev = *first;

            if (prev == last) {
                return;
            }
        }
    }
}

#endif //LLIB_UTIL_HPP
