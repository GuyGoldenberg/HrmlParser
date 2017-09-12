//
// Created by guy on 9/10/17.
//

#include <string>
#include <sstream>
#include <memory>
#include "hrml.h"

std::string Hrml::run_cmd(const std::string &cmd) {
    std::stringstream cmd_stream(cmd);
    std::string command;
    std::shared_ptr<HrmlToken> last_token = nullptr;

    // Go over the children to find the last child
    while(std::getline(cmd_stream, command, '.') && !cmd_stream.eof())
    {
        auto tmp_token = this->root_tokens.find(command);
        if(last_token == nullptr)
        {
            if(tmp_token == this->root_tokens.end())
                return "Not Found!";

            last_token = tmp_token->second;
            continue;
        }
        last_token = last_token->get_child_by_name(command);
    }


    std::string real_last_token_name;
    std::stringstream last_command_stream(command);
    // Find the last token name
    std::getline(last_command_stream, real_last_token_name, '~');

    std::string attribute_name;

    // Find the attribute name
    std::getline(last_command_stream, attribute_name);

    // If we want to get an attribute of a root token
    if(last_token == nullptr)
    {
        auto tmp_ptr = this->root_tokens.find(real_last_token_name);
        if (tmp_ptr == this->root_tokens.end())
            return "Not Found!";

        last_token = tmp_ptr->second;
    }
    else
        last_token = last_token->get_child_by_name(real_last_token_name);

    // Make sure we managed to find the token
    if(last_token == nullptr)
        return "Not Found!";

    return last_token->get_attribute_by_name(attribute_name);
}

Hrml::Hrml(std::string raw_hrml) {
    std::stringstream hrml_stream(raw_hrml);
    hrml_stream.exceptions(std::ios::failbit);

    while (hrml_stream.tellg() != raw_hrml.length()) {
        std::shared_ptr<HrmlToken> root_token = std::make_shared<HrmlToken>();
        root_token->parse_token(hrml_stream);
        root_tokens[root_token->get_token_name()] = root_token;
    }
}
