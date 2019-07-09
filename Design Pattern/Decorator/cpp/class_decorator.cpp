#include <iostream>
#include <chrono>

class Decorator {
private:
    void (*original_function)();

public:
    Decorator(void (*original_function)()) : original_function(original_function) {}

    void operator()(void) {
        auto t0 = std::chrono::high_resolution_clock::now();

        original_function();

        auto duration = std::chrono::high_resolution_clock::now() - t0;

        std::cout << "\nElapsed " << duration.count() * 1000.0f << " ms\n";
    }
};

void helloworld(void) {
    for (auto i = 0; i < 10; i++)
        std::cout << "Hello, World!\n";
}


int main(void) {
    auto my_helloworld = Decorator(helloworld);

    my_helloworld();
}
