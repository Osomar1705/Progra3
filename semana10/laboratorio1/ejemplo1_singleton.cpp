/*La clase Sesion permite ingresar a los usuarios a una determinada plataforma. La clase debería tener un método llamado view() que visualice el perfil del usuario y dar un mensaje de bienvenida siempre y cuando el usuario haya colocado correctamente su contraseña. 

Utilizando el patrón Singleton, un usuario que haya ingresado a la plataforma validando su contraseña, no le debería volver a solicitar la contraseña.

Completar los espacios en blanco del siguiente programa:
*/

#include <iostream>
#include <string>
using namespace std;

class Sesion {
public:
    // (1) Atributo estático: guarda la única instancia
    static Sesion* instance;

    // (2) Método estático de acceso
    static Sesion* get() {
        if (instance == nullptr) {
            // Primera vez: pedir contraseña
            string password;
            cout << "Password: ";
            cin >> password;

            if (password == "123456") {
                instance = new Sesion(); // Crea la sesión
            } else {
                cout << "Contraseña incorrecta." << endl;
                return nullptr;         // Acceso denegado
            }
        }
        // Segunda vez en adelante: devuelve la sesión ya creada
        return instance;
    }

    // (3) Visualizar el perfil / bienvenida
    void view() {
        cout << "Ingresaste a la app..." << endl;
    }

private:
    // (4) Constructor privado: nadie puede hacer new Sesion() desde afuera
    Sesion() {}
};

// Inicialización obligatoria del estático fuera de la clase
Sesion* Sesion::instance = nullptr;

int main() {
    Sesion* s1 = Sesion::get(); // Pide contraseña → crea instancia
    if (s1) s1->view();
    // Password: 123456
    // Ingresaste a la app...

    Sesion* s2 = Sesion::get(); // instance != nullptr → no pide contraseña
    if (s2) s2->view();
    // Ingresaste a la app...

    // s1 == s2 → true (mismo puntero)
    return 0;
}