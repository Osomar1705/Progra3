#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <stdexcept>
#include <concepts>
#include <algorithm>
#include <unordered_map>
using namespace std;

//sobrecarga de operadores
struct Stats;

template <typename T>
concept NumericType = is_arithmetic_v<T>;

template <typename T>
concept StatsType = is_same_v<T, Stats>;

template <typename T>
concept NumericOrStats = NumericType<T> || StatsType<T>;

struct Stats {
    float hp;
    float damage;
    float defense;

    Stats(float hp = 0.f, float dmg = 0.f, float def = 0.f)
        : hp(hp), damage(dmg), defense(def) {}

    // Sf = (Sb + Sb) * Sm (hacemos cumplir el sistema de Atributos y sobrecarga de Operadores)
    Stats operator+(const Stats& other) const {
        return Stats(hp + other.hp, damage + other.damage, defense + other.defense);
    }

    Stats operator*(const Stats& multiplier) const {
        return Stats(hp * multiplier.hp, damage * multiplier.damage, defense * multiplier.defense);
    }

    Stats& operator+=(const Stats& other) {
        hp       = max(0.f, hp + other.hp);
        damage   += other.damage;
        defense  += other.defense;
        return *this;
    }

    Stats& operator*=(const Stats& multiplier) {
        hp      *= multiplier.hp;
        damage  *= multiplier.damage;
        defense *= multiplier.defense;
        return *this;
    }

    bool operator==(const Stats& other) const {
        return hp == other.hp && damage == other.damage && defense == other.defense;
    }

    void print(const string& label = "") const {
        if (!label.empty()) cout << "(" << label << ") ";
        cout << "HP=" << hp << "  DMG=" << damage << "  DEF=" << defense << endl;
    }
};

// Restricciones para que no salgan errores como en clase
template <NumericType T>
T mitigate_damage(T raw_damage, T defense) {
    T result = raw_damage - defense;
    return result > T(0) ? result : T(0);
}
template <StatsType T>
T mitigate_damage(T raw, T def) {
    T result;
    result.damage  = max(0.f, raw.damage - def.defense);
    result.hp      = raw.hp;
    result.defense = raw.defense;
    return result;
}

// Despacho de Eventos con Variadic Templates
template <typename... Args>
class Despachador_de_Senales {

    public:
    using Handler = function<void(Args...)>;

    void connect(const string& event_name, Handler handler) {
        handlers_[event_name].push_back(move(handler));
    }

    void emit(const string& event_name, Args... args) {
        auto it = handlers_.find(event_name);
        if (it != handlers_.end()) {
            for (auto& h : it->second)
                h(args...);
        }
    }

private:
    unordered_map<string, vector<Handler>> handlers_;
};

//Ejecución de Acciones mediante Callables y Lambdas
class Skill {
public:
    using Action = function<Stats(const Stats& user_stats, Stats& target_stats)>;

    explicit Skill(string name, Action action)
        : name_(move(name)), action_(move(action)) {}

    // Ejecutamos la accion que nos retoma los stats como objeto llamable
    Stats execute(const Stats& user_stats, Stats& target_stats) const {
        return action_(user_stats, target_stats);
    }

    const string& name() const { return name_; }

private:// teniendo privete como el nombre y el actions
    string name_;
    Action action_;
};

//Entidades polimoficas
class Entity {
public:
    Entity(string name, Stats base): name_(move(name)), base_stats_(base), current_stats_(base),
          last_damage_received_(0.f) {}

    virtual ~Entity() = default;

    //entidades unicas por eso no se copian
    Entity(const Entity&)            = delete;
    Entity& operator=(const Entity&) = delete;

    // Y los movibles que nos ayudaran a ordenar
    Entity(Entity&&)            = default;
    Entity& operator=(Entity&&) = default;

    virtual void on_turn_start() {
        cout << name_ << " comienza su turno. ";
        current_stats_.print("Stats");
    }

    // Aplicacion del bonus que teniamos de Sf = (Sb+ Sa)Sm
    void apply_buff(const Stats& bonus, const Stats& multiplier) {
        current_stats_ = (base_stats_ + bonus) * multiplier;
        cout << name_ << " recibe bonus. ";
        current_stats_.print("Nuevo Stats");
    }

    //Creo los getters y setters, con intelij seria mas rapido :c
    void take_damage(float dmg) {
        float mitigated = mitigate_damage(dmg, current_stats_.defense);
        last_damage_received_ = mitigated;
        current_stats_.hp -= mitigated;
        if (current_stats_.hp < 0.f) current_stats_.hp = 0.f;
        cout << name_ << " recibe " << mitigated
                  << " de daño (mitigado de " << dmg << "). HP restante: "
                  << current_stats_.hp << "\n";
    }

    bool is_alive() const { return current_stats_.hp > 0.f; }

    const string& name()          const { return name_; }
    const Stats&       current_stats() const { return current_stats_; }
    Stats&             current_stats()       { return current_stats_; }
    float              last_damage()   const { return last_damage_received_; }

    virtual string type() const = 0;
// Protected nos ayudara para heredar
protected:
    string name_;
    Stats       base_stats_;
    Stats       current_stats_;
    float       last_damage_received_;
};

// pasamos con el Jugador
class Jugador : public Entity {
public:
    Jugador(string name, Stats base)
        : Entity(move(name), base) {}

    void on_turn_start() override {
        cout << "(Jugador) ";
        Entity::on_turn_start();
    }

    string type() const override { return "Jugador"; }

    void use_skill(Skill& skill, Entity& target) {
        cout << name_ << " usa (" << skill.name() << ") sobre " << target.name() << "\n";
        skill.execute(current_stats_, target.current_stats());
    }
};

// Creamos a la clase Enemigo
class Enemigo : public Entity {
public:
    Enemigo(string name, Stats base, int aggro_level = 1)
        : Entity(move(name), base), aggro_level_(aggro_level) {}

    void on_turn_start() override {
        cout << "(Enemigo) ";
        Entity::on_turn_start();
    }

    string type() const override { return "Enemigo"; }

    int aggro() const { return aggro_level_; }

private:
    int aggro_level_;
};

// Hacemos el elemento del entorno
class entorno_Objeto : public Entity {
public:
    entorno_Objeto(string name, Stats base)
        : Entity(move(name), base) {}

    void on_turn_start() override {
        cout << "(Entorno) ";
        Entity::on_turn_start();
    }

    string type() const override { return "Entorno"; }
};

// Campo de Batalla
class Battlefield {
public:
    using EntityPtr = unique_ptr<Entity>;

    void add_entity(EntityPtr entity) {
        cout << entity->name() << " (" << entity->type()
                  << ") entra al campo de batalla.\n";
        entities_.push_back(move(entity));
    }

    void run_turn() {
        cout << endl<< "Nuevo Turno "<<endl;
        for (auto& e : entities_) {
            if (e->is_alive()) e->on_turn_start();
        }
        // Lanzamos el evento Turno_start
        dispatcher_.emit("turno_Start", 1);
    }

    // Acceso por nombre
    Entity* find(const string& name) {
        for (auto& e : entities_)
            if (e->name() == name) return e.get();
        return nullptr;
    }

    Despachador_de_Senales<int>& dispatcher() { return dispatcher_; }

    void print_status() const {
        cout << endl<<"#######Estado del campo##### "<<endl;
        for (auto& e : entities_) {
            cout << "  " << e->name() << " (" << e->type() << ") "
                      << (e->is_alive() ? "vivo" :"DERROTADO") << "  HP="
                      << e->current_stats().hp << "\n";
        }
        cout << "\n";
    }

    // hacemos el vector Entity
private:
    vector<EntityPtr>    entities_;
    Despachador_de_Senales<int>     dispatcher_;
};

//Probamos

int main() {
    cout << "PC1 Simulacion de Batalla"<< endl<< endl ;

    Battlefield campo;

    // Creamos a los personajes
    auto heroe = make_unique<Jugador>("Osmar", Stats(100.f, 25.f, 5.f));
    auto villano = make_unique<Enemigo>("Examen de DBP", Stats(60.f, 18.f, 2.f));

    // Guardamos punteros
    Jugador* p_heroe = heroe.get();
    Enemigo* p_villano = villano.get();

    campo.add_entity(move(heroe));
    campo.add_entity(move(villano));

    // Definimos como vamos a jugar
    // Ataque normal
    Skill tajo("Tajo Básico", [](const Stats& user, Stats& target) -> Stats {
        float dmg = mitigate_damage(user.damage, target.defense);
        target.hp = max(0.f, target.hp - dmg);
        cout << "  -> Aplica " << dmg << " de daño.\n";
        return target;
    });

    //Habilidad de curación
    Skill curar("Poción de Salud", [](const Stats& user, Stats& target) -> Stats {
        float curacion = 30.f;
        target.hp += curacion;
        cout << "Efecto verde! Recupera " << curacion << " HP. HP actual: " << target.hp << "\n";
        return target;
    });

    // Simulación de los turnos
    campo.run_turn();

    cout << endl<<"++++++ Fase de Acciones +++++++++++\n"<<endl;
    p_heroe->use_skill(tajo, *p_villano);

    // probamos el ataque directo
    cout << p_villano->name() << " ataca de vuelta\n";
    p_heroe->take_damage(p_villano->current_stats().damage);

    campo.print_status();
    //Hacemos el turno 2
    cout <<endl<<"++++++ Turno 2++++++++++"<<endl;
    p_heroe->use_skill(curar, *p_heroe);

    campo.print_status();

    return 0;
}