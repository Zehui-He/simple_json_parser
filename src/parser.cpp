#include <iostream>
#include "parser.h"

namespace json_parser {
    std::string extractContnet(std::string json_name) {
        std::string content;
        unsigned int quotation_count = 0;

        std::ifstream json_file(json_name);
        if (!json_file.is_open()) {
            std::cout << "The file does not exist.\n";
            return content;
        }

        // Remove any tab, space, end of line that is not enclosed by quotation mark 
        while (1) {
            char c = json_file.get();
            if (c == static_cast<char>(-1)) {
                break;
            }

            switch (c)
            {
            case '"':
                if (quotation_count == 0) {
                    quotation_count++;
                } else {
                    quotation_count--;
                }
                content += c;
                break;
            case '\n':
                if (quotation_count == 0) {
                    break;
                }
            case ' ':
                if (quotation_count == 0) {
                    break;
                }
            case '\t':
                if (quotation_count == 0) {
                    break;
                }
            default:
                content += c;
                break;
            }
        }

        json_file.close();
        return content;
    }

    JsonObj parseIntoJson(std::string& content) {
        auto it_begin = content.begin();
        auto it_end = content.end();
        JsonObj res = iterIntoJson(it_begin,it_end);
        return res;
    }

    // Note: this is a super naive but recursive approach. 
    JsonObj iterIntoJson(std::string::iterator& it_begin, std::string::iterator& it_end) {
        int is_sub_json = false;
        int quotation_count = 0;
        bool read_value = false;
        std::string attribute_buffer{};
        std::string value_buffer{}; 
        std::string str{};
        JsonObj res{};

        while (it_begin != it_end) {
            if (*it_begin == '{') {
                if (is_sub_json) {
                    JsonObj j_obj = iterIntoJson(it_begin,it_end);
                    JsonValue val(std::move(j_obj));
                    std::string attribute{attribute_buffer};
                    res.emplace(std::move(attribute), std::move(val));
                }
                is_sub_json = true;
            }
            else if (*it_begin == '}') {
                read_value = false;
                value_buffer = str;
                JsonValue j_val{std::atoi(value_buffer.c_str())};
                auto s = std::string(attribute_buffer);
                res.emplace(std::move(s), std::move(j_val));
                return res;
            }
            else if (*it_begin == '"') {
                if (!read_value) {
                    if (quotation_count == 0) {
                        quotation_count++;
                    } else {
                        quotation_count--;
                        attribute_buffer = str;
                        str.clear();
                    }
                } else {
                    str += *it_begin;
                }
            }
            else if (*it_begin == ':') {
                read_value = true;
            }
            else if (*it_begin == ',') {
                read_value = false;
                value_buffer = str;
                auto [key, val] = parseIntoPair(attribute_buffer, value_buffer);
                res.emplace(std::move(key), std::move(val));
                str.clear();
            }
            else {
                str += *it_begin;
            }
            it_begin++;
        }
        return res;
    }

    std::pair<std::string, JsonValue> parseIntoPair(std::string& attribute_str, std::string& value_str) {
        std::string attribute{attribute_str};
        int val = std::atoi(value_str.c_str());
        JsonValue value(val);
        return {attribute, val};
    }
}
