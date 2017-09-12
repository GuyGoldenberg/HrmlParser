//
// Created by guy on 9/9/17.
//
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <regex>
#include <iostream>
#include "hrml.h"


int main()
{
//    HrmlToken tag {};
//    std::stringstream x{R"(<tag1></tag1><tag2></tag2>)"};
//
//    tag.parse_token(x);

    uint32_t hrml_lines = 0;
    uint n_commands = 0;
    std::cin >> hrml_lines >> n_commands;
    std::stringstream stream;
    std::string hrml_content;
    for(uint32_t i = 0; i <= hrml_lines; i++)
    {
        std::string line;
        std::getline(std::cin, line);
        hrml_content += line;
    }

    std::string commands[n_commands];
    for (std::string& command : commands) {
        std::getline(std::cin, command);
    }


    Hrml hrml {hrml_content};
    for (std::string& command : commands) {
        std::cout << hrml.run_cmd(command) << std::endl;
    }

    
    return 0;
}