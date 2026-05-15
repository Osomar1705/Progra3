
int main() {
    cout << "Simulacion de Combate " << endl;
    // campo

    Battlefield field;

    // agrangando las entidades
    auto hero  = make_unique<Player>("Arthas",  Stats(100.f, 25.f, 5.f));
    auto mage  = make_unique<Player>("Jaina",   Stats(70.f,  40.f, 2.f));
    auto goblin= make_unique<Enemy> ("Goblin",  Stats(50.f,  15.f, 3.f), 2);
    auto dragon= make_unique<Enemy> ("Dragon",  Stats(200.f, 50.f, 10.f), 5);
    auto pillar= make_unique<EnvironmentObject>("Columna", Stats(80.f, 0.f, 8.f));

    // Guardamos punteros crudos antes de mover
    Player* arthas  = hero.get();
    Player* jaina   = mage.get();
    Enemy* gob_ptr = goblin.get();
    Enemy* drag_ptr= dragon.get();

    field.add_entity(move(hero));
    field.add_entity(move(mage));
    field.add_entity(move(goblin));
    field.add_entity(move(dragon));
    field.add_entity(move(pillar));

    // --- Sección 4: Registrar eventos en el despachador ---
    field.dispatcher().connect("turn_start", [](int turn_num) {
        cout << "[Dispatcher] Turno #" << turn_num << " iniciado. Todos listos.\n";
    });
    field.dispatcher().connect("turn_start", [&](int) {
        if (!gob_ptr->is_alive())
            cout << "[Dispatcher] El Goblin ya fue derrotado.\n";
    });

    // --- Sección 5: Definir habilidades con lambdas ---

    // Ataque básico
    Skill basic_attack("Golpe Básico",
        [](const Stats& user, Stats& target) -> Stats {
            float dmg = mitigate_damage(user.damage, target.defense);
            target.hp = max(0.f, target.hp - dmg);
            cout << "  -> Inflige " << dmg << " de daño. HP objetivo: " << target.hp << "\n";
            return target;
        });

    // Contraataque: depende del daño recibido en el turno anterior (clausura)
    // Captura el estado del entorno mediante lambda con capture
    Skill counter_attack("Contraataque",
        [arthas](const Stats& user, Stats& target) -> Stats {
            float bonus  = arthas->last_damage() * 1.5f;  // clausura sobre daño previo
            float total  = user.damage + bonus;
            float dmg    = mitigate_damage(total, target.defense);
            target.hp    = max(0.f, target.hp - dmg);
            cout << "  -> Contraataque! Daño base=" << user.damage
                      << " + bonus=" << bonus << " = " << total
                      << "  mitigado=" << dmg
                      << "  HP objetivo: " << target.hp << "\n";
            return target;
        });

    // Hechizo de Jaina: daño mágico (ignora defensa)
    Skill blizzard("Blizzard",
        [](const Stats& user, Stats& target) -> Stats {
            float dmg = user.damage * 1.2f;
            target.hp = max(0.f, target.hp - dmg);
            cout << "  -> ¡Blizzard! Daño mágico=" << dmg
                      << "  HP objetivo: " << target.hp << "\n";
            return target;
        });

    // Buff de poción (solo estadísticas positivas)
    Stats potion_bonus(20.f, 5.f, 2.f);
    Stats potion_mult (1.f,  1.f, 1.f);

    // ============================================================
    // SIMULACIÓN DE COMBATE
    // ============================================================

    cout << "\n========== TURNO 1 ==========\n";
    field.run_turn();

    cout << "\n--- Acciones ---\n";

    // Arthas ataca al Goblin
    arthas->use_skill(basic_attack, *gob_ptr);

    // Goblin contraataca a Arthas (toma daño primero para probar clausura)
    gob_ptr->take_damage(arthas->current_stats().damage);   // Goblin recibe daño directo
    arthas->take_damage(gob_ptr->current_stats().damage);   // Arthas recibe daño

    // Jaina lanza Blizzard al Dragon
    jaina->use_skill(blizzard, *drag_ptr);

    // Arthas usa contraataque (captura last_damage)
    arthas->use_skill(counter_attack, *drag_ptr);

    field.print_status();

    cout << "\n========== TURNO 2 ==========\n";

    // Buff a Arthas antes del turno
    cout << "Arthas bebe una poción de poder:\n";
    arthas->apply_buff(potion_bonus, potion_mult);

    field.run_turn();

    cout << "\n--- Acciones ---\n";

    // Arthas remata al Goblin
    if (gob_ptr->is_alive()) {
        arthas->use_skill(basic_attack, *gob_ptr);
        cout << (gob_ptr->is_alive() ? "  Goblin sobrevive.\n" : "  ¡Goblin derrotado!\n");
    }

    // Jaina ataca al Dragon
    jaina->use_skill(blizzard, *drag_ptr);

    // Arthas usa contraataque contra el Dragon
    arthas->use_skill(counter_attack, *drag_ptr);

    field.print_status();

    //
    cout << "\n========== DEMO: Restricciones de Tipo (Concepts) ==========\n";

    float raw_float = 30.f, def_float = 7.f;
    float result_f  = mitigate_damage(raw_float, def_float);
    cout << "mitigate_damage(30.0f, 7.0f) = " << result_f << "\n";

    int raw_int = 20, def_int = 5;
    int result_i = mitigate_damage(raw_int, def_int);
    cout << "mitigate_damage(20, 5) = " << result_i << "\n";

    Stats raw_stats(0.f, 35.f, 0.f);
    Stats def_stats(0.f,  0.f, 8.f);
    Stats result_s = mitigate_damage(raw_stats, def_stats);
    cout << "mitigate_damage(Stats dmg=35, Stats def=8) -> daño efectivo= "
              << result_s.damage << "\n";

    // El siguiente código NO compilaría (prevención en tiempo de compilación):
    // mitigate_damage(string("x"), string("y")); // error: constraint not satisfied

    return 0;
}