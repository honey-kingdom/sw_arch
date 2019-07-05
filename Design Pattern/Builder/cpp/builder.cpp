#include <iostream>
#include <string>

class Item {
public:
    std::string name;
    Item(std::string name): name(name) {}
    virtual ~Item() {}
};

class Head: public Item { public: Head(std::string name): Item(name) {} };
class Arm: public Item { public: Arm(std::string name): Item(name) {} };
class Leg: public Item { public: Leg(std::string name): Item(name) {} };

class Body: public Item {
public:
    Body(std::string name): Item(name) {}

    Head * head;
    Arm * arm[2];
    Leg * leg[2];

    void Print() {
        std::cout << name << ": {" << head->name << ", " << arm[0]->name << ", " << leg[0]->name << "}\n";
    }
};

class BaseBuilder {
protected:
    Body * body {};

public:
    virtual void BuildBody() = 0;
    virtual void BuildHead() = 0;
    virtual void BuildArms() = 0;
    virtual void BuildLegs() = 0;

    Body * ReturnProduct() {
        auto product = body;
        body = nullptr;
        return product;
    }

    virtual ~BaseBuilder() {}
};

class HumanBuilder: public BaseBuilder {
public:
    void BuildBody() override { body         = new Body("Human Body"); }
    void BuildHead() override { body->head   = new Head("Human Head"); }
    void BuildArms() override { body->arm[0] = new Arm("Human Arm");
                                body->arm[1] = new Arm("Human Arm"); }
    void BuildLegs() override { body->leg[0] = new Leg("Human Leg");
                                body->leg[1] = new Leg("Human Leg"); }
};

class RobotBuilder: public BaseBuilder {
public:
    void BuildBody() override { body         = new Body("Robot Body"); }
    void BuildHead() override { body->head   = new Head("Robot Head"); }
    void BuildArms() override { body->arm[0] = new Arm("Robot Arm");
                                body->arm[1] = new Arm("Robot Arm"); }
    void BuildLegs() override { body->leg[0] = new Leg("Robot Leg");
                                body->leg[1] = new Leg("Robot Leg"); }
};

class Director {
private:
    BaseBuilder * builder;

public:
    void SetBuilder(BaseBuilder * new_builder) { builder = new_builder; }

    Body * GetProduct() { // Steps to build, Dealing with composition
        builder->BuildBody();
        builder->BuildHead();
        builder->BuildArms();
        builder->BuildLegs();
        
        return builder->ReturnProduct();
    }
};

int main() {
    Director aa;

    aa.SetBuilder(new HumanBuilder());
    auto x = aa.GetProduct();

    x->Print();

    aa.SetBuilder(new RobotBuilder());
    auto y = aa.GetProduct();

    y->Print();
}
