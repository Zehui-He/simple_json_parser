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

        std::string toString() const {
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

    // Do not advance it_begin if it has reached the end 
    void safeIteratorIncrement(std::string::const_iterator& it_begin, std::string::const_iterator& it_end) {
        if (it_begin == it_end) {
            return;
        }
        it_begin++;
    }

    JsonObj parseIntoJson(std::string const& content) {
        auto it_begin = content.cbegin();
        auto it_end = content.cend();
        auto stack = std::stack<char>{};
        JsonObj res = objectHandler(it_begin,it_end,stack);
        return res;
    }

    // Convert the string into a JsonValue 
    // The value type recognition takes place here 
    JsonValue stringToValue(std::string const& value) {
        if (isdigit(value[0])) {
            return std::move(parsing_trait<int>::intoJson(value));
        // } else if (isalpha(value[0])) {
        } else {
            return std::move(parsing_trait<std::string>::intoJson(value));
        }
    }

    // Currently no support for special characters such as '\n' and '[' 
    // The string handler should pass the tailing '"' 
    std::string stringHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        Token token{};
        while (it_begin != it_end) {
            if (*it_begin == '"' && stack.top() == '"') { // End of string 
                stack.pop();
                safeIteratorIncrement(it_begin, it_end); // Pass the tailing '"' 
                return std::move(token.toString());
            } else if (*it_begin == '"') { // Start of string 
                stack.push('"');
                token.set(it_begin+1);
            } else { 
                token++;
            }
            safeIteratorIncrement(it_begin, it_end);
        }
        throw std::runtime_error("Syntax error: \" is not enclosed");
    }

    JsonValue vectorHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack);

    // Handle values inside vector 
    // The ',' is not handle in this case to sign the vector is no finished 
    JsonValue vectorValueHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        Token token{};
        token.set(it_begin);
        while (it_begin != it_end) {
            if (*it_begin == '"') {
                return std::move(stringHandler(it_begin, it_end, stack));
            } else if (*it_begin == '[') {
                return std::move(vectorHandler(it_begin, it_end, stack));
            } else if (*it_begin == '{') { 
                return std::move(objectHandler(it_begin, it_end, stack));
            } else if (*it_begin == ',' || *it_begin == ']') { 
                return std::move(stringToValue(token.toString()));
            } else { 
                token++;
            }
            safeIteratorIncrement(it_begin, it_end);
        }
        throw std::runtime_error("Syntax error: value cannot be parsed");
    }

    // The vector handler should pass the tailing ']' 
    JsonValue vectorHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        std::vector<JsonValue> value_vec{};
        while (it_begin != it_end) {
            if (*it_begin == '[') { // Start of a vector 
                stack.push('[');
                safeIteratorIncrement(it_begin, it_end);
                value_vec.emplace_back(vectorValueHandler(it_begin, it_end, stack));
            } 
            else if (*it_begin == ',') {
                safeIteratorIncrement(it_begin, it_end);
                value_vec.emplace_back(vectorValueHandler(it_begin, it_end, stack));
            } 
            else if (*it_begin == ']') { // End of a vector 
                if (stack.top() == '[') {
                    safeIteratorIncrement(it_begin, it_end);
                    stack.pop();
                    return std::move(value_vec);
                }
            }
        }
        throw std::runtime_error("Syntax error: ] is not enclosed");
    }

    // The value handler should handle the tailing ','
    JsonValue valueHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        Token token{};
        while (it_begin != it_end) {
            if (*it_begin == ':') { // Start of value 
                token.set(it_begin+1);
            } else if (*it_begin == '"') {
                return std::move(stringHandler(it_begin, it_end, stack));
            } else if (*it_begin == '[') {
                return std::move(vectorHandler(it_begin, it_end, stack));
            } else if (*it_begin == '{') { // The value is an object 
                return std::move(objectHandler(it_begin, it_end, stack));
            } else if (*it_begin == ',' || *it_begin == '}' || *it_begin == ']') { // End of value 
                if (*it_begin == ',') { // Pass the tailing ',' 
                    safeIteratorIncrement(it_begin, it_end);
                }
                return std::move(stringToValue(token.toString()));
            } else { 
                token++;
            }
            safeIteratorIncrement(it_begin, it_end);
        }
        throw std::runtime_error("Syntax error: value cannot be parsed");
    }

    // The object handler should handle the tailing '}' 
    JsonObj objectHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack) {
        json_parser::Token token{};
        std::string attribute_buff{};
        JsonObj res{};

        while (it_begin != it_end) {
            if (*it_begin == '{') { // Start of object 
                stack.push('{');
                token.set(it_begin+1);
            }
            else if (*it_begin == '"') { // Start of string 
                attribute_buff = stringHandler(it_begin, it_end, stack);
                continue;
            }
            else if (*it_begin == ':') { // Start of vlaue 
                res.emplace(attribute_buff, std::move(valueHandler(it_begin, it_end, stack)));
                continue;
            } 
            else if (*it_begin == '}') { // End of object 
                if (stack.top() != '{') {
                    throw std::runtime_error("Syntax error: { is not enclosed.");
                } else {
                    safeIteratorIncrement(it_begin,it_end); // Pass the tailing '}' 
                    stack.pop();
                    return res;
                }
            }
            else {
                token++;
            }
            safeIteratorIncrement(it_begin, it_end); 
        }
        return res;
    }

}
