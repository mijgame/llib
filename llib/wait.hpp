#ifndef LLIB_WAIT_HPP
#define LLIB_WAIT_HPP

#include <units.hpp>

namespace llib {
    void wait_for(llib::us us);

    void wait_for(llib::ms ms);

    void wait_for(llib::s s);
}

#endif //LLIB_WAIT_HPP
