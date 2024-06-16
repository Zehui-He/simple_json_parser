#pragma once
#include <variant>
#include <stdexcept>
#include "json_fwd.h"

namespace json_parser {
    class JsonValue {
    public:
        using Data = std::variant<
            int,
            double,
            unsigned int,
            bool,
            std::string,
            std::unique_ptr<Json>, 
            JsonArray,
            std::nullptr_t
        >;

        JsonValue() noexcept;

        JsonValue(int i) noexcept;

        JsonValue(double d) noexcept;

        JsonValue(unsigned int u) noexcept;

        JsonValue(bool b) noexcept;

        JsonValue(std::nullptr_t n) noexcept;

        template <typename T, typename Enable = std::enable_if_t<std::is_convertible_v<T, std::string>>>
        JsonValue(T&& str) noexcept : m_value(std::string(std::forward<T>(str))) {}

        JsonValue(std::vector<JsonValue>&& v) noexcept;

        JsonValue(Json&& json) noexcept;

        // Move constructor
        JsonValue(JsonValue&& other) noexcept;

        // Move assignment
        JsonValue& operator=(JsonValue&& other) noexcept;

        // Copy constructor
        JsonValue(JsonValue const& other);

        // Copy assignment operator
        JsonValue& operator=(const JsonValue& other);

        // Get the type of value that the JsonValue currently holds
        JsonValueType get_type() const;

        // Get the underlying value of the JsonValue.
        // Return a reference of the value.
        template <typename T, typename Enable = std::enable_if_t<is_json_impl_type_v<T>, void>>
        T& get() {
            return std::get<T>(m_value);
        }

        template <JsonValueType T, typename Enable = std::enable_if_t<is_json_value_type_v<T>, void>>
        data_impl_mapping_t<T>& get() {
            return std::get<data_impl_mapping_t<T>>(m_value);
        }

        // Read the underlying value of the JsonValue.
        // Return a const reference of the value.
        template <typename T, typename Enable = std::enable_if_t<is_json_impl_type_v<T>, void>>
        T const& read() const {
            return std::get<T>(m_value);
        }

        template <JsonValueType T, typename Enable = std::enable_if_t<is_json_value_type_v<T>, void>>
        data_impl_mapping_t<T> const& read() const {
            return std::get<data_impl_mapping_t<T>>(m_value);
        }

    friend std::ostream& operator<<(std::ostream& os, const JsonValue& jsonvalue);

    private:
        Data m_value;

        void copy_helper(JsonValue& t, JsonValue const& other);
        void print_vec_helper(std::ostream& os) const noexcept; 
        void print_string_helper(std::ostream& os) const noexcept; 
    }; // strcut json_value 
} // namespace json_parser
