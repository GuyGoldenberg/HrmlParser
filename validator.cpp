//
// Created by guy on 9/10/17.
//
#include "validator.h"

const std::regex Validator::KEYWORD_REGEX = std::regex {R"(^([^\d\W][\w-]*)$)"};

bool Validator::validate_keyword(const std::string &keyword_candidate) {
    std::smatch m;
    return std::regex_match(keyword_candidate, m, KEYWORD_REGEX);
}
