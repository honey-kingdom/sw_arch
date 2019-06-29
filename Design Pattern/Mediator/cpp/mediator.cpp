#include <iostream>
#include <string>
#include <list>

class Mediator;

class Component {
private:
    std::string name;
    Mediator & mediator;

public:
    Component(std::string name, Mediator & mediator);

    void receiveMessage(std::string s);
    void sendMessage(std::string s);
};



class Mediator {
private:
    std::list<Component *> colleagues;

public:
    void add(Component * c);
    void sendMessage(std::string s, Component * c);
};



Component::Component(std::string name, Mediator & mediator)
    : name(name), mediator(mediator) {
    mediator.add(this);
}

void Component::receiveMessage(std::string s) {
    std::cout << "[" + name + "] " + s << std::endl;
};

void Component::sendMessage(std::string s) {
    mediator.sendMessage(name + ": " + s, this);
}



void Mediator::add(Component * c) {
    colleagues.push_back(c);
}

void Mediator::sendMessage(std::string s, Component * c) {
    for (auto & i : colleagues) {
        if (i != c)
            i->receiveMessage(s);
    }
}



int main() {
    Mediator aa;

    Component x("Colleague 1", aa);
    Component y("Colleague 2", aa);

    x.sendMessage("Hello, World!");
    y.sendMessage("Nice to meet you!");

    Component z("Colleague 3", aa);
    z.sendMessage("Nice to meet you, too!");
}
