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

void HashTable::Set(Values values) {
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
            break;
        }
    }
}

Values HashTable::Get(std::string key) {
    int key_int = StringToKeyInt(key), number_of_scanned_keys = 0;
    i_ = 0;
    Values empty_values;
    std::cout << "key_int == " << key_int << std::endl;
    while (true) {
        int index = HashFunction(key_int);
        if (!values_vector[index]) {
            return empty_values;
            break;
        } else if (values_vector[index]->key_ == key) {
            return *values_vector[index];
            break;
        } else if (++number_of_scanned_keys == values_vector.size()) {
            return empty_values;
            break;
        }
    }
    return empty_values;
}

bool HashTable::Exists(std::string key) {
    return false;
}

bool HashTable::Del(std::string key) {
    return false;
}

bool HashTable::Update(Values values) {
    return false;
}

std::vector<std::string> HashTable::Keys() {
    return std::vector<std::string>();
}

bool HashTable::Rename(std::string key_old, std::string key) {
    return false;
}

int HashTable::TTL(std::string key) {
    return -1;
}

void HashTable::Find(Values values) {

}

std::vector<Values> HashTable::ShowAll() {
    return std::vector<Values>();
}

int HashTable::Upload(std::fstream& fs) {
    return -1;
}

int HashTable::Export(std::fstream& fs) {
    return -1;
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