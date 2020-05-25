#include <iostream>

#include "stream_target.hpp"

void llib::tests::detail::write_impl(char c) {
    // write character to cout
    std::cout << c;
}

char llib::tests::detail::read_impl() {
    char t;
    // get a character from cin
    std::cin >> t;

    return t;
}