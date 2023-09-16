/*!
    @file txt_captcha_stage.h
    @brief The TxtCaptchaStage class is a class that represents the name stage in the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

/*!
    @brief The TxtCaptchaStage class is a class that represents a txt captcha stage in the game.
    @details The TxtCaptchaStage class is a class that represents a txt captcha stage in the game. It contains
    concrete stage implementions for the txt captcha stage in the game.
*/
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