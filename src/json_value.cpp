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

    JsonValue::JsonValue(std::vector<int>&& data) {
        this->data = std::make_unique<std::vector<int>>(std::move(data));
        type = INT_VEC;
    }

    JsonValue::JsonValue(std::vector<double>&& data) {
        this->data = std::make_unique<std::vector<double>>(std::move(data));
        type = DOUBLE_VEC;
    }

    JsonValue::JsonValue(std::vector<std::unique_ptr<std::string>>&& data) {
        this->data = std::make_unique<std::vector<std::unique_ptr<std::string>>>(std::move(data));
        type = DOUBLE_VEC;
    }

    JsonValue::JsonValue(std::vector<std::unique_ptr<JsonObj>>&& data) {
        this->data = std::make_unique<std::vector<std::unique_ptr<JsonObj>>>(std::move(data));
        type = DOUBLE_VEC;
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
                other.data = std::unique_ptr<std::string>();
                break;
            case INT_VEC:
                other.data = std::unique_ptr<std::vector<int>>();
            case DOUBLE_VEC:
                other.data = std::unique_ptr<std::vector<double>>();
            case STRING_VEC:
                other.data = std::unique_ptr<std::vector<std::unique_ptr<std::string>>>();
            case JSON_VEC:
                other.data = std::unique_ptr<std::vector<std::unique_ptr<JsonObj>>>();
            case NONE:
                throw std::runtime_error("Cannot move JsonValue::JsonValue of type NONE"); // Throw error when try to consturct an invalid object 
        }
        other.type = NONE;
    }

    // Destructor 
    JsonValue::~JsonValue() = default;
}
