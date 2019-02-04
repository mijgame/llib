#include "uart.hpp"

void llib::due::detail::write_impl(char c) {
    uart::put_char(c);
}
