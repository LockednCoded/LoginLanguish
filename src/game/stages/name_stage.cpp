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

rapidjson::Value NameStage::getStageState(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value stageState(rapidjson::kObjectType);
    rapidjson::Value firstNameObj(rapidjson::kObjectType);
    firstNameObj.AddMember("value", first_name, allocator);
    firstNameObj.AddMember("errors", getStageErrors({"firstName"}), allocator);
    stageState.AddMember("firstName", firstNameObj, allocator);
    rapidjson::Value lastNameObj(rapidjson::kObjectType);
    lastNameObj.AddMember("value", last_name, allocator);
    lastNameObj.AddMember("errors", getStageErrors({"lastName"}), allocator);
    stageState.AddMember("lastName", lastNameObj, allocator);
    return stageState;
};