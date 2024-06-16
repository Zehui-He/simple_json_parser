#pragma once
#include <memory>
#include <vector>
#include <string>
#include <json_value_type.h>
#include <json_traits.h>
#include <json_macro.h>

namespace json_parser {
    // Forward declaration of Json and JsonValue
    class Json;
    class JsonValue;

    // Define JsonArray
    using JsonArray = std::vector<JsonValue>;

    // Trait implementation 
    DATA_IMPL_MAPPING(JsonValueType::int_t, int);
    DATA_IMPL_MAPPING(JsonValueType::double_t, double);
    DATA_IMPL_MAPPING(JsonValueType::unsigned_int_t, unsigned int);
    DATA_IMPL_MAPPING(JsonValueType::bool_t, bool);
    DATA_IMPL_MAPPING(JsonValueType::string_t, std::string);
    DATA_IMPL_MAPPING(JsonValueType::array_t, JsonArray);
    DATA_IMPL_MAPPING(JsonValueType::object_t, std::unique_ptr<Json>);
    DATA_IMPL_MAPPING(JsonValueType::null_t, std::nullptr_t);

    IS_JSON_VALUE_TYPE(JsonValueType::int_t);
    IS_JSON_VALUE_TYPE(JsonValueType::double_t);
    IS_JSON_VALUE_TYPE(JsonValueType::unsigned_int_t);
    IS_JSON_VALUE_TYPE(JsonValueType::bool_t);
    IS_JSON_VALUE_TYPE(JsonValueType::string_t);
    IS_JSON_VALUE_TYPE(JsonValueType::array_t);
    IS_JSON_VALUE_TYPE(JsonValueType::object_t);
    IS_JSON_VALUE_TYPE(JsonValueType::null_t);

    IS_JSON_IMPL_TYPE(int);
    IS_JSON_IMPL_TYPE(double);
    IS_JSON_IMPL_TYPE(unsigned int);
    IS_JSON_IMPL_TYPE(bool);
    IS_JSON_IMPL_TYPE(std::string);
    IS_JSON_IMPL_TYPE(JsonArray);
    IS_JSON_IMPL_TYPE(std::unique_ptr<Json>);
    IS_JSON_IMPL_TYPE(std::nullptr_t);

} // namespace json_parser
