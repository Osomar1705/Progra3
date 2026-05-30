#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstring>
#include <cstdint>

using namespace std;

// Convierte float a entero que mantiene el mismo orden
uint32_t floatAEntero(float f) {
    uint32_t bits;
    memcpy(&bits, &f, sizeof(float));
    if (bits & 0x80000000)   // si es negativo
        bits = ~bits;        // invertir todos los bits
    else
        bits ^= 0x80000000;  // invertir solo el bit de signo
    return bits;
}

// Convierte de vuelta a float
float enteroAFloat(uint32_t bits) {
    if (bits & 0x80000000)
        bits ^= 0x80000000;
    else
        bits = ~bits;
    float f;
    memcpy(&f, &bits, sizeof(float));
    return f;
}

// RADIX SORT para floats - Complejidad: O(n)
void radixSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // Convertir floats a enteros ordenables
    vector<uint32_t> claves(n);
    for (int i = 0; i < n; i++)
        claves[i] = floatAEntero(arr[i]);

    vector<uint32_t> temp(n);

    // 4 pasadas de 8 bits (32 bits en total)
    for (int shift = 0; shift < 32; shift += 8) {
        int conteo[256] = {0};

        for (int i = 0; i < n; i++)
            conteo[(claves[i] >> shift) & 0xFF]++;

        for (int i = 1; i < 256; i++)
            conteo[i] += conteo[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int idx = (claves[i] >> shift) & 0xFF;
            temp[--conteo[idx]] = claves[i];
        }

        swap(claves, temp);
    }

    // Convertir de vuelta a float
    for (int i = 0; i < n; i++)
        arr[i] = enteroAFloat(claves[i]);
}

bool validar_orden(const vector<float>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<float> numbers;
    ifstream in("output.txt");
    float num;

    while (in >> num) {
        numbers.push_back(num);
    }
    in.close();

    cout << "Vector (size): " << numbers.size() << endl;

    auto start = chrono::high_resolution_clock::now();

    if (!numbers.empty()) {
        radixSort(numbers);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Tiempo: " << duration.count() << " ms" << endl;
    cout << "Ordenado: " << (validar_orden(numbers) ? "Si" : "No") << endl;

    return 0;
}