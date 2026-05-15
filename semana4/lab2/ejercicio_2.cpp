#include <iostream>
#include <cmath>
#include <vector>
using  namespace std;

void bubble_sort(vector<int> &A, bool(*F)(int,int)) {
  for (int i = 0; i < A.size() - 1; i++)
    for (int j = 0; j < A.size() - i - 1; j++)
      if (F(A[j], A[j + 1]))
        swap(A[j],A[j+1]);
}
bool opcion1(int a, int b) {
    return a > b;
}
bool opcion2(int a, int b) {
    return a < b;
}
bool opcion3(int a, int b) {
    return abs(a) > abs(b);
}

/// opcion 1: ordenamiento de menor a mayor
/// opcion 2: ordenamiento de mayor a menor
///opcion 3: ordenamiento de menor a mayor con valor abosoluto


struct rectangulo{
    int a , b;
    rectangulo(int x, int y) : a(x), b(y) {}
    int area() const { return a * b; }
};
 
void bubble_sort(vector<rectangulo> &A, bool(*F)(rectangulo,rectangulo)) {
  for (int i = 0; i < A.size() - 1; i++)
    for (int j = 0; j < A.size() - i - 1; j++)
      if (F(A[j], A[j + 1]))
        swap(A[j],A[j+1]);
}
bool opcion4(rectangulo a, rectangulo b) {
    return (a.a * a.b) > (b.a * b.b);
}   

int main () {
    vector<rectangulo> A = {rectangulo(64, 34), rectangulo(25, 12), rectangulo(22, 11), rectangulo(90, 5)};
    bubble_sort(A , opcion4);
    for (const auto& e : A) {
        cout << "(" << e.a << ", " << e.b << ")Area : "<<e.area() << " ";
    }
    cout << endl;
    
}
