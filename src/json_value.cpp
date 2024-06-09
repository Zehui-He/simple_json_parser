#include <stdexcept>
#include "json_value.h"

namespace json_parser {
    // The default constructor will return a JsonValue object with null value 
    JsonValue::JsonValue() {
        this->data = nullptr;
    }

    JsonValue::JsonValue(int i) {
        this->data = i;
    }

    JsonValue::JsonValue(double d) {
        this->data = d;
    }

    JsonValue::JsonValue(unsigned int i) {
        this->data = i;
    }

    JsonValue::JsonValue(bool b) {
        this->data = b;
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

    std::ostream& operator<<(std::ostream& os, const JsonValue& jsonvalue) {
        switch (jsonvalue.get_type()) {
            case JsonValue::OBJECT:
                os << "Object";
                break;
            case JsonValue::STRING:
                os << *jsonvalue.read<std::unique_ptr<std::string>>();
                break;
            case JsonValue::DOUBLE:
                os << jsonvalue.read<double>();
                break;
            case JsonValue::INT:
                os << jsonvalue.read<int>();
                break;
            case JsonValue::UNSIGNED_INT:
                os << jsonvalue.read<unsigned int>();
                break;
            case JsonValue::ARRAY:
                os << "Array";
                break;
            case JsonValue::BOOL:
                if (jsonvalue.read<bool>()) {
                    os << "true";
                } else {
                    os << "false";
                }
                break;
            default:
                throw std::runtime_error("Show function of this type is not implemented.");
        }
        return os;
    }

}
