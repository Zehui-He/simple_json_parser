#include <iostream>
#include <variant>
#include "json_obj.h"

namespace json_parser {
    JsonObj::Iterator JsonObj::begin() {
        return data_.begin();
    }

    JsonObj::Iterator JsonObj::end() {
        return data_.end();
    }

    JsonObj::Const_iterator JsonObj::begin() const {
        return data_.begin();
    }

    JsonObj::Const_iterator JsonObj::end() const {
        return data_.end();
    }

    void JsonObj::show() const {
        for (auto it = data_.begin(); it != data_.end(); ++it) {
            switch (it->second.type)
            {
            case JsonValue::JSON:
                std::cout << it->first << ": \n";
                it->second.read<std::unique_ptr<JsonObj>>()->show();
                break;
            case JsonValue::STRING:
                std::cout << it->first << ": ";
                std::cout << *it->second.read<std::unique_ptr<std::string>>();
                break;
            case JsonValue::DOUBLE:
                std::cout << it->first << ": ";
                std::cout << it->second.read<double>();
                break;
            case JsonValue::INT:
                std::cout << it->first << ": ";
                std::cout << it->second.read<int>();
                break;
            }
            std::cout << std::endl;
        }
    }

    bool JsonObj::empty() const {
        return data_.empty();
    }
}
