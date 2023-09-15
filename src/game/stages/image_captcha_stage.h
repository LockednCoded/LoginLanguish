#pragma once

#include "stage.h"

class ImageCaptchaStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void updateField(std::string field, std::string value);
    std::string getStageName();
protected:
    //TODO: tidy up
    std::string name = "imagecaptcha";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::vector<std::string> image_urls;
    std::string challenge_text = "";
    std::vector<int> selected;
};