// Reference
//      https://stackoverflow.com/questions/5739611/what-are-the-differences-between-abstract-factory-and-factory-design-patterns

#include <iostream>

class BaseObject {
public:
    virtual void Print() = 0;

    virtual ~BaseObject() {}
};

class PlainEnv: public BaseObject {
public:
    void Print() override {
        std::cout << "Plain UVM environment\n";
    }
};

class CoverageEnv: public BaseObject {
public:
    void Print() override {
        std::cout << "UVM environment with coverage collector\n";
    }
};

class BaseCreator {
private:
    BaseObject * object;

public:
    virtual BaseObject * FactoryMethod() {
        return new PlainEnv();
    }

    void DoPrint() {
        object = FactoryMethod();
        object->Print();
        delete object;
    }

    virtual ~BaseCreator() {}
};

class PlainCreator: public BaseCreator {
public:
    BaseObject * FactoryMethod() override {
        return new PlainEnv();
    }
};

class CoverageCreator: public BaseCreator {
public:
    BaseObject * FactoryMethod() override {
        return new CoverageEnv();
    }
};

int main(void) {
    PlainCreator aa;
    aa.DoPrint();

    CoverageCreator bb;
    bb.DoPrint();
}
