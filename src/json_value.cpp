#include <stdexcept>
#include "json_value.h"
#include "json_obj.h"

namespace json_parser {
    JsonValue::JsonValue() {
        this->data = nullptr;
    }

    JsonValue::JsonValue(int data) {
        this->data = data;
    }

    JsonValue::JsonValue(double data) {
        this->data = data;
    }

    JsonValue::JsonValue(unsigned int data) {
        this->data = data;
    }

    JsonValue::JsonValue(bool data) {
        this->data = data;
    }

    JsonValue::JsonValue(JsonObj&& data) {
        this->data = std::make_unique<JsonObj>(std::move(data));
    }

    JsonValue::JsonValue(std::string&& data) {
        this->data = std::make_unique<std::string>(std::move(data));
    }

    JsonValue::JsonValue(std::vector<JsonValue>&& data) {
        this->data = std::make_unique<std::vector<JsonValue>>(std::move(data));
    }

    // Move constructor 
    JsonValue::JsonValue(JsonValue&& other) noexcept {
        data = std::move(other.data);
    }

    // Destructor 
    JsonValue::~JsonValue() = default;

    JsonValue::DataType JsonValue::get_type() const {
        size_t type = this->data.index();
        return static_cast<JsonValue::DataType>(type);
    }
}
