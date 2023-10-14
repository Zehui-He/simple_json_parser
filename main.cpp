#include <iostream>
#include <string>
#include <queue>
#include "src/json_value.h"
#include "src/parser.h"

int main(int argc, char **argv) {
    std::string json_name(argv[1]);
    std::string content = extractContnet(json_name);

    JsonObj json = parseIntoJson(content);
    json.show();

    return 0;
}
