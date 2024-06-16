#include <stdexcept>
#include <iostream>
#include "json_value.h"
#include "json.h"

namespace json_parser {
    JsonValue::JsonValue() noexcept : m_value(nullptr) {};

    JsonValue::JsonValue(int i) noexcept : m_value(i) {};

    JsonValue::JsonValue(double d) noexcept : m_value(d) {};

    JsonValue::JsonValue(unsigned int u) noexcept : m_value(u) {};

    JsonValue::JsonValue(bool b) noexcept : m_value(b) {};

    JsonValue::JsonValue(std::nullptr_t n) noexcept : m_value(n) {};

    JsonValue::JsonValue(std::vector<JsonValue>&& v) noexcept : m_value(std::move(v)) {};

    JsonValue::JsonValue(Json&& json) noexcept : m_value(std::make_unique<Json>(std::move(json))) {};

    // Move constructor 
    JsonValue::JsonValue(JsonValue&& other) noexcept : m_value(std::move(other.m_value)) {
        other.m_value = nullptr;
    }

    // Move assignment 
    JsonValue& JsonValue::operator=(JsonValue&& other) noexcept {
        this->m_value = std::move(other.m_value);
        other.m_value = nullptr;
        return *this;
    }

    // Copy constructor
    JsonValue::JsonValue(JsonValue const& other) {
        copy_helper(*this, other);
    }

    // Copy assignment operator
    JsonValue& JsonValue::operator=(const JsonValue& other) {
        copy_helper(*this, other);
        return *this;
    }

    // Get the type of value that the JsonValue currently holds 
    JsonValueType JsonValue::get_type() const {
        return static_cast<JsonValueType>(this->m_value.index());
    }

    void JsonValue::copy_helper(JsonValue& t, JsonValue const& other) {
        switch (other.get_type()) {
            case JsonValueType::int_t:
                t.m_value = std::get<int>(other.m_value);
                break;
            case JsonValueType::double_t:
                t.m_value = std::get<double>(other.m_value);
                break;
            case JsonValueType::unsigned_int_t:
                t.m_value = std::get<unsigned int>(other.m_value);
                break;
            case JsonValueType::bool_t:
                t.m_value = std::get<bool>(other.m_value);
                break;
            case JsonValueType::string_t:
                t.m_value = std::get<std::string>(other.m_value);
                break;
            case JsonValueType::array_t:
                t.m_value = std::get<JsonArray>(other.m_value);
                break;
            case JsonValueType::object_t:
                t.m_value = std::make_unique<Json>(*std::get<std::unique_ptr<Json>>(other.m_value));
                break;
            case JsonValueType::null_t:
                t.m_value = nullptr;
                break;
            default:
                throw std::runtime_error("No implementation for this type.");
        }
    }

    std::ostream& operator<<(std::ostream& os, const JsonValue& jsonvalue) {
        switch (jsonvalue.get_type()) {
            case JsonValueType::object_t:
                os << *jsonvalue.read<object_t>();
                break;
            case JsonValueType::string_t:
                jsonvalue.print_string_helper(os);
                break;
            case JsonValueType::double_t:
                os << jsonvalue.read<double_t>();
                break;
            case JsonValueType::int_t:
                os << jsonvalue.read<int_t>();
                break;
            case JsonValueType::unsigned_int_t:
                os << jsonvalue.read<unsigned_int_t>();
                break;
            case JsonValueType::array_t:
                jsonvalue.print_vec_helper(os);
                break;
            case JsonValueType::bool_t:
                if (jsonvalue.read<bool_t>()) {
                    os << "true";
                } else {
                    os << "false";
                }
                break;
            case JsonValueType::null_t:
                os << "null";
                break;
            default:
                throw std::runtime_error("Show function of this type is not implemented.");
        }
        return os;
    }

    void JsonValue::print_vec_helper(std::ostream& os) const noexcept {
        auto value_ref = this->read<JsonValueType::array_t>();
        auto v_begin = value_ref.cbegin();
        auto v_end = value_ref.cend();
        os << '[';
        while (v_begin != v_end) {
            os << *v_begin;
            v_begin++;
            if (v_begin != v_end) {
                os << ',';
            }
        }
        os << ']';
    }

    void JsonValue::print_string_helper(std::ostream& os) const noexcept {
        auto value_ref = this->read<JsonValueType::string_t>();
        os << '\"';
        os << value_ref;
        os << '\"';
    }
} // namespace json_parser
