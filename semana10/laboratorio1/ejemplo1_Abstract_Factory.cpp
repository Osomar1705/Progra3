#include <iostream>
using namespace std;

// ── Productos abstractos ──────────────────────────────────────────
class Camara {
public:
    virtual void capturar() = 0;
    virtual ~Camara() {}
};

class BotonRec {
public:
    virtual void grabar() = 0;
    virtual ~BotonRec() {}
};

// ── Productos concretos Windows ───────────────────────────────────
class CamaraWindows : public Camara {
public:
    void capturar() override {
        cout << "[Windows] Capturando video con DirectShow..." << endl;
    }
};

class BotonRecWindows : public BotonRec {
public:
    void grabar() override {
        cout << "[Windows] Grabando con Media Foundation..." << endl;
    }
};

// ── Productos concretos Linux ─────────────────────────────────────
class CamaraLinux : public Camara {
public:
    void capturar() override {
        cout << "[Linux] Capturando video con V4L2..." << endl;
    }
};

class BotonRecLinux : public BotonRec {
public:
    void grabar() override {
        cout << "[Linux] Grabando con GStreamer..." << endl;
    }
};

// ── Fábrica abstracta ─────────────────────────────────────────────
class AppFactory {
public:
    virtual Camara*   crearCamara()   = 0;
    virtual BotonRec* crearBotonRec() = 0;
    virtual ~AppFactory() {}
};

// ── Fábricas concretas ────────────────────────────────────────────
class WindowsFactory : public AppFactory {
public:
    Camara* crearCamara() override {
        cout << "Creando camara para Windows..." << endl;
        return new CamaraWindows();
    }
    BotonRec* crearBotonRec() override {
        cout << "Creando boton de grabar para Windows..." << endl;
        return new BotonRecWindows();
    }
};

class LinuxFactory : public AppFactory {
public:
    Camara* crearCamara() override {
        cout << "Creando camara para Linux..." << endl;
        return new CamaraLinux();
    }
    BotonRec* crearBotonRec() override {
        cout << "Creando boton de grabar para Linux..." << endl;
        return new BotonRecLinux();
    }
};

// ── App: solo habla con la fábrica abstracta ──────────────────────
class App {
private:
    AppFactory* factory;
public:
    App(AppFactory* f) : factory(f) {}

    void crearApp() {
        Camara*   camara = factory->crearCamara();
        BotonRec* boton  = factory->crearBotonRec();

        camara->capturar();
        boton->grabar();

        delete camara;
        delete boton;
    }
};

// ── main ──────────────────────────────────────────────────────────
int main() {
    AppFactory* factory;

    #ifdef _WIN32
        factory = new WindowsFactory();
    #else
        factory = new LinuxFactory();
    #endif

    App app(factory);
    app.crearApp();   // typo corregido: crearApp, no creaApp

    delete factory;
    return 0;
}