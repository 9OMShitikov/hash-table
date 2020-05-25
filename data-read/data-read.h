
#ifndef HASH_TABLE_DATA_READ_H
#define HASH_TABLE_DATA_READ_H
#include <iostream>
#include <string_view>
#include <assert.h>
#include <cstring>
#include <cstdio>
#include <iostream>

#define MY_ASSERT(expr) if (!(expr)) throw std::exception()

size_t read_data (char **buff, const char* input_name);

size_t parse_data(char ***strings, char **buff, size_t buff_size);
#endif //HASH_TABLE_DATA_READ_H
