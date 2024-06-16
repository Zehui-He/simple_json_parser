#include <catch2/catch_test_macros.hpp>
#include "src/json.h"
#include "src/json_value.h"
#include "src/parser.h"

TEST_CASE("JsonValue default constructor") {
    SECTION("JsonValue can be default constructed and it should contain be null") {
        json_parser::JsonValue json_value{};
        REQUIRE(json_value.get_type() == json_parser::JsonValueType::null_t);
        REQUIRE(json_value.read<std::nullptr_t>() == nullptr);
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

TEST_CASE("Json object default constructor") {
    SECTION("Json object can be default constructed and it should be a empty map") {
        json_parser::Json json{};
        REQUIRE(json.size() == 0);
    }

    // SECTION("Json object can insert a pair of key and value") {
    // }

    // SECTION("Json object can get the Json value with string key") {
    // }
}

TEST_CASE("Json value can be initilized with various types") {
    SECTION("Initialize with int") {
        json_parser::JsonValue null_json_value(10);
        REQUIRE(null_json_value.get_type() == json_parser::JsonValueType::int_t);
        REQUIRE(null_json_value.read<json_parser::JsonValueType::int_t>() == 10);
    }

    SECTION("Initilize with double") {
        json_parser::JsonValue double_json_value(10.1);
        REQUIRE(double_json_value.get_type() == json_parser::JsonValueType::double_t);
        REQUIRE(double_json_value.read<json_parser::JsonValueType::double_t>() == 10.1);
    }

    SECTION("Initilize with string") {
        std::string str1("Hello");
        std::string str2("Hello");
        json_parser::JsonValue string_json_value(std::move(str1));
        REQUIRE(string_json_value.get_type() == json_parser::JsonValueType::string_t);
        REQUIRE(string_json_value.get<json_parser::JsonValueType::string_t>() == str2);
    }

    SECTION("Initilize with Json object") {
        json_parser::Json json{}; 
        json_parser::JsonValue object_json_value(std::move(json));
        REQUIRE(object_json_value.get_type() == json_parser::JsonValueType::object_t);
        REQUIRE(object_json_value.read<json_parser::JsonValueType::object_t>() != nullptr);
    }

    SECTION("Initilize with bool") {
        json_parser::JsonValue bool_json_value(true);
        REQUIRE(bool_json_value.get_type() == json_parser::JsonValueType::bool_t);
        REQUIRE(bool_json_value.read<json_parser::JsonValueType::bool_t>() == true);
    }

    SECTION("Initilize with null") {
        json_parser::JsonValue null_json_value(nullptr);
        REQUIRE(null_json_value.get_type() == json_parser::JsonValueType::null_t);
        REQUIRE(null_json_value.read<json_parser::JsonValueType::null_t>() == nullptr);
    }

    SECTION("Initilize with vector") {
        std::vector<json_parser::JsonValue> jsonvalue_vec;
        json_parser::JsonValue vector_json_value(std::move(jsonvalue_vec));
        REQUIRE(vector_json_value.get_type() == json_parser::JsonValueType::array_t);
        REQUIRE(vector_json_value.read<json_parser::array_t>().size() == 0);
    }
}

TEST_CASE("Json value can be moved constructed") {
    SECTION("Move construct from int and invalid the original object") {
        json_parser::JsonValue json(10);
        json_parser::JsonValue json2(std::move(json));
        REQUIRE(json2.read<int>() == 10);
        REQUIRE(json2.get_type() == json_parser::JsonValueType::int_t);
        REQUIRE(json.get_type() == json_parser::JsonValueType::null_t);
    }
}