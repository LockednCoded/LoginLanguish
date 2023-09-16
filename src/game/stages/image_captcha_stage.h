#pragma once

#include "stage.h"
#include "../game_manager.h"

class ImageCaptchaStage : public Stage {
public:
    ImageCaptchaStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
    
private:
    void updateErrors(std::string field);
    GameManager* gm;
    std::vector<std::string> image_urls;
    std::string challenge_text = "";
    std::vector<int> selected;
};