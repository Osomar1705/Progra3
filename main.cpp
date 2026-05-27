#include <iostream>
#include <future>

int calcularFibonacci(int n) {
    if (n <= 1)
        return n;

    std::future<int> future1 = std::async(std::launch::async, calcularFibonacci, n - 1);
    std::future<int> future2 = std::async(std::launch::async, calcularFibonacci, n - 2);

    return future1.get() + future2.get();
}

int main() {
    int numero = 20; // Número para calcular la secuencia de Fibonacci

    int resultado = calcularFibonacci(numero);

    std::cout << "El numero de Fibonacci para " << numero << " es: " << resultado << std::endl;

    return 0;
}

