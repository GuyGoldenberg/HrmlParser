//
// Created by guy on 9/10/17.
//

#ifndef LEARNING_HRML_TOKEN_H
#define LEARNING_HRML_TOKEN_H

/**
 *  This class is used to parse an HRML token
 *  The parsing includes all of the token children
 *  Each token contains a map of all of his children
 */
class HrmlToken {
public:
    /**
     * @return true if the token is a closing token (starts with '/')
     */
    bool is_close_token();

    /**
     * This function is used to parse an entire tag with it children tags
     * @param tokens_stream A stream of the tag data
     */
    void parse_token(std::stringstream &tokens_stream);

    /**
     * Get the name of the current token
     * @return The token name
     */
    std::string get_token_name() const;

    /**
     * Get a one of the child tokens of the current token by it's name
     * @param name The name of the child token
     */
    std::shared_ptr<HrmlToken> get_child_by_name(std::string name);

    /**
     * Get an attribute value by name
     * @param attr_name The name of the attribute
     * @return The value of the attribute
     */
    std::string get_attribute_by_name(const std::string& attr_name);

private:
    /**
     * This function is used to parse the token attributes
     * @param token_stream The current stream of the token, after parsing the token name
     */
    void parse_token_attributes(std::stringstream &token_stream);

    /**
     * Add a new attribute to the tag
     * @param name The name of the attribute (the key)
     * @param value The value of the attribute
     * @throws std::invalid_argument
     */
    void add_attribute(std::string name, std::string value);

    /**
     * Add a new child to the current token
     * @param token A token to add to the childs
     * @throws std::invalid_argument
     */
    void add_child(std::shared_ptr<HrmlToken> token);

    // The name of the token
    std::string m_token_name{};
    // The attributes of the token
    std::unordered_map<std::string, std::string> m_attributes;
    // The children tokens of the current token
    std::unordered_map<std::string, std::shared_ptr<HrmlToken>> m_children;

    static const uint32_t MIN_TAG_NAME_LENGTH = 1;
    static const uint32_t MIN_ATTR_NAME_LENGTH = 1;
    bool closing_scope_token = false;
    bool current_token_ended = false;
};


#endif //LEARNING_HRML_TOKEN_H
