cmake_minimum_required(VERSION 3.16)
project(hash_table)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
enable_language(ASM)

add_subdirectory(googletest-master)
include_directories(hash-table)
include_directories(googletest-master/googletest/include)
include_directories(googletest-master/googlemock/include)

add_executable(hash_table main.cpp
               hash-table/hash_table.h hash-table/hash_table.cpp
               hash-table/without-optimizations/hash_table_without_optimizations.cpp
               hash-table/without-optimizations/hash_table_without_optimizations.h
               data-read/data-read.h data-read/data-read.cpp
               hash-table/without-optimizations/UnitTestWithoutOptimizations.cpp
               hash-table/without-optimizations/StressTestWithoutOptimizations.cpp)

target_link_libraries(hash_table gtest gtest_main)

add_executable(hash_table_with_optimizations main.cpp
        hash-table/hash_table.h hash-table/hash_table.cpp
        data-read/data-read.h data-read/data-read.cpp
        hash-table/with-optimizations/hash_table_with_optimizations.cpp
        hash-table/with-optimizations/hash_table_with_optimizations.h
        hash-table/with-optimizations/UnitTestWithOptimizations.cpp
        hash-table/with-optimizations/StressTestWithOptimizations.cpp
        hash-table/with-optimizations/funcs.S)

target_link_libraries(hash_table_with_optimizations gtest gtest_main)