#ifndef TRANSACTIONS_HASHTABLE_H
#define TRANSACTIONS_HASHTABLE_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../AbstractClass.h"

namespace s21 {
class HashTable : public AbstractClass {
public:
    HashTable();
    ~HashTable();
    void Start();
    void Set(std::string str);
    void Get(std::string str) {}
    void Exists(std::string str) {}
    void Del(std::string str) {}
    void Update(std::string str) {}
    void Keys(std::string str) {}
    void Rename(std::string str) {}
    void TTL(std::string str) {}
    void Find(std::string str) {}
    void Snowfall(std::string str) {}
    void Upload(std::string str) {}
    void Export(std::string str) {}

private:
    int buffer_size_ = 10;
    struct Values {
        Values() = default;
        Values(Values& other_values)
            : key_(other_values.key_),
              last_name_(other_values.last_name_),
              first_name_(other_values.first_name_),
              year_of_birth_(other_values.year_of_birth_),
              city_(other_values.city_),
              number_of_coins_(other_values.number_of_coins_) {}
        std::string key_;
        std::string last_name_;
        std::string first_name_;
        int year_of_birth_;
        std::string city_;
        int number_of_coins_;
        Values* next;
    };

    std::vector<Values*> values_vector;
    int number_of_indexes_filled_in = 0;

    int StringToKeyInt(std::string str);
    int HashFunction1(int key);
    int HashFunction2(int key);
};
}  // namespace s21

#endif  // TRANSACTIONS_HASHTABLE_H
