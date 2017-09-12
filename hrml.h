#ifndef LEARNING_HRML_H
#define LEARNING_HRML_H

#include <unordered_map>
#include "hrml_token.h"

/**
 * This class is the wrapper for the HRML tag parser
 * It is used to store the root tokens and access their attributes
 */
class Hrml {

public:
    explicit Hrml(std::string raw_hrml);

    /**
     * This function is used to run a command
     * @param cmd A command is 'parent.child~attr1'
     * @return The value of the attribute
     */
    std::string run_cmd(const std::string& cmd);

private:
    std::unordered_map<std::string, std::shared_ptr<HrmlToken>> root_tokens;
};

#endif //LEARNING_HRML_H
