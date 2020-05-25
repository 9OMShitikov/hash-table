
#include <iostream>
#include "hash_table_without_optimizations.h"
#include "../../data-read/data-read.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST (HashTable, StressTest) {
    size_t loops_cnt = 4;
    char* data = NULL;
    char** strings = NULL;

    size_t size = read_data(&data, "data");
    size_t string_cnt = parse_data(&strings, &data, size);
    HashtableWithoutOptimizations<uint> table;
    for (int i = 0; i < string_cnt; ++i) {
        table.add(strings[i], i);
    }

    for (int j = 0; j < loops_cnt; ++j) {
        for (int i = 0; i < string_cnt; ++i) {
            auto it = table.find(strings[i]);
            it.set_value(i + j);
        }
        for (int i = 0; i < string_cnt; ++i) {
            auto it = table.find(strings[i]);
            ASSERT_FALSE(it.is_empty());
            ASSERT_EQ(it.get_value(), i + j);
        }
    }
    free(data);
    free(strings);
}
