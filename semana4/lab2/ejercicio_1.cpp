#include <iostream>
#include <cmath>
using  namespace std;

double x3(double x) {
    return x * x * x;
}
double log_e(double x) {
    return log(x);
}

double DERIVADA(double (*f)(double), double x0) {
    double h = 1e-6;
    double df = (f(x0 + h) - f(x0)) / h;
    return df;

    
}


int main() {

    cout << DERIVADA(x3, 2.0) << endl;
    cout << DERIVADA(log_e, 0.4) << endl;

    return 0;
}