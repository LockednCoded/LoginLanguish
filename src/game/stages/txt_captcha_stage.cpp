#include "txt_captcha_stage.h"

bool TxtCaptchaStage::validateStage()
{
    return true;
}

std::vector<std::string> TxtCaptchaStage::getStageErrors(std::vector<std::string> args)
{   
    std::vector<std::string> errors;
    return errors;
}

void TxtCaptchaStage::updateField(std::string field, std::string value)
{
    
}

std::string TxtCaptchaStage::getStageName()
{
    return "txtcaptcha";
}

rapidjson::Value TxtCaptchaStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value txtCaptchaValue(txt_captcha.c_str(), allocator);
    rapidjson::Value txtCaptchaObj = createFieldState("txtcaptcha", txtCaptchaValue, allocator);
    fieldStates.AddMember("txtcaptcha", txtCaptchaObj, allocator);

    rapidjson::Value imageUrlValue(image_url.c_str(), allocator);
    fieldStates.AddMember("imageURL", imageUrlValue, allocator);

    return fieldStates;
};