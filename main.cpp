#include <iostream>
#include <string>
#include <queue>
#include "src/json_value.h"
#include "src/helper.h"
#include <unordered_map>

int main(int argc, char **argv) {
    std::string json_name(argv[1]);
    std::string content = extractContnet(json_name);

    std::cout << content;
    return 0;
}