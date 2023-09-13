#include "credentials_stage.h"

bool CredentialsStage::validateStage()
{
    return true;
}

std::map<std::string, std::vector<std::string>> CredentialsStage::getStageErrors()
{
    return errors;
}

void CredentialsStage::updateStage(std::string args)
{
    
}

std::string CredentialsStage::getStageName()
{
    return "credentials";
}