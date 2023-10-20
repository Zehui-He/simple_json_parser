#include <catch2/catch_test_macros.hpp>
#include "src/json_obj.h"
#include "src/json_value.h"
#include "src/parser.h"

TEST_CASE("Json object constructor") {
    SECTION("Json object can be default constructed and it should be empty") {
        json_parser::JsonObj j_obj{};
        REQUIRE(j_obj.empty() == true);
    }

    SECTION("Json object can insert a pair of key and value") {
        json_parser::JsonObj j_obj{};
        json_parser::JsonValue j_val(10);
        auto [it, insert_success] = j_obj.emplace("int", std::move(j_val));
        REQUIRE(j_obj.empty() == false);
        REQUIRE(insert_success == true);
        REQUIRE(it->second.read<int>() == 10);
    }

    SECTION("Json object can get the Json value with string key") {
        json_parser::JsonObj j_obj{};
        json_parser::JsonValue j_val(10);
        j_obj.emplace("int", std::move(j_val));
        REQUIRE(j_obj[std::string("int")].read<int>() == 10);
        REQUIRE(j_obj["int"].read<int>() == 10);
    }
}

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

    SECTION("Initilize with JsonObj") {
        json_parser::JsonObj j_obj{};
        json_parser::JsonValue j_val(std::move(j_obj));
        REQUIRE(j_val.read<std::unique_ptr<json_parser::JsonObj>>()->empty() == true);
        REQUIRE(j_val.type == json_parser::JsonValue::JSON);
    }
}

TEST_CASE("Json value can be moved constructed") {
    SECTION("Move construct from int and invalid the original object") {
        json_parser::JsonValue jval(10);
        json_parser::JsonValue jval2(std::move(jval));
        REQUIRE(jval2.read<int>() == 10);
        REQUIRE(jval2.type == json_parser::JsonValue::INT);
        REQUIRE(jval.type == json_parser::JsonValue::NONE);
    }
}