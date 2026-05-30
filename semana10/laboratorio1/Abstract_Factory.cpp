#include <iostream>
using namespace std;

// ── Productos abstractos ──────────────────────────────
class Button   { public: virtual void draw() = 0; };
class CheckBox { public: virtual void draw() = 0; };

// ── Productos concretos Windows ───────────────────────
class WindowsButton   : public Button   {
    void draw() override { cout << "[Win] Button\n"; }
};
class WindowsCheckBox : public CheckBox {
    void draw() override { cout << "[Win] CheckBox\n"; }
};

// ── Productos concretos Linux ─────────────────────────
class LinuxButton   : public Button   {
    void draw() override { cout << "[Lin] Button\n"; }
};
class LinuxCheckBox : public CheckBox {
    void draw() override { cout << "[Lin] CheckBox\n"; }
};

// ── Fábrica abstracta ─────────────────────────────────
class AbstractFactory {
public:
    virtual Button*   createButton()   = 0;
    virtual CheckBox* createCheckBox() = 0;
};

// ── Fábricas concretas ────────────────────────────────
class WindowsFactory : public AbstractFactory {
public:
    Button*   createButton()   override { return new WindowsButton(); }
    CheckBox* createCheckBox() override { return new WindowsCheckBox(); }
};

class LinuxFactory : public AbstractFactory {
public:
    Button*   createButton()   override { return new LinuxButton(); }
    CheckBox* createCheckBox() override { return new LinuxCheckBox(); }
};

// ── Uso ───────────────────────────────────────────────
int main() {
    AbstractFactory* factory;

    #ifdef _WIN32
        factory = new WindowsFactory();
    #else
        factory = new LinuxFactory();
    #endif

    Button*   btn = factory->createButton();
    CheckBox* chk = factory->createCheckBox();

    btn->draw();   // [Win] Button   ← o [Lin] según SO
    chk->draw();   // [Win] CheckBox

    delete btn; delete chk; delete factory;
    return 0;
}