#include "table.h"

Table::Table(std::string n, std::vector<std::pair<std::string, FieldType> > s) {
    Table::name = n;
    Table::schema = s;
}

void Table::print_schema() {
    for (const auto& field : Table::schema) {
        std::cout << field.first << ":" << field_to_string.at(field.second) << " ";
    }
    
    std::cout << std::endl;
}