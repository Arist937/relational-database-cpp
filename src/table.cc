#include "table.h"

std::ostream& operator<<(std::ostream& os, const FieldDefinition& fd) {
    os << fd.name << ':' << field_type_to_string.at(fd.type);
    return os;
}

void Schema::print() {
    for (const auto &def : Schema::field_defs) {
        std::cout << def << " ";
    }

    std::cout << "\n";
}

void Table::print_schema() {
    Table::schema.print();
}

void Table::insert_row() {

}