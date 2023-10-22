cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

# Sepcify the source codes
set(SOURCES main.cpp src/json_obj.cpp src/json_value.cpp src/parser.cpp)

project(json_parser)

add_executable(json_parser.out ${SOURCES})
