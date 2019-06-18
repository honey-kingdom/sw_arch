#include <iostream>

class SortBehavior { // Interface
public:
    virtual void sort() = 0;
};

class Container {
private:
    SortBehavior * m_sort; // Composition

public:
    void Sort() {
        m_sort->sort();
    }

    void SetBehavior(SortBehavior * s) { // Delegation
        m_sort = s;
    }
};

class MergeSort: public SortBehavior {
    void sort() override {
        std::cout << "Merge Sort!" << std::endl;
    }
};

class HeapSort: public SortBehavior {
    void sort() override {
        std::cout << "Heap Sort!" << std::endl;
    }
};

int main(void) {
    Container aa;

    auto x = new MergeSort;
    aa.SetBehavior(x);
    aa.Sort();

    auto y = new HeapSort;
    aa.SetBehavior(y);
    aa.Sort();

    delete x, y;
}
