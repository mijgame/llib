#ifndef LLIB_BASE_HPP
#define LLIB_BASE_HPP

#define register

#include "sam.h"

// TODO: switch targets
namespace llib {
    namespace due {
        namespace pins {}
    }

    namespace target = due;
    namespace pins = target::pins;
}

#endif //LLIB_BASE_HPP
