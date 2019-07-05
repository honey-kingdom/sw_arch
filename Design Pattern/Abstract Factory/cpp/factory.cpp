#include <iostream>
#include <cstdint>

class SequenceItem;

class UvmFactory {
public:
    virtual SequenceItem * Create() = 0; // Factory Method

    virtual ~UvmFactory() {}
};

class SequenceItem {
private:
    static UvmFactory * global_factory; // Singleton Pattern

public:
    virtual void DoPrint() = 0; // Client only needs knowledge of this abstract method

    static void DeleteFactory() {
        if (global_factory != nullptr)
            delete global_factory;
    }

    static void FactoryOverride(UvmFactory * factory) {
        global_factory = factory;
    }

    static SequenceItem * Create() { return global_factory->Create(); } // Strategy Pattern

    virtual ~SequenceItem() {}
};

class CstatePacket: public SequenceItem {
private:
    bool    DisableT05Lookup = false;
    bool    DisableT10Lookup = false;
    bool    DisableBucketing = false;
    uint8_t GenerateTestPattern = 0;

public:
    void DoPrint() override;
};

class GstatePacket: public SequenceItem {
private:
    uint8_t texBaseAddr = 0;
    uint8_t texType = 0;
    uint8_t texelSize = 2;

public:
    void DoPrint() override;
};

class CstatePacketFactory: public UvmFactory {
public:
    SequenceItem * Create() override {
        return new CstatePacket();
    }
};

class GstatePacketFactory: public UvmFactory {
public:
    SequenceItem * Create() override {
        return new GstatePacket();
    }
};



UvmFactory * SequenceItem::global_factory = nullptr;

void CstatePacket::DoPrint() {
    std::cout << "gsm2tex: {"
        << "DisableT05Lookup: " << DisableT05Lookup << ", "
        << "DisableT10Lookup: " << DisableT10Lookup << ", "
        << "DisableBucketing: " << DisableBucketing << ", "
        << "GenerateTestPattern: " << +GenerateTestPattern
        << "}\n";
}

void GstatePacket::DoPrint() {
    std::cout << "gsm2tex: {"
        << "texBaseAddr: " << +texBaseAddr << ", "
        << "texType: " << +texType << ", "
        << "texelSize: " << +texelSize
        << "}\n";
}



int main(void)
{
    SequenceItem::FactoryOverride(new CstatePacketFactory()); // Analogy : Super Mario Maker's Theme
    SequenceItem * cstate = SequenceItem::Create();

    SequenceItem::DeleteFactory();



    SequenceItem::FactoryOverride(new GstatePacketFactory()); // Only this single line needs to be modified
    SequenceItem * gstate = SequenceItem::Create();

    SequenceItem::DeleteFactory();



    cstate->DoPrint();
    gstate->DoPrint();

    delete cstate;
    delete gstate;
}
