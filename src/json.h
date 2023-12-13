#pragma once 
#include <variant>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "json_types.h"
#include "json_traits.h"

namespace json_parser {
    class Json {
    public:
        using JsonObject = std::unordered_map<std::string, Json>;
        using JsonArray = std::vector<Json>;
        using JsonObjectPtr = std::unique_ptr<JsonObject>;
        using JsonArrayPtr = std::unique_ptr<JsonArray>;

        // The data types stored in the varaint are called implementation types 
        // They are the true value type that stores the data 
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
        // The input type must be an implmentation type otherwise no such function is instantiated 
        template <typename V> 
        std::enable_if_t<is_json_impl_type_v<V>, V>& get() {
            return std::get<V>(m_data);
        }

        template <typename V>
        std::enable_if_t<is_json_impl_type_v<V>, V> const& read() const {
            return std::get<V>(m_data);
        }

        // Get the value helded by the json using json type 
        // The function would check if the given type is a json type at compile time 
        template <JsonValueType T>
        auto& get_by_type() {
            static_assert(is_json_value_type_v<T>, "This value is not a Json type.");
            using V = typename json_parser::json_value_impl_mapping_t<T>;
            return std::get<V>(m_data);
        }

        template <JsonValueType T>
        auto const& get_by_type() const {
            static_assert(is_json_value_type_v<T>, "This value is not a Json type.");
            using V = typename json_parser::json_value_impl_mapping_t<T>;
            return std::get<V>(m_data);
        }

        // Deconstructor 
        ~Json() = default;

    private:
        JsonValue m_data; 
        std::ostream& outputObject(std::ostream& os) const;
        std::ostream& outputArray(std::ostream& os) const;
    }; // Json class 

    // Implement the trait for implementation types 
    template <>
    struct is_json_impl_type<int> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<double> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<unsigned int> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<bool> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<std::unique_ptr<std::string>> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<Json::JsonObjectPtr> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<Json::JsonArrayPtr> {
        static const bool value = true;
    };

    template <>
    struct is_json_impl_type<std::nullptr_t> {
        static const bool value = true;
    };

} // namespace json_parser 
