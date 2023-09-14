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
    usernameObj.AddMember("value", username, allocator);
    usernameObj.AddMember("errors", getStageErrors({"username"}), allocator);
    stageState.AddMember("firstName", usernameObj, allocator);
    rapidjson::Value passwordObj(rapidjson::kObjectType);
    passwordObj.AddMember("value", password, allocator);
    passwordObj.AddMember("errors", getStageErrors({"password"}), allocator);
    stageState.AddMember("lastName", passwordObj, allocator);
    return stageState;
};