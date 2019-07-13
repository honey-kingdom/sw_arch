#include <iostream>
#include <chrono>

class Interface {
public:
    virtual void doIt() = 0;
    virtual ~Interface() {}
};

class HelloWorld: public Interface {
public:
    void doIt() override {
        for (auto i = 0; i < 10; i++)
            std::cout << "Hello, World!\n";
    }
};

class Decorator: public Interface {
private:
    Interface * original_function;

public:
    Decorator(Interface * original_function) : original_function(original_function) {}

    virtual void doIt() override {
        original_function->doIt();
    }
};

class Timer: public Decorator {
public:
    Timer(Interface * original_function) : Decorator(original_function) {}

    virtual void doIt() override {
        auto t0 = std::chrono::high_resolution_clock::now();

        Decorator::doIt();

        auto duration = std::chrono::high_resolution_clock::now() - t0;

        std::cout << "\nElapsed " << duration.count() * 1000.0f << " ms\n";
    }
};

class Logger: public Decorator {
public:
    Logger(Interface * original_function) : Decorator(original_function) {}

    virtual void doIt() override {
        Decorator::doIt();
        std::cout << "Output files have been generated.\n";
    }
};


int main(void) {
    auto aa = new Logger(new Timer(new HelloWorld()));

    aa->doIt();
}
