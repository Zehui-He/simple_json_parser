#pragma once 

#include <string>
#include <unordered_map>
#include <memory>
#include <variant>


class JsonValue;
using JsonObj = std::unordered_map<std::string, JsonValue>;

class JsonValue {
public:
    using Data = std::variant<int, double, std::unique_ptr<JsonObj>, std::unique_ptr<std::string>>;

    Data data;
    enum DataType {
        INT,
        DOUBLE,
        JSON,
        STRING,
        NONE
    } type;

    // JsonValue is not copyable 
    JsonValue(JsonValue&) = delete;
    JsonValue& operator=(JsonValue&) = delete;

    JsonValue(int data) : type(INT) {
        this->data = data;
    }

    JsonValue(double data) {
        this->data = data;
        type = DOUBLE;
    }

    JsonValue(JsonObj&& data) {
        this->data = std::make_unique<JsonObj>(std::move(data));
        type = JSON;
    }

    JsonValue(std::string&& data) {
        this->data = std::make_unique<std::string>(std::move(data));
        type = STRING;
    }

    // Move constructor 
    JsonValue(JsonValue&& other) noexcept : type(other.type) {
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
        }
        other.type = NONE;
    }

    // Destructor 
    ~JsonValue() {
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
        }
    }
};
