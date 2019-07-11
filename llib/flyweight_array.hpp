#ifndef LLIB_FLYWEIGHT_ARRAY_HPP
#define LLIB_FLYWEIGHT_ARRAY_HPP

#include <cstddef>
#include <algorithm>
#include <tuple>

namespace llib {
    template<typename T, size_t Size, size_t Cap>
    class flyweight_array;

    template<typename T, size_t Size, size_t Cap>
    class flyweight_reference {
        flyweight_array<T, Size, Cap> &arr;
        size_t index;

        flyweight_reference(
            flyweight_array<T, Size, Cap> &arr,
            size_t index
        ) noexcept : arr(arr), index(index) { }

    public:
        operator T() const noexcept;

        flyweight_reference &operator=(const T &x) noexcept;

        flyweight_reference &operator=(const flyweight_reference &other) noexcept;
    };

    /**
     * The flyweight array is used in situations
     * where there might be a lot of (large) objects
     * that are duplicated in memory, but should be stored
     * in an array.
     *
     * Internally, a list of instances and a list of indices
     * is kept. This allows the user to use the object just
     * like an array.
     *
     * @tparam T
     * @tparam Size
     * @tparam Cap
     */
    template<typename T, size_t Size, size_t Cap>
    class flyweight_array {
    protected:
        friend flyweight_reference<T, Size, Cap>;

        struct entry {
            size_t count;
            T instance;

            constexpr entry() : count(0), instance() {}

            constexpr explicit entry(const T &instance)
                : count(1), instance(instance) {}

            constexpr explicit entry(T &&instance)
                : count(1), instance(std::move(instance)) {}
        };

        entry store[Cap] = {};
        size_t indices[Size] = {};
        size_t indices_index = 0;

        /**
         * Try to find the item in the objects lists.
         * Otherwise return the first usable index for
         * the new object.
         *
         * If the bool is true, a refcount was used.
         * If the bool is false, the size_t contains the
         * location for the new object.
         *
         * @param item
         * @return
         */
        std::tuple<bool, size_t> try_refcount(const T &item) {
            constexpr size_t max_val = std::numeric_limits<size_t>::max();

            size_t pos = max_val;

            for (size_t i = 0; i < Cap; i++) {
                if (pos == max_val && store[i].count == 0) {
                    pos = i;
                }

                if (store[i].instance == item) {
                    store[i].count += 1;
                    indices[indices_index++] = i;

                    return std::tuple(true, i);
                }
            }

            return std::tuple(false, pos);
        }

        void decrease_refcount(const size_t index) {
            const size_t store_index = indices[index];

            // Make sure we don't underflow
            if (store[store_index].count <= 1) {
                store[store_index].count = 0;
            } else {
                store[store_index].count -= 1;
            }
        }

    public:
        constexpr flyweight_array() = default;

        constexpr void push(const T &item) {
            const auto[refcount, index] = try_refcount(item);

            if (refcount) {
                return;
            }

            store[index] = entry(item);
            indices[indices_index++] = index;
        }

        constexpr void emplace(T &&item) {
            const auto[refcount, index] = try_refcount(item);

            if (refcount) {
                return;
            }

            store[index] = std::move(item);
            indices[indices_index++] = index;
        }

        constexpr void erase(const size_t index) {
            const size_t store_index = indices[index];

            decrease_refcount(index);

            for (size_t i = store_index; i < indices_index; i++) {
                store[i] = store[i + 1];
            }

            indices_index -= 1;
        }

        constexpr flyweight_reference<T, Size, Cap> operator[](const size_t index) {

        }

        constexpr size_t max_size() const {
            return Size;
        }

        constexpr size_t max_object_capacity() const {
            return Cap;
        }
    };

    template<typename T, size_t Size, size_t Cap>
    flyweight_reference<T, Size, Cap>::operator T() const noexcept {
        return arr.store[
            arr.indices[index]
        ];
    }

    template<typename T, size_t Size, size_t Cap>
    flyweight_reference<T, Size, Cap> &flyweight_reference<T, Size, Cap>::operator=(const T &x) noexcept {
        const auto store_index = arr.indices[index];

        // If the values equal, there is nothing to do.
        if (arr.store[store_index] == x) {
            return *this;
        }

        // Decrement the old object ref counter
        arr.decrease_refcount(index);

        // Check if the value already exists on the array
        const auto [refcount, new_store_index] = arr.try_refcount(x);

        if (refcount) {
            // Make the index point to the new
            // store index
            arr.indices[index] = new_store_index;

            return *this;
        }

        // The value is new in the array
        // We don't use arr.push(...) here, because that would
        // cause another full iteration over the array
        arr.store[index] = x;
        arr.indices[arr.indices_index++] = new_store_index;

        return *this;
    }

    template<typename T, size_t Size, size_t Cap>
    flyweight_reference<T, Size, Cap> &flyweight_reference<T, Size, Cap>::operator=(const flyweight_reference &other) noexcept {
        *this = other.T();
        return *this;
    }
}

#endif //LLIB_FLYWEIGHT_ARRAY_HPP
