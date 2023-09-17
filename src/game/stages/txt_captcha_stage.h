/*!
    @file txt_captcha_stage.h
    @brief the TxtCaptchaStage class is the class that represents the text captcha stage of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"
#include <set>

const char MENACING_CAPTCHAS = 0;

/*!
    @brief the TxtCaptchaStage class is a class that represents a txt captcha stage in the game
    @details contains concrete stage implementions for the txt captcha stage in the game
*/
class TxtCaptchaStage : public Stage {
public:
    TxtCaptchaStage(GameManager *gameManager);
    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
    bool setNewChallenge();

private:
    void updateErrors(std::string field);
    void progressStage();
    void rerollChallenge();

    GameManager* gm;

    std::string txt_captcha = "";
    std::string challenge_text = "";
    std::string image_url = "";
    std::set<char> challenges_remaining = {MENACING_CAPTCHAS};
    char current_challenge = 0;
    std::string challenge_answer = "";
    bool captcha_passed = false;
    std::string last_round_error = "";
    std::string current_roll_identifier = ""; // Used to identify the particular item rolled in a given challenge
};