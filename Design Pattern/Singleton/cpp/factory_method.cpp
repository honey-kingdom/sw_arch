#include <iostream>

class DvmLogger;

class LoggerFactory {
public:
    DvmLogger & getLogDebug();
};

class DvmLogger {
private:
    DvmLogger() { std::cout << "DVM Logger Constructed" << std::endl; }

    friend class LoggerFactory;

public:
    DvmLogger & operator<<(std::string message) {
        std::cout << "[logdebug.txt] " << message << std::endl;

        return *this;
    }
};

DvmLogger & LoggerFactory::getLogDebug() {
    static DvmLogger * logger = nullptr;
    
    if (logger == nullptr)
        logger = new DvmLogger();

    return *logger;
}



int main() {
    LoggerFactory aa;

    auto x = aa.getLogDebug();
    x << "1st tc2tf output";

    auto y = aa.getLogDebug();
    y << "2nd tc2tf output";

    return 0;
}
