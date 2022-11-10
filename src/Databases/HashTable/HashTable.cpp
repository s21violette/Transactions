#include "HashTable.h"

namespace s21 {
HashTable::HashTable() {
    values_vector.resize(buffer_size_);
    for (Values* values : values_vector) {
        values = nullptr;
    }
}

HashTable::~HashTable() {
    for (Values* values : values_vector) {
        if (values) delete values;
    }
}

void HashTable::Set(std::string operands) {
    std::istringstream iss(operands);
    Values values;
    char c;
    std::string year_of_birth, number_of_coins;
    if (!(iss >> values.key_) || !(iss >> values.last_name_) || !(iss >> values.first_name_) ||
        !(iss >> year_of_birth) || !(iss >> values.city_) || !(iss >> number_of_coins) || (iss >> c)) {
        std::cout << "Invalid operands" << std::endl;
    } else if (values.key_ == "-") {
        std::cout << "You must specify the key" << std::endl;
    } else if (!IsNumber(year_of_birth) && year_of_birth != "-") {
        std::cout << "ERROR: unable to cast value \"" << year_of_birth << "\" to type int" << std::endl;
    } else if (!IsNumber(number_of_coins) && number_of_coins != "-") {
        std::cout << "ERROR: unable to cast value \"" << number_of_coins << "\" to type int" << std::endl;
    } else {
        values.year_of_birth_ = atoi(year_of_birth.c_str());
        values.number_of_coins_ = atoi(number_of_coins.c_str());
        if (number_of_indexes_filled_in >= values_vector.size() * 0.75) {
            values_vector.resize(number_of_indexes_filled_in + buffer_size_);
        }
        int key_int = StringToKeyInt(values.key_);
        i_ = 0;
        std::cout << "key_int == " << key_int << std::endl;
        while (true) {
            int index = HashFunction(key_int);
            std::cout << "index == " << index << std::endl;
            if (!values_vector[index]) {
                values_vector[index] = new Values(values);
                ++number_of_indexes_filled_in;
                break;
            } else if (values_vector[index]->key_ == values.key_) {
                std::cout << "The key already exists" << std::endl;
                break;
            }
        }
    }
}

std::string HashTable::Get(std::string operands) {
    std::istringstream iss(operands);
    std::string key;
    char c;
    std::string year_of_birth, number_of_coins;
    if (!(iss >> key) || (iss >> c)) {
        std::cout << "Invalid operands" << std::endl;
    } else if (key == "-") {
        std::cout << "You must specify the key" << std::endl;
    } else {
        int key_int = StringToKeyInt(key), number_of_scanned_keys = 0;
        i_ = 0;
        std::cout << "key_int == " << key_int << std::endl;
        while (true) {
            int index = HashFunction(key_int);
//            std::cout << "index == " << index << std::endl;
            if (!values_vector[index]) {
                return std::string("(null)");
                break;
            } else if (values_vector[index]->key_ == key) {
                return values_vector[index]->last_name_ + " " + values_vector[index]->first_name_ + " " +
                       std::to_string(values_vector[index]->year_of_birth_) + " " +
                       values_vector[index]->city_ + " " +
                       std::to_string(values_vector[index]->number_of_coins_);
                break;
            } else if (++number_of_scanned_keys == values_vector.size()) {
                return std::string("(null)");
                break;
            }
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

int HashTable::HashFunction(int key) {
    return (key + i_++ * (1 + key % (values_vector.size() - 1))) % values_vector.size();
}
}  // namespace s21