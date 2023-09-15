#include "credentials_stage.h"

bool CredentialsStage::validateStage()
{
    return true;
}

std::vector<std::string> CredentialsStage::getStageErrors(std::vector<std::string> args)
{   
    std::vector<std::string> errors;
    errors.push_back("password is: " + password);
    return errors;
}

void CredentialsStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();
    if (field.compare("username") == 0)
        username = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("password") == 0)
        password = req[REQ_VALUE_INDEX].GetString();
}

std::string CredentialsStage::getStageName()
{
    return "credentials";
}

rapidjson::Value CredentialsStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value usernameValue(username.c_str(), allocator);
    rapidjson::Value usernameObj = createFieldState("username", usernameValue, allocator);
    fieldStates.AddMember("username", usernameObj, allocator);

    rapidjson::Value passwordValue(password.c_str(), allocator);
    rapidjson::Value passwordObj = createFieldState("password", passwordValue, allocator);
    fieldStates.AddMember("password", passwordObj, allocator);

    return fieldStates;
}
