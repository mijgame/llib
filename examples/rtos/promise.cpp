#include "rtos/rtos.hpp"
#include "rtos/promise.hpp"

using namespace llib::rtos;

promise<int> fetch_some_info() {
    return rtos::async([] {
        // Fetch some information
    });
}

int main() {
    auto promise = fetch_some_info();
    auto future = promise.get_future();

    // Execute some code

    // Wait for the result...
    int result = future.get();
}