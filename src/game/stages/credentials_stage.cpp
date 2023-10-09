/*!
    @file credentials_stage.cpp
    @brief the implementation of the CredentialsStage class
    @author Jack Searle, Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#include "credentials_stage.h"
#include <vector>
#include <algorithm>
#include "password_utils.h"
#include "string_utils.h"

// bool isPalindrome(const std::string &str);
// bool isPrime(int n);
// bool hasPrime(std::string input);
// bool hasColour(std::string input);

/*!
    @brief constructor for CredentialsStage
    @param gameManager the game manager object owning this stage
*/
CredentialsStage::CredentialsStage(GameManager *gameManager) : Stage(gameManager)
{
    name = "credentials";
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
    int numErrors = field_errors["username"].size() + field_errors["password"].size();
    if (numErrors == 0 && username.length() > 0 && password.length() > 0)
        return true;
    return false;
}

/*!
    @brief updates error messages
    @details updates the error messages for the given field
    @param field the name of the field to update
*/
void CredentialsStage::updateErrors(const std::string &field)
{
    Stage* nameStage = gm->getStage("name");
    std::vector<std::string> errors;

    // retrieve name fields
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Value fieldStates = nameStage->getFieldStates(doc.GetAllocator());
    std::string fName = fieldStates["firstName"]["value"].GetString();
    std::string lName = fieldStates["lastName"]["value"].GetString();
    // remove whitespace
    fName.erase(std::remove(fName.begin(), fName.end(), ' '), fName.end());
    lName.erase(std::remove(lName.begin(), lName.end(), ' '), lName.end());
    // remove apostrophes
    fName.erase(std::remove(fName.begin(), fName.end(), '\''), fName.end());
    lName.erase(std::remove(lName.begin(), lName.end(), '\''), lName.end());

    // username
    if (field.compare("username") == 0){
        bool valid = false;
        std::string invalidChars = " !@#$%^&*()=+[]{}\\|;:'\",.<>/?`~";

        // fill vector with valid usernames
        std::vector<std::string> validNames;
        validNames.push_back(fName + "Stinks" + std::to_string(420));
        validNames.push_back("xX_" + fName + "_" + lName + "_Xx");

        // build suggestions string and check if username is valid
        std::string suggestions = "\nConsider ";
        std::string sep = "";
        for (std::string name : validNames){
            suggestions += sep + name;
            sep = ", ";
            if (username.compare(name) == 0)
                valid = true;
        }
        suggestions += ".";

        if (username.length() == 0){
            // do nothing
        } else if (username.length() < 8 || username.length() > 26){            // length out of bounds
            errors.push_back(lengthError);
        } else if (username.find_first_of(invalidChars) != std::string::npos){  // invalid special character(s)
            errors.push_back(invalidCharError);
        } else if (!valid){
            errors.push_back(takenError + suggestions);               
        }

        field_errors["username"] = errors;

    // password
    } else if (field.compare("password") == 0){                                 
        // get lowercase initials from names
        std::string initials = string_utils::toLowerCase(std::string(1, fName[0]) + std::string(1, lName[0]));
        // create a lowercase copy of password to test against initials
        std::string lowercasePW = string_utils::toLowerCase(password);
        

        // password puzzles
        // empty password
        if (password.length() == 0){                                            
            metTooShort = metMissingDigit = metMissingUppercase = metMissingLowercase = metMissingSpecialChar = 
                metMissingPrime = metMissingInitials = metMissingColour = metMissingRomanNumeral = metNotPalindrome = metTooLong = false;
            field_errors["password"] = errors;
            return;                                                       
        }
        // minimum length not reached
        if (password.length() < 8){                                             
            errors.push_back(tooShortError);
            if (!metTooShort){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metTooShort = true;
        }
        // missing digit(s)
        if (password.find_first_of(digits) == std::string::npos){        
            errors.push_back(missingDigitError);
            if (!metMissingDigit){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingDigit = true;
        }
        // missing uppercase letter(s)
        if (password.find_first_of(uppercaseChars) == std::string::npos){
            errors.push_back(missingUppercaseError);
            if (!metMissingUppercase){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingUppercase = true;
        }
        // missing lowercase letter(s)
        if (password.find_first_of(lowercaseChars) == std::string::npos){
            errors.push_back(missingLowercaseError);
            if (!metMissingLowercase){
                
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingLowercase = true;
        }
        // missing special character(s)
        if (password.find_first_of(specialChars) == std::string::npos){  
            errors.push_back(missingSpecialError);
            if (!metMissingSpecialChar){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingSpecialChar = true;
        }
        // missing prime number(s)
        if (!password_utils::hasPrime(password)){                                        
            errors.push_back(missingPrimeError);
            if (!metMissingPrime){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingPrime = true;
        }
        // missing user initials
        if (lowercasePW.find(initials) == std::string::npos){            
            errors.push_back(missingInitialsError);
            if (!metMissingInitials){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingInitials = true;
        }
        // missing colour
        if (!password_utils::hasColour(password)){                                       
            errors.push_back(missingColourError);
            if (!metMissingColour){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingColour = true;
        }
        // missing Roman numeral(s)
        if (password.find_first_of(romanNumerals) == std::string::npos){ 
            errors.push_back(missingRomanNumError);
            if (!metMissingRomanNumeral){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metMissingRomanNumeral = true;
        }
        // is not a palindrome
        if (!password_utils::isPalindrome(password)){                                    
            errors.push_back(notPalindromeError);
            if (!metNotPalindrome){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metNotPalindrome = true;
        }
        // maximum length exceeded
        if (password.length() > 20){                                     
            errors.push_back(tooLongError);
            if (!metTooLong){
                field_errors["password"] = errors;
                return; 
            }
        } else {
            metTooLong = true;
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