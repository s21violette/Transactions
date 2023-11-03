#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;
using std::pair;

class Person {
public:
    Person(string name="-", string surname="-",
           string city="-", int year=-1, int coins=-1,
           int time=-1, bool temporary=false) {
        fill_data(name, surname, city, year, coins, time, temporary);
    }

    Person(const Person &other) {
        *this = other;
    }

    void operator=(const Person &other) {
        fill_data(other.name_, other.surname_, other.city_,
                  other.year_, other.coins_, other.time_, other.temporary_);
    }

    bool operator==(const Person &other) const {
        return (name_ == other.name_ && surname_ == other.surname_ &&
                city_ == other.city_ && year_ == other.year_ &&
                coins_ == other.coins_ && time_ == other.time_);
    }

    string GetInfo() const {
        string ret = surname_ + " " +
                     name_ + " " +
                     std::to_string(year_) + " " +
                     city_ + " " +
                     std::to_string(coins_);
        return ret;
    }

private:
    string name_;
    string surname_;
    string city_;
    int coins_;
    int year_;
    int time_;
    bool temporary_;

    void fill_data(string name, string surname, string city,
                   int year, int coins, int time, bool temporary) {
        this->name_ = name;
        this->surname_ = surname;
        this->city_ = city;
        this->year_ = year;
        this->coins_ = coins;
        this->time_ = time;
        this->temporary_ = temporary;
    }
};

using HashNode = pair<string, Person>;  // first - Key, second - Person

class HashTable {
public:
    HashTable() {
        arr_.resize(1024);
    }

    bool SET(const string &key, const Person &value) {
        int idx = hashFunction_(key);
        HashNode new_node = HashNode(key, value);
        arr_[idx].push_back(new_node);
        keys_.push_back(key);
        return true;
    }

    string GET(const string &key) const {
        try {
            HashNode item = find_item(key);
            return item.second.GetInfo();
        } catch (const std::invalid_argument &) {
            return "(null)";
        }
    }

    bool DEL(const string &key) {
        int idx = hashFunction_(key);
        try {
            HashNode item = find_item(key);
            std::remove(keys_.begin(), keys_.end(), item.first);
            arr_[idx].remove(item);
            return true;
        } catch (const std::invalid_argument &) {
            return false;
        }
    }

    bool UPDATE(const string &key, const string &value) {

    }

    const vector<string> KEYS() const {
        return keys_;
    }

private:
    vector<list<HashNode>> arr_;
//    TODO Might wanna change keys_'s type to my own binary tree
    vector<string> keys_;

//    Reverse polynomial hash function
    int hashFunction_(const string &key) const {
        const int factor = 31;
        long long hash = 0;
        int size = arr_.capacity();

        for (char c : key) {
            int x = (int) (c - 'a' + 1);
            hash = (hash * factor + x) % size;
        }
        return hash;
    }

    const HashNode find_item(const string &key) const {
        int idx = hashFunction_(key);

        for (const auto &item : arr_[idx]) {
            if (item.first == key) {
                return item;
            }
        }
        throw std::invalid_argument("");
    }
};

int main() {
    HashTable map;
    string key, val;
    Person kek("Dmitry", "Utkin", "Moscow", 2001, 228, -1, false);
    Person lol("Daniel", "Shakalov", "Minsk", 1996, 228, -1, false);
    map.SET("hallo", lol);
    map.SET("hello", kek);
//    while (true) {
//        std::cin >> key;
//        if (key == "q")
//            break;
//        std::cin >> val;
//        map.SET(key, val);
//    }
//    std::cout << map.DEL("hallo") << std::endl;
    std::cout << map.GET("hello") << std::endl;
//    std::cout << map.GET("hallo");
}
