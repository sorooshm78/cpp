#include <iostream>


using namespace std;


class Parent{
public:
    void print(){
        cout << "Parent" << endl;
    }    
};

class Child: public Parent{
public:
    void print(){
        cout << "Child" << endl;
    }    
};


int main(){
    Parent p;
    Child c;
    
    c.print(); // Child
    p.print(); // Parent

    Parent *rp;
    rp = &c;
    rp->print(); // Parnet
}
