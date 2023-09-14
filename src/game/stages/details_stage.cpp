#include "details_stage.h"

bool DetailsStage::validateStage()
{
    return true;
}

std::string DetailsStage::getStageErrors(std::vector<std::string> args)
{
    return "";
}

void DetailsStage::updateStage(std::vector<std::string> args)
{
    
}

std::string DetailsStage::getStageName()
{
    return "details";
}

rapidjson::Value DetailsStage::getStageState(rapidjson::Document::AllocatorType &allocator)
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