#pragma once

#include <unordered_map>
#include <string>
#include "json_value.h"

class JsonObj {
private:
    std::unordered_map<std::string, JsonValue> data_;
public:
    using Iterator = std::unordered_map<std::string, JsonValue>::iterator;
    JsonObj() = default;
    ~JsonObj() = default;
    // Allow copy and move 
    JsonObj(JsonObj&) = default;
    JsonObj(JsonObj&&) = default;
    JsonObj& operator=(JsonObj&) = default;
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
};
