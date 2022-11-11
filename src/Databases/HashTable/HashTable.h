#ifndef TRANSACTIONS_HASHTABLE_H
#define TRANSACTIONS_HASHTABLE_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../AbstractDatabase.h"

namespace s21 {
class HashTable : public AbstractDatabase {
public:
    HashTable();
    ~HashTable();
    void Set(Values values);
    Values Get(std::string key);
    bool Exists(std::string key);
    bool Del(std::string key);   // возвращает false, если ключа нет
    bool Update(Values values);  // возвращает false, если ключа нет
    std::vector<std::string> Keys();
    bool Rename(std::string key_old, std::string key);  // возвращает false, если ключа нет
    int TTL(std::string key);
    void Find(Values values);
    std::vector<Values> ShowAll();
    int Upload(std::fstream& fs);  // возвращает кол-во считанных строк
    int Export(std::fstream& fs);  // возвращает кол-во выгруженных строк

private:
    int buffer_size_ = 10;

    std::vector<Values*> values_vector;
    int number_of_indexes_filled_in = 0;

    bool IsNumber(const std::string& s);
    int StringToKeyInt(std::string str);
    int i_;
    int HashFunction(int key);
};
}  // namespace s21

#endif  // TRANSACTIONS_HASHTABLE_H
