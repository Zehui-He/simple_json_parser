#include <string>
#include <unordered_map>

union JsonValue;
using JsonObj = std::unordered_map<std::string, JsonValue>;

union JsonValue {
    std::string s;
    int i;
    double d;
    JsonObj* j;
};

