#include "unique.h"
#include <iostream>
#include <memory>

using namespace std;


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

    cout << "//////////////////////////////" << endl;

    UniquePtr<Consol> c_org(new Consol());
    c_org.get()->Print();
    UniquePtr<Consol> c_copy = move(c_org);
    c_org.get()->Print();
    c_copy.get()->Print();
}
