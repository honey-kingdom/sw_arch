// Need to be compiled with -lstdc++ --std=c++14 options
#include <iostream>
#include <functional>
#include <chrono>

auto decorator(std::function<void()> original_function) {
    return [=]() { // returns a capturing lambda
        auto t0 = std::chrono::high_resolution_clock::now();

        original_function();

        auto duration = std::chrono::high_resolution_clock::now() - t0;

        std::cout << "\nElapsed " << duration.count() * 1000.0f << " ms\n";
    };
}

void helloworld() {
    for (auto i = 0; i < 10; i++)
        std::cout << "Hello, World!\n";
}

int main() {
    auto my_helloworld = decorator(helloworld);
    my_helloworld(); // Lambda is a class with () operator overloaded

    auto my_my_helloworld = decorator(decorator(helloworld));
    my_my_helloworld();

    return 0;
}
