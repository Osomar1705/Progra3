#include <iostream>
#include <vector>
using namespace std;

//ejercicio 1: vasados en algoritmos

/*manera 1 para verificar si un par de numeros suman 10, es con un algoritmo de fuerza bruta, que consiste en comparar cada numero con los demas para ver si su suma es igual a 10.

std::string algoritmo_que_verifica_si_un_par_de_numeros_suman10(const std::vector<int>& numeros) {
    for (size_t i = 0; i < numeros.size(); ++i) {
        for (size_t j = i + 1; j < numeros.size(); ++j) {
            if (numeros[i] + numeros[j] == 10) {
                return "Verdadero";
            }
        }
    }
    return "Falso";
}

int main() {
    std::vector<int> numeros = {1,3,4,5,8};
    std::string resultado = algoritmo_que_verifica_si_un_par_de_numeros_suman10(numeros);
    std::cout << resultado << std::endl; 
    return 0;
}*/


bool Detector(const vector<int>& A){
    int i= 0 ;
    int j = A.size()-1;
    while (i<j)
    {
        if (A[i]+A[j]==10)
            return true;
        else if (A[i]+A[j]<10)
            i++;
        else if (A[i]+A[j]<10)  
            j--;
    }
    return false;
    
}
int main (){
    vector<int> A = {-4,-3,1,2,3,5,13,15};
    COU|   
}