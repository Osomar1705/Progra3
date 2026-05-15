#include <iostream>
#include <cmath>
#include <ctime>

using namespace std ;

void check_all() { cout << endl; }

template <typename T>
bool check_all(T val) {
    return val > 0;  // retorna true si es positivo
}

// caso recursivo: primero + el resto
template <typename T, typename... Args>
bool check_all(T first, Args... rest) {
    return (first > 0) && check_all(rest...);  // && en vez de imprimir
}


int main() {
    Vehiculo* v[2];
    v[0] = new Auto(120);
    v[1] = new Moto(80);

    for(int i = 0; i < 2; i++) {
        v[i]->describir();
        delete v[i];
    }
    // Auto a 120 km/h
}