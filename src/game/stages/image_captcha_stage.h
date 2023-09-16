#pragma once

#include "stage.h"
#include "../game_manager.h"

class ImageCaptchaStage : public Stage {
public:
    ImageCaptchaStage(GameManager *gameManager);

    bool validateStage();
    std::vector<std::string> getStageErrors(std::vector<std::string> args);
    void update(const rapidjson::Value &req);
    std::string getStageName();
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
protected:
    //TODO: tidy up
    std::string name = "imagecaptcha";
    
private:
    GameManager* gm;
    std::vector<std::string> image_urls;
    std::string challenge_text = "";
    std::vector<int> selected;
};