#pragma once 

#include <string>
#include <unordered_map>
#include <memory>
#include <variant>

class JsonObj;

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

    JsonValue(int data);
    JsonValue(double data);
    JsonValue(JsonObj&& data);
    JsonValue(std::string&& data);
    // Move constructor 
    JsonValue(JsonValue&& other) noexcept;
    // Destructor 
    ~JsonValue();
};
