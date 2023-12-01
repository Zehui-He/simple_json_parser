#include <catch2/catch_test_macros.hpp>
#include "src/json.h"
#include "src/json_types.h"
#include "src/parser.h"

TEST_CASE("Json object constructor") {
    SECTION("Json object can be default constructed and it should contain be null") {
        json_parser::Json json{};
        REQUIRE(json.get_type() == json_parser::JsonValueType::null_t);
        REQUIRE(json.read<std::nullptr_t>() == nullptr);
    }

    // SECTION("Json object can insert a pair of key and value") {
    //     json_parser::Json json{};
    //     auto [it, insert_success] = j_obj.emplace("int", std::move(j_val));
    //     REQUIRE(j_obj.empty() == false);
    //     REQUIRE(insert_success == true);
    //     REQUIRE(it->second.read<int>() == 10);
    // }

    // SECTION("Json object can get the Json value with string key") {
    //     json_parser::JsonObj j_obj{};
    //     json_parser::JsonValue j_val(10);
    //     j_obj.emplace("int", std::move(j_val));
    //     REQUIRE(j_obj[std::string("int")].read<int>() == 10);
    //     REQUIRE(j_obj["int"].read<int>() == 10);
    // }
}

TEST_CASE("Json value can be initilized with various types") {
    SECTION("Initialize with int") {
        json_parser::Json json(10);
        REQUIRE(json.get_type() == json_parser::JsonValueType::int_t);
        REQUIRE(json.read<int>() == 10);
    }

    SECTION("Initilize with double") {
        json_parser::Json json(10.1);
        REQUIRE(json.get_type() == json_parser::JsonValueType::double_t);
        REQUIRE(json.read<double>() == 10.1);
    }

    SECTION("Initilize with string") {
        std::string str1("Hello");
        std::string str2("Hello");
        json_parser::Json json(std::move(str1));
        REQUIRE(json.get_type() == json_parser::JsonValueType::string_t);
        REQUIRE(*(json.read<std::unique_ptr<std::string>>()) == str2);
    }

    SECTION("Initilize with Object") {
        json_parser::Json inner_json{json_parser::JsonValueType::object_t}; // Construct a json whose data type is object 
        json_parser::Json outer_json(std::move(inner_json));
        REQUIRE(outer_json.get_type() == json_parser::JsonValueType::object_t);
        REQUIRE(outer_json.read<json_parser::Json::JsonObjectPtr>() != nullptr);
    }
}

TEST_CASE("Json value can be moved constructed") {
    SECTION("Move construct from int and invalid the original object") {
        json_parser::Json json(10);
        json_parser::Json json2(std::move(json));
        REQUIRE(json2.read<int>() == 10);
        REQUIRE(json2.get_type() == json_parser::JsonValueType::int_t);
        REQUIRE(json.get_type() == json_parser::JsonValueType::null_t);
    }
}