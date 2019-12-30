#ifndef LLIB_BASE_HPP
#define LLIB_BASE_HPP

#define register

#include "device_include.hpp"

// TODO: switch targets
namespace llib {
    namespace sam3x8e {
        namespace due {
            namespace pins {}
        }
    }    

    namespace imx1062 {
        namespace teensy_4 {
            namespace pins {}
        }
    }

    namespace lpc2138 {
        namespace mcb2130 {
            namespace pins {}
        }
    }

    namespace tests {
        namespace tests {
            namespace pins {}
        }
    }

    namespace target = LLIB_TARGET;
    namespace pins = target::LLIB_BOARD::pins;
}

#endif //LLIB_BASE_HPP
