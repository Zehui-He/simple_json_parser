# This document is outdated! Please do not use! 
# A simple JSON parser implemented by C++ 

A simple JSON parser which take the JSON file name via command line argument as input and store the result in an unoreded map of string and JsonValue pairs. 

## Assumptions:
In this project, it is assumed that the given JSON file is always valid. This is because handling invalid JSON files would introduce lots of edges cases that make the project extremely complex. If the input file is not legit, a runtime error will be thrown. 


## Functionality:
This section would describe some functionality of this library and why did I designed in that way. 

### 1. Construct a Json object from file(string) 
To construct a Json object from a file, the first step we do is extrating the content of the file into a string with the `json_parser::extraContent` function. During extraction, we also do some pre-processing to the content, that is, removing the unnessary spaces, tabs and new line characters. Then, the string containing the content of the file is passed to the `json_parser::parseIntoJson` function to generate a Json object. 

Exception: If the given file does not exist, a `std::runtime_error` is thrown. 
```
#include <iostream>
#include <json_parser/parser.h>
#include <json_parser/Json.h>

int main(int argc, char **argv) {
    std::string json_name(argv[1]);
    std::string content = json_parser::extractContnet(json_name);
    json_parser::Json json = json_parser::parseIntoJson(content);
    std::cout << json << std::endl;

    return 0;
}
```

### 2. Default construction of JsonValue 
When a Json object is default constructed, it holds a null pointer, indicating that it contains no value. 
```
#include <cassert>
#include <json_parser/parser.h>
#include <json_parser/json_types.h>

int main() {
    json_parser::Json j;
    assert(j.get_type() == json_parser::JsonValueType::null_t);

    return 0;
}
```

### 3. Construct a Json object with a given value 
It should be noted that some types can only be constructed by rvalue reference. This design is to minimise the unnecessary copy of the data. **Due this reason, the Json class is not copy constructable.**
```
#include <vector>
#include <unordered_map>
#include <json_parser/json.h>

int main() {
    // Initialize with int 
    json_parser::Json j1(1); 

    // Initialize with double 
    json_parser::Json j2(1.2); 

    // Initialize with unsigned int 
    json_parser::Json j3(1U); 

    // Initialize with bool 
    json_parser::Json j4(true); 

    // Initialize with string literal
    json_parser::Json j5("Hello"); 
    
    // Initialize with string&& 
    std::string str("Good");
    json_parser::Json j6(std::move(str)); 

    // Initialize with std::vector<Json>&& 
    std::vector<Json> j_vec{};
    json_parser::Json j7(std::move(j_vec)); 

    // Initialize with std::unordered_map<std::string, Json>&& 
    std::unordered_map<std::string, Json> j_map{};
    json_parser::Json j8(std::move(j_map)); 

    // Initialize with nullptr 
    json_parser::Json j9(nullptr); 

    return 0;
}
```
### 4. Construct a Json object with JsonValueType 
Construct a Json object which hold a defalt value of the given JsonValueType. The default value for int_t, double_t and unsigned_int_t is 0. The default value for bool_t is false. The default value for string_t is empty string. The default value for array_t is an empty vector of type `std::vector<Json>`. The default value for object_t is an empty map of type `std::unordered_map<std::string, Json>`. The default value for null_t is nullptr. 
```
#include <json_parser/json.h>
#include <json_parser/json_types.h>

int main() {
    // Initialize with int_t 
    json_parser::Json j1(json_parser::JsonValueType::int_t); 

    // Initialize with double_t
    json_parser::Json j2(json_parser::JsonValueType::double_t); 

    // Initialize with unsigned int 
    json_parser::Json j3(json_parser::JsonValueType::unsigned_int_t); 

    // Initialize with bool_t 
    json_parser::Json j4(json_parser::JsonValueType::bool_t); 

    // Initialize with string_t
    json_parser::Json j5(json_parser::JsonValueType::string_t); 
    
    // Initialize with array_t
    json_parser::Json j6(json_parser::JsonValueType::array_t); 

    // Initialize with object_t
    json_parser::Json j7(json_parser::JsonValueType::object_t); 

    // Initialize with null_t
    json_parser::Json j8(json_parser::JsonValueType::null_t); 

    return 0;
}
```
### 5. Move construction 
The move constructed Json object will take the ownership of data of the orginal one. The orginal data afer move construction should hold a nullptr, indicating that it holds no data. 
```
#include <cassert>
#include <json_parser/parser.h>
#include <json_parser/json_types.h>

int main() {
    json_parser::Json origin_json{1};
    assert(origin_json.get_type() == json_parser::JsonValueType::int_t);
    json_parser::Json new_json{std::move(origin_json)};
    assert(origin_json.get_type() == json_parser::JsonValueType::null_t);
    assert(new_json.get_type() == json_parser::JsonValueType::int_t);
    assert(new_json.get_by_type<json_parser::JsonValueType::int_t>() == 1);

    return 0;
}
```
## Design:
### 1. JsonValueType 
The JsonValueType is a enumerated class which represents the value types that a JSON object can hold. For example, number, null, array and object. However, the number type can be further divided into three types: int, double and unsigned int. As a result, there are 8 JSON value types in total. 
```
enum JsonValueType : size_t {
    int_t,              // for integer number 
    double_t,           // for decimal number 
    unsigned_int_t,     // for large integer number 
    bool_t,             // for boolean value 
    string_t,           // for string 
    array_t,            // for array 
    object_t,           // for object 
    null_t,             // for null 
};
```
### 2. Json 
#### 2.1 How to represent a JSON value? 
To represent all the JSON value type, we need 8 concrete types. In my design, these concrete types are called **implementation types**, indicating they are the implmentation of the JSON types. The mapping between JSON value types and implementation types are shown in this table.
| JSON value type| implementation type | Description|
| :---          |    :----:    |          ---:     |
| int_t         | int          | integer number    |
| double_t      | double       | decimal number    |
| unsigned_int_t| unsigned int       | large integer number    |
| string_t      | std::unique_ptr\<std::string\>       | string    |
| array_t       | std::unique_ptr<std::vector\<Json\>>       | array of Json values   |
| object_t      | std::unique_ptr<std::unordered_map\<std::string, Json\>>       | string/JSON value pair   |
| null_t        | std::nullptr_t       | null   |
#### 2.2 How to store a JSON value? 
In the previous section, we know that a JSON object can hold various types of values. To store the data, a brute force approach is having several data members that cover all JSON value types. However, such design is clearly memory ineffcient and it makes the data difficult to access or modify without introducing an error. A better approch is to store all data types in a single data member while keep tracking the type of the data that is being stored. In the C++ standard library, both `union type` and `std::variant` can achieve this. In this project, I decided to use `std::variant` to store the data because it is a type-safe version of `union` which can keep me away from accessing the data incorrectly. On the other hand, it does not require an extra data member to store the underlying data type. If such data member is needed, it potentially intoduce error because we may forget the modify it when we change the data type. This problem does not exist for `std::variant` as it tracks the data type it holds. It is very important to note that the size of the `std::variant` depends on the largest alternative. Its size can grow significantly when it holds large types. 

I wrapped the complex types with unique pointer for two reasons. Firstly, I don't want the complex data being copied. Secondly, the Json object should be respsible for freeing its data. With the unique pointer, we can guarantee the data is being freed when the Json object go out of scope. 

NOTE: Since C++ standard says that `std::variant` cannot hold `void`, I used a null pointer to represents the null JSON value.  
```
class Json {
    // Other members...
    public:
    using JsonValue = std::variant<
        int, 
        double,
        unsigned int, 
        bool,
        std::unique_ptr<std::string>,
        std::unique_ptr<JsonArray>,
        std::unique_ptr<JsonObject>,
        std::nullptr_t
    >; 

    private:
    JsonValue m_data; 

    // Other members...
}
```
#### 2.3 Mapping between JSON value types and implementation types 
As discussed in section 2.1, each JSON value type has a corresponding implementation type. In most of the cases, we prefer to use the JSON value types rather than the implementation types because they are easy to understand. On the other hand, the implementation types are usually verbose However, there is a problem that we must use the implementation types. For instance, the implementation types are the returning type of a function. To make our code more readable, it is necessary to make a mapping between the JSON value types and the implementation types. In this project, a type trait called `json_value_impl_mapping` is used. The design of this trait is very similar to the STL type trait, that is, when you specify a JSON value type in the template parameter, you can get the implementation types via its `type` member. 
```
template <JsonValueType V>
struct json_value_impl_mapping;

template <>
struct json_value_impl_mapping<int_t> {
    using type = int;
};

template <>
struct json_value_impl_mapping<double_t> {
    using type = double;
};

// Other implementations... 
```
In addition, to simplify the usage of this type trait, a helper class `is_json_value_type_v` is used to provider easier access. 
```
template <JsonValueType V>
inline constexpr bool is_json_value_type_v = is_json_value_type<V>::value;
```