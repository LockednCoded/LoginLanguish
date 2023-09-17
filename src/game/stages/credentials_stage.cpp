/*!
    @file credentials_stage.cpp
    @brief the implementation of the CredentialsStage class
    @author Jack Searle, Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include "credentials_stage.h"
#include <vector>
#include <algorithm>

bool isPalindrome(std::string str);
bool isPrime(int n);
bool hasPrime(std::string input);
bool hasColour(std::string input);

/*!
    @brief constructor for CredentialsStage
    @param gameManager the game manager object owning this stage
*/
CredentialsStage::CredentialsStage(GameManager *gameManager){
    name = "credentials";
    gm = gameManager;
    field_errors = {
        {"username", std::vector<std::string>()},
        {"password", std::vector<std::string>()}
    };
}

/*!
    @brief validates the stage
    @details validates the stage by checking if the requirements are met
    @return true if the stage is valid, false otherwise
*/
bool CredentialsStage::validateStage()
{
    //TODO: implement this
    return true;
}

/*!
    @brief updates error messages
    @details updates the error messages for the given field
    @param field the name of the field to update
*/
void CredentialsStage::updateErrors(std::string field)
{
    std::vector<std::string> errors;
    // password puzzles
    if (field.compare("password") == 0){
        // strings of characters to find in password
        std::string digits = "0123456789";
        std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
        std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string special = "!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?`~";
        std::string roman = "IVXLCDM";
        // get initials
        Stage* nameStage = gm->getStage("name");
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Value fieldStates = nameStage->getFieldStates(doc.GetAllocator());
        std::string fName = fieldStates["firstName"]["value"].GetString();
        std::string lName = fieldStates["lastName"]["value"].GetString();
        std::string initials = std::string(1, fName[0]) + std::string(1, lName[0]);
        std::transform(initials.begin(), initials.end(), initials.begin(), [](unsigned char c) { return std::tolower(c); });
        // create a lowercase copy of password to test against initials
        std::string lowercasePW = password;
        std::transform(lowercasePW.begin(), lowercasePW.end(), lowercasePW.begin(), [](unsigned char c) { return std::tolower(c); });


        if (password.length() == 0){                                            // empty password
            //do nothing                                                        
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
        } else if (lowercasePW.find(initials) == std::string::npos){            // missing user initials
            errors.push_back(missingInitialsError);
        } else if (!hasColour(password)){                                       // missing colour
            errors.push_back(missingColourError);
        } else if (password.find_first_of(roman) == std::string::npos){         // missing Roman numeral(s)
            errors.push_back(missingRomanNumError);
        } else if (!isPalindrome(password)){                                    // is not a palindrome
            errors.push_back(notPalindromeError);
        } else if (password.length() > 22){                                     // maximum length exceeded
            errors.push_back(tooLongError);
        }

        field_errors["password"] = errors;
    }
}

/*!
    @brief updates the stage
    @details updates the stage using the given request parameters
    @param req the request to update the stage with
*/
void CredentialsStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("username") == 0)
        username = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("password") == 0)
        password = req[REQ_VALUE_INDEX].GetString();

    updateErrors(field);
}

/*!
    @brief creates the JSON object for the field states
    @details creates the rapidjson::Value for the aggregated field states
    @param allocator The rapidjson::Document::AllocatorType object used to allocate memory for the JSON objects.
    @return the field states
    @ref Stage::createFieldState
*/
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


/*!
    @brief checks if a string is a palindrome
*/
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

/*!
    @brief checks if a number is prime
*/
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

/*!
    @brief checks if a string contains a prime number
    @details this checks entire numbers; 15 will be read as 15, not 1 and 5.
*/
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

/*!
    @brief checks if a string contains a colour
*/
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