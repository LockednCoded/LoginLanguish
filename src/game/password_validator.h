#ifndef PASSWORDVALIDATOR_H_
#define PASSWORDVALIDATOR_H_

#include <string>
#include <regex>

class PasswordValidator {

public:
    static bool Validate(std::string password);
};

#endif