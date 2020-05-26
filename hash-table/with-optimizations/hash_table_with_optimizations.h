
#ifndef HASH_TABLE_HASH_TABLE_WITH_OPTIMIZATIONS_H
#define HASH_TABLE_HASH_TABLE_WITH_OPTIMIZATIONS_H

#include "hash_table_with_optimizations.h"
#include "../hash_table.h"
#include <cstring>

extern "C" size_t GetHash(void* hashed);
extern "C" size_t CmpStr(const char* first, const char* second);

template<class T>
class HashtableWithOptimizations: public HashTable<T> {
    using typename HashTable<T>::MyString;
private:
    size_t get_hash (MyString* hashed) {
        return GetHash(hashed);
    }
    bool mystrcmp (const char* first, const char* second) {
        return CmpStr(first, second) != 0;
    }
};

#endif //HASH_TABLE_HASH_TABLE_WITH_OPTIMIZATIONS_H
