#include "credentials_stage.h"
#include <vector>

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
        // iterate through password and update fields
        for (char c : password){
            if (lowercase.find(c) != std::string::npos){        // char is lowercase
                numLowercase++;
                continue;
            } else if (uppercase.find(c) != std::string::npos){ // char is uppercase
                numUppercase++;
                continue;
            } else if (digits.find(c) != std::string::npos){    // char is digit
                numDigits++;
                continue;
            } else {                                            // char is special character
                containsSpecial = true;
            }
        }

        // empty password
        if (password.length() == 0)
            return errors;
        // minimum length
        if (password.length() < 8)
            errors.push_back(tooShortError); 
        // contains an uppercase letter
        if (numUppercase < 1)
            errors.push_back(missingUppercaseError);
        // contains a digit
        if (numDigits < 1)
            errors.push_back(missingDigitError);
        // contains a special character    
        if (!containsSpecial)
            errors.push_back(missingSpecialError);
        
        // maximum length
        if (password.length() > 12)
            errors.push_back(tooLongError);
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

rapidjson::Value CredentialsStage::getStageState(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value stageState(rapidjson::kObjectType);
    rapidjson::Value usernameObj(rapidjson::kObjectType);
    rapidjson::Value usernameValue(username.c_str(), allocator);
    usernameObj.AddMember("value", usernameValue, allocator);
    rapidjson::Value usernameErrors(getStageErrors({"username"}).c_str(), allocator);
    usernameObj.AddMember("errors", usernameErrors, allocator);
    rapidjson::Value passwordObj(rapidjson::kObjectType);
    rapidjson::Value passwordValue(password.c_str(), allocator);
    passwordObj.AddMember("value", passwordValue, allocator);
    rapidjson::Value passwordErrors(getStageErrors({"password"}).c_str(), allocator);
    passwordObj.AddMember("errors", passwordErrors, allocator);

    return stageState;
};
