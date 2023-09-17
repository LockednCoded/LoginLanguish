/*!
    @file image_captcha_stage.h
    @brief the ImageCaptchaStage class is the class that represents the image captcha stage of the game
    @author Cameron Bruce
    @copyright 2023 Locked & Coded
*/

#pragma once

#include "stage.h"
#include "../game_manager.h"

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
    
private:
    void updateErrors(std::string field);

    std::vector<std::string> listSubdirectories(std::string path);
    std::vector<std::string> listFiles(std::string path);
    int randomInt(int min, int max);
    std::vector<std::string> getNRandomFiles(int n, std::string directory);
    std::vector<std::string> getNRandomFilesFromSubdirectories(int n, std::vector<std::string> directories);

    GameManager* gm;
    std::vector<std::string> image_urls;
    std::vector<std::string> correct_images;
    std::string challenge_text = "";
    std::vector<int> selected;
};