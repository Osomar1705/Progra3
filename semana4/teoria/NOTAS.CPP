

/*
Variadic templates : permite escribir funciones con número variable de argumentos. O clases con número variable de miembros.
Pack de parametros : forma de representar un numero de variables de parametros tamplate

FOLD EXPRESSIONS : permite escribir expresiones que se expanden sobre un pack de parametros. Se pueden usar para aplicar una operación a cada elemento del pack, o para combinar los elementos de alguna manera.
sintaxis : ( ... op pack ) o ( pack op ... ) o ( pack op ... op pack )
op: Operador Binario
pack: El pack de parámetros
init: Todo lo que no sea un pack o un op

Expansión:
(pack op ... ) se expande a (a1 op(...op(an-1 op an)))
( ... op pack ) se expande a (a1 op(...op(an-1 op an)))

Varuiadic Alias Template:es una platilla de alias que puede tomar un número variable de parámetros de plantilla. 
Se utiliza para crear alias para una familia de tipos con un número variable de parámetros Template:

template <typename T, typename... Ts> 
struct foo{
. . .
};

template <typename... Ts>---> definir para la viable local 
using int_foo = foo<int, Ts...>;


CALLABLES: Funciones, lambdas, objetos con operador de llamada, 
punteros a funciones, etc. que pueden ser invocados con un conjunto de argumentos.
cada objeto llamable tiene su propio firma, La firma detalla el tipo de dato que 
retorna la llamada y el tipo de parámetros que esta requiere.

Funciones Callback: aquellas que se pasan como argumentos a otras funciones externa.
Esto con el objetivo de llamar a la funcion dentro ejemplo:

int suma(int x1, int x2){return x1 + x2;}​
int resta(int x1, int x2){return x1 - x2;}​
​
void calculadora(int (*f)(int, int), int x1, int x2){​
    cout << "El resultado es: " << f(x1, x2) << endl;​
}​

Functore: son un tipo especial de parametros como un sobrecarga especial

Exprecsiones Lambda: son funciones anónimas. Similar a los Functores 
auto foo = [](){​
    cout << "Hola Mundo" << endl;​
};



void foo(){​
    cout << "Hola Mundo" << endl;​
}​

Sintaxis de las expresiones lambda:
[Iniciador] (Parametros) mutable noexpet -> tipo{cuerpo}
iniciador: captura de variables del entorno tenemos :[](Ninguna variable externa es capturada​),
[LISTA](Solo las variables en lista son capturadas​),
[&](Todas las variables externas del cuerpo se capturan por referencia.​), 
[this](Todas las variables externas del cuerpo se capturan por valor.);
Parametros: lista de parametros de la funcion lambda    
mutable: permite modificar las variables capturadas por valor
noexcept: indica que la función lambda no lanzará excepciones


LIBRERIAS DE ALGORITMOS: <algorithm> y <numeric> contienen una gran cantidad de algoritmos 
genéricos que pueden ser aplicados a contenedores de datos. Estos algoritmos pueden ser 
utilizados con cualquier tipo de dato que cumpla con los requisitos necesarios para el algoritmo en cuestión.
Algunos ejemplos de algoritmos incluyen:for_each​,generate​,sort​,find​,transform​,shuffle​
*/