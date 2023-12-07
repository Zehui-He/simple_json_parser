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

    template <JsonValueType V>
    using json_value_impl_mapping_t = typename json_value_impl_mapping<V>::type;

    // A trait that check if the value is a valid json type 
    template <JsonValueType V>
    struct is_json_value_type {
        static const bool value = false;
    };

    template <JsonValueType V>
    inline constexpr bool is_json_value_type_v = is_json_value_type<V>::value;

    ///////////////////////////////////////////////////////////////////
    //             Implementation of the above traits                //
    ///////////////////////////////////////////////////////////////////

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

    template <>
    struct is_json_value_type<int_t> {
        static const bool value = true;
    };

    template <>
    struct is_json_value_type<double_t> {
        static const bool value = true;
    };

    template <>
    struct is_json_value_type<unsigned_int_t> {
        static const bool value = true;
    };

    template <>
    struct is_json_value_type<bool_t> {
        static const bool value = true;
    };

    template <>
    struct is_json_value_type<array_t> {
        static const bool value = true;
    };

    template <>
    struct is_json_value_type<string_t> {
        static const bool value = true;
    };

    template <>
    struct is_json_value_type<object_t> {
        static const bool value = true;
    };

    template <>
    struct is_json_value_type<null_t> {
        static const bool value = true;
    };

} // namespace json_parser
