#ifndef LLIB_UNITS_HPP
#define LLIB_UNITS_HPP

#include <stdint.h>

namespace llib {
    /*
    * Time
    */
    struct us {
        uint32_t value;

        constexpr us() : value(0) {}
        constexpr us(uint32_t us) : value(us) {}
    };

    struct ms {
        uint32_t value;

        constexpr ms() : value(0) {}
        constexpr ms(uint32_t ms) : value(ms) {}
    };

    struct s {
        uint32_t value;

        constexpr s() : value(0) {}
        constexpr s(uint32_t s) : value(s) {}
    };


    /*
     * Frequency
     *
     * These functions generally miss nanosecond functions, because
     * it would simply not fit into a 32 bits unsigned integer.
     */
    struct centihertz {
        uint32_t value;

        constexpr centihertz(uint32_t chz) : value(chz) {}

        constexpr centihertz() : value (0) {}

        constexpr static centihertz from_us(const uint32_t us) {
            return centihertz{us * 100'000'000};
        }

        constexpr static centihertz from(const llib::us us) {
            return from_us(us.value);
        }

        constexpr static centihertz from_ms(const uint32_t ms) {
            return centihertz{ms * 100'000};
        }

        constexpr static centihertz from(const llib::ms ms) {
            return from_ms(ms.value);
        }

        constexpr static centihertz from_s(const uint32_t s) {
            return centihertz{s * 100};
        }

        constexpr static centihertz from(const llib::s s) {
            return from_s(s.value);
        }
    };

    struct hertz {
        uint32_t value;

        constexpr hertz(uint32_t hz) : value(hz) {}

        constexpr hertz(centihertz chz) : value (chz.value / 100) {}

        constexpr hertz() : value(0) {}

        constexpr static hertz from_us(const uint32_t us) {
            return hertz{us * 1'000'000};
        }

        constexpr static hertz from(const llib::us us) {
            return from_us(us.value);
        }

        constexpr static hertz from_ms(const uint32_t ms) {
            return hertz{ms * 1'000};
        }

        constexpr static hertz from(const llib::ms ms) {
            return from_ms(ms.value);
        }

        constexpr static hertz from_s(const uint32_t s) {
            return hertz{s};
        }

        constexpr static hertz from(const llib::s s) {
            return from_s(s.value);
        }

        operator centihertz() const {
            return centihertz{value * 100};
        }
    };
}

#endif //LLIB_UNITS_HPP
