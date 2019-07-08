#include <iostream>

class DvmLogger {
private:
    static bool enabled;
    static DvmLogger * logger;

    DvmLogger() { std::cout << "DVM Logger Constructed" << std::endl; }

public:
    static void setEnabled(bool new_enabled) { enabled = new_enabled; }
    static bool getEnabled(void) { return enabled; }

    static DvmLogger & getLogDebug() {
        if (logger == nullptr)
            logger = new DvmLogger();

        return *logger;
    }

    DvmLogger & operator<<(std::string message) {
        std::cout << "[logdebug.txt] " << message << std::endl;

        return *this;
    }
};

bool DvmLogger::enabled = false;
DvmLogger * DvmLogger::logger = nullptr;

#define LOGDEBUG \
    if (!DvmLogger::getEnabled()) {} \
    else DvmLogger::getLogDebug()


int main() {
    DvmLogger::setEnabled(true);
    //DvmLogger aa;
    LOGDEBUG << "1st tc2tf output";
    LOGDEBUG << "2nd tc2tf output";
    LOGDEBUG << "3rd tc2tf output"
             << "Simulation Completed";
}
