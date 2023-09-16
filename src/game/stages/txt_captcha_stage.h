#pragma once

#include "stage.h"
#include "../game_manager.h"

class TxtCaptchaStage : public Stage {
public:
    TxtCaptchaStage(GameManager *gameManager);
    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
private:
    void updateErrors(std::string field);

    GameManager* gm;
    
    std::string txt_captcha = "";
    std::string challenge_text = "";
    std::string image_url = "";
};