#include <iostream>
#include <variant>
#include <vector>
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

    void printJsonVec(JsonValue const& item, int depth) {
        if (item.type != JsonValue::VEC) {
            throw std::runtime_error("Should not call this function with JsonValue.type != VEC");
        }
        auto const& vec = std::get<std::unique_ptr<std::vector<JsonValue>>>(item.data);
        for (int i = 0; i < vec->size(); i++) {
            switch (vec->at(i).type) {
            case JsonValue::JSON:
                vec->at(i).read<std::unique_ptr<JsonObj>>()->show_with_depth(depth);
                break;
            case JsonValue::STRING:
                std::cout << "\"" << *vec->at(i).read<std::unique_ptr<std::string>>() << "\"";
                break;
            case JsonValue::DOUBLE:
                std::cout << vec->at(i).read<double>();
                break;
            case JsonValue::INT:
                std::cout << vec->at(i).read<int>();
                break;
            case JsonValue::VEC:
                std::cout << "[";
                printJsonVec(vec->at(i), depth);
                std::cout << "]";
                break;
            }
            if (i == vec->size() - 1) {
                continue;
            }
            std::cout << " , ";
        }
    }

    void JsonObj::show_with_depth(int depth) const {
        for (auto it = data_.begin(); it != data_.end(); ++it) {
            for (int i = 0; i < depth; i++) {
                std::cout << "\t";
            }
            switch (it->second.type)
            {
            case JsonValue::JSON:
                std::cout << it->first << ": \n";
                it->second.read<std::unique_ptr<JsonObj>>()->show_with_depth(depth + 1);
                break;
            case JsonValue::STRING:
                std::cout << it->first << ": \"";
                std::cout << *it->second.read<std::unique_ptr<std::string>>();
                std::cout << "\"";
                break;
            case JsonValue::DOUBLE:
                std::cout << it->first << ": ";
                std::cout << it->second.read<double>();
                break;
            case JsonValue::INT:
                std::cout << it->first << ": ";
                std::cout << it->second.read<int>();
                break;
            case JsonValue::VEC:
                std::cout << it->first << ": ";
                std::cout << "[";
                printJsonVec(it->second, depth);
                std::cout << "]";
                break;
            }
            std::cout << std::endl;
        }
    }

    void JsonObj::show() const {
        show_with_depth(0);
    }

    bool JsonObj::empty() const {
        return data_.empty();
    }
}
