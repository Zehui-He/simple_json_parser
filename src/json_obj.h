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

    void emplace(std::string&& key, JsonValue&& value);

    Iterator begin();
    Iterator end();
};
