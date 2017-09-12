//
// Created by guy on 9/10/17.
//


#include <utility>
#include <stdexcept>
#include <memory>
#include <sstream>
#include <unordered_map>
#include "hrml_token.h"
#include "utils.h"
#include "validator.h"

bool HrmlToken::is_close_token() {
    return this->closing_scope_token;
}

void HrmlToken::parse_token(std::stringstream &tokens_stream) {
    tokens_stream >> std::ws;
    if(tokens_stream.get() != ControlChars::TAG_START)
        throw std::invalid_argument(std::string("A tag must begin with ") + static_cast<char>(ControlChars::TAG_START));

    tokens_stream >> std::noskipws;
    while(true)
    {
        char tmp;

        if(tokens_stream.peek() == ControlChars::TAG_END)
        {
            this->current_token_ended = true;
            break;
        }

        tokens_stream >> tmp;
        if(tmp == ControlChars::SPACE)
            break;
        this->m_token_name += tmp;
    }

    if(this->m_token_name.length() < MIN_TAG_NAME_LENGTH)
        throw std::invalid_argument("Tag name is to short at index " + std::to_string(tokens_stream.tellg()));

    // Check if this is a closing tag
    if(this->m_token_name[0] == ControlChars::TAG_CLOSE)
    {

        // Make sure the token was closed with no remaining
        if(!this->current_token_ended)
        {
            tokens_stream >> std::ws;

            if(tokens_stream.peek() != ControlChars::TAG_END)
                throw std::invalid_argument("Closing tag must only contain the tag name");
        }

        // Skip the slash and remove the '>'
        this->m_token_name = this->m_token_name.substr(1);
        this->closing_scope_token = true;
        tokens_stream.ignore();
    }

    if(!Validator::validate_keyword(this->m_token_name))
        throw std::invalid_argument("Tag name is not a keyword!" + std::to_string(tokens_stream.tellg()));

    // If this is an end token, validate the token and exit
    if(this->closing_scope_token)
        return;


    // Parse the current token attributes
    this->parse_token_attributes(tokens_stream);

    // Skip over the token end '>'
    tokens_stream.ignore();

    while(true)
    {

        std::shared_ptr<HrmlToken> child_token = std::make_shared<HrmlToken>();
        child_token->parse_token(tokens_stream);
        if(child_token->is_close_token())
        {
            if(child_token->get_token_name() != this->m_token_name)
                throw std::invalid_argument("Closing tag doesn't match opening tag name: " + std::to_string(tokens_stream.tellg()));

            break;
        }

        this->add_child(child_token);
    }

}

void HrmlToken::add_attribute(std::string name, std::string value) {
    if(!m_attributes.insert(std::make_pair(name, value)).second)
    {
        throw std::invalid_argument("Attribute " + name + " already exists in " + this->m_token_name);
    }
}

void HrmlToken::add_child(std::shared_ptr<HrmlToken> token) {
    if(!m_children.insert(std::make_pair(token->get_token_name(), token)).second)
    {
        throw std::invalid_argument("Child tag " + token->get_token_name() + " already exists in " + this->m_token_name);
    }
}

void HrmlToken::parse_token_attributes(std::stringstream &token_stream) {
    while(token_stream.peek() != ControlChars::TAG_END)
    {
        // Skip whitespaces
        token_stream >> std::ws;

        // Get the attribute name
        std::string tmp_attribute_name;
        std::getline(token_stream >> std::ws, tmp_attribute_name, static_cast<char>(ControlChars::ATTR_EQU));
        if(tmp_attribute_name.length() < MIN_ATTR_NAME_LENGTH)
            throw std::invalid_argument(
                    "Tag attribute name is to short at index " + std::to_string(this->m_token_name.length()) + " in tag " + this->m_token_name);

        // Trim any spaces after the attribute name
        right_trim(tmp_attribute_name);

        if(!Validator::validate_keyword(tmp_attribute_name))
            throw std::invalid_argument("Attribute name must a keyword: " + std::to_string(token_stream.tellg()));


        // Skip whitespaces
        token_stream >> std::ws;
        if(token_stream.get() != ControlChars::ATTR_VALUE_Q)
            throw std::invalid_argument("Attribute value must be a string. index " + std::to_string(token_stream.tellg()));


        // We don't support escaping
        std::string tmp_attribute_value;
        std::getline(token_stream, tmp_attribute_value, static_cast<char>(ControlChars::ATTR_VALUE_Q));

        this->add_attribute(tmp_attribute_name, tmp_attribute_value);
    }
}

std::string HrmlToken::get_token_name() const {
    return this->m_token_name;
}

std::shared_ptr<HrmlToken> HrmlToken::get_child_by_name(std::string name) {
    auto tmp_token = this->m_children.find(name);
    if (tmp_token == this->m_children.end())
        return nullptr;
    return this->m_children.at(name);
}

std::string HrmlToken::get_attribute_by_name(const std::string &attr_name) {
    auto attr = this->m_attributes.find(attr_name);
    if(attr == this->m_attributes.end())
        return "Not Found!";

    return attr->second;
}
