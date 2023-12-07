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

    // A trait that maps the JSON value type and the implementation type 
    template <JsonValueType V>
    struct json_value_impl_mapping;

    template <>
    struct json_value_impl_mapping<int_t> {
        using type = int;
    };

    template <>
    struct json_value_impl_mapping<double_t> {
        using type = double;
    };
    
    template <>
    struct json_value_impl_mapping<unsigned_int_t> {
        using type = unsigned int;
    };

    template <>
    struct json_value_impl_mapping<bool_t> {
        using type = bool;
    };

    template <>
    struct json_value_impl_mapping<string_t> {
        using type = std::unique_ptr<std::string>;
    };

    template <>
    struct json_value_impl_mapping<array_t> {
        using type = std::unique_ptr<std::vector<Json>>;
    };

    template <>
    struct json_value_impl_mapping<object_t> {
        using type = std::unique_ptr<std::unordered_map<std::string, Json>>;
    };

    template <>
    struct json_value_impl_mapping<null_t> {
        using type = std::nullptr_t;
    };
}
