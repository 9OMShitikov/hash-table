
#ifndef HASH_TABLE_HASH_TABLE_WITH_OPTIMIZATIONS_H
#define HASH_TABLE_HASH_TABLE_WITH_OPTIMIZATIONS_H

#include "hash_table_with_optimizations.h"
#include "../hash_table.h"
#include <cstring>

extern "C" uint GetHash(void* hashed);

template<class T>
class HashtableWithOptimizations: public HashTable<T> {
    using typename HashTable<T>::MyString;
private:
    const size_t hash_expon = 257;
    uint get_hash (MyString* hashed) {
        return GetHash(hashed);
    }
    bool mystrcmp (const char* first, const char* second) {
        return strcmp(first, second) != 0;
    }
};

#endif //HASH_TABLE_HASH_TABLE_WITH_OPTIMIZATIONS_H
