/*El patrón Builder es particularmente útil cuando se trata de construir consultas SQL complejas, ya que permite una forma fluida y legible de componer consultas. En este ejercicio, emplearemos este patrón para crear consultas SQL de manera sencilla con C++.
*/
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// ── SQLQueryBuilder ───────────────────────────────────
class SQLQueryBuilder {
private:
    string table_;
    vector<string> columns_;
    string whereCol_;
    string whereVal_;
    string orderBy_;
    int    limit_    = 0;
    bool   hasLimit_ = false;
    bool   hasWhere_ = false;

public:
    SQLQueryBuilder& setTable(const string& t) {
        table_ = t;
        return *this;
    }

    SQLQueryBuilder& addColumn(const string& col) {
        columns_.push_back(col);
        return *this;
    }

    SQLQueryBuilder& setWhereClause(const string& col, const string& val) {
        whereCol_ = col;
        whereVal_ = val;
        hasWhere_ = true;
        return *this;
    }

    SQLQueryBuilder& setOrderByClause(const string& order) {
        orderBy_ = order;
        return *this;
    }

    SQLQueryBuilder& setLimit(int n) {
        limit_    = n;
        hasLimit_ = true;
        return *this;
    }

    string build() {
        // ── validaciones ──────────────────────────────
        if (table_.empty())
            throw runtime_error("Falta la tabla (setTable)");
        if (columns_.empty())
            throw runtime_error("Agrega al menos una columna (addColumn)");

        // ── SELECT ────────────────────────────────────
        string q = "SELECT ";
        for (size_t i = 0; i < columns_.size(); i++) {
            q += columns_[i];
            if (i < columns_.size() - 1) q += ",";
        }

        // ── FROM ──────────────────────────────────────
        q += " FROM " + table_;

        // ── WHERE (opcional) ──────────────────────────
        if (hasWhere_)
            q += " WHERE " + whereCol_ + " = '" + whereVal_ + "'";

        // ── ORDER BY (opcional) ───────────────────────
        if (!orderBy_.empty())
            q += " ORDER BY " + orderBy_;

        // ── LIMIT (opcional) ──────────────────────────
        if (hasLimit_)
            q += " LIMIT " + to_string(limit_);

        return q + ";";
    }
};

// ── main ──────────────────────────────────────────────
int main() {
    try {
        string query = SQLQueryBuilder()
            .setTable("empleados")
            .addColumn("id")
            .addColumn("nombre")
            .addColumn("posicion")
            .setWhereClause("posicion", "Analista")
            .setOrderByClause("nombre ASC")
            .setLimit(10)
            .build();

        cout << query << endl;
        // SELECT id,nombre,posicion FROM empleados
        // WHERE posicion = 'Analista' ORDER BY nombre ASC LIMIT 10;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}