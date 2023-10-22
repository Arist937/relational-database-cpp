#include <iostream>
#include <sstream>
#include <string>
#include <map>

typedef enum {
    CREATE,
    SCHEMA,
    INSERT,
    SELECT,
    LOAD,
} Operator;

const std::unordered_map<std::string, Operator> str_to_operator = {
    {"create", CREATE},
    {"schema", SCHEMA},
    {"insert", INSERT},
    {"select", SELECT},
    {"load", LOAD},
};

std::unordered_map<std::string, Table*> tables;

void execute_sql(Operator op, std::stringstream& ss);
void handle_meta_command(std::string input);
void db_prompt();