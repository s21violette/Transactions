#ifndef TRANSACTIONS_HASHTABLE_H
#define TRANSACTIONS_HASHTABLE_H

#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../AbstractDatabase.h"

namespace s21 {
class HashTable : public AbstractDatabase {
public:
    HashTable();
    ~HashTable() override;
    void Set(Values values) override;
    Values Get(std::string key) override;
    bool Exists(std::string key) override;
    bool Del(std::string key) override;   // возвращает false, если ключа нет
    bool Update(Values values) override;  // возвращает false, если ключа нет
    std::vector<std::string> Keys() override;
    bool Rename(std::string key_old, std::string key) override;  // возвращает false, если ключа нет
    int TTL(std::string key) override;
    void Find(Values values) override;
    std::vector<Values> ShowAll() override;
    int Upload(std::fstream& fs) override;  // возвращает кол-во считанных строк
    int Export(std::fstream& fs) override;  // возвращает кол-во выгруженных строк

private:
    int buffer_size_ = 10;
    std::vector<Values*> values_vector;
    int number_of_indexes_filled_in = 0;

    int StringToKeyInt(std::string str);
    int i_;
    int HashFunction(int key);
    static void DeleteByTimer(HashTable* object, std::string key, int seconds);
};
}  // namespace s21

#endif  // TRANSACTIONS_HASHTABLE_H
