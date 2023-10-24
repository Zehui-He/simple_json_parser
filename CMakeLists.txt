cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

# Sepcify the source codes
set(SOURCES src/json_obj.cpp src/json_value.cpp src/parser.cpp)

# Third party libraries 
add_subdirectory(lib)

project(json_parser)

add_executable(json_parser.out main.cpp ${SOURCES})

add_executable(test.out test.cpp ${SOURCES})
target_link_libraries(test.out Catch2::Catch2WithMain)
