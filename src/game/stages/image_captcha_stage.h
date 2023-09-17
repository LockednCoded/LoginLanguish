/*!
    @file image_captcha_stage.h
    @brief the ImageCaptchaStage class is the class that represents the image captcha stage of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

#include <filesystem>

namespace fs = std::filesystem;

/*!
    @brief the ImageCaptchaStage class is a class that represents a image captcha stage in the game
    @details contains concrete stage implementions for the image captcha stage in the game
*/
class ImageCaptchaStage : public Stage {
public:
    ImageCaptchaStage(GameManager *gameManager);

    bool validateStage();
    void update(const rapidjson::Value &req);
    rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);
    virtual void progressStage();
    
private:
    void updateErrors(std::string field);
    void initialiseCaptchaImages();

    std::vector<std::string> image_urls;
    std::vector<std::string> correct_images;
    std::string challenge_text = "";
    std::vector<std::string> selected;
    std::string last_round_error = "";
    size_t current_round = 0;
    std::vector<fs::path> challenge_sets;
};