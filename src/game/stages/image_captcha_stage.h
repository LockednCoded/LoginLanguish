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
#include <set>

const char CELEB_CAPTCHAS = 0;
const char MUFFIN_DOG_CAPTCHAS = 1;
const char FREEDOM_CAPTCHAS = 2;

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
    void initialiseDatasetImages(fs::path dataset_path, size_t MAX_NUM_IMAGES, size_t MAX_NUM_CORRECT, size_t MIN_NUM_CORRECT);
    void initialiseCountryImages(size_t num_correct, size_t total_num);

    char current_challenge = 0;
    void initialiseChallenge();
    bool setNewChallenge();
    std::set<char> challenges_remaining = {CELEB_CAPTCHAS, MUFFIN_DOG_CAPTCHAS, FREEDOM_CAPTCHAS};
    std::vector<std::string> image_urls;
    std::vector<std::string> image_labels; // The labels for each image, to be displayed to the user. Can be empty.
    std::vector<std::string> correct_images;
    std::string challenge_text = "";
    std::vector<std::string> selected;
    std::string last_round_error = "";
    std::vector<fs::path> challenge_sets;
};