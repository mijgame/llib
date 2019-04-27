#include <uart.hpp>
#include <watchdog.hpp>

#include "llib/wait.hpp"
#include "llib/string.hpp"

int main() {
    llib::target::watchdog::disable();
    llib::target::uart::init();

    const llib::string hello("Hello");
    llib::string world("World!");

    const auto combined = hello + ' ' + world;

    world = "Sailer!";

    const auto copy = hello + ' ' + world;

    const llib::string<64> other_string = {'A', 'B', 'C'};

    const llib::string foo("12345", 3);
    const llib::string bar(foo, 2);

    const std::initializer_list<char> chars = {'T', 'E', 'S', 'T'};
    const llib::string quux(chars.begin(), chars.end());

    const llib::string filled('x', 3);

    const llib::string iter_from_other(filled.begin(), filled.end());
    const auto smaller = iter_from_other.to_smaller_buffer<4>();

    for (;;) {
        llib::cout << "Combi:            " << combined << llib::endl;
        llib::cout << "Combi adjusted:   " << copy << llib::endl;
        llib::cout << "Initializer list: " << other_string << llib::endl;
        llib::cout << "Partial copy:     " << foo << llib::endl;
        llib::cout << "Partial str copy: " << bar << llib::endl;
        llib::cout << "Input iterator:   " << quux << llib::endl;
        llib::cout << "Filled:           " << filled << llib::endl;
        llib::cout << "Iter from other:  " << iter_from_other<< llib::endl;
        llib::cout << "Smaller buffer:   " << smaller << llib::endl;
        llib::cout << "Front:            " << combined.front() << llib::endl;
        llib::cout << "Back:             " << combined.back() << llib::endl;
        llib::cout << "Starts with:      " << combined.starts_with("Hello") << llib::endl;
        llib::cout << "Ends with:        " << combined.ends_with("Hello") << llib::endl;

        llib::cout << llib::endl;

        llib::wait_for(4_s);
    }
}