#pragma once

#include <unordered_map>
#include <string>
#include "json_value.h"

namespace json_parser {
    class JsonObj {
    private:
        std::unordered_map<std::string, JsonValue> data_;
    public:
        using Iterator = std::unordered_map<std::string, JsonValue>::iterator;
        using Const_iterator = std::unordered_map<std::string, JsonValue>::const_iterator;
        JsonObj() = default;
        ~JsonObj() = default;
        // Json is not copyable but movable 
        JsonObj(JsonObj&) = delete;
        JsonObj(JsonObj&&) = default;
        JsonObj& operator=(JsonObj&) = delete;
        JsonObj& operator=(JsonObj&&) = default;

        // This would allow the key constructed with whatever type that can be converted to std::string
        template <typename K>
        std::pair<Iterator, bool> emplace(K&& key, JsonValue&& value) {
            return data_.emplace(std::forward<K>(key), std::move(value));
        }

        // Print the content of the JsonObj
        void show() const;

        Iterator begin();
        Iterator end();
        Const_iterator begin() const;
        Const_iterator end() const;
        // Check if the JsonObj is empty 
        bool empty() const;
        // Access the value with the key 
        template <typename K>
        JsonValue& operator[](K&& key) {
            return data_.at(std::forward<K>(key));
        }
        
        template <typename K>
        const JsonValue& operator[](K&& key) const {
            return data_.at(std::forward<K>(key));
        }
    };
}
