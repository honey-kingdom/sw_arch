#include <iostream>
#include <list>

class Subscriber {
public:
    virtual void update() = 0;
};

class ChattingRoom {
private:
    std::list<Subscriber *> subscribers;
    std::string message;

public:
    void add(Subscriber * s) {
        subscribers.push_back(s);
    }

    void notify() {
        for (auto & i : subscribers)
            i->update();
    }

    void newMessage(std::string s) {
        message = s;
        notify();
    }

    std::string getMessage() {
        return message;
    }
};

class ChatMember: public Subscriber {
private:
    ChattingRoom & publisher;

public:
    ChatMember(ChattingRoom & p) : publisher(p) {
        publisher.add(this);
    }

    void update() override {
        std::cout << publisher.getMessage() << std::endl;
    }
};

int main(void) {
    ChattingRoom aa;

    ChatMember x(aa);
    ChatMember y(aa);
    aa.newMessage("Hello, World!");

    ChatMember z(aa);
    aa.newMessage("Hello, again!");
}
