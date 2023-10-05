#include <vector>
#include <utility>
#include <string>
#include <map>
#include <iostream>

typedef enum {
    INTEGER,
    STRING,
} FieldType;

typedef std::variant<int, std::string> FieldValue;

const std::unordered_map<std::string, FieldType> string_to_field_type = {
    {"int", INTEGER},
    {"string", STRING}
};

const std::unordered_map<FieldType, std::string> field_type_to_string = {
    {INTEGER, "int"},
    {STRING, "string"}
};

class FieldDefinition {
    const std::string name;
    const FieldType type;

    public:
        FieldDefinition(std::string n, FieldType t) : name{n}, type{t} {}
        friend std::ostream& operator<<(std::ostream& os, const FieldDefinition& fd);
};

class Field {
    const FieldValue val;
    const FieldType type;

    public:
        Field(FieldValue v, FieldType t) : val{v}, type{t} {}
};

class Row {
    const std::vector<Field> fields;

    public:
        Row(std::vector<Field> f) : fields{f} {}
};

class Schema {
    const std::vector<FieldDefinition> field_defs;

    public:
        Schema(std::vector<FieldDefinition> f) : field_defs{f} {}
        void print();
};

class Table {
    std::string name;
    Schema schema;
    std::vector<Row> data;

    public:
        Table(std::string n, Schema s) : name{n}, schema{s} {}

        void insert_row();
        void print_schema();
};