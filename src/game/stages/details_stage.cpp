#include "details_stage.h"

bool DetailsStage::validateStage()
{
    return true;
}

std::vector<std::string> DetailsStage::getStageErrors(std::vector<std::string> args)
{
    std::vector<std::string> errors;
    return errors;
}

void DetailsStage::updateField(std::string field, std::string value)
{
    
}

std::string DetailsStage::getStageName()
{
    return "details";
}

rapidjson::Value DetailsStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value usernameValue(username.c_str(), allocator);
    rapidjson::Value usernameObj = createFieldState("username", usernameValue, allocator);
    fieldStates.AddMember("username", usernameObj, allocator);

    rapidjson::Value passwordValue(password.c_str(), allocator);
    rapidjson::Value passwordObj = createFieldState("password", passwordValue, allocator);
    fieldStates.AddMember("password", passwordObj, allocator);

    return fieldStates;
};