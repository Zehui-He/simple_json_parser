#!/bin/bash

rm -f *.out 
g++ -g -Wall -Wextra -pedantic main.cpp src/helper.cpp -o json_parser.out 