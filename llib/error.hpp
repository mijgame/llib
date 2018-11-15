#ifndef LLIB_ERROR_HPP
#define LLIB_ERROR_HPP

#include "stream.hpp"

#define LLIB_ERROR(message) {           \
    ::llib::uart::init();               \
    ::llib::cout << "ERROR ("           \
                 << __file_ << ':'      \
                 << __line__ << "): "   \
                 << message             \
                 << ::llib::endl;       \
}

#endif //LLIB_ERROR_HPP
