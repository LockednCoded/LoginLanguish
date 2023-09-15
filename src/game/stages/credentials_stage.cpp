#include "credentials_stage.h"

bool CredentialsStage::validateStage()
{
    return true;
}

std::string CredentialsStage::getStageErrors(std::vector<std::string> args)
{
    // password puzzles
    if (args[0].compare("password") == 0){
        // minimum length
        if (password.length() < 8)
            return "Password must include 8 or more characters."; // "Minimum password length not yet reached"?
        // contains a capital letter
        if (password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
            return "Password must include atleast one capital letter (A-Z).";
        // contains a digit
        if (password.find_first_of("0123456789") != std::string::npos)
            return "Password must include atleast one digit (0-9).";
        // conatins a special character    
        bool containsSymbol = false;
        for (char c : password){
            if (!std::isalnum(c)){
                containsSymbol = true;
                break;
            }
        }
        if (!containsSymbol)
            return "Password must include atleast one special character.";
        // maximum length
        if (password.length() > 12)
            return "Password must be 12 or less characters."; // "Maximum password length exceeded"?
    }
    return "password is: " + password;
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
