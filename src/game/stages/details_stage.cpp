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
    usernameObj.AddMember("value", username, allocator);
    usernameObj.AddMember("errors", getStageErrors({"username"}), allocator);
    stageState.AddMember("firstName", usernameObj, allocator);
    rapidjson::Value passwordObj(rapidjson::kObjectType);
    passwordObj.AddMember("value", password, allocator);
    passwordObj.AddMember("errors", getStageErrors({"password"}), allocator);
    stageState.AddMember("lastName", passwordObj, allocator);
    return stageState;
};