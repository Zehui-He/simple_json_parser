#include <json.h>
#include <iostream>

namespace json_parser {
    Json::Json(){
        m_value = std::unordered_map<std::string, JsonValue>();
    };

    std::ostream& operator<<(std::ostream& os, const Json& json) {
        auto it_begin = json.m_value.cbegin();
        auto it_end = json.m_value.cend();
        os << '{';
        while (it_begin != it_end) {
            os << it_begin->first << ':' << it_begin->second;
            it_begin++;
            if (it_begin != it_end) {
                os << ',';
            }
        }
        os << '}';
        return os;
    }
} // namespace json_parser
