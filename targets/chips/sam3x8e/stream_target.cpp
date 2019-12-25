#include "uart.hpp"
#include "stream_target.hpp"

void llib::sam3x8e::detail::write_impl(char c) {
    sam3x8e::uart::put_char(c);
}

char llib::sam3x8e::detail::read_impl() {
    return sam3x8e::uart::get_char();
}