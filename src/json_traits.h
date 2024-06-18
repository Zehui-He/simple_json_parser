#pragma once 
#include "json_value_type.h"

namespace json_parser {

    // A type trait which check if a given type is json implementation type 
    template <typename T>
    struct is_json_impl_type : std::false_type {};

    template <typename T>
    inline constexpr bool is_json_impl_type_v = is_json_impl_type<T>::value;

    // A type trait which maps from json value type to its implementation type 
    template <JsonValueType T>
    struct data_impl_mapping {};

    template <JsonValueType T>
    using data_impl_mapping_t = typename data_impl_mapping<T>::type;

    // A type trait which check if a type(size_t) is a json value type 
    template <JsonValueType T>
    struct is_json_value_type : std::false_type {};

    template <JsonValueType T>
    inline constexpr bool is_json_value_type_v = is_json_value_type<T>::value;

} // namspace json_parser 
