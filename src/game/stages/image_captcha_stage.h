/*!
    @file image_captcha_stage.h
    @brief The ImageCaptchaStage class is a class that represents the extras stage in the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

/*!
    @brief The ImageCaptchaStage class is a class that represents a image captcha stage in the game.
    @details The ImageCaptchaStage class is a class that represents a image captcha stage in the game. It contains
    concrete stage implementions for the image captcha stage in the game.
*/
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