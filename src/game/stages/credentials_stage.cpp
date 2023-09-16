/*!
 @file credentials_stage.cpp
 @brief credentials stage validation
 @author Jack Searle
 @copyright 2023 Locked & Coded
*/

#include "credentials_stage.h"
#include <vector>
#include <algorithm>

bool isPalindrome(std::string str);
bool isPrime(int n);
bool hasPrime(std::string input);
bool hasColour(std::string input);

bool CredentialsStage::validateStage()
{
    return true;
}

/*!
 @brief validates password input and returns errors (puzzle tasks)
 @details checks password input against a set of conditions
 @return vector containing first error message
*/
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
        } else if (!hasPrime(password)){                                        // missing prime number(s)
            errors.push_back(missingPrimeError);
        } else if (!hasColour(password)){                                       // missing colour
            errors.push_back(missingColourError);
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


// helper function to check if a string (input) is a palindrome.
bool isPalindrome(std::string input){
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
// this checks entire numbers; 15 will be read as 15, not 1 and 5.
bool hasPrime(std::string input){
    std::vector<int> numbers;
    std::string numStr;
    // iterate through string and append any number to nums
    for (int i = 0; i < input.length(); i++){
        if (isdigit(input[i]))
            numStr += input[i];
        if (numStr.length() > 0 && (!isdigit(input[i]) || i == input.length()-1)){
            numbers.push_back(std::stoi(numStr));
            numStr = "";
        }
    }
    // iterate through numbers and check if they are prime
    for (int num : numbers){
        if (isPrime(num))
            return true;
    }
    return false;
}

// helper function to check if a string contains a colour
bool hasColour(std::string input){
    // vector of all accepted colours
    std::vector<std::string> colours = {
        "red", "orange", "yellow", "green", "blue", "indigo", "violet",
        "black", "white", "gray", "grey", "pink", "brown", "purple",
        "cyan", "magenta", "lime", "olive", "maroon", "navy", "teal",
        "lavender", "turquoise", "gold", "silver", "bronze", "beige",
        "salmon", "coral", "orchid", "peru", "khaki", "crimson",
        "chartreuse", "aqua", "plum", "sienna", "turquoise", "almond",
        "slate", "sepia", "azure", "ivory", "tan", "sapphire", "ruby",
        "stone", "jade", "peach", "mauve", "indigo", "mahogany",
        "lilac", "rose", "wine", "snow", "smoke", "egg", "bronze",
        "fuchsia", "apricot", "ash", "azure", "blush", "burgundy", 
        "camel", "charcoal", "chestnut", "chocolate", "copper", "cream",
        "desert", "ebony", "grape", "lemon", "maroon", "moss", 
        "mustard", "onyx", "crayola", "pantone", "bud", "pine", "puce",
        "berry", "rust", "sand", "shell", "sky", "vanilla", "tuscan"
    };
    // convert input to lowercase
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
    // iterate through colours and check if they are in the string
    for (std::string colour : colours){
        if (input.find(colour) != std::string::npos)
            return true;
    }
    return false;
}