#include <algorithm>
#include <sstream>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;
using std::pair;

class Person {
public:
    Person(const Person &other) {
        *this = other;
    }

    Person(const string &parameters) {
        ParseInput(parameters);
    }

    void ParseInput(const string &parameters) {
        vector<string> p;
        string str;
        std::stringstream ss(parameters);
        while (std::getline(ss, str, ' ')) {
            if (str.length() > 0)
                p.push_back(str);
        }
        if (p.size() == 5)
            fill_data(p[0], p[1], get_val(p[2]), p[3], get_val(p[4]));
        else if (p.size() == 6)
            fill_data(p[0], p[1], get_val(p[2]), p[3],
                      get_val(p[4]), get_val(p[5]));
    }

    void operator=(const Person &other) {
        fill_data(other.surname_, other.name_, other.year_,
                  other.city_, other.coins_, other.time_);
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

    int get_val(const string &str) {
        if (str == "-")
            return -1;
        return std::stol(str);
    }

    void fill_data(string surname, string name,
                   int year, string city,
                   int coins, int time=-1) {
        if (name != "-")
            this->name_ = name;
        if (surname != "-")
            this->surname_ = surname;
        if (city != "-")
            this->city_ = city;
        if (year != -1)
            this->year_ = year;
        if (coins != -1)
            this->coins_ = coins;
        this->time_ = time;
    }
};

using HashNode = pair<string, Person>;  // first - Key, second - Person

class HashTable {
public:
    HashTable() {
        arr_.resize(1024);
    }

    bool Set(const string &key, const Person &value) {
        if (std::find(keys_.begin(), keys_.end(), key) != keys_.end())
            return false;
        int idx = hashFunction_(key);
        HashNode new_node = HashNode(key, value);
        arr_[idx].push_back(new_node);
        keys_.push_back(key);
        return true;
    }

    [[nodiscard]] string Get(const string &key) const {
        try {
            HashNode item = find_item(key);
            return item.second.GetInfo();
        } catch (const std::invalid_argument &) {
            return "(null)";
        }
    }

//    [[nodiscard]] bool

    bool Del(const string &key) {
        int idx = hashFunction_(key);
        try {
            HashNode item = find_item(key);
            keys_.erase(std::remove(
                            keys_.begin(),
                            keys_.end(),
                            item.first),
                        keys_.end());
            arr_[idx].remove(item);
            return true;
        } catch (const std::invalid_argument &) {
            return false;
        }
    }

    bool Update(const string &key, const string &value) {
            int idx = hashFunction_(key);
            for (auto &item : arr_[idx]) {
                if (item.first == key) {
                    Person tmp(item.second);
                    tmp.ParseInput(value);
                    item.second = tmp;
                    return true;
                }
            }
            return false;
    }

    [[nodiscard]] const vector<string> Keys() const {
        return keys_;
    }

    bool Rename(const string &old_key, const string &new_key) {
        int idx = hashFunction_(old_key);
        if (old_key != new_key) {
            for (auto &item: arr_[idx]) {
                if (item.first == old_key) {
                    Person node = item.second;
                    Set(new_key, node);
                    return Del(item.first);
                }
            }
        }
        return false;
    }

    [[nodiscard]] const vector<string> Find(const string &data) {
        vector<string> ret;
        for (const string &key : keys_) {
            int idx = hashFunction_(key);
            for (HashNode &item: arr_[idx]) {
                if (item.first == key) {
                    Person compare(item.second);
                    compare.ParseInput(data);
                    if (item.second == compare)
                       ret.push_back(key);
                }
            }
        }
        return ret;
    }

private:
    vector<list<HashNode>> arr_;
//    TODO Might wanna change keys_'s type to my own binary tree
//    TODO function EXISTS for hash

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

    const HashNode &find_item(const string &key) const {
        int idx = hashFunction_(key);

        for (const auto &item : arr_[idx]) {
            if (item.first == key) {
                return item;
            }
        }
        throw std::invalid_argument("");
    }
};