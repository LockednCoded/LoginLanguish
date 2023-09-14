#include "txt_captcha_stage.h"

bool TxtCaptchaStage::validateStage()
{
    return true;
}

std::string TxtCaptchaStage::getStageErrors(std::vector<std::string> args)
{
    return "";
}

void TxtCaptchaStage::updateStage(std::vector<std::string> args)
{
    
}

std::string TxtCaptchaStage::getStageName()
{
    return "txtcaptcha";
}

rapidjson::Value TxtCaptchaStage::getStageState(rapidjson::Document::AllocatorType &allocator)
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