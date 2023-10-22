#include "include/table.h"
#include "include/db.h"

int main() {
    // std::ifstream file("databases/empty.txt", std::ios::out);

    // size_t size;
    // file.read(reinterpret_cast<char*>(&size), sizeof(size_t));

    // std::vector<Field> fields;
    // for (unsigned int i = 0; i < size; ++i) {
    //     fields.push_back(Field::deserialize(file));
    // }

    // for (const auto &f : fields) {
    //     std::cout << f;
    // }

    // std::cout << "\n";

    // return 0;

    std::string input;
    while (true) {
        db_prompt();
        std::getline(std::cin, input);
        std::stringstream ss(input);

        // Handle meta commands
        if (input[0] == '.') {
            handle_meta_command(input);
            continue;
        }

        // Handle SQL Statements
        std::string op; ss >> op;
        execute_sql(str_to_operator.at(op), ss);
    }

    return 0;
}

void execute_sql(Operator op, std::stringstream& ss) {
    switch (op) {
        case CREATE:
        {
            std::string table_name; ss >> table_name;

            std::vector<FieldDefinition> field_defs;
            std::string field;
            while (ss >> field) {
                int split = field.find(':');
                std::string field_name = field.substr(0, split);
                std::string field_type = field.substr(split + 1);

                field_defs.push_back(FieldDefinition(field_name, string_to_field_type.at(field_type)));
            }

            std::vector<Row> table_data;
            Table *table = new Table(table_name, Schema(field_defs), table_data);

            std::string file_path = "databases/" + table_name;
            table->serialize(file_path);
            tables[table_name] = table;
            break;
        }
        case SCHEMA:
        {
            std::string table_name; ss >> table_name;
            tables[table_name]->print_schema();
            break;
        }
        case INSERT:
        {
            std::string table_name; ss >> table_name;

            std::vector<Field> fields;
            std::string field;
            while (ss >> field) {
                int split = field.find(':');
                std::string val = field.substr(0, split);
                FieldType type = string_to_field_type.at(field.substr(split + 1));

                switch (type) {
                    case INTEGER:
                    {
                        int field_val = std::stoi(val);
                        fields.push_back(Field(type, field_val));
                        break;
                    }
                    default:
                        fields.push_back(Field(type, val));
                }
            }

            Row row = Row(fields);
            tables[table_name]->insert_row(row);
            break;
        }
        case SELECT:
        {
            std::string table_name; ss >> table_name;
            tables[table_name]->select_all();

            break;
        }
        case LOAD:
        {
            std::string table_name; ss >> table_name;
            std::string file_path = "databases/" + table_name;
            Table* test = Table::deserialize(file_path);

            tables[table_name] = test;
            break;
        }
        default:
            std::cout << "Invalid SQL statement.\n";
    }
}

void handle_meta_command(std::string input) {
    if (input == ".exit") {
        std::cout << "Exiting database...\n";
        exit(0);
    } else {
        std::cout << "Unrecognized command: " << input << "\n";
    }
}

void db_prompt() {
    std::cout << "db > ";
}