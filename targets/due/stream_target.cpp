#include "uart.hpp"
#include "stream_target.hpp"

void llib::due::detail::write_impl(char c) {
    uart::put_char(c);
}

char llib::due::detail::read_impl() {
    return uart::get_char();
}