#ifndef TRANSACTIONS_ABSTRACTCLASS_H
#define TRANSACTIONS_ABSTRACTCLASS_H

class AbstractClass {
public:
    virtual ~AbstractClass() = default;
    virtual void Set() = 0;
    virtual void Get() = 0;
    virtual void Exists() = 0;
    virtual void Del() = 0;
    virtual void Update() = 0;
    virtual void Keys() = 0;
    virtual void Rename() = 0;
    virtual void TTL() = 0;
    virtual void Find() = 0;
    virtual void Snowfall() = 0;
    virtual void Upload() = 0;
    virtual void Export() = 0;
};

#endif  // TRANSACTIONS_ABSTRACTCLASS_H
