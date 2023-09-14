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
    rapidjson::Value firstnameObj(rapidjson::kObjectType);
    rapidjson::Value firstnameValue(first_name.c_str(), allocator);
    firstnameObj.AddMember("value", firstnameValue, allocator);
    rapidjson::Value firstnameErrors(getStageErrors({"firstName"}).c_str(), allocator);
    firstnameObj.AddMember("errors", firstnameErrors, allocator);
    rapidjson::Value lastnameObj(rapidjson::kObjectType);
    rapidjson::Value lastnameValue(last_name.c_str(), allocator);
    lastnameObj.AddMember("value", lastnameValue, allocator);
    rapidjson::Value lastnameErrors(getStageErrors({"lastName"}).c_str(), allocator);
    lastnameObj.AddMember("errors", lastnameErrors, allocator);
    return stageState;
};