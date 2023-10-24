#include "catch2/catch_test_macros.hpp"
#include "src/json_obj.h"
#include "src/json_value.h"
#include "src/parser.h"

TEST_CASE("Json value can be initilized with various types") {
    SECTION("Initialize with int") {
        json_parser::JsonValue jval(10);
        REQUIRE(jval.read<int>() == 10);
        REQUIRE(jval.type == json_parser::JsonValue::INT);
    }

    SECTION("Initilize with double") {
        json_parser::JsonValue jval(10.1);
        REQUIRE(jval.read<double>() == 10.1);
        REQUIRE(jval.type == json_parser::JsonValue::DOUBLE);
    }

    SECTION("Initilize with string") {
        std::string str1("Hello");
        std::string str2("Hello");
        json_parser::JsonValue jval(std::move(str1));
        REQUIRE(*(jval.read<std::unique_ptr<std::string>>()) == str2);
        REQUIRE(jval.type == json_parser::JsonValue::STRING);
    }
}