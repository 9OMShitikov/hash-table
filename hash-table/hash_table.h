#ifndef HASH_TABLE_HASH_TABLE_H
#define HASH_TABLE_HASH_TABLE_H

#include <cstdlib>
#include <cstring>
#include <iostream>

const size_t table_size = 524288;
const size_t alignment = 16;
template <class T>
class HashTable {
public:
    struct Entry;

    struct MyString {
        explicit MyString(const char* string);
        ~MyString() {
            if (my_string != NULL) {
                free(my_string);
            }
            my_string = NULL;
        }

        char* my_string;
        size_t size;
    };

    struct Entry {
        MyString key;
        T value;
        size_t hash;
        ~Entry() = default;
    };

    class Iterator {
        friend HashTable;
    public:
        bool is_empty() {
            return entry_ == nullptr;
        }
        MyString& get_string() {
            return entry_->key;
        }
        T& get_value() {
            return entry_->value;
        }
        void set_value(const T& value) {
            entry_->value = value;
        }
    private:
        explicit Iterator(Entry* entry): entry_(entry) {
        }
        Entry* entry_;
    };

    HashTable();
    ~HashTable();

    Iterator find(const char* key);
    Iterator add (const char* key, const T& value);
private:

    virtual size_t get_hash (MyString* hashed) = 0;
    virtual bool mystrcmp (const char* first, const char* second) = 0;
    Entry** table_;
    size_t* sizes_;
    size_t* bounds_;
};

template <class T>
HashTable<T>::HashTable() {
    table_ = (Entry**) calloc(table_size, sizeof(Entry*));
    sizes_ = (size_t*) calloc(table_size, sizeof(size_t));
    bounds_ = (size_t*) calloc(table_size, sizeof(size_t));
    const size_t start_len = 10;
    for (int i = 0; i < table_size; ++i) {
        bounds_[i] = start_len;
        sizes_[i] = 0;
        table_[i] = (Entry*) calloc(start_len, sizeof(Entry));
    }
}

template <class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < table_size; ++i) {
        Entry *next = table_[i];
        for (int j = 0; j < sizes_[i]; ++j) {
            next[j].~Entry();
        }
        free(table_[i]);
    }
    free (table_);
    free(sizes_);
    free(bounds_);
}

template <class T>
typename HashTable<T>::Iterator HashTable<T>::find(const char* key) {
    MyString my_string(key);
    size_t hash = get_hash(&my_string);
    if (hash >= table_size) {
        throw;
    }

    Entry* checked_list = table_[hash];
    size_t s = sizes_[hash];
    for (int i = 0; i < s; ++i) {
        if (mystrcmp(my_string.my_string, checked_list[i].key.my_string) == 0) {
            return Iterator(&checked_list[i]);
        }
    }
    return Iterator(nullptr);
}


template <class T>
typename HashTable<T>::Iterator HashTable<T>::add (const char* key, const T& value) {
    MyString added(key);
    size_t pos = get_hash(&added);

    ++sizes_[pos];
    if (sizes_[pos] == bounds_[pos]) {
        bounds_[pos] *= 2;
        Entry* new_list = (Entry*) calloc(bounds_[pos], sizeof(Entry));
        for (int i = 0; i < sizes_[pos]; ++i) {
            new_list[i] = table_[pos][i];
        }
        free(table_[pos]);
        table_[pos] = new_list;
    }

    size_t ind = sizes_[pos] - 1;
    table_[pos][ind].key.my_string = added.my_string;
    table_[pos][ind].key.size = added.size;
    table_[pos][ind].value = value;
    table_[pos][ind].hash = pos;

    added.my_string = NULL;
}

template <class T>
HashTable<T>::MyString::MyString(const char* string) {
    size = strlen(string);
    my_string = (char*) aligned_alloc(alignment, size - size % alignment + 2 * alignment);
    memset(my_string, 0, size - size % alignment + 2 * alignment);
    strcpy(my_string, string);
}
#endif //HASH_TABLE_HASH_TABLE_H
