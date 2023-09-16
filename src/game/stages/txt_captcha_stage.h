#pragma once

#include "stage.h"
#include "../game_manager.h"

class TxtCaptchaStage : public Stage {
public:
    TxtCaptchaStage(GameManager *gameManager);

    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
protected:
    std::string name = "txtcaptcha";
    
private:
    GameManager* gm;
    std::string txt_captcha = "";
    std::string challenge_text = "";
    std::string image_url = "";
};