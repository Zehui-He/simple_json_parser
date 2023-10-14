#include "json_obj.h"

JsonObj::Iterator JsonObj::begin() {
    return data_.begin();
}

JsonObj::Iterator JsonObj::end() {
    return data_.end();
}

void JsonObj::emplace(std::string&& key, JsonValue&& value) {
    data_.emplace(std::move(key), std::move(value));
}
