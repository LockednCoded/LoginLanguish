#include "credentials_stage.h"

bool CredentialsStage::validateStage()
{
    return true;
}

std::string CredentialsStage::getStageErrors(std::vector<std::string> args)
{
    if (args[0].compare("password") == 0){
        // password puzzles
        if (password.compare("ps") == 0)
            return "cannot be 'ps'.";
        
    }
    return "password is:" + password;
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