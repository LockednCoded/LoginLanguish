#include "password_validator.h"

bool PasswordValidator::Validate(std::string password) {
    //regex to check if password contains only alphanumeric characters
    std::regex regex = std::regex("[a-zA-Z0-9]+", std::regex::ECMAScript);

    return (password.length() >= 1 && !std::regex_match(password, regex));
}