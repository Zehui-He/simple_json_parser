#pragma once
#include <cstddef>

namespace json_parser {
    // The possible data type that can be held by Json 
    // It should be noted that these types are not the implementaion type 
    enum JsonValueType : size_t {
        int_t,
        double_t,
        unsigned_int_t,
        bool_t,
        string_t,
        object_t,
        array_t,
        null_t,
    };
} // namespace json_parser
