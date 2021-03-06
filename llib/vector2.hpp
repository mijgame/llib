#ifndef LLIB_VECTOR2_HPP
#define LLIB_VECTOR2_HPP

#include <math.hpp>

namespace llib {
    /**
     * Templated 2-dimensional vector
     * class.
     *
     * @tparam T
     */
    template<typename T>
    struct vector2 {
        T x;
        T y;

        /**
         * Default; initialize to zero.
         */
        constexpr vector2() : x(0), y(0) {}

        /**
         * Initialize the vector with the given
         * values.
         *
         * @param x
         * @param y
         */
        constexpr vector2(T x, T y)
            : x(x), y(y) {}

        /**
         * Initialize both values with
         * the given value.
         *
         * @param val
         */
        constexpr explicit vector2(T val)
            : x(val), y(val) {}

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator+(const vector2 &other) const {
            return vector2(x + other.x, y + other.y);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator+=(const vector2 &other) {
            x += other.x;
            y += other.y;

            return *this;
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator+(T other) const {
            return vector2(x + other, y + other);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator+=(T other) {
            x += other.x;
            y += other.y;

            return *this;
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator-(const vector2 &other) const {
            return vector2(x - other.x, y - other.y);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator-=(const vector2 &other) {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator-(T other) const {
            return vector2(x - other.x, y - other.y);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator-=(T other) {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator*(const vector2 &other) const {
            return vector2(x * other.x, y * other.y);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator*=(const vector2 &other) {
            x *= other.x;
            y *= other.y;

            return *this;
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator*(T other) const {
            return vector2(x * other.x, y * other.y);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator*=(T other) {
            x *= other.x;
            y *= other.y;

            return *this;
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator/(const vector2 &other) const {
            return vector2(x / other.x, y / other.y);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator/=(const vector2 &other) {
            x /= other.x;
            y /= other.y;

            return *this;
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 operator/(T other) const {
            return vector2(x / other.x, y / other.y);
        }

        /**
         * @param other
         * @return
         */
        constexpr vector2 &operator/=(T other) {
            x /= other.x;
            y /= other.y;

            return *this;
        }

        /**
         * Helper function for casting a
         * vector to another vector.
         *
         * @tparam U
         * @return
         */
        template<typename U>
        constexpr vector2<U> cast() const {
            return vector2<U>(
                static_cast<U>(x),
                static_cast<U>(y)
            );
        }
    };

    // some nice aliases
    using vector2i = vector2<int_fast32_t>;
    using vector2u = vector2<uint_fast32_t>;
}

#endif //LLIB_VECTOR2_HPP
