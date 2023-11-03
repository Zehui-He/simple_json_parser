#pragma once 

#include <fstream>
#include <string>
#include <stack>
#include "json_value.h"
#include "json_obj.h"


namespace json_parser {
    // Extract the content of the json file and store as a string, 
    // removing any unnecessary tabs, spaces and new line characters. 
    std::string extractContnet(std::string json_name);

    // Convert the string into a json object. 
    JsonObj parseIntoJson(std::string const& content);

    // Generate json object with string iterator. 
    JsonObj iterIntoJson(std::string::const_iterator& it_begin, std::string::const_iterator& it_end, std::stack<char>& stack);
}
