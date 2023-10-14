#pragma once 

#include <fstream>
#include <string>
#include "json_value.h"
#include "json_obj.h"


namespace json_parser {
    // Extract the content of the json file and store as a string, 
    // removing any unnecessary tabs, spaces and new line characters. 
    std::string extractContnet(std::string json_name);

    // Convert the string into a json object. 
    JsonObj parseIntoJson(std::string& content);

    // Generate json object with string iterator. 
    JsonObj iterIntoJson(std::string::iterator& it_begin, std::string::iterator& it_end);

    // Parse the string into json value. 
    std::pair<std::string, JsonValue> parseIntoPair(std::string& attribute, std::string& value);
}
