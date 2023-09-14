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
