#ifndef LLIB_ERROR_HPP
#define LLIB_ERROR_HPP

#ifndef LLIB_DISABLE_MESSAGES
#include "stream.hpp"

#define LLIB_WARNING(message) {           \
    ::llib::cout << "WARNING ("           \
                 << __FILE__ << ':'       \
                 << __LINE__ << "): "     \
                 << message               \
                 << ::llib::endl;         \
}

#define LLIB_ERROR(message) {           \
    ::llib::cout << "ERROR ("           \
                 << __FILE__ << ':'     \
                 << __LINE__ << "): "   \
                 << message             \
                 << ::llib::endl;       \
    for(;;){}                           \
}
#else
#define LLIB_WARNING(message)
#define LLIB_ERROR(message)
#endif

#endif //LLIB_ERROR_HPP
