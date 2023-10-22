#include "include/table.h"

void Schema::print() {
    for (const auto &def : Schema::field_defs) {
        std::cout << def << " ";
    }

    std::cout << "\n";
}

bool Table::validate_row(Row &r) {
    if (r.size != Table::schema.size) {
        return false;
    }

    for (unsigned int i = 0; i < r.size; ++i) {
        if (r.fields[i].type != Table::schema.field_defs[i].type) {
            return false;
        }
    }

    return true;
}

void Table::print_schema() {
    Table::schema.print();
}

void Table::insert_row(Row &r) {
    if (validate_row(r)) {
        std::string file_path = "databases/" + Table::name;
        r.serialize(file_path);

        Table::data.push_back(r);
    }
}

void Table::select_all() {
    for (const auto &r : Table::data) {
        std::cout << r << "\n";
    }
}