#ifndef HASH_TABLE_HASH_TABLE_H
#define HASH_TABLE_HASH_TABLE_H

#include <cstdlib>
#include <cstring>
#include <iostream>
typedef unsigned int uint;
const size_t table_size = 524288;
const size_t alignment = 64;
template <class T>
class HashTable {
public:
    struct Entry;

    struct MyString {
        explicit MyString(const char* string);
        ~MyString() {
            free(my_string);
            my_string = nullptr;
        }

        char* my_string;
        size_t size;
    };

    struct Entry {
        MyString key;
        T value;
        size_t hash;
        Entry* next = nullptr;
        Entry* prev = nullptr;
        ~Entry();
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
    void erase(Iterator& it);
    Iterator add (const char* key, const T& value);
private:

    virtual uint get_hash (MyString* hashed) = 0;
    virtual bool mystrcmp (const char* first, const char* second) = 0;
    Entry** table_;
};

template <class T>
HashTable<T>::HashTable() {
    table_ = (Entry**) calloc(table_size, sizeof(Entry*));
}

template <class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < table_size; ++i) {
        Entry *next = table_[i], *tmp = nullptr;
        while (next != nullptr) {
            tmp = next;
            next = next->next;
            delete(tmp);
        }
    }
    free (table_);
}

template <class T>
typename HashTable<T>::Iterator HashTable<T>::find(const char* key) {
    MyString my_string(key);
    uint hash = get_hash(&my_string);

    if (hash >= table_size) {
        throw;
    }

    Entry* checked = table_[hash];
    while (checked != nullptr) {
        if (mystrcmp(my_string.my_string, checked->key.my_string) == 0) {
            return Iterator(checked);
        }
        checked = checked->next;
    }
    return Iterator(nullptr);
}

template <class T>
HashTable<T>::Entry::~Entry() {
    prev = nullptr;
    next = nullptr;
}

template <class T>
typename HashTable<T>::Iterator HashTable<T>::add (const char* key, const T& value) {
    auto new_head = new Entry ({
                                       MyString (key),
                                       value,
                                       0,
                                       nullptr,
                                       nullptr
                               });

    uint pos = get_hash(&(new_head->key));
    Entry* last_head = table_[pos];
    new_head->hash = pos;
    new_head->next = last_head;
    table_[pos] = new_head;
    if (last_head != nullptr) {
        last_head->prev = table_[pos];
    }
}

template <class T>
void HashTable<T>::erase (Iterator& it) {
    if (it.entry_ == nullptr) {
        return;
    }
    if (it.entry_->prev != nullptr) {
        it.entry_->prev->next = it.entry_->next;
    }
    else {
        table_[it.entry_->hash] = it.entry_->next;
    }
    if (it.entry_->next != nullptr) {
        it.entry_->next->prev = it.entry_->prev;
    }
    delete it.entry_;
    it.entry_ = nullptr;
}

template <class T>
HashTable<T>::MyString::MyString(const char* string) {
    size = strlen(string);
    my_string = (char*) aligned_alloc(alignment, size - size % alignment + 2 * alignment);
    memset(my_string, 0, size - size % alignment + 2 * alignment);
    strcpy(my_string, string);
}
#endif //HASH_TABLE_HASH_TABLE_H
