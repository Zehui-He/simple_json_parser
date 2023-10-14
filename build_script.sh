#!/bin/bash

rm -f *.out 
g++ -g -Wall -Wextra -pedantic main.cpp src/parser.cpp src/json_obj.cpp src/json_value.cpp -o json_parser.out 