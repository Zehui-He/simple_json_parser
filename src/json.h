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
        using JsonObjectPtr = std::unique_ptr<JsonObject>;
        using JsonArrayPtr = std::unique_ptr<JsonArray>;
        // using JsonObjectIterator = JsonObject::iterator;
        // using JsonObjectIterator_const = JsonObject::const_iterator;

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

        // Construct json with given value type 
        Json(JsonValueType);

        // Json is not copyable 
        Json& operator=(Json&) = delete;
        Json(Json&) = delete;

        // Json is movable 
        Json(Json&& other) noexcept;

        // Return the data type currently held by the Json object 
        JsonValueType get_type() const;

        friend std::ostream& operator<<(std::ostream& os, const Json& json);

        // [] operator can only be used on objects 
        // If a key does not exist in the json object, a new key-value pair is inserted where the key equals to parameter 'key' and the value is null 
        template <typename K>
        Json& operator[](K&& key) {
            if (this->get_type() != JsonValueType::object_t) {
                throw std::runtime_error("[] operator can only be used on objects.");
            }
            return (*std::get<std::unique_ptr<JsonObject>>(m_data))[std::forward<K>(key)];
        }

        // const version of operator[] 
        template <typename K>
        Json const& operator[](K&& key) const {
            if (this->get_type() != JsonValueType::object_t) {
                throw std::runtime_error("[] operator can only be used on objects.");
            }
            return (*std::get<std::unique_ptr<JsonObject>>(m_data))[std::forward<K>(key)];
        }

        // Insert a key value pair into the json value in place 
        template <typename K>
        void emplace(K&& key, Json&& value) {
            std::get<JsonObjectPtr>(m_data)->emplace(std::forward<K>(key), std::move(value));
        }

        // Get the value helded by the json 
        template <typename V> 
        V& get() {
            return std::get<V>(m_data);
        }

        template <typename V>
        V const& read() const {
            return std::get<V>(m_data);
        }

        template <JsonValueType T>
        auto& get_by_type() {
            using V = typename json_parser::JsonValueReturnType<T>::type;
            return std::get<V>(m_data);
        }

        template <JsonValueType T>
        auto const& get_by_type() const {
            using V = typename json_parser::JsonValueReturnType<T>::type;
            return std::get<V>(m_data);
        }

        // Deconstructor 
        ~Json() = default;

    private:
        JsonValue m_data; 
        std::ostream& outputObject(std::ostream& os) const;
        std::ostream& outputArray(std::ostream& os) const;
    };
}
