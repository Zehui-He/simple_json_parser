#pragma once 

namespace json_parser {
    // Macro to generate specializations for data_impl_mapping
    #define DATA_IMPL_MAPPING(JsonValueType, ImplType) \
    template <> \
    struct data_impl_mapping<JsonValueType> { \
        using type = ImplType; \
    }

    // Macro to generate specializations for is_json_value_type
    #define IS_JSON_VALUE_TYPE(JsonValueType) \
    template <> \
    struct is_json_value_type<JsonValueType> : std::true_type {}

    // Macro to generate specializations for is_json_impl_type
    #define IS_JSON_IMPL_TYPE(ImplType) \
    template <> \
    struct is_json_impl_type<ImplType> : std::true_type {}

} //namespace json_parser
