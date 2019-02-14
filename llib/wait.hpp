#ifndef LLIB_WAIT_HPP
#define LLIB_WAIT_HPP

#include <cstdint>

namespace llib {
    struct ns {
        uint32_t value;
    };

    struct us {
        uint32_t value;
    };

    struct ms {
        uint32_t value;
    };

    struct s {
        uint32_t value;
    };

    void wait_for(llib::ns ns);

    void wait_for(llib::us us);

    void wait_for(llib::ms ms);

    void wait_for(llib::s s);

    /**
     * Wait for the given amount of nanoseconds.
     * The implementation of this function is left to the
     * target and accuracy might very.
     *
     * Likely, this function is most accurate in the microsecond range.
     * @param ns
     */
    void wait_for(uint64_t ns);

    /**
     * Sleep for the given amount of nanoseconds.
     * The implementation of this function is left to the
     * target and accuracy might very.
     *
     * Likely, this function is most accurate in the microsecond range.
     */
    void sleep_for(uint64_t);
}

#endif //LLIB_WAIT_HPP
