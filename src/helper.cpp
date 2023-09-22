#include "helper.h"
#include <iostream>

std::string extractContnet(std::string json_name) {
    std::string content;
    unsigned int quotation_count = 0;

    std::ifstream json_file(json_name);
    if (!json_file.is_open()) {
        std::cout << "The file does not exist.\n";
        return content;
    }

    // Remove any tab, space, end of line that is not enclosed by quotation mark 
    while (1) {
        char c = json_file.get();
        if (c == static_cast<char>(-1)) {
            break;
        }

        switch (c)
        {
        case '"':
            if (quotation_count == 0) {
                quotation_count++;
            } else {
                quotation_count--;
            }
            content += c;
            break;
        case '\n':
            if (quotation_count == 0) {
                break;
            }
        case ' ':
            if (quotation_count == 0) {
                break;
            }
        case '\t':
            if (quotation_count == 0) {
                break;
            }
        default:
            content += c;
            break;
        }
    }

    json_file.close();
    return content;
}
