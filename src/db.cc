#include "table.h"
#include "db.h"

int main() {
    std::unordered_map<std::string, Table*> tables;

    std::string input;
    while (true) {
        db_prompt();
        std::getline(std::cin, input);
        std::stringstream ss(input);

        // Meta commands
        if (input[0] == '.') {
            handle_meta_command(input);
            continue;
        }

        // Handle SQL Statements
        std::string op;
        ss >> op;
        if (op == "create") {
            std::string table_name;
            ss >> table_name;

            std::vector<std::pair<std::string, FieldType>> schema;
            std::string field;
            while (ss >> field) {
                int split = field.find(':');

                std::string field_name = field.substr(0, split);
                std::string field_type = field.substr(split + 1);

                schema.push_back(std::make_pair(field_name, string_to_field.at(field_type)));
            }

            Table *table = new Table(table_name, schema);
            tables[table_name] = table;
        } else if (op == "schema") {
            std::string table_name;
            ss >> table_name;

            tables[table_name]->print_schema();
        } else if (op == "select") {

        } else if (op == "insert") {
            std::string table_name;
            ss >> table_name;
        } else {
            std::cout << "Unrecognized operation: " << op << "\n";
        }
    }

    return 0;
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