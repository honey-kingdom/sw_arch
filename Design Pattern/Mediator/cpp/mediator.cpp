#include <iostream>
#include <string>
#include <list>

class Component;

class IMediator {
public: // Delegated functions
    virtual void add(Component * c) = 0;
    virtual void sendMessage(std::string s, Component * c) = 0;
};



class Component {
private:
    std::string name;
    IMediator & mediator;

public:
    Component(std::string name, IMediator & mediator): name(name), mediator(mediator) {
        mediator.add(this);
    }

    void receiveMessage(std::string s) {
        std::cout << "[" + name + "] " + s << std::endl;
    }

    void sendMessage(std::string s) {
        mediator.sendMessage(name + ": " + s, this);
    }
};



class Mediator: public IMediator {
private:
    std::list<Component *> colleagues;

public:
    void add(Component * c) override {
        colleagues.push_back(c);
    }

    void sendMessage(std::string s, Component * c) override {
        for (auto & i : colleagues) {
            if (i != c)
                i->receiveMessage(s);
        }
    }
};



int main() {
    Mediator aa;

    Component x("Colleague 1", aa);
    Component y("Colleague 2", aa);

    x.sendMessage("Hello, World!");
    y.sendMessage("Nice to meet you!");

    Component z("Colleague 3", aa);
    z.sendMessage("Nice to meet you, too!");
}
