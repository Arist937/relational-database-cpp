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
        friend class Table;
};

class Field {
    const FieldValue val;
    const FieldType type;

    public:
        Field(FieldValue v, FieldType t) : val{v}, type{t} {}

        friend std::ostream& operator<<(std::ostream& os, const Field& f);
        friend class Table;
};

class Row {
    const std::vector<Field> fields;

    public:
        const size_t size;

        Row(std::vector<Field> f) : fields{f}, size{f.size()} {}
        
        friend std::ostream& operator<<(std::ostream& os, const Row& r);
        friend class Table;
};

class Schema {
    const std::vector<FieldDefinition> field_defs;

    public:
        const size_t size;

        Schema(std::vector<FieldDefinition> f) : field_defs{f}, size{f.size()} {}
        void print();

        friend class Table;
};

class Table {
    std::string name;
    Schema schema;
    std::vector<Row> data;

    bool validate_row(Row &r);

    public:
        Table(std::string n, Schema s) : name{n}, schema{s} {}

        void insert_row(Row &r);
        void select_all();
        void print_schema();
};