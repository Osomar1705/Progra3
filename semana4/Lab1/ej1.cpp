#include <iostream>
#include <vector>
#include <string>
#include<cmath>

using namespace std;    




template <typename T>
string tipo(T input) {
    return "de tipo T";
}

template <>//especialización de plantilla para int
string tipo(char input) {
    return "de tipo char";
}

template<typename T>//sobrecarga de plantilla para puntero
string tipo(T* input) {
    return "es puntero de tipo T";
}

template<>//especialización de plantilla para puntero a double
string tipo(double* input) {
    return "es puntero de tipo double";
}

//EJERCICIO 2
template<typename T>
T Maximo(vector<T>U) {
    T maximo=U[0];
    for(auto e:U){
        if(e>maximo){
            maximo=e;
        }
    }
    return maximo;
}
int contador(string imput){
    int cont = 0;
    for (char c : imput){
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            cont ++;}}
    return cont;
}

template<>
string Maximo(vector<string>U) {
    string maximo=U[0];
    for(auto e:U){
        if(contador(maximo)<contador(e)){
            maximo=e;
        }
    }
    return maximo;
}

template<typename...Ts>
double norma2(Ts... args) {  
    return sqrt((pow(args,2) + ...)); 
}
int elevado(int x){
    return pow(x,2);
}
template<typename...Ts>
double foo1(Ts... args) {
    return (elevado(args) + ...);

}
int conversion(double x){
    return static_cast<int>(x);
}
template<typename T1, typename T2>
double Max(T1 x1, T2 x2) {
    if (x1 > x2) {
        return x1;
    } else {
        return x2;
    }
}
template<typename T1, typename T2, typename...Ts>
double Max(T1 x1, T2 x2, Ts... xs) {
    return Max(Max(x1,x2),xs...);
}
int main() {
   
   
   
    /*ej5 max pero de una vector de diferente datos 
    cout << Max(3,8,5,6) << endl;
    cout << Max(3.1,4) << endl;
    cout << Max(13,7.4,-5,-61,101,0.01) << endl;
    */
    
    /*ej4 entender bien
    cout<< foo1(4,4,5.2,11)<<endl;
    cout<<foo2(4,4,5.2,11)<<endl;*/

   /*ej3
   cout << norma2(3,4.11)<<endl;
   cout << norma2(3,4,5.2,11)<<endl;/*
    
   /*ej2
    vector<int> v1={6,2,7,-3,-1,3,5,-12,2};
    vector<string> v2={"hola","mundo","en","c++","gaaaaa"};

    cout <<Maximo(v1)<<endl;
    cout <<Maximo(v2)<<endl;*/
    
    /*ej1
    ej1
    int x;
    int y;
    double z;
    int* ptr1;
    double* ptr2;

    cout << tipo(x)<<endl;
    cout << tipo(y)<<endl;
    cout << tipo(z)<<endl;
    cout << tipo(ptr1)<<endl;
    cout << tipo(ptr2)<<endl;
    */


}

