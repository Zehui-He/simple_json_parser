#include <stdexcept>
#include "json_value.h"
#include "json_obj.h"

namespace json_parser {
    JsonValue::JsonValue(int data) : type(INT) {
        this->data = data;
    }

    JsonValue::JsonValue(double data) {
        this->data = data;
        type = DOUBLE;
    }

    JsonValue::JsonValue(JsonObj&& data) {
        this->data = std::make_unique<JsonObj>(std::move(data));
        type = JSON;
    }

    JsonValue::JsonValue(std::string&& data) {
        this->data = std::make_unique<std::string>(std::move(data));
        type = STRING;
    }

    // Move constructor 
    JsonValue::JsonValue(JsonValue&& other) noexcept : type(other.type) {
        data = std::move(other.data);
        switch (type) {
            case INT:
                other.data = -1;
                break;
            case DOUBLE:
                other.data = -1;
                break;
            case JSON:
                other.data = std::unique_ptr<JsonObj>(); // Set the pointer as nullptr 
                break;
            case STRING:
                other.data = std::unique_ptr<JsonObj>();
                break;
            case NONE:
                throw std::runtime_error("Cannot move JsonValue::JsonValue of type NONE"); // Throw error when try to consturct an invalid object 
        }
        other.type = NONE;
    }

    // Destructor 
    JsonValue::~JsonValue() {
        switch (type) {
            case INT:
            case DOUBLE:
                break;
            case JSON:
                std::get<std::unique_ptr<JsonObj>>(data).reset();
                break;
            case STRING:
                std::get<std::unique_ptr<JsonObj>>(data).reset();
                break;
            case NONE:
                break;
            default:
                throw std::runtime_error("A new type of JsonValue::DataType is added but not handled in JsonValue::~JsonValue()");
                break;
        }
    }
}
