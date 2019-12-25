#ifndef LLIB_BASE_HPP
#define LLIB_BASE_HPP

#define register

#include "device_include.hpp"

// TODO: switch targets
namespace llib {
    namespace sam3x8e {
        namespace pins {}
    }    

    namespace imx1062 {
        namespace pins {}
    }

    namespace tests {
        namespace pins {}
    }

    namespace target = LLIB_TARGET;
    namespace pins = target::pins;
}

#endif //LLIB_BASE_HPP
