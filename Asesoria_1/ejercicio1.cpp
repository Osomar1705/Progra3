#include <iostream>
#include <algorithm> 
#include <cstdlib>  
#include <ctime>     

using namespace std;

class polinomio {
private:
    int grado;
    int *coeficientes;

public:
    polinomio(int g) {
        grado = g;
        coeficientes = new int[grado + 1];
        for (int i = 0; i <= grado; i++) {
            coeficientes[i] = rand() % 10 + 1; 
        }
    }

    polinomio(const polinomio& p) {
        grado = p.grado;
        coeficientes = new int[grado + 1];
        for (int i = 0; i <= grado; i++) {
            coeficientes[i] = p.coeficientes[i];
        }
    }

    ~polinomio() {
        delete[] coeficientes;
    }

    // Declaración de funciones amigas para acceder a variables privadas
    friend polinomio operator+(const polinomio &p1, const polinomio &p2);
    friend ostream& operator<<(ostream& os, const polinomio& p);
};

polinomio operator+(const polinomio &p1, const polinomio &p2) {
    int maxGrado = max(p1.grado, p2.grado);
    polinomio resultado(maxGrado);
    
    for (int i = 0; i <= maxGrado; i++) {
        int c1 = (i <= p1.grado) ? p1.coeficientes[i] : 0;
        int c2 = (i <= p2.grado) ? p2.coeficientes[i] : 0;
        
        resultado.coeficientes[i] = c1 + c2;
    }
    return resultado;
}

ostream& operator<<(ostream& os, const polinomio& p) {
    for (int i = p.grado; i >= 0; i--) {
        os << p.coeficientes[i];
        if (i > 0) os << "x^" << i << " + ";
    }
    return os;
}

int main() {
    srand(time(0)); 
    polinomio poli1(3); 
    polinomio poli2(2); 

    polinomio sum = poli1 + poli2;
    
    cout << "poli1 : " << poli1 << endl;
    cout << "poli2 : " << poli2 << endl;
    cout << "suma  : " << sum << endl;

    return 0;
}