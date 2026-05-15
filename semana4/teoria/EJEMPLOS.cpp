/*
EJ1
#include <iostream>
using namespace std;

template<class... Ts>
auto suma(Ts... args){
    return (args+...);
}

int main(){
    cout << "Utilizando 'suma'" << endl;
    cout << suma(1) << endl;
    cout << suma(1,2) << endl;
    cout << suma(1,2,3.5,0.5,5) << endl;

    return 0;
}


EJ2
#include <iostream>
using namespace std;

template<typename... Ts>
void print(Ts... args){
    (cout << ... << args) << endl;
}

int main(){
    print();
    print(1,2,3,4,5);
    print("Hola", 1, "Mundo");

    return 0;
}

Ej3
#include <iostream>
using namespace std;
void print(){cout << endl;}
​
template<typename T, typename... Ts>​
void print(T arg, Ts... args){​
    cout << arg << ‘ ’;​
    print(args...);​
}​
​
int main(){
    print();
    print(1,2,3,4,5);
    print("Hola", 1, "Mundo");
}

Ejemplo Funcion Callback
int suma(int x1, int x2){return x1 + x2;}​
int resta(int x1, int x2){return x1 - x2;}​
​

int main(){​
    int (*pf)(int, int);​
​
    pf = suma;​
    cout << "El resultado es: " << pf(x1, x2) << endl;​
    pf = resta;​
    cout << "El resultado es: " << pf(x1, x2) << endl;​
​
    return 0;​
}

EJEMPLO DE FUNCTORES
struct printString{​
    char _c;​
    printString(char c = ' '): _c(c) {}​
    void operator() (string s){​
        cout << s << _c;​
    }​
};​

int main(){​
    printString line('\n');​
    line("Hola");​
    ​
    printString excl('!');​
    excl("Ingrese un entero valido");​
​
    return 0;​
}​
EJEMPLO  CON <Algorithm>

    #include <algorithm>​
​
int main(){​
    string v[4] = {"Hola","Mundo","en","C++"};​
​
    for_each(v, v+4, printString('\n'));​
​
    return 0;​
}


ejemplo de expresiones lambda [=]

#include <iostream>
using namespace std;

struct C {
    int num = 0;
    void metodo(int x) {
        auto f = [this, x]() { this->num = x; };
        f();
    }
};

int main() {
    C c;
    cout << "this->num = " << c.num << endl;
    c.metodo(5);
    cout << "this->num = " << c.num << endl;
    return 0;
}

EJEMPLO DE LIBRERIAS DE ALGORITMOS

Ej1
#include <iostream>
#include <vector>
#include <algorithm>     
using namespace std;

int main() {
    vector<int> v(5);
    generate(v.begin(), v.end(), []() { return rand() % 10; });
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << "\n";
    return 0;
}

EJ2

#include <iostream>
#include <vector>
#include <algorithm>     
using namespace std;
int main() {
    vector<int> v(5);

    int n = 1;
   generate(v.begin(), v.end(), [&n](){ return n++;});
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << "\n";
}

EJ3

#include <iostream>
#include <vector>
#include <algorithm>    
using namespace std;
int main(){​
    vector<string> v = {"Hola","Mundo","en","C++"};​
    sort(v.begin(), v.end(), ​
        [](string s1, string s2){return s1.size() < s2.size();});​
​
    for_each(v.begin(), v.end(), [](string s){cout << s << ' ';});​
    cout << "\n---------------------------------\n";​
}

ej4 
int fibonacci(int n){​
    if(n<=2) return 1;​
    return fibonacci(n-1) + fibonacci(n-2);​
}​
int main(){​
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};​
​
    transform(v.begin(), v.end(), v.begin(), fibonacci);​
    for_each(v.begin(), v.end(), [](int x){cout << x << " ";});​
    cout << "\n";​
}

*/