#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class UniquePtr {
public:
    UniquePtr(T *pointer) {
        this->pointer = pointer;
    }

    T operator*() {
        return *pointer;
    }
private:
    T *pointer;
};


int main() {
    unique_ptr<int> p(new int);
    *p = 1;
    cout << *p << endl;

    UniquePtr<int> ptr(new int);
    cout << *ptr << endl;
}
