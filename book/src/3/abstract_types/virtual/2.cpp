#include <iostream>


using namespace std;


class VirtualParent{
public:
    virtual void print(){
        cout << "Parent" << endl;
    }    
};

class VirtualChild: public VirtualParent{
public:
    void print() override{
        cout << "Child" << endl;
    }    
};


int main(){
    VirtualParent p;
    VirtualChild c;
    
    c.print(); // Child
    p.print(); // Parent

    VirtualParent *rp;
    rp = &c;
    rp->print(); // Child
}
