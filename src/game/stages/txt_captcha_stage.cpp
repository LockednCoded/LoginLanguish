#include "txt_captcha_stage.h"

TxtCaptchaStage::TxtCaptchaStage(GameManager *gameManager){
    gm = gameManager;
};

bool TxtCaptchaStage::validateStage()
{
    return true;
}

std::vector<std::string> TxtCaptchaStage::getStageErrors(std::vector<std::string> args)
{   
    std::vector<std::string> errors;
    return errors;
}

void TxtCaptchaStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();

    if (field.compare("txtcaptcha") == 0)
        txt_captcha = req[REQ_VALUE_INDEX].GetString();
    else if (field.compare("imageURL") == 0)
        image_url = req[REQ_VALUE_INDEX].GetString();
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