#include <iostream>
#include <string>
using namespace std;

class CifradoAfin {
private:
    int a, b;
    const int m = 26; 

public:
    CifradoAfin(int _a, int _b) : a(_a), b(_b) {}

    char operator()(char x) const {
        if (x >= 'A' && x <= 'Z') {
            int valor_x = x - 'A';
            
            int valor_c = (a * valor_x + b) % m;
            
            return static_cast<char>(valor_c + 'A');
        }
        return x; 
    }
};

int main() {
    CifradoAfin cifrar(7, 3);

    string palabra = "HOLA";
    string resultado = "";

    for (char c : palabra) {
        resultado += cifrar(c);
    }

    cout << "Original: " << palabra << endl;
    cout << "Cifrado:  " << resultado << endl;

    return 0;
}