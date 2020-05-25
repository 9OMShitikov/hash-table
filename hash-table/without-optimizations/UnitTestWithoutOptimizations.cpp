#include <iostream>
#include "hash_table_without_optimizations.h"
#include "../../data-read/data-read.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST (HashTable, AddValue) {
    HashtableWithoutOptimizations<uint> table;

    ASSERT_TRUE(table.find("test").is_empty());
    table.add("test", 265);

    auto it = table.find("test");
    ASSERT_FALSE(it.is_empty());
    ASSERT_EQ(it.get_value(), 265);
}

TEST (HashTable, Set) {
    HashtableWithoutOptimizations<uint> table;

    ASSERT_TRUE(table.find("test").is_empty());
    table.add("test", 2);
    auto it = table.find("test");
    ASSERT_FALSE(it.is_empty());
    ASSERT_EQ(it.get_value(), 2);

    it.set_value(265);
    it = table.find("test");
    ASSERT_FALSE(it.is_empty());
    ASSERT_EQ(it.get_value(), 265);

}

TEST (HashTable, Erase) {
    HashtableWithoutOptimizations<uint> table;

    ASSERT_TRUE(table.find("test").is_empty());
    table.add("test", 265);

    auto it = table.find("test");
    ASSERT_FALSE(it.is_empty());
    ASSERT_EQ(it.get_value(), 265);

    table.erase(it);
    ASSERT_TRUE(table.find("test").is_empty());
}



