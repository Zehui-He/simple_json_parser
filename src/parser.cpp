#include <iostream>
#include "parser.h"

namespace json_parser {
    template <typename T>
    struct parsing_trait {
        static JsonValue intoJson(std::string& value_str) {
            return 0;
        };
    };

    template <>
    struct parsing_trait<int>
    {
        static JsonValue intoJson(std::string& value_str) {
            int val = std::atoi(value_str.c_str());
            return val;
        };
    };

    template <>
    struct parsing_trait<std::string>
    {
        static JsonValue intoJson(std::string& value_str) {
            std::string val = value_str;
            return val;
        };
    };

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
        auto stack = std::stack<char>{};
        JsonObj res = iterIntoJson(it_begin,it_end,stack);
        return res;
    }

    // Note: this is a super naive but recursive approach. 
    JsonObj iterIntoJson(std::string::iterator& it_begin, std::string::iterator& it_end, std::stack<char>& stack) {
        stack.push('{');
        it_begin++;
        std::string token{};
        std::string attribute_buff{};
        std::string value_buff{};
        JsonObj res{};

        while (it_begin != it_end) {
            if (*it_begin == '{') {
                JsonObj j_obj = iterIntoJson(it_begin, it_end, stack);
                JsonValue j_val{std::move(j_obj)};
                res.emplace(attribute_buff, std::move(j_val));
            }
            else if (*it_begin == '}') {
                if (stack.top() == '{') {
                    stack.pop();
                    // Insert entry into json object 
                    if (isdigit(value_buff[0])) {
                        res.emplace(attribute_buff, std::move(parsing_trait<int>::intoJson(value_buff)));
                    } else if (isalpha(value_buff[0])) {
                        res.emplace(attribute_buff, std::move(parsing_trait<std::string>::intoJson(value_buff)));
                    }
                    return res;
                } else {
                    throw std::runtime_error("Syntax error: the '{' is not enclosed.");
                }
            }
            else if (*it_begin == '"') {
                if (stack.top() == '"') {
                    stack.pop();
                } else {
                    stack.push('"');
                }
            }
            else if (*it_begin == ':') {
                attribute_buff = token;
                token.clear();
            }
            else if (*it_begin == ',') {
                value_buff = token;
                token.clear();
                // Insert entry into json object 
                if (isdigit(value_buff[0])) {
                    res.emplace(attribute_buff, std::move(parsing_trait<int>::intoJson(value_buff)));
                } else if (isalpha(value_buff[0])) {
                    res.emplace(attribute_buff, std::move(parsing_trait<std::string>::intoJson(value_buff)));
                }
            }
            else {
                token += *it_begin;
            }
            it_begin++;
        }
        return res;
    }

}
