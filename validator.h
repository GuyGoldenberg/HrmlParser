//
// Created by guy on 9/10/17.
//
#include <regex>

#ifndef LEARNING_VALIDATOR_H
#define LEARNING_VALIDATOR_H

class Validator {
public:
    /**
     * This function validates that a given string is a keyword
     * @param keyword_candidate A possible keyword candidate
     * @return Whether the candidate is a keyword or not
     */
    static bool validate_keyword(const std::string& keyword_candidate);

private:
    // A keyword regex
    static const std::regex KEYWORD_REGEX;
};


#endif //LEARNING_VALIDATOR_H
