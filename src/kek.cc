#include <iostream>
#include "kek.h"

int main() {
    HashTable map;
    Person kek("Utkin Dmitry 2001 Moscow 112");
    map.Set("hello", kek);
    Person kek1("Utkin Dmitry 2001 Moscow 112");
    map.Set("hello1", kek1);
    Person kek2("Utkin Loshara 2001 Moscow 112");
    map.Set("hello2", kek2);
    Person lol("Shakalov Daniel 1996 Minsk 228");
    map.Set("hey", lol);
    map.Update("hello", "Utkin - - - -");
    auto res =  map.Find("Utkin - - - -");
    for (auto item : res)
        std::cout << item << "\n";
}
