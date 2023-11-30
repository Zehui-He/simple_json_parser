#include <iostream>
#include <string>
#include <queue>
#include "src/json_value.h"
#include "src/parser.h"
#include "src/json.h"

int main(int argc, char **argv) {
    // std::string json_name(argv[1]);
    // std::string content = json_parser::extractContnet(json_name);

    // json_parser::JsonObj json = json_parser::parseIntoJson(content);
    // // json.show();
    // auto& a = json["Person"]["Name"]["Last"];
    // std::cout << a <<std::endl;

    json_parser::Json a{};
    std::cout << a << std::endl;

    return 0;
}
