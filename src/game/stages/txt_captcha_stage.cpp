#include "txt_captcha_stage.h"

TxtCaptchaStage::TxtCaptchaStage(GameManager *gameManager){
    name = "txtcaptcha";
    gm = gameManager;
    field_errors = {
        {"txtcaptcha", std::vector<std::string>()}
    };
}

bool TxtCaptchaStage::validateStage()
{
    return true;
}

void TxtCaptchaStage::updateErrors(std::string field)
{   
    //TODO: implement this
}

void TxtCaptchaStage::update(const rapidjson::Value &req)
{
    std::string field = req[REQ_FIELD_INDEX].GetString();

    if (field.compare("txtcaptcha") == 0)
        txt_captcha = req[REQ_VALUE_INDEX].GetString();
    
    updateErrors(field);
}

rapidjson::Value TxtCaptchaStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value txtCaptchaValue(txt_captcha.c_str(), allocator);
    rapidjson::Value txtCaptchaObj = createFieldState("txtcaptcha", txtCaptchaValue, allocator);
    fieldStates.AddMember("txtcaptcha", txtCaptchaObj, allocator);

    rapidjson::Value imageUrlValue(image_url.c_str(), allocator);
    fieldStates.AddMember("imageURL", imageUrlValue, allocator);

    rapidjson::Value challengeTextValue(challenge_text.c_str(), allocator);
    fieldStates.AddMember("challengeText", challengeTextValue, allocator);

    return fieldStates;
};