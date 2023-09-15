#pragma once

#include "stage.h"

class TxtCaptchaStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
protected:
    std::string name = "txtcaptcha";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::string txt_captcha = "";
    std::string image_url = "";
};