#ifndef LLIB_WAIT_HPP
#define LLIB_WAIT_HPP

#include <cstdint>

/**
 * Literal for nanoseconds. Nanoseconds
 * are the base unit for timing things like waits.
 *
 * @param value
 * @return
 */
constexpr uint64_t operator"" _ns(unsigned long long value) {
    return value;
}

/**
 * Literal for microseconds.
 *
 * @param value
 * @return
 */
constexpr uint64_t operator"" _us(unsigned long long value) {
    return operator""_ns(value) * 1000;
}

/**
 * Literal for milliseconds.
 *
 * @param value
 * @return
 */
constexpr uint64_t operator"" _ms(unsigned long long value) {
    return operator""_us(value) * 1000;
}

/**
 * Literal for seconds.
 *
 * @param value
 * @return
 */
constexpr uint64_t operator"" _s(unsigned long long value) {
    return operator""_ms(value) * 1000;
}

namespace llib {
    /**
     * Wait for the given amount of nanoseconds.
     * The implementation of this function is left to the
     * target and accuracy might very.
     *
     * Likely, this function is most accurate in the microsecond range.
     * @param ns
     */
    void wait_for(uint64_t ns);
}

#endif //LLIB_WAIT_HPP
