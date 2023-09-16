#include "credentials_stage.h"
#include <vector>
#include <iostream>

bool isPalindrome(const std::string& str);
bool isPrime(int n);
bool hasPrime(const std::string& input);

bool CredentialsStage::validateStage()
{
    return true;
}

std::vector<std::string> CredentialsStage::getStageErrors(std::vector<std::string> args)
{
    std::vector<std::string> errors;
    // password puzzles
    if (args[0].compare("password") == 0){
        std::string digits = "0123456789";
        std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string special = "!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?`~";
        std::string roman = "IVXLCDM";

        // int numDigits = 0;
        // int numLowercase = 0;
        // int numUppercase = 0;
        // bool containsSpecial = false;

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
        } else if (password.find_first_of(roman) == std::string::npos){         // missing Roman numeral(s)
            errors.push_back(missingRomanNumError);
        } else if (!isPalindrome(password)){                                    // is not a palindrome
            errors.push_back(notPalindromeError);
        } else if (password.length() > 12){                                     // maximum length exceeded
            errors.push_back(tooLongError);
        }
    }
    return errors;
}

void CredentialsStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("username") == 0)
        username = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("password") == 0)
        password = req[REQ_VALUE_INDEX].GetString();
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


// helper function to check if a string (input) is a palindrome.
bool isPalindrome(const std::string& input){
    // find midpoint of the password
    int midpoint = input.length() / 2;
    
    // check if the first half is the same as the second half reversed
    for (int i = 0; i < midpoint; i++) {
        if (input[i] != input[input.length() - i - 1]) {
            return false;
        }
    }
    return true;
}

// helper function to check if an int (n) is prime.
bool isPrime(int n){
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// helper function to check if a string (input) contains any prime numbers.
bool hasPrime(const std::string& input){
    std::string numStr;
    // iterate through string and extract digits
    for (char c : input){
        if (isdigit(c))
            numStr += c;
    }
    std::cout << numStr;

    for (int front = 0; front < numStr.length()-1; front++){
        for (int back = front+1; back < numStr.length(); back++){
            std::string subStr = input.substr(front, back+1);
            std::cout << subStr;
            int num = std::stoi(subStr);
            if (isPrime(num))
                return true;
        }
    }
    return false;
}