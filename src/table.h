#include <vector>
#include <utility>
#include <string>
#include <map>
#include <iostream>

typedef enum {
    INTEGER,
    STRING,
} FieldType;

const std::unordered_map<std::string, FieldType> string_to_field = {
    {"int", INTEGER},
    {"string", STRING}
};

const std::unordered_map<FieldType, std::string> field_to_string = {
    {INTEGER, "int"},
    {STRING, "string"}
};

class Table {
    std::string name;
    std::vector<std::pair<std::string, FieldType> > schema;
    std::vector<FieldType> rows;

    public:
        Table(std::string n, std::vector<std::pair<std::string, FieldType> > s);
        void print_schema();
};