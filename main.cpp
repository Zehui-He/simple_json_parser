#include <iostream>
#include <string>
#include <queue>
#include "src/json_value.h"
#include "src/helper.h"

int main(int argc, char **argv) {
    std::string json_name(argv[1]);
    std::string content = extractContnet(json_name);

    JsonObj json = parseIntoJson(content);

    for (auto it = json.begin(); it != json.end(); it++) {
        if (it->second.type == JsonValue::JSON) {
            std::cout << it->first << ": " << it->second.data.j->size() << "\n";
        } else {
            std::cout << it->first << ": " << it->second.data.i << "\n";
        }
    }

    return 0;
}
