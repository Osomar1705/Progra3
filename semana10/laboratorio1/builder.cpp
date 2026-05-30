#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// ── 1. Objeto a construir ─────────────────────────────
class Email {
    friend class Builder;   // Builder puede tocar los privados
private:
    string destinatario_;
    string remitente_;
    string asunto_;
    string cuerpo_;
public:
    void enviar() {
        cout << "De:     " << remitente_    << endl;
        cout << "Para:   " << destinatario_ << endl;
        cout << "Asunto: " << asunto_       << endl;
        cout << "Cuerpo: " << cuerpo_       << endl;
    }
};

// ── 2. Builder: configura cada atributo ──────────────
class Builder {
private:
    Email* email_ = new Email();    // empieza con objeto vacío
public:
    // Cada método guarda el valor y devuelve *this → permite encadenar
    Builder& Destinatario(const string& v) { email_->destinatario_ = v; return *this; }
    Builder& Remitente   (const string& v) { email_->remitente_    = v; return *this; }
    Builder& Asunto      (const string& v) { email_->asunto_       = v; return *this; }
    Builder& Cuerpo      (const string& v) { email_->cuerpo_       = v; return *this; }

    // build() valida y entrega el objeto terminado
    Email* build() {
        if (email_->remitente_.empty())
            throw runtime_error("Falta el remitente");
        return email_;
    }
};

// ── 3. Uso ────────────────────────────────────────────
int main() {
    Builder builder;

    Email* email = builder
        .Remitente   ("yo@gmail.com")
        .Destinatario("tu@gmail.com")
        .Asunto      ("Reunion")
        .Cuerpo      ("Nos vemos el lunes.")
        .build();

    email->enviar();
    delete email;
    return 0;
}