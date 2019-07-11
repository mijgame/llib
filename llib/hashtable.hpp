#ifndef LLIB_HASHTABLE_HPP
#define LLIB_HASHTABLE_HPP

#include <functional>
#include <bitset.hpp>

namespace llib {
    /**
     * A fixed capacity hashtable implementation.
     * It uses open addressing and linear probing internally.
     * The hashtable is meant for infrequent/known use, such as storing
     * configuration variables in a convenient way.
     *
     * The implementation is meant to be simple and compact; more
     * complex features (such as a more complex addressing schema or
     * probing type) demand more from the (often simple) microcontroller
     * and require more (flash) memory.
     *
     * @tparam Key
     * @tparam Value
     * @tparam Capacity
     * @tparam HashFunction
     */
    template<
        typename Key,
        typename Value,
        size_t Capacity = 64, // Multiples of 2 perform better!
        typename HashFunction = std::hash<Key>
    >
    class hashtable {
    protected:
        Key keys[Capacity];
        Value values[Capacity];

        bitset<Capacity> used;

        std::optional<int> find_position(const Key &key) const {
            auto hash = HashFunction{}(key) % Capacity;
            const auto original_hash = hash;

            while (used.test(hash) && !(keys[hash] == key)) {
                hash = (hash + 1) % Capacity;

                // We've wrapped around, no position available.
                if (hash == original_hash) {
                    return std::nullopt;
                }
            }

            return hash;
        }

    public:
        /**
         * Tries to retrieve a value from the
         * hashtable. If the optional is empty,
         * the value is not available in the hashtable.
         *
         * @param key
         * @return
         */
        std::optional<Value> get(const Key &key) const {
            const auto pos = find_position(key);

            if (!pos) {
                return std::nullopt;
            }

            return {values[*pos]};
        }

        /**
         * Copy a value into the hashtable.
         * Returns true if the value could be inserted,
         * false otherwise.
         *
         * @param key
         * @param value
         * @return
         */
        bool put(const Key &key, const Value &value) {
            const auto pos = find_position(key);

            if (!pos) {
                return false;
            }

            values[*pos] = value;

            return true;
        }

        /**
         * Move a value into the hashtable.
         * Returns true if the value could be inserted,
         * false otherwise.
         *
         * @param key
         * @param value
         * @return
         */
        bool put(const Key &key, Value &&value) {
            const auto pos = find_position(key);

            if (!pos) { // We're full!
                return false;
            }

            const auto index = *pos;

            keys[index] = value;
            values[index] = std::move(value);
            used.set(index);

            return true;
        }
    };
}

#endif //LLIB_HASHTABLE_HPP
