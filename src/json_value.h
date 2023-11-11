#pragma once 

#include <string>
#include <unordered_map>
#include <memory>
#include <variant>
#include <vector>

namespace json_parser {
    class JsonObj;

    class JsonValue {
    public:
        using Data = std::variant<
            int,
            double, 
            std::unique_ptr<JsonObj>, 
            std::unique_ptr<std::string>, 
            std::unique_ptr<std::vector<JsonValue>>
        >;

        Data data;
        enum DataType {
            INT,
            DOUBLE,
            JSON,
            STRING,
            VEC,
            NONE
        } type;

        // JsonValue is not copyable 
        JsonValue(JsonValue&) = delete;
        JsonValue& operator=(JsonValue&) = delete;

        JsonValue(int data);
        JsonValue(double data);
        JsonValue(JsonObj&& data);
        JsonValue(std::string&& data);
        JsonValue(std::vector<JsonValue>&& data);
        // Move constructor 
        JsonValue(JsonValue&& other) noexcept;
        // Destructor 
        ~JsonValue();
        // Give a const reference of the data 
        template <typename T>
        const T& read() const {
            return std::get<T>(data);
        }
        // Give a reference of the data 
        template <typename T>
        T& get() {
            return std::get<T>(data);
        }
    };
}
