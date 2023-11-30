#pragma once 
#include <variant>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "json_types.h"

namespace json_parser {
    class Json {
    public:
        using JsonObject = std::unordered_map<std::string, Json>;
        using JsonArray = std::vector<Json>;

        using JsonValue = std::variant<
            int, 
            double,
            unsigned int, 
            bool,
            std::unique_ptr<std::string>,
            std::unique_ptr<JsonArray>,
            std::unique_ptr<JsonObject>,
            std::nullptr_t
        >; 

        // By default, the json object holds a null value 
        Json();

        // Construct with given value 
        Json(int data);
        Json(double data);
        Json(unsigned int data);
        Json(bool data);
        Json(std::string&& data);
        Json(JsonArray&& data);
        Json(JsonObject&& data);

        // Json is not copyable 
        Json& operator=(Json&) = delete;
        Json(Json&) = delete;

        // Json is movable 
        Json(Json&& other) noexcept;

        // Return the data type currently held by the Json object 
        JsonValueType get_type() const;

        friend std::ostream& operator<<(std::ostream& os, const Json& json);

        // [] operator can only be used on objects 
        template <typename K>
        JsonValue& operator[](K&& key) {
            if (this->get_type() != JsonValueType::object_t) {
                throw std::runtime_error("[] operator can only be used on objects.");
            }
            return (*std::get<std::unique_ptr<JsonObject>>(m_data))[std::forward<K>(key)];
        }

        // const version of operator[] 
        template <typename K>
        JsonValue const& operator[](K&& key) const {
            if (this->get_type() != JsonValueType::object_t) {
                throw std::runtime_error("[] operator can only be used on objects.");
            }
            return (*std::get<std::unique_ptr<JsonObject>>(m_data))[std::forward<K>(key)];
        }

        // Deconstructor 
        ~Json() = default;

    private:
        JsonValue m_data; 
    };
}
