#include "json.h"

namespace json_parser {

    // A type trait which check if a given type is json implementation type 
    template <typename T>
    struct is_json_impl_type {
        static const bool value = false;
    };

    template <typename T>
    inline constexpr bool is_json_impl_type_v = is_json_impl_type<T>::value;

    template <>
    struct is_json_impl_type<int> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<double> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<unsigned int> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<bool> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<std::unique_ptr<std::string>> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<Json::JsonObjectPtr> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<Json::JsonArrayPtr> {
        static const bool value = true;
    };

} // namspace json_parser 
