#include "image_captcha_stage.h"

bool ImageCaptchaStage::validateStage()
{
    return true;
}

std::vector<std::string> ImageCaptchaStage::getStageErrors(std::vector<std::string> args)
{   
    std::vector<std::string> errors;
    return errors;
}

void ImageCaptchaStage::updateField(std::string field, std::string value)
{
    if (field.compare("selected") == 0) {
        //TODO: implement this

    }
}

std::string ImageCaptchaStage::getStageName()
{
    return "imagecaptcha";
}

rapidjson::Value ImageCaptchaStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
    rapidjson::Value fieldStates(rapidjson::kObjectType);

    rapidjson::Value imagesValue(rapidjson::kArrayType);
    for (std::string image : image_urls) {
        rapidjson::Value imageValue(image.c_str(), allocator);
        imagesValue.PushBack(imageValue, allocator);
    }
    fieldStates.AddMember("images", imagesValue, allocator);

    rapidjson::Value challengeTextValue(challenge_text.c_str(), allocator);
    fieldStates.AddMember("challengeText", challengeTextValue, allocator);

    rapidjson::Value selectedValue(rapidjson::kArrayType);
    for (int i : selected) {
        rapidjson::Value intValue(i);
        selectedValue.PushBack(intValue, allocator);
    }
    fieldStates.AddMember("selected", selectedValue, allocator);

    return fieldStates;
};