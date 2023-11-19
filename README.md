This is a c++ practice project. 
This proejct has gone much further than I expected so I decided to make it a long-term project.

Objective:
A simple json parser which take the json file name via command line argument as input and store the result in an unoreded map. 

Limitation: 
As this is a practice project, I decided to reduce the complexity by making some assumptions. 

1. The JSON file is always valid. 
4. The result is stored in the form unordered_map<string, JsonValue>

20/11/2023 
Assumption 2 and 3 are removed, as the program now supports almost all kinds of JSON values except numeric values written in scientific notation. 
The program can store, access, modify and print the JSON values. 
More test should be added to ensure the program work correctly. 
A dump function should be implemented to allow outputting JSON value into a file. 
