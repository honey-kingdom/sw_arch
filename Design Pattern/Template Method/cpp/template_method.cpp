#include <iostream>

class Base {
private:
    void a() { std::cout << "a "; }
    void c() { std::cout << "c "; }
    void e() { std::cout << "e "; }
    virtual void ph1() = 0;
    virtual void ph2() = 0;

public:
    void Execute() {
        a(); ph1(); c(); ph2(); e();
    }
};



class One: public Base {
private:
    void ph1() override { std::cout << "b "; }
    void ph2() override { std::cout << "d "; }

};



class Two: public Base {
private:
    void ph1() override { std::cout << "2 "; }
    void ph2() override { std::cout << "4 "; }

};



int main() {
    auto x = new One;
    auto y = new Two;

    Base * aa[2] = {x, y};

    for (auto & i : aa) {
        i->Execute();
        std::cout << std::endl;
    }

    delete x, y;
}
