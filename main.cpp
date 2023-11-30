#include <iostream>
#include <string>
#include <queue>
#include "src/parser.h"

int main(int argc, char **argv) {
    std::string json_name(argv[1]);
    std::string content = json_parser::extractContnet(json_name);

    json_parser::Json json = json_parser::parseIntoJson(content);
    // // json.show();
    // auto& a = json["Person"]["Name"]["Last"];
    // std::cout << a <<std::endl;

    // std::cout << json["Address1"]["Country"] << std::endl;
    std::cout << json << std::endl;

    return 0;
}
