#include <vector>
#include <utility>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

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
        void serialize(std::ofstream &file) const;
        static FieldDefinition deserialize(std::ifstream &file);

        FieldDefinition(std::string n, FieldType t) : name{n}, type{t} {}
        
        friend std::ostream& operator<<(std::ostream& os, const FieldDefinition& fd);
        friend class Table;
};

class Field {
    const FieldType type;
    const FieldValue val;

    public:
        void serialize(std::ofstream& file) const;
        static Field deserialize(std::ifstream& file);
        Field(FieldType t, FieldValue v) : type{t}, val{v} {}

        friend std::ostream& operator<<(std::ostream& os, const Field& f);
        friend class Table;
};

class Row {
    const std::vector<Field> fields;

    public:
        const size_t size;
        void serialize(const std::string& file_path) const;
        static Row deserialize(std::ifstream& file);
        Row(std::vector<Field> f) : fields{f}, size{f.size()} {}
        
        friend std::ostream& operator<<(std::ostream& os, const Row& r);
        friend class Table;
};

class Schema {
    const std::vector<FieldDefinition> field_defs;

    public:
        void serialize(std::ofstream &file) const;
        static Schema deserialize(std::ifstream &file);

        const size_t size;
        Schema(std::vector<FieldDefinition> f) : field_defs{f}, size{f.size()} {}
        void print();

        friend class Table;
};

class Table {
    std::string name;
    std::vector<Row> data;

    bool validate_row(Row &r);

    public:
        Schema schema;
        Table(std::string n, Schema s, std::vector<Row> d) : name{n}, schema{s}, data{d} {}

        void insert_row(Row &r);
        void select_all();
        void print_schema();

        void serialize(const std::string& filePath) const;
        static Table* deserialize(const std::string& filePath);
};