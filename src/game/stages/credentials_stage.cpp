#include "credentials_stage.h"

bool CredentialsStage::validateStage()
{
    return true;
}

std::string CredentialsStage::getStageErrors(std::vector<std::string> args)
{
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

rapidjson::Value CredentialsStage::getStageState(rapidjson::Document::AllocatorType &allocator)
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
