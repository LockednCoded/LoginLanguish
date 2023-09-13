#include "name_stage.h"

bool NameStage::validateStage()
{
    return true;
}

std::string NameStage::getStageErrors(std::vector<std::string> args)
{
    return "";
}

void NameStage::updateStage(std::vector<std::string> args)
{
    if (args[0].compare("firstName") == 0)
        first_name = args[1];
    else if (args[0].compare("lastName") == 0)
        last_name = args[1];
}

std::string NameStage::getStageName()
{
    return "name";
}