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
            std::cout << it->first << std::endl;
            auto j = &std::get<std::unique_ptr<JsonObj>>(it->second.data);
            for (auto it2 = j->get()->begin(); it2 != j->get()->end(); it2++) {
                std::cout << it2->first << ": " << std::get<int>(it2->second.data) << "\n";
            }
        } else {
            std::cout << it->first << ": " << std::get<int>(it->second.data) << "\n";
        }
    }

    return 0;
}
