#include "HashTable.h"

namespace s21 {
HashTable::HashTable() {
    values_vector.resize(3);
    for (Values* values : values_vector) {
        values = nullptr;
    }
}

HashTable::~HashTable() {
    for (Values* values : values_vector) {
        if (values) delete values;
    }
}

void HashTable::Start() {
    std::string function, operands;
    std::cin >> function;
    getline(std::cin, operands);
    std::cout << "function == " << function << std::endl;
    std::cout << "operands == " << operands << std::endl;
    if (function == "SET") {
        Set(operands);
    } else if (function == "GET") {
        std::cout << "GET function" << std::endl;
    } else if (function == "EXISTS") {
        std::cout << "EXISTS function" << std::endl;
    } else if (function == "DEL") {
        std::cout << "DEL function" << std::endl;
    } else if (function == "UPDATE") {
        std::cout << "UPDATE function" << std::endl;
    } else if (function == "KEYS") {
        std::cout << "KEYS function" << std::endl;
    } else if (function == "RENAME") {
        std::cout << "RENAME function" << std::endl;
    } else if (function == "TTL") {
        std::cout << "TTL function" << std::endl;
    } else if (function == "FIND") {
        std::cout << "FIND function" << std::endl;
    } else if (function == "SHOWALL") {
        std::cout << "SHOWALL function" << std::endl;
    } else if (function == "UPLOAD") {
        std::cout << "UPLOAD function" << std::endl;
    } else if (function == "EXPORT") {
        std::cout << "EXPORT function" << std::endl;
    } else {
        std::cout << "Invalid function" << std::endl;
    }
}

void HashTable::Set(std::string operands) {
    std::istringstream iss(operands);
    std::string key;
    Values values;
    if (!(iss >> key) || !(iss >> values.last_name_) || !(iss >> values.first_name_) ||
        !(iss >> values.year_of_birth_) || !(iss >> values.city_) || !(iss >> values.number_of_coins_)) {
        std::cout << "Invalid operands" << std::endl;
    } else {
        values.key_ = key;
        if (number_of_indexes_filled_in == values_vector.size()) {
            values_vector.resize(number_of_indexes_filled_in + buffer_size_);
        }
        int key_int = StringToKeyInt(key), i = 0;
        std::cout << "key_int == " << key_int << std::endl;
        while (true) {
            int index = (key_int + i * HashFunction2(key_int)) % values_vector.size();
            std::cout << "index == " << index << std::endl;
            if (!values_vector[index]) {
                values_vector[index] = new Values(values);
                ++number_of_indexes_filled_in;
                break;
            } else if (values_vector[index]->key_ == key) {
                std::cout << "The key already exists" << std::endl;
                break;
            }
            ++i;
        }
    }
}

int HashTable::StringToKeyInt(std::string str) {
    int key_int = 0;
    for (char c : str) {
        key_int += c;
    }
    return key_int;
}

int HashTable::HashFunction1(int key) { return key % values_vector.size(); }

int HashTable::HashFunction2(int key) { return 1 + key % (values_vector.size() - 1); }
}  // namespace s21

int main() {
    s21::HashTable hash_table;
    while (true) {
        hash_table.Start();
    }
}