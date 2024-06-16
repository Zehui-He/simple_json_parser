#pragma once 
#include <fstream>
#include <string>
#include <stack>
#include <json.h>


namespace json_parser {
    // Extract the content of the json file and store as a string, 
    // removing any unnecessary tabs, spaces and new line characters. 
    std::string extractContnet(std::string json_name);

    // Convert the string into a json object. 
    Json parseIntoJson(std::string const& content);

    // Generate json object with string iterator. 
    Json objectHandler(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack);
} // namespace json_parser
