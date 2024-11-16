#include <iostream>
#include <vector>

using namespace std;

constexpr double square(double x) {
    return x * x;
}

double sum(const vector<double>& vec) {
    double total = 0.0;
    for (double value : vec) {
        total += value;
    }
    return total;
}

constexpr int sum_constexpr(int a, int b){
    return a + b;
}


int main() {
    // const int number; // error: uninitialized ‘const number’
    const int dmv = 17; // dmv is a named constant
    int var = 17;       // var is not a constant
    constexpr double max1 = 1.4 * square(dmv); // OK if square(17) is a constant expression
    // constexpr double max2 = 1.4 * square(var); // error: var is not a constant expression
    const double max3 = 1.4 * square(var);  // OK, may be evaluated at run time

    vector<double> v {1.2, 3.4, 4.5}; // v is not a constant
    const double s1 = sum(v); // OK: evaluated at run time
    // constexpr double s2 = sum(v); // error : sum(v) not constant expression

    int x = 10;
    int y = 3;
    const int cx = 10;
    const int cy = 3;

    constexpr int compile_time_sum = sum_constexpr(cx, cy); // Compile-time calculation
    int runtime_sum = sum_constexpr(x, y); // Runtime calculation

    return 0;
}
