#ifndef LLIB_BASE_HPP
#define LLIB_BASE_HPP

#define register

// #include "sam.h"

// TODO: switch targets
namespace llib {
    namespace due {
        namespace pins {}
    }

    namespace teensy {
        namespace pins {}
    }

    namespace tests {
        namespace pins {}
    }

    namespace target = LLIB_TARGET;
    namespace pins = target::pins;
}

#endif //LLIB_BASE_HPP
