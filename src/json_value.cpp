#include <stdexcept>
#include "json_value.h"
#include "json_obj.h"
#include "macros.h"

namespace json_parser {
    // The default constructor will return a JsonValue object with null value 
    JsonValue::JsonValue() {
        this->data = nullptr;
    }

    CONSTRUCT_WITH_DATA(int);

    CONSTRUCT_WITH_DATA(double);

    CONSTRUCT_WITH_DATA(unsigned int);

    CONSTRUCT_WITH_DATA(bool);

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
