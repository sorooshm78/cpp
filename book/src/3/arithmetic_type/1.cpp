#include<iostream>

using namespace std;


class complex {
    double re, im; // representation: two doubles

public:
    // Constructors
    complex(double r, double i) : re{r}, im{i} {}      // construct complex from two scalars
    complex(double r) : re{r}, im{0} {}               // construct complex from one scalar
    complex() : re{0}, im{0} {}                       // default complex: {0,0}

    // Accessors and mutators
    double real() const { return re; }
    void real(double d) { re = d; }
    double imag() const { return im; }
    void imag(double d) { im = d; }

    // Arithmetic operators
    complex& operator+=(complex z) { 
        re += z.re; 
        im += z.im; 
        return *this; 
    } // add to re and im and return the result

    complex& operator-=(complex z) { 
        re -= z.re; 
        im -= z.im; 
        return *this; 
    }

    complex& operator*=(complex); // defined out-of-class somewhere
    complex& operator/=(complex); // defined out-of-class somewhere
};

int main()
{
    return 0;
}