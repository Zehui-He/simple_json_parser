#include <iostream>
#include <string>
#include <queue>
#include "src/parser.h"

int main(int argc, char **argv) {
    std::string json_name(argv[1]);
    std::string content = json_parser::extractContnet(json_name);
    std::cout << content << std::endl;

    json_parser::Json json = json_parser::parseIntoJson(content);
    std::cout << json << std::endl;

    return 0;
}
