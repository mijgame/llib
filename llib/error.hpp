#ifndef LLIB_ERROR_HPP
#define LLIB_ERROR_HPP

#include "stream.hpp"

#define LLIB_ERROR(message) {           \
    ::llib::cout << "ERROR ("           \
                 << __FILE__ << ':'      \
                 << __LINE__ << "): "   \
                 << message             \
                 << ::llib::endl;       \
}

#endif //LLIB_ERROR_HPP
