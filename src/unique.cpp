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
        delete this->pointer;
    }

    T operator*() {
        return *pointer;
    }

    T* get() {
        return pointer;
    }
};


int main() {
    unique_ptr<int> p(new int(10));
    cout << *p << endl;
    cout << p.get() << endl;


    UniquePtr<int> ptr(new int(20));
    cout << *ptr << endl;
    cout << ptr.get() << endl;
}
