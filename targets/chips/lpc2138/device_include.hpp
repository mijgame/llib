#include <stdint.h>

/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ             (uint8_t)__builtin_clz

#include "lpc2138.hpp"