#pragma once 
#include <cstddef>

namespace json_parser {
    class Json;
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

    template <JsonValueType V>
    struct JsonValueReturnType;

    template <>
    struct JsonValueReturnType<int_t> {
        using type = int;
    };

    template <>
    struct JsonValueReturnType<double_t> {
        using type = double;
    };
    
    template <>
    struct JsonValueReturnType<unsigned_int_t> {
        using type = unsigned int;
    };

    template <>
    struct JsonValueReturnType<bool_t> {
        using type = bool;
    };

    template <>
    struct JsonValueReturnType<string_t> {
        using type = std::unique_ptr<std::string>;
    };

    template <>
    struct JsonValueReturnType<array_t> {
        using type = std::unique_ptr<std::vector<Json>>;
    };

    template <>
    struct JsonValueReturnType<object_t> {
        using type = std::unique_ptr<std::unordered_map<std::string, Json>>;
    };

    template <>
    struct JsonValueReturnType<null_t> {
        using type = std::nullptr_t;
    };
}
