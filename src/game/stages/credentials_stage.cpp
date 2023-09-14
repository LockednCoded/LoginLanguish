#include "credentials_stage.h"

bool CredentialsStage::validateStage()
{
    return true;
}

std::string CredentialsStage::getStageErrors(std::vector<std::string> args)
{
    if (args[0].compare("password") == 0){
        // password puzzles
        if (password.length() < 8)
            return "Password must include 8 or more characters.";
        if (password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
            return "Password must include atleast one capital letter (A-Z).";
        if (password.find_first_of("0123456789") != std::string::npos)
            return "Password must include atleast one digit (0-9).";
        bool containsSymbol = false;
        for (char c : password){
            if (!std::isalnum(c)){
                containsSymbol = true;
                break;
            }
        }
        if (!containsSymbol)
            return "Password must include atleast one special character.";
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