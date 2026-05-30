constructor privado
    ┌────────────────────────┐
    │       Singleton        │
    ├────────────────────────┤
    │ − instance: Singleton* │  ← puntero estático, empieza en nullptr
    ├────────────────────────┤
    │ − Singleton()          │  ← nadie puede llamarlo directamente
    │ + getInstance() *      │  ← único punto de entrada
    └────────────────────────┘

class Singleton {
private:
    static Singleton* instance;   // Única instancia compartida

    Singleton() {}                // (1) Constructor privado:
                                  //     nadie puede hacer "new Singleton()"
                                  //     desde afuera

public:
    // (2) Método estático: no necesita objeto para llamarse
    static Singleton* getInstance() {
        if (instance == nullptr) {      // ¿Primera vez?
            instance = new Singleton(); // Crea la instancia
        }
        return instance;                // Siempre devuelve la misma
    }

    // (3) Evitar copia y asignación (buena práctica)
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

// Inicialización fuera de la clase (obligatorio para estáticos)
Singleton* Singleton::instance = nullptr;


// uso 
int main() {
    Singleton* a = Singleton::getInstance(); // Crea la instancia
    Singleton* b = Singleton::getInstance(); // Devuelve la misma

    // a == b → true (mismo puntero)
}