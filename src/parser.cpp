#include <iostream>
#include "parser.h"

namespace json_parser {
    class Token {
        private:
        std::string::const_iterator start;
        size_t size;

        public:
        Token() {
            this->size = 0;
        }

        std::string to_string() const {
            std::string res{start, start + size};
            return std::move(res);
        }

        // Set the token to a new begin 
        void set(std::string::const_iterator begin) {
            this->start = begin;
            this->size = 0;
        }

        // Increase the position of start by 1 
        void advance() {
            this->start++;
        }

        bool empty() const {
            return size == 0;
        }

        void reset() {
            size = 0;
        };

        // Increase the size of token by 1 
        void operator++(int) {
            this->size++;
        }
    };
    // A trait to parse string value into JsonValue 
    template <typename T>
    struct parsing_trait {
        static JsonValue intoJson(std::string const& value_str) {
            return 0;
        };
    };

    template <>
    struct parsing_trait<int>
    {
        static JsonValue intoJson(std::string const& value_str) {
            int val = std::atoi(value_str.c_str());
            return val;
        };
    };

    template <>
    struct parsing_trait<std::string>
    {
        static JsonValue intoJson(std::string const& value_str) {
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

    JsonObj parseIntoJson(std::string const& content) {
        auto it_begin = content.cbegin();
        auto it_end = content.cend();
        auto stack = std::stack<char>{};
        JsonObj res = iterIntoJson(it_begin,it_end,stack);
        return res;
    }

    // Insert an entry to the json object with given value string and attribute string 
    // The value type recognition takes place here 
    void insertEntry(std::string const& attribute, std::string const& value, json_parser::JsonObj& j_obj) {
        if (isdigit(value[0])) {
            j_obj.emplace(attribute, std::move(parsing_trait<int>::intoJson(value)));
        // } else if (isalpha(value[0])) {
        } else {
            j_obj.emplace(attribute, std::move(parsing_trait<std::string>::intoJson(value)));
        }
    }

    // Currently no support for special characters such as '\n'
    std::string stringHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        Token token{};
        while (it_begin != it_end) {
            if (*it_begin == '"' && stack.top() == '"') { // End of string 
                stack.pop();
                return std::move(token.to_string());
            } else if (*it_begin == '"') { // Start of string 
                stack.push('"');
                token.set(it_begin+1);
            } else {    // Increase the size of string 
                token++;
            }
            it_begin++;
        }
        throw std::runtime_error("Syntax error: \" is not enclosed");
    }

    std::string valueHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        Token token{};
        while (it_begin != it_end) {
            if (*it_begin == ':') { // End of string 
                token.set(it_begin+1);
            } else if (*it_begin == ',' || *it_begin == '}') { // End of value 
                return std::move(token.to_string());
            } else { 
                token++;
            }
            it_begin++;
        }
        throw std::runtime_error("Syntax error: value cannot be parsed");
    }

    // This updated version has improved performance by avoiding unnecessary copying 
    JsonObj iterIntoJson(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        stack.push('{');
        it_begin++;
        json_parser::Token token{};
        std::string attribute_buff{};
        std::string value_buff{};
        JsonObj res{};

        while (it_begin != it_end) {
            if (*it_begin == '{') { // Start of object 
                // WARNING: the program never go to this line because object is handled in value 
                if (stack.top() == '{') {
                    JsonObj j_obj = iterIntoJson(it_begin, it_end, stack);
                    JsonValue j_val{std::move(j_obj)};
                    res.emplace(attribute_buff, std::move(j_val));
                }
            }
            else if (*it_begin == '"') { // Start of string 
                attribute_buff = stringHandler(it_begin, it_end, stack);
            }
            else if (*it_begin == ':') { // Start of vlaue 
                value_buff = valueHandler(it_begin, it_end, stack);
                insertEntry(attribute_buff, value_buff, res);
                if (*it_begin == '}') { // End of object 
                    if (stack.top() != '{') {
                        throw std::runtime_error("Syntax error: { is not enclosed.");
                    } else {
                        return res;
                    }
                }
            }
            else {
                token++;
            }
            it_begin++;
        }
        return res;
    }

}
