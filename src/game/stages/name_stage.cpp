#include "name_stage.h"

bool NameStage::validateStage()
{
    return true;
}

std::map<std::string, std::vector<std::string>> NameStage::getStageErrors()
{
    return errors;
}

void NameStage::updateStage(std::string args)
{
    
}

std::string NameStage::getStageName()
{
    return "name";
}