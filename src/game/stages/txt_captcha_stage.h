#pragma once

#include "stage.h"

class TxtCaptchaStage : public Stage {
public:
    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void updateStage(std::vector<std::string> args);
    std::string getStageName();
protected:
    std::string name = "txtcaptcha";
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    std::string username = "";
    std::string password = "";
};