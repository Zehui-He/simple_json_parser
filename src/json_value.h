#include <string>
#include <unordered_map>
#include <memory>

#pragma once 

class JsonValue;
using JsonObj = std::unordered_map<std::string, JsonValue>;

class JsonValue {
public:
    union Data {
        int i;
        double d;
        std::unique_ptr<JsonObj> j;
        std::unique_ptr<std::string> s;

        Data() {};
        ~Data() {};
        // Data is not copyable 
        Data(Data&) = delete;
    } data;

    enum DataType {
        INT,
        DOUBLE,
        JSON,
        STRING
    } type;

    // JsonValue is not copyable 
    JsonValue(JsonValue&) = delete;

    // Move constructor for JsonValue
    JsonValue(JsonValue&& other) noexcept : type(other.type) {
        switch (type) {
            case INT:
                data.i = other.data.i;
                break;
            case DOUBLE:
                data.d = other.data.d;
                break;
            case JSON:
                data.j = std::move(other.data.j);
                break;
            case STRING:
                data.s = std::move(other.data.s);
                break;
        }
    }

    JsonValue(int data) : type(INT) {
        this->data.i = data;
    }

    JsonValue(double data) {
        this->data.d = data;
        type = DOUBLE;
    }

    JsonValue(JsonObj&& data) {
        this->data.j = std::make_unique<JsonObj>(std::move(data));
        type = JSON;
    }

    JsonValue(std::string&& data) {
        this->data.s = std::make_unique<std::string>(std::move(data));
        type = STRING;
    }
};
