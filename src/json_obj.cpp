#include <iostream>
#include <variant>
#include <vector>
#include <exception>
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
        if (item.get_type() != JsonValue::ARRAY) {
            throw std::runtime_error("Should not call this function with JsonValue.type != ARRAY");
        }
        auto const& vec = std::get<std::unique_ptr<std::vector<JsonValue>>>(item.data);
        for (int i = 0; i < vec->size(); i++) {
            switch (vec->at(i).get_type()) {
            case JsonValue::OBJECT:
                std::cout << "{\n";
                vec->at(i).read<std::unique_ptr<JsonObj>>()->showWithDepth(depth + 1);
                for (int i = 0; i < depth; i++) {
                    std::cout << "\t";
                }
                std::cout << "}";
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
            case JsonValue::UNSIGNED_INT:
                std::cout << vec->at(i).read<unsigned int>();
                break;
            case JsonValue::ARRAY:
                std::cout << "[";
                printJsonVec(vec->at(i), depth);
                std::cout << "]";
                break;
            case JsonValue::BOOL:
                if (vec->at(i).read<bool>()) {
                    std::cout << "true";
                } else {
                    std::cout << "false";
                }
                break;
            default:
                throw std::runtime_error("Show function of this type is not implemented.");
            }
            if (i == vec->size() - 1) {
                continue;
            }
            std::cout << " , ";
        }
    }

    void JsonObj::showWithDepth(int depth) const {
        for (auto it = data_.begin(); it != data_.end(); ++it) {
            for (int i = 0; i < depth; i++) {
                std::cout << "\t";
            }
            switch (it->second.get_type())
            {
            case JsonValue::OBJECT:
                std::cout << it->first << ": \n";
                it->second.read<std::unique_ptr<JsonObj>>()->showWithDepth(depth + 1);
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
            case JsonValue::UNSIGNED_INT:
                std::cout << it->first << ": ";
                std::cout << it->second.read<unsigned int>();
                break;
            case JsonValue::ARRAY:
                std::cout << it->first << ": ";
                std::cout << "[";
                printJsonVec(it->second, depth);
                std::cout << "]";
                break;
            case JsonValue::null:
                std::cout << it->first << ": ";
                std::cout << "null";
                break;
            case JsonValue::BOOL:
                std::cout << it->first << ": ";
                if (it->second.read<bool>()) {
                    std::cout << "true";
                } else {
                    std::cout << "false";
                }
                break;
            default:
                throw std::runtime_error("Show function of this type is not implemented.");
            }
            std::cout << std::endl;
        }
    }

    void JsonObj::show() const {
        showWithDepth(0);
    }

    bool JsonObj::empty() const {
        return data_.empty();
    }
}
