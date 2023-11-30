#pragma once 
#include <cstddef>

enum JsonValueType : size_t {
    int_t,
    double_t,
    unsigned_int_t,
    bool_t,
    string_t,
    array_t,
    object_t,
    null_t,
};
