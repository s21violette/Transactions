#ifndef TRANSACTIONS_HASHTABLE_H
#define TRANSACTIONS_HASHTABLE_H

#include <vector>

#include "../AbstractClass.h"

class HashTable : public AbstractClass {
public:
    HashTable();
    ~HashTable();
    void Start();
    void Set();
    void Get();
    void Exists();
    void Del();
    void Update();
    void Keys();
    void Rename();
    void TTL();
    void Find();
    void Snowfall();
    void Upload();
    void Export();

private:
    struct Values {
        std::string last_name;
        std::string first_name;
        int year_of_birth;
        std::string city;
        int number_of_coins;
    };
    std::vector<std::pair<int, Values*> keys;
    void HashFunction1(double key);
    void HashFunction2(double key);
};

#endif  // TRANSACTIONS_HASHTABLE_H
