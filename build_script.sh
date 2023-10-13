#!/bin/bash

rm -f *.out 
g++ -g -Wall -Wextra -pedantic main.cpp src/parser.cpp -o json_parser.out 