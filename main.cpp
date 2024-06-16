#include <cassert>
#include <iostream>
#include "src/json.h"
#include "src/parser.h"

int main(int argc, char* argv[]) {
    std::string file = argv[1];

    auto content = json_parser::extractContnet(file);
    std::cout << content << std::endl;

    auto json = json_parser::parseIntoJson(content);
    std::cout << json << std::endl; 

    return 0;
}