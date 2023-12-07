#pragma once 

namespace json_parser {

    // A type trait which check if a given type is json implementation type 
    template <typename T>
    struct is_json_impl_type {
        static const bool value = false;
    };

    template <typename T>
    inline constexpr bool is_json_impl_type_v = is_json_impl_type<T>::value;

} // namspace json_parser 
