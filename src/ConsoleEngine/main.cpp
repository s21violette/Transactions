#include "ConsoleEngine.h"

int main() {
    s21::ConsoleEngine console;
#ifdef HASHTABLE
    console.SetHashTable();
#endif
#ifndef SELFBALANCINGBINARYSEARCHTREE
    console.SetSelfBalancingBinarySearchTree();
#endif
#ifdef BPLUSTREE
    console.SetBPlusTree();
#endif
    console.Start();
    return 0;
}
