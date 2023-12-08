#include <cassert>
#include "src/json.h"
#include "src/json_types.h"

int main() {
    json_parser::Json origin_json{1};
    assert(origin_json.get_type() == json_parser::JsonValueType::int_t);
    json_parser::Json new_json{std::move(origin_json)};
    assert(origin_json.get_type() == json_parser::JsonValueType::null_t);
    assert(new_json.get_type() == json_parser::JsonValueType::int_t);
    assert(new_json.get_by_type<json_parser::JsonValueType::int_t>() == 1);

    return 0;
}