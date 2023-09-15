#include "credentials_stage.h"
#include <vector>

bool isPalindrome(const std::string& str);

bool CredentialsStage::validateStage()
{
    return true;
}

std::vector<std::string> CredentialsStage::getStageErrors(std::vector<std::string> args)
{
    std::vector<std::string> errors;
    std::string password = args[1];
    // password puzzles
    if (args[0].compare("password") == 0){
        int numDigits = 0;
        int numLowercase = 0;
        int numUppercase = 0;
        bool containsSpecial = false;
        std::string digits = "0123456789";
        std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string special = "!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?`~";
        std::string roman = "IVXLCDM";
        
        // iterate through password and update fields
        // for (char c : password){
        //     if (lowercase.find(c) != std::string::npos){        // char is lowercase
        //         numLowercase++;
        //         continue;
        //     } else if (uppercase.find(c) != std::string::npos){ // char is uppercase
        //         numUppercase++;
        //         continue;
        //     } else if (digits.find(c) != std::string::npos){    // char is digit
        //         numDigits++;
        //         continue;
        //     } else if (special.find(c) != std::string::npos){   // char is special character
        //         containsSpecial = true;
        //     }
        // }

        if (password.length() == 0){                                            // empty password
            return errors;
        } else if (password.length() < 8){                                      // minimum length not reached
            errors.push_back(tooShortError);
        } else if (password.find_first_of(digits) == std::string::npos){        // missing digit(s)
            errors.push_back(missingDigitError);
        } else if (password.find_first_of(uppercase) == std::string::npos){     // missing uppercase letter(s)
            errors.push_back(missingUppercaseError);
        } else if (password.find_first_of(lowercase) == std::string::npos){     // missing lowercase letter(s)
            errors.push_back(missingLowercaseError);
        } else if (password.find_first_of(special) == std::string::npos){       // missing special character(s)
            errors.push_back(missingSpecialError);
        } else if (!isPalindrome(password)){                                    // is not a palindrome
            errors.push_back(notPalindromeError);
        } else if (password.length() > 12){                                     // maximum length exceeded
            errors.push_back(tooLongError);
        }
    }
    return errors;
}

void CredentialsStage::updateStage(std::vector<std::string> args)
{
    if (args[0].compare("username") == 0)
        username = args[1];
    else if (args[0].compare("password") == 0)
        password = args[1];
}

std::string CredentialsStage::getStageName()
{
    return "credentials";
}

rapidjson::Value CredentialsStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value usernameValue(username.c_str(), allocator);
    rapidjson::Value usernameObj = createFieldState("username", usernameValue, allocator);
    fieldStates.AddMember("username", usernameObj, allocator);

    rapidjson::Value passwordValue(password.c_str(), allocator);
    rapidjson::Value passwordObj = createFieldState("password", passwordValue, allocator);
    fieldStates.AddMember("password", passwordObj, allocator);

    return fieldStates;
}


bool isPalindrome(const std::string& str) {
    // find midpoint of the password
    int midpoint = str.length() / 2;
    
    // check if the first half is the same as the second half reversed
    for (int i = 0; i < midpoint; i++) {
        if (str[i] != str[str.length() - i - 1]) {
            return false;
        }
    }
    return true;
}