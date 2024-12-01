#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class UniquePtr {
private:
    T *pointer;

public:
    UniquePtr(T *pointer) {
        this->pointer = pointer;
    }

    ~UniquePtr() {
        delete pointer;
    }

    T operator*() {
        return *pointer;
    }

    T *operator->() {
        return pointer;
    }

    bool operator!() {
        return pointer == nullptr;
    }

    T *get() {
        return pointer;
    }

    void reset() {
        delete pointer;
        pointer = nullptr;
    }
};


class Consol {
public:
    void Print() {
        cout << "Printing ..." << endl;
    }
};

int main() {
    unique_ptr<int> p(new int(10));
    cout << *p << endl;
    cout << p.get() << endl;

    cout << "//////////////////////////////" << endl;

    UniquePtr<int> ptr(new int(20));
    cout << *ptr << endl;
    cout << ptr.get() << endl;

    cout << "//////////////////////////////" << endl;

    unique_ptr<Consol> console(new Consol());
    console.get()->Print();
    console->Print();
    console.reset();
    if(!console) {
        cout << "pointer is nullptr!" << endl;
    }
    console->Print();


    cout << "//////////////////////////////" << endl;

    UniquePtr<Consol> c_ptr(new Consol());
    c_ptr.get()->Print();
    c_ptr->Print();
    c_ptr.reset();
    if(!c_ptr) {
        cout << "pointer is nullptr!" << endl;
    }
    c_ptr->Print();
}
