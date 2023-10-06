#include "include/table.h"

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

void FieldDefinition::serialize(const std::string& filePath) {
    std::ofstream file(filePath, std::ios::binary);


    // Serialize field name length and field name
    size_t nameLength = name.size();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
    file.write(name.c_str(), nameLength);

    // Serialize field type
    FieldType fieldType = type;
    file.write(reinterpret_cast<const char*>(&fieldType), sizeof(FieldType));
}

FieldDefinition FieldDefinition::deserialize(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    // Deserialize field name length and field name
    size_t nameLength;
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
    char nameBuffer[nameLength];
    file.read(nameBuffer, nameLength);
    std::string name = std::string(nameBuffer, nameLength);

    // Deserialize field type
    FieldType type;
    file.read(reinterpret_cast<char*>(&type), sizeof(FieldType));

    return FieldDefinition(name, type);
}
