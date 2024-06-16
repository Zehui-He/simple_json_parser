cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(json_parser)

# Sepcify the source codes
set(SOURCES src/parser.cpp src/json.cpp src/json_value.cpp)

# Third party libraries 
add_subdirectory(lib)

add_library(simple_json_parser ${SOURCES})

include_directories(include)

add_executable(json_parser.out main.cpp)
target_link_libraries(json_parser.out simple_json_parser)

add_executable(test.out test.cpp ${SOURCES})
target_link_libraries(test.out simple_json_parser Catch2::Catch2WithMain)
