//
// Created by guy on 9/10/17.
//
#include <string>
#include <algorithm>

#ifndef LEARNING_UTILS_H_H
#define LEARNING_UTILS_H_H

/**
 * This function is used to trim whitespaces after a given string
 * @param A string to trim
 */
static inline void right_trim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !static_cast<bool>(std::isspace(ch));
    }).base(), s.end());
}

/**
 * Defines a set of control chars for the parsing process
 */
enum ControlChars : char {
    TAG_START           = '<',
    TAG_END             = '>',
    SPACE               = ' ',
    ATTR_EQU            = '=',
    ATTR_VALUE_Q        = '"',
    TAG_CLOSE           = '/'
};


#endif //LEARNING_UTILS_H_H
