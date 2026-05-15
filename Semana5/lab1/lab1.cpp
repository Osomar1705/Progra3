#include <iostream>
using namespace std;

class Item {
    //clase abstracta
    friend struct Hacha;
    friend class Espada;
    friend class Arco;
    friend class Baston;
    friend class Pj;

    int pts;
    string nomb;
    public:
    virtual int usar()=0; //metodo virtual puro
    Item(int puntos, string nombre) : pts(puntos), nomb(nombre) {}
};

class Arma: public Item {
    public:
    Arma(int puntos_ataque,string nombre): Item(puntos_ataque, nombre) {};
    int usar() override {return 0;}
};

struct Hacha: public Arma {
    Hacha():Arma(10,"Hacha") {}
    int usar() override {
        cout <<"Usando"<<nomb<<" ,restando -"<<pts<<" pts. de vida"<<endl;
        return pts;
    };
};
struct Espada: public Arma {//peso(multiplica daño)
    double filo_espada;
public:
    Espada(int filo):filo_espada(filo) ,Arma(5,"Espada") {}
    int usar() override {
        cout <<"Usando"<<nomb<<" ,restando -"<<pts * filo_espada<<" pts. de vida"<<endl;
        return pts*filo_espada;
    }
};
class Arco:public Arma {
    double punteria;
    public:
    // punteria(multiplique el daño)
    Arco(double punteria):punteria(punteria),Arma(7,"Espada") {}
    int usar() override {
        cout <<"Usando"<<nomb<<" ,restando -"<<pts * punteria<<" pts. de vida"<<endl;
        return pts * punteria;
    }
};
class Baston: public Arma {//hechizo (sume daño)
    int puntos_hech;
public:
    Baston(int puntos_hech):puntos_hech(puntos_hech),Arma(6,"Espada") {}
    int usar() override {
        cout <<"Usando "<<nomb<<" ,restando -"<<pts + puntos_hech<<" pts. de vida"<<endl;
        return pts+puntos_hech;
    }
};

class Pj;

template<typename T>
concept varpj = same_as<T,Pj>;


class Pj {
    string nomb;
    Arma** armas;
    int vida;
    int max_armas;
    int ind_armas;
public:
    Pj(string nombre, int size_inventario): nomb(nombre), max_armas(size_inventario) {
        armas = new Arma*[size_inventario];
        ind_armas=0;
    }
    void recoger(Arma* arma) {
        armas[ind_armas] = arma;
        ind_armas++;
    }
    template<typename T, typename... Ts>
    void recoleccion_multiple_armas(T arma_input, Ts... armas_input) {
        this->recoger(arma_input);
        if (sizeof...(armas_input) >0) {
            this->recoleccion_multiple_armas(arma_input);
        }
    }

    void operator +(Arma* arma) {
        this->recoger(arma);
    }

    void curar(Pj& otro) {
        otro.vida+=10;
    }
    void atacar(Pj& otro) {
        Arma* arma;
        for (int i=0; i<ind_armas; i++) {
            cout << "["<<i<<"]"<< armas[i]->nomb;
        }
        int op;
        cout<<"Selecciona una opcion: ";
        cin >> op;
        otro.vida-=armas[op]->usar();
        cout << "\tObjetivo: "<<otro.nomb<<endl;
    }
    void operator -(Pj& otro) {
        this->atacar(otro);
    }
    template<typename F>
    void combate(Pj& otro,F f) {
        f(*this,otro);
    }
    void operator >>(Pj& otro) {
        this->atacar(otro);
    }
    void combat(Pj& otro, void (*f)(Pj&,Pj&)) {
        f(*this,otro);
    }

};


template <typename F>
concept accion=requires (F func){
    func(Pj("1",1),Pj("2",2));
};

void hechizar(Pj& pj1, Pj& pj2) {
    pj1.atacar(pj2);
}

void curar(Pj& pj1,Pj& pj2) {
    
}

int main() {
    Pj pj1("Orco",10);
    Pj pj2("Elfo",12);
    pj1.recoger(new Hacha());
    pj1.recoger(new Arco(1.9));
    pj1.recoleccion_multiple_armas(new Baston(120),new Espada(23));
    pj1.atacar(pj2);

    pj1.combate(pj2,hechizar);

    return 0;
}