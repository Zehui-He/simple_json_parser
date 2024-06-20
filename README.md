# A simple Json parser implemented by C++ 

A simple Json parser which take the Json file name via command line argument as input and store the result in an unoreded map of string and JsonValue pairs. 

## Assumptions:
In this project, it is assumed that the given Json file is always valid. This is because handling invalid Json files would introduce lots of edges cases that make the project extremely complex. If the input file is not legit, a runtime error will be thrown. 


## Functionality:
This section would describe some functionality of this library and why did I designed in that way. 

### 1. Construct a Json object from file(string) 
To construct a Json object from a file, the first step we do is extrating the content of the file into a string with the `json_parser::extraContent` function. During extraction, we also do some pre-processing to the content, that is, removing the unnessary spaces, tabs and new line characters. Then, the string containing the content of the file is passed to the `json_parser::parseIntoJson` function to generate a Json object. 

Exception: If the given file does not exist, a `std::runtime_error` is thrown. 
```
#include <iostream>
#include <parser.h>
#include <json.h>

int main(int argc, char **argv) {
    std::string json_name(argv[1]);
    std::string content = json_parser::extractContnet(json_name);
    json_parser::Json json = json_parser::parseIntoJson(content);
    std::cout << json << std::endl;

    return 0;
}
```

### 2. Default construction of JsonValue object 
When a Json object is default constructed, it holds a null pointer, indicating that it contains no value. 
```
#include <cassert>
#include <parser.h>
#include <json_value.h>

int main() {
    json_parser::JsonValue jv;
    assert(jv.get_type() == json_parser::JsonValueType::null_t);
    assert(jv.get<json_parser::null_t>() == nullptr);

    return 0;
}
```

### 3. Construct a JsonValue object with a given value 
It should be noted that some types can only be constructed with rvalue reference. This design is to minimise the unnecessary copy of the data. 
```
#include <vector>
#include <unordered_map>
#include <json_value.h>
#include <json.h>

int main() {
    // Initialize with int 
    json_parser::JsonValue j1(1); 

    // Initialize with double 
    json_parser::JsonValue j2(1.2); 

    // Initialize with unsigned int 
    json_parser::JsonValue j3(1u); 

    // Initialize with bool 
    json_parser::JsonValue j4(true); 

    // Initialize with string literal
    json_parser::JsonValue j5("Hello"); 
    
    // Initialize with string&& 
    std::string str("Good");
    json_parser::JsonValue j6(std::move(str)); 

    // Initialize with JsonArray&& 
    json_parser::JsonArray j_vec{1, 1u, true, nullptr};
    json_parser::JsonValue j7(std::move(j_vec)); 

    // Initialize with Json&& 
    json_parser::Json j_obj;
    json_parser::JsonValue j8(std::move(j_obj)); 

    // Initialize with nullptr 
    json_parser::JsonValue j9(nullptr); 

    return 0;
}
```
### 4. Construct a JsonValue object with given JsonValueType 
Construct a JsonValue object which hold a defalt value of the given JsonValueType. The default value for int_t, double_t and unsigned_int_t is 0. The default value for bool_t is false. The default value for string_t is empty string. The default value for array_t is an empty vector of type `JsonArray`. The default value for object_t is an unique pointer of type `std::unique_ptr<Json>`. The default value for null_t is nullptr. 
```
#include <cassert>
#include <json.h>
#include <json_value_type.h>

int main() {
    // Initialize with int_t 
    json_parser::JsonValue jv1(json_parser::JsonValueType::int_t); 
    assert(jv1.get<json_parser::int_t>() == 0);

    // Initialize with double_t
    json_parser::JsonValue jv2(json_parser::JsonValueType::double_t); 
    assert(jv2.get<json_parser::double_t>() == 0);

    // Initialize with unsigned int 
    json_parser::JsonValue jv3(json_parser::JsonValueType::unsigned_int_t); 
    assert(jv3.get<json_parser::unsigned_int_t>() == 0);

    // Initialize with bool_t 
    json_parser::JsonValue jv4(json_parser::JsonValueType::bool_t); 
    assert(jv4.get<json_parser::bool_t>() == false);

    // Initialize with string_t
    json_parser::JsonValue jv5(json_parser::JsonValueType::string_t); 
    assert(jv5.get<json_parser::string_t>() == "");
    
    // Initialize with array_t
    json_parser::JsonValue jv6(json_parser::JsonValueType::array_t); 
    assert(jv6.get<json_parser::array_t>().size() == 0);

    // Initialize with object_t
    json_parser::JsonValue jv7(json_parser::JsonValueType::object_t); 
    assert(jv7.get<json_parser::object_t>()->size() == 0);

    // Initialize with null_t
    json_parser::JsonValue jv8(json_parser::JsonValueType::null_t); 
    assert(jv8.get<json_parser::null_t>() == nullptr);

    return 0;
}
```
### 5. Move construction 
The move constructed JsonValue object will take the ownership of data of the orginal one. The orginal data afer move construction should hold a nullptr, indicating that it holds no data. 
```
#include <cassert>
#include <parser.h>
#include <json_value_type.h>
#include <json_value.h>

int main() {
    json_parser::JsonValue original{1};
    json_parser::JsonValue new_jv{std::move(original)};
    assert(original.get_type() == json_parser::JsonValueType::null_t);
    assert(new_jv.get_type() == json_parser::JsonValueType::int_t);
    assert(new_jv.get<json_parser::int_t>() == 1);

    return 0;
}
```
## Design:
### 1. JsonValueType 
The JsonValueType is a enumerated class which represents the value types that a Json can hold. For example, number, null, array and object. However, the number type can be further divided into three types: int, double and unsigned int. As a result, there are 8 Json value types in total. 
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
### 2. JsonValue class  
#### 2.1 How to implement all JsonValueType in C++? 
To represent all the Json value type, we need 8 concrete types. In my design, these concrete types are called **implementation types**, indicating they are the implmentation of the JsonValueType. The mapping between JsonValueType and implementation types are shown in this table.
| Json value type| implementation type | Description|
| :---          |    :----:    |          ---:     |
| int_t         | int          | integer number    |
| double_t      | double       | decimal number    |
| unsigned_int_t| unsigned int       | large integer number    |
| string_t      | std::string     | string    |
| array_t       | std::vector\<JsonValue\>       | array of Json values   |
| object_t      | std::unique_ptr<std::unordered_map\<std::string, JsonValue\>>       | string/JsonValue pair   |
| null_t        | std::nullptr_t       | null   |
#### 2.2 How to store a Json value? 
In the previous section, we know that a JsonValue can hold various types of values. To store the data, a brute force approach is having several data members that cover all Json value types. However, such design is clearly memory ineffcient and it makes the data difficult to access or modify without introducing an error. A better approch is to store all data types in a single data member while keep tracking the type of the data that is being stored. In the C++ standard library, both `union type` and `std::variant` can achieve this. In this project, I decided to use `std::variant` to store the data because it is a type-safe version of `union` which can keep me away from accessing the data incorrectly. On the other hand, it does not require an extra data member to store the underlying data type. If such data member is needed, it potentially intoduce error because we may forget the modify it when we change the data type. This problem does not exist for `std::variant` as it tracks the data type it holds. It is very important to note that the size of the `std::variant` depends on the largest alternative. Its size can grow significantly when it holds large types. 

I wrapped the Json object with unique pointer because the definition of Json is incomplete at the moment it is used in JsonValue. 

NOTE: Since C++ standard says that `std::variant` cannot hold `void`, I used a null pointer to represents the null Json value.  
```
class Json {
    // Other members...
    public:
    using JsonValue = std::variant<
        int, 
        double,
        unsigned int, 
        bool,
        std::string,
        JsonArray,
        std::unique_ptr<Json>,
        std::nullptr_t
    >; 

    private:
    JsonValue m_data; 

    // Other members...
}
```
#### 2.3 How to check if a type is an implementation type? 
When we construct functions for JsonValue types, we often want to use templates because we don't want to construct a separate function for each implementation type. A problem raises when we write template function: the type of the template has no constraint such that it can generate functions for types that is not an implmentation type. A detail example can see section 2.5. To address the issue, a `is_json_impl_type` trait is used for checking if a given type is implementation type. 
```
template <typename T>
struct is_json_impl_type : std::false_type {}; 

template <typename T>
inline constexpr bool is_json_impl_type_v = is_json_impl_type<T>::value;

template <>
struct is_json_impl_type<int> : std::true_type {};

// Other specializations...
```
#### 2.4 Mapping between Json value types and implementation types 
As discussed in section 2.1, each Json value type has a corresponding implementation type. In most of the cases, we prefer to use the Json value types rather than the implementation types because they are easy to understand. On the other hand, the implementation types are usually verbose. However, there is a problem that we must use the implementation types. For instance, users need to specify the returning type of the 'get' function. To make our code more readable, it is necessary to make a mapping between the Json value types and the implementation types. In this project, a type trait called `data_impl_mapping` is used. The design of this trait is very similar to the STL type trait, that is, when you specify a Json value type in the template parameter, you can get the implementation types via its `type` member. 
```
template <JsonValueType T>
struct data_impl_mapping;

template <>
struct data_impl_mapping<JsonValueType::int_t> {
    using type = int;
};

template <>
struct data_impl_mapping<JsonValueType::double_t> {
    using type = double;
};

// Other specializations... 
```
In addition, to simplify the usage of this type trait, a helper expression `data_impl_mapping_t` is used to provider easier access. 
```
template <JsonValueType V>
using data_impl_mapping_t = typename data_impl_mapping<T>::type;
```
<!-- #### 2.5 Data access 
To get a reference of the data held by `std::variant` object, we need to use the `std::get` function. The use of `std::get` function will required the user to specify the return type. For example, if we want to get an `int&`, we need to use the function like this `std::get<int>(variant)`. As we have several implmentation types, it is clear that we don't want to write the  -->
