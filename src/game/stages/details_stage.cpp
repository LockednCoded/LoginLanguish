#include "details_stage.h"

bool DetailsStage::validateStage()
{
    return true;
}

std::map<std::string, std::vector<std::string>> DetailsStage::getStageErrors()
{
    return errors;
}

void DetailsStage::updateStage(std::string args)
{
    
}

std::string DetailsStage::getStageName()
{
    return "details";
}