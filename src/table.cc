#include "table.h"

std::ostream& operator<<(std::ostream& os, const FieldDefinition& fd) {
    os << fd.name << ':' << field_type_to_string.at(fd.type);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Field& f) {
    switch (f.type) {
        case INTEGER:
            os << std::get<int>(f.val) << ':' << field_type_to_string.at(f.type);
            break;
        case STRING:
            os << std::get<std::string>(f.val) << ':' << field_type_to_string.at(f.type);
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Row& r) {
    for (const auto &field : r.fields) {
        os << field << " ";
    }
    return os;
}

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
        Table::data.push_back(r);
    }
}

void Table::select_all() {
    for (const auto &r : Table::data) {
        std::cout << r << "\n";
    }
}