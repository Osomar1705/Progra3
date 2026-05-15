#include<vector>
#include <iostream>
#include <algorithm> 
#include <cstdlib>  
#include <iostream>
#include <algorithm>

using namespace std;

class VectorMath {
    int size;
    float *data;

public:
    VectorMath(int s) {
        size = s;
        data = new float[size];
        for(int i = 0; i < size; i++) {
            data[i] = 0.0;
        }
    }

    void set(int index, float val) {
        data[index] = val; 
    }
};

// SOBRECARGA DE OPERADORES
VectorMath operator +(VectorMath v1, VectorMath v2) { 
    int maxSize = max(v1.size, v2.size); 
    VectorMath res(maxSize);
    
    for(int i = 0; i < maxSize; i++) {
        res.data[i] = v1.data[i] + v2.data[i]; 
    }
    return res;
}

void operator<<(ostream& os, VectorMath v) { 
    os << "[ ";
    for(int i = 0; i < v.size; i++) {
        os << v.data[i] << " ";
    }
    os << "]";
}

int main() {
    VectorMath v1(3);
    v1.set(0, 1.5); 
    v1.set(1, 2.0); 
    v1.set(2, 3.5);

    VectorMath v2(2);
    v2.set(0, 4.0); 
    v2.set(1, 5.0);

    // Sumamos vectores de diferente tamaño
    VectorMath v3 = v1 + v2;

    cout << "El vector 3 es: " << v3 << endl;

    return 0;
}