#ifndef TRANSACTIONS_ABSTRACTCLASS_H
#define TRANSACTIONS_ABSTRACTCLASS_H

#include <string>

namespace s21 {
class AbstractClass {
public:
    virtual ~AbstractClass() = default;
    virtual void Set(std::string str) = 0;
    virtual void Get(std::string str) = 0;
    virtual void Exists(std::string str) = 0;
    virtual void Del(std::string str) = 0;
    virtual void Update(std::string str) = 0;
    virtual void Keys(std::string str) = 0;
    virtual void Rename(std::string str) = 0;
    virtual void TTL(std::string str) = 0;
    virtual void Find(std::string str) = 0;
    virtual void Snowfall(std::string str) = 0;
    virtual void Upload(std::string str) = 0;
    virtual void Export(std::string str) = 0;
};
}  // namespace s21

#endif  // TRANSACTIONS_ABSTRACTCLASS_H
