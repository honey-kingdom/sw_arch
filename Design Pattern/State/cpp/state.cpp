#include <iostream>

class VendingMachine;

class State {
public:
    virtual void insertCoin(VendingMachine * context)   { std::cerr << "Unexpected Behavior!" << std::endl; }
    virtual void selectItem(VendingMachine * context)   { std::cerr << "Unexpected Behavior!" << std::endl; }
    virtual void dispenseItem(VendingMachine * context) { std::cerr << "Unexpected Behavior!" << std::endl; }
    virtual void returnChange(VendingMachine * context) { std::cerr << "Unexpected Behavior!" << std::endl; }

    virtual ~State() {}
};




class VendingMachine {
private:
    State * current_state;

public:
    VendingMachine();
    ~VendingMachine();
    void setState(State * new_state) { current_state = new_state; }

    void insertCoin()   { current_state->insertCoin(this);   }
    void selectItem()   { current_state->selectItem(this);   }
    void dispenseItem() { current_state->dispenseItem(this); }
    void returnChange() { current_state->returnChange(this); }
};



class Idle: public State {
public:
    void insertCoin(VendingMachine * context) override;
};

class SelectingItem: public State {
public:
    void selectItem(VendingMachine * context) override;
};

class DispensingItem: public State {
public:
    void dispenseItem(VendingMachine * context) override;
};

class ReturningChange: public State {
public:
    void returnChange(VendingMachine * context) override;
};



VendingMachine::VendingMachine() : current_state(new Idle) {}
VendingMachine::~VendingMachine() { delete current_state; }

void
Idle::insertCoin(VendingMachine * context) {
    std::cout << "Coin Inserted!" << std::endl;

    delete this;
    context->setState(new SelectingItem);
}

void
SelectingItem::selectItem(VendingMachine * context) {
    std::cout << "Item Selected!" << std::endl;

    delete this;
    context->setState(new DispensingItem);
    context->dispenseItem(); // Dependencies between State subclasses introduced
}

void
DispensingItem::dispenseItem(VendingMachine * context) {
    std::cout << "Item Dispensed!" << std::endl;

    delete this;
    context->setState(new ReturningChange);
    context->returnChange();
}

void
ReturningChange::returnChange(VendingMachine * context) {
    std::cout << "Changed Returned!" << std::endl;

    delete this;
    context->setState(new Idle);
}




int main(void) {
    VendingMachine aa;

    aa.insertCoin();
    aa.selectItem();
}
